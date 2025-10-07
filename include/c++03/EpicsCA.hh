// thl : tiny header-only library
//
// EpicsCA : wrapper class for EPICS channel access
//
// -std=c++03
//
#ifndef THL_EPICS_CA_HH
#define THL_EPICS_CA_HH

#include <sys/time.h> // localtime_r(), ...
#include <unistd.h> // sleep(), usleep()
#include <cstdarg> // vsnprintf(),...
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cadef.h> // original epics include file
#include <vector>

namespace thl {
// ca_real is defined as double in EPICS
  ca_real ConnectionTimeout = 2.0;

  void EpicsCA_default_event_handler(struct event_handler_args args);

  class EpicsCA {// EPICS Channel Access wrapper class
  private:
    enum {MAX_STRLEN=40};
    chid _chid;
    char _name[215];
    char _val_string[MAX_STRLEN];
    std::vector<double> _val;
    std::vector<double> _last_val;
    unsigned long _event_mask;
    bool _connected;
    bool _mon_flag;
    struct timeval _tv;
    char _time_str[128];
    int _option;
  public:
    enum {DEBUG=0x1, ENABLE_LAST_VAL=0x2, ENABLE_MONITOR=0x4};

    EpicsCA() : _chid(0), _connected(0), _mon_flag(0) {
      _event_mask = DBE_VALUE | DBE_ALARM; _option = 0;
    }
    EpicsCA(const char *name, const char *opt="")
      : _chid(0), _connected(0), _mon_flag(0) {
      _event_mask = DBE_VALUE | DBE_ALARM; _option = 0;
      connect(name,opt);
    }
    ~EpicsCA() {disconnect();}
    void disconnect() {
      if( _connected ) {
	ca_context_destroy();
	_connected = false;
	_mon_flag = 0;
	if(_option & DEBUG) fprintf(stderr,"EpicsCA [%s] closed.\n",_name);
      }
    }
    bool connect(const char *name) {
      if( _connected ) {disconnect();  usleep(1000);}
      snprintf(_name,215,"%s",name);
      SEVCHK(ca_task_initialize(),"EpicsCA init failed");
      SEVCHK(ca_search(name,&_chid),"EpicsCA connect() invalid name");
      if(ca_pend_io(ConnectionTimeout) == ECA_TIMEOUT) {
	fprintf(stderr,"EpicsCA [%s] connection timeout\n",name);
	_connected = false;
      } else {
	_connected = true;
	_val.resize(n_elems(),0);
	if(_option & DEBUG) fprintf(stderr,"EpicsCA [%s] opened.\n",_name);
	if(_option & ENABLE_LAST_VAL) {
	  _last_val.resize(n_elems(),0);
	  if(_option & DEBUG)
	    fprintf(stderr,"EpicsCA [%s] allocated _last_val.\n",_name);
	}
	if(_option & ENABLE_MONITOR) monitor();
      }
      return _connected;
    }
    bool connect(const char *name, const char *opt) {
      for(const char *c=opt; *c!=0; c++) {
	if(*c=='d') set_option(DEBUG);
	if(*c=='l') set_option(ENABLE_LAST_VAL);
	if(*c=='m') set_option(ENABLE_MONITOR);
      }
      return connect(name);
    }
    void poll(double wait_sec=0.001) {
      usleep((int)(wait_sec*1000000));
      ca_poll();
    }
    void set_option(int flag) {_option |= flag;}
    void reset_option(int flag) {_option &= (~flag);}
    int option() {return _option;}
    bool is_connected() {return _connected;}
    chid get_chid() {return _chid;}
    const char *name() {return _name;}
    const char *host() {return ca_host_name(_chid);}
    long dbf_type() {return ca_field_type(_chid);}
    long dbr_type() {return dbf_type_to_DBR(dbf_type());}
    int status() {return ca_state(_chid);}
    int n_elems() {return (int)ca_element_count(_chid);}
    bool read_ok() {return ca_read_access(_chid);}
    bool write_ok() {return ca_write_access(_chid);}
    const char *val_string() {return _val_string;}
    char  val_char(int j=0) {
      return (j<n_elems())? ((char*)_val.data())[j] : 0;
    }
    short val_short(int j=0) {
      return (j<n_elems())? ((short*)_val.data())[j] : 0;
    }
    long  val_long(int j=0) {
      return (j<n_elems())? ((long*)_val.data())[j] : 0;
    }
    float val_float(int j=0) {
      return (j<n_elems())? ((float*)_val.data())[j] : 0;
    }
    double val_double(int j=0) {return (j<n_elems())?_val[j] :0;}
    double *p_val() {return _val.data();}
    double *p_last_val() {return _last_val.data();}

