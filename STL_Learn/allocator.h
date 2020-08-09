
#ifndef _JJALLOC_
#define _JJALLOC_

#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>
using namespace std;
namespace JJ
{
	template<class T>
	inline T* _allocate(ptrdiff_t size, T*)
	{
		set_new_handler(0);
		T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
		if (tmp == 0)
		{
			cerr << "out of memory" << endl;
			exit(1);
		}
		return tmp;
	}

	template<class T>
	inline void _deallocate(T* buffer)
	{
		::operator delete(buffer);
	}

	template<class T1, class T2>
	inline void _construct(T1* p, const T2& value)
	{
		new (p) T1(value);
	}

	template<class T>
	inline void _destroy(T* ptr)
	{
		ptr->~T();
	}



	template<class T>
	class Myallocator
	{
	public:
		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type =size_t;
		using difference_type = ptrdiff_t;

		template<class U>
		struct rebind
		{
			using other = Myallocator<U>;
		};


		pointer myallocate(size_type n, const void* hint = 0)
		{
			return _allocate((difference_type)n, (pointer)0);
		}

		void mydeallocate(pointer p, size_type n)
		{
			_deallocate(p); 
		}

		void myconstruct(pointer p, const T& value)
		{
			_construct(p, value);
		}

		void destory(pointer p)
		{
			_destroy(p);
		}

		pointer address(reference x)
		{
			return (pointer)&x;
		}

		const_pointer const_adress(const_reference x)
		{
			return (const_pointer)&x;
		}

		size_type max_size()const
		{
			return size_type(UINT_MAX / sizeof(T));
		}

	};
}









#endif
