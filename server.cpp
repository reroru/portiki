#include <iostream>
#include <chrono>
#include <ctime>
#include <unistd.h>  
#include <fcntl.h>   

using namespace std;

class PortServer {
public:
    PortServer(const char* port) {
        fd = open(port, O_RDWR | O_NOCTTY | O_SYNC);  // открываем последовательный порт
        if (fd < 0) { // если при открытии порта вознкает ошибка, фунуция open() вернет -1
            cerr << "Не удалось открыть порт: " << port << endl;
        }
    }

    ~PortServer() {
        close(fd); // закрываем порт при завершении работы
    }

    void start() {
        while (true) {
            char buffer[1]; // буфер для чтения запроса
            // ожидание запроса от клиента
            int bytesRead = read(fd, buffer, 1);
            if (bytesRead > 0) {
                string currentTime = getCurrentTime();
                // отправка времени клиенту
                write(fd, currentTime.c_str(), currentTime.size());
            }
            usleep(1000000); // задержка 1 секунда
        }
    }

private:
    int fd;  // дескриптор файла для ппорта

    string getCurrentTime() { // получаем текущее время системы
        auto now = chrono::system_clock::now(); // получает текущее время.
        time_t currentTime = chrono::system_clock::to_time_t(now); // преобразует его в стандартный формат 
        return ctime(&currentTime);
    }
};

int main() {
    PortServer server("/dev/pts/2");  // виртуальный порт
    server.start();
    return 0;
}