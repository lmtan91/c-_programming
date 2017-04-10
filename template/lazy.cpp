/*
 * lazy.cpp
 *
 *  Created on: Mar 22, 2017
 *      Author: lia1hc
 */



template <typename T>
class Safe
{
};

template <int N>
class Danger
{
public:
   typedef char Block[N]; // would fail for N<=0
};

template <typename T, int N>
class Tricky
{
public:
   virtual ~Tricky() {}
   void no_body_here(Safe<T> = 3);
   void inclass()
   {
      Danger<N> no_boom_yet;
   }
   // void error() { Danger<0> boom; }
   void unsafe(T (*p)[N]);
   T operator->();
   // virtual Safe<T> suspect();
   struct Nested
   {
      Danger<N> pfew;
   };

   union
   { // anonymous union
      int align;
      //Safe<T> anonymous;
      Danger<N> anonymous;
   };
};


int main()
{
   Tricky<int, 0> ok;
}
