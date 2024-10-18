#include "/home/reroru/project_1/general/port_client.h"
#include <unistd.h>
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if(argc != 3) { // мы должны передать исполняемый файл, порт и интервал запроса
        std::cerr << "Задано неверное количество аргументов" << std::endl;
    return 1;
    }

    const char* port = argv[1];
    int pollInterval = std::atoi(argv[2]); // string -> int

    PortClient client(port);  // передаем порт через аргумент
    while (true) {
        client.requestTime();
        sleep(pollInterval);  // используем заданный интервал
    }
    return 0;
}