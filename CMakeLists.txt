cmake_minimum_required (VERSION 3.10)
project (OpenBCI_GUI_Helpers)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_VERBOSE_MAKEFILE ON)
set (BRAINFLOW_VERSION 2.1.0)

macro (configure_msvc_runtime)
    if (MSVC)
        # Default to statically-linked runtime.
        if ("${MSVC_RUNTIME}" STREQUAL "")
            set (MSVC_RUNTIME "static")
        endif ()
        # Set compiler options.
        set (variables
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_MINSIZEREL
            CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_MINSIZEREL
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_RELWITHDEBINFO
        )
        if (${MSVC_RUNTIME} STREQUAL "static")
            message(STATUS
                "MSVC -> forcing use of statically-linked runtime."
            )
            foreach (variable ${variables})
                if (${variable} MATCHES "/MD")
                    string (REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
                endif ()
            endforeach ()
        else ()
            message (STATUS
                "MSVC -> forcing use of dynamically-linked runtime."
            )
            foreach (variable ${variables})
                if (${variable} MATCHES "/MT")
                    string (REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
                endif ()
            endforeach ()
        endif ()
    endif ()
endmacro ()

# link msvc runtime statically
configure_msvc_runtime ()

SET (GANGLION_LIB "GanglionScan")
set (GANGLION_SOURCE_LIB
    ${CMAKE_HOME_DIRECTORY}/src/callbacks.cpp
    ${CMAKE_HOME_DIRECTORY}/src/cmd_def.cpp
    ${CMAKE_HOME_DIRECTORY}/src/stubs.cpp
    ${CMAKE_HOME_DIRECTORY}/src/uart.cpp
    ${CMAKE_HOME_DIRECTORY}/src/openbci_gui_helpers.cpp
)

add_library (${GANGLION_LIB} SHARED ${GANGLION_SOURCE_LIB})

target_include_directories (${GANGLION_LIB} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_HOME_DIRECTORY}/third_party/json>
    $<BUILD_INTERFACE:${CMAKE_HOME_DIRECTORY}/src/inc>
)

set_property (TARGET ${GANGLION_LIB} PROPERTY POSITION_INDEPENDENT_CODE ON)

set_target_properties (${GANGLION_LIB}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/java-package/openbci_gui_helpers/src/main/resources/
)