    double val(int j=0) {
      switch( dbr_type() ) {
      case DBR_STRING:
	fprintf(stderr,"EpicsCA [%s] refers DBR_STRING\n",_name);
	return 0;
      case DBR_SHORT: // case DBR_INT:
      case DBR_ENUM:
	return (double)val_short(j);
      case DBR_FLOAT:
	return (double)val_float(j);
      case DBR_CHAR:
	return (double)val_char(j);
      case DBR_LONG:
	return (double)val_long(j);
      case DBR_DOUBLE:
	return val_double(j);
      default:
	fprintf(stderr,"EpicsCA [%s] unknown dbr_type\n",_name);
	return 0;
      }
    }
    double get_val(int j=0, int n_req=0, double timeout=10.0) {
      get(n_req,timeout); return val(j);
    }
    const char *get_string(int n_req=0, double timeout=10.0) {
      get(n_req,timeout); return val_string();
    }
    char  get_char(int j=0, int n_req=0, double timeout=10.0) {
      get(n_req,timeout); return val_char(j);
    }
    short get_short(int j=0, int n_req=0, double timeout=10.0) {
      get(n_req,timeout); return val_short(j);
    }
    long  get_long(int j=0, int n_req=0, double timeout=10.0) {
      get(n_req,timeout); return val_long(j);
    }
    float get_float(int j=0, int n_req=0, double timeout=10.0) {
      get(n_req,timeout); return val_float(j);
    }
    double get_double(int j=0, int n_req=0, double timeout=10.0) {
      get(n_req,timeout); return val_double(j);
    }

    double last_val_double(int j=0) {
      if(_option & ENABLE_LAST_VAL) return (j<n_elems())?_last_val[j] :0;
      else return 0;
    }

    bool val_updated(int n_req=0) {// compare only first n_req elements at most
      if(_option & ENABLE_LAST_VAL) {
	int n = (n_req) ? n_req : n_elems();
	for(int j=0; j < n; j++) {
	  if( _val[j] != _last_val[j] ) {
	    for(int k=0; k < n; k++) _last_val[k] = _val[k]; 
	    return true;
	  }
	}
      }
      return false;
    }

    bool get(int n_req=0, double timeout=10.0) {
      if(! _connected ) return false;
      int n = (n_req) ? n_req : n_elems();
      switch( dbr_type() ) {
      case DBR_STRING:
	ca_array_get(DBR_STRING, 1u, _chid, _val_string);
	_val_string[MAX_STRLEN-1] = 0; break;
      case DBR_SHORT: // case DBR_INT:
      case DBR_ENUM:
	ca_array_get(DBR_SHORT, n, _chid, (short*)_val.data()); break;
      case DBR_FLOAT:
	ca_array_get(DBR_FLOAT, n, _chid, (float*)_val.data()); break;
      case DBR_CHAR:
	ca_array_get(DBR_CHAR, n, _chid, (char*)_val.data()); break;
      case DBR_LONG:
	ca_array_get(DBR_LONG, n, _chid, (long*)_val.data()); break;
      case DBR_DOUBLE:
	ca_array_get(DBR_DOUBLE, n, _chid, _val.data()); break;
      default:
	break;
      }
      if( ca_pend_io(timeout) == ECA_TIMEOUT ) {
	fprintf(stderr,"EpicsCA [%s] get() timed out\n",_name);
	return false;
      } else {
	get_time();
	if(_option & ENABLE_LAST_VAL) return val_updated(n);
	else return true;
      }
    }

