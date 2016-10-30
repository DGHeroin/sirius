#include <net/Inet4Address.h>

#define LOG_TAG "Inet4Address"

// funcs
static struct Inet4AddressContext* Inet4AddressContext_create();
static void Inet4AddressContext_destroy(struct Inet4AddressContext*);
static int Inet4AddressContext_connect(struct Inet4AddressContext*, const char* ip, uint16_t port);
static int Inet4AddressContext_send(struct Inet4AddressContext*, const char* data, size_t lenght);
static int Inet4AddressContext_recv(struct Inet4AddressContext*, char* buffer, size_t lenght);

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

typedef struct Inet4AddressContext{
    SOCKET socket;
    char* ip;
    int port;
}Inet4AddressContext;

static Inet4AddressContext* Inet4AddressContext_create(){
    struct Inet4AddressContext* ctx = NULL;
    ctx = (struct Inet4AddressContext*) calloc(1, sizeof(struct Inet4AddressContext));
    if (ctx != NULL){
        ctx->socket = INVALID_SOCKET;
        ctx->ip     = NULL;
        ctx->port   = 0;
    }
    return ctx;
}


static int Inet4AddressContext_connect(struct Inet4AddressContext* ctx,
                                       const char* ip,
                                       uint16_t port){
    struct addrinfo* result = NULL;
    struct addrinfo* ptr    = NULL;
    struct addrinfo hints;
    char portStr[5];
    WSADATA wsaData;
    int iResult;
    if(ctx->ip != NULL){
        free(ctx->ip);
    }
    ctx->ip   = _strdup (ip);
    ctx->port = port;

    sprintf_s(&portStr[0], 5, "%d", port);

    // init winsock
    iResult = WSAStartup (MAKEWORD(1,2), &wsaData);
    if (iResult != 0){
        log_error("WASStartup failed with error:%d", iResult);
        return -1;
    }
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo (ip, portStr, &hints, &result);
    if (iResult != 0){
        log_error("getaddrinfo  failed with error:%d", iResult);
        WSACleanup ();
        return -1;
    }
    for(ptr = result; ptr != NULL; ptr = ptr->ai_next){
        // create sock for connect to server
        ctx->socket = ::socket(ptr->ai_family,
                        ptr->ai_socktype,
                        ptr->ai_protocol);
        if (ctx->socket == INVALID_SOCKET){
            log_error("getaddrinfo  failed with error:%ld", WSAGetLastError());
            WSACleanup ();
            return -1;
        }
        // connect to server
        iResult = connect (ctx->socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR){
            closesocket (ctx->socket);
            ctx->socket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo (result);
    if (ctx->socket == INVALID_SOCKET){
        log_error("Unable to connect to server");
        WSACleanup ();
        return -1;
    }
    return 0;
}

void Inet4AddressContext_destroy(struct Inet4AddressContext*ctx){
    shutdown(ctx->socket, SD_SEND);
    closesocket(ctx->socket);
    free(ctx->ip);
    ctx->ip   = NULL;
    ctx->port = 0;
    WSACleanup();

    free(ctx);
}

int Inet4AddressContext_send (Inet4AddressContext *ctx, const char *data, size_t lenght){
    int iResult;
    iResult = ::send(ctx->socket, data, (int)lenght, 0);
    if (iResult == SOCKET_ERROR) {
        log_error("send data failed. error:%s", WSAGetLastError());
        return -1;
    }
    return iResult;
}

static int Inet4AddressContext_recv(struct Inet4AddressContext* ctx, char* buffer, size_t lenght){
    int iResult;
    iResult = ::recv(ctx->socket, buffer, (int)lenght, 0);
    return iResult;
}


#else
#endif

Inet4Address::Inet4Address() :
    mContext(NULL)
{
}

Inet4Address::~Inet4Address (){
    if(mContext!=NULL){
        Inet4AddressContext_destroy (mContext);
    }
    mContext = NULL;
}

int Inet4Address::connect (const char* ip, uint16_t port){
    mContext = Inet4AddressContext_create();
    if(mContext == NULL){
        log_error("create context errror.");
        return -1;
    }
    return Inet4AddressContext_connect (mContext, ip, port);
}

int Inet4Address::send (const char *data, size_t lenght){
    return Inet4AddressContext_send(mContext, data, lenght);
}

int Inet4Address::recv (char *buffer, size_t lenght){
    return Inet4AddressContext_recv (mContext, buffer, lenght);
}

