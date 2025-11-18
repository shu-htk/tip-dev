// thl : tiny header-only library
//
// ArgOpt : class to take command line arguments and options 
//
// c++03
//
#ifndef THL_ARGOPT_HH
#define THL_ARGOPT_HH

#include <map>
#include <cstdio>
#include "StrNum.hh"
#include "StrSplit.hh"

namespace thl {
  class ArgOpt {
    enum {Undefined=0, WithoutArg=1, WithArg=2}; // option key type
  private:
    std::map<std::string,std::string> _opt;
    std::vector<std::string> _rest_arg;
    std::string _cmd_name; // command name
    std::string _key_list; // option key list
    StrNum _sn;
    int _nerr;
  public:
    ArgOpt(void) {}
    ArgOpt(int argc, const char *argv[], const std::string &key_list="",
	   bool usage=1)
      : _key_list(key_list), _nerr(0) {
      std::vector<std::string> vstr(argc);
      for(int j=0; j<argc; j++) vstr[j]=argv[j];
      parse(vstr, usage);
    }
    ArgOpt(const std::string &buffer, const std::string &key_list="",
	   bool usage=1)
      : _key_list(key_list), _nerr(0) {
      StrSplit sp; sp.set_quot_to_skip_split('\''); sp.split(buffer);
      parse(sp.field(), usage);
    }
    void print_usage(void) {
      StrSplit sp(_key_list,", ");
      fprintf(stderr,"usage : %s %s rest_args...\n",_cmd_name.c_str(),
	      sp.size() ? "[options...]" : "");
      for(size_t j=0; j<sp.size(); j++)
	fprintf(stderr," -%s\n",sp(j).c_str());
    }
    int key_type(const std::string &key) {
      std::string key_with_colon = key + ":";
      StrSplit sp(_key_list,", ");
      for(size_t j=0; j < sp.size(); j++) {
	if(sp(j) == key ) return WithoutArg;
	if(sp(j) == key_with_colon) return WithArg;
      }
      return Undefined;
    }
    void parse(const std::vector<std::string> &vstr, bool usage=1) {
      _cmd_name = vstr[0];
      if( vstr.size() < 2 && usage ) {
	print_usage();
	exit(1);
      }
      for(size_t j=0; j < vstr.size(); j++) {
	if( vstr[j][0] == '-'  && vstr[j].size() > 1 ) {
	  std::string key = vstr[j].substr(1);
	  int type = key_type(key);
	  if(type==Undefined) {
	    fprintf(stderr,"undefined option: %s\n",vstr[j].c_str());
	    exit(1);
	  } else if(type==WithoutArg) {
	    _opt[key] = "on"; // "on" is dummy arg
	  } else if(type==WithArg) {
	    if(j+1 < vstr.size()) {
	      _opt[key] = vstr[j+1];
	    } else {
	      fprintf(stderr,"%s require argument\n",vstr[j].c_str());
	      exit(1);
	    }
	    j++;
	  }
	} else {// without "-*" rest of args
	  _rest_arg.push_back(vstr[j]);
	}
      }
    }
    std::string cmd_name(void) {return _cmd_name;}

    int nerr() {return _nerr+_sn.nerr();}
    int size(void) {return _rest_arg.size();}
    const std::string rest_arg(int j) {
      if(j >= 0 && j < size()) {_nerr=0; return _rest_arg[j];}
      else {_nerr=10; return "";}
    }
    const std::string operator () (int j) {return rest_arg(j);}
    int stoi(int j) {return _sn.stoi(rest_arg(j));}
    long stol(int j) {return _sn.stol(rest_arg(j));}
    double stof(int j) {return _sn.stof(rest_arg(j));}
    bool find_opt(const std::string &key) {return _opt.count(key);}
    int opt_size(void) {return _opt.size();}
    std::string opt(const std::string &key) {return _opt[key];}
    std::string opt_def(const std::string &key,
			const std::string &default_opt) {
      return find_opt(key) ? opt(key) : default_opt;
    }
    int opt_stoi(const std::string &key) {return _sn.stoi(_opt[key]);}
    long opt_stol(const std::string &key) {return _sn.stol(_opt[key]);}
    double opt_stof(const std::string &key) {return _sn.stof(_opt[key]);}
    int opt_def_stoi(const std::string &key,
		      const std::string &default_opt) {
      return find_opt(key) ? _sn.stoi(_opt[key]) : _sn.stoi(default_opt);
    }
    long opt_def_stol(const std::string &key,
			  const std::string &default_opt) {
      return find_opt(key) ? _sn.stol(_opt[key]) : _sn.stol(default_opt);
    }
    double opt_def_stof(const std::string &key,
			const std::string &default_opt) {
      return find_opt(key) ? _sn.stof(_opt[key]) : _sn.stof(default_opt);
    }
  };// class ArgOpt

}// namespace thl

#endif //THL_ARGOPT_HH
