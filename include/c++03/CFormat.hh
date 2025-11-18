// thl : tiny header-only library
//
// CFormat : class to get c_str() by printf's format
//
// c++03
//
#ifndef THL_CFORMAT_HH
#define THL_CFORMAT_HH

#include <string>
#include <cstdio>
#include <cstdarg>

namespace thl {
  class CFormat {
  private:
    std::string _buf;
  public:
    CFormat(size_t n=16) {_buf.resize(n);}
    const char* operator() (const char *fmt, ...) {
      while(1) {
	size_t size = _buf.size();
	va_list ap;
	va_start(ap, fmt);
	size_t n = vsnprintf(&_buf[0], size, fmt, ap);
	va_end(ap);
	if(n >= size) {
	  _buf.resize(size*2);
	} else break;
      }
      _buf=_buf.c_str(); // copy c_str() to resize the _buf
      return _buf.c_str();
    }

    const char* operator() (void) {return _buf.c_str();}

    const std::string str(void) {return _buf;}
    
  };//-- class CFormat
}//-- namespace thl

#endif //THL_CFORMAT_HH
