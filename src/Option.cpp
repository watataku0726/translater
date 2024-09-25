#include "Option.h"
#include "parser.hh"
#include <sstream>
#include <string>

#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

Option::Option()
    :mErrorCount(0)
    {}

Option::~Option() {
    for(auto inst : mInstructions)
        delete inst;
    mInstructions.clear();
    for(auto reg : mRegisters)
        delete reg;
    mRegisters.clear();
}

bool Option::compile(const std::string& f) {

    mFileName = f;
    scan_begin();
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
    mRegisters.push_back(name);
}

void Option::WriteInstruction(std::stringstream& ss) {
    for(auto inst : mInstructions) {
       inst->Anaylze(this, ss);
    }
}

void Instruction::Anaylze(Option* option, std::stringstream& ss) {
    ss << "static bool trans_" << *mName << "(DisasContext *ctx, arg_" << *mName << " *a) {\n";
    mBlock->Analyze(option, ss);
    ss << "\treturn true;\n}\n";
}