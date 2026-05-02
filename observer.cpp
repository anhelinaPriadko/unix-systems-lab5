// observer_pro.cpp
#include <iostream>
#include <sys/uio.h>
#include <unistd.h>

int main() {
    pid_t target_pid;
    unsigned long address;

    std::cout << "Введіть PID: ";
    std::cin >> target_pid;
    std::cout << "Введіть адресу: ";
    std::cin >> std::hex >> address;

    int buffer;
    
    struct iovec local[1];
    local[0].iov_base = &buffer;
    local[0].iov_len = sizeof(int);

    struct iovec remote[1];
    remote[0].iov_base = (void*)address;
    remote[0].iov_len = sizeof(int);

    while (true) {
        ssize_t nread = process_vm_readv(target_pid, local, 1, remote, 1, 0);
        
        if (nread == -1) {
            perror("process_vm_readv failed");
            break;
        }

        std::cout << "\rЗначення в target: " << std::dec << buffer << "   " << std::flush;
        usleep(100000); 
    }

    return 0;
}