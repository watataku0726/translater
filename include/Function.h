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
    void SetMyNumber(int number) { mNumber = number; }
    void SetMainStackSize(int size) { mMainStackSize = size; };
    void IncNumArgStacks(int size) { ++mNumArgStacks; WriteArgStack = true; mCurArgStackSize = size; }

    //void AbletoWriteArgStack() { WriteArgStack = true; }
    void NotAbletoWriteArgStack() { WriteArgStack = false; mCurArgStackSize = 0; }

    int GetStart() const { return mStart; }
    int GetEnd() const { return mEnd; }
    int GetNumLabels() const { return mNumLabels; }
    int GetNumArgs() const { return mNumArgs; }
    int GetMyNumber() const { return mNumber; }
    int GetMainStackSize() const { return mMainStackSize; }
    int GetNumArgStacks() const { return mNumArgStacks; }
    int GetCurArgStackSize() const { return mCurArgStackSize; }
    bool IsArgStackWriten() const { return WriteArgStack; }
    const std::string& GetName() const { return mFunctionName; }
    const std::vector<Label*>& GetLabels() const { return mLabels; }
private:
    std::string mFunctionName;
    std::vector<Label*> mLabels;
    int mNumber;
    int mStart;
    int mEnd;
    int mNumLabels;
    int mNumArgs;
    int mMainStackSize;

    int mNumArgStacks;
    int mCurArgStackSize;
    bool WriteArgStack;

};

#endif //!__FUNCTION_H__