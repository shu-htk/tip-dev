// thl : tiny header-only library
//
// Random : class to make random numbers of uniform, gauss, exponential
//
// c++11
//
#ifndef THL_RANDOM_HH
#define THL_RANDOM_HH

#include <random>
#include <ctime>
#include <cmath>
#ifndef USE_CLOCK_GETTIME
#include <sys/time.h>
#endif

namespace thl {

  class Random {
   private:
    std::mt19937 _mt;
    std::random_device _rd;
    unsigned long int _seed;
   public:
    Random(unsigned int seed=0) {set_seed(seed);}
    void set_seed(unsigned int seed) {_mt.seed(_seed=seed);}
    void set_seed_by_device(void) {
      _mt.seed(_rd());
    }
    void set_seed_by_utime(void) {
      _mt.seed(_seed=time(0));
    }
    void set_seed_by_clock(void) {
#ifdef USE_CLOCK_GETTIME
      struct timespec tv;
      //      clock_gettime(CLOCK_MONOTONIC_RAW,&tv);
      clock_gettime(CLOCK_MONOTONIC,&tv);
      _mt.seed(_seed=(unsigned long int)tv.tv_nsec);
#else
      struct timeval tv;
      gettimeofday(&tv, NULL);
      _mt.seed(_seed=(unsigned long int)tv.tv_usec);
#endif
    }
    unsigned long int seed(void) {return _seed;}
    double uniform(double x1, double x2) {
      std::uniform_real_distribution<double> dist(x1, x2);
      return dist(_mt);
    }
    double gaus(double sigma, double mean=0) {//Box-Muller transform
      std::normal_distribution<double> dist(mean, sigma);
      return dist(_mt);
    }
    double exp(double tau) {
      if(tau==0) return 1;
      if(tau<0) tau=-tau;
      std::exponential_distribution<double> dist(tau);      
      return dist(_mt);
    }
  };

}//-- namespace thl

#endif // THL_RANDOM_HH
