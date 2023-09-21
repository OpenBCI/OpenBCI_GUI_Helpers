SET(OPENBCI_GANGLION_NATIVE_LIB "GanglionNativeScan")

add_library(
    ${OPENBCI_GANGLION_NATIVE_LIB} SHARED
    modules/common/src/serialization.cpp
    modules/native-ble/src/openbci_gui_native_helpers.cpp
)

target_include_directories(
    ${OPENBCI_GANGLION_NATIVE_LIB} PUBLIC
    modules/native-ble/include
    modules/common/include
    3rdparty/json
    3rdparty/SimpleBLE/simpleble/include/simpleble
)

target_link_libraries(
    ${OPENBCI_GANGLION_NATIVE_LIB} PRIVATE
    simpleble
)

set_property(TARGET ${OPENBCI_GANGLION_NATIVE_LIB} PROPERTY POSITION_INDEPENDENT_CODE ON)

set_target_properties(${OPENBCI_GANGLION_NATIVE_LIB}
    PROPERTIES

    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/

    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
)