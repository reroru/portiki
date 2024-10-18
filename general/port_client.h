#ifndef PORT_CLIENT_H
#define PORT_CLIENT_H

class PortClient {
public:
    PortClient(const char* port);
    ~PortClient();
    void requestTime();

private:
    int fd;
};

#endif