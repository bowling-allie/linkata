cmake_minimum_required(VERSION 3.15)

add_subdirectory(lk)

add_executable(linkata
        ${CMAKE_CURRENT_BINARY_DIR}/lk/config.hpp
        main.cpp
        lk/app.cpp
        lk/app.hpp
        lk/emoji.cpp
        lk/emoji.hpp
        lk/emoji_svg_cache.cpp
        lk/emoji_svg_cache.hpp
        lk/emoji_texture_cache.cpp
        lk/emoji_texture_cache.hpp
        lk/fmt_corrade.tpp
        lk/fmt_magnum.tpp
        lk/id.cpp
        lk/id.hpp
        lk/log.cpp
        lk/log.hpp
        lk/log.tpp
        lk/lk.hpp
        lk/ready_task_queue.cpp
        lk/ready_task_queue.hpp
        lk/resource.cpp
        lk/resource.hpp
        lk/resource_handle.cpp
        lk/resource_handle.hpp
        lk/state.cpp
        lk/state.hpp
        lk/svg.cpp
        lk/svg.hpp
        lk/util.cpp
        lk/util.hpp)

add_subdirectory("lk/${LINKATA_UI}")

target_sources(linkata PRIVATE ${LINKATA_UI_SOURCES})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_link_options(linkata PRIVATE "-lpthread")
endif ()

if (LINKATA_HAX)
    target_sources(linkata PRIVATE
            lk/hax.hpp
            lk/hax.cpp)
endif ()

target_include_directories(linkata PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(linkata PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
#[[
if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set_target_properties(linkata PROPERTIES
            WIN32_EXECUTABLE TRUE
            MACOSX_BUNDLE TRUE)
endif ()
]]
if (MSVC)
    cmake_minimum_required(VERSION 3.15)
    set_target_properties(linkata
            PROPERTIES MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>)
    target_compile_options(linkata PRIVATE /utf-8)
endif ()

# for sdl2. needs to be moved to FindSDL2.cmake, but improved before that
if (CORRADE_TARGET_WINDOWS)
    # needed because sdl2 ain't so hot with its config file >:[
    #set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid")

    # these were all different tries and stuff, just memory for tinkering, sorry
    #target_link_options(linkata PRIVATE -static -lmingw32 -lSDL2main -lSDL2 -mwindows  -Wl,--no-undefined -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -static-libgcc)
    #target_link_options(linkata PRIVATE -mwindows -Wl,--no-undefined -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -static-libgcc -static)
endif ()

set(_Corrade_COMPONENTS
        Containers
        Main
        PluginManager
        #TestSuite
        Utility
        )
#if (LINKATA_FIND_corrade)
    find_package(Corrade REQUIRED COMPONENTS ${_Corrade_COMPONENTS})
#endif ()
foreach (_Corrade_COMPONENT ${_Corrade_COMPONENTS})
    target_link_libraries(linkata PRIVATE Corrade::${_Corrade_COMPONENT})
endforeach (_Corrade_COMPONENT)
unset(_Corrade_COMPONENTS)

if (LINKATA_EMBED_RESOURCES)
    corrade_add_resource(LINKATA_RES_SOURCE ${LINKATA_RES_FILE})
    target_sources(linkata PRIVATE ${LINKATA_RES_SOURCE})
endif ()

set(_Magnum_COMPONENTS
        AnyAudioImporter
        AnyImageConverter
        AnyImageImporter
        #AnySceneImporter
        Audio
        DebugTools
        GL
        MeshTools
        Primitives
        SceneGraph
        Shaders
        Text
        TextureTools
        Trade
        #Vk
        #GlfwApplication
        #GlutApplication
        #GlxApplication
        #Sdl2Application
        #XEglApplication
        #WindowlessCglApplication
        #WindowlessEglApplication
        #WindowlessGlxApplication
        #WindowlessIosApplication
        #WindowlessWglApplication
        #WindowlessWindowsEglApplication
        #CglContext
        #EglContext
        #GlxContext
        #WglContext
        #OpenGLTester
        #MagnumFont
        #MagnumFontConverter
        #ObjImporter
        #TgaImageConverter
        #TgaImporter
        #WavAudioImporter
        #distancefieldconverter
        #fontconverter
        #imageconverter
        #gl-info
        #al-info
        )
list(APPEND _Magnum_COMPONENTS ${LINKATA_PLATFORM})
#if (LINKATA_FIND_magnum)
    find_package(Magnum REQUIRED COMPONENTS ${_Magnum_COMPONENTS})
