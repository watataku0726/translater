#include <fstream>
#include <iostream>
#include <string>

class Option;

class Translater {
public:
    Translater(std::string filename, const Option* option);
    ~Translater();

    bool Initialize();
    void RunLoop();

private:
    std::string mFileName;
    std::ifstream mFile;
    const Option* mOption;

    int mNumLabel;

};