/* #include <iostream>
#include <string>
#include <cmath>
#include <time.h> */
#include <bits/stdc++.h>
#include <algorithm>
#define max_int 18446744073709551615ULL
typedef unsigned long long int ull;
using namespace std;

struct BigInt
{
    bool pos;
    string num;
};

BigInt operator+(BigInt a, BigInt b);
BigInt operator-(BigInt a, BigInt b);
BigInt _itoBI(const ull &n, const bool &pos);
ull _BItoi(BigInt &a); //only big positive integer

BigInt P_Max = _itoBI(max_int, true);
BigInt N_Max = _itoBI(max_int, false);

ostream &operator<<(ostream &os, BigInt &a)
{
    if (!a.pos && a.num != "0")
        os << "-";
    int n = a.num.length(), pos = 0;
    if (n % 3 == 1)
        os << a.num[pos++] << " ";
    else if (n % 3 == 2)
        os << a.num[pos++] << a.num[pos++] << " ";
    while (pos <= n - 3)
        os << a.num[pos++] << a.num[pos++] << a.num[pos++] << " ";
    return os;
}

bool fill_zero(BigInt &a, const int &n)
{
    for (int i = 0; i < n; ++i)
    {
        string tmp = '0' + a.num;
        a.num = tmp;
    }
    return true;
}

bool remove_zero(BigInt &a)
{
    int n = a.num.length(), cnt = 0;
    if (n > 1)
    {
        for (int i = 0; i < n - 1; ++i)
        {
            if (a.num[i] == '0')
                ++cnt;
            else
                break;
        }
        a.num.erase(0, cnt);
    }
    return true;
}

BigInt _init()
{
    BigInt res;
    res.num = "";
    res.pos = true;
    return res;
}

BigInt _itoBI(const ull &n, const bool &pos)
{
    BigInt res = _init();
    ull num = n;
    res.pos = pos;
    if (num >= 0 && num <= 9)
        res.num += (num + '0');
    else
        while (num > 0)
        {
            char value = (num % 10) + '0';
            string tmp = value + res.num;
            res.num = tmp;
            num /= 10;
        }
    return res;
}

ull _BItoi(BigInt &a)
{
    ull res = a.num[0] - '0';
    int n = a.num.length();
    for (int i = 1; i < n; ++i)
        res = res * 10 + (a.num[i] - '0');
    return res;
}

bool _swap(BigInt &a, BigInt &b)
{
    BigInt tmp = a;
    a = b;
    b = tmp;
    return true;
}

int _min(const int &a, const int &b)
{
    return (a < b) ? a : b;
}

int _max(const int &a, const int &b)
{
    return (a > b) ? a : b;
}

bool operator==(BigInt a, BigInt b)
{
    return ((a.pos == b.pos) && (a.num == b.num));
}

bool operator<(BigInt a, BigInt b)
{
    if (a.pos > b.pos)
        return false;
    if (a.pos < b.pos)
        return true;
    if (a.num.length() < b.num.length())
    {
        if (a.pos && b.pos)
            return true;
        else
            return false;
    }
    if (a.num.length() > b.num.length())
    {
        if (a.pos && b.pos)
            return false;
        else
            return true;
    }
    int n = a.num.length();
    for (int i = 0; i < n; ++i)
    {
        if (a.num[i] == b.num[i])
            continue;
        if (a.num[i] > b.num[i])
            return false;
        if (a.num[i] < b.num[i])
            return true;
    }
    return false;
}

bool operator<=(BigInt a, BigInt b)
{
    return (a < b || a == b);
}

BigInt operator+(BigInt a, BigInt b)
{
    if (a.num == "0")
        return b;
    if (b.num == "0")
        return a;
    if (a.pos != b.pos)
    {
        if (!a.pos)
        {
            a.pos = true;
            return b - a;
        }
        if (!b.pos)
        {
            b.pos = true;
            return a - b;
        }
    }
    BigInt res = _init();
    int n = 0;
    if (!a.pos && !b.pos)
        res.pos = false;
    if (a.num.length() < b.num.length())
    {
        res.num = b.num;
        n = b.num.length();
        fill_zero(a, n - a.num.length());
    }
    else
    {
        res.num = a.num;
        n = a.num.length();
        fill_zero(b, n - b.num.length());
    }
    int carry = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        int value = a.num[i] - '0' + b.num[i] - '0' + carry;
        carry = value / 10;
        value %= 10;
        res.num[i] = value + '0';
    }
    if (carry > 0)
    {
        char value = carry + '0';
        string tmp = value + res.num;
        res.num = tmp;
    }
    return res;
}

