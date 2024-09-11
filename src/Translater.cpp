#include "Translater.h"

Translater::Translater(std::string filename, const Option* option) 
    :mFileName(filename), mOption(option), mNumLabel(0)
{

}

Translater::~Translater() {}

bool Translater::Initialize() {
    mFile.open(mFileName);
    if(!mFile.is_open())
        return false;

    return true;
}

void Translater::RunLoop() {
    std::string line;
    int depth = 0;

    while(std::getline(mFile, line)) {
        ++depth;
        if(line.find("tcg_gen_") != std::string::npos) {
            std::cout << depth << ": " << line << std::endl;
        }
    }
}