#pragma once
#include "Infiniteger.h"


inf_t abs(const inf_t &n) {
	 return n < 0 ? n * (-1) : n;
}


inf_t pow(const inf_t &base, inf_t n) {
	 inf_t result = base;
	 while (n-- > 1) {
		  result *= base;
	 }
	 return result;
}


inf_t square(const inf_t &base, const inf_t &degree = 2) {
	 inf_t left = 0;
	 inf_t right = base / 2;
	 while (left <= right) {
		  inf_t mid = (left + right) / 2;
		  inf_t current = pow(mid, degree);

		  if (base >= current) {
			   if (base - current <= mid) {
					return mid;
			   }
			   else {
					left = mid + 1;
			   }
		  }
		  else {
			   if (current - base <= mid) {
					return mid - 1;
			   }
			   else {
					right = mid - 1;
			   }
		  }
	 }
	 return 1;
}


bool issimple(const inf_t &n) {
	 int simples[4] = { 2, 3, 5, 7};
	 if (n <= 4) {
		  for (size_t i = 0; i < 4; ++i) {
			   if (n == simples[i]) {
					return true;
			   }
		  }
		  return false;
	 }
	 else {
		  inf_t end = square(n + 1);
		  inf_t current = 3;
		  while (current <= end) {
			   if (n % current == 0) {
					return false;
			   }
			   else {
					current += 2;
			   }
		  }
		  return true;
	 }
}
