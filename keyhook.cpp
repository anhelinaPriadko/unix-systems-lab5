// keyhook.cpp
#include <iostream>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

int main() {
    const char* dev = "/dev/input/event3"; 
    int fd = open(dev, O_RDONLY);

    if (fd == -1) {
        perror("Не вдалося відкрити пристрій (спробуйте sudo)");
        return 1;
    }

    struct input_event ev;
    std::cout << "Слухаю клавіатуру... (натисніть Ctrl+C для виходу)\n";

    while (read(fd, &ev, sizeof(ev)) > 0) {
        if (ev.type == EV_KEY && ev.value == 1) {
            std::cout << "Натиснуто клавішу з кодом: " << ev.code << std::endl;
        }
    }

    close(fd);
    return 0;
}