#ifndef _Inet4Address_h_
#define _Inet4Address_h_

#include <base/macros.h>
struct Inet4AddressContext;
class Inet4Address{
public:
    Inet4Address();
    ~Inet4Address();
    int connect(const char *ip, uint16_t port);
    int send(const char* data, size_t lenght);
    int recv(char* buffer, size_t lenght);
private:
    Inet4AddressContext* mContext;
};

#endif //_Inet4Address_h_
