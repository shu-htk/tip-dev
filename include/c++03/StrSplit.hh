// thl : tiny header-only library
//
// StrSplit : class to split the string by the delimiter
//
// c++03
//
#ifndef THL_STRSPLIT_HH
#define THL_STRSPLIT_HH

#include <fstream>
#include <vector>
#include <cstdio>
#include "StrNum.hh"

namespace thl {
  class StrSplit {
  private:
    std::vector<size_t> _index;       // index of splitted fields
    std::vector<std::string> _field;  // contents of splitted fields
    StrNum _sn;
    int _nerr;
    int _verb;        // verbose level
    bool _null_field; // flag to take null-field
    bool _dlm_as_str; // flag to take delimiter as string
    char _quot;       // quotation to skip split (default '\0' not skip)
  public:
    StrSplit() : _nerr(0),_verb(1),_null_field(0),_dlm_as_str(0),_quot(0) {}
    StrSplit(const std::string &str, const std::string dlm="") 
      : _nerr(0),_verb(1),_null_field(0),_dlm_as_str(0),_quot(0) {
      if(!str.empty()) split(str,dlm);
    }
    StrSplit(const std::string &str, char dc) 
      : _nerr(0),_verb(1),_null_field(0),_dlm_as_str(0),_quot(0) {
      if(!str.empty()) split(str,dc);
    }
    void set_verbose(int n) {_verb=n; _sn.set_verbose(n);}
    void take_null_field(bool b) {_null_field=b;}
    void take_delimiter_as_string(bool b) {_dlm_as_str=b;}
    void set_quot_to_skip_split(char quot) {_quot=quot;}
    void clear() {_index.clear(); _field.clear();}
    
    void split(const std::string &str, char dc) {
      split(str,std::string(1,dc));
    }
    void split(const std::string &str, std::string dlm="") {
      clear();
      bool omit_null = !_null_field;
      if(dlm.size()==0) {
	dlm=" \t\n";    // default delimiters are white spaces
	omit_null=true; // always omit null-field when dlm is white spaces
      }
      size_t inc=_dlm_as_str ? dlm.size() : 1; // incremental-size of index
      size_t index=0; // index of field
      size_t idlm=0;  // index of delimiter
      bool skip=0;    // flag to skip inside of quotations
      for(size_t j=0; j<str.size(); j++) {
	if(_quot != '\0') {
	  if(!skip && str[j]==_quot) {skip=1; continue;}
	  if(skip && str[j]==_quot) {skip=0; continue;}
	  if(skip) continue;
	}
	if(_dlm_as_str) {
	  idlm = str.find(dlm,j);
	} else {
	  idlm = str.find_first_of(dlm,j);
	}
	if(j==idlm) {
	  if(omit_null && j==index) {index += inc; continue;}
	  _index.push_back(index);
	  _field.push_back(str.substr(index,j-index));
	  index = j + inc;
	}
      }
      if(index<str.size()) {
	_index.push_back(index);
	_field.push_back(str.substr(index));
      } else if(!omit_null && index==str.size()) {
	size_t n=(index>0) ? index-1: 0;
	_index.push_back(n);
	_field.push_back("");
      }
    }
    bool getline(std::istream &is, const std::string dlm="") {
      std::string buf;
      bool flag=(bool)std::getline(is,buf);
      if(flag) {split(buf,dlm);}
      return flag;
    }
    const std::vector<size_t> &index(void) {return _index;}    
    size_t index(size_t j) {
      if(j < 0 || j >= size()) {
	if(_verb>0) fprintf(stderr,"StrSplit: index out of range\n");
	_nerr=10; return 0;
      }
      return _index[j];
    }
    const std::vector<std::string> &field(void) {return _field;}    
    const std::string field(size_t j) {
      if(j < 0 || j >= size()) {
	if(_verb>0) fprintf(stderr,"StrSplit: index out of range\n");
	_nerr=10; return "";
      }
      _nerr=0;
      return _field[j];
    }
    const char field(size_t j, size_t k) {
      if(k < 0 || k >= field(j).size()) {
	if(_verb>0) fprintf(stderr,"StrSplit: index out of range\n");
	_nerr=20; return 0;
      }
      _nerr=0; return field(j)[k];
    }
    size_t size() {return _index.size();}
    std::string last_field(void) {return field(size()-1);}
    const std::string operator()(size_t j) {return field(j);}
    const char operator()(size_t j, size_t k) {return field(j,k);}
    int nerr(void) {return _nerr+_sn.nerr();}
    const int stoi(size_t j) {return _sn.stoi(field(j));}
    const long stol(size_t j) {return _sn.stol(field(j));}
    const double stof(size_t j) {return _sn.stof(field(j));}
    const char pchar(void) {return _sn.pchar();}
    const std::string back(void) {return _field.back();}
    //    std::string* begin() {return &_field[0];}
    //    std::string* end() {return &_field[_field.size()];}
    void print() {
      for(size_t j=0;j<size();j++) printf("%d:[%s]\n",(int)j,field(j).c_str());
    }
    static const size_t npos = -1;
    size_t find(const std::string &name) {
      size_t n=npos;
      for(size_t j=0; j<size(); j++) if(field(j)==name) {n=j; break;}
      return n;
    }
  };//-- class StrSplit
}//namespace thl

#endif //THL_STRSPLIT_HH
