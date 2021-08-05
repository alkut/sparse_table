#include "sparse_table.hpp"

int main()
{
    int n;
    std::cin>>n;
    std::vector<int> v(n);
    for (auto& it:v) 
    std::cin>>it;
    sp_t::sparse_table<int> table(v, [](const int& x, const int& y)
    {
        return std::max(x,y);
    });
    for (int i=0; i<n; ++i)
    {
        std::cout<<table.query(i, i+2)<<" ";
    }
    return 0;
}