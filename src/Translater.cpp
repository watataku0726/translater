#include "Translater.h"
#include "Option.h"
#include "Function.h"

#include "cassert"


/*======================================*/
/*             PUBLIC                   */
/*======================================*/


Translater::Translater() 
    :mOption(nullptr), mStackFlag(false), mHelperFlag(0), mOutputFile(""), mN(0), mHasInit(false)
{   
    mFunctions.clear();
    mContents.clear();
    mGlobalRegisters.clear();
    mFunctionTable.clear();
    mConstValues.clear();
}

Translater::~Translater() {
    for(Function* f : mFunctions)
        delete f;
    mFunctions.clear();
    for(auto v : mConstValues)
        delete v.second;
    mConstValues.clear();
    delete mOption;
}

bool Translater::Initialize(int argc, char** argv) {
    enum InitializeState {
        NORMAL,
        OPTION,
        OUTPUT,
    } state = InitializeState::NORMAL;
    char *asmfilename = nullptr;
    char *optionfilename = nullptr;
    for(++argv; argv[0]; ++argv) {
        switch(state) {
            case InitializeState::NORMAL:
                if((*argv)[0] != '-')
                    asmfilename = *argv;
                else if((*argv)[1] != '-') {
                    if((*argv)[1] != 'o' || (*argv)[2] != '\0') {
                        std::cerr << "Unknown Argument : " << *argv << std::endl;
                        return false;
                    }
                    state = InitializeState::OUTPUT;
                } else {
                    std::string str(*argv);
                    if(str == "--output") 
                        state = InitializeState::OUTPUT;
                    else if(str == "--option")
                        state = InitializeState::OPTION;
                    else if(str == "--help") {
                        Help();
                        return false;
                    }
                    else if(str == "--version") {
                        Version();
                        return false;
                    }
                    else {
                        std::cerr << "Unknown Argument : " << *argv << std::endl;
                        return false;
                    }
                }
                break;

            case InitializeState::OPTION:
                if((*argv)[0] == '-') {
                    std::cerr << "missig filename after \'" <<  *(argv - 1) << "\'" << std::endl;
                    return false;
                } else {
                    optionfilename = *argv;
                    state = InitializeState::NORMAL;
                }
                break;

            case InitializeState::OUTPUT:
                if((*argv)[0] == '-') {
                    std::cerr << "missig filename after \'" <<  *(argv - 1) << "\'" << std::endl;
                    return false;
                } else {
                    mOutputFile = std::string(*argv);
                    state = InitializeState::NORMAL;
                }
                break;

            default:
                return false;
                break;
        }
    }

    if(state != InitializeState::NORMAL) {
        std::cerr << "missig filename after \'" <<  *(argv - 1) << "\'" << std::endl;
        return false;
    }

    if(!asmfilename) {
        std::cerr << "translater: fatal error: no input file" << std::endl;
        return false;
    }
    std::ifstream file(asmfilename);
    if(file.fail()){
        std::cerr << "Failed to open file: " << asmfilename << std::endl;
        return false;
    }
    std::stringstream ss;
    ss << file.rdbuf();
    if(!Analyze(ss)) {
        std::cerr << "Unknonw Format File: "  << asmfilename << std::endl;
        return false;
    }
    
    if(!optionfilename) {
        std::cerr << "translater: fatal error: no option file" << std::endl;
        return false;
    }

    mOption = new Option(this);
    bool ret = mOption->compile(optionfilename);
    if(!ret) {
        std::cerr << "option error" << std::endl;
        return false;
    }

    if(mOutputFile == "") {
        std::string str = mOption->GetProjectName();
        if(str == "")
            mOutputFile = "trans_.c.inc";
        else
            mOutputFile = "trans_" + str + ".c.inc";
    }

    return true;
}

void Translater::RunLoop() {
#if(0)
    int i = 0;
    for( std::string str : mContents) {
        //if(str[0] == '?')
            std::cout << i++ << " : " << str << std::endl;
    }

    for(Function *f : mFunctions) {
        std::cout << f->GetStart() << " " << f->GetEnd() << " " << f->GetNumArgs() << " "  << f->GetNumLabels() << " " << f->GetMyNumber() << std::endl;
    }

    for(auto iter = mGlobalRegisters.begin(); iter != mGlobalRegisters.end(); ++iter) {
        std::cout << iter->first << " " << iter->second << std::endl;
    }

    for(auto iter = mFunctionTable.begin(); iter != mFunctionTable.end(); ++iter) {
        std::cout << iter->first << " " << iter->second << std::endl;
    }
/*
    for(auto iter = mConstValues.begin(); iter != mConstValues.end(); ++iter) {
        std::cout << iter->first << " " << iter->second->size() <<  std::endl;
        for(unsigned i : *iter->second) 
            std::cout << '\n' << i;
    }
*/
#else
    std::stringstream ss, tmpss;

    std::stringstream helperss;
    GenerateNewRegisters(helperss);

    Prologue(ss);

    int pos = 0, function_number = 0;
    bool stack_flag = false;
    for(std::string& line : mContents) {
        if(line[0] != '?' && line[0] != '!') {
            tmpss << "\t" << line << "\n";
            ++pos;
            line.clear();
            continue;
        } else if(line[0] == '!') {
            NormalStatement(pos, tmpss, function_number);
            ++pos;
            line.clear();
            continue;
        }
        std::string opcode;
        GetSubString(line.substr(1), opcode, '\t');
        
        if(opcode == "goto")
            GotoStatement(pos, tmpss, function_number);
        else if(opcode == "ld")
            LoadStatement(pos, tmpss, function_number);
        else if(opcode == "st")
            StoreStatement(pos, tmpss, function_number);
        else if(opcode == "assign")
            AssignStatement(pos, tmpss, function_number);
        else if(opcode == "stki")
            StackStatement(pos, tmpss, function_number);
        else if(opcode == "start")
            StartStatement(pos, ss, function_number);
        else if(opcode == "end")
            EndStatement(pos, ss, tmpss, function_number);
        else if(opcode == "frmi")
            FrameStatement(pos, tmpss, function_number);
        else if(opcode == "ret")
            ReturnStatement(pos, tmpss, function_number);
        else if(opcode == "call")
            CallStatement(pos, tmpss, function_number);
        ++pos;
        line.clear();
    }
    mContents.clear();

    Epilogue(ss);

    GenerateHelpers(helperss);

    std::ofstream file(mOutputFile);

    file    << "/*=========================================================================================*/\n"
            << "/*                          This file was generated by \"translater\".                       */\n"
            << "/*=========================================================================================*/\n\n"
            << "/*=========================================================================================*/\n"
            << "/*\t1. Install \"" << mOutputFile <<"\" in target/riscv/translate.c  \n";
    if(mHasInit) {
        file    << "\t2. The function void riscv_translate_init(void) in target/riscv/translate.c calls the function \"riscv_" 
                << mOption->GetProjectName() << "_translate_init\".\n"
                << "\t3. Add the following two statements to struct CPUArchState in target/riscv/cpu.h.\n"
                << "\t\t#define NEW_REGISTERS\n"
                << "\t\t#include \"insn_trans/" << mOutputFile << "\"\n";
                  
    }
    file << "/ =========================================================================================*/\n\n"; 

    file << helperss.rdbuf() << ss.rdbuf();

#endif
    
}

