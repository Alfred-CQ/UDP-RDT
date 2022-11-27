#ifndef __UDP_CLIENT__
    #define __UDP_CLIENT__

        #include "main_header.h"

        class UDPClient
        {
            public:
               /* Variables */
                int                 client_sockFD;
                SOCK_ADDR_IN        server_addr;
                HOST*               client_host;
            
               /* Constructors and Destructor*/
                UDPClient           (string ip, uint port = PORT);
               ~UDPClient           ();

               /** Methods **/
               /* Senders */
                void send_Request   (string resource_request);
                
               /* Receivers */

               /* Utilities */
                void print_Information();

            private:
               /* Variables */
                uint                client_port;
                
                int                 client_bytes_recv;
                int                 client_bytes_send;

                string              client_send_buffer;
        };
        
#endif // !__UDP_CLIENT__