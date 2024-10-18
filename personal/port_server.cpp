#include "/home/reroru/project_1/general/port_server.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <ctime>
#include <cstdint>

PortServer::PortServer(const char* port) {
    fd = open(port, O_RDWR | O_NOCTTY | O_SYNC);  // открытие последовательного порт
    if (fd < 0) { // если при открытии порта возникнет ошибка, функция open() вернет -1
        std::cerr << "Не удалось открыть порт: " << port << std::endl;
        exit(EXIT_FAILURE); // завершаем работу программы, если порт не открыт
    }
}

PortServer::~PortServer() {
    close(fd);  // закрываем порт при завершении работы
}

void PortServer::start() {
    while (true) {
        char buffer[1]; // буфер для чтения запроса
        // ожидание запроса от клиента
        int bytesRead = read(fd, buffer, 1);


        if (bytesRead > 0 && buffer[0] == 'T') { // добавлена проверка на принимаемое значение, для отсеивания ненужный запросов
            // приведение результата фукнции time(nullptr) к типу uint32_t.
            uint32_t currentTime = static_cast<uint32_t>(time(nullptr));
            // отправка времени клиенту
            write(fd, &currentTime, sizeof(currentTime));
        }

        usleep(50000); // 50 мс задержка
    }
}