    void set_string(const char *s) {snprintf(_val_string,MAX_STRLEN,"%s",s);}
    void set_char(char x) {((char*)_val.data())[0] = x;}
    void set_short(short x) {((short*)_val.data())[0] = x;}
    void set_float(float x) {((float*)_val.data())[0] = x;}
    void set_long(long x) {((long*)_val.data())[0] = x;}
    void set_double(double x) {_val[0] = x;}
    void set_val_by_string(const char *val_string) {
      set_val_by_string(0,val_string);
    }
    void set_char(int j, char x) {((char*)_val.data())[j] = x;}
    void set_short(int j, short x) {((short*)_val.data())[j] = x;}
    void set_float(int j, float x) {((float*)_val.data())[j] = x;}
    void set_long(int j, long x) {((long*)_val.data())[j] = x;}
    void set_double(int j, double x) {_val[j] = x;}
    void set_val_by_string(int j, const char *val_string) {
      switch( dbr_type() ) {
      case DBR_STRING:
	set_string(val_string); break;
      case DBR_SHORT: // case DBR_INT:
      case DBR_ENUM:
	set_short(j,(short)atoi(val_string)); break;
      case DBR_FLOAT:
	set_float(j,(float)atof(val_string)); break;
      case DBR_CHAR:
	set_char(j,(char)atoi(val_string)); break;
      case DBR_LONG:
	set_long(j,(long)atoi(val_string)); break;
      case DBR_DOUBLE:
	set_double(j,(double)atof(val_string)); break;
      default:
	break;
      }
    }
    void put_string(const char *s) {set_string(s); put();}
    void put_char(char x) {set_char(x); put();}
    void put_short(short x) {set_short(x); put();}
    void put_float(float x) {set_float(x); put();}
    void put_long(long x) {set_long(x); put();}
    void put_double(double x) {set_double(x); put();}
    void put_val_by_string(const char *val_string) {
      set_val_by_string(val_string); put();
    }
    bool put() {
      if(! _connected ) return false;
      int n = n_elems();
      switch( dbr_type() ) {
      case DBR_STRING:
	ca_array_put(DBR_STRING, 1u, _chid, _val_string); break;
      case DBR_SHORT: // case DBR_INT:
      case DBR_ENUM:
	ca_array_put(DBR_SHORT, n, _chid, (short*)_val.data()); break;
      case DBR_FLOAT:
	ca_array_put(DBR_FLOAT, n, _chid, (float*)_val.data()); break;
      case DBR_CHAR:
	ca_array_put(DBR_CHAR, n, _chid, (char*)_val.data()); break;
      case DBR_LONG:
	ca_array_put(DBR_LONG, n, _chid, (long*)_val.data()); break;
      case DBR_DOUBLE:
	ca_array_put(DBR_DOUBLE, n, _chid, (double*)_val.data()); break;
      default:
	break;
      }
      if( ca_pend_io(10.0) == ECA_TIMEOUT ) {
	fprintf(stderr,"EpicsCA [%s] put() timed out\n",_name);
	return false;
      } else {
	ca_flush_io();
	get_time();
	return true;
      }
    }

    void set_event_mask(unsigned long event_mask) {_event_mask = event_mask;}

    bool monitor(caEventCallBackFunc *event_handler, void *usr_arg) {
      if(! _connected ) {reset_option(ENABLE_MONITOR); return false;}
      else set_option(ENABLE_MONITOR);
      ca_create_subscription(dbr_type(), n_elems(), get_chid(), _event_mask,
			     event_handler, usr_arg, NULL);
      if(_option & DEBUG)
	fprintf(stderr,"EpicsCA [%s] monitor with user handler.\n",_name);
      return true;
    }

    bool monitor(int n_req=0) {
      if(! _connected ) {reset_option(ENABLE_MONITOR); return false;}
      else set_option(ENABLE_MONITOR);
      if(n_req <= 0|| n_req > n_elems() ) n_req = n_elems();
      ca_create_subscription(dbr_type(), n_req, get_chid(), _event_mask,
			     EpicsCA_default_event_handler, (void *)this, NULL);
      if(_option & DEBUG)
	fprintf(stderr,"EpicsCA [%s] monitor with default handler.\n",_name);
      return true;
    }

    bool set_monitor_data(struct event_handler_args &args) {
      if(!(_option & ENABLE_MONITOR) ) return false;
      if(args.status == ECA_NORMAL) {
	get_time();
	if( args.type == DBR_STRING ) 
	  snprintf(_val_string,MAX_STRLEN,"%s",(char*)args.dbr);
	else
	  memcpy(_val.data(), args.dbr, dbr_size_n(args.type, args.count));
	return _mon_flag = true;
      }
      return false;
    }

    bool mon_flag() {return _mon_flag;}

    void reset_mon_flag() {_mon_flag = false;}

    void pend_event(double timeout=0.0) {ca_pend_event(timeout);}

    void get_time() {gettimeofday(&_tv, NULL);}

    struct timeval get_tv() {return _tv;}

    const char *time_str() {
      struct tm t;
      localtime_r(&_tv.tv_sec, &t);
      int usec = _tv.tv_usec;
      snprintf(_time_str,128,"%.4d-%.2d-%.2d %.2d:%.2d:%.2d.%.6d",
	       t.tm_year+1900, t.tm_mon+1, t.tm_mday, t.tm_hour,
	       t.tm_min, t.tm_sec, usec);
      return _time_str;
    }

