// thl : tiny header-only library
//
// Bracket : class to get the string between brackets 
//
// c++03
//
#ifndef THL_BRACKET_HH
#define THL_BRACKET_HH

#include <string>
#include <vector>

namespace thl {
  class Bracket {
  private:
    char _bra,_cket;
    std::string _buf;
    std::vector<size_t> _ib; // index of bras
    std::vector<size_t> _ic; // index of ckets
  public:
    Bracket() : _bra('('), _cket(')') {}
    Bracket(char bra, char cket, std::string s="") {
      init(bra,cket,s);
    }
    void init(char bra, char cket, std::string s="") {
      _bra=bra;_cket=cket;
      if(s.size()>0) parse(s);
    }
    void parse(std::string s) {
      _buf = s;
      clear();
      if(_bra != _cket ) {
	for(size_t j=0; j<s.size(); j++) {
	  if(s[j]==_bra) {
	    size_t start=++j, nest=0;
	    while(j<s.size()) {
	      if(s[j]==_bra) {nest++; j++; continue;}
	      if(s[j]==_cket && nest>0) {nest--; j++; continue;}
	      if(s[j]==_cket && nest==0) {
		_ib.push_back(start);
		_ic.push_back(j);
		break;
	      }
	      j++;
	    }
	  }
	}
      } else { // _bra == _cket
	size_t start=0, inside=0;
	for(size_t j=0; j<s.size(); j++) {
	  if(s[j]==_bra && inside==0) {start=j+1; inside=1; continue;}
	  if(s[j]==_bra && inside==1) {
	    _ib.push_back(start);
	    _ic.push_back(j);
	    inside=0;  continue;
	  }
	}      
      }
    }
    void clear() {_ib.clear(); _ic.clear();}
    size_t size() {return _ib.size();}
    size_t ib(size_t j) {return (j<size()) ? _ib[j] : 0;} // index of bra
    size_t ic(size_t j) {return (j<size()) ? _ic[j] : 0;} // index of cket
    std::string contents(size_t j) {
      return (j<size()) ? _buf.substr(_ib[j],_ic[j]-_ib[j]) : "";
    }
    std::string last_contents(void) {
      return (size()>0) ? contents(size()-1) : "";
    }
    std::string before(size_t j) {
      if(j>=size()) return "";
      if(j==0) return _buf.substr(0,_ib[j]-1);
      if(j>0 && j<size()) return _buf.substr(_ic[j-1]+1,_ib[j]-_ic[j-1]-2);
      return "";
    }
    std::string last_before(void) {
      return (size()>0) ? before(size()-1) : "";
    }
    std::string after(size_t j) {
      if(j>=size()) return "";
      if(j<size()-1) return before(j+1);
      if(j==size()-1) return _buf.substr(_ic[j]+1);
      return "";
    }
    std::string last_after(void) {
      return after(size()-1);
    }
  };//-- class Bracket
}//-- namespace thl

#endif //THL_BRACKET_HH

