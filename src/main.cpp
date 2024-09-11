#include <iostream>
#include "Translater.h"

int main(int argc, char **argv) {
    std::string filename(argv[1]);
    Translater translater(filename, nullptr);
    if(!translater.Initialize())
        return -1;
    translater.RunLoop();
    return 0;
}