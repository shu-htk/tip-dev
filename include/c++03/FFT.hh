// thl : tiny header-only library
//
// FFT : class for primitive FFT (Fast Fourier Transform)
//
// c++03
//
#ifndef THL_FFT_HH
#define THL_FFT_HH

#include <complex>
#include <cmath>

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

#define Complex std::complex<double> //undefined at the end of this file

namespace thl {
  class FFT {
  private:
    size_t _size0;            // size of input array
    double _dt;               // sampling interval of time-domain (sec)
    std::vector<Complex > _x; // complex array of FFT
    size_t _least_2n(size_t n) { // return the least value of 2^N larger than n
      size_t m=1; while(m < n) m <<= 1; return m;
    }
  public:
    enum {Rectangle=0, Hann=1, Hamming=2, Blackman=3, BH=4};
    int wid; // id of window functions
    double wfunc(size_t j, size_t size) { // window functions
      double x = (double)j/(double)size;
      if(wid==Hann) {return 0.5 - 0.5*std::cos(2*M_PI*x);}
      if(wid==Hamming) {return 0.54 - 0.46*std::cos(2*M_PI*x);}
      if(wid==Blackman) {
	return 0.42 - 0.5*std::cos(2*M_PI*x) + 0.08*std::cos(4*M_PI*x);
      }
      if(wid==BH) {return 0.35875 - 0.48829*std::cos(2*M_PI*x)
	  + 0.14128*std::cos(4*M_PI*x) - 0.01168*std::cos(6*M_PI*x);}
      return 1.;
    }
    FFT(void) : _size0(0),_dt(1),wid(0) {}
    FFT(size_t n, double dt=1) : _size0(0),_dt(dt),wid(0) {allocate(n);}
    void allocate(size_t n) {_x.resize(_least_2n(_size0=n));}
    size_t size0() {return _size0;}  // size of input array
    size_t size() {return _x.size();} // the least value of 2^N
    void clear() {for(size_t j=0; j<size(); j++) _x[j]=Complex(0,0);}
    double dt(void) {return _dt;} // sampling interval (sec)
    double df(void) {return 1./(_dt*size());} // sampling frequency (Hz)
    void set_dt(double dt) {_dt=dt;}
    std::vector<Complex >& data(void) {return _x;}
    Complex data(size_t j) {return _x[j];}
    double freq(size_t j) {return j/(_dt*size());} // frequency (Hz)
    double amp(size_t j) {return std::abs(_x[j]);} // amplitude
// using amp_norm freq-domain-amp ~= time-domain-amp
//    double amp_norm(size_t j) {return std::abs(_x[j])*2.056/_size0;}
    double amp_norm(size_t j) {return std::abs(_x[j])*5.246/_size0;}

    void set_complex(size_t j, Complex c) {
      if(0<=j && j<size()) _x[j] = c*wfunc(j,_size0);
    }
    void set(size_t j, double x) {
      if(0<=j && j<_size0) _x[j] = Complex(x*wfunc(j,_size0), 0);
      if(_size0<=j && j<size()) _x[j] = Complex(0,0);
    }
    void swap_index(void) {
      for(size_t j=0; j < size(); j++){
	size_t k = 0;
	for(size_t a=1, b=(size()>>1); b >= a ; b >>= 1, a <<= 1) {
	  if(b & j) k |= a;
	  if(a & j) k |= b;
	}
	if(j < k) std::swap(_x[j],_x[k]);
	//	if(j < k) {Complex tmp=_x[j]; _x[j]=_x[k]; _x[k]=tmp;}
      }
    }
    void calc(bool is_reverse=false) {
      swap_index();
      for(size_t m=2; m <= size(); m <<= 1) {
	Complex dz = std::polar(1.,-2.*M_PI/m);
	if( is_reverse ) dz = 1./dz;
	for(size_t j=0; j < size(); j += m) {
	  Complex z(1.,0);
	  for(size_t k = 0; k < (m>>1); k++) {
	    size_t a=j+k, b=j+k+(m>>1);
	    Complex tmp = z * _x[b];
	    _x[b] = _x[a] - tmp;
	    _x[a] += tmp;
	    z *= dz;
	  }
	}
      }
    }
    void reverse(void) {
      bool is_reverse = true;
      calc(is_reverse);
      for(size_t j=0; j<size(); j++) _x[j] /= (double)size();
    }
  }; // class FFT

} // namespace thl

#undef Complex

#endif// THL_FFT_HH
