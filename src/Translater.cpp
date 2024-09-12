#include "Translater.h"
#include "Option.h"
#include "Function.h"

Translater::Translater(const std::string& filename, const Option* option) 
    :mFileName(filename), mOption(option)
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

void Translater::RunLoop() {
    int i = 0;
    for( std::string str : mContents) {
        std::cout << i++ << " : " << str << std::endl;
    }

    for(Function *f : mFunctions) {
        std::cout << f->GetStart() << " " << f->GetEnd() << " " << f->GetNumArgs() << " "  << f->GetNumLabels() << std::endl;
    }
}

bool Translater::GetLabelName(const std::string& line, std::string &name, const char delimiter) {
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

    
    std::string functionLabel;
    if(!GetLabelName(line, functionLabel))
        return true;
    
    Function* f = new Function(pos, functionLabel);
    if(f->GetName()  == "") {
        std::cerr << "Unknown Function Format: " << functionLabel << std::endl;
        delete f;
        return false; 
    }
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
            std::cout << line << std::endl;
        }
    }

    return true;
}

