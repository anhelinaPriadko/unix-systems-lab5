// process_b.cpp
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

int main() {
    pid_t target_pid;
    unsigned long address;

    std::cout << "Введіть PID цілі: ";
    std::cin >> target_pid;
    std::cout << "Введіть адресу змінної: ";
    std::cin >> std::hex >> address;

    char mem_path[64];
    sprintf(mem_path, "/proc/%d/mem", target_pid);

    if (ptrace(PTRACE_ATTACH, target_pid, NULL, NULL) == -1) {
        perror("ptrace attach");
        return 1;
    }
    waitpid(target_pid, NULL, 0);

    int fd = open(mem_path, O_RDONLY);
    if (fd == -1) {
        perror("open mem");
        return 1;
    }

    int buffer;
    while (true) {
        pread(fd, &buffer, sizeof(int), address);
        std::cout << "\rЗчитане значення: " << std::dec << buffer << std::flush;
        usleep(500000); // 0.5 сек
    }

    close(fd);
    ptrace(PTRACE_DETACH, target_pid, NULL, NULL);
    return 0;
}