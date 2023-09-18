# OpenBCI GUI Helpers

Helpers for [OpenBCI GUI](https://github.com/OpenBCI/OpenBCI_GUI)

Built using Github Actions for all OS. The .dylib files for Mac are also provided as an artifact. These files should be included in the `libraries` folder outside of the .jar file as shown below. As a result, we do not need to extract them from the .jar file on Mac.

When updating this library in the GUI, use the following folder structure:

- GUI Repo Root Directory
  - OpenBCI_GUI
    - libraries
      - openbci_gui_helpers
        - library
          - `openbci_gui_helpers.jar`
          - `libGanglionNativeScan.dylib`
          - `libGanglionScan.dylib`

## License:

MIT
