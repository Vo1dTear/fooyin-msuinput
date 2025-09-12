cmake_minimum_required(VERSION 3.16)

project(fooyin-msuinput)

# ---------------- Paths ----------------
set(FOOYIN_SRC ${CMAKE_BINARY_DIR}/fooyin-src)
set(FOOYIN_BUILD ${CMAKE_BINARY_DIR}/fooyin-build)
set(MSUINPUT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/msuinput)
set(PLUGINS_CMAKELISTS ${FOOYIN_SRC}/src/plugins/CMakeLists.txt)
set(OUTPUT_LIB ${CMAKE_CURRENT_SOURCE_DIR}/fyplugin_msuinput.so)

# ---------------- Clone Fooyin if missing ----------------
if(NOT EXISTS ${FOOYIN_SRC})
    message(STATUS "Cloning Fooyin repository...")
    execute_process(
        COMMAND git clone --recursive https://github.com/fooyin/fooyin.git ${FOOYIN_SRC}
        RESULT_VARIABLE res
    )
    if(NOT res EQUAL 0)
        message(FATAL_ERROR "Failed to clone Fooyin")
    endif()
endif()

# ---------------- Target to update Fooyin ----------------
add_custom_target(fooyin_update
    COMMAND git -C ${FOOYIN_SRC} fetch --all
    COMMAND git -C ${FOOYIN_SRC} reset --hard origin/master
    COMMAND git -C ${FOOYIN_SRC} submodule update --init --recursive
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "✅ Fooyin updated to latest master."
    COMMAND ${CMAKE_COMMAND} -E echo "⚠️ Run: cmake --build build --target prepare_msu"
    COMMAND ${CMAKE_COMMAND} -E echo "   to reinject msuinput after updating Fooyin"
    COMMENT "🔄 Updating Fooyin to latest master"
)

# ---------------- Prepare msuinput plugin ----------------
add_custom_target(prepare_msu
    COMMAND ${CMAKE_COMMAND}
            -DMSUINPUT_SRC=${MSUINPUT_SRC}
            -DFOOYIN_SRC=${FOOYIN_SRC}
            -DPLUGINS_CMAKELISTS=${PLUGINS_CMAKELISTS}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/prepare_msu.cmake
    COMMENT "⚙️ Preparing msuinput plugin"
)

# ---------------- Instructions ----------------
message(STATUS "✅ Preparation complete. Next steps:")
message(STATUS "  cd ${FOOYIN_BUILD}")
message(STATUS "  cmake -G Ninja ${FOOYIN_SRC} -DCMAKE_BUILD_TYPE=Release")
message(STATUS "  cmake --build . -- -j\$(nproc)")
message(STATUS "")
message(STATUS "📦 After building, copy the plugin manually with:")
message(STATUS "  cmake --build build --target copy_msu")

# ---------------- Manual copy command ----------------
set(MSU_LIB_PATH ${FOOYIN_BUILD}/run/lib/fooyin/plugins/fyplugin_msuinput.so)
add_custom_target(copy_msu_lib
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MSU_LIB_PATH} ${OUTPUT_LIB}
    DEPENDS ${MSU_LIB_PATH}
    COMMENT "📦 Copying fyplugin_msuinput.so to project root"
)
