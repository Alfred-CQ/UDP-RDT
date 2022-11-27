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

    thread(&UDPServer::recv_Requests, this).detach();
}

/* Methods */
// Senders


// Receivers
void UDPServer::recv_Requests()
{
    char size_Request[3];
    string resource_name;

    server_bytes_recv = 0;
    server_recv_buffer = new char[REQUEST_SIZE];
   
    while (1)
    {
        server_bytes_recv = recvfrom(server_sockFD, server_recv_buffer, 
                                     REQUEST_SIZE, 0, 
                                     (SOCK_ADDR *)& client_addr, &server_addr_len
                                    );
        
        strncpy(size_Request, server_recv_buffer, 2);

        resource_name = string(server_recv_buffer, 2, atoi(size_Request));

        if (query_Available(resource_name))
        {
            cout << "Resource found ✨\n";
            cout << "Resource path: " << resource_name << "\n";
        }
        else
        {
            cout << "Resource not found 🚫" << endl;
        }
    }
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

bool UDPServer::query_Available(string& resource_name)
{
    for (const auto & entry : fs::directory_iterator(server_resources_path))
    {
        if ( entry.path().filename() == resource_name )
        {
            resource_name = server_resources_path + resource_name;
            return true;
        }
            
    }

    return false;
}