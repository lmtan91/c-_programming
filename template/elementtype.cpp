/*
 * elementtype.cpp
 *
 *  Created on: Mar 30, 2017
 *      Author: lia1hc
 */

#include <vector>
#include <list>
#include <stack>
#include <iostream>
#include <typeinfo>

template <typename T>
class ElementT;

template <typename T>
class ElementT<std::vector<T> >
{
public:
   typedef T Type;
};

template <typename T>
class ElementT<std::list<T> >
{
public:
   typedef T Type;
};

template <typename T>
class ElementT<std::stack<T> >
{
public:
   typedef T Type;
};

template <typename T>
void print_elem_type(T const & c)
{
   std::cout << "Container of "
             << typeid(typename ElementT<T>::Type).name()
             << " elements.\n";
}

int main()
{
   std::stack<bool> s;
   print_elem_type(s);
}
