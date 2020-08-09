
#include <iostream>
#include "shuzu.h"
using namespace std;

template<typename T=true_type>
struct Func {};

template<>
struct Func<true_type>
{

	Func() {};

	void operator()()
	{
		cout << "AMD Yes" << endl;
	}
};



template<>
struct Func<false_type>
{
	Func() = default;

	void operator()()
	{
		cout << "Intel OK" << endl;
	}
};


int main()
{
	void* p = Func();





}