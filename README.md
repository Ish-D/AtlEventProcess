# AtlEventProcess

### Repository for GSoC project on ATLAS data compression

Contains a simplified & modernized version of [ATLCopyBSEvent.cxx](https://gitlab.cern.ch/atlas/athena/-/blob/main/Event/ByteStreamCnvSvc/test/AtlCopyBSEvent.cxx).

### Build Instructions:
Requires boost, eformat, ers, DataWriter, & DataReader libraries.

```
mkdir build
cd build
cmake ..
./AtlEventProcess <parameters>
```

Input parameters:
```
[-d --deflate] -e [--event] <eventNumbers> [-r, --run <runnumber>] [-l, --listevents] [-t --checkevents] -o, --out outputfile inputfiles....
Where eventNumbers is a comma-separated list of events
```
