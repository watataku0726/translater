#include "Translater.h"
#include "Option.h"
#include "Function.h"

#include "cassert"

Translater::Translater(const std::string& filename, const Option* option) 
    :mFileName(filename), mOption(option), mStackFlag(false)
{
    mFunctions.clear();
    mContents.clear();
    mGlobalRegisters.clear();
}

Translater::~Translater() {
    for(Function* f : mFunctions)
        delete f;
}

bool Translater::Initialize() {
    std::ifstream file(mFileName);
    if(file.fail()){
        std::cerr << "Failed to open file:" << mFileName << std::endl;
        return false;
    }
    std::stringstream ss;
    ss << file.rdbuf();
    Analyze(ss);
    return true;
}

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

bool Translater::Analyze(std::stringstream& ss) {
    std::string line;
    int pos = 0;
    State state = State::OutofFunction;

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
        //mContents.push_back("?end\t" + mFunctions.back()->GetName());
        mFunctions.back()->SetEnd(pos - 1);
        state = State::OutofFunction;
        //++pos;
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
    if(opcode == ".p2align") {
        std::string imm;
        offset += opcode.size() + 1;
        GetSubString(line.c_str() + offset, imm, '\0');
        p2align = atol(imm.c_str());
    } else if(opcode == ".size") {
        std::string name, imm;
        offset += opcode.size() + 1;
        GetSubString(line.c_str() + offset, name, ',');
        offset += name.size() + 2;
        GetSubString(line.c_str() + offset, imm, '\0');
        bool isArray = atol(imm.c_str()) >> p2align != 1;
        mGlobalRegisters.emplace(name, isArray);
        state == State::OutofFunction;
        p2align = 2;
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
        std::cout << iter->first << " " << (iter->second ? "true" : "false") << std::endl;
    }

#else
    std::stringstream ss;
    int pos = 0, function_number = 0;
    bool stack_flag = false;
    for(std::string line : mContents) {
        if(line[0] != '?' && line[0] != '!') {
            ss << "\t" << line << "\n";
            ++pos;
            continue;
        } else if(line[0] == '!') {
            NormalStatement(pos, ss, function_number);
            ++pos;
            continue;
        }
        std::string opcode;
        GetSubString(line.substr(1), opcode, '\t');

        if(opcode == "goto")
            GotoStatement(pos, ss, function_number);
        else if(opcode == "ld")
            LoadStatement(pos, ss, function_number);
        else if(opcode == "st")
            StoreStatement(pos, ss, function_number);
        else if(opcode == "assign")
            AssignStatement(pos, ss, function_number);
        else if(opcode == "stki")
            StackStatement(pos, ss, function_number);
        else if(opcode == "start")
            StartStatement(pos, ss, function_number);
        //else if(opcode == "end")
        //    EndStatement(pos, ss, function_number);
        else if(opcode == "ret")
            ReturnStatement(pos, ss, function_number);
        else if(opcode == "call")
            CallStatement(pos, ss, function_number);
        ++pos;
    }
    std::cout << ss.str() << std::endl;
#endif
    
}

void Translater::NormalStatement(int pos, std::stringstream& ss,  int& function_number) {
    std::string opcode, rd;
    const std::string& line = mContents[pos];
    int offset = 1;
    GetSubString(line.c_str() + offset, opcode, '\t');
    offset += opcode.size() + 1;
    GetSubString(line.c_str() + offset, rd, ',');
    int rd_number = GetRegNumber(rd);
    if(opcode == "add") {
        std::string rs1, rs2;
        offset += rd.size() + 2;
        GetSubString(line.c_str() + offset, rs1, ',');
        offset += rs1.size() + 2;
        GetSubString(line.c_str() + offset, rs2, '.');

        int rs1_number = GetRegNumber(rs1);
        int rs2_number = GetRegNumber(rs2);
        bool isrs1Assigned = IsAssignedGlobal(rs1_number);
        bool isrs2Assigned = IsAssignedGlobal(rs2_number);
        if(!isrs1Assigned && !isrs2Assigned) {
            FreeAssign(rd_number);
            ss << "\ttcg_gen_" << opcode << "_tl(" << rd << ", " << rs1 <<  ", " << rs2 << ");\n";
        } else if(isrs1Assigned && !isrs2Assigned) {
            AssignGlobal(rd_number, mGlobalAssignedRegisters[rs1_number].globalRegister, rs2);
            ss << "\t/*Assign " << rd << " to " << mGlobalAssignedRegisters[rs1_number].globalRegister << "[" << rs2 << "]" << ".*/\n";
            
        } else if(!isrs1Assigned && isrs2Assigned) {
            AssignGlobal(rd_number, mGlobalAssignedRegisters[rs2_number].globalRegister, rs1);
            ss << "\t/*Assign " << rd << " to " << mGlobalAssignedRegisters[rs2_number].globalRegister << "[" << rs1 << "]" << ".*/\n";
        } else {
            ss << "/*" << pos <<": add true true*/\n";
        }
    } else {
        FreeAssign(rd_number);
        std::string ops;
        GetSubString(line.c_str() + offset, ops, '.');
        ss << "\ttcg_gen_" << opcode << "_tl(" << ops << ");\n";
    }
}

int Translater::GetRegNumber(const std::string& reg) {
    int idx = -1;
    if(reg[0] == 't' && reg[1] == 'm' && reg[2] == 'p') {
        idx = atol(reg.c_str() + 3) - 1;
    } else if(reg[0] == 'a') {
        idx = atol(reg.c_str() + 1) + NUMBER_OF_TMP_REGISTERS;
    } else if(reg[0] == 'r') {
        idx = MAX_GLOBAL_ASSIGNED_REIGSTERS - 1;
    }

    return idx;
}