/*======================================*/
/*             Helpers                  */
/*======================================*/

bool Translater::GetSubString(const std::string& line, std::string &name, const char delimiter) {
    name.clear();
    for(size_t i = 0; i <= line.size(); ++i) {
        if(line[i] == delimiter) {
            return true;
        } 
        name += line[i];
    }
    name.clear();
    return false;
}

int Translater::GetRegNumber(const std::string& reg, int function_number) {
    int idx = -1;
    if(reg[0] == 't' && reg[1] == 'm' && reg[2] == 'p') {
        idx = atol(reg.c_str() + 3) - 1;
        mFunctions[function_number]->SetNumTmp(idx + 1);
    } else if(reg[0] == 'a') {
        idx = atol(reg.c_str() + 1) + NUMBER_OF_TMP_REGISTERS;
        mFunctions[function_number]->SetNumA(idx - NUMBER_OF_TMP_REGISTERS + 1);
    } else if(reg[0] == 'r') {
        idx = MAX_GLOBAL_ASSIGNED_REIGSTERS - 1;
    }

    return idx;
}

void Translater::FreeAssign(int reg_number) {
    if(reg_number >= 0 && reg_number < MAX_GLOBAL_ASSIGNED_REIGSTERS) {
        mAssignedRegisters[reg_number].assignState = Register::AssignState::None;
    }
}

bool Translater::IsAssignedGlobal(int reg_number) {
    bool ret = false;
    if(reg_number >= 0 && reg_number < MAX_GLOBAL_ASSIGNED_REIGSTERS) {
        ret = (mAssignedRegisters[reg_number].assignState == Register::AssignState::Global);
    }
    return ret;
}

bool Translater::IsAssignedFrame(int reg_number) {
    bool ret = false;
    if(reg_number >= 0 && reg_number < MAX_GLOBAL_ASSIGNED_REIGSTERS) {
        ret = (mAssignedRegisters[reg_number].assignState == Register::AssignState::Frame);
    }
    return ret;
}

bool Translater::IsAssignedConst(int reg_number) {
    bool ret = false;
    if(reg_number >= 0 && reg_number < MAX_GLOBAL_ASSIGNED_REIGSTERS) {
        ret = (mAssignedRegisters[reg_number].assignState == Register::AssignState::Const);
    }
    return ret;
}

Translater::Register::AssignState Translater::GetAssignState(int reg_number) {
    Translater::Register::AssignState ret = Translater::Register::AssignState::Unknown;
    if(reg_number >= 0 && reg_number < MAX_GLOBAL_ASSIGNED_REIGSTERS) {
        ret = mAssignedRegisters[reg_number].assignState; 
    }
    return ret;
}

void Translater::AssignGlobal(int reg_number, const std::string& global_register_name, const std::string& index_reg_name) {
    if(reg_number >= 0 && reg_number < MAX_GLOBAL_ASSIGNED_REIGSTERS) {
        auto iter = mGlobalRegisters.find(global_register_name);
        if(iter != mGlobalRegisters.end()) {
            mAssignedRegisters[reg_number].assignState = Register::AssignState::Global;
            mAssignedRegisters[reg_number].globalRegister = global_register_name;
            mAssignedRegisters[reg_number].indexglobalRegister = index_reg_name; 
            mAssignedRegisters[reg_number].arraySize = iter->second;
        }
    }
}

void Translater::AssignFrame(int reg_number, int index, int size, const std::string& index_reg_name) {
    if(reg_number >= 0 && reg_number < MAX_GLOBAL_ASSIGNED_REIGSTERS) {
        mAssignedRegisters[reg_number].assignState = Register::AssignState::Frame;
        mAssignedRegisters[reg_number].arraySize = size;
        mAssignedRegisters[reg_number].frameIdx = index;
        mAssignedRegisters[reg_number].indexglobalRegister = index_reg_name;
    }
}

void Translater::AssignConst(int reg_number, const std::string& const_register_name, const std::string& index_reg_name) {
    if(reg_number >= 0 && reg_number < MAX_GLOBAL_ASSIGNED_REIGSTERS) {
        auto iter = mGlobalRegisters.find(const_register_name);
        if(iter != mGlobalRegisters.end()) {
            mAssignedRegisters[reg_number].assignState = Register::AssignState::Const;
            mAssignedRegisters[reg_number].globalRegister = const_register_name;
            mAssignedRegisters[reg_number].indexglobalRegister = index_reg_name;
            mAssignedRegisters[reg_number].arraySize = iter->second;
        }
    }
}

int Translater::IsFunction(const std::string& name) const {
    auto iter = mFunctionTable.find(name);
    if(iter != mFunctionTable.end()) 
        return iter->second;
    return -1;
}

int Translater::IsGlobalRegister(const std::string& name) const {
    auto iter = mGlobalRegisters.find(name);
    if(iter != mGlobalRegisters.end())
        return iter->second;
    return -1;
}

void Translater::AddGlobalRegister(const std::string& name) {
    auto iter = mGlobalRegisters.find(name);
    if(iter == mGlobalRegisters.end())
        mGlobalRegisters.emplace(name, 1);
    else
        std::cerr << name << " already exists." << std::endl;
}

/*======================================*/
/*             ANALYZE                  */
/*======================================*/

bool Translater::Analyze(std::stringstream& ss) {
    std::string line;
    int pos = 0;
    State state = State::OutofFunction;
    if(std::getline(ss, line)) {
        if(line != "\t.text")
            return false;
    }
    

    while(std::getline(ss, line)) {
        if(line == "" || line[0] == '#')
            continue;
        
        switch(state) {
            case State::InFunction:
                if(!Analyze_in_InFunction(line, state, pos))
                    return false;
                break;
            case State::IntoFunction:
                if(!Analyze_in_IntoFunction(line, state, pos))
                    return false;
                break;
            case State::OutofFunction: 
                if(!Analyze_in_OutofFunction(line, state))
                    return false;
                break;
            case State::InObject:
                if(!Analyze_in_InObject(line, state))
                    return false;
                break;
            case State::InConstobject:
                if(!Analyze_in_InConstobject(line, state))
                    return false;
                break;

            default:
                std::cerr << "Unknown State in Analyze" << std::endl;
                return false;
        }
        
    }   

    return true;
}

