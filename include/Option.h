#if !defined(__OPTION_H__)
#define __OPTION_H__

#include <stack>
#include "parser.hh"
#include "Node.h"

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
        :mName(name), mBlock(states)
    {}
    ~Instruction() {
        delete mName;
        delete mBlock;
    }

    void Anaylze(Option* option, std::stringstream& ss);

private:
    const std::string* mName;
    OptStateBlock* mBlock;
};

class Option {
public:
    Option();
    virtual ~Option();

    std::string& GetFileName() { return mFileName; }
    bool compile(const std::string& f);

    void DefineInstruction(const yy::location& l, const std::string* name, OptStateBlock* block);
    void DefineRegister(const yy::location& l, const std::string* name);

    void error(const yy::location& l, const std::string& m);
    void error(const std::string& m);

    const std::vector<const std::string*> GetRegisters() const { return mRegisters; }
    void WriteInstruction(std::stringstream& ss);
private:
    void scan_begin();
    void scan_end();

private:
    std::vector<Instruction*> mInstructions;
    std::vector<const std::string*> mRegisters;
    int mErrorCount;

    std::string mFileName;
};

#endif //!__OPTION_H__