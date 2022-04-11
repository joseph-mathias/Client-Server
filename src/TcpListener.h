#include <iostream>
#include <ws2tcpip.h>
#include <string>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

class TcpListener
{
public:
    TcpListener(const char *ipAddress, int port) : m_ipAddress(ipAddress), m_port(port) {}
    // Initialize the listener
    int init();
    // Run the listener
    int run();

protected:
    virtual void onClientConnected();
    virtual void onClientDisconnected();
    void sendToClient(int clientSocket, const char *msg, int length);
    void broadcastToClient(int sendingClient, const char *msg, int length);

private:
    const char *m_ipAddress; // IP Address server will run om
    int m_port;              // Port # for the web service
    int m_socket;            // Internal FD For the listening socket
    fd_set m_master;         // master file description
};