BigInt operator-(BigInt a, BigInt b)
{
    if (a.pos != b.pos)
    {
        if (!a.pos)
        {
            b.pos = false;
            return a + b;
        }
        if (!b.pos)
        {
            b.pos = true;
            return a + b;
        }
    }
    if (!a.pos && !b.pos)
    {
        b.pos = true;
        a.pos = true;
        return b - a;
    }
    if (a.num == "0")
    {
        b.pos = false;
        return b;
    }
    if (b.num == "0")
        return a;
    BigInt res = _init();
    if (a < b)
    {
        res.pos = false;
        _swap(a, b);
    }
    if (a < P_Max && b < P_Max)
        return _itoBI(_BItoi(a) - _BItoi(b), res.pos);
    res.num = a.num;
    int n = a.num.length();
    fill_zero(b, n - b.num.length());
    int borrow = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        int value = (a.num[i] - b.num[i]) - borrow;
        if (value < 0)
        {
            borrow = 1;
            value += 10;
        }
        else
            borrow = 0;
        res.num[i] = value + '0';
    }
    remove_zero(res);
    return res;
}

BigInt operator*(BigInt a, BigInt b)
{
    BigInt res = _init();
    if (b.num == "0" || a.num == "0")
    {
        res.num = "0";
        return res;
    }
    if (a.pos != b.pos)
        res.pos = false;
    if (a.num == "1")
    {
        res.num = b.num;
        return res;
    }
    if (b.num == "1")
    {
        res.num = a.num;
        return res;
    }
    res.num = a.num + b.num;
    for (int i = res.num.length() - 1; i >= 0; --i)
        res.num[i] = '0';
    for (int i = b.num.length() - 1; i >= 0; --i)
    {
        int carry = 0, pos = 0;
        for (int j = a.num.length() - 1; j >= 0; --j)
        {
            pos = i + j + 1;
            int value = (res.num[pos] - '0') + (a.num[j] - '0') * (b.num[i] - '0') + carry;
            carry = value / 10;
            res.num[pos] = (value % 10) + '0';
        }
        res.num[--pos] = carry + '0';
    }
    remove_zero(res);
    return res;
}

BigInt operator/(BigInt a, BigInt b)
{
    BigInt res = _init();
    if (a.pos != b.pos)
        res.pos = false;
    if (b == a)
    {
        res.num = "1";
        return res;
    }
    a.pos = true;
    b.pos = true;
    if (b < a && b.num != "0")
    {
        if (b.num == "1")
        {
            res.num = a.num;
            return res;
        }
        if (a < P_Max && b < P_Max)
            return _itoBI(_BItoi(a) / _BItoi(b), res.pos);
        int pos = 0, n = a.num.length();
        BigInt remainder = _init(), value[20];
        for (int i = 0; i < 20; ++i)
            value[i] = _init();
        while (pos <= n - 1)
        {
            remainder.num += a.num[pos++];
            if (remainder < b)
                res.num += "0";
            else if (remainder == b)
            {
                res.num += "1";
                remainder.num = "";
            }
            else
            {
                int try_num = 0;
                if (remainder.num[0] > b.num[0])
                    try_num = (remainder.num[0] - '0') / (b.num[0] - '0');
                else
                    try_num = ((remainder.num[0] - '0') * 10 + (remainder.num[1] - '0')) / (b.num[0] - '0');
                for (int i = try_num; i >= 1; --i)
                {
                    BigInt quotient = _itoBI(i, true);
                    if (value[i].num == "" && i < 20)
                        value[i] = quotient * b;
                    if (value[i] <= remainder)
                    {
                        if (value[i] == remainder)
                            remainder.num = "";
                        else
                            remainder = remainder - value[i];
                        res.num += quotient.num;
                        break;
                    }
                }
            }
        }
        remove_zero(res);
    }
    return res;
}

BigInt operator%(BigInt a, BigInt b)
{
    if (a < b)
        return a;
    BigInt remainder = _init();
    if (b == a)
    {
        remainder.num = "0";
        return remainder;
    }
    a.pos = true;
    b.pos = true;
    if (b < a && b.num != "0")
    {
        if (b.num == "1")
        {
            remainder.num = "0";
            return remainder;
        }
        int pos = 0, n = a.num.length();
        BigInt value[20];
        for (int i = 0; i < 20; ++i)
            value[i] = _init();
        while (pos <= n - 1)
        {
            remainder.num += a.num[pos++];
            if (remainder < b)
                continue;
            if (remainder == b)
                remainder.num = "";
            else
            {
                int try_num = 0;
                if (remainder.num[0] > b.num[0])
                    try_num = (remainder.num[0] - '0') / (b.num[0] - '0');
                else
                    try_num = ((remainder.num[0] - '0') * 10 + (remainder.num[1] - '0')) / (b.num[0] - '0');
                for (int i = try_num; i >= 1; --i)
                {
                    BigInt quotient = _itoBI(i, true);
                    if (value[i].num == "" && i < 20)
                        value[i] = quotient * b;
                    if (value[i] <= remainder)
                    {
                        if (value[i] == remainder)
                            remainder.num = "";
                        else
                            remainder = remainder - value[i];
                        break;
                    }
                }
            }
        }
        remove_zero(remainder);
    }
    return remainder;
}

