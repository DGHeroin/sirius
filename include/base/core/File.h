#ifndef _file_h_
#define _file_h_

#include <base/macros.h>
#include <string>

bool file_exist(const char* fullpath);
std::string file_subfix(const char *fullpath);
std::string file_get_name(const char* fullpath);
int file_put_content(const char* fullpath, std::string content);

#endif
