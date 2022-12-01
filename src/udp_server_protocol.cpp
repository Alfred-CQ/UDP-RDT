#include "../include/udp_server.h"
#include "../include/utils.h"
#include "../include/message.h"

/* Constructors */
UDPServer::UDPServer(string _ip, uint _port)
{
    ip       = _ip;
    port     = _port;
    addr_len = sizeof(struct sockaddr);
    stream   = 0;
    
    if ((sockFD = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bzero(&(addr.sin_zero), 8);

    if (bind(sockFD, (SOCK_ADDR *)&addr, sizeof(SOCK_ADDR)) == -1)
    {
        perror("Bind");
        exit(1);
    }

    server_current_path   = fs::current_path();
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
void UDPServer::send_Responses(string resource_name)
{
    string   resource_path { server_resources_path + resource_name };
    ifstream resource      { resource_path, std::ios::in };

    int      size_resource;
    uint     number_segments, padding{0};
    char     data_read[MAX_DATA_SIZE];

    resource.seekg(0, resource.end);
    size_resource = resource.tellg();
    resource.seekg(0, resource.beg);

    number_segments = (size_resource + MAX_DATA_SIZE - 1) / MAX_DATA_SIZE;
    
    Response* response = new Response(resource_name, stream++, number_segments);
    
    response->set_Source(sockFD);
    response->set_Destination((SOCK_ADDR*)& client_addr);

    cout << "******************************************************\n"
         << " 📨 Sending resource " << resource_name << " in the stream " << endl;

    for (size_t i = 0; i < number_segments; ++i)
    {
        resource.read(data_read,MAX_DATA_SIZE);
        
        size_resource -= MAX_DATA_SIZE;

        if (size_resource < 0)
        {
            padding = (size_resource * -1);
            utils::fill_Zeros(data_read, padding);
        }

        response->insert_Segment( i + 10, padding, data_read);
        response->send_Segment(i + 10);
    }

    response->print_Head();
    response->print_Tail();
    
    cout << " 📪 Resource sent \n"
         << "******************************************************" << endl;
         
    resource.close();
}

// Receivers
void UDPServer::recv_Requests()
{
    char size_Request[3];
    string resource_name;

    bytes_recv = 0;
    recv_buffer = new char[REQUEST_NAME_SIZE];
   
    while (1)
    {
        bytes_recv = recvfrom(sockFD, recv_buffer, REQUEST_NAME_SIZE, 0, (SOCK_ADDR *)& client_addr, &addr_len);
        
        strncpy(size_Request, recv_buffer, 2);

        resource_name = string(recv_buffer, 2, atoi(size_Request));

        if (find_Resource(resource_name))
        {
            cout << " Resource found ✨ in " << resource_name << " 🗃\n";
            thread(&UDPServer::send_Responses, this, resource_name).detach();
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
         << "        IP            : " << ip << "\n"
         << "        PORT          : " << port << "\n"
         << "        RESOURCES_PATH: " << server_resources_path << "\n"
         << "******************************************************"
         << endl;
}

bool UDPServer::find_Resource(string resource_name)
{
    for (const auto & entry : fs::directory_iterator(server_resources_path))
    {
        if ( entry.path().filename() == resource_name )
            return true;
    }

    return false;
}