#include<iostream>
#include<math.h>
#include<string>
#include<fstream>
#include<time.h>
#include<iomanip>

#define Char unsigned char

using namespace std;

long long cntmem = 0;

clock_t st, en;

struct INT
{
	bool sign;
	int cnt;
	int base;
	Char* List;
};

ofstream& operator << (ofstream& fo, INT& ans);
INT operator - (INT a, INT b);//all base
INT operator + (INT a, INT b);//all base
INT operator * (INT a, INT b);//all base
INT operator % (INT a, INT b);//all base
INT operator / (INT a, INT b);//all base
INT tobase(int Base, INT a);
INT bu2(INT a);
INT tracebu2(INT a);

void newChar(Char*& List, int n)
{
	cntmem += n;
	List = new Char[n];
}

INT abs(INT a)
{
	a.sign = 0;
	return a;
}

INT bang(INT a)
{
	INT ans;
	ans.cnt = a.cnt;
	ans.base = a.base;
	ans.sign = a.sign;
	newChar(ans.List, a.cnt);
	memcpy(ans.List, a.List, a.cnt * sizeof(Char));
	return ans;
}

INT operator + (INT a, INT b)// all base
{
	INT ans;
	if (a.sign && !b.sign) return (abs(b) - abs(a));
	if (!a.sign && b.sign) return (abs(a) - abs(b));
	if (a.sign && b.sign)
	{
		ans = abs(b) + abs(a);
		ans.sign = 1;
		return ans;
	}
	int n = (a.cnt > b.cnt) ? a.cnt : b.cnt;
	newChar(ans.List, n + 2);
	int temp = 0;
	for (int i = 0; i < n; i++)
	{
		Char x;
		if (i >= b.cnt) x = 0;
		else x = b.List[i];
		Char y;
		if (i >= a.cnt) y = 0;
		else y = a.List[i];
		int val = y + x + temp;
		ans.List[i] = val % a.base;
		temp = val / a.base;
	}
	if (temp != 0)
	{
		ans.List[n] = temp;
		n++;
	}
	ans.cnt = n;
	ans.sign = 0;
	ans.base = a.base;
	return ans;
}

bool operator < (INT a, INT b)// 0: duong, 1: am
{
	while (a.cnt - 1 >= 0 && a.List[a.cnt - 1] == 0) a.cnt--;
	while (b.cnt - 1 >= 0 && b.List[b.cnt - 1] == 0) b.cnt--;
	if (a.sign != b.sign)
	{
		if (b.sign == 0) return true;
		else return false;
	}
	if (!a.sign && !b.sign)
	{
		if (a.cnt < b.cnt) return true;
		if (a.cnt > b.cnt) return false;
		for (int i = a.cnt - 1; i >= 0; i--)
		{
			if (a.List[i] != b.List[i])
			{
				return (a.List[i] < b.List[i]);
			}
		}
	}
	if (a.sign && b.sign) return (abs(b) < abs(a));
	return false;
}

bool operator == (INT a, INT b)
{
	while (a.cnt - 1 >= 0 && a.List[a.cnt - 1] == 0) a.cnt--;
	while (b.cnt - 1 >= 0 && b.List[b.cnt - 1] == 0) b.cnt--;
	if (a.sign != b.sign) return false;
	if (a.cnt != b.cnt) return false;
	for (int i = 0; i < a.cnt; i++) if (!(a.List[i] == b.List[i])) return false;
	return true;
}

INT operator - (INT a, INT b)// all base
{
	INT ans;
	if (a.sign && !b.sign)
	{
		ans = abs(a) + abs(b);
		ans.sign = 1;
		return ans;
	}
	if (!a.sign && b.sign) return (abs(a) + abs(b));
	if (a.sign && b.sign) return (abs(b) - abs(a));
	if (a < b && !(a == b))
	{
		INT c;
		c = a;
		a = b;
		b = c;
		ans.sign = 1;
	}
	else ans.sign = 0;
	int n = a.cnt;
	newChar(ans.List, n + 2);
	int temp = 0;
	for (int i = 0; i < n; i++)
	{
		Char x;
		if (i >= b.cnt) x = 0;
		else x = b.List[i];
		int val = a.List[i] - x - temp;
		if (val < 0)
		{
			val += a.base;
			temp = 1;
		}
		else temp = 0;
		ans.List[i] = val % a.base;
	}
	ans.base = a.base;
	if (ans.base != 2) while (n - 1 >= 1 && ans.List[n - 1] == 0) n--;
	ans.cnt = n;
	return ans;
}

