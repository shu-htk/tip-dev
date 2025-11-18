// thl : tiny header-only library
//
// MoveAve : class to make moving average of the data
//
// c++03
//
#ifndef THL_MOV_AVE_HH
#define THL_MOV_AVE_HH

#include <vector>
#include <cmath>

namespace thl {

  template <class T> class MovAve { // Moving Average
  private:
    std::vector<T> _buf;
    std::vector<T> _vout;
    int  _nave;
    int  _index;
    bool _flag;
  public:
    MovAve() : _nave(0), _index(0), _flag(0){}
    MovAve(int nave) : _buf(nave,0), _nave(nave), _index(0), _flag(0) {}
    MovAve(std::vector<T> &vin, int nave, bool corb=1)
      : _buf(nave,0), _vout(vin.size(),0), _nave(nave), _index(0), _flag(0) {
      for(size_t j=0; j<vin.size(); j++) {
	set_val(vin[j]);
	_vout[j] = get_ave();
      }
      if( corb ) {// correct beginning of array
	for(int j=0; j < nave && j < (int)vin.size(); j++) {
	  _vout[j] = calc_ave(vin,j,j+nave);
	}
      }
    }
    void init_buf() {_index=0; _flag=0; _buf.resize(_nave,0);}
    void init_buf(int nave) {_index=0; _flag=0; _buf.resize(_nave=nave,0);}
    void set_val(T x) {
      if( _index < _nave) {
	_buf[_index] = x;
	_index++;
      } else {
	_flag = 1;
	_index = 0;
	_buf[_index] = x;
      }
    }
    T calc_ave(std::vector<T> &v, int n0, int n1) {
      double sum=0;
      for(int j=n0; j<n1; j++) sum += (double)v[j];
      return (T)(sum/(n1-n0));
    }
    T get_ave() {
      int nsum = (_flag) ? _nave : _index;
      return calc_ave(_buf,0,nsum);
    }
    std::vector<T>& data(void) {return _vout;}
    std::vector<T>& operator()(void) {return _vout;}
    T operator() (int j) {return _vout[j];}
    int get_index() {return _index;}
  };

}//-- namespace thl

#if 0
#include <cstdio>

void example1() {
  Thc::MovAve<double> ave(3);

  for(int j=0; j<10; j++) {
    ave.set_val((double)j);
    printf("%d %f %f\n",j,(double)j,ave.get_ave());
  }
}

void example2() {
  std::vector<double> vin(10);
  for(int j=0; j<vin.size(); j++) vin[j] = j;

  Thc::MovAve<double> ave(vin, 3);

  for(int j=0; j<vin.size(); j++) {
    printf("%d %f %f\n",j,vin[j],ave(j));
  }
}

int main() {
  printf("-----example1\n");
  example1();
  printf("-----example2\n");
  example2();
  return 0;
}

#endif

#endif // THL_MOV_AVE_HH