bool Translater::Analyze_in_InFunction(const std::string& line, State& state, int& pos) {
    if(state != State::InFunction) {
        std::cerr << "Analyze_in_InFunction is called unexpected place!!" << std::endl;
        return false;
    }

    if(line.substr(0, 6) == "label_") {
        std::string name;
        if(!GetLabelName(line, name)){
            std::cerr << "Unknown Label Format: "  << line << std::endl;
            return false;
        }
        mFunctions.back()->AddLabel(pos, name);
        mContents.push_back("\n\tgen_set_label(" + name + ");");
        ++pos;
        return true;    
    } else if (line.substr(0,9) == "$func_end") {
        mContents.push_back("?end\t" + mFunctions.back()->GetName());
        mFunctions.back()->SetEnd(pos);
        state = State::OutofFunction;
        ++pos;
        return true;
    }

    int i = 0;
    while(line[i] == '\t' || line[i] == ' ') { ++i; }
    if(line[i] != '#') {
        mContents.push_back(line.substr(i));
        ++pos;
    }
    return true;
}

bool Translater::Analyze_in_IntoFunction(const std::string& line, State& state, int& pos) {
    if(state != State::IntoFunction) {
        std::cerr << "Analyze_in_IntoFunction is called unexpected place!!" << std::endl;
        return false;
    }
    static int numFunctions = 0;
    
    std::string functionLabel;
    if(!GetLabelName(line, functionLabel))
        return true;
    
    Function* f = new Function(pos, functionLabel);
    if(f->GetName()  == "") {
        std::cerr << "Unknown Function Format: " << functionLabel << std::endl;
        delete f;
        return false; 
    }
    f->SetMyNumber(numFunctions);
    ++numFunctions;
    mFunctions.push_back(f);
    mFunctionTable.emplace(f->GetName(), f->GetNumArgs());
    std::stringstream tmp;
    tmp << mFunctions.back()->GetMyNumber();
    mContents.push_back("?start\t" + tmp.str());
    ++pos;
    state = State::InFunction;
    return true;
}

bool Translater::Analyze_in_OutofFunction(const std::string& line, State& state) {
    if(state != State::OutofFunction) {
        std::cerr << "Analyze_in_OutofFunction is called unexpected place!!" << std::endl;
        return false;
    }

    if(line.substr(0,6) == "\t.type") {
        if(line.find("@function") != std::string::npos) {
            state = State::IntoFunction;
        } else if(line.find("@object") != std::string::npos) {
            state = State::InObject;
        }
    }

    return true;
}

bool Translater::Analyze_in_InObject(const std::string& line, State& state) {
    static int p2align = 2;
    std::string opcode;
    int offset = 1;
    GetSubString(line.c_str() + 1, opcode, '\t');
    if(opcode == ".section") {
        std::string str;
        offset += opcode.size() + 1;
        GetSubString(line.c_str() + offset, str, ',');
        if(line.substr(offset, 7) == ".rodata")
            state = State::InConstobject;
    } else if(opcode == ".p2align") {
        //std::string imm;
        //offset += opcode.size() + 1;
        //GetSubString(line.c_str() + offset, imm, '\0');
        //p2align = atol(imm.c_str());
    } else if(opcode == ".size") {
        std::string name, imm;
        offset += opcode.size() + 1;
        GetSubString(line.c_str() + offset, name, ',');
        offset += name.size() + 2;
        GetSubString(line.c_str() + offset, imm, '\0');
        int size = atol(imm.c_str()) >> p2align;
        mGlobalRegisters.emplace(name, size);
        state == State::OutofFunction;
        p2align = 2;
    }

    return true;
}

bool Translater::Analyze_in_InConstobject(const std::string& line, State& state) {
    static int p2align = 2;
    std::string opcode;
    int offset = 1;
    static std::vector<unsigned>* arr = nullptr;
    if(GetSubString(line.c_str() + 1, opcode, '\t')) {
        if(opcode == ".p2align") {
            std::string imm;
            offset += opcode.size() + 1;
            GetSubString(line.c_str() + offset, imm, '\0');
            p2align = atol(imm.c_str());
        } else if(opcode == ".4bytes") {
            if(arr) {
                offset += opcode.size() + 1;
                const char *str = line.c_str() + offset;
                std::stringstream ss;
                while('0' <= *str && *str <= '9') {
                    ss << *(str++);
                }
                unsigned val = 0;
                ss >> val;
                arr->push_back(val);
            }
        } else if(opcode == ".size") {
            state == State::OutofFunction;
            p2align = 2;
        } 
    } else if(GetSubString(line, opcode, ':')) {
        if(opcode.size() > 4 && opcode[0] == '_' && opcode[1] == 'Z' && opcode[2] == 'L') {
            int idx = 3;
            int len = 0;
            while('0' <= opcode[idx] && opcode[idx] <= '9') {
                ++idx;
            }
            std::istringstream ss = std::istringstream(opcode.substr(3, idx - 3));
            ss >> len;
            arr = new std::vector<unsigned>;
            arr->clear();
            mConstValues.emplace(opcode.substr(idx, len), arr);
        }
    }
    return true;
}


/*======================================*/
/*             STATEMENTS               */
/*======================================*/

