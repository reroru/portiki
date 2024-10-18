#include "/home/reroru/project_1/general/port_server.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if(argc != 2) { // мы должны передать исполняемый файл и порт
        std::cerr << "Задано неверное количество аргументов" << std::endl;
    return 1;
    }

    const char* port = argv[1];

    PortServer server(port); // передаем порт через аргумент
    server.start();
    return 0;
}