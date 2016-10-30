#include <sirius.h>

extern int echo_main(int argc, char** argv);
extern int lua_main(int argc, char** argv);

int main(int argc, char** argv){
    lua_main (argc, argv);
    return 0;
}
