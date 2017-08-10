/*
 * GlobalConstructor.h
 *
 *  Created on: Aug 7, 2017
 *      Author: lia1hc
 */

#ifndef GH_GLOBALCONSTRUCTOR_H_
#define GH_GLOBALCONSTRUCTOR_H_

class GlobalConstructor
{
public:
   typedef void (*GlobalConstructorFunc)();

   GlobalConstructor(GlobalConstructorFunc init) : mFunc( NULL ) { init(); }
   GlobalConstructor(GlobalConstructorFunc init, GlobalConstructorFunc destroy)
   : mFunc( destroy ) { init(); }
   ~GlobalConstructor()
   {
      if ( mFunc != NULL )
      {
         mFunc();
      }
   }
private:
   GlobalConstructorFunc mFunc;
};

#define GLOBAL_CONSTRUCT( construct ) static GlobalConstructor gh_function( construct )
#define GLOBAL_CONSTRUCT_DESTRUCT( construct, destruct ) static GlobalConstructor gh_function( construct, destruct )

#endif /* GH_GLOBALCONSTRUCTOR_H_ */
