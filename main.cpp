#include <iostream>

#include "src/simple_audio_source.hpp"

int main(int argc, char** argv)
{
    std::cout << "Hello, world!" << std::endl;

    // инициализируем PortAudio
    auto err = Pa_Initialize();
    if (err != paNoError) {
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
        return 0; // больше делать нечего
    }

    // ... work ...

    // завершаем работу PortAudio
    err = Pa_Terminate();
    if (err != paNoError) {
        printf("PortAudio error: %s\n", Pa_GetErrorText(err));
    }

    return 0;
}
