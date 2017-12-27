// 1.5의 예제.

#include <iostream>
using namespace std;

template <class T>
struct OpNewCreator
{
    static T* Create()
    {
        cout << "OpNewCreator.Create" << endl;
        return new T;
    }
};

template <class T>
struct MallocCreator
{
    static T* Create()
    {
        cout << "MallocCreator.Create" << endl;
        void* buf = std::malloc(sizeof(T));
        if (!buf) return 0;
        return new(buf) T;  //이건 무슨 표현이지?
    }
};

template <class T>
struct PrototypeCreator
{
    PrototypeCreator(T* pObj = 0) : pPrototype_(pObj) {}
    T* Create()
    {
        cout << "PrototypeCreator.Create" << endl;
        return pPrototype_ ? pPrototype_->Clone() : 0;
    }
    T* GetPrototype() { return pPrototype_; }
    void SetPrototype(T* pObj) { pPrototype_ = pObj; }
    private:
    T* pPrototype_;
};

template <class CreationPolicy>
class WidgetManager : public CreationPolicy {};

int main (void) {
    typedef WidgetManager<OpNewCreator<int>> MyintManager;
    
    MyintManager mim;
    
    mim.Create();
    return 0;
}