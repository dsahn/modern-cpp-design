// 1.5.1 의 예제.
// 템플릿 템플릿 인자를 통한 단위전략 클래스 구현

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

template <template <class Created> class CreationPolicy>
class WidgetManager : public CreationPolicy<int> {
    void Dosomething(/*args*/) {
        double* pD = CreationPolicy<double>().Create();
        // 내부에서 CreationPolicy 를 재사용 할 수있다.
    }
};
// 어차피 WidgetManager 를 만든 개발자가 어떤 타입에 대해서 들어올지 알고있기 
// 때문에 여기서 타입을 넣어주는듯?

int main (void) {
    // typedef WidgetManager<OpNewCreator<int>> MyintManager;
    // Creator의 인자를 명시적으로 넘겨주기는 불편한 동작임.
    // 여기서는 어떤 정책을 넣는지만 결정한다.
    typedef WidgetManager<OpNewCreator> MyintManager;
    
    MyintManager mim;
    
    int * pI = mim.Create();
    
    return 0;
}