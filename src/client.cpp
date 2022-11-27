#include "../include/udp_client.h"

int main()
{
    UDPClient* myClient     { new UDPClient("127.0.0.1") };
    string     command      { "Y" };
    FILES      file_Names;
    
    myClient->print_Information();

    while (command != "N")
    {
        cout << "*****************************************************"
             << "\n[ -all for all resources ] [ -start to start receiving]\n"
             << "           Type the resources you need🔎\n";

        while (command != ALL && command != START)
        {
            string file_Name;

            cout << "  > ";
            cin >> file_Name;

            file_Names.push_back(file_Name);

            command = file_Name;
        }

        for (size_t i = 0; i < file_Names.size(); ++i)
            myClient->send_Request(file_Names[i]);

        cout << "Would like to retry? (Y/N)" << endl;
        cin >> command;

        file_Names.clear();
    }

    cout << " 🏁 FINISH UDP CLIENT PROGRAM 🏁\n";

    return 0;
}