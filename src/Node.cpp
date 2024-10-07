#include "Node.h"
#include "Option.h"
#include "Translater.h"

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

void OptNode::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth, int& times) {

    if(mOp == OPCODE::OP_CONST) {
        for(int i = 0; i < depth; ++i) 
            ss << '\t';
        ss << "tcg_gen_movi_tl(tmp" << times++ << ", " << mValue << ");\n";
        return;
    }
    
    OptNode *value1 = nullptr, *value2 = nullptr, *integier = nullptr;
    if(mLeft->Op() == OPCODE::OP_CONST && mRight->Op() == OPCODE::OP_VALUE) {
        value1 = mRight;
        value2 = nullptr;
        integier = mLeft;
    } else if(mLeft->Op() == OPCODE::OP_VALUE && mRight->Op() == OPCODE::OP_CONST) {
        value1 = mLeft;
        value2 = nullptr;
        integier = mRight;
    } else if(mLeft->Op() == OPCODE::OP_VALUE && mRight->Op() == OPCODE::OP_VALUE) {
        value1 = mLeft;
        value2 = mRight;
        integier = nullptr;
    }

    if(value1 != nullptr) {
        int ret = inst->IsLocal(option, value1->String());
        if(ret < 0)
            option->error(mL, "Unknown Local : " + value1->String());
        if(value2 != nullptr) {
            ret = inst->IsLocal(option, value1->String());
            if(ret < 0)
                option->error(mL, "Unknown Local : " + value1->String());
        }

        for(int i = 0; i < depth; ++i)
            ss << '\t';

        std::stringstream args;
        args << value1->String() + ", ";
        if(value2 != nullptr)
            args << value2->String();
        else if(integier != nullptr)
            args << integier->Value();

        switch(mOp) {
            case OPCODE::OP_LOGAND:
                ss << "LOGICAL_AND";
                if(integier != nullptr) {
                    ss << "i";
                    option->GetTranslater()->UseHelper(Translater::HelperFlag::LOGICAL_ANDi);
                } else 
                    option->GetTranslater()->UseHelper(Translater::HelperFlag::LOGICAL_AND);
                    
                ss << "(tmp" << times++ << ", " << args.str() << ");";
                break;
            case OPCODE::OP_LOGOR:
                ss << "LOGICAL_OR";
                if(integier != nullptr) {
                    ss << "i";
                    option->GetTranslater()->UseHelper(Translater::HelperFlag::LOGICAL_ORi);
                } else 
                    option->GetTranslater()->UseHelper(Translater::HelperFlag::LOGICAL_OR);
                    
                ss << "(tmp" << times++ << ", " << args.str() << ");";
                break;
            case OPCODE::OP_EQ:
                ss << "tcg_gen_setcond";
                if(integier != nullptr)
                    ss << "i";
                ss << "_tl(TCG_COND_EQ, tmp" << times++ << ", "<< args.str() <<");";
                break;
            case OPCODE::OP_NE:
                ss << "tcg_gen_setcond";
                if(integier != nullptr)
                    ss << "i";
                ss << "_tl(TCG_COND_NE, tmp" << times++ << ", "<< args.str() <<");";
                break;
            case OPCODE::OP_GT:
                ss << "tcg_gen_setcond";
                if(integier != nullptr)
                    ss << "i";
                ss << "_tl(TCG_COND_";
                if(value1 == mLeft)
                    ss << "GT";
                else
                    ss << "LT";
                ss << ", tmp" << times++ << ", "<< args.str() <<");";
                break;
            case OPCODE::OP_GE:
                ss << "tcg_gen_setcond";
                if(integier != nullptr)
                    ss << "i";
                ss << "_tl(TCG_COND_";
                if(value1 == mLeft)
                    ss << "GE";
                else
                    ss << "LE";
                ss << ", tmp" << times++ << ", "<< args.str() <<");";
                break;
            case OPCODE::OP_LT:
                ss << "tcg_gen_setcond";
                if(integier != nullptr)
                    ss << "i";
                ss << "_tl(TCG_COND_";
                if(value1 == mLeft)
                    ss << "LT";
                else
                    ss << "GT";
                ss << ", tmp" << times++ << ", "<< args.str() <<");";
                break;
            case OPCODE::OP_LE:
                ss << "tcg_gen_setcond";
                if(integier != nullptr)
                    ss << "i";
                ss << "_tl(TCG_COND_";
                if(value1 == mLeft)
                    ss << "LE";
                else
                    ss << "GE";
                ss << ", tmp" << times++ << ", "<< args.str() <<");";
                break;
            default:
                option->error(mL, "Unknown OPCODE");
                break;
        }
        ss << "\n";
    } else {
        mLeft->Analyze(option, inst, ss, depth, times);
        mRight->Analyze(option, inst, ss, depth, times);

        for(int i = 0; i < depth; ++i)
            ss << '\t';

        std::stringstream args;
        args <<  "tmp" << times  << ", tmp" << times - 2 << ", tmp" << times - 1 << ");";
        ++times;
        switch(mOp) {
            case OPCODE::OP_LOGAND:
                ss << "LOGICAL_AND(" << args.str();
                option->GetTranslater()->UseHelper(Translater::HelperFlag::LOGICAL_AND);
                break;
            case OPCODE::OP_LOGOR:
                ss << "LOGICAL_OR(" << args.str();
                option->GetTranslater()->UseHelper(Translater::HelperFlag::LOGICAL_OR);
                break;
            case OPCODE::OP_EQ:
                ss << "tcg_gen_setcond_tl(TCG_COND_EQ, " << args.str();
                break;
            case OPCODE::OP_NE:
                ss << "tcg_gen_setcond_tl(TCG_COND_NE, " << args.str();
                break;
            case OPCODE::OP_GT:
                ss << "tcg_gen_setcond_tl(TCG_COND_GT, " << args.str();
                break;
            case OPCODE::OP_GE:
                ss << "tcg_gen_setcond_tl(TCG_COND_GE, " << args.str();
                break;
            case OPCODE::OP_LT:
                ss << "tcg_gen_setcond_tl(TCG_COND_LT, " << args.str();
                break;
            case OPCODE::OP_LE:
                ss << "tcg_gen_setcond_tl(TCG_COND_LE, " << args.str();
                break;
            default:
                option->error(mL, "Unknown OPCODE");
                break;
        }
        ss << "\n";
    }
}

