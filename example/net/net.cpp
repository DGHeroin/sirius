#include <base/log/log.h>
#include <net/net.h>
#include <sstream>
#include <base/core/File.h>

#define LOG_TAG "example net"
int net_main(int argc, char** argv){
    using namespace std;
    string ip = "14.17.32.211";
    string get_http = "GET / HTTP/1.1\r\nHost: www.qq.com\r\nConnection: close\r\n\r\n";

    Inet4Address inet4;
    int retval = inet4.connect (ip.c_str (), 80);
    log_info("connect ret:%d", retval);
    if(retval == 0){
        retval = inet4.send (get_http.c_str(), get_http.size ());
        log_info("send ret:%d", retval);
        if(retval != -1){
            char buffer[1024];
            stringstream ss;
            do{
                retval = inet4.recv (buffer, 1024);
                if(retval == 0 || retval == -1){
                    log_info("retval ret:%d", retval);
                    break;
                }
                string tmp(buffer, retval);
                ss << tmp;
            }while(1);
            string response = ss.str ();
            const char* ptr = strstr(response.c_str (), "\r\n\r\n");
            size_t offset = ptr - response.c_str () - 4;
            string header = response.substr (0, offset + 4);
            string html(ptr + 4);

            file_put_content ("test/net/head.html", header.c_str ());
            file_put_content ("test/net/qq.html", html.c_str ());
            file_put_content ("test/net/all.html", response.c_str ());
        }
    }

    return 0;
}

