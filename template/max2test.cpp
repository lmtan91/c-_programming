/*
 * max2test.cpp
 *
 *  Created on: Mar 19, 2017
 *      Author: lmtan91
 *  template function overloading example
 */

inline int const& max(int const& a, int const& b)
{
   return a > b ? a : b;
}

template <typename T>
T const& max(T const& a, T const& b)
{
   return a > b ? a : b;
}

template <typename T>
T const& max(T const& a, T const& b, T const& c)
{
   return max(max(a, b), c);
}

int main()
{
   ::max(17, 12, 91);
   ::max(17.0, 12.0);
   ::max('a', 'b');
   ::max(17, 12);
   ::max<>(17, 12);
   ::max<double>(17, 12);
   ::max('a', 17.13);
}
