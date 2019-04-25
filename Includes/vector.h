#pragma once
#include "base_iterator.h"

#include <algorithm>

YOBEGIN

#define THIS this->data

template<typename T, size_t _capacity>
class YOVECTOR {
public:
	 typedef YOVECTOR<T, _capacity> base;
public:
	 class iterator;

	 vector() { YO_ASSERT_THROW(_capacity < 1, "Capacity can not be less than 1!";) }
	 vector(const std::initializer_list<T> &list);
	 vector(const YOVECTOR<T> &vec);
	 ~vector();

	 void push_back(const T &item);
	 void push_back(const YOVECTOR<T> &vec);
	 void pop_back();
	 void clear();
	 void fill(const T& item);
	 void resize(size_t newsize);
	 void insert(iterator it, const T &item);
	 void erase(const iterator &it);
	 void emplace(iterator it, const T &item) { *it = item; }

	 iterator begin() { return iterator(THIS); }
	 iterator end() { return iterator(THIS + SIZE); }
	 iterator begin() const { return iterator(THIS); }
	 iterator end() const { return iterator(THIS + SIZE); }

	 bool empty()const { return SIZE == 0; }

	 size_t size() const { return SIZE; }
	 size_t capacity() { return CAP; }

	 T front() const;
	 T back() const;

	 T& operator[](size_t n);
	 T operator[](size_t n) const;

	 void operator=(const YOVECTOR<T> &other);
protected:
	 size_t SIZE = 0;
	 size_t CAP = _capacity;

	 T* data = new T[CAP];

	 void replace_data(size_t _oldsize, size_t _newsize);
	 void calculate_new_cap();
};

YOEND


template<typename T, size_t _capacity>
inline YOVECTOR<T, _capacity>::vector(const std::initializer_list<T>& list) : base() {
	 for (const T &item : list) {
		  push_back(item);
	 }
}


template<typename T, size_t _capacity>
inline YOVECTOR<T, _capacity>::vector(const YOVECTOR<T>& vec) : base() {
	 for (const auto &item : vec) {
		  push_back(item);
	 }
}


template<typename T, size_t _capacity>
inline YOVECTOR<T, _capacity>::~vector() {
	 delete[] THIS;
}


template<typename T, size_t _capacity>
inline void YOVECTOR<T, _capacity>::push_back(const T &item) {
	 calculate_new_cap();
	 THIS[SIZE++] = item;
}


template<typename T, size_t _capacity>
inline void YOVECTOR<T, _capacity>::push_back(const YOVECTOR<T> &vec) {
	 for (const auto &item : vec) {
		  push_back(item);
	 }
}


template<typename T, size_t _capacity>
inline void YOVECTOR<T, _capacity>::pop_back() {
	 YO_ASSERT_THROW(SIZE-- == 0, "Empty vector");
	 calculate_new_cap();
}


template<typename T, size_t _capacity>
inline void YOVECTOR<T, _capacity>::fill(const T& item) {
	 YO_ASSERT_THROW(SIZE == 0, "Empty vector");
	 for (size_t i = 0; i < SIZE; ++i) {
		  THIS[i] = item;
	 }
}


template<typename T, size_t _capacity>
inline void YOVECTOR<T, _capacity>::clear() {
	 replace_data(SIZE = 0, CAP = _capacity);
}


template<typename T, size_t _capacity>
inline void YOVECTOR<T, _capacity>::resize(size_t newsize) {
	 CAP = newsize < _capacity ? _capacity : newsize;
	 replace_data(SIZE < newsize ? SIZE : newsize, CAP);
	 SIZE = newsize;
}


template<typename T, size_t _capacity>
inline void YOVECTOR<T, _capacity>::insert(iterator it, const T &item) {
	 YO_ASSERT_THROW(SIZE == 0 && it != begin(), "Out of bounds";)
		  if (it == end()) {
			   push_back(item);
		  }
		  else {
			   T* pos = end()() - 1;
			   T last = back();
			   while (pos != it()) {
					*pos = *(pos - 1);
					pos--;
			   }
			   *pos = item;
			   push_back(last);
		  }
}


template<typename T, size_t _capacity>
inline void YOVECTOR<T, _capacity>::erase(const iterator &it) {
	 YO_ASSERT_THROW(it == end(), "Incorrect position");
	 T* finish = end()();
	 T* pos = it();
	 while (pos != finish) {
		  *pos = *(pos + 1);
		  ++pos;
	 }
	 pop_back();
}


template<typename T, size_t _capacity>
inline T YOVECTOR<T, _capacity>::front() const {
	 YO_ASSERT_THROW(SIZE == 0, "Empty vector");
	 return *THIS;
}


template<typename T, size_t _capacity>
inline T YOVECTOR<T, _capacity>::back() const {
	 YO_ASSERT_THROW(SIZE == 0, "Empty vector");
	 return THIS[SIZE - 1];
}


template<typename T, size_t _capacity>
inline T & YOVECTOR<T, _capacity>::operator[](size_t n) {
	 YO_ASSERT_THROW(n >= SIZE || n < 0, "Out of range");
	 return THIS[n];
}


template<typename T, size_t _capacity>
inline T YOVECTOR<T, _capacity>::operator[](size_t n) const {
	 YO_ASSERT_THROW(n >= SIZE || n < 0, "Out of range");
	 return THIS[n];
}


template<typename T, size_t _capacity>
inline void YOVECTOR<T, _capacity>::operator=(const YOVECTOR<T>& other) {
	 clear();
	 for (const T& item : other) {
		  push_back(item);
	 }
}



//.......PRIVATE..........//

template<typename T, size_t _capacity>
inline void YOVECTOR<T, _capacity>::replace_data(size_t _oldsize, size_t _newsize) {
	 T* _new = new T[_newsize];
	 for (size_t i = 0; i < _oldsize; ++i) {
		  _new[i] = THIS[i];
	 }
	 delete[] THIS;
	 THIS = _new;
}


template<typename T, size_t _capacity>
inline void YOVECTOR<T, _capacity>::calculate_new_cap() {
	 size_t new_cap = CAP * 0.5;
	 if (SIZE <= new_cap) {
		  replace_data(SIZE, CAP = new_cap < _capacity ? _capacity : new_cap);
	 }
	 else if (SIZE >= CAP) {
		  replace_data(SIZE, CAP *= 2);
	 }
}



//.......ITERATOR.....//

template<typename T, size_t _capacity>
class YOVECTOR<T, _capacity>::iterator : public _base_iterator_<T, iterator> {
public:
	 typedef _base_iterator_<T, iterator> BASE;
	 iterator(T* pointer) : _base_iterator_<T, iterator>(pointer) {}

	 bool operator==(const iterator &other) const { return BASE::pointer == other.pointer; }
	 bool operator==(const T* &other) { return BASE::pointer == other; }
	 bool operator!=(const iterator &other) { return BASE::pointer != other.pointer; }
	 bool operator!=(const T* &other) { return BASE::pointer != other; }
};