INT get_INT()
{
	INT a;
	a.cnt = 1;
	newChar(a.List, a.cnt);
	a.List[0] = 0;
	a.sign = 0;
	a.base = 256;
	return a;
}

INT operator << (INT a, int x)//base 256
{
	INT ans;
	ans.sign = a.sign;
	ans.base = a.base;
	ans.cnt = a.cnt;
	newChar(ans.List, ans.cnt + 2);
	Char temp = 0;
	for (int i = 0; i < a.cnt; i++)
	{
		int x = (a.List[i] << 1);
		ans.List[i] = (x & 255) + temp;
		temp = ((x & 256) == 256);
	}
	if (temp)
	{
		ans.List[ans.cnt] = temp;
		ans.cnt++;
	}
	if (x == 1) return ans;
	else return (ans << (x - 1));
}

INT operator >> (INT a, int x)//base 256
{
	INT ans;
	ans.sign = a.sign;
	ans.base = a.base;
	ans.cnt = a.cnt;
	newChar(ans.List, ans.cnt + 2);
	Char temp = 0;
	for (int i = 0; i < a.cnt; i++)
	{
		if (i == a.cnt - 1)
		{
			ans.List[i] = (a.List[i] >> 1);
			continue;
		}
		Char x = (a.List[i] >> 1);
		Char dd = (a.List[i + 1] & 1);
		ans.List[i] = x;
		ans.List[i] += (dd * (1 << 7));
	}
	while (ans.cnt - 1 >= 1 && ans.List[ans.cnt - 1] == 0) ans.cnt--;
	if (x == 1) return ans;
	else return(ans >> (x - 1));
}

INT operator * (INT a, INT b)//all base
{
	INT ans;
	ans.sign = 1 - (a.sign == b.sign);
	ans.base = a.base;
	int n = a.cnt;
	int m = b.cnt;
	ans.cnt = n + m;
	newChar(ans.List, ans.cnt + 1);
	int temp = 0;
	for (int i = 0; i <= n + m - 1; i++)
	{
		int val = 0;
		for (int j = 0; j <= m - 1; j++)
		{
			if (i - j <= n - 1 && i - j >= 0)
			{
				val += b.List[j] * a.List[i - j];
			}
		}

		val += temp;
		temp = (val / ans.base);
		val = val % ans.base;
		ans.List[i] = val;
	}
	while (ans.cnt - 1 >= 1 && ans.List[ans.cnt - 1] == 0) ans.cnt--;
	return ans;
}

INT operator & (INT a, INT b)
{
	int dd = a.base;
	a = tobase(2, a);
	b = tobase(2, b);
	if (a.sign == 1) a = bu2(a);
	if (b.sign == 1) b = bu2(b);
	INT ans;
	ans.cnt = (a.cnt > b.cnt) ? a.cnt : b.cnt;
	newChar(ans.List, ans.cnt + 2);
	int ok = 0;
	for (int i = 0; i <= ans.cnt; i++)
	{
		Char x;
		if (i >= b.cnt) x = b.sign;
		else x = b.List[i];
		Char y;
		if (i >= a.cnt) y = a.sign;
		else y = a.List[i];
		ans.List[i] = (x & y);
		if (ans.cnt == i && ans.List[i] == 1) ok = 1;
	}
	if (ok == 1) ans.cnt++;
	ans.sign = (a.sign & b.sign);
	ans.base = 2;
	if (ans.sign == 0) return tobase(dd, ans);
	else return tobase(dd, tracebu2(ans));
}

