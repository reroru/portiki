#ifndef PORT_SERVER_H
#define PORT_SERVER_H

class PortServer {
public:
    PortServer(const char* port);
    ~PortServer();
    void start();

private:
    int fd;
};

#endif