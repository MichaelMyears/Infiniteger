#pragma once
#include "yo_namespace.h"

YOBEGIN

template<typename T, typename Derived>
class _base_iterator_ {
public:
	 typedef _base_iterator_<T, typename Derived> BASE;

	 _base_iterator_(T* p) { pointer = p; }

	 Derived& operator++() { return *BASE(++pointer).self(); };
	 Derived& operator++(int) { return *BASE(pointer++).self(); };
	 Derived& operator--() { return *BASE(--pointer).self(); };
	 Derived& operator--(int) { return *BASE(pointer--).self(); };
	 Derived& operator+(int n) { return *BASE(pointer + n).self(); }
	 Derived& operator-(int n) { return *BASE(pointer - n).self(); }

	 T*& operator->() { return pointer; }
	 T* operator->() const { return pointer; }
	 T*& operator()() { return pointer; }
	 T* operator()() const { return pointer; }
	 T& operator*() { return *pointer; }
	 T operator*() const { return *pointer; }
protected:
	 T* pointer;
private:
	 Derived* self() { return static_cast<Derived*>(this); }
};

YOEND