void Translater::NormalStatement(int pos, std::stringstream& ss,  int& function_number) {
    std::string opcode, rd;
    const std::string& line = mContents[pos];
    int offset = 1;
    GetSubString(line.c_str() + offset, opcode, '\t');
    offset += opcode.size() + 1;
    GetSubString(line.c_str() + offset, rd, ',');
    int rd_number = GetRegNumber(rd, function_number);
    if(opcode == "add") {
        std::string rs1, rs2;
        offset += rd.size() + 2;
        GetSubString(line.c_str() + offset, rs1, ',');
        offset += rs1.size() + 2;
        GetSubString(line.c_str() + offset, rs2, '.');

        int rs1_number = GetRegNumber(rs1, function_number);
        int rs2_number = GetRegNumber(rs2, function_number);
        Register::AssignState rs1State = GetAssignState(rs1_number);
        Register::AssignState rs2State = GetAssignState(rs2_number);
        if(rs2State == Register::AssignState::None) {
            const Register& reg = mAssignedRegisters[rs1_number];
            switch(rs1State) {
                case Register::AssignState::Global:
                    AssignGlobal(rd_number, reg.globalRegister, rs2);
                    ss << "\t/*Assign " << reg.globalRegister << "[" << rs2 << "]" << " to " << rd << ".*/\n";
                    break;

                case Register::AssignState::Frame:
                    AssignFrame(rd_number, reg.frameIdx, mFunctions[function_number]->GetMainStackSize(), rs2);
                    ss << "\t/*Assign sp[" << reg.frameIdx << " + " << rs2 << "] to " << rd << ".*/\n";
                    break;

                case Register::AssignState::Const:
                    AssignConst(rd_number, reg.globalRegister, rs2);
                    ss << "\t/*Assign const " << reg.globalRegister << "[" << rs2 << "]" << " to " << rd << ".*/\n";
                     break;

                case Register::AssignState::None:
                    FreeAssign(rd_number);
                    ss << "\ttcg_gen_" << opcode << "_tl(" << rd << ", " << rs1 <<  ", " << rs2 << ");\n";
                    break;

                default:
                    ss << "/*" << pos <<": " << rs1 <<" is Unknown*/\n";
                    break;
            }
        } else if(rs1State == Register::AssignState::None) {
            const Register& reg = mAssignedRegisters[rs2_number];
            switch(rs2State) {
                case Register::AssignState::Global:
                    AssignGlobal(rd_number, reg.globalRegister, rs1);
                    ss << "\t/*Assign " << reg.globalRegister << "[" << rs1 << "]" << " to " << rd << ".*/\n";
                    break;

                case Register::AssignState::Frame:
                    AssignFrame(rd_number, reg.frameIdx, mFunctions[function_number]->GetMainStackSize(), rs1);
                    ss << "\t/*Assign sp[" << reg.frameIdx << " + " << rs1 << "] to " << rd << ".*/\n";
                    break;

                case Register::AssignState::Const:
                    AssignConst(rd_number, reg.globalRegister, rs1);
                    ss << "\t/*Assign const " << reg.globalRegister << "[" << rs1 << "]" << " to " << rd << ".*/\n";
                     break;

                case Register::AssignState::None:
                    FreeAssign(rd_number);
                    ss << "\ttcg_gen_" << opcode << "_tl(" << rd << ", " << rs1 <<  ", " << rs2 << ");\n";
                    break;

                default:
                    ss << "/*" << pos <<": " << rs2 <<" is Unknown*/\n";
                    break;
            }
        } else {
            ss << "/*" << pos <<": add true true*/\n";
        }
    } else if(opcode == "movi") {
        FreeAssign(rd_number);
        std::string imm;
        offset += rd.size() + 2;
        GetSubString(line.c_str() + offset, imm, '.');
        ss << "\ttcg_gen_movi_tl(" << rd << ", " << imm << ");\n"; 
        
    } else if(opcode == "mov") {
        FreeAssign(rd_number);
        std::string op1;
        offset += rd.size() + 2;
        GetSubString(line.c_str() + offset, op1, '.');
        GetRegNumber(op1, function_number);
        ss << "\ttcg_gen_mov_tl(" << rd << ", " << op1 << ");\n"; 
        
    } else {
        std::string op1, op2, op3, op4;
        GetSubString(line.c_str() + offset, op1, ',');
        offset += op1.size() + 2;
        GetSubString(line.c_str() + offset, op2, ',');
        offset += op2.size() + 2;
        if(op1[0] == 'T') {
            FreeAssign(GetRegNumber(op2, function_number));
            GetSubString(line.c_str() + offset, op3, ',');
            offset += op3.size() + 2;
            GetSubString(line.c_str() + offset, op4, '.');
            ss << "\ttcg_gen_" << opcode << "_tl(" << op1 << ", " << op2 << ", " << op3 << ", " << op4 << ");\n";
            GetRegNumber(op3, function_number);
            GetRegNumber(op4, function_number);
        } else {
            FreeAssign(GetRegNumber(op1, function_number));
            GetSubString(line.c_str() + offset, op3, '.');
            ss << "\ttcg_gen_" << opcode << "_tl(" << op1 << ", " << op2 << ", " << op3  << ");\n";
            GetRegNumber(op2, function_number);
            GetRegNumber(op3, function_number);
        }   
    }
}

void Translater::StartStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "start" << std::endl;
#endif
    mStackFlag = true;
    function_number = atol(mContents[pos].substr(7).c_str());
    assert(function_number < mFunctions.size());
    const Function* f = mFunctions[function_number];
    ss << "\nstatic void " << f->GetName() << "(DisasContext *ctx, TCGv r0";
    for(int i = 0, e = f->GetNumArgs() > NUMBER_OF_A_REGISTERS ? NUMBER_OF_A_REGISTERS : f->GetNumArgs(); i < e; ++i)
        ss << ", TCGv a" << i;
        
    if (f->GetNumArgs() > NUMBER_OF_A_REGISTERS) {
        ss << ", TCGV arg_sp[" << f->GetNumArgs() - NUMBER_OF_A_REGISTERS << "]";
    } 
    ss << ") {\n";



    for(Label* label : f->GetLabels()) {
        ss << "\tTCGLabel *" << label->name <<" = " << "gen_new_label();\n";
    }
    ss << "\tTCGLabel *end_label = gen_new_label();\n\n";
}

#if(1)
void Translater::EndStatement(int pos, std::stringstream& ss,  std::stringstream& tmp_ss, int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "end" << std::endl;
#endif
    mStackFlag = false;
    const Function* f = mFunctions[function_number];
    for(int i = 1; i <= f->GetNumTmp(); ++i) {
        ss  << "\tTCGv tmp" << i << " = tcg_temp_new();\n";
    }
    for(int i = 1; i <= f->GetNumTmp(); ++i) {
        ss  << "\ttcg_gen_movi_tl(tmp" << i << ", 0);\n";
    }
        
    for(int i = f->GetNumArgs(); i < f->GetNumA(); ++i) {
        ss  << "\tTCGv a" << i << " = tcg_temp_new();\n";
    }
    for(int i = f->GetNumArgs(); i < f->GetNumA(); ++i) {
        ss  << "\ttcg_gen_movi_tl(a" << i << ", 0);\n";
    }

    if(f->GetUseArray())
        ss << "\tTCGv index = tcg_temp_new();\n\ttcg_gen_movi_tl(index, 0);\n";
    ss << "\n";
    ss << tmp_ss.rdbuf();
    tmp_ss.clear();
    ss << "\n\tgen_set_label(end_label);\n}\n";
}
#endif

void Translater::GotoStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "goto" << std::endl;
#endif
    mStackFlag = false;
    std::string label;
    GetSubString(mContents[pos].c_str() + 6, label, '.');
    ss << "\ttcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, " << label << ");\n"; 
}

void Translater::LoadStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0) 
    std::cout << pos << " : " << "load" << std::endl;
