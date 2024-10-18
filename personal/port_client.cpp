#include "/home/reroru/project_1/general/port_client.h"
#include <iostream>
#include <unistd.h>  
#include <fcntl.h>   
#include <cstdint>
#include <ctime>

PortClient::PortClient(const char* port) {
    fd = open(port, O_RDWR | O_NOCTTY | O_SYNC); // открываем последовательный порт
    if (fd < 0) { // если при открытии порта возникнет ошибка, функция open() вернет -1
        std::cerr << "Не удалось открыть порт: " << port << std::endl;
        exit(EXIT_FAILURE); // завершаем работу программы, если порт не открыт
    }
}

PortClient::~PortClient() {
    close(fd); // закрываем порт при завершении работы
}

void PortClient::requestTime() {
    char request = 'T'; // создаем запрос для сервера
    write(fd, &request, 1); // отправляем запрос на сервер

    uint32_t timeStamp;
    int bytesRead = read(fd, &timeStamp, sizeof(timeStamp));
    if (bytesRead > 0) {
        std::time_t timeStampTime = static_cast<std::time_t>(timeStamp); // преобразуем timestamp в time_t
        std::tm* localTime = std::localtime(&timeStampTime); // преобразуем time_t в локальное время
        
        // форматируем время в строку
        char buffer[21]; // для вывода в виде ГГГГ-ММ-ДД ЧЧ:ММ:СС нужен 21 символ с учетом нуль-символа
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
        
        std::cout << "Время в данный момент: " << buffer << std::endl;
    }
}