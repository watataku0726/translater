#if !defined(__TRANSLATER_H__)
#define __TRANSLATER_H__

#define WORDSIZE_SHIFT 2
#define WORDSIZE (1 << WORDSIZE_SHIFT)
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
    enum HelperFlag {
        LOAD_ARRAY = 1 << 0,
        STORE_ARRAY = 1 << 1,
        LOAD_FRAME_ARRAY = 1 << 2,
        STORE_FRAME_ARRAY = 1 << 3,
        LOAD_ARRAY_CONST = 1 << 4,
        LOGICAL_AND = 1 << 5,
        LOGICAL_OR = 1 << 6,
        LOGICAL_ANDi= 1 << 7,
        LOGICAL_ORi= 1 << 8,
    };

    Translater();
    ~Translater();

    bool Initialize(int argc, char** argv);
    void RunLoop();

    int IsFunction(const std::string& name) const;
    int IsGlobalRegister(const std::string& name) const;
    void AddGlobalRegister(const std::string& name);
    inline void UseHelper(HelperFlag flag) { mHelperFlag |= flag; }
private:
    enum class State {
        InFunction = 0,
        IntoFunction,
        OutofFunction,
        InObject,
        InConstobject,
    };    


    struct Register {
        std::string globalRegister;
        std::string indexglobalRegister;
        int frameIdx;
        enum class AssignState : char {
            Unknown = -1,
            None = 0,
            Global = 1,
            Frame = 2,
            Const = 4,
        } assignState;
        int arraySize;
        Register() 
            :globalRegister(""), indexglobalRegister(""), frameIdx(0)
            ,assignState(AssignState::None), arraySize(0) {};
    } mAssignedRegisters[MAX_GLOBAL_ASSIGNED_REIGSTERS];    

    std::map<std::string, std::vector<unsigned>*> mConstValues;
    std::map<std::string, int> mGlobalRegisters;
    std::map<std::string, int> mFunctionTable;
    std::vector<std::string> mContents;
    std::vector<Function*> mFunctions;
    std::string mOutputFile;
    Option* mOption;
    int mN;
    int mHelperFlag;
    bool mStackFlag;

private:

    bool Analyze(std::stringstream& ss);
    bool Analyze_in_InFunction(const std::string& line, State& state, int& pos);
    bool Analyze_in_IntoFunction(const std::string& line, State& state, int& pos);
    bool Analyze_in_OutofFunction(const std::string& line, State& state);
    bool Analyze_in_InObject(const std::string& line, State& state);
    bool Analyze_in_InConstobject(const std::string& line, State& state);
    
    void Prologue(std::stringstream& ss);
    void Epilogue(std::stringstream& ss);
    void GenerateHelpers(std::stringstream& ss);

    void NormalStatement(int pos, std::stringstream& ss,  int& function_number);

    void StartStatement(int pos, std::stringstream& ss,  int& function_number);
    void EndStatement(int pos, std::stringstream& ss,  std::stringstream& tmp_ss,  int& function_number);
    void GotoStatement(int pos, std::stringstream& ss,  int& function_number);
    void LoadStatement(int pos, std::stringstream& ss,  int& function_number);
    void StoreStatement(int pos, std::stringstream& ss,  int& function_number);
    void AssignStatement(int pos, std::stringstream& ss,  int& function_number);
    void StackStatement(int pos, std::stringstream& ss,  int& function_number);
    void ReturnStatement(int pos, std::stringstream& ss,  int& function_number);
    void CallStatement(int pos, std::stringstream& ss,  int& function_number);
    void FrameStatement(int pos ,std::stringstream& ss, int& function_number);

    bool GetSubString(const std::string& line, std::string &name, const char delimiter);
    inline bool GetLabelName(const std::string& line, std::string &name) {
        return GetSubString(line, name, ':');
    }

    int GetRegNumber(const std::string& reg, int function_number);
    void FreeAssign(int reg_number);
    bool IsAssignedGlobal(int reg_number);
    bool IsAssignedFrame(int reg_number);
    bool IsAssignedConst(int reg_number);
    Register::AssignState GetAssignState(int reg_number);
    void AssignGlobal(int reg_number, const std::string& global_register_name, const std::string& index_reg_name = "");
    void AssignFrame(int reg_number, int index, int size, const std::string& index_reg_name = "");
    void AssignConst(int reg_number, const std::string& const_register_name, const std::string& index_reg_name = "");

    void Help();
    void Version();
};

#endif //!__TRANSLATER_H__