#endif
    mStackFlag = false;
    std::string op1, op2, imm, bitshift;
    const std::string& line = mContents[pos];
    int offset = + 4;
    GetSubString(line.c_str() + offset, bitshift, ',');
    offset += bitshift.size() + 2;
    GetSubString(line.c_str() + offset, op1, ',');

    if(op1[0] == 'r' && op1[1] == 'a' && op1[2] == '\0')
        return;
    offset += op1.size() + 2;
    GetRegNumber(op1, function_number);
    GetSubString(line.c_str() + offset, imm, '(');
    offset += imm.size() + 1;
    GetSubString(line.c_str() + offset, op2, ')');
    int idx = atol(imm.c_str()) >> WORDSIZE_SHIFT;
    Function* func = mFunctions[function_number];
    if(op2 == "sp") {
        if(func->IsArgStackWriten()) {
            if(idx < func->GetCurArgStackSize()) {
                ss << "\ttcg_gen_mov_tl(" << op1 << ", " << "arg_sp" 
                    << func->GetNumArgStacks() 
                    << "[" << idx << "]);\n";
            } else {
                ss << "\ttcg_gen_mov_tl(" << op1 << ", " << "sp[" 
                    << idx - func->GetCurArgStackSize() << "]);\n";
            }
        } else {
            if(idx < func->GetMainStackSize()) {
                ss << "\ttcg_gen_mov_tl(" << op1 << ", " << "sp[" << idx << "]);\n";
            } else {
                ss << "\ttcg_gen_mov_tl(" << op1 << ", " << "arg_sp[" 
                    << idx - func->GetMainStackSize() << "]);\n";
            }
        }
    } else {
        int op2_number = GetRegNumber(op2, function_number);
        const Register& reg = mAssignedRegisters[op2_number];
        if(reg.assignState == Register::AssignState::Global) {
            if(reg.indexglobalRegister == "" && reg.arraySize > 1) {
                ss << "\ttcg_gen_mov_tl(" << op1 << ", " << reg.globalRegister << "[" << idx <<"]);\n";
            } else if(reg.indexglobalRegister == "" ) {
                ss << "\ttcg_gen_mov_tl(" << op1 << ", " << reg.globalRegister <<");\n";
            } else {
                if(reg.arraySize != 1 && reg.indexglobalRegister != "") {
                    ss  << "\n\t/*ARRAY ACCESS*/\n"
                        << "\tLOAD_ARRAY(ctx, " << op1 << ", " << reg.globalRegister << ", "  << reg.arraySize << ", "
                        << reg.indexglobalRegister << ", " << idx << ", " << mN++ << ");\n";
                    ss << "\t/*End ARRAY ACCESS*/\n\n";
                    mHelperFlag |= HelperFlag::LOAD_ARRAY;
                    func->UseArray();
                } else if(reg.arraySize != 1) {
                    ss << "\ttcg_gen_mov_tl(" << op1 << ", " << reg.globalRegister << "[0]);\n";
                } else {
                    ss << "\ttcg_gen_mov_tl(" << op1 << ", " << reg.globalRegister << ");\n";
                }
            }
        } else if(reg.assignState == Register::AssignState::Const) {
            if(reg.indexglobalRegister == "" && reg.arraySize > 1) {
                ss << "\ttcg_gen_movi_tl(" << op1 << ", " << reg.globalRegister << "[" << idx <<"]);\n";
            } else if(reg.indexglobalRegister == "" ) {
                ss << "\ttcg_gen_movi_tl(" << op1 << ", " << reg.globalRegister <<");\n";
            } else {
                if(reg.indexglobalRegister != "") {
                    ss  << "\n\t/*ARRAY ACCESS*/\n"
                        << "\tLOAD_ARRAY_CONST(ctx, " << op1 << ", " << reg.globalRegister << ", "  << reg.arraySize << ", "
                        << reg.indexglobalRegister << ", " << idx << ", " << mN++ << ");\n";

                    ss << "\t/*End ARRAY ACCESS*/\n\n";
                    mHelperFlag |= HelperFlag::LOAD_ARRAY_CONST;
                    func->UseArray();
                } else {
                    ss << "\ttcg_gen_movi_tl(" << op1 << ", " << reg.globalRegister << "[0]);\n";
                }
            }
        } else if(reg.assignState == Register::AssignState::Frame) {
            bool hasindexreg = (reg.indexglobalRegister != "");
            ss  << "\n\t/*STACK POINTER ACCESS*/\n";
            ss  << "\tLOAD_FRAME_ARRAY(ctx, " << op1 << ", " << "sp" << ", " << reg.arraySize 
                << ", " << reg.indexglobalRegister << ", " << (reg.frameIdx + idx) << ", " << mN++ << ");\n";
            mHelperFlag |= HelperFlag::LOAD_FRAME_ARRAY;
            func->UseArray();

            ss  << "\t/*End STACK POINTER ACCESS*/\n\n";
        } 
    }
    FreeAssign(GetRegNumber(op1, function_number));
}

void Translater::StoreStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "store" << std::endl;
#endif
    mStackFlag = false;
    std::string op1, op2, imm, bitshift;
    const std::string& line = mContents[pos];
    int offset = 4;
    GetSubString(line.c_str() + offset, bitshift, ',');
    offset += bitshift.size() + 2;
    GetSubString(line.c_str() + offset, imm, '(');
    offset += imm.size() + 1;
    GetSubString(line.c_str() + offset, op1, ')');
    offset += op1.size() + 3;
    GetSubString(line.c_str() + offset, op2, '.');

    if(op2[0] == 'r' && op2[1] == 'a' && op2[2] == '\0')
        return;
    GetRegNumber(op2, function_number);
    int idx = atol(imm.c_str()) >> WORDSIZE_SHIFT;
    Function* func = mFunctions[function_number];
    if(op1 == "sp") {
        if(func->IsArgStackWriten()) {
            if(idx < func->GetCurArgStackSize()) {
                ss << "\ttcg_gen_mov_tl(arg_sp" << func->GetNumArgStacks() 
                    << "[" << idx << "], " << op2 <<");\n";
            } else {
                ss << "\ttcg_gen_mov_tl(sp[" << idx - func->GetCurArgStackSize() 
                    << "], " << op2 <<");\n";
            }
        } else {
            if(idx < func->GetMainStackSize()) {
                ss << "\ttcg_gen_mov_tl(sp[" << idx << "], " << op2 <<");\n";
            } else {
                ss << "\ttcg_gen_mov_tl(arg_sp[" << idx - func->GetMainStackSize()
                     << "], " << op2 << ");\n";
            }
        }
    } else {
        int op1_number = GetRegNumber(op1, function_number);
        const Register& reg = mAssignedRegisters[op1_number];
        if(reg.assignState == Register::AssignState::Global) {
            if(reg.indexglobalRegister == "" && reg.arraySize > 1) {
                ss << "\ttcg_gen_mov_tl(" << reg.globalRegister << "[" << idx <<"], " << op2 << ");\n";
            } else if(reg.indexglobalRegister == "") {
                ss << "\ttcg_gen_mov_tl(" << reg.globalRegister << ", " << op2 << ");\n";
            } else {
                if(reg.arraySize != 1 && reg.indexglobalRegister != "") {
                    ss  << "\n\t/*ARRAY ACCESS*/\n"
                        << "\tSTORE_ARRAY(ctx, " << reg.globalRegister << ", "  << reg.arraySize << ", "
                        << reg.indexglobalRegister << ", " <<  idx << ", " << op2 <<  ", " << mN++ << ");\n";

                    ss  << "\t/*End ARRAY ACCESS*/\n\n";
                    mHelperFlag |= HelperFlag::STORE_ARRAY;
                    func->UseArray();
                } else if(reg.arraySize != 1) {
                    ss << "\ttcg_gen_mov_tl(" << reg.globalRegister << "[0], " << op2 <<  ");\n";
                } else {
                    ss << "\ttcg_gen_mov_tl(" << reg.globalRegister << ", " << op2 <<  ");\n";
                }
            }
        } else if(reg.assignState == Register::AssignState::Frame) {
            bool hasindexreg = (reg.indexglobalRegister != "");
            ss  << "\n\t/*STACK POINTER ACCESS*/\n";
            ss  << "\tSTORE_FRAME_ARRAY(ctx, " <<"sp" << ", " << reg.arraySize << ", " << reg.indexglobalRegister 
                << ", " << (reg.frameIdx + idx) << ", " << op2 << ", " << mN++ << ");\n";
            mHelperFlag |= HelperFlag::STORE_FRAME_ARRAY;
            func->UseArray();
            ss  << "\t/*End STACK POINTER ACCESS*/\n\n";
        } else if(reg.assignState == Register::AssignState::Const) {
            ss << "\n\t/*Permission Denied*/\n";
        }
    }
}

