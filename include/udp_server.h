#ifndef __UDP_SERVER__
    #define __UDP_SERVER__

        #include "utils.h"

        class UDPServer
        {
            public:
               /* Variables */
                int                 server_sockFD;
                string              server_ip;

                SOCK_ADDR_IN        server_addr;
                SOCK_ADDR_IN        client_addr;
            
               /* Constructors */
                UDPServer           ();
                UDPServer           (string ip, uint port = PORT);

               /** Methods **/
               /* Senders */

               /* Receivers */
                bool recv_Request   ();

               /* Utilities */
                void print_Information();

            private:
               /* Variables */
                uint                server_port;
                socklen_t           server_addr_len = sizeof(struct sockaddr);
                
                string              server_resources_path;
                string              server_current_path;
        };
        
#endif // !__UDP_SERVER__
