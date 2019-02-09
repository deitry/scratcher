#include <iostream>

// #include <QFile>
// #include <QByteArray>
// #include <QAudioOutput>
#include <QDebug>

#include <QDataStream>
#include <qmath.h>
#include <QCoreApplication>
#include <QTimer>

#include "src/application.h"


int main(int argc, char** argv)
{
    // https://doc.qt.io/QT-5/qaudiooutput.html

    // QFile sourceFile;
    // QAudioOutput* audio;

    // QByteArray bytes(65536, 0);
    // auto stream = new QDataStream(&bytes, QIODevice::ReadWrite);
    // stream->setByteOrder(QDataStream::LittleEndian);
    // auto audio = new QAudioOutput(m_device, m_format,this);
    // audio->setBufferSize(131072);
    // audio->setNotifyInterval(50);
    // auto audiodevice = audio->start();
    // connect(audio,SIGNAL(notify()),this,SLOT(slot_writedata()));
    // read_frames();




    // // sourceFile.setFileName("resources/test.raw");
    // // sourceFile.open(QIODevice::ReadOnly);

    // QAudioFormat format;
    // // Set up the format, eg.
    // format.setSampleRate(8000);
    // format.setChannelCount(1);
    // format.setSampleSize(8);
    // format.setCodec("audio/pcm");
    // format.setByteOrder(QAudioFormat::LittleEndian);
    // format.setSampleType(QAudioFormat::UnSignedInt);

    // QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    // if (!info.isFormatSupported(format)) {
    //     qWarning() << "Raw audio format not supported by backend, cannot play audio.";
    //     return 0;
    // }

    // audio = new QAudioOutput(format, this);
    // connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
    // audio->start(&sourceFile);

    QScopedPointer< QCoreApplication > app(new MyApplication(argc, argv));






    return app->exec();
}