#endif ()
target_link_libraries(linkata PRIVATE Magnum::Magnum)
foreach (_Magnum_COMPONENT ${_Magnum_COMPONENTS})
    set(_Magnum_COMPONENT_FULLNAME Magnum::${_Magnum_COMPONENT})
    get_target_property(_Magnum_COMPONENT_TYPE "${_Magnum_COMPONENT_FULLNAME}" TYPE)
    if (NOT "${_Magnum_COMPONENT_TYPE}" STREQUAL "MODULE_LIBRARY")
        target_link_libraries(linkata PRIVATE ${_Magnum_COMPONENT_FULLNAME})
    endif ()
endforeach (_Magnum_COMPONENT)
unset(_Magnum_COMPONENTS)

set(_MagnumPlugins_COMPONENTS
        #AssimpImporter
        #ColladaImporter
        #DdsImporter
        #DevIlImageImporter
        #DrFlacAudioImporter
        #DrWavAudioImporter
        #Faad2AudioImporter
        #FreeTypeFont
        #HarfBuzzFont
        #JpegImageConverter
        #JpegImporter
        #MiniExrImageConverter
        #OpenGexImporter
        #PngImageConverter
        #PngImporter
        #StanfordImporter
        StbImageConverter
        StbImageImporter
        #StbTrueTypeFont
        #StbVorbisAudioImporter
        #TinyGltfImporter
        )
#if (LINKATA_FIND_magnum-plugins)
    find_package(MagnumPlugins REQUIRED COMPONENTS ${_MagnumPlugins_COMPONENTS})
#endif ()
foreach (_MagnumPlugins_COMPONENT ${_MagnumPlugins_COMPONENTS})
    set(_MagnumPlugins_COMPONENT_FULLNAME MagnumPlugins::${_MagnumPlugins_COMPONENT})
    get_target_property(_MagnumPlugins_COMPONENT_TYPE ${_MagnumPlugins_COMPONENT_FULLNAME} TYPE)
    if (NOT "${_MagnumPlugins_COMPONENT_TYPE}" STREQUAL "MODULE_LIBRARY")
    #if (TARGET ${_MagnumPlugins_COMPONENT_FULLNAME})
        target_link_libraries(linkata PRIVATE ${_MagnumPlugins_COMPONENT_FULLNAME})
    endif ()
endforeach (_MagnumPlugins_COMPONENT)
unset(_MagnumPlugins_COMPONENTS)

set(_MagnumIntegration_COMPONENTS
        #Bullet
        #Dart
        #Glm
        #ImGui
        )
if ("${LINKATA_UI}" STREQUAL "imgui")
    list(APPEND _MagnumIntegration_COMPONENTS ImGui)
endif ()
#if (LINKATA_FIND_magnum-integration)
    find_package(MagnumIntegration REQUIRED COMPONENTS ${_MagnumIntegration_COMPONENTS})
#endif ()
foreach (_MagnumIntegration_COMPONENT ${_MagnumIntegration_COMPONENTS})
    target_link_libraries(linkata PRIVATE MagnumIntegration::${_MagnumIntegration_COMPONENT})
endforeach (_MagnumIntegration_COMPONENT)
unset(_MagnumIntegration_COMPONENTS)

if (EMSCRIPTEN AND USE_EMSCRIPTEN_PORTS_BOOST_HEADERS)
    target_compile_options(linkata PRIVATE "SHELL:-s USE_BOOST_HEADERS=1")
    message(STATUS "Using emscripten-ports/boost (passing '-s USE_BOOST_HEADERS=1' to emcc)")
else ()
    set(_Boost_COMPONENTS
            program_options
            )
    find_package(Boost REQUIRED COMPONENTS ${_Boost_COMPONENTS})
    foreach (_Boost_COMPONENT ${_Boost_COMPONENTS})
        target_link_libraries(linkata PRIVATE Boost::${_Boost_COMPONENT})
    endforeach (_Boost_COMPONENT)
    if (CMAKE_VERSION VERSION_LESS 3.15)
        target_link_libraries(linkata PRIVATE Boost::boost)
    else ()
        target_link_libraries(linkata PRIVATE Boost::headers)
    endif ()
    unset(_Boost_COMPONENTS)

    if (Boost_VERSION VERSION_LESS "1.67.0")
        FetchContent_Declare(container_hash
                GIT_REPOSITORY https://github.com/boostorg/container_hash.git
                #GIT_SHALLOW ON
                GIT_PROGRESS ON)

        FetchContent_GetProperties(container_hash)
        if (NOT container_hash_POPULATED)
            FetchContent_Populate(container_hash)
            target_include_directories(linkata PRIVATE ${container_hash_SOURCE_DIR}/include)
        endif ()
    endif ()
endif ()

if (LINKATA_FIND_fmt)
    find_package(fmt CONFIG REQUIRED)
endif ()
target_link_libraries(linkata PRIVATE fmt::fmt)

if (LINKATA_FIND_nanosvg)
    find_package(nanosvg REQUIRED)
