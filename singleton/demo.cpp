#include "singleton.h"

class TestContainer
{
public:
  int GetA()
  {
    return a;
  }
  
private:
  Test() {}
  friend class SingletonClass<Test>; 
  int a;
}

#define TEST_CNTER SingletonClass<Test>::get_instance()
