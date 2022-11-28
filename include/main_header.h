#ifndef __MAIN_HEADER_H__
#define __MAIN_HEADER_H__

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
#include <thread>

/* Usings */
using std::cout;            using std::cin;   
using std::endl;
using std::string;          using std::ifstream;
using std::ofstream;        using std::vector;
using std::thread;

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
typedef long unsigned int   luint;
typedef vector<string>      RESOURCES;

/* Definitions */
// Sizes
#define MAX_MESSAGE_SIZE    1024
#define MAX_SEGMENT_SIZE    10

#define MIN_MESSAGE_SIZE    0

#define SOCK_ADDR_SIZE      sizeof(sockaddr)
#define REQUEST_SIZE        102

#define NUMBER_STREAMS      9

// Connection
#define PORT                5000

// Commands
#define ALL                 "-all"
#define START               "-start"

// Directories
#define RESOURCES_DIR       "resources"
#define REQUESTS_DIR        "requests"

#endif // !__MAIN_HEADER_H__