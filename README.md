# OpenBCI GUI Helpers

Helpers for the [OpenBCI GUI](https://github.com/OpenBCI/OpenBCI_GUI)

These libraries provide utilities for native functions required by the OpenBCI GUI application. This includes support for:

* Native BLE discovery
* BLED112 Bluetooth discovery

# Usage

These files should be included in the `libraries` folder outside of the .jar file as shown below. Note that the .dylib files should be included outside of the .jar file so that they do not need to be extracted on MacOS systems. 

When updating this library in the GUI, use the following folder structure:

- GUI Repo Root Directory
  - OpenBCI_GUI
    - libraries
      - openbci_gui_helpers
        - library
          - `openbci_gui_helpers.jar`
          - `libGanglionNativeScan.dylib`
          - `libGanglionScan.dylib`

# Building

## Dependencies

- [CMake](https://cmake.org/)
- [Maven](https://maven.apache.org/)

## Build Process

- [Run CMake](https://cmake.org/runningcmake/) using the `CMakeLists.txt` configuration at the root of the repository to build the native libraries.
- Navigate to the `java-package/openbci_gui_helpers` directory.
- Run `mvn package`

Libraries will be built in the `compiled/<Build Configuration>` directory.
The .jar file will be built in the `java-package/openbci_gui_helpers/target` directory.

# Examples

There are several examples that can be used to test the features supported in the project. These examples are located in the `java-package/openbci_gui_helpers/src/main/java/openbci_gui_helpers/examples` directory.