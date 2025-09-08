# Copy plugin
file(COPY "${MSUINPUT_SRC}" DESTINATION "${FOOYIN_SRC}/src/plugins")
message(STATUS "Copied msuinput to ${FOOYIN_SRC}/src/plugins")

# Read the plugins CMakeLists.txt
file(READ "${PLUGINS_CMAKELISTS}" CONTENTS)

# Add add_subdirectory(msuinput) only if it doesn't exist
if(NOT "${CONTENTS}" MATCHES "add_subdirectory\\(msuinput\\)")
    # Append at the end
    set(NEW_CONTENTS "${CONTENTS}\n# Added automatically by fooyin-msuinput\nadd_subdirectory(msuinput)\n")
    file(WRITE "${PLUGINS_CMAKELISTS}" "${NEW_CONTENTS}")
    message(STATUS "Added add_subdirectory(msuinput) to the end of ${PLUGINS_CMAKELISTS}")
else()
    message(STATUS "msuinput already present in ${PLUGINS_CMAKELISTS}")
endif()