void Translater::FreeAssign(int reg_number) {
    if(reg_number >= 0 && reg_number < MAX_GLOBAL_ASSIGNED_REIGSTERS) {
        mGlobalAssignedRegisters[reg_number].isAssigned = false;
    }
}

bool Translater::IsAssignedGlobal(int reg_number) {
    bool ret = false;
    if(reg_number >= 0 && reg_number < MAX_GLOBAL_ASSIGNED_REIGSTERS) {
        ret = mGlobalAssignedRegisters[reg_number].isAssigned;
    }
    return ret;
}

void Translater::AssignGlobal(int reg_number, const std::string& global_register_name, const std::string& index_reg_name) {
    if(reg_number >= 0 && reg_number < MAX_GLOBAL_ASSIGNED_REIGSTERS) {
        auto iter = mGlobalRegisters.find(global_register_name);
        if(iter != mGlobalRegisters.end()) {
            mGlobalAssignedRegisters[reg_number].isAssigned = true;
            mGlobalAssignedRegisters[reg_number].globalRegister = global_register_name;
            mGlobalAssignedRegisters[reg_number].indexglobalRegister = index_reg_name; 
            mGlobalAssignedRegisters[reg_number].isArray = iter->second;
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

    for(int i = 1; i <= NUMBER_OF_TMP_REGISTERS; ++i)
        ss << "\tTCGv tmp" << i << " = tcg_temp_local_new();\n";
    for(int i = f->GetNumArgs(); i < NUMBER_OF_A_REGISTERS; ++i) {
        ss << "\tTCGv a" << i << " = tcg_temp_local_new();\n";
    }
    ss << "\n";

    for(Label* label : f->GetLabels()) {
        ss << "\tTCGLabel *" << label->name <<" = " << "gen_new_label();\n";
    }

    ss << "\n";
}

void Translater::EndStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "end" << std::endl;
#endif
    mStackFlag = false;
}

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

    if(op1[0] == 'r' && op1[1] == 'a' && op1[2] == ' ')
        return;
    offset += op1.size() + 2;
    GetSubString(line.c_str() + offset, imm, '(');
    offset += imm.size() + 1;
    GetSubString(line.c_str() + offset, op2, ')');
    int idx = atol(imm.c_str()) / WORDSIZE;
    const Function* func = mFunctions[function_number];
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
        int op2_number = GetRegNumber(op2);
        if(idx) {
            ss << "\ttcg_gen_mov_tl(" << op1 << ", " << mGlobalAssignedRegisters[op2_number].globalRegister << "[" << idx <<"]);\n";
        } else {
            if(mGlobalAssignedRegisters[op2_number].isArray) {
                ss  << "\ttcg_gen_srai_tl(" << mGlobalAssignedRegisters[op2_number].indexglobalRegister << ", "
                    << mGlobalAssignedRegisters[op2_number].indexglobalRegister << ", 2);\n" 
                    << "\tLOAD_ARRAY(" << op1 << ", " << mGlobalAssignedRegisters[op2_number].globalRegister << ", " 
                    << mGlobalAssignedRegisters[op2_number].indexglobalRegister << ");\n"
                    << "\ttcg_gen_shli_tl(" << mGlobalAssignedRegisters[op2_number].indexglobalRegister << ", "
                    << mGlobalAssignedRegisters[op2_number].indexglobalRegister << ", 2);\n";
            } else {
                ss << "\ttcg_gen_mov_tl(" << op1 << ", " << mGlobalAssignedRegisters[op2_number].globalRegister << ");\n";
            }
        }
    }
    FreeAssign(GetRegNumber(op1));
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

    if(op2[0] == 'r' && op2[1] == 'a' && op2[2] == ' ')
        return;

    int idx = atol(imm.c_str()) / WORDSIZE;
    const Function* func = mFunctions[function_number];
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
        int op1_number = GetRegNumber(op1);
        if(idx) {
            ss << "\ttcg_gen_mov_tl(" << mGlobalAssignedRegisters[op1_number].globalRegister << "[" << idx <<"], " << op2 << ");\n";
        } else {
            if(mGlobalAssignedRegisters[op1_number].isArray) {
                ss  << "\ttcg_gen_sari_tl(" << mGlobalAssignedRegisters[op1_number].indexglobalRegister << ", "
                    << mGlobalAssignedRegisters[op1_number].indexglobalRegister << ", 2);\n" 
                    << "\tSTORE_ARRAY(" << op1 << ", " << mGlobalAssignedRegisters[op1_number].globalRegister << ", " 
                    << mGlobalAssignedRegisters[op1_number].indexglobalRegister << ");\n"
                    << "\ttcg_gen_shli_tl(" << mGlobalAssignedRegisters[op1_number].indexglobalRegister << ", "
                    << mGlobalAssignedRegisters[op1_number].indexglobalRegister << ", 2);\n" ;
            } else {
                ss << "\ttcg_gen_mov_tl(" << mGlobalAssignedRegisters[op1_number].globalRegister << ", " << op2 <<  ");\n";
            }
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
    int rd_number = GetRegNumber(rd);
    AssignGlobal(rd_number, op);
    ss << "\t/*Assign " << rd << " to " << op << ".*/\n"; 
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
        ss  << "\tTCGv " << sp <<"[" << size << "];\n"
            << "\tfor(int i = 0; i < " << size << "; ++i){ " << sp <<"[i] = tcg_temp_local_new(); }\n\n";
    }
}

void Translater::ReturnStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "return" << std::endl;
#endif
    mStackFlag = false;
    ss << "}\n";
}

void Translater::CallStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "call" << std::endl;
#endif
    mStackFlag = false;
    mFunctions[function_number]->NotAbletoWriteArgStack();
    ss << "call\n";
}
