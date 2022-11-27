#ifndef __UDP_SERVER__
    #define __UDP_SERVER__

        #include "main_header.h"

        class UDPServer
        {
            public:
               /* Variables */
                int                     server_sockFD;
                string                  server_ip;

                SOCK_ADDR_IN            server_addr;
                SOCK_ADDR_IN            client_addr;
            
               /* Constructors */
                UDPServer               ();
                UDPServer               (string ip, uint port = PORT);

               /** Methods **/
               /* Senders */

               /* Receivers */
                void recv_Requests      ();

               /* Utilities */
                void print_Information  ();
                bool query_Available    (string& resource_name);

            private:
               /* Variables */
                uint                    server_port;
                int                     server_bytes_recv;

                socklen_t               server_addr_len = sizeof(struct sockaddr);

                char*                   server_recv_buffer;
                
                string                  server_resources_path;
                string                  server_current_path;
        };
        
#endif // !__UDP_SERVER__
