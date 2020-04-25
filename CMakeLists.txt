cmake_minimum_required(VERSION 3.15)
project(linkata
        VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules/")

set(LINKATA_RES_DIR "${CMAKE_SOURCE_DIR}/res" CACHE PATH "Resource dir")

include(LinkataFetchDependencies)

linkata_fetch_option(corrade OFF)
if (LINKATA_FETCH_corrade)
    FetchContent_Declare(corrade
            GIT_REPOSITORY https://github.com/mosra/corrade.git
            #GIT_SHALLOW ON
            GIT_PROGRESS ON)

    set(BUILD_DEPRECATED OFF CACHE BOOL "")
    set(BUILD_STATIC ON CACHE BOOL "")

    message(STATUS "configuring corrade")
    FetchContent_MakeAvailable(corrade)

    list(APPEND CMAKE_MODULE_PATH "${corrade_SOURCE_DIR}/modules")
    #set(CORRADE_INCLUDE_DIR "${corrade_SOURCE_DIR}/src" CACHE PATH "")
endif ()

find_package(Corrade REQUIRED)

if (CORRADE_TARGET_ANDROID)
    set(LINKATA_PLATFORM AndroidApplication)
elseif (CORRADE_TARGET_EMSCRIPTEN)
    set(LINKATA_PLATFORM EmscriptenApplication)
else ()
    #set(LINKATA_PLATFORM Sdl2Application)
    set(LINKATA_PLATFORM GlfwApplication)
    #set(LINKATA_PLATFORM GlutApplication) # ew
endif ()

linkata_fetch_option(magnum OFF)
if (LINKATA_FETCH_magnum)
    FetchContent_Declare(magnum
            GIT_REPOSITORY https://github.com/mosra/magnum.git
            #GIT_SHALLOW ON
            GIT_PROGRESS ON)

    set(BUILD_DEPRECATED OFF CACHE BOOL "")
    set(BUILD_STATIC ON CACHE BOOL "")

    set(WITH_ANYAUDIOIMPORTER ON CACHE BOOL "")
    set(WITH_ANYIMAGECONVERTER ON CACHE BOOL "")
    set(WITH_ANYIMAGEIMPORTER ON CACHE BOOL "")
    #set(WITH_ANYSCENEIMPORTER ON CACHE BOOL "")
    set(WITH_AUDIO ON CACHE BOOL "")

    if (CORRADE_TARGET_EMSCRIPTEN)
        set(TARGET_GLES2 OFF CACHE BOOL "")
    endif ()

    string(TOUPPER "${LINKATA_PLATFORM}" LINKATA_PLATFORM_UPPERCASE)
    set(WITH_${LINKATA_PLATFORM_UPPERCASE} ON CACHE BOOL "")

    message(STATUS "configuring magnum")
    FetchContent_MakeAvailable(magnum)

    list(APPEND CMAKE_MODULE_PATH "${magnum_SOURCE_DIR}/modules")
    #set(MAGNUM_INCLUDE_DIR "${magnum_SOURCE_DIR}/src" CACHE PATH "")
endif ()

linkata_fetch_option(magnum-plugins OFF)
if (LINKATA_FETCH_magnum-plugins)
    FetchContent_Declare(magnum-plugins
            GIT_REPOSITORY https://github.com/mosra/magnum-plugins.git
            #GIT_SHALLOW ON
            GIT_PROGRESS ON)

    set(BUILD_DEPRECATED OFF CACHE BOOL "")
    set(BUILD_STATIC ON CACHE BOOL "")

    set(WITH_STBIMAGECONVERTER ON CACHE BOOL "")
    set(WITH_STBIMAGEIMPORTER ON CACHE BOOL "")

    message(STATUS "configuring magnum-plugins")
    FetchContent_MakeAvailable(magnum-plugins)

    list(APPEND CMAKE_MODULE_PATH "${magnum-plugins_SOURCE_DIR}/modules")
    #set(MAGNUMPLUGINS_INCLUDE_DIR "${magnum-plugins_SOURCE_DIR}/src" CACHE PATH "")
endif ()

if (VCPKG_TOOLCHAIN)
    set(_LINKATA_FETCH_IMGUI_DEFAULT OFF)
else ()
    set(_LINKATA_FETCH_IMGUI_DEFAULT ON)
endif ()
linkata_fetch_option(imgui "${_LINKATA_FETCH_IMGUI_DEFAULT}")
if (LINKATA_FETCH_imgui)
    FetchContent_Declare(imgui
            GIT_REPOSITORY https://github.com/ocornut/imgui.git
            GIT_TAG v1.75
            #GIT_SHALLOW ON
            GIT_PROGRESS ON)
    FetchContent_GetProperties(imgui)
    if (NOT imgui_POPULATED)
        FetchContent_Populate(imgui)
        set(IMGUI_DIR "${imgui_SOURCE_DIR}" CACHE PATH "")
    endif ()
endif ()

linkata_fetch_option(magnum-integration OFF)
if (LINKATA_FETCH_magnum-integration)
    FetchContent_Declare(magnum-integration
            GIT_REPOSITORY https://github.com/mosra/magnum-integration.git
            #GIT_SHALLOW ON
            GIT_PROGRESS ON)

    set(BUILD_DEPRECATED OFF CACHE BOOL "")
    set(BUILD_STATIC ON CACHE BOOL "")

    #set(WITH_BULLET ON CACHE BOOL "")
    set(WITH_IMGUI ON CACHE BOOL "")
    #[[if (EMSCRIPTEN)
        set(USE_EMSCRIPTEN_PORTS_BULLET ON CACHE BOOL "")
    endif ()]]

    message(STATUS "configuring magnum-integration")
    FetchContent_MakeAvailable(magnum-integration)

    list(APPEND _LINKATA_EXTRA_MODULE_PATHS "${magnum-integration_SOURCE_DIR}/modules")
    #set(MagnumIntegration_ROOT "${magnum-integration_SOURCE_DIR}/src" CACHE PATH "")
