cmake_minimum_required(VERSION 3.16)
project(fooyin-msuinput)

include(ExternalProject)

# Paths
set(FOOYIN_SRC ${CMAKE_BINARY_DIR}/fooyin-src)
set(FOOYIN_BUILD ${CMAKE_BINARY_DIR}/fooyin-build)
set(MSUINPUT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/msuinput)
set(PLUGINS_CMAKELISTS ${FOOYIN_SRC}/src/plugins/CMakeLists.txt)
set(OUTPUT_LIB ${CMAKE_SOURCE_DIR}/fyplugin_msuinput.so)

# Download and build Fooyin
ExternalProject_Add(fooyin
    GIT_REPOSITORY https://github.com/fooyin/fooyin.git
    GIT_TAG master
    SOURCE_DIR ${FOOYIN_SRC}
    BINARY_DIR ${FOOYIN_BUILD}
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release
               -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install
    BUILD_ALWAYS 1
)

# Prepare the msuinput plugin before building Fooyin
ExternalProject_Add_Step(fooyin prepare_msu
    COMMAND ${CMAKE_COMMAND} -DMSUINPUT_SRC=${MSUINPUT_SRC} -DFOOYIN_SRC=${FOOYIN_SRC} -DPLUGINS_CMAKELISTS=${PLUGINS_CMAKELISTS} -P ${CMAKE_CURRENT_SOURCE_DIR}/prepare_msu.cmake
    DEPENDEES download
    COMMENT "Copying msuinput and adding it to Fooyin plugins"
)

# Path to the compiled plugin
set(MSU_LIB_PATH ${FOOYIN_BUILD}/run/lib/fooyin/plugins/fyplugin_msuinput.so)
set(OUTPUT_LIB ${CMAKE_CURRENT_SOURCE_DIR}/fyplugin_msuinput.so)

# Step to copy the plugin to the root of fooyin-msuinput
ExternalProject_Add_Step(fooyin copy_msu_lib
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MSU_LIB_PATH} ${OUTPUT_LIB}
    DEPENDEES build
    COMMENT "Copying fyplugin_msuinput.so to project root"
)
