#if !defined(__NODE_H__)
#define __NODE_H__

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "location.hh"


class Option;
class Instruction;
class OptNode;
class OptValueNode;
class OptDecl;
class OptStatement;

template<typename T>
class OptNodeList {
    struct delete_object {
        void operator()(T* ptr) { delete ptr; }
    };

public: 
    OptNodeList(T* node) {
        mArgs.push_back(node);
    }
    ~OptNodeList() {
        std::for_each(mArgs.begin(), mArgs.end(), delete_object());
    }
    OptNodeList<T> *Add(T* add) {
        mArgs.push_back(add);
        return this;
    }
/*
    template<typename Fn>
    void for_each(const Fn& func) {
        std::for_each(mArgs.begin(), mArgs.end(), func);
    }

    template<typename Fn>
    void for_each_rev(const Fn& func) {
        std::for_each(mArgs.rbegin(), mArgs.rend(), func);
    }
*/
    size_t Size() const { return mArgs.size(); }
    T* Get(size_t idx) { return mArgs[idx]; }
    T* operator[](size_t idx) { return mArgs[idx]; }
    const T* Get(size_t idx) const { return mArgs[idx]; }
    const T* operator[](size_t idx) const { return mArgs[idx]; }

private:
    std::vector<T*> mArgs;
};

typedef OptNodeList<OptNode>        OptArgs;
typedef OptNodeList<OptDecl>        OptDeclList;
typedef OptNodeList<OptStatement>   OptStateList;  

enum class OPCODE : int {
    OP_LOGAND,
    OP_LOGOR,
    OP_EQ,
    OP_NE,
    OP_GT,
    OP_GE,
    OP_LT,
    OP_LE,
    OP_VALUE,
    OP_CONST,
    OP_FUNCTION,
};

class OptNode {
public:
    OptNode(const yy::location& l, OPCODE op, OptNode* left, OptNode* right = nullptr)
        :mL(l), mOp(op), mLeft(left), mRight(right), mValue(0), mString(nullptr)
    {}
    OptNode(const yy::location& l, OPCODE op, int value)
        :mL(l), mOp(op), mLeft(nullptr), mRight(nullptr), mValue(value), mString(nullptr)
    {}
    OptNode(const yy::location& l, OPCODE op, std::string* str)
        :mL(l), mOp(op), mLeft(nullptr), mRight(nullptr), mValue(0), mString(str)
    {}
    OptNode(const yy::location& l, OPCODE op, std::string* str, OptNode* node)
        :mL(l), mOp(op), mLeft(node), mRight(nullptr), mValue(0), mString(str)
    {}
    virtual ~OptNode() {
        delete mLeft;
        delete mRight;
        delete mString;
    }

    virtual int Push(Option* option) const;
    virtual int Pop(Option* option) const;

    const yy::location& Location() const { return mL; }
    OPCODE Op() const { return mOp; }
    int Value() const { return mValue; }
    const std::string& String() const { return *mString; }
    const std::string* StringPtr() const { return mString; }
    const OptNode* Left() const { return mLeft; }
    const OptNode* Right() const { return mRight; }

    virtual void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth, int& times);

    static OptNode* MakeNode(Option& option, const yy::location& l, 
        OPCODE op, OptNode* left, OptNode* right = nullptr);

protected:
    const yy::location mL;
    OPCODE mOp;
    int mValue;
    std::string* mString;
    OptNode* mLeft;
    OptNode* mRight;
};

class OptValueNode : public OptNode {
public:
    OptValueNode(const yy::location& l, std::string* name, OptNode* node = nullptr)
        :OptNode(l, OPCODE::OP_VALUE, name, node)
    {}

    void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth, int& times);

    int Push(Option* option) const;
    int Pop(Option* option) const;
};

class OptFunctionNode : public OptNode {
public:
    OptFunctionNode(const yy::location& l, std::string* name, OptArgs* args)
        :OptNode(l, OPCODE::OP_FUNCTION, name), mArgs(args)
    {}
    ~OptFunctionNode() {
        delete mArgs;
    }

    void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth, int& times);

    int Push(Option* option) const;
    int Pop(Option* option) const;

private:
    OptArgs* mArgs;
};

class OptLet {
public:
    OptLet(const yy::location& l, int op, OptNode* value, OptNode* expr) 
        :mL(l), mOp(op), mValue(value), mExpr(expr)
    {}
    ~OptLet() {
        delete mValue;
        delete mExpr;
    }

