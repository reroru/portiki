#include <iostream>
#include <unistd.h>  
#include <fcntl.h>   

using namespace std;

class PortClient {
public:
    PortClient(const char* port) {
        fd = open(port, O_RDWR | O_NOCTTY | O_SYNC); // открываем последовательный порт
        if (fd < 0) { // если при открытии порта вознкает ошибка, фунуция open() вернет -1
            cerr << "Не удалось открыть порт: " << port << endl;
        }
    }

    ~PortClient() {
        close(fd);  // закрываем порт при завершении работы
    }

    void requestTime() {
        char request = 'T';  // создаем запрос для сервера
        write(fd, &request, 1); // отправляем запрос на сервер

        char buffer[128]; // буфер для получения ответа
        int bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0'; 
            cout << "Время в данный момент: " << buffer << endl;
        }
    }

private:
    int fd;  // дескриптор файла для порта
};

int main() {
    PortClient client("/dev/pts/3");  // виртуальный порт
    while (true) {
        client.requestTime();  // запрос времени у сервера
        sleep(1);  // ожидание 1 секунда между запросами
    }
    return 0;
}
