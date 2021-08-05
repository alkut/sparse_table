#include <iostream>
#include <vector>
#include <functional>
#include <utility>

namespace sp_t 
{
template<class key_t, class f_t = std::function<key_t(const key_t&, const key_t&)>>
class sparse_table
{
    std::vector<std::vector<key_t>> table;
    std::vector<int> bin_logs;
    f_t fun;
    public:
    sparse_table(const std::vector<key_t>& v, f_t fun=f_t()) : fun(fun)
    {
        int n = v.size();
        int tmp=1;
        bin_logs.resize(n+1);
        bin_logs[0]=-1;
        for (int i=1; i<=n; ++i)
        {
            if (i==tmp)
            {
                tmp<<=1;
                bin_logs[i]=bin_logs[i-1]+1;
            }
            else
            {
                bin_logs[i]=bin_logs[i-1];
            }
        }
        table.push_back(v);
        for (int t=2; t<=n; t<<=1)
        {
            int level= bin_logs[t];
            std::vector<key_t> tmp_level;
            for (int i=0; i+t<=n; ++i)
            {
                tmp_level.push_back(fun(table[level-1][i], table[level-1][i+(t>>1)]));
            }
            table.push_back(std::move(tmp_level));
        }
    }
    key_t query(int l, int r);
};

template<class key_t, class f_t>
key_t sparse_table<key_t, f_t>::query(int l, int r) // half_interval
{
    if (l<0 || r>table[0].size() || r<=l)
    {
        std::cout<<"wrong boundaries"<<std::endl;
        return key_t();
    }
    int size=bin_logs[r-l];
    return fun(table[size][l], table[size][r-(1<<size)]);
}
}