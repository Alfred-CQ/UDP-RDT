#include "../include/udp_server.h"

/* Constructors */
UDPServer::UDPServer(string ip, uint port)
{
    server_port = port;
    server_ip   = ip;

    if ((server_sockFD = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero), 8);

    if (bind(server_sockFD, (SOCK_ADDR *)&server_addr, sizeof(SOCK_ADDR)) == -1)
    {
        perror("Bind");
        exit(1);
    }

    server_current_path  = fs::current_path();
    server_resources_path = "../" + string(RESOURCES_DIR) + "/";

    for (const auto & entry : fs::directory_iterator(server_current_path))
    {
        if (entry.is_directory() && entry.path().filename() == RESOURCES_DIR)
                server_resources_path = string(RESOURCES_DIR) + "/";
    }

}

/* Methods */
// Senders


// Receivers
bool UDPServer::recv_Request()
{
    
}

// Utilities
void UDPServer::print_Information()
{   
    system("clear");
    
    cout << "      ░░█▀▀░█▀▀░█▀▄░█░█░█▀▀░█▀▄░░░█░█░█▀▄░█▀█░░\n" 
         << "      ░░▀▀█░█▀▀░█▀▄░▀▄▀░█▀▀░█▀▄░░░█░█░█░█░█▀▀░░\n"
         << "      ░░▀▀▀░▀▀▀░▀░▀░░▀░░▀▀▀░▀░▀░░░▀▀▀░▀▀░░▀░░░░\n"
         << "******************************************************\n"
         << "        IP            : " << server_ip << "\n"
         << "        PORT          : " << server_port << "\n"
         << "        RESOURCES_PATH: " << server_resources_path << "\n"
         << "******************************************************"
         << endl;
}