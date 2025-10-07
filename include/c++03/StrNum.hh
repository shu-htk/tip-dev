// thl : tiny header-only library
//
// StrNum : class to convert string to number
//
// -std=c++03
//
#ifndef THL_STRNUM_HH
#define THL_STRNUM_HH

#include <string>
#include <climits>
#include <cfloat>
#include <cstdlib>
#include <cerrno>

namespace thl {
  class StrNum { // string conversion to the number
  private:
    int _nerr;
    int _verb; // verbose level
    char _pchar; // post character after the number
  public:
    StrNum(void) : _nerr(0), _verb(1), _pchar(0) {}
    int nerr() {return _nerr;}
    void set_verbose(int n) {_verb=n;}
    char pchar(void) {return _pchar;}
    const int stoi(const std::string &s) {
      long ret = stol(s);
      if(ret >= INT_MAX || ret <= INT_MIN) {
	_nerr=3;
	if(_verb>0) fprintf(stderr,"StrNum::stoi(): INT out of range\n");
      }
      return (int)ret;
    }
    const long stol(const std::string &s) {
      _nerr=0; errno=0;
      const char *start_ptr=s.c_str();
      char *end_ptr=0;
      long ret = (long)strtoll(start_ptr,&end_ptr,10);
      _pchar = *end_ptr;
      if(errno==ERANGE) {
	_nerr=1;
	if(_verb>0)
	  fprintf(stderr,"StrNum::stol(): out of numerical range\n");
      } else if(end_ptr==start_ptr) {
	_nerr=2;
	if(_verb>0)
	  fprintf(stderr,"StrNum::stol(): not a number [%s]\n",s.c_str());
      }
      if(ret >= LONG_MAX || ret <= LONG_MIN) {
	_nerr=3;
	if(_verb>0)
	  fprintf(stderr,"StrNum::stol(): LONG out of range\n");
      }
      return ret;
    }
    const double stof(const std::string &s) {
      _nerr=0; errno=0;
      const char *start_ptr=s.c_str();
      char *end_ptr=0;
      double ret=strtod(start_ptr,&end_ptr);
      _pchar = *end_ptr;
      if(errno==ERANGE) {
	_nerr=1;
	if(_verb>0)
	  fprintf(stderr,"StrNum::stof(): out of numerical range\n");
      } else if(end_ptr==start_ptr) {
	_nerr=2;
	if(_verb>0)
	  fprintf(stderr,"StrNum::stof(): not a number [%s]\n",s.c_str());
      }
      if(ret >= DBL_MAX || ret <= -DBL_MAX) {
	_nerr=3;
	if(_verb>0)
	  fprintf(stderr,"StrNum::stof(): DOUBLE out of range\n");
      }
      return ret;
    }
  };//class StrNum
}//namespace thl

#endif //THL_STRNUM_HH