endif ()

linkata_fetch_option(fmt OFF)
if (LINKATA_FETCH_fmt)
    FetchContent_Declare(fmt
            GIT_REPOSITORY https://github.com/fmtlib/fmt.git
            GIT_TAG 6.1.2
            #GIT_SHALLOW ON
            GIT_PROGRESS ON)

    set(MASTER_PROJECT OFF CACHE BOOL "")

    message(STATUS "configuring fmt")
    FetchContent_MakeAvailable(fmt)
endif ()

linkata_fetch_option(nanosvg ON)
if (LINKATA_FETCH_nanosvg)
    FetchContent_Declare(nanosvg
            GIT_REPOSITORY https://github.com/memononen/nanosvg.git
            #GIT_SHALLOW ON
            GIT_PROGRESS ON)
    FetchContent_GetProperties(nanosvg)
    if (NOT nanosvg_POPULATED)
        FetchContent_Populate(nanosvg)

        set(nanosvg_INCLUDE_DIR
                "${nanosvg_SOURCE_DIR}/src")

        add_library(nanosvg INTERFACE)

        target_include_directories(nanosvg INTERFACE
                ${nanosvg_INCLUDE_DIR})

        add_library(nanosvg::nanosvg ALIAS nanosvg)
    endif ()
endif ()

linkata_fetch_option(nanovg ON)
if (LINKATA_FETCH_nanovg)
    FetchContent_Declare(nanovg
            GIT_REPOSITORY https://github.com/memononen/nanovg.git
            #GIT_SHALLOW ON
            GIT_PROGRESS ON)

    FetchContent_GetProperties(nanovg)
    if (NOT nanovg_POPULATED)
        FetchContent_Populate(nanovg)

        set(nanovg_SOURCES
                "${nanovg_SOURCE_DIR}/src/nanovg.c")

        set(nanovg_INCLUDE_DIR
                "${nanovg_SOURCE_DIR}/src")

        add_library(nanovg STATIC
                ${nanovg_SOURCES})

        if (MSVC)
            cmake_minimum_required(VERSION 3.15)
            set_target_properties(nanovg
                    PROPERTIES MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>)
            target_compile_options(nanovg PRIVATE /utf-8)
        endif ()

        target_include_directories(nanovg PUBLIC
                ${nanovg_INCLUDE_DIR})

        add_library(nanovg::nanovg ALIAS nanovg)
    endif ()
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/magnum_modules")

