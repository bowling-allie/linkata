include(FetchContent)
include(CMakeDependentOption)

option(LINKATA_FETCH_ALL "fetch all dependencies using cmake's FetchContent" OFF)

macro(linkata_fetch_option lib_name default)
    string(TOUPPER "${lib_name}" lib_name_upper)
    cmake_dependent_option(LINKATA_FETCH_${lib_name} "fetch ${lib_name} using cmake's FetchContent" "${default}"
            "NOT LINKATA_FETCH_ALL" ON)
    if (LINKATA_FETCH_${lib_name} OR LINKATA_FETCH_ALL)
        set(LINKATA_FIND_${lib_name} OFF CACHE INTERNAL "")
    else ()
        set(LINKATA_FIND_${lib_name} ON CACHE INTERNAL "")
    endif ()
endmacro()
