#include<iostream>
#include<vector>
#include<algorithm>
#include"huge_int.h"

std::vector<short> mul(const std::vector<short> v, int n)
{
    std::vector<short> res(v.size() + 1);
    short carry = 0;                        //for carrying number from last operation
    for(int i = v.size() - 1; i >= 0; --i)
    {
        res[i + 1] = v[i] * n + carry;
        carry = res[i + 1] / 10;
        res[i + 1] %= 10;
    }
    res[0] = carry;
    if(res[0] == 0)
    {
        std::reverse(res.begin(), res.end());
        res.pop_back();
        std::reverse(res.begin(), res.end());
    }
    return res;
}

std::vector<short> add(const std::vector<short>& val, const std::vector<short> & arg_val)
{
        std::vector<short> res_val;
        const std::vector<short>& big = (val.size() >= arg_val.size())? val : arg_val;
        std::vector<short> small = (arg_val.size() <= val.size())? arg_val : val;
        if(small.size() < big.size())           //makeing two vectors for same size to facilitate operations
        {
            small.reserve(big.size());
            std::reverse(small.begin(), small.end());
            for(int i = small.size(); i < big.size(); ++i)
                small.push_back(0);             //adding "0"s to the start of number 
            std::reverse(small.begin(), small.end());  
        }
        res_val.resize(big.size() + 1);         //the max size that res can be big.size() + 1
        short carry = 0;
        for(int i = small.size() - 1; i >= 0; --i)
        {
            res_val[i + 1] = big[i] + small[i] + carry;
            carry = res_val[i + 1] / 10;
            res_val[i + 1] %= 10;
        }
        res_val[0] = carry;                     
        if(res_val[0] == 0)                     //first el is the numbers firs digit it can be 0 which means the last carry is 0, for real value for the number it must be deleted
        {
            std::reverse(res_val.begin(), res_val.end());
            res_val.pop_back();
            std::reverse(res_val.begin(), res_val.end());
        }
        return res_val; 
 
}
short compare_vecs(const std::vector<short> v1,const std::vector<short> & v2) //comares two vectors as numbers
{
    for(int i = 0; i < v1.size(); ++i)
    {
        if(v1[i] > v2[i])
            return 1;
        if(v1[i] < v2[i])
            return -1;
    }
    return 0;

}
std::vector<short> sub(const std::vector<short>& val, const std::vector<short> & arg_val) //for subing two vecors
{
        std::vector<short> res_val;
        const std::vector<short>& big = (val.size() >= arg_val.size())? val : arg_val;
        std::vector<short> small = (arg_val.size() <= val.size())? arg_val : val;
        if(small.size() < big.size())
        {
            small.reserve(big.size());
            std::reverse(small.begin(), small.end());
            for(int i = small.size(); i < big.size(); ++i)
                small.push_back(0);
            std::reverse(small.begin(), small.end());  
        }
        res_val.resize(big.size());
        short  carry = 0;
        short prev_carry = 0;
        for(int i = small.size() - 1; i >= 0; --i)
        {
            short tmp = big[i];
            if(tmp + carry < small[i])      //if cur digit number is small than the digit we must sub, we need to takeing 
            {
                tmp += 10;                  //takeing 1  from the left number
                carry = -1;                 //saveing taken  for substracting from  the left number in the next step
            }
            else
            {
                carry = 0;                  
            }
            res_val[i] = tmp - small[i] + prev_carry; 
            prev_carry = carry;
        }
        std::reverse(res_val.begin(), res_val.end());  
        short last = res_val[res_val.size() - 1];
        while(last == 0)
        {
            res_val.pop_back(); 
            last = res_val[res_val.size() - 1];
        }
        std::reverse(res_val.begin(), res_val.end());  
        return res_val; 
 
}
HugeInt::HugeInt(const std::string& value) 
{
    val.reserve(value.size());  
    int i = 0;
    if(value[0] == '-') //if value is negative value[0] is sign '-'
    {
        sign = 1;
        i = 1;
    }
    else 
    {
        sign = 0;
    }
    for(; i < value.size(); ++i)
    {
        val.push_back(value[i] - '0');
    }
}
HugeInt::HugeInt(int value)
{
    sign = 0;
    while(value)
    {
        short digit = value % 10;
        if(digit < 0)
        {
            digit *= -1;
            sign = 1;
        }
        val.push_back(digit);
        value /= 10;
    }
    std::reverse(val.begin(), val.end());
}
HugeInt::HugeInt(const std::vector<short> & val) : val(val), sign(0) {}
void HugeInt::set_sign() //seting sign for already created instance
{
    sign = 1;
}

bool HugeInt::is_signed() const //checking sign of the value
{
    return sign == 1;
}

HugeInt HugeInt::operator + (const HugeInt & arg) const
{
    if(arg.val.empty())
        return *this;
    if(val.empty())
        return arg;
    std::vector<short> res_val;
    bool to_set_sign = 0;
    if(this->is_signed() == arg.is_signed()) // when two number are signed similar
    {
        res_val = add(val, arg.val); //adding numbers
        if(this->is_signed())           // and seting sign 
            to_set_sign = 1;
    }
    else //when two numbers have different signs
    {

        const HugeInt & B = (val.size() >= arg.val.size())? *this  : arg;
        const HugeInt & S = (arg.val.size() <= val.size())? arg : *this;
        const std::vector<short>& big = B.value();
        const std::vector<short>& small = S.value();
        if(big.size() == small.size())
        {
            short flag = compare_vecs(big, small);
            if(flag == -1)      //it means needed substract a + (-b) = a - b
            {
                res_val = sub(small, big);
                if(S.sign == 1)     
                    to_set_sign = 1;
            }
            else if(flag == 0)
            {
                res_val = {0};
                to_set_sign = 0;
            }
        }
        else
        {
            res_val = sub(big, small);
            if(B.sign == 1)
                to_set_sign = 1;
        }


    }
    HugeInt result(res_val);
    if(to_set_sign)
    {
        result.set_sign();
    }
    return result;

}
HugeInt HugeInt::operator * (const HugeInt & arg) const
{

    const std::vector<short>& big = (val.size() >= arg.val.size())? val : arg.val;
    std::vector<short> small = (arg.val.size() <= val.size())? arg.val : val;
    std::vector<short> result;
    for(int i = small.size() - 1; i >= 0; --i) //implementing mult algorithm
    {

        std::vector<short> cur_res;
        cur_res.reserve(big.size() + 1);
        cur_res = mul(big, small[i]);   //multiplicating the whole number with any digit of another number
        for(int j = 0; j < small.size() - 1 - i; ++j)//in any stage of multing adding 0 to cur_res fo right ordering 
            cur_res.push_back(0);
        result = add(result, cur_res);
    }
    HugeInt res(result);
    if(arg.sign != this->sign) //if signs are different the res must have '-' sign 
        res.set_sign(); 
    return res;
}

std::vector<short> HugeInt::value() const
{
    return val; 
}

void HugeInt::Print() const 
{
    if(this->is_signed())
    {
        std::cout << '-';
    }
    for(int i = 0; i < val.size(); ++i)
        std::cout << val[i];
}




