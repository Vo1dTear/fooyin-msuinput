#pragma once

#include <core/engine/audioinput.h>
#include <QFile>

namespace Fooyin::MSU {

    class MSUDecoder : public AudioDecoder
    {
    public:
        MSUDecoder();
        qint64 loopTimeMs() const { return m_loopTimeMs; }
        quint64 loopFrame() const { return m_loopFrame; }

        [[nodiscard]] QStringList extensions() const override;
        [[nodiscard]] bool isSeekable() const override;
        [[nodiscard]] uint64_t totalFrames() const { return m_totalFrames; }
        [[nodiscard]] const AudioFormat& format() const { return m_format; }

        std::optional<AudioFormat> init(const AudioSource& source, const Track& track, DecoderOptions options) override;
        void stop() override;
        void seek(uint64_t pos) override;
        AudioBuffer readBuffer(size_t bytes) override;

    private:
        QIODevice* m_file{nullptr};
        AudioFormat m_format;
        uint64_t m_currentFrame{0};

        quint64 m_totalFrames{0};
        qint64 m_dataOffset{0};
        quint64 m_loopFrame{0};

        // --- loop point ---
        qint64 m_loopTimeMs{0};  // loop point in milliseconds
    };

    class MSUReader : public AudioReader
    {
    public:
        [[nodiscard]] QStringList extensions() const override;
        [[nodiscard]] bool canReadCover() const override;
        [[nodiscard]] bool canWriteMetaData() const override;

        bool readTrack(const AudioSource& source, Track& track) override;
    };

} // namespace Fooyin::MSU
