#include "TcpListener.h"

int TcpListener::init()
{
    // Initialize win sock
    WSADATA wsdata;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsdata);
    if (wsOk != 0)
    {
        return wsOk;
    }

    // create a socket
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == INVALID_SOCKET)
    {
        return WSAGetLastError();
    }

    // Bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(m_port);
    inet_pton(AF_INET, m_ipAddress, &hint.sin_addr);

    if (bind(m_socket, (sockaddr *)&hint, sizeof(hint)) == SOCKET_ERROR)
    {
        return WSAGetLastError();
    }

    if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        return WSAGetLastError();
    }

    FD_ZERO(&m_master);
    FD_SET(m_socket, &m_master);

    return 0;
}

int TcpListener::run()
{
    bool running = true;
    while (running)
    {
        fd_set copy = m_master;
        int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
        for (int i = 0; i < socketCount; i++)
        {
            SOCKET socket = copy.fd_array[i];
            if (sock == m_socket)
            {
                SOCKET client = accept(m_socket, nullptr, nullptr);
                FD_SET(client, &m_master);
                // TODO:
            }
            else
            {
                char buf[4096];
                ZeroMemory(buf, 4096);

                int bytesIn = recv(sock, buf, 4096, 0);
                if (bytesIn <= 0)
                {
                    closesocket(sock);
                    FD_CLR(sock, &m_master);
                }
                else
                {
                    if (buf[0] == '\\')
                    {
                        for (int i = 0; i < m_master; i++)
                        {
                            SOCKET outSock = m_master.fd_array[i];
                            if (outSock != m_socket && outSock != sock)
                            {
                            }
                        }
                    }
                }
            }
        }
    }
    FD_CLR(m_socket, &m_master);
    closesocket(m_socket);

    // string msg = "Server is shutting down. GoodBye\r\n";

    while (m_master.fd_count > 0)
    {
        SOCKET sock = m_master.fd_array[0];
        // send(sock, msg.c_str(), msg.size + 1, 0);

        FD_CLR(sock, &m_master);
        closesocket(sock);
    }
    WSACleanup();
}
void TcpListener::sendToClient(int clientSocket, const char *msg, int length){

};
void TcpListener::broadcastToClient(int sendingClient, const char *msg, int length){
    
};