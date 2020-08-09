
#ifndef STL_CONSTRUCT
#define STL_CONSTRUCT


#include <new>
#include <type_traits>

using namespace std;

template<typename T1, typename T2>
inline void construct(T1* p, const T2& value)
{
	new (p) T1(value);
}

template<class T>
inline void destroy(T* pointer)
{
	pointer->~T();
}

template<class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last)
{
	__destory(first, last, value_type(first));
}

template<class ForwardIterator, class T>
inline void __destory(ForwardIterator first, ForwardIterator last, T*)
{
	using trivial_destructor = typename  is_trivially_destructible<T>::type;
	_destroy_aux(first, last, trivial_destructor());
}

template<class ForwardIterator>
inline void _destroy_aux(ForwardIterator first, ForwardIterator last, false_type)
{
	for (; first < last; ++first)
	{
		destroy(&*first);
	}
}


template<class ForwardIterator>
inline void _destroy_aux(ForwardIterator first, ForwardIterator last, true_type)
{
	//do nothing
}




//这是一级容器，后面还有二级容器
template<int inst>
class _mallloc_alloc_templete
{
private:
	static void* oom_malloc(size_t);
	static void* oom_realloc(void*, size_t);
	static void (*__malloc_alloc_oom_handler)();

public:
	static void* allocate(size_t n)
	{
		void* result = malloc(n);
		if (nullptr == result) result = oom_malloc(n);
		return result;
	}


	static void deallocate(void* p, size_t)
	{
		free(p);
	}

	static void* reallocate(void* p, size_t /* old_sz */, size_t new_sz)
	{
		void* result = realloc(p, new_sz);
		if (0 == result) result = oom_realloc(p, new_sz);
		return result;
	}

};


template<int inst>
inline void* _mallloc_alloc_templete<inst>::oom_malloc(size_t n)
{
	void (*my_malloc_handler)();
	void* result;
	while (true)
	{
		my_malloc_handler = my_malloc_handler;
		if (0 == my_malloc_handler) { exit(1); }
		(*my_malloc_handler)();
		result = malloc(n);
		if (result) return result;
	}
}

template<int inst>
inline void* _mallloc_alloc_templete<inst>::oom_realloc(void*, size_t)
{



	return NULL;
}



template<typename T, typename Alloc=_mallloc_alloc_templete<0>>
class Simple_Alloc
{
public:
	using pointer = T*;
public:
	static pointer allocate(size_t n)
	{
		if (n == 0)
			return nullptr;
		void* ptr = Alloc::allocate(n*sizeof(T));
		pointer MyPointer = static_cast<pointer>(ptr);
		return MyPointer;
	}

	static pointer allocate(void)
	{
		return static_cast<pointer>(Alloc::allocate(1 * sizeof(T)));
	}
	static void deallocate(pointer p, size_t n)
	{
		Alloc::deallocate(p, n);
	
	}
	static void deallocate(pointer p) 
	{
		Alloc::deallocate(p, 1);
		
	}
};











#endif

