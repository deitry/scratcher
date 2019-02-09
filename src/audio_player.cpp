#include "audio_player.h"

AudioPlayer::AudioPlayer(const QAudioDeviceInfo &audioDevice, const QAudioFormat &format, QObject *parent): QObject(parent), m_audioFile(NULL)
{
    m_audioDevice = new QAudioDeviceInfo(audioDevice);
    m_audioFormat = new QAudioFormat(format);

    m_audioOutput = new QAudioOutput(*m_audioDevice, *m_audioFormat, this);
    m_audioDecoder = new QAudioDecoder(this);
    m_audioBuffer = new QBuffer(this);
    m_outputData = new QBuffer(this);

    m_audioDecoder->setAudioFormat(*m_audioFormat);

    connect(m_audioOutput, SIGNAL(stateChanged(QAudio::State)), this, SLOT(OnHandleStateChanged(QAudio::State)));
    connect(m_audioDecoder, SIGNAL(bufferReady()), this, SLOT(OnBufferReady()));
}

AudioPlayer::~AudioPlayer()
{
//  delete m_audioBuffer;
}

void AudioPlayer::play(const QString &fileName)
{
    m_audioFile = new QFile(fileName);
    this->play(m_audioFile);
}

void AudioPlayer::play(QByteArray* data)
{
    if(!data->isEmpty())
    {
        if (m_audioBuffer->isOpen())
            m_audioBuffer->close();
        m_audioBuffer->setBuffer(data);
        play(m_audioBuffer);
    }
    else
    {
        emit audioPlayerFree();
    }
}

void AudioPlayer::play(QIODevice* inputDevice)
{
    emit audioPlayerBusy();

    if(!inputDevice->isOpen())
        inputDevice->open(QIODevice::ReadOnly);
    m_audioDecoder->setSourceDevice(inputDevice);
    emit m_audioDecoder->start();
}

void AudioPlayer::OnBufferReady()
{
    qDebug() << "onBifferReady";

    QAudioBuffer audioBuffer = m_audioDecoder->read();
    if (!audioBuffer.isValid())
        return;

    (m_outputData->buffer()).append(static_cast<const char*>(audioBuffer.data()), audioBuffer.byteCount());
    if(m_audioOutput->state() != QAudio::ActiveState)
    {
        m_outputData->open(QIODevice::ReadOnly);
        m_audioOutput->start(m_outputData);
    }
}

void AudioPlayer::OnHandleStateChanged(QAudio::State state)
{
    qDebug() << "enter state" << static_cast<int>(state);
    switch (state)
    {
        case QAudio::IdleState:
        {
            m_audioOutput->stop();
            m_audioBuffer->close();
            (m_outputData->buffer()).clear();
            delete m_audioFile;
            emit audioPlayerFree();
            break;
        }
        default:
        {
        }
    }
}
