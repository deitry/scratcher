#include "application.h"

#include <QDataStream>
#include <QTimer>
#include <qmath.h>

#include "src/audio_player.h"

MyApplication::MyApplication(int &argc, char **argv)
    : QCoreApplication(argc, argv)
{
    QTimer timer;
    timer.setInterval(1000);

    QAudioDeviceInfo di = QAudioDeviceInfo::defaultOutputDevice();
    qDebug() << di.deviceName();

    QAudioFormat af = QAudioFormat();
    af.setCodec("audio/pcm");
    af.setSampleRate(44100);
    af.setSampleSize(8);
    af.setByteOrder(QAudioFormat::LittleEndian);
    af.setSampleType(QAudioFormat::UnSignedInt);
    af.setChannelCount(2);

    if(!di.isFormatSupported(af)){
        af = di.nearestFormat(af);
    }

    auto audio = new QAudioOutput(af);
    audio->setNotifyInterval(50);
    audio->setBufferSize(32768);

    // QObject::connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));

    auto buf = new QByteArray();
    QDataStream s(buf, QIODevice::ReadWrite);

    // qDebug() << "Len: " << buf->length();
    // audio->start(s.device());
    // qDebug() << "State: " << audio->state();
    // qDebug() << "Error: " << audio->error();

    QObject::connect(&timer, &QTimer::timeout, this,
    [&] () {
        qDebug() << "onTimeout";

        for (int i = 0; i < 100; ++i) {
            for(float ii=0.0f; ii<360.0f; ii+=(360.0f*1000.0f/af.sampleRate())){
                int sample = ((int)(qSin(qDegreesToRadians(ii)) * 65536));
                // char sample = (char)(qSin(qDegreesToRadians(ii)) * 256); // also tried 8 bit with char sample
                s << sample;
                qDebug() << sample;
            }
        }
    });
    timer.start();

    AudioPlayer player(di, af);
    // player.play(s.device());
    player.play(buf);

    qDebug() << "end constructor";
}

MyApplication::~MyApplication() {
}
