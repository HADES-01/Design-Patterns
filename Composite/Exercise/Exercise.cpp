#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

struct BaseValues
{
    virtual int sum() = 0;
};

struct SingleValue : BaseValues
{
    int val{0};
    SingleValue(int val) : val(val) {}
    int sum() override { return val; }
};

struct ManyValues : BaseValues
{
    vector<BaseValues *> vals;
    ManyValues() {}
    ManyValues(initializer_list<BaseValues *> list) : vals(list) {}

    void add(int val)
    {
        vals.push_back(new SingleValue{val});
    }

    int sum() override
    {
        int res = 0;
        for (auto a : vals)
            res += a->sum();
        return res;
    }
};

int sum(ManyValues &&vals)
{
    return vals.sum();
}