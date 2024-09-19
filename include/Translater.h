#if !defined(__TRANSLATER_H__)
#define __TRANSLATER_H__

#define WORDSIZE 4
#define NUMBER_OF_TMP_REGISTERS 6
#define NUMBER_OF_A_REGISTERS 8 
#define NUMBER_OF_R_REGISTERS 1
#define MAX_GLOBAL_ASSIGNED_REIGSTERS NUMBER_OF_A_REGISTERS + NUMBER_OF_R_REGISTERS + NUMBER_OF_TMP_REGISTERS

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

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
        InObject,
    }; 
    bool Analyze(std::stringstream& ss);
    bool Analyze_in_InFunction(const std::string& line, State& state, int& pos);
    bool Analyze_in_IntoFunction(const std::string& line, State& state, int& pos);
    bool Analyze_in_OutofFunction(const std::string& line, State& state);
    bool Analyze_in_InObject(const std::string& line, State& state);
    
    void NormalStatement(int pos, std::stringstream& ss,  int& function_number);

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

    int GetRegNumber(const std::string& reg);
    void FreeAssign(int reg_number);
    bool IsAssignedGlobal(int reg_number);
    void AssignGlobal(int reg_number, const std::string& global_register_name, const std::string& index_reg_name = "");

    std::map<std::string, bool> mGlobalRegisters;

    struct Register {
        std::string globalRegister;
        std::string indexglobalRegister;
        bool isAssigned;
        bool isArray;
        Register() 
            :globalRegister(""), indexglobalRegister("")
            ,isAssigned(false), isArray(false) {};
    } mGlobalAssignedRegisters[MAX_GLOBAL_ASSIGNED_REIGSTERS];
};

#endif //!__TRANSLATER_H__