void Translater::AssignStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "assign" << std::endl;
#endif
    mStackFlag = false;
    const std::string& line = mContents[pos];
    std::string rd, op;
    int offset = 8;
    GetSubString(line.c_str() + offset, rd, ',');
    offset += rd.size() + 2;
    GetSubString(line.c_str() + offset, op, '.');
    int rd_number = GetRegNumber(rd, function_number);
    if(op.size() > 3 && op[0] == '_' && op[1] == 'Z' && op[2] == 'L') {
        const char* str = op.c_str() + 3;
        std::stringstream lss;
        while('0' <= *str && *str <= '9') 
            lss << *(str++);
        AssignConst(rd_number, str);
        ss << "\t/*Assign const " << str << " to " << rd << ".*/\n"; 
    } else {
        AssignGlobal(rd_number, op);
        ss << "\t/*Assign " << op << " to " << rd << ".*/\n"; 
    }
    
}

void Translater::StackStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "stack" <<  mContents[pos] <<  std::endl;
#endif
    int size = atol(mContents[pos].c_str() + 14) / WORDSIZE;
    if(size > 0 ) {
        std::string sp = "sp";
        if(!mStackFlag){
            mFunctions[function_number]->IncNumArgStacks(size);
            sp += (char)mFunctions[function_number]->GetNumArgStacks() + '0'; 
            sp = "arg_" + sp;
        }
        else {
            mFunctions[function_number]->SetMainStackSize(size); 
            mStackFlag = false;
        }
        ss  << "\tTCGv " << sp <<"[" << size << "]; "
            << "for(int i = 0; i < " << size << "; ++i) { " << sp <<"[i] = tcg_temp_new(); }\n\n";
    }
}

void Translater::ReturnStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "return" << std::endl;
#endif
    mStackFlag = false;
    ss << "\ttcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, end_label);\n";
}

void Translater::CallStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "call" << std::endl;
#endif
    mStackFlag = false;
    mFunctions[function_number]->NotAbletoWriteArgStack();
    std::string functionLabel;
    GetSubString(mContents[pos].c_str() + 6, functionLabel, '.');

    if(functionLabel[0] != '_' || functionLabel[1] != 'Z')
        std::cerr << "UnKnown Function Format : " << functionLabel << std::endl;
    else {
        int idx = 2;
        while('0' <= functionLabel[idx] && functionLabel[idx] <= '9') {
            ++idx;
        }
        assert(idx > 2);
        int len = atol(functionLabel.substr(2, idx - 2).c_str());
        int numArgs;
        if(functionLabel[idx + len] != 'v')
            numArgs = functionLabel.size() - (idx + len);
        else
            numArgs = 0;

        ss << "\t" <<  functionLabel.substr(idx, len) << "(ctx, r0";

        for(int i = 0, e = numArgs > NUMBER_OF_A_REGISTERS ? NUMBER_OF_A_REGISTERS : numArgs ; i < e; ++i) { 
            ss << ", a" << i;
        }
        if(numArgs > NUMBER_OF_A_REGISTERS)
            ss << ", arg_sp" << mFunctions[function_number]->GetNumArgStacks();
        ss << ");\n";
    }

}

void Translater::FrameStatement(int pos ,std::stringstream& ss, int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "frame" << std::endl;
#endif
    mStackFlag = false;
    const std::string& line = mContents[pos];
    std::string rd, sp, imm;
    int offset = 6;
    GetSubString(line.c_str() + offset, rd, ',');
    offset += rd.size() + 2;
    GetSubString(line.c_str() + offset, sp, ',');
    offset += sp.size() + 2;
    GetSubString(line.c_str() + offset, imm, '.');
    if(sp != "sp")
        std::cerr << "Unknown Format : " << pos << " : " << line << std::endl;
    int idx = atol(imm.c_str()) >> WORDSIZE_SHIFT;
    const Function *f = mFunctions[function_number];
    AssignFrame(GetRegNumber(rd, function_number), idx, f->GetMainStackSize());
    
    ss << "\t/*Assign sp[" << idx << "] to " << rd << ".*/\n";
}


/*======================================*/
/*       PROLOUGE EPILOGUE              */
/*======================================*/

