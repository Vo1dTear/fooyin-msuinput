# Copy plugin
file(COPY "${MSUINPUT_SRC}" DESTINATION "${FOOYIN_SRC}/src/plugins")
message(STATUS "✅ Copied msuinput to ${FOOYIN_SRC}/src/plugins")

# Modify Fooyin's CMakeLists.txt to include msuinput
file(READ "${PLUGINS_CMAKELISTS}" CONTENTS)

if(NOT "${CONTENTS}" MATCHES "add_subdirectory\\(msuinput\\)")
    set(NEW_CONTENTS "${CONTENTS}\n# Added automatically by fooyin-msuinput\nadd_subdirectory(msuinput)\n")
    file(WRITE "${PLUGINS_CMAKELISTS}" "${NEW_CONTENTS}")
    message(STATUS "✅ Added add_subdirectory(msuinput) to ${PLUGINS_CMAKELISTS}")
else()
    message(STATUS "ℹ️ msuinput already present in ${PLUGINS_CMAKELISTS}")
endif()
