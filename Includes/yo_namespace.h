#pragma once
#include <iostream>
#include <initializer_list>

#define YO_ASSERT_THROW(statement, message) if(statement == true) throw message

#define YOBEGIN namespace yo{
#define YOEND }

#define YOLIST yo::list
#define YOARRAY yo::array
#define YOHASH yo::hash
#define YOVECTOR yo::vector

#define NEXUS nexus<T>
#define CELL cell<KEY, DATA>





YOBEGIN

template<typename T, typename Derived>
class _base_iterator_;

template<typename T>
struct nexus {
	 nexus* right = nullptr;
	 nexus* left = nullptr;
	 T item;

	 nexus() {}
	 nexus(const T &item) { this->item = item; }
};

template<typename KEY, typename DATA>
struct cell {
	 KEY key;
	 DATA data;
	 bool operator==(const KEY &key)const { return this->key == key; }
};

template<typename T>
class _My_iterator_;

template <typename T>
class list;

template<typename T, uint32_t size>
class array;

template<typename T, size_t _capacity = 32>
class vector;

template<typename KEY, typename DATA, uint32_t SIZE = 5167>
class hash;







//.......functions.........//
template<typename Iterator, typename Item>
Iterator find(Iterator begin, const Iterator &end, const Item &item) {
	 while (begin != end) {
		  if (*begin == item) {
			   return begin;
		  }
		  else {
			   ++begin;
		  }
	 }
	 return Iterator(nullptr);
}

template<typename T>
void swap(T& item1, T& item2) {
	 T temp = item1;
	 item1 = item2;
	 item2 = temp;
}

YOEND