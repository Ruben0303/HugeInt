#include"huge_int.h"
#include<iostream>
#include<vector>
#include<string>

int main()
{
    HugeInt a("1111111111111119999999999911111111");
    HugeInt b("-98888888899999999999999999999999999999999999999999999999999999999999999999999999999999999999");
    const std::string mulres = "-109876543222223101234567991209876531234567899999999999999999999999999999999999999999999999998888888888888880000000000088888889";
    //result regarding https://www.calculator.net/big-number-calculator.html 
    HugeInt c = a * b;
    auto mult =  c.value();
    const std::string fail_res = "Mul result is not true";
    if(mult.size() + 1 != mulres.size())
    {
        std::cout << fail_res ;
    }
    else
    {
        int i = 1;
        bool right_res = 1;
        for(auto el : mult)
        {
            if(el != mulres[i] - '0')
            {
                std::cout << el << "!=" << mulres[i] - '0';
                std::cout << fail_res;
                right_res = 0;
                break;
            }
            ++i;
        }
        if(right_res == 1)
        {
            std::cout << "a * b = ";
            c.Print();
            std::cout << std::endl;
        }

    }
    HugeInt k = a + b;
    const std::string add_res = "-98888888899999999999999999999999999999999999999999999999998888888888888880000000000088888888";
    //result regarding https://www.calculator.net/big-number-calculator.html 
    auto addr =  k.value();
    const std::string fail_add_res = "Add result is not true";
    if(addr.size() + 1 != add_res.size())
    {
        std::cout << "SIZE";
        std::cout << fail_add_res ;
    }
    else
    {
        int i = 1;
        bool right_res = 1;
        for(auto el : addr)
        {
            if(el != add_res[i] - '0')
            {
                std::cout << el << "!=" << add_res[i] - '0';
                std::cout << fail_add_res;
                right_res = 0;
                break;
            }
            ++i;
        }
        if(right_res == 1)
        {
            std::cout << "a +  b = ";
            k.Print();
            std::cout << std::endl;
        }

    }
    const std::string Ores = "98888888900000000000000000000000000000000000000000000000001111111111111119999999999911111110";
    //result regarding https://www.calculator.net/big-number-calculator.html 
    HugeInt o = a + HugeInt(-1) * b;
    auto o_val = o.value();
    if(Ores.size() != o_val.size())
        std::cout << fail_add_res;
    else
    {    
        for(int i = 0; i < Ores.size(); ++i)
        {
            if(o_val[i] != Ores[i] - '0')
                std::cout << fail_add_res;
        }
        std::cout << "a + (-1) * b = ";
        o.Print();
    }
    std::cout << std::endl;
    return 0;
}

