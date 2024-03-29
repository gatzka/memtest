# SPDX-License-Identifier: Nexplore Technology GmbH Proprietary
# 
# Copyright (C) 2021 Nexplore Technology GmbH
function(LocateProgram PROGRAM_NAME PROGRAM_PATH)
    set(${PROGRAM_PATH} "${PROGRAM_PATH}-NOTFOUND" CACHE FILEPATH "Path to '${PROGRAM_NAME}' executable")
    if("${${PROGRAM_PATH}}" STREQUAL "${PROGRAM_PATH}-NOTFOUND")
        find_program(${PROGRAM_PATH} ${PROGRAM_NAME})
        if("${${PROGRAM_PATH}}" STREQUAL "${PROGRAM_PATH}-NOTFOUND")
            message(FATAL_ERROR "Unable to locate '${PROGRAM_NAME}'")
        endif()
    else()
        if(NOT EXISTS ${${PROGRAM_PATH}})
            message(FATAL_ERROR "${PROGRAM_PATH} does not exist: '${${PROGRAM_PATH}}'")
        endif()
    endif()
    message(STATUS "${PROGRAM_PATH}=${${PROGRAM_PATH}}")
endfunction(LocateProgram)