INT operator | (INT a, INT b)
{
	int dd = a.base;
	a = tobase(2, a);
	b = tobase(2, b);
	if (a.sign == 1) a = bu2(a);
	if (b.sign == 1) b = bu2(b);
	INT ans;
	ans.cnt = (a.cnt > b.cnt) ? a.cnt : b.cnt;
	newChar(ans.List, ans.cnt + 2);
	int ok = 0;
	for (int i = 0; i <= ans.cnt; i++)
	{
		Char x;
		if (i >= b.cnt) x = b.sign;
		else x = b.List[i];
		Char y;
		if (i >= a.cnt) y = a.sign;
		else y = a.List[i];
		ans.List[i] = (x | y);
		if (ans.cnt == i && ans.List[i] == 1) ok = 1;
	}
	if (ok == 1) ans.cnt++;
	ans.sign = (a.sign | b.sign);
	ans.base = 2;
	if (ans.sign == 0) return tobase(dd, ans);
	else return tobase(dd, tracebu2(ans));
}

INT operator ^ (INT a, INT b)
{
	int dd = a.base;
	a = tobase(2, a);
	b = tobase(2, b);
	if (a.sign == 1) a = bu2(a);
	if (b.sign == 1) b = bu2(b);
	INT ans;
	ans.cnt = (a.cnt > b.cnt) ? a.cnt : b.cnt;
	newChar(ans.List, ans.cnt + 2);
	int ok = 0;
	for (int i = 0; i <= ans.cnt; i++)
	{
		Char x;
		if (i >= b.cnt) x = b.sign;
		else x = b.List[i];
		Char y;
		if (i >= a.cnt) y = a.sign;
		else y = a.List[i];
		ans.List[i] = (x ^ y);
		if (ans.cnt == i && ans.List[i] == 1) ok = 1;
	}
	if (ok == 1) ans.cnt++;
	ans.sign = (a.sign ^ b.sign);
	ans.base = 2;
	if (ans.sign == 0) return tobase(dd, ans);
	else return tobase(dd, tracebu2(ans));
}

INT operator ~ (INT a)
{
	int dd = a.base;
	a = tobase(2, a);
	if (a.sign == 1) a = bu2(a);
	INT k = a;
	INT ans;
	ans.cnt = a.cnt;
	newChar(ans.List, ans.cnt + 1);
	for (int i = 0; i < ans.cnt; i++) ans.List[i] = (1 - a.List[i]);
	ans.sign = 1 - a.sign;
	ans.base = 2;
	if (ans.sign == 0) return tobase(dd, ans);
	else return tobase(dd, tracebu2(ans));
}

INT daonguoc(INT a)
{
	INT ans;
	newChar(ans.List, a.cnt);
	ans.sign = a.sign;
	ans.base = a.base;
	ans.cnt = a.cnt;
	Char* x;
	newChar(x, a.cnt);
	memcpy(x, a.List, a.cnt * sizeof(Char));
	for (int i = 0; i < a.cnt; i++) x[i] = a.List[a.cnt - 1 - i];
	memcpy(ans.List, x, a.cnt * sizeof(Char));
	return ans;
}

INT getBase(int j, INT a)
{
	INT ans;
	ans.base = a.base;
	ans.sign = a.sign;
	ans.cnt = 1;
	newChar(ans.List, 1);
	ans.List[0] = Char(j);
	return ans;
}

INT operator / (INT a, INT b)//all base
{
	INT ans;
	ans.cnt = 0;
	ans.base = a.base;
	int dd = 1 - (a.sign == b.sign);
	ans.sign = 0;
	a.sign = 0; b.sign = 0;
	newChar(ans.List, a.cnt);
	if (a == b)
	{
		INT x = get_INT();
		x.base = a.base;
		x.sign = dd;
		x.List[0] = 1;
		return x;
	}
	if (a < b) return get_INT();
	INT temp;
	temp.cnt = 0;
	newChar(temp.List, a.cnt + 1);
	temp.base = a.base;
	temp.sign = ans.sign;
	for (int i = a.cnt - 1; i >= 0; i--)
	{
		temp.List[temp.cnt] = a.List[i];
		temp.cnt++;
		for (int j = ans.base - 1; j >= 0; j--)
		{
			INT x = getBase(j, ans);
			if (b * x < daonguoc(temp) || b * x == daonguoc(temp))
			{
				ans.List[ans.cnt] = x.List[0];
				ans.cnt++;
				temp = daonguoc(temp) - (b * x);
				temp = daonguoc(temp);
				break;
			}
		}
	}
	ans = daonguoc(ans);
	while (ans.cnt - 1 >= 1 && ans.List[ans.cnt - 1] == 0) ans.cnt--;
	ans.sign = dd;
	return ans;
}

