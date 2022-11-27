#include "../include/udp_server.h"

int main()
{
    UDPServer* myServer { new UDPServer("127.0.0.1") };
    bool       stop     { false };
 
    myServer->print_Information();

    cout << "   ⏳ UDPServer waiting for data transmission ⏳\n";

    while (!stop)
    {
        sleep(5);
    }

    cout << " 🏁 FINISH UDP SERVER PROGRAM 🏁\n";

    return 0;
}