endif ()
target_link_libraries(linkata PRIVATE nanosvg::nanosvg)

if (LINKATA_FIND_nanovg)
    find_package(nanovg REQUIRED)
endif ()
target_link_libraries(linkata PRIVATE nanovg::nanovg)

if (CORRADE_TARGET_WINDOWS)
    target_sources(linkata PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/ICON.rc")

    set(linkata_HI_DPI_MANIFEST "WindowsHiDPI.manifest" CACHE FILEPATH "manifest file for HiDPI on windows")
    mark_as_advanced(linkata_HI_DPI_MANIFEST)
    #if (MINGW)
        set(linkata_HI_DPI_RC "WindowsHiDPI.rc" CACHE FILEPATH "resource file for HiDPI on windows")
        mark_as_advanced(linkata_HI_DPI_RC)
        target_sources(linkata PRIVATE ${linkata_HI_DPI_RC})
    #elseif (MSVC)
        #target_sources(linkata PRIVATE ${linkata_HI_DPI_MANIFEST})
    #endif ()

    install(TARGETS linkata
            DESTINATION ${MAGNUM_DEPLOY_PREFIX})

    if (MINGW)
        include(UseMingw)

        get_filename_component(_LINKATA_MINGW_BIN_DIR ${CMAKE_CXX_COMPILER} PATH)
        set(DLL_SEARCH_PATH ${_LINKATA_MINGW_BIN_DIR})

        mingw_bundle_dlls(${MAGNUM_DEPLOY_PREFIX}
                "libwinpthread-1.dll"
                "libgcc_s_seh-1.dll"
                "libstdc++-6.dll"
                "glfw3.dll")
    endif ()
elseif (CORRADE_TARGET_EMSCRIPTEN)
    target_link_options(linkata PRIVATE "SHELL:--pre-js ${CMAKE_CURRENT_SOURCE_DIR}/linkata_pre.js")
    target_link_options(linkata PRIVATE "SHELL:--post-js ${CMAKE_CURRENT_SOURCE_DIR}/linkata_post.js")
    set_property(TARGET linkata APPEND
            PROPERTY LINK_DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/linkata_pre.js"
            "${CMAKE_CURRENT_SOURCE_DIR}/linkata_post.js")

    # bug with wasm and fastcomp/non-upstream emscripten that shows up in imgui
    # fixes initial gray screen loading bug at ImGui::NewFrame
    # i think the issue boiled down to a float instruction in asm.js that couldn't be converted to wasm
    # linking to js instead of wasm fixes it
    #target_compile_options(linkata PRIVATE "SHELL:-s WASM=0")
    #target_link_options(linkata PRIVATE "SHELL:-s WASM=0")

    target_compile_options(linkata PRIVATE "SHELL:-s WASM=1")
    target_link_options(linkata PRIVATE "SHELL:-s WASM=1")

    target_compile_options(linkata PRIVATE "SHELL:-s FETCH=1")
    target_link_options(linkata PRIVATE "SHELL:-s FETCH=1")

    target_compile_options(linkata PRIVATE "SHELL:-s TOTAL_MEMORY=64MB")
    target_link_options(linkata PRIVATE "SHELL:-s TOTAL_MEMORY=64MB")

    target_compile_options(linkata PRIVATE "SHELL:-s MINIMAL_RUNTIME=1")
    target_link_options(linkata PRIVATE "SHELL:-s MINIMAL_RUNTIME=1")

    #target_compile_options(linkata PRIVATE "SHELL:-s EXIT_RUNTIME=1")
    #target_link_options(linkata PRIVATE "SHELL:-s EXIT_RUNTIME=1")

    #target_compile_options(linkata PRIVATE "SHELL:-s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1")
    #target_link_options(linkata PRIVATE "SHELL:-s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1")

    install(TARGETS linkata
            DESTINATION "${MAGNUM_DEPLOY_PREFIX}/static")

    install(FILES
            "${MAGNUM_EMSCRIPTENAPPLICATION_JS}"
            "${MAGNUM_WEBAPPLICATION_CSS}"
            "linkata.css"
            "${CMAKE_CURRENT_BINARY_DIR}/linkata.wasm"
            DESTINATION "${MAGNUM_DEPLOY_PREFIX}/static")

    if ("${LINKATA_UI}" STREQUAL "emscripten")
        install(FILES
                "lk/emscripten/linkata.js"
                DESTINATION "${MAGNUM_DEPLOY_PREFIX}/static")
    endif ()

    install(FILES index.html
            DESTINATION "${MAGNUM_DEPLOY_PREFIX}/templates")

    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        install(FILES server.py
                DESTINATION "${MAGNUM_DEPLOY_PREFIX}")
    endif ()
else ()
    install(TARGETS linkata
            DESTINATION ${MAGNUM_DEPLOY_PREFIX})
endif ()
