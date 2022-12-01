#ifndef __UDP_SERVER__
    #define __UDP_SERVER__

        #include "main_header.h"

        class UDPServer
        {
            public:
               /* Variables */
                int                     sockFD;
                string                  ip;

                SOCK_ADDR_IN            addr;
                SOCK_ADDR_IN            client_addr;
            
               /* Constructors */
                UDPServer               ();
                UDPServer               (string _ip, uint _port = PORT);

               /** Methods **/
               /* Senders */
                void send_Responses     (string resource_name);

               /* Receivers */
                void recv_Requests      ();

               /* Utilities */
                void print_Information  ();
                bool find_Resource      (string resource_name);

            private:
               /* Variables */
                uint                    port;
                uint                    stream;

                int                     bytes_recv;
                int                     bytes_send;

                socklen_t               addr_len;

                char*                   recv_buffer;
                
                string                  server_resources_path;
                string                  server_current_path;
        };
        
#endif // !__UDP_SERVER__
