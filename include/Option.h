#if !defined(__OPTION_H__)
#define __OPTION_H__

#include <stack>
#include "parser.hh"
#include "Node.h"
#include "Translater.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

class Option;

#define YY_DECL                             \
    yy::parser::token_type                  \
    yylex(yy::parser::semantic_type* yylval, \
    yy::parser::location_type* yylloc,      \
    Option& driver)

YY_DECL;

class Instruction {
public:
    Instruction(const std::string* name, OptStateBlock* states)
        :mName(name), mBlock(states), mNumTmp(0), mNumA(0), mNumLabel(0)
    {   
        mLocals.emplace("rd", 0);
        mLocals.emplace("rs1", 0);
        mLocals.emplace("rs2", 0);
    }
    ~Instruction() {
        delete mName;
        delete mBlock;
        mLocals.clear();
    }

    void Anaylze(Option* option, std::stringstream& ss);
    void AddLocal(const std::string* local, int size) { mLocals.emplace(*local, size); }
    int IsLocal(const Option* option, const std::string& local);
    void SetNumTmp(int num) { mNumTmp = mNumTmp > num ? mNumTmp : num; }
    void SetNumA(int num) { mNumA= mNumA > num ? mNumA : num; }
    int SetLabel() { return mNumLabel++; } 
private:
    std::map<std::string, int> mLocals;
    const std::string* mName;
    OptStateBlock* mBlock;
    int mNumTmp;
    int mNumA;
    int mNumLabel;
};

class Option {
public:
    Option(Translater* translater);
    virtual ~Option();

    std::string& GetFileName() { return mFileName; }
    const std::string& GetProjectName() const; 
    bool compile(const std::string& f);

    void DefineInstruction(const yy::location& l, const std::string* name, OptStateBlock* block);
    void DefineRegister(const yy::location& l, const std::string* name);
    void SetProjectName(const yy::location& l, const std::string* name) { mProjectName = name; }

    void error(const yy::location& l, const std::string& m);
    void error(const std::string& m);

    //const std::vector<const std::string*> GetRegisters() const { return mRegisters; }
    const Translater* GetTranslater() const { return mTranslater; }
    void WriteInstruction(std::stringstream& ss);
private:
    void scan_begin();
    void scan_end();

private:
    std::string mFileName;
    std::vector<Instruction*> mInstructions;
    //std::vector<const std::string*> mRegisters;
    const std::string* mProjectName;
    Translater* mTranslater;
    int mErrorCount;

};

#endif //!__OPTION_H__