    void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth);
    void PushValue(Option* option) { mValue->Push(option); }
    void PopValue(Option* option) { mValue->Pop(option); }

private:
    const yy::location mL;
    int mOp;
    OptNode* mValue;
    OptNode* mExpr;
};

class OptDecl {
public:
    OptDecl(OptValueNode* value)
        :mValue(value)
    {}
    ~OptDecl() {
        delete mValue;
    }

    void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth);
    
private:
    OptValueNode* mValue;
};

class OptStateBlock {
public:
    OptStateBlock(OptDeclList* decls, OptStateList* states)
        :mDecls(decls), mStates(states)
    {}
    ~OptStateBlock() {
        delete mDecls;
        delete mStates;
    }

    void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth);

private:
    OptDeclList* mDecls;
    OptStateList* mStates;
};

struct case_action_param {
    Option* opt_;
    int& default_label;
    case_action_param(Option* opt, int& label)
        :opt_(opt), default_label(label)
    {}
};

class OptStatement {
public:
    enum {
        NOP,
        ASSIGN,
        FUNCTION,
        IF,
        WHILE,
        BLOCK,
        LOAD,
        STORE,
    };

public:
    OptStatement(const yy::location& l, int code)
        :mL(l), mCode(code)
    {}
    virtual ~OptStatement() {

    }

    virtual void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) = 0;
//    virtual void case_analyze(case_action_param) {
//
//    }

protected:
    const yy::location& mL;
    int mCode;
};

class OptNopStatement : public OptStatement {
public:
    OptNopStatement(const yy::location& l)
        :OptStatement(l, NOP)
    {}
    virtual void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth);
};

class OptLetStatement : public OptStatement {
public:
    OptLetStatement(const yy::location& l, OptLet* assign)
        :OptStatement(l, ASSIGN), mAssign(assign)
    {}
    ~OptLetStatement() {
        delete mAssign;
    }

    virtual void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth);

private:
    OptLet* mAssign;
};

class OptFunctionStatement : public OptStatement {
public:
    OptFunctionStatement(const yy::location& l, std::string* name, OptArgs* args)
        :OptStatement(l, FUNCTION), mNode(l, name, args)
    {}
    ~OptFunctionStatement() {

    }
    virtual void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth);

private:
    OptFunctionNode mNode;
};

class OptIfStatement : public OptStatement {
public:
    OptIfStatement(const yy::location& l, OptNode* expr, OptStatement* then_statement, 
        OptStatement* else_statement = nullptr)
        :OptStatement(l, IF), mExpr(expr)
        ,mThenStatement(then_statement),mElseStatement(else_statement)
    {}
    ~OptIfStatement() {
        delete mExpr;
        delete mThenStatement;
        delete mElseStatement;
    }

    virtual void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth);

private:
    OptNode* mExpr;
    OptStatement* mThenStatement;
    OptStatement* mElseStatement;
};

class OptWhileStatement : public OptStatement {
public:
    OptWhileStatement(const yy::location& l, OptNode* expr, OptStatement* statement) 
        :OptStatement(l, WHILE), mExpr(expr), mStatement(statement)
    {}
    ~OptWhileStatement() {
        delete mExpr;
        delete mStatement;
    }

    virtual void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth);

private:
    OptNode* mExpr;
    OptStatement* mStatement;
};

class OptBlockStatement : public OptStatement {
public:
    OptBlockStatement(const yy::location& l, OptStateBlock* block)
        :OptStatement(l, BLOCK), mBlock(block)
    {}

    ~OptBlockStatement() {
        delete mBlock;
    }

    virtual void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth);

private:
    OptStateBlock* mBlock;
};

class OptLoadStatement : public OptStatement {
public:
    OptLoadStatement(const yy::location& l, OptValueNode* rd, OptValueNode* addr)
        :OptStatement(l, LOAD), mrd(rd), mAddr(addr)
    {}
    ~OptLoadStatement() {
        delete mrd;
        delete mAddr;
    }

    virtual void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth);

private:
    OptValueNode* mrd;
    OptValueNode* mAddr;
};

class OptStoreStatement : public OptStatement {
public:
    OptStoreStatement(const yy::location& l, OptValueNode* rs1, OptValueNode* addr)
        :OptStatement(l, STORE), mrs1(rs1), mAddr(addr)
    {}
    ~OptStoreStatement() {
        delete mrs1;
        delete mAddr;
    }

    virtual void Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth);

private:
    OptValueNode* mrs1;
    OptValueNode* mAddr;
};

#endif //!__NODE_H__