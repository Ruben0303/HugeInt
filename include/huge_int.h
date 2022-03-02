#include<iostream>
#include<vector>
#include<algorithm>

std::vector<short> mul(const std::vector<int> v, int n);
std::vector<short> add(const std::vector<int>& val, const std::vector<int> & arg_val);
short compare_vecs(const std::vector<short> v1,const std::vector<short> & v2);
std::vector<short> sub(const std::vector<short>& val, const std::vector<short> & arg_val);
class HugeInt
{
    std::vector<short> val;
    bool sign; 
public:
	HugeInt(const std::string& value);
	HugeInt(int value);
    HugeInt(const std::vector<short> & val);
    void set_sign();
    bool is_signed() const;
    std::vector<short> value() const;
    void Print() const;
    HugeInt operator + (const HugeInt & arg) const;
    HugeInt operator * (const HugeInt & arg) const;

};