option(LINKATA_EMBED_RESOURCES "Embed files in res/ into executable" ON)
if (LINKATA_EMBED_RESOURCES)
    set(LINKATA_RES_FILE "${CMAKE_BINARY_DIR}/resources.conf" CACHE FILEPATH "linkata resource file")

    include(GenerateCorradeResourceFile)
    generate_corrade_res_file(${LINKATA_RES_DIR} ${LINKATA_RES_FILE})
endif ()

option(LINKATA_PREFER_STATIC_LIBS "When calling things like find_library(), prefer the static lib extensions: '.a', '.lib' (rearranges CMAKE_FIND_LIBRARY_SUFFIXES)" ON)
if (LINKATA_PREFER_STATIC_LIBS)
    foreach (_linkata_CMAKE_FIND_LIBRARY_SUFFIX ${CMAKE_FIND_LIBRARY_SUFFIXES})
        if ("${_linkata_CMAKE_FIND_LIBRARY_SUFFIX}" MATCHES  "^(.a|.lib)$")
            set(_linkata_CMAKE_FIND_LIBRARY_SUFFIXES ${_linkata_CMAKE_FIND_LIBRARY_SUFFIX} ${_linkata_CMAKE_FIND_LIBRARY_SUFFIXES})
        else ()
            set(_linkata_CMAKE_FIND_LIBRARY_SUFFIXES ${_linkata_CMAKE_FIND_LIBRARY_SUFFIXES} ${_linkata_CMAKE_FIND_LIBRARY_SUFFIX})
        endif ()
    endforeach ()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ${_linkata_CMAKE_FIND_LIBRARY_SUFFIXES})
endif ()

if (CORRADE_TARGET_EMSCRIPTEN)
    option(USE_EMSCRIPTEN_PORTS_BOOST_HEADERS "Use emscripten-ports/boost instead of asking cmake for it" ON)
endif ()

option(LINKATA_COPY_IMGUI_FONT_DATA "Avoid const_cast and copy font data so imgui can own it" OFF)
option(LINKATA_WITH_EMOJIS "Emojis!" OFF)

if (CORRADE_TARGET_EMSCRIPTEN)
    set(LINKATA_UI_STRINGS emscripten)
else ()
    set(LINKATA_UI_STRINGS ultralight)
endif ()
list(APPEND LINKATA_UI_STRINGS imgui)
list(GET LINKATA_UI_STRINGS 0 LINKATA_UI_DEFAULT)

set(LINKATA_UI ${LINKATA_UI_DEFAULT} CACHE STRING "UI backend")
set_property(CACHE LINKATA_UI PROPERTY STRINGS ${LINKATA_UI_STRINGS})
set(LINKATA_UI_${LINKATA_UI} ON)

option(LINKATA_MAGNUM_2019_10_COMPATIBILITY "" OFF)

option(LINKATA_HAX "Workarounds for if you have no control over lib versions or whatever (you probably shouldn't rely on these)" OFF)
mark_as_advanced(LINKATA_HAX)
cmake_dependent_option(LINKATA_HAX_ATLAS_TEXTURE "Use workaround to get ImGuiIntegration::Context atlas texture (reliable)" OFF
        "LINKATA_HAX;LINKATA_UI_imgui" OFF)
mark_as_advanced(LINKATA_HAX_ATLAS_TEXTURE)

add_subdirectory(src)
#[[
if (NOT LINKATA_EMBED_RESOURCES)
    if (EMSCRIPTEN)
        install(DIRECTORY res
                DESTINATION ${MAGNUM_DEPLOY_PREFIX})
    else ()
        install(DIRECTORY res
                DESTINATION ${MAGNUM_DEPLOY_PREFIX})
    endif ()
endif ()
]]