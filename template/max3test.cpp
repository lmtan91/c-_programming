/*
 * max3test.cpp
 *
 *  Created on: Mar 19, 2017
 *      Author: lmtan91
 *  template for pointer
 */

#include <iostream>
#include <cstring>
#include <string>

template <typename T>
inline T const& max(T const& a, T const& b)
{
   return a < b ? b : a;
}

template <typename T>
inline T* const& max(T* const& a, T* const& b)
{
   return *a < *b ? b : a;
}

template <typename T>
inline T const& max(T const& a, T const& b, T const& c)
{
   return max(max(a, b), c);
}

inline char const* const& max(char const* const&a,
                              char const* const&b)
{
   return std::strcmp(a, b) < 0 ? b : a;
}

int main()
{
   int a=17;
   int b=91;
   ::max(a, b);

   std::string s = "hey";
   std::string t = "you";
   ::max(s, t);

   int* p1 = &b;
   int* p2 = &a;
   ::max(p1, p2);

   char const* s1 = "David";
   char const* s2 = "Nico";
   std::cout << ::max(s1, s2) << std::endl;

   s1 = "frederic";
   s2 = "anica";
   const char* s3 = "lucas";
   std::cout << ::max(s1, s2, s3) << std::endl;
}
