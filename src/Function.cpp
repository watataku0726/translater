#include "Function.h"

#include <iostream>
#include <sstream>
#include <cassert>

Function::Function(int pos, const std::string& functionLabel) 
    :mStart(pos), mEnd(pos), mNumLabels(0)
{
    mLabels.clear();
    if(functionLabel.substr(0, 2) != "_Z"){
        mFunctionName = "";
        mNumArgs = 0;
        
    }
    else {
        int idx = 2;
        int len = 0;
        while('0' <= functionLabel[idx] && functionLabel[idx] <= '9') {
            ++idx;
        }
        assert(idx > 2);
        std::istringstream ss = std::istringstream(functionLabel.substr(2, idx - 2));
        ss >> len;
        mFunctionName = functionLabel.substr(idx, len);
        mNumArgs = functionLabel.size() - (idx + len);
    }   
}

Function::~Function() {
    for(Label* label : mLabels) 
        delete label;
}


void Function::SetEnd(int pos) {
    if(pos < mStart)
        mEnd = mStart;
    else
        mEnd = pos;
}

void Function::AddLabel(int pos, const std::string& name) {
    if(mStart < pos) {
        Label* label = new Label();
        label->pos = pos;
        label->name = std::string(name);
        mLabels.push_back(label);
        ++mNumLabels;
    }
}