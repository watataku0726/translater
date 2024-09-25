#include "Node.h"
#include "Option.h"

OptNode* OptNode::MakeNode(Option& option, const yy::location& l, OPCODE op, OptNode* left, OptNode* right) {
    if(right == nullptr) {
        return new OptNode(l, op, left);
    }

    if(left->mOp == OPCODE::OP_CONST && right->mOp == OPCODE::OP_CONST) {
        switch(op) {
            case OPCODE::OP_LOGAND:
                left->mValue = (left->mValue && right->mValue) ? 1 : 0;
                break;
            case OPCODE::OP_LOGOR:
                left->mValue = (left->mValue || right->mValue) ? 1 : 0;
                break;
            case OPCODE::OP_EQ:
                left->mValue = (left->mValue == right->mValue) ? 1 : 0;
                break;
            case OPCODE::OP_NE:
                left->mValue = (left->mValue != right->mValue) ? 1 : 0;
                break;
            case OPCODE::OP_GT:
                left->mValue = (left->mValue > right->mValue) ? 1 : 0;
                break;
            case OPCODE::OP_GE:
                left->mValue = (left->mValue >= right->mValue) ? 1 : 0;
                break;
            case OPCODE::OP_LT:
                left->mValue = (left->mValue < right->mValue) ? 1 : 0;
                break;
            case OPCODE::OP_LE:
                left->mValue = (left->mValue <= right->mValue) ? 1 : 0;
                break;

            default:
                return new OptNode(l, op, left, right);
        }
        delete right;
        return left;
    }

    return new OptNode(l, op, left, right);
}

int OptNode::Push(Option* opt) const {
    return 0;
}

int OptNode::Pop(Option* opt) const {
    return 0;
}

int OptValueNode::Push(Option* opt) const {
    return 0;
}

int OptValueNode::Pop(Option* opt) const {
    return 0;
}

int OptFunctionNode::Push(Option* opt) const {
    return 0;
}

int OptFunctionNode::Pop(Option* opt) const {
    return 0;
}

void OptLet::Analyze(Option* opt, std::stringstream& ss) {

}

void OptNopStatement::Analyze(Option* opt, std::stringstream& ss) {
    
}

void OptLetStatement::Analyze(Option* opt, std::stringstream& ss) {
    
}

void OptFunctionStatement::Analyze(Option* opt, std::stringstream& ss) {
    
}

void OptIfStatement::Analyze(Option* opt, std::stringstream& ss) {
    
}

void OptWhileStatement::Analyze(Option* opt, std::stringstream& ss) {
    
}

void OptBlockStatement::Analyze(Option* opt, std::stringstream& ss) {
    
}

void OptLoadStatement::Analyze(Option* opt, std::stringstream& ss) {
    
}

void OptStoreStatement::Analyze(Option* opt, std::stringstream& ss) {
    
}