include(FetchContent)
include(CMakeDependentOption)

option(LINKATA_FETCH_ALL "fetch all dependencies using cmake's FetchContent" OFF)

function(linkata_fetch_option lib_name default)
    cmake_parse_arguments(
            _LINKATA_FETCH_OPTION
            ""
            "GIT_TAG_DEFAULT"
            ""
            ${ARGN})
    string(TOUPPER "${lib_name}" lib_name_upper)
    cmake_dependent_option(LINKATA_FETCH_${lib_name} "fetch ${lib_name} using cmake's FetchContent" "${default}"
            "NOT LINKATA_FETCH_ALL" ON)
    if ("${_LINKATA_FETCH_OPTION_GIT_TAG_DEFAULT}" STREQUAL "")
        set(_LINKATA_FETCH_OPTION_GIT_TAG_DEFAULT "origin/master")
    endif ()
    set(LINKATA_FETCH_${lib_name}_GIT_TAG "${_LINKATA_FETCH_OPTION_GIT_TAG_DEFAULT}" CACHE STRING "git branch name, tag or commit hash")
    if (LINKATA_FETCH_${lib_name} OR LINKATA_FETCH_ALL)
        set(LINKATA_FIND_${lib_name} OFF CACHE INTERNAL "")
    else ()
        set(LINKATA_FIND_${lib_name} ON CACHE INTERNAL "")
    endif ()
endfunction()
