// thl : tiny header-only library
//
// IsoTimeStr : class to take the time information of ISO format
//
// -std=c++03
//
#ifndef THL_ISOTIMESTR_HH
#define THL_ISOTIMESTR_HH

#include <ctime>
#include <cmath>
#include <cctype>
#ifndef USE_CLOCK_GETTIME
#include <sys/time.h>
#endif
#include "StrSplit.hh"
#include "Bracket.hh"

namespace thl {
  class IsoTimeStr { //time format of extended ISO 8601 (RFC 3339)
  private:
    char _date_buf[48]; // buffer to output date string
    char _date_fmt[24]; // output format of strftime()
    char _tsd[4]; // time string delimiters "- :"
    struct tm _t;  // structure to hold the information of local time
    double _usec;  // micro seconds of the time information
    double _utime; // unix epoch time in UTC (with precision of usec)
  public:
    IsoTimeStr(const std::string &tsd="- :") : _usec(0) {
      set_delimiters(tsd);
      tzset(); // printf("timezone=%d\n",timezone);
    }
    void print_delimiters(void) {printf("%s\n",_tsd);}
    void set_delimiters(const std::string &s) {
      snprintf(_date_fmt,24,"%s","%Y-%m-%dT%H:%M:%S");
      _tsd[0] = (s.size()>0) ? s[0] : '-';
      _tsd[1] = (s.size()>1) ? s[1] : 'T';
      _tsd[2] = (s.size()>2) ? s[2] : ':';
      _tsd[3] = '\0';
      for(char *c=&_date_fmt[0]; *c != 0; c++) {
	if(*c=='-') *c=_tsd[0];
	if(*c=='T') *c=_tsd[1];
	if(*c==':') *c=_tsd[2];
      }
    }
    const char *tsd(void) {return _tsd;}
    void get_now(void) {
#ifdef USE_CLOCK_GETTIME
      struct timespec tv;
      clock_gettime(CLOCK_REALTIME,&tv);
      _usec = 1e-3*(double)tv.tv_nsec;
#else
      struct timeval tv;
      gettimeofday(&tv, NULL);
      _usec = (double)tv.tv_usec;
#endif
      struct tm t;
      localtime_r(&tv.tv_sec, &t);
      _t = t;
      _t.tm_isdst = 0;
      _utime = (double)mktime(&_t) - timezone + 1e-6*_usec;
    }
    size_t find_end_point(const std::string &s) {//check timezone's delimiters
      int n=0,m=s.size()-7;
      if(m<0) m=0;
      if((n=s.rfind("+")) > m) {return n;}
      if((n=s.rfind("-")) > m) {return n;}
      if((n=s.rfind("Z")) > m) {return n;}
      return s.size();
    }
    int count_delimiters(const std::string &s, char delm) {
      int n=0;
      for(size_t j=0; j<s.size(); j++) {
	if(isdigit(s[j])) {if(s[j+1]==delm) {n++; j++;}}
      }
      return n;
    }
    int calc_yday(void) {
      const int mdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
      int daysum=0;
      for(int m=0; m < _t.tm_mon; m++) {
	daysum += mdays[m];
      }
      return daysum+_t.tm_mday;
    }
    int get_str(std::string str) {
      Bracket bc('"','"',str);
      std::string s = (bc.size()) ? bc.contents(0) : str; // remove quotation
      s = s.substr(0,find_end_point(s));
      int ndd = count_delimiters(s,_tsd[0]);
      int ndt = count_delimiters(s,_tsd[2]);
      StrSplit day,tim;
      if(ndd>0 && ndt>0) {
	StrSplit daytim(s,_tsd[1]);
	day.split(daytim(0),_tsd[0]);
	tim.split(daytim(1),_tsd[2]);
      }
      if(ndd==0 && ndt>0) {tim.split(s,_tsd[2]);}
      if(ndd>0 && ndt==0) {day.split(s,_tsd[0]);}
      get_now(); // get current time as default value
      int nerr=0;
      if(day.size()>0) {_t.tm_year = day.stoi(0)-1900; nerr += day.nerr();}
      if(day.size()>1) {_t.tm_mon  = day.stoi(1)-1;    nerr += day.nerr();}
      if(day.size()>2) {_t.tm_mday = day.stoi(2);      nerr += day.nerr();}
      if(tim.size()>0) {_t.tm_hour = tim.stoi(0);      nerr += tim.nerr();}
      if(tim.size()>1) {_t.tm_min  = tim.stoi(1);      nerr += tim.nerr();}
      _t.tm_yday = calc_yday();
      if(tim.size()>2) {
	if(tim(2).size()>2) {
	  double rsec = tim.stof(2);
	  double sec = std::floor(rsec);
	  _t.tm_sec = (int)sec;
	  _usec = (rsec-sec)*1e6;
	} else {
	  _t.tm_sec = tim.stoi(2);
	}
	nerr += tim.nerr();
      }
      if(tim.size()>3) {// special case: 4th field of tim() takes msec
	_usec = 1e3*tim.stof(3);
	nerr += tim.nerr();
      }
      _utime = (double)mktime(&_t) - timezone + 1e-6*_usec;
      return nerr;
    }
    double utime(void) {return _utime;}
    double str_to_utime(std::string s) {
      int nerr = get_str(s);
      return (nerr) ? 0 : utime();
    }
    const char* c_str(bool flag_us=0) {
      char tmp[32];
      strftime(tmp,32,_date_fmt,&_t);
      int us = (int)_usec;
      if(flag_us) snprintf(_date_buf,48,"%s.%.6d",tmp,us);
      else        snprintf(_date_buf,48,"%s",tmp);
      return _date_buf;
    }
    std::string str(bool flag_us=0) {
      return c_str(flag_us);
    }
    void get_utime(double utime) {
      _utime = utime + timezone;
      double sec = std::floor(_utime);
      _usec = (_utime - sec)*1e6;
      time_t tsec = (time_t)sec;
      localtime_r(&tsec, &_t);
    }
    const char* utime_to_c_str(double utime, bool flag_us=0) {
      get_utime(utime);
      return c_str(flag_us);
    }
    std::string utime_to_str(double utime, bool flag_us=0) {
      return utime_to_c_str(utime, flag_us);
    }
    int iyear(void) {return _t.tm_year+1900;}
    int imon(void) {return _t.tm_mon+1;}
    int iday(void) {return _t.tm_mday;}
    int ihour(void) {return _t.tm_hour;}
    int imin(void) {return _t.tm_min;}
    int isec(void) {return _t.tm_sec;}
    int iusec(void) {return (int)_usec;}
    int iyday(void) {return _t.tm_yday;}
    bool is_leap_year(void) {
      int y = iyear();
      return (y%4==0 && (y%100!=0 || y%400==0));
    }
    double ryear(void) {
      double maxdays = is_leap_year() ? 366 : 365;
      return (double)iyear() + ryday()/maxdays;
    }
    double rmon(void) {
      const int mdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
      int mdays_cr = (imon()==2 && is_leap_year()) ? 29 : mdays[_t.tm_mon];
      return (double)imon() + (rday()-1)/(double)mdays_cr;
    }
    double rday(void) {
      return (double)iday() + rhour()/24.;
    }
    double rhour(void) {
      return (double)ihour() + rmin()/60.;
    }
    double rmin(void) {
      return (double)imin() + rsec()/60.;
    }
    double rsec(void) {
      return (double)isec() + 1e-6*rusec();
    }
    double rusec(void) {return _usec;}
    double ryday(void) {
      return (double)iyday() + rhour()/24.;
    }
    int subtract(double utime2) {
      double utime1=utime();
      if(utime2 > utime1) {
	printf("IsoTimeStr::subtract() offset is larger than this.\n");
	return 1;
      }
      utime1 -= utime2;
      get_utime(utime1);
      return 0;
    }
    double str_to_num(const std::string &tstr, const std::string &unit) {
      if(tstr.size()==0) return 0;
      if(tstr=="now") get_now(); else get_str(tstr);
      if(unit.size()==0) return utime();
      if(unit=="utime") return utime();
      if(unit=="year") return ryear();
      if(unit=="mon") return rmon();
      if(unit=="day") return rday();
      if(unit=="hour") return rhour();
      if(unit=="min") return rmin();
      if(unit=="sec") return rsec();
      if(unit=="usec") return rusec();
      return 0;
    }
    double utime_to_num(double utim, const std::string &unit) {
      get_utime(utim);
      if(unit.size()==0) return utime();
      if(unit=="utime") return utime();
      if(unit=="year") return ryear();
      if(unit=="mon") return rmon();
      if(unit=="day") return rday();
      if(unit=="hour") return rhour();
      if(unit=="min") return rmin();
      if(unit=="sec") return rsec();
      if(unit=="usec") return rusec();
      return 0;
    }
    int distinguish_time_string(const std::string &s) {
      // distinguish "YYYY-mm-dd HH:MM:SS"
      int n0=count_delimiters(s,_tsd[0]);
      int n2=count_delimiters(s,_tsd[2]);
      if(n0==2 && n2!=2) return 1;
      if(n0!=2 && n2==2) return 2;
      if(n0==2 && n2==2) return 3;
      return 0;
    }
  };//IsoTimeStr
} //namespace thl

#endif//THL_ISOTIMESTR_HH
