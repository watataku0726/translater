#include "Translater.h"
#include "Option.h"
#include "Function.h"

#include "cassert"

Translater::Translater(const std::string& filename, const Option* option) 
    :mFileName(filename), mOption(option), mStackFlag(false)
{
    mFunctions.clear();
    mContents.clear();
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
    for(size_t i = 0; i < line.size(); ++i) {
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
        mContents.push_back("gen_set_label(" + name + ");");
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
    mContents.push_back("?start\t" + mFunctions.back()->GetName());
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
        }
    }

    return true;
}

void Translater::RunLoop() {
#if(0)
    int i = 0;
    for( std::string str : mContents) {
        if(str[0] == '?')
            std::cout << i++ << " : " << str << std::endl;
    }

    for(Function *f : mFunctions) {
        std::cout << f->GetStart() << " " << f->GetEnd() << " " << f->GetNumArgs() << " "  << f->GetNumLabels() << std::endl;
    }
#else
    std::stringstream ss;
    int pos = 0, function_number = 0;
    bool stack_flag = false;
    for(std::string line : mContents) {
        if(line[0] != '?' ) {
            ss << "\t" << line << "\n";
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
        else if(opcode == "end")
            EndStatement(pos, ss, function_number);
        else if(opcode == "ret")
            ReturnStatement(pos, ss, function_number);
        else if(opcode == "call")
            CallStatement(pos, ss, function_number);
        ++pos;
    }
#endif
    std::cout << ss.str() << std::endl;
}

void Translater::StartStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "start" << std::endl;
#endif
    mStackFlag = true;
    assert(function_number < mFunctions.size()); 
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
    ss << "\ttcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, " << mContents[pos].c_str() + 6 << ");\n"; 
}

void Translater::LoadStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0) 
    std::cout << pos << " : " << "load" << std::endl;
#endif
    mStackFlag = false;
    std::string op1, op2, imm;
    const std::string& line = mContents[pos];
    GetSubString(line.c_str() + 4, op1, ',');
    GetSubString(line.c_str() + 4 + op1.size() + 2, imm, '(');
    GetSubString(line.c_str() + 4 + op1.size() + 2 + imm.size() + 1, op2, ')');
    int idx = atol(imm.c_str()) / WORDSIZE;
    if(op2 == "sp") {
        if(mFunctions[function_number]->IsArgStackWriten()) {
            if(idx < mFunctions[function_number]->GetCurArgStackSize()) {
                ss << "\ttcg_gen_mov_tl(" << op1 << ", " << "arg_sp" 
                << mFunctions[function_number]->GetNumArgStacks() 
                << "[" << idx << "]);\n";
            } else {
                ss << "\ttcg_gen_mov_tl(" << op1 << ", " << "sp[" 
                    << idx - mFunctions[function_number]->GetCurArgStackSize() << "]);\n";
            }
        } else {
            if(idx < mFunctions[function_number]->GetMainStackSize()) {
                ss << "\ttcg_gen_mov_tl(" << op1 << ", " << "sp[" << idx << "]);\n";
            } else {
                ss << "\ttcg_gen_mov_tl(" << op1 << ", " << "arg_sp[" 
                    << idx - mFunctions[function_number]->GetMainStackSize() << "]);\n";
            }
        }
    } else {
        //Process Global 
    }
}

void Translater::StoreStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "store" << std::endl;
#endif
    mStackFlag = false;
}

void Translater::AssignStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "assign" << std::endl;
#endif
    mStackFlag = false;
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
            << "\tfor(int i = 0; i < " << size << "; ++i){ " << sp <<"[i] = tcg_temp_local_new(); }\n";
    }
}

void Translater::ReturnStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "return" << std::endl;
#endif
    mStackFlag = false;
}

void Translater::CallStatement(int pos, std::stringstream& ss,  int& function_number) {
#if !defined(NDEBUG) && (0)
    std::cout << pos << " : " << "call" << std::endl;
#endif
    mStackFlag = false;
    mFunctions[function_number]->NotAbletoWriteArgStack();
    ss << "call\n";
}