INT operator % (INT a, INT b)//all base
{
	if (a == b) return get_INT();
	if (a.sign != b.sign)
	{
		if (a.sign == 1) return b - (abs(a) % b);
		if (b.sign == 1) return (a % abs(b)) - abs(b);
	}
	INT ans;
	ans.cnt = 0;
	ans.base = a.base;
	if (a.sign == 1 && b.sign == 1)
	{
		ans.sign = 1;
		a.sign = 0;
		b.sign = 0;
	}
	else ans.sign = 0;
	if (a < b) return a;
	newChar(ans.List, a.cnt);
	INT temp;
	temp.cnt = 0;
	newChar(temp.List, a.cnt + 1);
	temp.base = a.base;
	temp.sign = ans.sign;
	for (int i = a.cnt - 1; i >= 0; i--)
	{
		temp.List[temp.cnt] = a.List[i];
		temp.cnt++;
		for (int j = ans.base - 1; j >= 0; j--)
		{
			INT x = getBase(j, ans);
			if (b * x < daonguoc(temp) || b * x == daonguoc(temp))
			{
				ans.List[ans.cnt] = j;
				ans.cnt++;
				temp = daonguoc(temp) - (b * x);
				temp = daonguoc(temp);
				break;
			}
		}
	}
	ans = daonguoc(temp);
	while (ans.cnt - 1 >= 1 && ans.List[ans.cnt - 1] == 0) ans.cnt--;
	return ans;
}

int to_int(INT x, int Base)
{
	int ans = 0;
	for (int i = 0; i < x.cnt; i++) ans = ans + (x.List[i] * (pow(Base, i)));
	return ans;
}

INT tobase(int Base, INT a)// any base to base
{
	int ddd = a.sign;
	a.sign = 0;
	if (a.cnt == 1 && a.List[0] == 0)
	{
		INT x = get_INT();
		x.base = Base;
		x.sign = a.sign;
		return x;
	}
	int dd = Base;
	INT ans;
	ans.base = a.base;
	ans.sign = a.sign;
	ans.cnt = 0;
	newChar(ans.List, 1024);
	INT x;
	x.base = a.base;
	x.cnt = 0;
	x.sign = a.sign;
	newChar(x.List, 10);
	while (Base > 0)
	{
		x.List[x.cnt] = Base % a.base;
		x.cnt++;
		Base /= a.base;
	}
	INT temp = get_INT();
	temp.sign = a.sign;
	temp.base = a.base;
	while (!(temp == a))
	{
		INT y = a % x;// y cung base voi a va x<< " ";
		if (dd <= a.base)
		{
			ans.List[ans.cnt] = y.List[0];
			ans.cnt++;
		}
		else
		{
			ans.List[ans.cnt] = to_int(y, a.base);
			ans.cnt++;
		}
		a = a / x;
	}
	delete[] x.List;
	x.List = NULL;
	ans.base = dd;
	ans.sign = ddd;
	return ans;
}

INT to_string(INT a)
{
	INT ans = tobase(10, a);
	return ans;
}
INT to_base32(INT a)
{
	INT ans = tobase(32, a);
	string s = "0123456789ABCDEFGHJKMNPQRSTVWXYZ";
	for (int i = 0; i < ans.cnt; i++) ans.List[i] = s[ans.List[i]];
	return ans;
}
INT to_base58(INT a)
{
	INT ans = tobase(58, a);
	string s = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
	for (int i = 0; i < ans.cnt; i++) ans.List[i] = s[ans.List[i]];
	return ans;
}
INT to_base64(INT a)
{
	INT ans = tobase(64, a);
	string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	for (int i = 0; i < ans.cnt; i++) ans.List[i] = s[ans.List[i]];
	return ans;
}

int digits(INT a)
{
	INT x = tobase(10, a);
	return x.cnt;
}

INT min(INT a, INT b)
{
	if (a < b) return a;
	return b;
}

