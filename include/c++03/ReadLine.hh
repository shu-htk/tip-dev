// thl : tiny header-only library
//
// ReadLine : wrapper class of GNU readline
//
// -std=c++03
//
#ifndef THL_ReadLine_HH
#define THL_ReadLine_HH

#include <string>
#include <cstdlib>
#include <cstdio>
#include <readline/readline.h>
#include <readline/history.h>
#include "StrSplit.hh"

namespace thl {

  class ReadLine {
  private:
    std::string _buf;
    std::string _prompt;
    std::string _history_fname;
    StrSplit _sp;
    size_t _n;
    char _comment_char;
    bool _skip_comment;
  public:
    ReadLine(std::string prompt=">", std::string history_fname=".rl_history")
      : _prompt(prompt),_history_fname(history_fname),_n(0),_comment_char('#'),
	_skip_comment(0) {
      using_history();
      read_history(_history_fname.c_str());
    }
    ~ReadLine() {
      write_history(_history_fname.c_str());
    }
    void take_null_field(bool nf=0) {
      _sp.take_null_field(nf);
    }
    void set_quot_to_skip_split(char quot=0) {
      _sp.set_quot_to_skip_split(quot);
    }
    void set_comment(char c) {_skip_comment=1; _comment_char=c;}
    void unset_comment(void) {_skip_comment=0;}

    size_t get(void) {
      char *line = readline(_prompt.c_str());
      if(line==0) return 0;
      if(_skip_comment && line[0]==_comment_char) return 0;
      if(strlen(line) > 0 && strcmp(line,_buf.c_str()) != 0) add_history(line);
      _buf = line;
      free(line);
      return _buf.size();
    }
    std::string get_string(void) {
      if(get()>0) {return _buf;} else {return "";}
    }
    std::string get_split_string(std::string delm) {
      if(_n==0) {
	if(get()>0) {
	  _sp.split(_buf,delm);
	  return _sp.size() ? _sp(_n++) : "";
	} else {
	  return "";
	}
      } else {
	if(_n<_sp.size()) {
	  return _sp(_n++);
	} else {
	  _n=0;
	  return get_split_string(delm);
	}
      }
    }
    std::string &operator() (void) {return _buf;}
    char operator() (size_t j) {
      if(j<0 || j>=_buf.size()) {
	fprintf(stderr,"thl::ReadLine: access out of the buffer range\n");
	return 0;
      }
      return _buf[j];
    }
    void set_prompt(std::string prompt) {_prompt = prompt;}

  };//-- class ReadLine

}//-- namespace thl

#endif //THL_ReadLine_HH