void OptValueNode::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth, int& times) {
    int ret = inst->IsLocal(option, *mString);
    if(ret < 0) {
        option->error(mL, "Unknown Local : " + *mString);
        //return;
    }

    for(int i = 0; i < depth; ++i)
        ss << '\t';
    ss << "tcg_gen_mov_tl(tmp" << times++ << ", " << *mString << ");\n";
}

void OptFunctionNode::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth, int& times) {
    int args = option->GetTranslater()->IsFunction(*mString);
    if(args < 0) {
        option->error(mL, "Unknown Function : " + *mString);
        return;
    }

    int numArgs = 0;
    if(mArgs) numArgs = mArgs->Size();        

    if(numArgs != args) {
        option->error(mL, "Defferent number of Arguments: " + *mString);
        return;
    }
    inst->SetNumA(numArgs);
    for(int i = 0, e = numArgs > NUMBER_OF_A_REGISTERS ? NUMBER_OF_A_REGISTERS : numArgs; i < e;  ++i) {
        OptNode* arg = mArgs->Get(i);
        switch(arg->Op()) {
            case OPCODE::OP_CONST:
                for(int j = 0; j < depth; ++j)
                    ss << '\t';
                ss << "tcg_gen_movi_tl(a" << i << ", " << arg->Value() << ");\n";
                break;
            case OPCODE::OP_VALUE:
                for(int j = 0; j < depth; ++j)
                    ss << '\t';
                ss << "tcg_gen_mov_tl(a" << i << ", " << arg->String() << ");\n";
                break;
            default:
                arg->Analyze(option, inst, ss, depth, times);
                for(int j = 0; j < depth; ++j)
                    ss << '\t';
                ss << "tcg_gen_mov_tl(a" << i << ", tmp" << times - 1 << ");\n";
                break;
        }
    }

    for(int i = NUMBER_OF_A_REGISTERS; i < numArgs; ++i) {
        OptNode* arg = mArgs->Get(i);
        switch(arg->Op()) {
            case OPCODE::OP_CONST:
                for(int j = 0; j < depth; ++j)
                    ss << '\t';
                ss << "tcg_gen_movi_tl(arg_sp[" << i - numArgs<< "], " << arg->Value() << ");\n";
                break;
            case OPCODE::OP_VALUE:
                for(int j = 0; j < depth; ++j)
                    ss << '\t';
                ss << "tcg_gen_mov_tl(arg_sp[" << i - numArgs << "], " << arg->String() << ");\n";
                break;
            default:
                arg->Analyze(option, inst, ss, depth, times);
                for(int j = 0; j < depth; ++j)
                    ss << '\t';
                ss << "tcg_gen_mov_tl(arg_sp[" << i - numArgs << "], tmp" << times - 1 << ");\n";
                break;
        }
    }

    for(int i = 0; i < depth; ++i)
        ss << '\t';
    ss << *mString << "(ctx, r0";
    for(int i = 0, e = numArgs > NUMBER_OF_A_REGISTERS ? NUMBER_OF_A_REGISTERS : numArgs; i < e;  ++i) {

        ss << ", a" << i;
    }

    if(numArgs > NUMBER_OF_A_REGISTERS)
        ss << ", arg_sp";

    ss << ");\n";
    for(int i = 0; i < depth; ++i)
        ss << '\t';
    ss << "tcg_gen_mov_tl(tmp" << times++ <<  ", r0);\n";
}

