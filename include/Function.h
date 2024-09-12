#if !defined(__FUNCTION_H__)
#define __FUNCTION_H__

#include <vector>
#include <string>

struct Label {
    int pos;
    std::string name;
};

class Function {
public:
    Function(int pos, const std::string& functionLabel);
    ~Function();

    void AddLabel(int pos, const std::string& name);
    void SetEnd(int pos);

    int GetStart() const { return mStart; }
    int GetEnd() const { return mEnd; }
    int GetNumLabels() const { return mNumLabels; }
    int GetNumArgs() const { return mNumArgs; }
    const std::string& GetName() const { return mFunctionName; }
private:
    std::string mFunctionName;
    int mStart;
    int mEnd;
    int mNumLabels;
    int mNumArgs;
    std::vector<Label*> mLabels;
};

#endif //!__FUNCTION_H__