void Translater::Prologue(std::stringstream& ss) {
        
    int numGlobals = mGlobalRegisters.size();
    if(numGlobals > 0) {
        mHasInit = true;
        ss << "static TCGv";
        int i = 1;
        for(auto iter : mGlobalRegisters) {
            ss << " " << iter.first;
            if(iter.second != 1)
                ss << "[" << iter.second << "]";
            ss << (i < numGlobals ? ',' : ';' );
            ++i;
        }
        ss  << "\n";

        for(auto iter : mGlobalRegisters) {
            if(iter.second != 1) {
                int digit = std::to_string(iter.second).length();
                ss << "static const char " << iter.first << "_name[][" << (iter.first.size() + digit + 2) <<"] = {";
                for(int i = 0; i < iter.second; ++i) {
                    ss << "\"" << iter.first << "_" << i << "\", ";
                }
                ss << "};\n";
            }
        }

        ss  << "\nstatic void riscv_" << mOption->GetProjectName() << "_translate_init(void) {\n";
        for(auto iter : mGlobalRegisters) {
            if(iter.second == 1) {
                ss  << "\t" << iter.first << " = tcg_global_mem_new(tcg_env, offsetof(CPURISCVState, "
                    << iter.first << "), \"" << iter.first <<"\");\n";
            } else {
                ss  << "\tfor(int i = 0; i < " << iter.second << "; ++i) {\n"
                    << "\t\t" << iter.first << "[i] = tcg_global_mem_new(tcg_env, offsetof(CPURISCVState,"
                    << iter.first << "[i]), " << iter.first << "_name[i]);\n"
                    << "\t}\n";
            }
        }
        ss  <<"}\n" ;

    }

    ss << "\n";

    for(auto iter : mConstValues) {
        size_t size = iter.second->size();
        int i = 0;
        ss << "static const unsigned " << iter.first << "[" << size << "] = { " << std::hex;
        for(unsigned v : *iter.second) {
            if( i++ % 16 == 0)
                ss << "\n\t";
            ss << "0x" << v << ", ";
        }
        ss << "\n};\n\n";
        ss << std::dec;
        mGlobalRegisters.emplace(iter.first, iter.second->size());
        delete iter.second;
    }
    mConstValues.clear();

    for(auto f : mFunctions) {
        ss << "static void " << f->GetName() << "(DisasContext *ctx, TCGv r0";
        for(int i = 0, e = f->GetNumArgs() > NUMBER_OF_A_REGISTERS ? NUMBER_OF_A_REGISTERS : f->GetNumArgs(); i < e; ++i)
            ss << ", TCGv a" << i;
            
        if (f->GetNumArgs() > NUMBER_OF_A_REGISTERS) {
            ss << ", TCGV arg_sp[" << f->GetNumArgs() - NUMBER_OF_A_REGISTERS << "]";
        } 
        ss << ");\n";
    }


}

void Translater::Epilogue(std::stringstream& ss) {
    ss << '\n';
    mOption->WriteInstruction(ss);

    if(mHelperFlag & HelperFlag::LOAD_ARRAY) 
        ss << "#undef LOAD_ARRAY\n";

    if(mHelperFlag & HelperFlag::STORE_ARRAY) 
        ss << "#undef STORE_ARRAY\n";

    if(mHelperFlag & HelperFlag::LOAD_FRAME_ARRAY)
        ss << "#undef LOAD_FRAME_ARRAY\n";
    
    if(mHelperFlag & HelperFlag::STORE_FRAME_ARRAY)
        ss << "#undef STORE_FRAME_ARRAY\n";

    if(mHelperFlag & HelperFlag::LOAD_ARRAY_CONST) 
        ss << "#undef LOAD_ARRAY_CONST\n";

    ss << "#endif";
}

