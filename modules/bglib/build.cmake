SET(GANGLION_LIB "GanglionScan")

add_library(
    ${GANGLION_LIB} SHARED
    modules/common/src/serialization.cpp
    modules/bglib/src/callbacks.cpp
    modules/bglib/src/cmd_def.cpp
    modules/bglib/src/stubs.cpp
    modules/bglib/src/uart.cpp
    modules/bglib/src/openbci_gui_helpers.cpp
)

target_include_directories(
    ${GANGLION_LIB} PUBLIC
    3rdparty/json
    modules/bglib/include
    modules/common/include
)

set_property(TARGET ${GANGLION_LIB} PROPERTY POSITION_INDEPENDENT_CODE ON)

set_target_properties(${GANGLION_LIB}
    PROPERTIES

    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/

    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
)