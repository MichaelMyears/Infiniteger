#pragma once
#include <iostream>

#include "Includes/vector.h"


#define THIS this->data
#define OTHER other.data


class _base_infiniteger_ {
public:
	 typedef signed char                value_type;
public:
	 _base_infiniteger_                 (bool negative = false);
	 _base_infiniteger_                 (const char* number);
	 _base_infiniteger_                 (int number);


	 _base_infiniteger_ operator+       (const _base_infiniteger_ &other)const;
	 _base_infiniteger_ operator-       (const _base_infiniteger_ &other)const;
	 _base_infiniteger_ operator*       (const _base_infiniteger_ &other)const;
	 _base_infiniteger_ operator/       (const _base_infiniteger_ &other)const;
	 _base_infiniteger_ operator%       (const _base_infiniteger_ &other)const;


	 _base_infiniteger_ operator+=      (const _base_infiniteger_ &other);
	 _base_infiniteger_ operator-=      (const _base_infiniteger_ &other);
	 _base_infiniteger_ operator*=      (const _base_infiniteger_ &other);
	 _base_infiniteger_ operator/=      (const _base_infiniteger_ &other);
	 _base_infiniteger_ operator%=      (const _base_infiniteger_ &other);


	 _base_infiniteger_ operator++      ();
	 _base_infiniteger_ operator--      ();
	 _base_infiniteger_ operator++      (int);
	 _base_infiniteger_ operator--      (int);


	 _base_infiniteger_ operator=       (const char* number);
	 _base_infiniteger_ operator=       (int number);
	 _base_infiniteger_ operator=       (const _base_infiniteger_ &other);


	 bool operator==                    (const _base_infiniteger_ &other)const;
	 bool operator!=                    (const _base_infiniteger_ &other)const;
	 bool operator>                     (const _base_infiniteger_ &other)const;
	 bool operator<                     (const _base_infiniteger_ &other)const;
	 bool operator>=                    (const _base_infiniteger_ &other)const;
	 bool operator<=                    (const _base_infiniteger_ &other)const;


	 friend std::ostream& operator<<    (std::ostream &os, const _base_infiniteger_ &inf);
	 friend std::istream& operator>>    (std::istream &is, _base_infiniteger_ &inf);
private:
	 void cut_0                         ();
	 void reverse                       ();


	 _base_infiniteger_ find_multiplier (const  _base_infiniteger_ &dividend)const;
	 _base_infiniteger_ absolute        ()const;
private:
	 YOVECTOR<value_type>               data;
	 bool                               negative;
};


inline _base_infiniteger_::_base_infiniteger_(bool negative) {
	 this->negative = negative;
}


inline _base_infiniteger_::_base_infiniteger_(const char *number) {
	 negative = *number == '-' ? true : false;
	 char* current = negative ? (char*)(number + 1) : (char*)number;
	 while (*current != '\0') {
		  THIS.push_back(*current - '0');
		  current++;
	 }
	 reverse();
	 cut_0();
}


inline _base_infiniteger_::_base_infiniteger_(int number) {
	 negative = number < 0 ? true : false;
	 do {
		  THIS.push_back(abs(number % 10));
	 } while ((number /= 10) != 0);
}


inline _base_infiniteger_ _base_infiniteger_::operator+(const _base_infiniteger_ & other) const {
	 _base_infiniteger_ result;
	 if (negative != other.negative) {
		  result = (this->absolute() - other.absolute()).absolute();
		  result.negative = this->absolute() > other.absolute() ? negative : other.negative;
	 }
	 else {
		  value_type temp = 0;
		  size_t length = THIS.size() > OTHER.size() ? THIS.size() : OTHER.size();
		  for (size_t i = 0; i < length; ++i) {
			   value_type n1 = i < THIS.size() ? THIS[i] : 0;
			   value_type n2 = i < OTHER.size() ? OTHER[i] : 0;

			   result.data.push_back(n1 + n2 + temp);
			   temp = result.data.back() * 0.1;
			   result.data[i] %= 10;
		  }
		  if (temp > 0) {
			   result.data.push_back(temp);
		  }
		  result.negative = negative;
	 }
	 result.cut_0();
	 return result;
}


inline _base_infiniteger_ _base_infiniteger_::operator-(const _base_infiniteger_ & other) const {
	 _base_infiniteger_ result;
	 if (negative == other.negative) {
		  if (*this < other) {
			   result = other.absolute() - this->absolute();
			   result.negative = !negative;
		  }
		  else {
			   result = *this;
			   for (size_t i = 0; i < THIS.size(); ++i) {
					value_type n = i < OTHER.size() ? OTHER[i] : 0;
					result.data[i] -= n;
					if (result.data[i] < 0) {
						 result.data[i] += 10;
						 result.data[i + 1] -= 1;
					}
			   }
			   result.cut_0();
		  }
	 }
	 else {
		  result = this->absolute() + other.absolute();
		  result.negative = negative;
	 }
	 return result;
}


