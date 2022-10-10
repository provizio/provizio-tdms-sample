# tdmsreader

tdmsreader is an application that reads and parses files with [NI TDMS format](https://www.ni.com/en-ie/support/documentation/supplemental/06/the-ni-tdms-file-format.html).

## General

This application is based on the code from this repository [https://github.com/shumway/tdmsreader](https://github.com/shumway/tdmsreader),
with minimal modifications to fix bugs and add some functionalities. 
The original repository is provided with an [MIT license](https://en.wikipedia.org/wiki/MIT_License) 
and the [original license file](COPYING) is also included here for completeness.

## Instructions

### Build

No particular dependencies are required apart from make, cmake and a gcc compiler. 
However an `install_dependencies.sh` file has been included that can be run before building, to make sure that they 
are all installed. 

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

* This is a basic version that parses a tdms file and extract the structure. 
To read individual values, a sample method `TDMSData::getDataFloat64` has been created which can be replicated, 
with the appropriate modifications, to extract values of different data types.

* The `CMakeLists.txt` file requires version `3.10` because that is what I have installed on my machine at the moment,
so it hasn't been tested with older versions.
