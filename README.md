# tdmsreader

tdmsreader is an application that reads and parses files with NI TDMS format (.tdms).

## General

This application is based on the code from this repository [https://github.com/shumway/tdmsreader](https://github.com/shumway/tdmsreader),
with minimal modifications to fix bugs and add some functionalities.

## Instructions

### Build

To build, run the following commands from the project root folder

```shell
mkdir build && cd build
cmake ..
cmake --build .
```

The executable `tdmsreader` is going to be located in `build/bin/`.

### Run

This application can only parse one `.tdms` file at a time. 

To run from the project root folder, call

```shell
build/bin/tdmsreader path_to_tdms_file.tdms
```

There is the possibility to use two options:
* `tdmsreader -h` print help information and exit
* `tdmsreader -v path_to_tdms_file.tdms` prints verbose information about the file being parsed

### Notes

This is a basic version that parses a tdms file and extract the structure. 
To read individual values, a sample method `TDMSData::getDataFloat64` has been created which can be replicated, 
with the appropriate modifications, to extract values of different data types.
