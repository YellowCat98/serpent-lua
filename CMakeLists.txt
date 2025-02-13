# this cmakelists is based on https://git.norax.us.kg/Norax/apodora/src/branch/master/CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
project(Serpent VERSION 1.0.0)

add_library(lua STATIC 
    lua/lapi.c
    lua/lauxlib.c
    lua/lbaselib.c
    lua/lcode.c
    lua/ldblib.c
    lua/ldebug.c
    lua/ldo.c
    lua/ldump.c
    lua/lfunc.c
    lua/lgc.c
    lua/linit.c
    lua/liolib.c
    lua/llex.c
    lua/lmathlib.c
    lua/lmem.c
    lua/loadlib.c
    lua/lobject.c
    lua/lopcodes.c
    lua/loslib.c
    lua/lparser.c
    lua/lstate.c
    lua/lstring.c
    lua/lstrlib.c
    lua/ltable.c
    lua/ltablib.c
    lua/ltm.c
    lua/lundump.c
    lua/lvm.c
    lua/lzio.c
    lua/lutf8lib.c  
    lua/lctype.c  
    lua/lcorolib.c 
)

target_include_directories(lua PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/lua
)

if(MSVC)
    target_link_options(lua PRIVATE "/WHOLEARCHIVE:lua")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_link_options(lua PRIVATE "-Wl,--whole-archive" "-Wl,--no-whole-archive")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

CPMAddPackage(
    NAME sol2
    GITHUB_REPOSITORY ThePhD/sol2
    VERSION 3.3.0
)

file(GLOB_RECURSE SOURCES 
    src/*.cpp
)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    lua
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/lua
    ${sol2_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_dependencies(${PROJECT_NAME} lua)

setup_geode_mod(${PROJECT_NAME})