void Translater::GenerateHelpers(std::stringstream& ss) {
    
    if(mHelperFlag & HelperFlag::LOAD_ARRAY) {

        ss  << "#define LOAD_ARRAY(ctx, rd, array, length, index_reg, offset, n)\t\t\t\t\t\t\\\n"
            << "\t{\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_sari_tl(index, (index_reg), " << WORDSIZE_SHIFT << ");\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_addi_tl(index, index, (offset));\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tTCGLabel *(local_labels##n)[(length)];\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i) { (local_labels##n)[i] = gen_new_label(); }\t\\\n"
            << "\t\tTCGLabel *local_end##n = gen_new_label();\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i){\t\t\t\t\t\t\t\t\t\t\t\t\\\n" 
            << "\t\t\ttcg_gen_brcondi_tl(TCG_COND_EQ, index, i, ( local_labels##n )[i]);\t\t\t\\\n"
            << "\t\t}\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, (local_end##n));\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i) {\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\tgen_set_label((local_labels##n)[i]);\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\ttcg_gen_mov_tl((rd), (array)[i]);\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\ttcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, (local_end##n));\t\t\t\\\n"
            << "\t\t}\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tgen_set_label((local_end##n));\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t}\n\n";
    }

    if(mHelperFlag & HelperFlag::STORE_ARRAY) {

        ss  << "#define STORE_ARRAY(ctx, array, length, index_reg, offset, rs, n)\t\t\t\t\t\t\\\n"
            << "\t{\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_sari_tl(index, (index_reg), " << WORDSIZE_SHIFT << ");\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_addi_tl(index, index, (offset));\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tTCGLabel *(local_labels##n)[(length)];\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i) { (local_labels##n)[i] = gen_new_label(); }\t\\\n"
            << "\t\tTCGLabel *local_end##n = gen_new_label();\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i){\t\t\t\t\t\t\t\t\t\t\t\t\\\n" 
            << "\t\t\ttcg_gen_brcondi_tl(TCG_COND_EQ, index, i, ( local_labels##n )[i]);\t\t\t\\\n"
            << "\t\t}\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, (local_end##n));\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i) {\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\tgen_set_label((local_labels##n)[i]);\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\ttcg_gen_mov_tl((array)[i], (rs));\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\ttcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, (local_end##n));\t\t\t\\\n"
            << "\t\t}\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tgen_set_label((local_end##n));\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t}\n\n";
    }

    if(mHelperFlag & HelperFlag::LOAD_FRAME_ARRAY) {

        ss  << "#define LOAD_FRAME_ARRAY(ctx, rd, array, length, index_reg, offset, n)\t\t\t\t\t\\\n"
            << "\t{\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_sari_tl(index, (index_reg), "<< WORDSIZE_SHIFT <<");\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_addi_tl(index, index, (offset));\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tTCGLabel *(local_labels##n)[(length)];\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i) { (local_labels##n)[i] = gen_new_label(); }\t\\\n"
            << "\t\tTCGLabel *local_end##n = gen_new_label();\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i){\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\ttcg_gen_brcondi_tl(TCG_COND_EQ, index, i, ( local_labels##n )[i]);\t\t\t\\\n"
            << "\t\t}\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, (local_end##n));\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i) {\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\tgen_set_label((local_labels##n)[i]);\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\ttcg_gen_mov_tl((rd), (array)[i]);\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\ttcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, (local_end##n));\t\t\t\\\n"
            << "\t\t}\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tgen_set_label((local_end##n));\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t}\n\n";

    }

    if(mHelperFlag & HelperFlag::STORE_FRAME_ARRAY) {

        ss  << "#define STORE_FRAME_ARRAY(ctx, array, length, index_reg, offset, rs, n)\t\t\t\t\t\\\n"
            << "\t{\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_sari_tl(index, (index_reg), "<< WORDSIZE_SHIFT <<");\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_addi_tl(index, index, (offset));\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tTCGLabel *(local_labels##n)[(length)];\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i) { (local_labels##n)[i] = gen_new_label(); }\t\\\n"
            << "\t\tTCGLabel *local_end##n = gen_new_label();\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i){\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\ttcg_gen_brcondi_tl(TCG_COND_EQ, index, i, ( local_labels##n )[i]);\t\t\t\\\n"
            << "\t\t}\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, (local_end##n));\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i) {\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\tgen_set_label((local_labels##n)[i]);\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\ttcg_gen_mov_tl((array)[i], (rs));\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\ttcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, (local_end##n));\t\t\t\\\n"
            << "\t\t}\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tgen_set_label((local_end##n));\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t}\n\n";
    }

    if(mHelperFlag & HelperFlag::LOAD_ARRAY_CONST) {

        ss  << "#define LOAD_ARRAY_CONST(ctx, rd, array, length, index_reg, offset, n)\t\t\t\t\t\\\n"
            << "\t{\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_sari_tl(index, (index_reg), " << WORDSIZE_SHIFT << ");\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_addi_tl(index, index, (offset));\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tTCGLabel *(local_labels##n)[(length)];\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i) { (local_labels##n)[i] = gen_new_label(); }\t\\\n"
            << "\t\tTCGLabel *local_end##n = gen_new_label();\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i){\t\t\t\t\t\t\t\t\t\t\t\t\\\n" 
            << "\t\t\ttcg_gen_brcondi_tl(TCG_COND_EQ, index, i, ( local_labels##n )[i]);\t\t\t\\\n"
            << "\t\t}\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\ttcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, (local_end##n));\t\t\t\t\\\n"
            << "\t\tfor(int i = 0; i < (length); ++i) {\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\tgen_set_label((local_labels##n)[i]);\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\ttcg_gen_movi_tl((rd), (array)[i]);\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\t\ttcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, (local_end##n));\t\t\t\\\n"
            << "\t\t}\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t\tgen_set_label((local_end##n));\t\t\t\t\t\t\t\t\t\t\t\t\t\\\n"
            << "\t}\n\n"; 
    }
  
    if(mHelperFlag & HelperFlag::LOGICAL_AND) {
        ss  << "#if !defined(__HELPERS_LOGICAL_AND__)\n"
            << "#define __HELPERS_LOGICAL_AND__\n"
            << "static void LOGICAL_AND(DisasContext *ctx, TCGv rd, TCGv rs1, TCGv rs2) {\n"
            << "\tTCGLabel *label = gen_new_label();\n"
            << "\ttcg_gen_movi_tl(rd, 0);\n"
            << "\ttcg_gen_brcondi_tl(TCG_COND_EQ, rs1, 0x0, label);\n"
            << "\ttcg_gen_brcondi_tl(TCG_COND_EQ, rs2, 0x0, label);\n"
            << "\ttcg_gen_movi_tl(rd, 1);\n"
            << "\tgen_set_label(label);\n"
            << "}\n"
            << "#endif //!__HELPERS_LOGICAL_AND__\n\n";
    }

    if(mHelperFlag & HelperFlag::LOGICAL_OR) {
        ss  << "#if !defined(__HELPERS_LOGICAL_OR__)\n"
            << "#define __HELPERS_LOGICAL_OR__\n"
            << "static void LOGICAL_OR(DisasContext *ctx, TCGv rd, TCGv rs1, TCGv rs2) {\n"
            << "\tTCGLabel *label = gen_new_label();\n"
            << "\ttcg_gen_movi_tl(rd, 1);\n"
            << "\ttcg_gen_brcondi_tl(TCG_COND_NE, rs1, 0x0, label);\n"
            << "\ttcg_gen_brcondi_tl(TCG_COND_NE, rs2, 0x0, label);\n"
            << "\ttcg_gen_movi_tl(rd, 0);\n"
            << "\tgen_set_label(label);\n"
            << "}\n"
            << "#endif //!__HELPERS_LOGICAL_OR__\n\n";
    }

    if(mHelperFlag & HelperFlag::LOGICAL_ANDi) {
        ss  << "#if !defined(__HELPERS_LOGICAL_AND_I__)\n"
            << "#define __HELPERS_LOGICAL_AND_I__\n"
            << "static void LOGICAL_ANDi(DisasContext *ctx, TCGv rd, TCGv rs1, int imm) {\n"
            << "\tTCGLabel *label = gen_new_label();\n"
            << "\tTCGv rs2 = tcg_temp_new();\n"
            << "\ttcg_gen_movi_tl(rs2, imm);\n"
            << "\ttcg_gen_movi_tl(rd, 0);\n"
            << "\ttcg_gen_brcondi_tl(TCG_COND_EQ, rs1, 0x0, label);\n"
            << "\ttcg_gen_brcondi_tl(TCG_COND_EQ, rs2, 0x0, label);\n"
            << "\ttcg_gen_movi_tl(rd, 1);\n"
            << "\tgen_set_label(label);\n"
            << "}\n"
            << "#endif //!__HELPERS_LOGICAL_AND_I__\n\n";
    }

    if(mHelperFlag & HelperFlag::LOGICAL_ORi) {
        ss  << "#if !defined(__HELPERS_LOGICAL_OR_I__)\n"
            << "#define __HELPERS_LOGICAL_OR_I__\n"
            << "static void LOGICAL_ORi(DisasContext *ctx, TCGv rd, TCGv rs1, int imm) {\n"
            << "\tTCGLabel *label = gen_new_label();\n"
            << "\tTCGv rs2 = tcg_temp_new();\n"
            << "\ttcg_gen_movi_tl(rs2, imm);\n"
            << "\ttcg_gen_movi_tl(rd, 1);\n"
            << "\ttcg_gen_brcondi_tl(TCG_COND_NE, rs1, 0x0, label);\n"
            << "\ttcg_gen_brcondi_tl(TCG_COND_NE, rs2, 0x0, label);\n"
            << "\ttcg_gen_movi_tl(rd, 0);\n"
            << "\tgen_set_label(label);\n"
            << "}\n"
            << "#endif // !__HELPERS_LOGICAL_OR_I__\n\n";
    }

}

void Translater::GenerateNewRegisters(std::stringstream& ss) {
    ss  << "#if defined(NEW_REGISTERS)\n"
        << "#undef NEW_REGISTERS\n"
        << "#define NEWMEMBER(member) target_ulong member;\n\n";

    for(auto iter : mGlobalRegisters) {
        ss << "NEWMEMBER(" << iter.first;
        if(iter.second != 1)
            ss << "[" << iter.second << "]";
        ss << ")\n";
    }

    ss  << "\n#undef NEWMEMBER\n"
        << "#else\n\n";
}

/*======================================*/
/*      Argument Help and Version       */
/*======================================*/

void Translater::Help() {
    std::cout   << "Usage: translater [options] file...\n"
                << "Do not use optimization."
                << "Options: \n"
                << "\t--help\t\t\tDisplay this information.\n"
                << "\t--version\t\tDisplay compiler version information\n"
                << "\t-o <file>\t\tPlace the output into <file>.\n"
                << "\t--option <file>\t\tSepcify <file> as an option file.\n"
                << std::endl;
}

void Translater::Version() {
    std::cout   << "translater beta version\n"
                << "Copyright (C) 2023 Takuto Watanabe, Tokyo Institute of Technology\n"
                << std::endl; 
}