INT max(INT a, INT b)
{
	if (a < b) return b;
	return a;
}

INT pow(INT a, INT b)
{
	INT x = get_INT();
	x.base = 10;
	x.sign = 0;
	x.List[0] = 1;
	INT k = tobase(a.base, x);
	if (b == k) return a;
	x.List[0] = 0;
	k = tobase(a.base, x);
	if (b == k)
	{
		x.List[0] = 1;
		return x;
	}
	x.List[0] = 2;
	x = tobase(a.base, x);
	INT temp = pow(a, (b / x));
	if (b.List[0] % 2 == 0) return temp * temp;
	return temp * temp * a;
}

INT powmod(INT a, INT b, INT Base)
{
	INT x = get_INT();
	x.base = 10;
	x.sign = 0;
	x.List[0] = 1;
	INT k = tobase(a.base, x);
	if (b == k) return a;
	x.List[0] = 0;
	k = tobase(a.base, x);
	if (b == k)
	{
		x.List[0] = 1;
		return x;
	}
	x.List[0] = 2;
	x = tobase(a.base, x) % Base;
	INT temp = powmod(a, (b / x), Base);
	if (b.List[0] % 2 == 0) return (temp * temp) % Base;
	return (temp * temp * a) % Base;
}

INT Rand(INT n)
{
	INT ans;
	ans.cnt = n.cnt;
	ans.base = n.base;
	ans.sign = n.sign;
	INT x;
	x.cnt = 1;
	newChar(x.List, 1);
	x.sign = n.sign;
	x.base = 10;
	x.List[0] = 2;
	newChar(ans.List, n.cnt + 1);
	while (1)
	{
		for (int i = 0; i < n.cnt; i++) ans.List[i] = rand() % n.base;
		while (ans.cnt - 1 >= 1 && ans.List[ans.cnt - 1] == 0) ans.cnt--;
		if (ans < tobase(ans.base, x)) continue;
		INT xx = n - tobase(ans.base, x);
		if (xx < ans) continue;
		break;
	}
	return ans;
}

bool Test(INT d, INT n)
{
	INT x;
	x.cnt = 1;
	newChar(x.List, 1);
	x.sign = n.sign;
	x.base = 10;
	x.List[0] = 1;
	INT temp = Rand(n);
	INT k = powmod(temp, d, n);
	if (k == tobase(k.base, x)) return true;
	if (k == tobase(k.base, (n - x))) return true;
	INT dd = tobase(k.base, (n - x));
	while (!(d == dd))
	{
		k = (k * k) % n;
		x.List[0] = 2;
		d = d * tobase(d.base, x);
		x.List[0] = 1;
		if (k == tobase(temp.base, x)) return false;
		if (k == dd) return true;
	}
	return false;
}

bool isprime(INT a, int test)
{
	INT INT_test = get_INT();
	INT_test.base = 10;
	INT_test.sign = a.sign;
	INT_test.List[0] = 1;
	INT x;
	x = tobase(a.base, INT_test);
	if (a < x || a == x) return false;
	/*INT_test.List[0] = 4;
	x = tobase(a.base, INT_test);
	if (a == x) return false;*/
	INT_test.List[0] = 3;
	x = tobase(a.base, INT_test);
	if (a < x || a == x) return true;
	if ((int)a.List[0] % 2 == 0) return false;
	INT_test.List[0] = 1;
	x = tobase(a.base, INT_test);
	INT d = a - x;
	INT_test.List[0] = 2;
	x = tobase(a.base, INT_test);
	if (a.List[0] % 2 == 0) return false;
	while ((tobase(2, d)).List[0] == 0) d = d / x;
	for (int i = 0; i < test; i++) if (!Test(d, a)) return false;
	return true;
}

INT bu2(INT a)// to negetive
{
	int dd = a.sign;
	INT ans;
	ans.sign = 0;
	ans.cnt = a.cnt;
	ans.base = 2;
	newChar(ans.List, a.cnt + 1);
	for (int i = 0; i < a.cnt; i++) ans.List[i] = 1 - a.List[i];
	INT x = get_INT();
	x.base = 2;
	x.sign = 0;
	x.List[0] = 1;
	ans = ans + x;
	ans.sign = dd;
	return ans;
}