inline _base_infiniteger_ _base_infiniteger_::operator*(const _base_infiniteger_ & other) const {
	 _base_infiniteger_ result = negative == other.negative ? false : true;

	 result.data.resize(THIS.size() + OTHER.size());
	 result.data.fill(0);
	 for (size_t i = 0; i < THIS.size(); ++i) {
		  if (THIS[i] == 0) {
			   continue;
		  }
		  else {
			   int temp = 0;
			   for (size_t j = 0; j < OTHER.size(); ++j) {
					result.data[i + j] += THIS[i] * OTHER[j] + temp;
					temp = result.data[i + j] * 0.1;
					result.data[i + j] -= temp * 10;
			   }
			   if (temp > 0) {
					result.data[i + OTHER.size()] += temp;
			   }
		  }
	 }
	 result.cut_0();
	 return result;
}


inline _base_infiniteger_ _base_infiniteger_::operator/(const _base_infiniteger_ & other) const {
	 if (other == 0) throw "Dividing by zero";
	 if (this->absolute() < other.absolute()) return 0;

	 _base_infiniteger_ current = this->absolute();
	 _base_infiniteger_ result;
	 _base_infiniteger_ part;

	 while (part < other.absolute()) {
		  part.data.insert(part.data.begin(), current.data.back());
		  current.data.pop_back();
	 }
	 _base_infiniteger_ tempResult = part.find_multiplier(other.absolute());
	 result.data.push_back(tempResult.data);

	 part -= tempResult * other.absolute();
	 while (current.data.empty() == false) {
		  if (part == 0) part.data.clear();

		  part.data.insert(part.data.begin(), current.data.back());
		  current.data.pop_back();

		  if (part < other.absolute()) {
			   result.data.push_back(0);
		  }
		  else {
			   _base_infiniteger_ tempResult = part.find_multiplier(other.absolute());
			   result.data.push_back(tempResult.data);
			   part -= tempResult * other.absolute();
		  }
	 }
	 result.negative = negative == other.negative ? false : true;
	 result.reverse();
	 result.cut_0();
	 return result;
}


inline _base_infiniteger_ _base_infiniteger_::operator%(const _base_infiniteger_ & other) const {
	 if (other == 0) throw "Dividing by zero";
	 if (this->absolute() < other.absolute()) return *this;
	 if (*this == other) return 0;

	 _base_infiniteger_ current = this->absolute();
	 _base_infiniteger_ part;

	 while (part < other.absolute()) {
		  part.data.insert(part.data.begin(), current.data.back());
		  current.data.pop_back();
	 }

	 part -= part.find_multiplier(other.absolute()) * other.absolute();
	 while (current.data.empty() == false) {
		  if (part == 0) part.data.clear();

		  part.data.insert(part.data.begin(), current.data.back());
		  current.data.pop_back();
		  part -= part.find_multiplier(other.absolute()) * other.absolute();
	 }

	 part.negative = negative == other.negative ? false : true;
	 part.cut_0();
	 return part;
}


inline _base_infiniteger_ _base_infiniteger_::operator+=(const _base_infiniteger_ & other) {
	 return *this = *this + other;
}


inline _base_infiniteger_ _base_infiniteger_::operator-=(const _base_infiniteger_ & other) {
	 return *this = *this - other;
}


inline _base_infiniteger_ _base_infiniteger_::operator*=(const _base_infiniteger_ & other) {
	 return *this = *this * other;
}


inline _base_infiniteger_ _base_infiniteger_::operator/=(const _base_infiniteger_ & other) {
	 return *this = *this / other;
}


inline _base_infiniteger_ _base_infiniteger_::operator%=(const _base_infiniteger_ & other) {
	 return *this = *this % other;
}


inline _base_infiniteger_ _base_infiniteger_::operator++() {
	 return *this += 1;
}


inline _base_infiniteger_ _base_infiniteger_::operator--() {
	 return *this -= 1;
}


inline _base_infiniteger_ _base_infiniteger_::operator++(int) {
	 _base_infiniteger_ result = *this;
	 *this += 1;
	 return result;
}


inline _base_infiniteger_ _base_infiniteger_::operator--(int) {
	 _base_infiniteger_ result = *this;
	 *this -= 1;
	 return result;
}


inline _base_infiniteger_ _base_infiniteger_::operator=(const char * number) {
	 THIS.clear();
	 negative = *number == '-' ? true : false;
	 char* current = negative ? (char*)(number + 1) : (char*)number;
	 while (*current != '\0') {
		  THIS.push_back(*current - '0');
		  current++;
	 }
	 reverse();
	 cut_0();
	 return *this;
}


inline _base_infiniteger_ _base_infiniteger_::operator=(int number) {
	 negative = number < 0 ? true : false;
	 do {
		  THIS.push_back(abs(number % 10));
	 } while ((number /= 10) != 0);
	 return *this;
}


