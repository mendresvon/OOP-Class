#include <iostream>
using namespace std;

int main()
{
	int var = 20;
	//int* ip; // 不建議使用
	//int* ip = 0; // C++98之前的空指標定義，不建議使用
	//int* ip = NULL; // C++98之前的空指標定義，不建議使用
	int* ip = nullptr; // C++11之後的空指標定義
	ip = &var; // & 取址運算子


	cout << "var = " << var << endl;
	cout << "&var = " << &var << endl;
	cout << "ip = " << ip << endl;
	cout << "*ip = " << *ip << endl; // * 取值運算子
	cout << endl;


	int** ipp;
	ipp = &ip;


	cout << "var = " << var << endl;
	cout << "ip (i.e. &var) = " << ip << endl;
	cout << "ipp (i.e. &ip) = " << ipp << endl;
	cout << "*ipp = " << *ipp << endl;
	cout << "**ipp = " << **ipp << endl;
	cout << endl;


	const int N = 5;
	int a[N] = { 10, 20, 30, 40, 50 }; //整數陣列
	int* ptr = nullptr;
	ptr = a;


	cout << "a[3] = " << a[3] << endl;
	cout << "*(ptr+3) = " << *(ptr + 3) << endl;


	// for (int i = 0; i < N; i++) {
	// 	cout << "a[" << i << "] = " << a[i] << endl;
	// 	cout << "第" << i << "個指標 = " << ptr << endl;
	// 	cout << "第" << i << "個指標的內容 = " << *ptr << endl;
	// 	ptr++;
	// }


}