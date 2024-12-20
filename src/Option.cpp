#include "Option.h"
#include "parser.hh"
#include "Node.h"
#include <sstream>
#include <string>

#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

Option::Option(Translater* translater)
    :mErrorCount(0), mTranslater(translater), mProjectName(nullptr)
    {}

Option::~Option() {
    for(auto inst : mInstructions)
        delete inst;
    mInstructions.clear();
    delete mProjectName;
}

bool Option::compile(const std::string& f) {

    mFileName = f;
    if(!scan_begin())
        return false;
    yy::parser parser(*this);
    int result = parser.parse();
    scan_end();

    if(result != 0)
        return false;

    return mErrorCount == 0;
}

void Option::error(const yy::location& l, const std::string& m) {
    std::cerr << l << ": " << m << std::endl;
    ++mErrorCount;
}

void Option::error(const std::string& m) {
    std::cerr << m << std::endl;
    ++mErrorCount;
}

void Option::DefineInstruction(const yy::location& l, const std::string* name, OptStateBlock* block) {
    Instruction* inst = new Instruction(name, block);
    mInstructions.push_back(inst);
}

void Option::DefineRegister(const yy::location& l, const std::string* name){
    mTranslater->AddGlobalRegister(*name);
    delete name;
}

void Option::WriteInstruction(std::stringstream& ss) {
    for(auto inst : mInstructions) {
       inst->Anaylze(this, ss);
    }
}

const std::string& Option::GetProjectName() const {
    const static std::string empty = "";
    if(mProjectName)
        return *mProjectName;
    return empty;
}

void Instruction::Anaylze(Option* option, std::stringstream& ss) {
    ss << "static bool trans_" << *mName << "(DisasContext *ctx, arg_" << *mName << " *a) {\n";
    std::stringstream tmp_ss;
    mBlock->Analyze(option, this, tmp_ss, 1);

    for(int i = 0; i < mNumLabel; ++i) {
        ss << "\tTCGLabel *label" << i << " = gen_new_label();\n"; 
        if(i == mNumLabel - 1)
            ss << '\n';
    } 

    for(int i = 0; i < mNumTmp; ++i) 
        ss << "\tTCGv tmp" << i << " = tcg_temp_new();\n";
    
    for(int i = 0; i < mNumA; ++i) 
        ss << "\tTCGv a" << i << " = tcg_temp_new();\n";

    ss  << "\tTCGv r0 = tcg_temp_new();\n"
        << "\ttcg_gen_movi_tl(r0, 0);\n\n";

    ss << tmp_ss.rdbuf();
    ss << "\treturn true;\n}\n\n";
}

int Instruction::IsLocal(const std::string& local) {
    auto iter = mLocals.find(local);
    if(iter != mLocals.end()) {
        return iter->second;
    }
    return -1;
}