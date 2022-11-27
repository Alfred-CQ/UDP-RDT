#include "../include/udp_client.h"
#include "../include/utils.h"

/* Constructors and Destructor */
UDPClient::UDPClient(string ip_server, uint port)
{
    client_host = (HOST *)gethostbyname((char *)ip_server.c_str());
    client_port = port;

    if ((client_sockFD = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(client_port);
    server_addr.sin_addr   = *((IN_ADDR *)client_host->h_addr);

    bzero(&(server_addr.sin_zero), 8);
}

UDPClient::~UDPClient()
{

}

/* Methods */
// Senders
void UDPClient::send_Request(string resource_request)
{
    if (resource_request != START)
        cout << "\n 🗂️ Request: " << resource_request << " successfully sent ✅\n";
    else
    {
        cout << "\n 🗳️ End of requests, command [ " << resource_request << " ] found \n\n";
        return;
    }

    string request    = utils::complete_Bytes(resource_request.size(), 2) + resource_request;

    client_bytes_send = sendto(client_sockFD, &(request.front()), request.size(), 0, (SOCK_ADDR*)& server_addr, SOCK_ADDR_SIZE);
}

// Receivers

// Utilities
void UDPClient::print_Information()
{   
    system("clear");

    cout << "      ░░█▀▀░█░░░▀█▀░█▀▀░█▀█░▀█▀░░░█░█░█▀▄░█▀█░░\n" 
         << "      ░░█░░░█░░░░█░░█▀▀░█░█░░█░░░░█░█░█░█░█▀▀░░\n"
         << "      ░░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░░▀░░░░▀▀▀░▀▀░░▀░░░░\n"
         << "*****************************************************\n"
         << "        PORT          : " << client_port
         << endl;
}