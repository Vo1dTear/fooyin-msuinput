#pragma once

#include <core/engine/inputplugin.h>
#include <core/plugins/plugin.h>

class QCheckBox;
class QWidget;

namespace Fooyin::MSU {

    class MSUSettingsWidget;

    class MSUPlugin : public QObject,
    public Plugin,
    public InputPlugin
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "org.fooyin.fooyin.plugin" FILE "msuinput.json")
        Q_INTERFACES(Fooyin::Plugin Fooyin::InputPlugin)

    public:
        [[nodiscard]] QString inputName() const override;
        [[nodiscard]] InputCreator inputCreator() const override;

        [[nodiscard]] bool hasSettings() const override;
        void showSettings(QWidget* parent) override;
    };

} // namespace Fooyin::MSU
