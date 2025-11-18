// thl : tiny header-only library
//
// Random : class to make random numbers of uniform, gauss, exponential
//
// c++03
//
#ifndef THL_RANDOM_HH
#define THL_RANDOM_HH

#include <cstdlib>
#include <ctime>
#include <cmath>
#ifndef USE_CLOCK_GETTIME
#include <sys/time.h>
#endif

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

namespace thl {

  class Random {
   private:
    unsigned long int _seed;
   public:
    Random(unsigned int seed=0) {srandom(_seed=seed);}
    void set_seed(unsigned int seed) {srandom(_seed=seed);}
    void set_seed_by_utime(void) {
      srandom(_seed=time(0));
    }
    void set_seed_by_clock(void) {
#ifdef USE_CLOCK_GETTIME
      struct timespec tv;
      //      clock_gettime(CLOCK_MONOTONIC_RAW,&tv);
      clock_gettime(CLOCK_MONOTONIC,&tv);
      srandom(_seed=(unsigned long int)tv.tv_nsec);
#else
      struct timeval tv;
      gettimeofday(&tv, NULL);
      srandom(_seed=(unsigned long int)tv.tv_usec);
#endif
    }
    unsigned long int seed(void) {return _seed;}
    double ge0_le1(void) { // return  0 <= x <= 1
      return (double)random()/RAND_MAX;
    }
    double gt0_le1(void) { // return  0 < x <= 1
      long int n;
      do {n=random();} while( n == 0 );
      return (double)n/RAND_MAX;
    }
    double ge0_lt1(void) { // return  0 <= x < 1
      long int n;
      do {n=random();} while( n == RAND_MAX );
      return (double)n/RAND_MAX;
    }
    double gt0_lt1(void) { // return  0 < x < 1
      long int n;
      do {n=random();} while( n == 0 || n == RAND_MAX );
      return (double)n/RAND_MAX;
    }
    double uniform(double x1, double x2) {return x1 + (x2 - x1) * ge0_le1();}
    double gaus(double sigma, double mean=0) {//Box-Muller transform
      double a = gt0_le1();
      double b = ge0_le1();
      return sigma * std::sqrt(-2.*log(a))*std::sin(b*2*M_PI) + mean;
    }
    double exp(double tau) {
      double a = gt0_le1();
      return (tau>0) ? -std::log(a)/tau : (tau<0) ? std::log(a)/tau : 1.;
    }
  };

}//-- namespace thl

#endif // THL_RANDOM_HH
