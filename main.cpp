#include <iostream>

#include "src/simple_audio_source.hpp"


#define SAMPLE_RATE (44100)
static paTestData data;

int main(int argc, char** argv)
{
    std::cout << "Hello, world!" << std::endl;

    // инициализируем PortAudio
    auto err = Pa_Initialize();
    if (err != paNoError) {
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
        return 0; // больше делать нечего
    }

    // открываем аудиопоток
    PaStream *stream;
    err = Pa_OpenDefaultStream( &stream,
                                0,          /* no input channels */
                                2,          /* stereo output */
                                paFloat32,  /* 32 bit floating point output */
                                SAMPLE_RATE,
                                256,        /* frames per buffer, i.e. the number
                                                of sample frames that PortAudio will
                                                request from the callback. Many apps
                                                may want to use
                                                paFramesPerBufferUnspecified, which
                                                tells PortAudio to pick the best,
                                                possibly changing, buffer size.*/
                                patestCallback, /* this is your callback function */
                                &data ); /*This is a pointer that will be passed to
                                                your callback*/
    if (err != paNoError) {
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
    }

    // запускаем поток
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
    }

    // немного ждём
    Pa_Sleep(1*1000); // в мс

    // останавливаем поток
    err = Pa_StopStream(stream);
    if (err != paNoError) {
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
    }

    // завершаем работу PortAudio
    err = Pa_Terminate();
    if (err != paNoError) {
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
    }

    return 0;
}
