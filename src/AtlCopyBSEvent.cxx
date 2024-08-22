#include <iostream>
#include <optional>
#include <vector>

#include "EventStorage/DataWriter.h"
#include "EventStorage/pickDataReader.h"
#include "eformat/eformat.h"
#include "eformat/old/util.h"

#include <zstd.h>

void eventLoop(std::unique_ptr<DataReader>, std::unique_ptr<EventStorage::DataWriter>, uint64_t, const std::vector<uint64_t>&, uint32_t, bool, bool,
               bool, bool, bool, int);

int main(int argc, char* argv[])
{
    using namespace eformat;

    // Interpret command line arguments
    if (argc < 3) {
        std::cerr << "usage: " << argv[0]
                  << " [-c --compress <level>] [-d --deflate] -e [--event] <eventNumbers> [-r, --run "
                     "<runnumber>] [-l, --listevents] [-t --checkevents] -o, --out "
                     "outputfile "
                     "inputfiles...."
                  << std::endl;
        std::cerr << "eventNumbers is a comma-separated list of events" << std::endl;
        std::exit(1);
    }

    // Initialize program variables
    std::string              fileNameOut("extractedEvents.data");
    std::vector<std::string> fileNames;

    std::vector<uint64_t>    searchEvents;
    std::vector<std::string> searchTokens;
    uint32_t                 searchRun          = 0;
    bool                     searchRunSet       = false;
    bool                     listEvents         = false;
    bool                     checkEvents        = false;
    bool                     writePrecompressed = false;
    bool                     compressData       = false;
    int                      compressionLevel   = 1;
    uint64_t                 nFound             = 0;

    // Process command line arguments
    for (int i = 1; i < argc; i++) {
        const std::string& arg1{argv[i]};

        // Compress event
        if (arg1 == "-d" || arg1 == "--deflate") {
            writePrecompressed = true;
        }
        else if (arg1 == "-c" || arg1 == "--compress") {
            std::string arg2;

            if ((i + 1) < argc)
                arg2 = argv[i + 1];

            // Check if entire argument is a number
            if (std::all_of(arg2.begin(), arg2.end(), ::isdigit) || (arg2[0] == '-' && std::all_of(arg2.begin() + 1, arg2.end(), ::isdigit))) {
                compressionLevel = std::stoi(arg2);
                std::cout << "Compressing using ZSTD with level: " << compressionLevel << "\n";
                i++;
            }

            if (compressionLevel > 22) {
                std::cout << "Maximum compression level is 22.\n";
                return -1;
            }

            compressData = true;
        }
        // Parse numbers of events to be read, or all
        else if (arg1 == "-e" || arg1 == "--event") {
            // try read the list of event number
            std::string arg2;
            if ((i + 1) < argc)
                arg2 = argv[i + 1];
            if (arg2.size() > 0 && isdigit(arg2[0])) {
                size_t p = 0;

                while (p != std::string::npos) {
                    searchEvents.push_back(std::atoll(arg2.c_str() + p));
                    p = arg2.find(',', p);
                    if (p != std::string::npos)
                        p++;
                }
            }
            else if (arg2 == "all")
                std::cout << "Copy all events" << std::endl;
            else {
                std::cout << "ERROR: no numerical argument found after '" << arg1 << "'" << std::endl;
                return -1;
            }
            i++;
        }
        // Set name of output file
        else if (arg1 == "-o" || arg1 == "--out") {
            std::string arg2;
            if ((i + 1) < argc)
                arg2 = argv[i + 1];

            if (arg2.size() > 0)
                fileNameOut = arg2;
            else {
                std::cout << "ERROR: Expected output file name after '" << arg1 << "'" << std::endl;
                return -1;
            }

            i++;
        }

        // Search for specific run/event numbers
        else if (arg1 == "-r" || arg1 == "--run") {
            std::string arg2;
            if ((i + 1) < argc)
                arg2 = argv[i + 1];

            if (arg2.size() > 0 && isdigit(arg2[0]))
                searchRun = std::stoi(arg2);
            else {
                std::cout << "ERROR: no numerical argument found after '" << arg1 << "'" << std::endl;
                return -1;
            }

            i++;
            searchRunSet = true;
        }
        else if (arg1 == "-t" || arg1 == "--checkevents")
            checkEvents = true;
        // List events while running
        else if (arg1 == "-l" || arg1 == "--listevents")
            listEvents = true;
        // Add any input files to fileNames
        else
            fileNames.push_back(arg1);
    }
    // End loop over arguments

    std::sort(searchEvents.begin(), searchEvents.end());

    std::cout << "Events to copy: ";
    for (auto itEvt1 = searchEvents.begin(); itEvt1 != searchEvents.end(); ++itEvt1) {
        std::cout << *itEvt1 << " ";
    }
    std::cout << std::endl;

    std::unique_ptr<EventStorage::DataWriter> pDW;
    // Loop over and process input files
    for (const std::string& fName : fileNames) {

        std::cout << "Checking file " << fName << std::endl;

        std::unique_ptr<DataReader> pDR(pickDataReader(fName));
        if (pDR == nullptr) {
            std::cout << "Problem opening or reading this file!\n";
            return -1;
        }

        // Create data writer when reading first file
        if (pDW == nullptr) {
            // Copy run_parameters_pattern from first file:
            EventStorage::run_parameters_record runPara = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

            runPara.run_number   = pDR->runNumber();
            runPara.max_events   = pDR->maxEvents();
            runPara.rec_enable   = pDR->recEnable();
            runPara.trigger_type = pDR->triggerType();
            std::bitset<64> word1;
            std::bitset<64> word2;
            for (unsigned int i = 0; i < 64; ++i) {
                word1[i] = pDR->detectorMask()[i];
                word2[i] = pDR->detectorMask()[i + 64];
            }
            runPara.detector_mask_LS = word1.to_ulong();
            runPara.detector_mask_MS = word2.to_ulong();
            runPara.beam_type        = pDR->beamType();
            runPara.beam_energy      = pDR->beamEnergy();

            std::string       shortFileNameOut = fileNameOut;
            const std::string project          = pDR->projectTag();
            const std::string streamName       = "";
            const std::string streamType       = "";
            const std::string stream           = pDR->stream();
            const uint32_t    lbnbr            = pDR->lumiblockNumber();

            std::string dirNameOut = ".";
            size_t      p          = fileNameOut.rfind('/');
            if (p != std::string::npos) {
                dirNameOut       = fileNameOut.substr(0, p);
                shortFileNameOut = fileNameOut.substr(p + 1);
            }

            EventStorage::freeMetaDataStrings metaStrings;
            if (writePrecompressed) {
                pDW = std::make_unique<EventStorage::DataWriter>(dirNameOut, shortFileNameOut, runPara, project, streamType, streamName, stream,
                                                                 lbnbr, "AtlCopyBSEvent", metaStrings, EventStorage::ZLIB);
            }
            else {
                pDW = std::make_unique<EventStorage::DataWriter>(dirNameOut, shortFileNameOut, runPara, project, streamType, streamName, stream,
                                                                 lbnbr, "AtlCopyBSEvent", metaStrings);
            }

            pDW->setMaxFileMB(10000); // Max 10 metric GByte files
            if (!pDW->good()) {
                std::cout << "ERROR  Unable to initialize file " << std::endl;
                return -1;
            }

            std::cout << "Created DataWriter for file " << shortFileNameOut << " in directory " << dirNameOut << std::endl;
        }
        if (!pDR->good() || pDR->endOfFile()) {
            std::cerr << "No events in file " << fName << std::endl;
            continue;
        }

        eventLoop(std::move(pDR), std::move(pDW), nFound, searchEvents, searchRun, searchRunSet, listEvents, checkEvents, writePrecompressed,
                  compressData, compressionLevel);

        if (nFound >= searchEvents.size() && nFound != 0)
            break;
    }

    if (nFound == 0 && searchEvents.size() > 0)
        std::cout << "No events found!" << std::endl;
    else if (nFound)
        std::cout << "Wrote " << nFound << " events to file " << fileNameOut << std::endl;
    else
        std::cout << "Copied all events to file " << fileNameOut << std::endl;

    return 0;
}