inline _base_infiniteger_ _base_infiniteger_::operator=(const _base_infiniteger_ &other) {
	 negative = other.negative;
	 THIS = OTHER;
	 return *this;
}


inline bool _base_infiniteger_::operator==(const _base_infiniteger_ & other) const {
	 if (negative != other.negative) {
		  return false;
	 }
	 else if (THIS.size() != OTHER.size()) {
		  return false;
	 }
	 else {
		  size_t index = THIS.size() - 1;
		  do {
			   if (THIS[index] != OTHER[index]) {
					return false;
			   }
		  } while (index-- > 0);
		  return true;
	 }
}


inline bool _base_infiniteger_::operator!=(const _base_infiniteger_ & other) const {
	 return !(*this == other);
}


inline bool _base_infiniteger_::operator>(const _base_infiniteger_ & other) const {
	 if (negative > other.negative) {
		  return false;
	 }
	 else if (negative < other.negative) {
		  return true;
	 }
	 else if (THIS.size() > OTHER.size()) {
		  return true;
	 }
	 else if (THIS.size() < OTHER.size()) {
		  return false;
	 }
	 else {
		  size_t index = THIS.size() - 1;
		  do {
			   if (THIS[index] > OTHER[index]) {
					return true;
			   }
			   else if (THIS[index] < OTHER[index]) {
					return false;
			   }
		  } while (index-- > 0);
		  return false;
	 }
}


inline bool _base_infiniteger_::operator<(const _base_infiniteger_ & other) const {
	 if (negative > other.negative) {
		  return true;
	 }
	 else if (negative < other.negative) {
		  return false;
	 }
	 else if (THIS.size() > OTHER.size()) {
		  return false;
	 }
	 else if (THIS.size() < OTHER.size()) {
		  return true;
	 }
	 else {
		  size_t index = THIS.size() - 1;
		  do {
			   if (THIS[index] > OTHER[index]) {
					return false;
			   }
			   else if (THIS[index] < OTHER[index]) {
					return true;
			   }
		  } while (index-- > 0);
		  return false;
	 }
}


inline bool _base_infiniteger_::operator>=(const _base_infiniteger_ & other) const {
	 if (negative > other.negative) {
		  return false;
	 }
	 else if (negative < other.negative) {
		  return true;
	 }
	 else if (THIS.size() > OTHER.size()) {
		  return true;
	 }
	 else if (THIS.size() < OTHER.size()) {
		  return false;
	 }
	 else {
		  size_t index = THIS.size() - 1;
		  do {
			   if (THIS[index] > OTHER[index]) {
					return true;
			   }
			   else if (THIS[index] < OTHER[index]) {
					return false;
			   }
		  } while (index-- > 0);
		  return true;
	 }
}


inline bool _base_infiniteger_::operator<=(const _base_infiniteger_ & other) const {
	 if (negative > other.negative) {
		  return true;
	 }
	 else if (negative < other.negative) {
		  return false;
	 }
	 else if (THIS.size() > OTHER.size()) {
		  return false;
	 }
	 else if (THIS.size() < OTHER.size()) {
		  return true;
	 }
	 else {
		  size_t index = 0;
		  do {
			   if (THIS[index] > OTHER[index]) {
					return false;
			   }
			   else if (THIS[index] < OTHER[index]) {
					return true;
			   }
		  } while (index-- > 0);
		  return true;
	 }
}


inline void _base_infiniteger_::cut_0() {
	 while (THIS.empty() == false) {
		  if (THIS.back() == 0) {
			   THIS.pop_back();
		  }
		  else {
			   break;
		  }
	 }
	 if (THIS.empty() == true) {
		  negative = false;
		  THIS.push_back(0);
	 }
}


inline void _base_infiniteger_::reverse() {
	 size_t index = 0;
	 size_t end = THIS.size() - 1;
	 size_t middle = end * 0.5;
	 do {
		  value_type temp = THIS[index];
		  THIS[index] = THIS[end - index];
		  THIS[end - index] = temp;
	 } while (index++ < middle);
}


inline _base_infiniteger_ _base_infiniteger_::find_multiplier(const _base_infiniteger_ &dividend) const {
	 _base_infiniteger_ current = this->absolute();
	 _base_infiniteger_ result = 0;
	 while (current >= dividend) {
		  current -= dividend;
		  ++result;
	 }
	 return result;
}


inline _base_infiniteger_ _base_infiniteger_::absolute() const {
	 return *this < 0 ? *this * (-1) : *this;
}


inline std::ostream& operator<<(std::ostream & os, const _base_infiniteger_ &inf) {
	 if (inf.negative) os << '-';
	 size_t index = inf.data.size() - 1;
	 do {
		  os << (short)inf.data[index];
	 } while (index-- > 0);
	 return os;
}


inline std::istream & operator>>(std::istream & is, _base_infiniteger_ &inf) {
	 char* str = new char;
	 is >> str;
	 inf = str;
	 return is;
}





typedef _base_infiniteger_ inf_t;