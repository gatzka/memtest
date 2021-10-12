# SPDX-License-Identifier: Nexplore Technology GmbH Proprietary
# 
# Copyright (C) 2021 Nexplore Technology GmbH

include(LocateProgram)
LocateProgram(clang-format-13 CLANG_FORMAT_PATH)

if (NOT TARGET format-all)
    add_custom_target(format-all)
endif (NOT TARGET format-all)

if (NOT TARGET format-check-all)
    add_custom_target(format-check-all)
endif (NOT TARGET format-check-all)

function(AddClangFormat TARGET)
    get_property(TARGET_SOURCES TARGET ${TARGET} PROPERTY SOURCES)
    set(COMMENT "running C++ code formatter: clang-format")
    set(COMMENT "${COMMENT}\nworking directory: ${CMAKE_CURRENT_SOURCE_DIR}")
    set(COMMENT "${COMMENT}\nprocessing files:\n${TARGET_SOURCES}")
 
    set(FORMAT_TARGET "format-${TARGET}")
    add_custom_target(
        ${FORMAT_TARGET}
        COMMAND "${CLANG_FORMAT_PATH}" -i ${TARGET_SOURCES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )
    add_dependencies(format-all ${FORMAT_TARGET})

    set(FORMAT_CHECK_TARGET "format-check-${TARGET}")
    add_custom_target(
        ${FORMAT_CHECK_TARGET}
        COMMAND "${CLANG_FORMAT_PATH}" -i -n -Werror ${TARGET_SOURCES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )
    add_dependencies(format-check-all ${FORMAT_CHECK_TARGET})
endfunction(AddClangFormat)

