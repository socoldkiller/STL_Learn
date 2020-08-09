#pragma once
#include <iostream>
#include <algorithm>
const int maxinum = 20;
using namespace std;
template<typename T>
struct shuzu
{
	int length;
	//T shuzu_shuzu[maxinum];
	T* shuzu_shuzu;
	shuzu();
	shuzu(T l[], int i);
	void Show();


	bool ClearList(T* l);     //������Ա������
	int GetElem(T* l, int i);//��ȡĳ��Ԫ��
	bool ListDelete(T* l, int i);//ɾ����ĳ��Ԫ�ز�����
	bool ListInsert(T* l, int i, int e);//�����Ա�ĵ�i��Ԫ�ز���һ��Ԫ��
	


};




template<typename T>
shuzu<T>::shuzu()
{

	for (int i = 0; i < maxinum; i++)
		shuzu_shuzu[i] = 0;
	length = 0;
}

template<typename T>
shuzu<T>::shuzu(T l[], int i)
{
	shuzu_shuzu = l;
	length = i;
}

template<typename T>
void shuzu<T>::Show()
{
	/*
	cout << length << endl;
	for (int i = 0; i < length; i++)
		std::cout << shuzu_shuzu[i] << std::endl;
	*/
	for_each(shuzu_shuzu, shuzu_shuzu + length, [](int x) {cout << x << endl; });

}

template<typename T>
int shuzu<T>::GetElem(T* l, int i)
{
	return l[i];
}

template<typename T>
bool shuzu<T>::ListDelete(T* l, int i)
{
	int k = i;


}

template<typename T>
bool shuzu<T>::ListInsert(T* l, int i, int e)
{
	int k;
	if ((i > l->length) || (i < 0) || (l->length == 0))
	{
		std::cout << "�˲����������Ч";
		return false;
	}
	if (l->length >= i)
	{
		for (k = l->length - 1; k >= i - 1; k--)
			l->shuzu_shuzu[k + 1] = l->shuzu_shuzu[k];
	}
	l->shuzu_shuzu[i - 1] = e;
	l->length++;
	return true;
}

template<typename T>
bool shuzu<T>::ClearList(T* l)
{
	for (int i = 0; i < l->length; i++)
		l->shuzu_shuzu[i] = 0;
	l->length = 0;
	return true;
}

