#ifndef __RESOURCES_H__
#define __RESOURCES_H__

/* Libraries */
// NETWORK - SOCKETS
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

// UNIX
#include <unistd.h>
#include <errno.h>

// C
#include <string.h>

// STL
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

/* Usings */
using std::cout;            using std::cin;   
using std::endl;
using std::string;          using std::ifstream;
using std::ofstream;        using std::vector;

// Namespaces
namespace fs = std::filesystem;

/* Typedefs */
// Connection
typedef struct sockaddr_in  SOCK_ADDR_IN;
typedef struct sockaddr     SOCK_ADDR;
typedef struct in_addr      IN_ADDR;
typedef struct hostent      HOST;

// Program
typedef unsigned int        uint;
typedef vector<string>      FILES;

/* Definitions */
// Sizes
#define MAX_MESSAGE_SIZE    1024
#define MAX_SEGMENT_SIZE    1000

#define MIN_MESSAGE_SIZE    0

#define SOCK_ADDR_SIZE      sizeof(sockaddr)

// Connection
#define PORT                5000

// Commands
#define ALL                 "-all"
#define START               "-start"

// Directories
#define RESOURCES_DIR       "resources"
#define REQUESTS_DIR        "requests"

#endif // !__RESOURCES_H__