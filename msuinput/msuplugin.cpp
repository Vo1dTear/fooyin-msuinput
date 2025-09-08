#include "msuplugin.h"

namespace Fooyin::MSU {

    QString MSUPlugin::inputName() const
    {
        return QStringLiteral("MSU-1");
    }

    InputCreator MSUPlugin::inputCreator() const
    {
        InputCreator creator;
        creator.decoder = []() { return std::make_unique<MSUDecoder>(); };
        creator.reader  = []() { return std::make_unique<MSUReader>(); };
        return creator;
    }

} // namespace Fooyin::MSU

#include "moc_msuplugin.cpp"
