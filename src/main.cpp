#include <iostream>
#include "Translater.h"
#include "Option.h"

int main(int argc, char **argv) {

    Translater translater;
    if(!translater.Initialize(argc, argv))
        return -1;
    translater.RunLoop();
    
    return 0;
}
