#include "Node.h"
#include "Option.h"
#include "Translater.h"


OptNode* OptNode::MakeNode(Option& option, const yy::location& l, OPCODE op, OptNode* left, OptNode* right) {
    if(right == nullptr) {
        switch(op) {
            case OPCODE::OP_NEG:
                if(left->mOp == OPCODE::OP_CONST) {
                    left->mValue = -left->mValue;
                    return left;
                }
            break;
        }
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


void OptNode::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth, int& times) {

    if(mOp == OPCODE::OP_CONST) {
        for(int i = 0; i < depth; ++i) 
            ss << '\t';
        ss << "tcg_gen_movi_tl(tmp" << times++ << ", " << mValue << ");\n";
        return;
    } else if(mOp == OPCODE::OP_NEG) {
        if(mLeft->Op() == OPCODE::OP_VALUE) {
            for(int i = 0; i < depth; ++i) 
                ss << '\t';
            ss << "tcg_gen_neg_tl(tmp" << times++ << ", " << mLeft->String() << ");\n";
        } else {
            mLeft->Analyze(option,inst, ss, depth, times);
            for(int i = 0; i < depth; ++i) 
                ss << '\t';
            ss << "tcg_gen_neg_tl(tmp" << times <<", tmp" << times - 1 << ");\n";
        ++times;
        }
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
        char islocalvalue1 = 0, islocalvalue2 = 0;
        int ret = inst->IsLocal(value1->String());
        if(ret < 0) {
            ret = option->GetTranslater()->IsGlobalRegister(value1->String());
            if(ret < 0)
                option->error(mL, "Unknown Local : " + value1->String());
        } else 
            islocalvalue1 = '_';
            
        if(value2 != nullptr) {
            ret = inst->IsLocal(value2->String());
            if(ret < 0) {
                ret = option->GetTranslater()->IsGlobalRegister(value2->String());
                if(ret < 0)
                    option->error(mL, "Unknown Local : " + value1->String());
            } else
                islocalvalue2 = '_';
                
        }

        for(int i = 0; i < depth; ++i)
            ss << '\t';

        std::stringstream args;
        args << value1->String() << (islocalvalue1 ? "_" : "") <<  ", ";
        if(value2 != nullptr)
            args << value2->String() << (islocalvalue2 ? "_" : "");
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
                    
                ss << "(ctx, tmp" << times++ << ", " << args.str() << ");";
                break;
            case OPCODE::OP_LOGOR:
                ss << "LOGICAL_OR";
                if(integier != nullptr) {
                    ss << "i";
                    option->GetTranslater()->UseHelper(Translater::HelperFlag::LOGICAL_ORi);
                } else 
                    option->GetTranslater()->UseHelper(Translater::HelperFlag::LOGICAL_OR);
                    
                ss << "(ctx, tmp" << times++ << ", " << args.str() << ");";
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
    char islocal = 0;
    int ret = inst->IsLocal(*mString);
    if(ret < 0) {
        ret = option->GetTranslater()->IsGlobalRegister(*mString);
        if(ret < 0)
            option->error(mL, "Unknown Local : " + *mString);
    } else 
        islocal = '_';

    for(int i = 0; i < depth; ++i)
        ss << '\t';
    ss << "tcg_gen_mov_tl(tmp" << times++ << ", " << *mString << (islocal ? "_" : "") << ");\n";
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
            case OPCODE::OP_VALUE: {
                char islocal = 0;
                int ret = inst->IsLocal(arg->String());
                if(ret < 0) {
                    ret = option->GetTranslater()->IsGlobalRegister(arg->String());
                    if(ret < 0)
                        option->error(mL, "Unknown Local : " + arg->String());
                } else
                    islocal = '_';
                for(int j = 0; j < depth; ++j)
                    ss << '\t';
                ss << "tcg_gen_mov_tl(a" << i << ", " << arg->String() << (islocal ? "_" : "") << ");\n";
            }
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
    ss << "TCGv " << mValue->String() << '_';
    switch(mKind) {
        case Kind::LOCAL:
            ss << " = tcg_temp_new();\n";
            break;
        case Kind::RD:
            ss << " = get_gpr(ctx, a->rd, EXT_NONE);\n";
            break;
        case Kind::RS1:
            ss << " = get_gpr(ctx, a->rs1, EXT_NONE);\n";
            break;
        case Kind::RS2:
            ss << " = get_gpr(ctx, a->rs2, EXT_NONE);\n";
            break;
    }
    
    inst->AddLocal(mValue->StringPtr(), 0);
}
    

void OptLet::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    char islocalmValue = 0;
    int ret = inst->IsLocal(mValue->String());
    if(ret < 0) {
        ret = option->GetTranslater()->IsGlobalRegister(mValue->String());
        if(ret < 0)
            option->error(mL, "Unknown Local : " + mValue->String());
    } else 
        islocalmValue = '_';
        

    if(mExpr->Op() == OPCODE::OP_CONST) {
        for(int i = 0; i < depth; ++i)
            ss << '\t';
        switch(mOp) {
            case '=':
                ss << "tcg_gen_movi_tl(" << mValue->String() << (islocalmValue ? "_" : "") << ", " << mExpr->Value() << ");\n";
                break;
            case '+':
                ss  << "tcg_gen_addi_tl(" << mValue->String() << (islocalmValue ? "_" : "") << ", " 
                    << mValue->String() << (islocalmValue ? "_" : "") << ", " << mExpr->Value() << ");\n";
                break;
            case '-':
                ss  << "tcg_gen_addi_tl(" << mValue->String() << (islocalmValue ? "_" : "") << ", " 
                    << mValue->String() << (islocalmValue ? "_" : "") << ", -(" << mExpr->Value() << "));\n";
                break;
        }
    } else if (mExpr->Op() == OPCODE::OP_VALUE) {
        char islocalmExpr = 0;
        ret = inst->IsLocal(mExpr->String());
        if(ret < 0) {
            ret = option->GetTranslater()->IsGlobalRegister(mExpr->String());
            if(ret < 0)
                option->error(mL, "Unknown Local : " + mExpr->String());
        } else 
            islocalmExpr = '_';

        for(int i = 0; i < depth; ++i)
            ss << '\t';
        switch(mOp) {
            case '=':
                ss  << "tcg_gen_mov_tl(" << mValue->String() << (islocalmValue ? "_" : "") << ", " 
                    << mExpr->String() << (islocalmExpr ? "_" : "") << ");\n";
                break;
            case '+':
                ss  << "tcg_gen_add_tl(" << mValue->String() << (islocalmValue ? "_" : "") << ", " 
                    << mValue->String() << (islocalmValue ? "_" : "") << ", " << mExpr->String() << (islocalmExpr ? "_" : "") << ");\n";
                break;
            case '-':
                ss  << "tcg_gen_sub_tl(" << mValue->String() << (islocalmValue ? "_" : "") << ", " 
                    << mValue->String() << (islocalmValue ? "_" : "") << ", " << mExpr->String() << (islocalmExpr ? "_" : "") << ");\n";
                break;
        }
    } else {
        int times = 0;
        mExpr->Analyze(option, inst, ss, depth, times);
        inst->SetNumTmp(times);

        for(int i = 0; i < depth; ++i)
            ss << '\t';
        switch(mOp) {
            case '=':
                ss << "tcg_gen_mov_tl(" << mValue->String() << (islocalmValue ? "_" : "")  << ", tmp" << times - 1 << ");\n";
                break;
            case '+':
                ss  << "tcg_gen_add_tl(" << mValue->String() << (islocalmValue ? "_" : "") << ", " 
                    << mValue->String() << (islocalmValue ? "_" : "") << ", tmp" << times - 1 << ");\n";
                break;
            case '-':
                ss  << "tcg_gen_sub_tl(" << mValue->String() << (islocalmValue ? "_" : "") << ", " 
                    << mValue->String() << (islocalmValue ? "_" : "") << ", tmp" << times - 1 << ");\n";
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
}

void OptWhileStatement::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    int label1 = inst->SetLabel();
    int label2 = inst->SetLabel();
    int times = 0;
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
}

void OptBlockStatement::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    mBlock->Analyze(option, inst, ss, depth);
}

void OptLoadStatement::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    char islocalmrd = 0, islocalmAddr = 0;
    int ret = inst->IsLocal(mrd->String());
    if(ret < 0) {
        ret = option->GetTranslater()->IsGlobalRegister(mrd->String());
        if(ret < 0)
            option->error("Unknown Local : " + mrd->String());
    } else
        islocalmrd = '_';
        
    ret = inst->IsLocal(mAddr->String());
    if(ret < 0) {
        ret = option->GetTranslater()->IsGlobalRegister(mAddr->String());
        if(ret < 0)
            option->error("Unknown Local : " + mAddr->String());
    } else 
        islocalmAddr = '_';
        

    for(int i = 0; i < depth; ++i) 
        ss << '\t';
    ss << "tcg_gen_qemu_ld_tl(" << mrd->String() << (islocalmrd ? "_" : "") << ", " << mAddr->String() << (islocalmAddr ? "_" : "") << ", ctx->mem_idx, MO_TEUL);\n";
}

void OptStoreStatement::Analyze(Option* option, Instruction* inst, std::stringstream& ss, int depth) {
    char islocalmrs1 = 0, islocalmAddr = 0;
    int ret = inst->IsLocal(mrs1->String());
    if(ret < 0) {
        ret = option->GetTranslater()->IsGlobalRegister(mrs1->String());
        if(ret < 0)
            option->error("Unknown Local : " + mrs1->String());
    } else
        islocalmrs1 = '_';
        
    ret = inst->IsLocal(mAddr->String());
    if(ret < 0) {
        ret = option->GetTranslater()->IsGlobalRegister(mAddr->String());
        if(ret < 0)
            option->error("Unknown Local : " + mAddr->String());
    } else 
        islocalmAddr = '_';
    
    for(int i = 0; i < depth; ++i) 
        ss << '\t';
    ss << "tcg_gen_qemu_st_tl(" << mrs1->String() << (islocalmrs1 ? "_" : "") << ", " << mAddr->String() << (islocalmAddr ? "_" : "") << ", ctx->mem_idx, MO_TEUL);\n";
}

