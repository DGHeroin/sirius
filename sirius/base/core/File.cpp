#include <base/core/File.h>
#include <fstream>
#include <algorithm>

#define LOG_TAG "core file"
using namespace std;
/**
 * @brief call_write_file
 * @param fullpath
 * @param content
 * @return
 */
static int call_write_file(const char *fullpath, std::string content){
    std::ofstream ofile (fullpath, ios::out | ios::binary);
    if(ofile.is_open ()){
        ofile << content;
    }
    ofile.close ();
    return 0;
}

#ifdef _WIN32
#include <Windows.h>
#include <Shlwapi.h>

static bool call_file_exist (const char *fullpath){
    DWORD dwAttrib = GetFileAttributes(fullpath);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
             !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));

}

static bool call_folder_exist (const char *fullpath){
    DWORD dwAttrib = GetFileAttributesA(fullpath);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
             (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));

}

static int call_file_put_content(const char *fullpath, std::string content){
    std::string fullpath_str(fullpath);
    std::string filename = file_get_name (fullpath);
    std::string path;

    if(filename != fullpath){
        // fullpath is a filename only.
        path = fullpath_str.substr (0, fullpath_str.size () - filename.size ());
        //std::replace(path.begin (), path.end (), '/', '\\');
    }

    if(path != "" && call_folder_exist(path.c_str ()) == false){
        // mkdir
        size_t pos = 0;
        do
        {
            pos = path.find_first_of("/", pos + 1);
            CreateDirectory(path.substr(0, pos).c_str(), NULL);
            if(ERROR_ALREADY_EXISTS == GetLastError ()){
                log_error("create folder:%s failed. %d", path.c_str (), GetLastError () );
                return -1;
            }
        } while (pos != std::string::npos);
    }

    return call_write_file(fullpath, content);
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

std::string file_get_name(const char *fullpath){
    char* ptr = std::strrchr((char*)fullpath, '/');
    if(ptr){
        return std::string(ptr);
    }
    return std::string(fullpath);
}

/**
 * @brief file_put_content
 * @param fullpath
 * @param content
 * @return
 */
int file_put_content (const char *fullpath, std::string content){
    return call_file_put_content(fullpath, content);
}
