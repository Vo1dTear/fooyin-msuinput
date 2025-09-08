# Copiar plugin
file(COPY "${MSUINPUT_SRC}" DESTINATION "${FOOYIN_SRC}/src/plugins")
message(STATUS "Copied msuinput to ${FOOYIN_SRC}/src/plugins")

# Leer el CMakeLists.txt de plugins
file(READ "${PLUGINS_CMAKELISTS}" CONTENTS)

# Añadir add_subdirectory(msuinput) solo si no existe
if(NOT "${CONTENTS}" MATCHES "add_subdirectory\\(msuinput\\)")
    # Añadir al final
    set(NEW_CONTENTS "${CONTENTS}\n# Added automatically by fooyin-msuinput\nadd_subdirectory(msuinput)\n")
    file(WRITE "${PLUGINS_CMAKELISTS}" "${NEW_CONTENTS}")
    message(STATUS "Added add_subdirectory(msuinput) to the end of ${PLUGINS_CMAKELISTS}")
else()
    message(STATUS "msuinput already present in ${PLUGINS_CMAKELISTS}")
endif()