INT tracebu2(INT a)// to negetive
{
	int dd = a.sign;
	INT x = get_INT();
	x.base = 2;
	x.sign = 0;
	x.List[0] = 1;
	a.sign = 0;
	INT ans = a - x;
	for (int i = 0; i < a.cnt; i++) ans.List[i] = 1 - ans.List[i];
	ans.sign = dd;
	return ans;
}

bool dau(string x)
{
	if (x == "+" || x == "-" || x == "*" || x == "/" || x == "%") return true;
	if (x == "&" || x == "~" || x == "|" || x == "^") return true;
	if (x == ">>" || x == "<<") return true;
	return false;
}

ofstream& operator << (ofstream& fo, INT& ans)
{
	while (ans.cnt - 1 >= 1 && ans.List[ans.cnt - 1] == 0) ans.cnt--;
	if (ans.base != 2 && ans.sign == 1) fo << "-";
	if (ans.base == 2 && ans.sign == 0) fo << 0;
	if (ans.base == 2 || ans.base == 10) for (int i = ans.cnt - 1; i >= 0; i--) fo << int(ans.List[i]);
	else for (int i = ans.cnt - 1; i >= 0; i--) fo << ans.List[i];
	return fo;
}

bool checktype(int type, ofstream& fo)
{
	if (type == 1)
	{
		fo << cntmem << " byte\n";
		return 1;
	}
	if (type == 2)
	{
		en = clock();
		fo << fixed << setprecision(7) << ((float)(en - st)) / CLOCKS_PER_SEC << " s\n";
		return 1;
	}
	return 0;
}

void to_inp(INT& a, string y, int base1, int dau)
{
	int dd = 0;
	if (y[y.length() - 1] == ')') dd = 1;
	if (base1 == 10) //he co so 10
	{
		a.base = base1;
		a.sign = (y[dau] == '-');
		a.cnt = 0;
		newChar(a.List, y.length() + 1);
		for (int i = dau + a.sign; i < y.length() - dd; i++)
		{
			a.List[a.cnt] = y[i] - '0';
			a.cnt++;
		}
		a = daonguoc(a);
	}
	if (base1 == 2)//he co so 2
	{
		a.base = base1;
		a.sign = y[dau] - '0';
		a.cnt = 0;
		newChar(a.List, y.length() + 1);
		for (int i = dau; i < y.length() - dd; i++)
		{
			a.List[a.cnt] = y[i] - '0';
			a.cnt++;
		}
		a = daonguoc(a);
		if (a.sign) a = tracebu2(a);
		while (a.cnt - 1 >= 1 && a.List[a.cnt - 1] == 0) a.cnt--;
	}
}

void to_out(INT& ans, int base1)
{
	if (ans.sign && base1 == 2)
	{
		ans.List[ans.cnt] = 0;
		ans.cnt++;
		ans = bu2(ans);
	}
}

