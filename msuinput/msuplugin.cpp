#include "msuplugin.h"
#include "msusettingswidget.h"
#include "msuinput.h"

namespace Fooyin::MSU {

    QString MSUPlugin::inputName() const
    {
        return QStringLiteral("MSU-1");
    }

    InputCreator MSUPlugin::inputCreator() const
    {
        InputCreator creator;
        creator.decoder = []() {
            auto decoder = std::make_unique<MSUDecoder>();

            QSettings settings;
            double gainDb = settings.value("MSU/Gain", 0.0).toDouble();
            quint32 loopCount = settings.value("MSU/LoopCount", 0).toUInt();
            bool enableLoop = settings.value("MSU/EnableLoop", true).toBool();

            decoder->setGain(gainDb);
            decoder->setLoopCount(loopCount);
            decoder->setEnableLoop(enableLoop);

            return decoder;
        };
        creator.reader  = []() { return std::make_unique<MSUReader>(); };
        return creator;
    }

    // Inform the framework that this plugin has settings
    bool MSUPlugin::hasSettings() const
    {
        return true;
    }

    // Show the settings window consistently with other plugins
    void MSUPlugin::showSettings(QWidget* parent)
    {
        auto* dialog = new MSUSettingsWidget(parent);
        dialog->setAttribute(Qt::WA_DeleteOnClose); // Qt will delete the dialog on close
        dialog->show(); // non-blocking
    }

} // namespace Fooyin::MSU

#include "moc_msuplugin.cpp"