void eventLoop(std::unique_ptr<DataReader> pDR, std::unique_ptr<EventStorage::DataWriter> pDW, uint64_t nFound,
               const std::vector<uint64_t>& SearchEvents, uint32_t searchRun, bool searchRunSet, bool listEvents, bool checkEvents,
               bool writePrecompressed, bool compressData, int compressionLevel)
{
    using namespace eformat;

    uint32_t eventCounter = 0;

    // Loop over events
    while (pDR->good()) {
        unsigned int eventSize;
        char*        buf;

        // Process data from DataReader
        DRError                     ecode = pDR->getData(eventSize, &buf);
        std::unique_ptr<uint32_t[]> fragment{reinterpret_cast<uint32_t*>(buf)};
        if (ecode != DRError::DROK) {
            std::cout << "Can't read from file!" << std::endl;
            break;
        }
        ++eventCounter;

        try {
            // Make a fragment with eformat 3.0, check it's validity
            if (static_cast<eformat::HeaderMarker>(fragment[0]) != FULL_EVENT) {
                std::cout << "Event doesn't start with full event fragment (found " << std::ios::hex << fragment[0] << ") ignored." << std::endl;
                continue;
            }

            // Convert header to new eformat version if necessary
            const uint32_t formatVersion = eformat::helper::Version(fragment[3]).major_version();
            if (formatVersion != eformat::MAJOR_DEFAULT_VERSION) {
                // Add 1000 for increase of data-size due to header conversion
                uint32_t newEventSize = eventSize + 1000;

                auto newFragment = std::make_unique<uint32_t[]>(newEventSize);
                eformat::old::convert(fragment.get(), newFragment.get(), newEventSize);
                // set new pointer
                fragment = std::move(newFragment);
            }

            FullEventFragment<const uint32_t*> fe = fragment.get();
            if (checkEvents) {
                fe.check_tree();
            }

            const uint32_t size = fe.fragment_size_word();

            ZSTD_CCtx* cctx = ZSTD_createCCtx();

            auto writeData = [&]() {
                if (compressData) {
                    const size_t outputSizeBound = ZSTD_compressBound(sizeof(uint32_t) * (size));
                    void*        compressedData  = malloc(outputSizeBound);
                    const size_t outputSize =
                        ZSTD_compressCCtx(cctx, compressedData, outputSizeBound, reinterpret_cast<void*>(fragment.get()), size, compressionLevel);

                    pDW->putData(sizeof(uint32_t) * outputSize, compressedData);
                    free(compressedData);
                }
                else if (writePrecompressed) {
                    pDW->putPrecompressedData(sizeof(uint32_t) * size, reinterpret_cast<void*>(fragment.get()));
                }
                else {
                    pDW->putData(sizeof(uint32_t) * size, reinterpret_cast<void*>(fragment.get()));
                }
            };

            // Get current event data
            uint64_t eventNo = fe.global_id();
            uint32_t runNo   = fe.run_no();
            if (listEvents) {
                std::cout << "Index=" << eventCounter << " Run=" << runNo << " Event=" << eventNo << " LB=" << fe.lumi_block() << std::endl;
            }

            // Print out current event data
            if ((!searchRunSet || (runNo == searchRun)) && std::binary_search(SearchEvents.begin(), SearchEvents.end(), eventNo) == true) {
                nFound++;
                std::cout << std::endl;
                std::cout << "File:" << pDR->fileName() << std::endl;
                std::cout << "Event index: " << eventCounter << std::endl;
                std::cout << "Run:         " << runNo << std::endl;
                std::cout << "Event ID:    " << eventNo << std::endl;
                std::cout << "LumiBlock:   " << fe.lumi_block() << std::endl;

                // Write event to file
                writeData();
            }
            else if (SearchEvents.size() == 0) {
                // Write event to file
                writeData();
            }

            ZSTD_freeCCtx(cctx);
        }
        catch (eformat::Issue& ex) {
            std::cerr << "Uncaught eformat issue: " << ex.what() << std::endl;
        }
        catch (ers::Issue& ex) {
            std::cerr << "Uncaught ERS issue: " << ex.what() << std::endl;
        }
        catch (std::exception& ex) {
            std::cerr << "Uncaught std exception: " << ex.what() << std::endl;
        }
        catch (...) {
            std::cerr << std::endl << "Uncaught unknown exception" << std::endl;
        }


        // End event processing
    }
}