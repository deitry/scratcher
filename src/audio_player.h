    #ifndef AUDUOPLAYER_H
    #define AUDUOPLAYER_H

    #include <QtCore/qglobal.h>
    #include <QAudioOutput>
    #include <QAudioDecoder>
    #include <QBuffer>
    #include <QFile>


    class AudioPlayer: public QObject
    {
        Q_OBJECT

    private:
        QAudioDeviceInfo* m_audioDevice;
        QAudioFormat* m_audioFormat;
        QAudioOutput* m_audioOutput;
        QAudioDecoder *m_audioDecoder;
        QBuffer *m_outputData;
        QBuffer* m_audioBuffer;

        QFile* m_audioFile;

    public slots:
        void OnBufferReady();
        void OnHandleStateChanged(QAudio::State state);

    public:
        AudioPlayer(const QAudioDeviceInfo &audioDevice, const QAudioFormat &format, QObject *parent = 0);
        ~AudioPlayer();

        void play(QIODevice* inputDevice);
        void play(QByteArray* data);
        void play(const QString &fileName);

    signals:
        void audioPlayerBusy();
        void audioPlayerFree();
    };

    #endif  // AUDUOPLAYER_H_
