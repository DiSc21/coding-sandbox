#ifndef __DS_Singleton__
#define __DS_Singleton__

#include <memory>

class DS_Singleton
{
  public:
    static std::shared_ptr<DS_Singleton> getInstance();

    int getCount() { return counter_++; }

  protected:
    DS_Singleton(){};

  private:
     static std::shared_ptr<DS_Singleton> instance_;
     int counter_{0};
};

#endif

