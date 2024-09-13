#if !defined(__TRANSLATER_H__)
#define __TRANSLATER_H__

#define WORDSIZE 4

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
    
    void StartStatement(int pos, std::stringstream& ss,  int& function_number);
    void EndStatement(int pos, std::stringstream& ss,  int& function_number);
    void GotoStatement(int pos, std::stringstream& ss,  int& function_number);
    void LoadStatement(int pos, std::stringstream& ss,  int& function_number);
    void StoreStatement(int pos, std::stringstream& ss,  int& function_number);
    void AssignStatement(int pos, std::stringstream& ss,  int& function_number);
    void StackStatement(int pos, std::stringstream& ss,  int& function_number);
    void ReturnStatement(int pos, std::stringstream& ss,  int& function_number);
    void CallStatement(int pos, std::stringstream& ss,  int& function_number);

    bool GetSubString(const std::string& line, std::string &name, const char delimiter);
    inline bool GetLabelName(const std::string& line, std::string &name) {
        return GetSubString(line, name, ':');
    }

    const std::string& mFileName;
    const Option* mOption;
    std::vector<std::string> mContents;
    
    bool mStackFlag;

    std::vector<Function*> mFunctions;
};

#endif //!__TRANSLATER_H__