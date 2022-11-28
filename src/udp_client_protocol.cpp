#include "../include/udp_client.h"
#include "../include/utils.h"

/* Constructors and Destructor */
UDPClient::UDPClient(string ip_server, uint port)
{
    client_host     = (HOST *)gethostbyname((char *)ip_server.c_str());
    client_port     = port;
    client_addr_len = sizeof(struct sockaddr);

    if ((client_sockFD = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(client_port);
    server_addr.sin_addr   = *((IN_ADDR *)client_host->h_addr);

    bzero(&(server_addr.sin_zero), 8);

    thread(&UDPClient::recv_Responses, this).detach();
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
void UDPClient::recv_Responses()
{
    client_recv_buffer = new char[MAX_MESSAGE_SIZE];

    vector<bool> streams_used (NUMBER_STREAMS, false);
    vector<vector<string>> data_streams(NUMBER_STREAMS);

    char stream;
    string number_segments;

    while (1)
    {
        client_bytes_recv = recvfrom(client_sockFD, client_recv_buffer, MAX_MESSAGE_SIZE, MSG_WAITALL, (SOCK_ADDR *)& server_addr, &client_addr_len);
        stream = client_recv_buffer[5];
        
        size_t idx_stream = atoi(&stream);
        number_segments = string(client_recv_buffer, 6, 4);
        
        cout << client_recv_buffer << endl;
        cout << " - " << idx_stream << " - " << number_segments << endl;

        data_streams[idx_stream].push_back(string(client_recv_buffer, 14, MAX_SEGMENT_SIZE));

        if (data_streams[idx_stream].size() == luint(atoi(number_segments.c_str())))
        {
            cout << "*****************************************************\n"
                 << "      📬 Resource received in stream" << stream << endl;

            ofstream out_file (string("requests/out_file") + string(&stream) + string(".txt"));

            for (size_t i = 0; i < data_streams[idx_stream].size(); ++i)
                out_file << data_streams[idx_stream][i];
        }
    }
}

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