void main(int sl, char** val)
{
	ifstream fi(val[1]);
	ofstream fo(val[2]);
	int base1 = 0, base2 = 0;
	while (fi >> base1)
	{
		cntmem = 0;
		st = clock();
		int type = 0; // type = 1 get mem       type = 2	get time
		string x, y;
		fi >> x;
		if (x == "getmem") type = 1;
		if (x == "gettime") type = 2;
		if (type) fi >> x;
		if (x.length() >= 2 && x[0] == 'd' && x[1] == 'i')
		{
			INT a;
			to_inp(a, x, base1, 7);
			int ans = digits(a);
			if (checktype(type, fo)) continue;
			fo << ans << "\n";
			continue;
		}
		if (x.length() >= 3 && x[0] == 'p' && x[1] == 'o' && x[2] == 'w')
		{
			string z, t;
			fi >> z >> t;
			INT a, b;
			INT ans;
			to_inp(a, z, base1, 0);
			to_inp(b, t, base1, 0);
			ans = pow(a, b);
			to_out(ans, base1);
			if (checktype(type, fo)) continue;
			fo << ans << "\n";
			continue;
		}
		if (x.length() >= 3 && x[0] == 'm' && x[1] == 'i' && x[2] == 'n')
		{
			string z, t;
			fi >> z >> t;
			INT a, b;
			to_inp(a, z, base1, 0);
			to_inp(b, t, base1, 0);
			INT ans = min(a, b);
			to_out(ans, base1);
			if (checktype(type, fo)) continue;
			fo << ans << "\n";
			continue;
		}
		if (x.length() >= 3 && x[0] == 'm' && x[1] == 'a' && x[2] == 'x')
		{
			string z, t;
			fi >> z >> t;
			INT a, b;
			to_inp(a, z, base1, 0);
			to_inp(b, t, base1, 0);
			INT ans = max(a, b);
			to_out(ans, base1);
			if (checktype(type, fo)) continue;
			fo << ans << "\n";
			continue;
		}
		if (x.length() >= 3 && x[0] == 'a' && x[1] == 'b' && x[2] == 's')
		{
			INT a;
			to_inp(a, x, base1, 4);
			a = abs(a);
			to_out(a, base1);
			if (checktype(type, fo)) continue;
			fo << a;
			continue;
		}
		if (x.length() >= 2 && x[0] == 'i' && x[1] == 's')
		{
			if (x[8] == '-' || (x[8] == '1' && base1 == 2))
			{
				fo << "khong la so nguyen to.\n";
				continue;
			}
			INT a;
			to_inp(a, x, base1, 8);
			bool kq = isprime(a, 5);
			if (checktype(type, fo)) continue;
			if (kq) fo << "la so nguyen to\n";
			else fo << "khong la so nguyen to\n";
			continue;
		}
		if (x.length() >= 2 && x[0] == 't' && x[1] == 'o')
		{
			INT a;
			to_inp(a, x, base1, 10);
			INT ans;
			if (x[7] == '6') ans = to_base64(a);
			if (x[7] == '5') ans = to_base58(a);
			if (x[7] == '3') ans = to_base32(a);
			if (x[7] == 'n') ans = to_string(a);
			if (checktype(type, fo)) continue;
			fo << ans << "\n";
			continue;
		}
		fi >> y;
		string z;
		if (x == "~")
		{
			INT a;
			to_inp(a, y, base1, 0);
			INT ans = (~a);
			to_out(ans, base1);
			if (checktype(type, fo)) continue;
			fo << ans << "\n";
			continue;
		}
		if (dau(y))
		{
			fi >> z;
			INT ans = get_INT();
			ans.cnt = 0;
			INT a, b;
			to_inp(a, x, base1, 0);
			to_inp(b, z, base1, 0);
			if (y == "+") ans = a + b;
			if (y == "-") ans = a - b;
			if (y == "*") ans = a * b;
			if (y == "/") ans = a / b;
			if (y == "%") ans = a % b;
			if (ans.cnt != 0)
			{
				to_out(ans, base1);
				if (checktype(type, fo)) continue;
				fo << ans << "\n";
				continue;
			}
			if (y == "&" || y == "|" || y == "^")
			{
				a = tobase(10, a);
				b = tobase(10, b);
				if (y == "&") ans = a & b;
				if (y == "|") ans = a | b;
				if (y == "^") ans = a ^ b;
				ans = tobase(base1, ans);
				to_out(ans, base1);
				if (checktype(type, fo)) continue;
				fo << ans << "\n";
				continue;
			}
			if (y == ">>")
			{
				int Z = 0;
				for (int i = 0; i < z.length(); i++) Z = Z * 10 + (z[i] - '0');
				ans = tobase(base1, (tobase(256, a) >> Z));
			}
			if (y == "<<")
			{
				int Z = 0;
				for (int i = 0; i < z.length(); i++) Z = Z * 10 + (z[i] - '0');
				ans = tobase(base1, (tobase(256, a) << Z));
			}
			to_out(ans, base1);
			if (checktype(type, fo)) continue;
			fo << ans << "\n";
			continue;
		}
		int X = 0;
		for (int i = 0; i < x.length(); i++) X = X * 10 + (x[i] - '0');
		INT a;
		to_inp(a, y, base1, 0);
		INT ans = tobase(X, a);
		to_out(ans, X);
		if (checktype(type, fo)) continue;
		fo << ans << "\n";
	}
	fi.close();
	fo.close();
}