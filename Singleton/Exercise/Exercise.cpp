#include <functional>
using namespace std;

struct SingletonTester
{
    template <typename T>
    bool is_singleton(function<T *()> factory)
    {
        T *_1 = factory();
        T *_2 = factory();
        return _1 == _2;
    }
};