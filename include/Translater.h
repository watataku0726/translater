#if !defined(__TRANSLATER_H__)
#define __TRANSLATER_H__

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Option;
class Function;

class Translater {
public:
    Translater(const std::string& filename, const Option* option);
    ~Translater();

    bool Initialize();
    void RunLoop();

private:
    enum class State {
        InFunction = 0,
        IntoFunction,
        OutofFunction,
    }; 
    bool Analyze(std::stringstream& ss);
    bool Analyze_in_InFunction(const std::string& line, State& state, int& pos);
    bool Analyze_in_IntoFunction(const std::string& line, State& state, int& pos);
    bool Analyze_in_OutofFunction(const std::string& line, State& state);
    
    


    bool GetLabelName(const std::string& line, std::string &name, const char delimiter = ':');

    const std::string& mFileName;
    const Option* mOption;
    std::vector<std::string> mContents;
    

    std::vector<Function*> mFunctions;
};

#endif //!__TRANSLATER_H__