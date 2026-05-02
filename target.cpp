#include <iostream>
#include <unistd.h>

int main() {
    int secret_value = 100;
    std::cout << "PID: " << getpid() << std::endl;
    std::cout << "Адреса змінної: " << &secret_value << std::endl;

    while (true) {
        std::cout << "Поточне значення: " << secret_value << ". Введіть нове: ";
        std::cin >> secret_value;
    }
    return 0;
}