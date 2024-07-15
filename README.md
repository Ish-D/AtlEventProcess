# AtlEventProcess

### Repository for GSoC project on ATLAS data compression

Contains a simplified & modernized version of [ATLCopyBSEvent.cxx](https://gitlab.cern.ch/atlas/athena/-/blob/main/Event/ByteStreamCnvSvc/test/AtlCopyBSEvent.cxx).

This repository is for the Google Summer of Code (GSOC) project [Lossless compression of raw data for the ATLAS experiment at CERN](https://hepsoftwarefoundation.org/gsoc/2024/proposal_ATLASrawcompression.html). 

The goal of this project is to study the performance and effectiveness of various compression algorithms, specifically on ATLAS RAW data. The ATLAS experiment produces extremely large amounts of data, and it is only expected to increase with future planned upgrades within the LHC. Prior studies into compression of the data has shown that due to the highly redundant nature of the generated data, lossless data compression algorithms are extremely effective in reducing the binary size of ATLAS data. Here, we would like to find an algorithm that has a good balance of compression time, and compressed binary size.

### Build Instructions:
Building this project requires some CERN specific libraries such as eformat, ers, DataWriter, and DataReader. 
The most recommended way to build is to go through a virtual machine such as [Athena on Lima](https://atlassoftwaredocs.web.cern.ch/athena/lima/).

Once the virtual machine is installed, run the following commands to setup the correct GCC version (13.1.0) and allow CMake to find the required headers.

```
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
asetup Athena,main,latest
export CXXFLAGS=-isystem\ /cvmfs/atlas.cern.ch/repo/sw/tdaq/tdaq-common/tdaq-common-11-02-01/installed/include/
```

Then, to build the project:
```
mkdir build
cd build
cmake ..

# To run the program normally
./AtlEventProcess <parameters>

# To run the tests
make tests
```

The projects input parameters are as follows:
```
[-d --deflate] -e [--event] <eventNumbers> [-r, --run <runnumber>] [-l, --listevents] [-t --checkevents] -o, --out outputfile inputfiles....
Where eventNumbers is a comma-separated list of events
```

| Argument | Purpose|
|----------|------- |
|-d or --deflate| Compress the output file using ZLIB|
|-e or --event | Output only particular event numbers (comma separated, e.g. -e 1,2,3 ...)|
|-r or --run | Output only particular run numbers (comma separated, e.g. -r 4,5,6 ...)|
|-l or --listevents | List the events that are being processed|
|-t or --checkevents | Check the events that are being processed |
|-o or --out | Define the output file name|
| | name of inputfiles separated by spaces|
