# Provizio-TDMS-Sample

It's an application that reads and parses files in [NI TDMS format](https://www.ni.com/en-ie/support/documentation/supplemental/06/the-ni-tdms-file-format.html)
and them extracts Provizio radars data packets from it.
These packets are then imported in Provizio Radar API to extract meaningful information contained in them.

## General

This application is based on the code from this repository [https://github.com/shumway/tdmsreader](https://github.com/shumway/tdmsreader),
with some modifications to fix bugs and add some functionalities.
The original repository is provided with an [MIT license](https://en.wikipedia.org/wiki/MIT_License)
and the [original license file](libtdms/COPYING) is also included here for completeness.

## Instructions

### OS

Tested in Ubuntu 18.04+.

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

The executable `provizio-tdms-sample` is placed in `build/bin/`.

### Run

This application can only parse one `.tdms` file at a time.

To run from the project root folder, call

```shell
build/bin/provizio-tdms-sample path_to_tdms_file.tdms
```

There is the possibility to use two options:

* `provizio-tdms-sample -h` print help information and exit
* `provizio-tdms-sample -v path_to_tdms_file.tdms` prints verbose information about the file being parsed