BigInt remainder_Quotient(BigInt &a, BigInt &b, BigInt &remainder)
{
    BigInt res = _init();
    if (a < b)
    {
        remainder = a;
        return res;
    }
    if (a.pos != b.pos)
        res.pos = false;
    if (b == a)
    {
        res.num = "1";
        remainder.num = "0";
        return res;
    }
    a.pos = true;
    b.pos = true;
    if (b < a && b.num != "0")
    {
        if (b.num == "1")
        {
            res.num = a.num;
            return res;
        }
        int pos = 0, n = a.num.length();
        BigInt /* remainder = _init(), */ value[20];
        for (int i = 0; i < 20; ++i)
            value[i] = _init();
        while (pos <= n - 1)
        {
            remainder.num += a.num[pos++];
            if (remainder < b)
                res.num += "0";
            else if (remainder == b)
            {
                res.num += "1";
                remainder.num = "";
            }
            else
            {
                int try_num = 0;
                if (remainder.num[0] > b.num[0])
                    try_num = (remainder.num[0] - '0') / (b.num[0] - '0');
                else
                    try_num = ((remainder.num[0] - '0') * 10 + (remainder.num[1] - '0')) / (b.num[0] - '0');
                for (int i = try_num; i >= 1; --i)
                {
                    BigInt quotient = _itoBI(i, true);
                    if (value[i].num == "" && i < 20)
                        value[i] = quotient * b;
                    if (value[i] <= remainder)
                    {
                        if (value[i] == remainder)
                            remainder.num = "";
                        else
                            remainder = remainder - value[i];
                        res.num += quotient.num;
                        break;
                    }
                }
            }
        }
        remove_zero(remainder);
        remove_zero(res);
    }
    return res;
}

BigInt _factorial(BigInt &a)
{
    BigInt res = _init();
    if (a.pos == true)
    {
        if (a.num == "1" || a.num == "0")
        {
            res.num = "1";
            return res;
        }
        BigInt target = _itoBI(20, true); //20! < max_int < 21!
        if (target < a)
        {
            ull total = 1;
            for (int i = 2; i <= 20; ++i)
                total *= i;
            res = _itoBI(total, true);
            BigInt one = _init();
            one.num = "1";
            while (target < a)
            {
                target = target + one;
                res = res * target;
            }
        }
        else
        {
            int b = _BItoi(a), total = 1;
            for (int i = 2; i <= b; ++i)
                total *= i;
            res = _itoBI(total, true);
        }
    }
    return res;
}

BigInt _sqrt(BigInt &a) //Just approximately
{
    BigInt res = _init();
    if (a.pos == true)
    {
        if (a.num == "0" || a.num == "1")
            res = a;
        else if (a < P_Max)
            return _itoBI((ull)sqrtl(_BItoi(a)), true);
        else
        {
            ull remainder = 0, p = 0;
            unsigned int pos = 0, n = a.num.length();
            bool odd = false;
            if (n % 2 == 1)
            {
                odd = true;
                remainder = a.num[pos++] - '0';
            }
            else
                remainder = (a.num[pos++] - '0') * 10 + (a.num[pos++] - '0');
            while (remainder != 0 || pos <= n - 2)
            {
                //ull x = (ull)sqrtl((10 * p) * (10 * p) + remainder) - 10 * p + 1;
                unsigned int x = (p == 0) ? 9 : remainder / (20 * p);
                while ((20 * p + x) * x > remainder)
                    --x;
                res.num += _itoBI(x, true).num;
                if (res.num.length() >= (n + odd) / 2)
                    break;
                remainder -= (20 * p + x) * x;
                remainder *= 100;
                if (pos <= n - 2)
                    remainder += (a.num[pos++] - '0') * 10 + (a.num[pos++] - '0');
                p = p * 10 + x;
            }
        }
    }
    return res;
}

BigInt _sqr(BigInt &a)
{
    return a * a;
}

BigInt _power(BigInt &a, ull &b)
{
    if (b == 1)
        return a;
    else if (b == 2)
        return a * a;
    else
    {
        BigInt res = _init();
        res.num = "1";
        while (b > 0)
        {
            if (b % 2 == 1)
                res = res * a;
            a = a * a;
            b /= 2;
        }
        return res;
    }
}

