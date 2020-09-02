#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <signal.h>
#include <unistd.h>
#include <ctime>
#include <sstream>
#include <cstring>

void alarmHandler(int sig) {

}

int main(int argc, char **argv) {

    if (argc == 2 && (strcmp(argv[1], "-h") == 0)) {
            printf("usage: %s flag delay sound-file\n", argv[0]);
            printf("-s\tseconds\n");
            printf("-m\tminutes\n");
            printf("-h\thours\n");
            exit(0);
    }

    if (argc != 4) {
        printf("usage: %s flag delay sound-file\n", argv[0]);
        printf("help: %s -h\n", argv[0]);
        exit(0);
    }


    char *flag = argv[1], *fileName = argv[3];

    double delay;
    std::stringstream ss(argv[2]);
    ss >> delay;

    if (strcmp(flag, "-m") == 0) {
        delay *= 60;
    } else if (strcmp(flag, "-h") == 0) {
        delay *= 60 * 60;
    }

    printf("Waiting for alarm...\n");
    alarm(delay);
    signal(SIGALRM, alarmHandler);

    pause();

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(fileName))
        return -1;

    sf::Sound sound;
    sound.setLoop(true);
    sound.setBuffer(buffer);
    sound.play();

    printf("> It's time\n");
    printf("> Start your day routine\n");
    printf("> Stop alarm...");
    getchar();

    return 0;
}