void OptDecl::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    for(int i = 0; i < depth; ++i)
        ss << '\t';
    ss << "TCGv " << mValue->String() << " = tcg_temp_new();\n";
    inst->AddLocal(mValue->StringPtr(), 0);
}
    

void OptLet::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    if(inst->IsLocal(option, mValue->String()) == -1)
        option->error(mL, "Unknown Local : " + mValue->String());

    if(mExpr->Op() == OPCODE::OP_CONST) {
        for(int i = 0; i < depth; ++i)
            ss << '\t';
        switch(mOp) {
            case '=':
                ss << "tcg_gen_movi_tl(" << mValue->String() << ", " << mExpr->Value() << ");\n";
                break;
            case '+':
                ss << "tcg_gen_addi_tl(" << mValue->String() << ", " << mValue->String() << ", " << mExpr->Value() << ");\n";
                break;
            case '-':
                ss << "tcg_gen_addi_tl(" << mValue->String() << ", " << mValue->String() << ", -(" << mExpr->Value() << "));\n";
                break;
        }
    } else if (mExpr->Op() == OPCODE::OP_VALUE) {
        for(int i = 0; i < depth; ++i)
            ss << '\t';
        switch(mOp) {
            case '=':
                ss << "tcg_gen_mov_tl(" << mValue->String() << ", " << mExpr->String() << ");\n";
                break;
            case '+':
                ss << "tcg_gen_add_tl(" << mValue->String() << ", " << mValue->String() << ", " << mExpr->String() << ");\n";
                break;
            case '-':
                ss << "tcg_gen_sub_tl(" << mValue->String() << ", " << mValue->String() << ", " << mExpr->String() << ");\n";
                break;
        }
    }else {
        int times = 0;
        mExpr->Analyze(option, inst, ss, depth, times);
        inst->SetNumTmp(times);

        for(int i = 0; i < depth; ++i)
            ss << '\t';
        switch(mOp) {
            case '=':
                ss << "tcg_gen_mov_tl(" << mValue->String() << ", tmp" << times - 1 << ");\n";
                break;
            case '+':
                ss << "tcg_gen_add_tl(" << mValue->String() << ", " << mValue->String() << ", tmp" << times - 1 << ");\n";
                break;
            case '-':
                ss << "tcg_gen_sub_tl(" << mValue->String() << ", " << mValue->String() << ", tmp" << times - 1 << ");\n";
                break;
        }
    }
    
}

