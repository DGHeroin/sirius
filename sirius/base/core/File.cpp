#include <base/core/File.h>

#define LOG_TAG "core file"

#ifdef _WIN32
#include <Windows.h>
#include <Shlwapi.h>

static bool call_file_exist (const char *fullpath){
    DWORD dwAttrib = GetFileAttributes(fullpath);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
             !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}
#else

bool call_file_exist (const char *fullpath){
    log_assert(!"not impl");
}

#endif

/**
 * @brief file_exist
 * @param fullpath
 * @return
 */
bool file_exist (const char *fullpath){
    return call_file_exist (fullpath);
}

/**
 * @brief file_subfix
 * @param fullpath
 * @return
 */
std::string file_subfix(const char* fullpath){
    char* ptr = std::strrchr((char*)fullpath, '.');
    if(ptr){
        return std::string(ptr);
    }
    return "";
}