    void print_val(int n_req=0, bool omit_flag=0, FILE *fp = stdout,
		   int prec=0) {
      int n = (n_req>0) ? n_req : n_elems();
      if( ! omit_flag ) {
	if( n == 1 )
	  fprintf(fp,"%s %s ", name(), time_str());
	else
	  fprintf(fp,"%s %s %d", name(), time_str(), n);
      }
      switch(dbr_type()) {
      case DBR_STRING:
	fprintf(fp," %s",val_string());
	break;
      case DBR_SHORT: // case DBR_INT:
	for(int j=0; j<n; j++) fprintf(fp," %d",((short*)_val.data())[j]);
	break;
      case DBR_ENUM:
	for(int j=0; j<n; j++) fprintf(fp," %d",((short*)_val.data())[j]);
	break;
      case DBR_FLOAT:
	for(int j=0; j<n; j++) fprintf(fp," %f",((float*)_val.data())[j]);
	break;
      case DBR_CHAR:
	for(int j=0; j<n; j++) fprintf(fp," %d",((char*)_val.data())[j]);
	break;
      case DBR_LONG:
	for(int j=0; j<n; j++) fprintf(fp," %ld",((long*)_val.data())[j]);
	break;
      case DBR_DOUBLE:
	if( prec ) {
	  if(prec==1) for(int j=0; j<n; j++) fprintf(fp," %.1lf",_val[j]);
	  if(prec==2) for(int j=0; j<n; j++) fprintf(fp," %.2lf",_val[j]);
	  if(prec==3) for(int j=0; j<n; j++) fprintf(fp," %.3lf",_val[j]);
	  if(prec==4) for(int j=0; j<n; j++) fprintf(fp," %.4lf",_val[j]);
	  if(prec==5) for(int j=0; j<n; j++) fprintf(fp," %.5lf",_val[j]);
	  if(prec==6) for(int j=0; j<n; j++) fprintf(fp," %.6lf",_val[j]);
	  if(prec==7) for(int j=0; j<n; j++) fprintf(fp," %.7lf",_val[j]);
	  if(prec==8) for(int j=0; j<n; j++) fprintf(fp," %.8lf",_val[j]);
	  if(prec==9) for(int j=0; j<n; j++) fprintf(fp," %.9lf",_val[j]);
	} else {
	  for(int j=0; j<n; j++) fprintf(fp," %g",_val[j]);
	}
//	for(int j=0; j<n; j++) fprintf(fp," %g",_val[j]);
	break;
      default:
	break;
      }
      fprintf(fp,"\n");
    }

    void print_info() {
      const char *state_str[] = {
	"never connected", "previously connected", "connected", "closed"
      };
      printf("%s\n"
	     "    State:         %s\n"
	     "    Host:          %s\n"
	     "    Access:        read=%d, write=%d\n"
	     "    Data type:     %s (native: %s)\n"
	     "    Element count: %d\n"
	     ,_name, state_str[status()], host(),read_ok(), write_ok()
	     ,dbr_type_to_text(dbr_type()), dbf_type_to_text(dbf_type())
	     ,n_elems()
	     );
    }

    void log_put(const char *date, const char *fmt, ...) {//timestamp specified
      if(dbr_type() == DBR_STRING) {
	char buf[MAX_STRLEN];
	snprintf(buf,MAX_STRLEN,"%s: ",date);
	set_string(buf); put(); usleep(100000);
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf,MAX_STRLEN-1,fmt,ap);
	va_end(ap);
	strncat(buf,"\n",1);
	set_string(buf); put(); usleep(100000);
      }
    }
    void log_put(const char *fmt, ...) {//timestamp @ ca val is updated
      if(dbr_type() == DBR_STRING) {
	char buf[MAX_STRLEN];
	snprintf(buf,MAX_STRLEN,"%s: ",time_str());
	set_string(buf); put(); usleep(100000);
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf,MAX_STRLEN-1,fmt,ap);
	va_end(ap);
	strncat(buf,"\n",1);
	set_string(buf); put(); usleep(100000);
      }
    }

  };// class EpicsCA

  void EpicsCA_default_event_handler(struct event_handler_args args) {
    EpicsCA *ca = (EpicsCA *)args.usr;
    if( ! ca->mon_flag() ) ca->set_monitor_data(args);
  }

} // namespace thl

#endif //THL_EPICS_CA_HH