void OptStateBlock::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    if(mDecls) {
        for(int i = 0, e = mDecls->Size(); i < e; ++i) {
            mDecls->Get(i)->Analyze(option, inst, ss, depth);
        }
        ss << '\n';
    }
   
    if(mStates) {
        for(int i = 0, e = mStates->Size(); i < e; ++i) {
            mStates->Get(i)->Analyze(option, inst, ss, depth);
        }
    }
}

void OptNopStatement::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    
}

void OptLetStatement::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {

    
    mAssign->Analyze(option, inst, ss, depth);

}

void OptFunctionStatement::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    int times = 0;
    mNode.Analyze(option,inst, ss, depth, times);
    inst->SetNumTmp(times);
}

void OptIfStatement::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    int times = 0;
    mExpr->Analyze(option, inst, ss, depth, times);
    inst->SetNumTmp(times);
    int label1 = inst->SetLabel();
    //ss << "//If Statement\n";
    for(int i = 0; i < depth; ++i)
        ss << '\t';
    ss << "tcg_gen_brcondi_tl(TCG_COND_EQ, tmp" << times - 1 << ", 0, label" << label1 << ");\n";
    mThenStatement->Analyze(option, inst, ss, depth);
    if(mElseStatement) {
        int label2 = inst->SetLabel();
        for(int i = 0; i < depth; ++i)
            ss << '\t';
        ss << "tcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, label" << label2 << ");\n\n";
        for(int i = 0; i < depth; ++i)
            ss << '\t';
        ss << "gen_set_label(label" << label1 << ");\n";
        mElseStatement->Analyze(option, inst, ss, depth);
        ss << '\n';
        for(int i = 0; i < depth; ++i)
            ss << '\t';
        ss << "gen_set_label(label" << label2 << ");\n";
    } else {
        ss << '\n';
       for(int i = 0; i < depth; ++i)
            ss << '\t';
        ss << "gen_set_label(label" << label1 << ");\n"; 
    }
    //ss << "//If Statement End\n";
}

void OptWhileStatement::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    int label1 = inst->SetLabel();
    int label2 = inst->SetLabel();
    int times = 0;
    //ss << "//While Statement\n";
    ss << '\n';
    for(int i = 0; i < depth; ++i)
        ss << '\t';
    ss << "gen_set_label(label" << label1 << ");\n";
    mExpr->Analyze(option, inst, ss, depth, times);
    for(int i = 0; i < depth; ++i)
        ss << '\t';
    ss << "tcg_gen_brcondi_tl(TCG_COND_EQ, tmp" << times - 1 << ", 0, label" << label2 << ");\n";
    mStatement->Analyze(option, inst, ss, depth);
    for(int i = 0; i < depth; ++i)
        ss << '\t';
    ss << "tcg_gen_brcondi_tl(TCG_COND_ALWAYS, ctx->zero, 0, label" << label1 << ");\n";
    ss << '\n';
    for(int i = 0; i < depth; ++i)
        ss << '\t';
    ss << "gen_set_label(label" << label2 << ");\n";
    //ss << "//While Statement End\n";
}

void OptBlockStatement::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    mBlock->Analyze(option, inst, ss, depth);
}

void OptLoadStatement::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    if(inst->IsLocal(option, mrd->String()) == -1) 
        option->error("Unknown Local : " + mrd->String());

    if(inst->IsLocal(option, mAddr->String()) == -1) 
        option->error("Unknown Local : " + mAddr->String());

    for(int i = 0; i < depth; ++i) 
        ss << '\t';
    ss << "tcg_gen_qemu_ld_tl(" << mrd->String() << ", " << mAddr->String()  << ", ctx->mem_idx, MO_TUEL);\n";
}

void OptStoreStatement::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    if(inst->IsLocal(option, mrs1->String()) == -1) 
        option->error("Unknown Local : " + mrs1->String());

    if(inst->IsLocal(option, mAddr->String()) == -1) 
        option->error("Unknown Local : " + mAddr->String());
    
    for(int i = 0; i < depth; ++i) 
        ss << '\t';
    ss << "tcg_gen_qemu_st_tl(" << mrs1->String() << ", " << mAddr->String()  << ", ctx->mem_idx, MO_TUEL);\n";
}

