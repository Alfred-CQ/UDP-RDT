#ifndef __UDP_CLIENT__
    #define __UDP_CLIENT__

        #include "main_header.h"

        class UDPClient
        {
            public:
               /* Variables */
                int                     sockFD;
                SOCK_ADDR_IN            server_addr;
                HOST*                   host;
            
               /* Constructors and Destructor*/
                UDPClient               (string _ip, uint _port = PORT);
               ~UDPClient               ();

               /** Methods **/
               /* Senders */
                void send_Request       (string resource_request);
                
               /* Receivers */
                void recv_Responses     ();

               /* Utilities */
                void print_Information  ();

            private:
               /* Variables */
                uint                    port;
                
                int                     bytes_recv;
                int                     bytes_send;

                socklen_t               addr_len;

                string                  send_buffer;

                char*                   recv_buffer;
        };
        
#endif // !__UDP_CLIENT__