BigInt _powermod(BigInt &a, BigInt &b, BigInt &c) // (a^b) % c
{
    BigInt res = _itoBI(1, true);
    BigInt zero = _itoBI(0, true);
    BigInt two = _itoBI(2, true);
    a = a % c;
    while (zero < b)
    {
        BigInt remainder = _init();
        BigInt quotient = remainder_Quotient(b, two, remainder);
        if (remainder.num == "1")
            res = (res * a) % c;
        a = (a * a) % c;
        b = quotient;
    }
    return res;
}

BigInt _abs(BigInt &a)
{
    BigInt res = a;
    res.pos == true;
    return res;
}

double _sin(BigInt &a)
{
    BigInt b = _itoBI(360, true);
    BigInt res = a % b;
    return sin(_BItoi(res));
}

double _cos(BigInt &a)
{
    BigInt b = _itoBI(360, true);
    BigInt res = a % b;
    return cos(_BItoi(res));
}

double _tan(BigInt &a)
{
    BigInt b = a % _itoBI(360, true);
    ull ans = _BItoi(b);
    return tan(ans);
}

double _cot(BigInt &a)
{
    return 1.0 / _tan(a);
}

BigInt greatest_common_divisor(BigInt &a, BigInt &b)
{
    if (a < P_Max && b < P_Max)
        return _itoBI(__gcd(_BItoi(a), _BItoi(b)), true);
    if (b.num == "0")
        return a;
    BigInt remainder = a % b;
    if (remainder.num == "0")
        return b;
    else
        return greatest_common_divisor(b, remainder);
}

BigInt _gcd(BigInt &a, BigInt &b)
{
    a = _abs(a);
    b = _abs(b);
    return greatest_common_divisor(a, b);
}

BigInt _lcm(BigInt &a, BigInt &b)
{
    return (a * b) / _gcd(a, b);
}

bool is_not_Prime(BigInt &a)
{
    if (a.num == "0" || a.num == "1")
        return true;
    unsigned int n = a.num.length();
    if (a.num[n - 1] == '0' || a.num[n - 1] == '2' || a.num[n - 1] == '4' || a.num[n - 1] == '5' || a.num[n - 1] == '6' || a.num[n - 1] == '8')
        return true;
    unsigned int sum = 0, even_sum = 0, odd_sum = 0;
    for (unsigned int i = 0; i < n - 1; ++i)
    {
        int k = a.num[i] - '0';
        sum += k;
        if (k % 2 == 0)
            even_sum += k;
        else
            odd_sum += k;
    }
    if (sum % 3 == 0)
        return true;
    if ((odd_sum - even_sum) % 11 == 0)
        return true;
    return false;
}

bool is_Composite(BigInt &x, BigInt &a, BigInt &even_a, ull &r)
{
    if (x.num == "1" || x.num == even_a.num)
        return false;
    for (ull i = 0; i < r; ++i)
    {
        x = (x * x) % a;
        if (x.num == even_a.num)
            return false;
    }
    return true;
}

bool is_probable_Prime(BigInt &a)
{
    //a - 1 = 2^r * d with d = (a - 1)/2 until d odd
    BigInt even_a = a - _itoBI(1, true);
    BigInt two = _itoBI(2, true);
    BigInt d = even_a;
    ull r = 0;
    unsigned int n = d.num.length();
    while (d.num[n - 1] != '1' && d.num[n - 1] != '3' && d.num[n - 1] != '5' && d.num[n - 1] != '7' && d.num[n - 1] != '9')
    {
        d = d / two;
        ++r;
        n = d.num.length();
    }
    //Random unsigned long long int
    random_device rd;
    mt19937_64 eng(rd());
    uniform_int_distribution<unsigned long long> distr;
    //The more higher i the more accurate
    short int i = 100, cnt = 0;
    while (i > 0)
    {
        --i;
        BigInt t = _itoBI(distr(eng) + 2, true);
        BigInt x = _powermod(t, d, a);
        if (is_Composite(x, a, even_a, r) == true)
            cnt++;
    }
    return (cnt < 100 - cnt) ? true : false;
}

bool is_Prime(BigInt &a)
{
    if (a.pos == true)
    {
        if (is_not_Prime(a) == true)
            return false;
        else if (a < P_Max)
        {
            ull b = _BItoi(a);
            for (ull i = 2; i * i <= b; i += 6)
                if (b - (b / i) * i == 0 || b - (b / (i + 2)) * (i + 2) == 0)
                    return false;
        }
        else
        {
            return is_probable_Prime(a);
        }
        return true;
    }
    else
        return false;
}

int main()
{
    clock_t start = clock();
    BigInt a;
    a.num = "120012001200120013";
    a.pos = true;
    cout << is_Prime(a) << endl;
    clock_t stop = clock();
    cout << "Execution time = " << double(stop - start) / double(CLOCKS_PER_SEC) << " sec";
    return 0;
}