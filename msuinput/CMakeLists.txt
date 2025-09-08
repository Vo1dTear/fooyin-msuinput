set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTORCC OFF)

create_fooyin_plugin_internal(
    msuinput
    DEPENDS Fooyin::Core
            Fooyin::Gui
    SOURCES msuplugin.cpp
            msuplugin.h
            msuinput.cpp
            msuinput.h
            msusettingswidget.cpp
            msusettingswidget.h

)
