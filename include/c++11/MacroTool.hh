// thl : tiny header-only library
//
// Calc      : class to parse numerical expression
// NumLogic  : class to parse numerical logical expression 
// StrLogic  : class to parse string logical expression 
// Logic     : class to parse both of num and str logic
// Var       : class to create variables which have key and value
// Loop      : class to control 'for', 'do', 'while' loops 
// If        : class to control 'if', 'elif', 'else', 'fi' 
// MacroTool : class to parse macro commands using above tools
//
// c++11
//
#ifndef THL_MACRO_TOOL_HH
#define THL_MACRO_TOOL_HH

#include <map>
#include <fstream>
#include <fnmatch.h>
#include <unistd.h> // usleep()
#include <ctime>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include "Trim.hh"
#include "StrSplit.hh"
#include "CFormat.hh"
#include "Bracket.hh"
#include "IsoTimeStr.hh"
#include "ReadLine.hh"

namespace thl {
//-----------------------------------------------------
  class Calc {
  private:
    char *_cp;
    int _not_digit={0};
    std::vector<std::string> _tag;
    std::map<std::string,double> _var_num;
    enum Func {
      ABS,SQRT,EXP,LOG,LOG10,COS,ACOS,SIN,ASIN,TAN,ATAN,COSH,SINH,TANH,FLOOR,
      POW,ATAN2
    };
  public:
    Calc(void) {}
    double eval(const std::string &expr) {
      _not_digit=0; _cp=(char*)expr.c_str(); return addsub();
    }
    int not_digit(void) {return _not_digit;}
    void clear(void) {
      for(auto &&a : _tag) {_var_num.erase(a);}
      _tag.clear();
    }
    void set_var_num(const std::string &tag, double val) {
      if(_var_num.count(tag)==0) _tag.push_back(tag);
      _var_num[tag] = val;
    }
  private:
    double factor(void) {
      while(*_cp == ' ' || *_cp == '\t') {_cp++;}
      if(*_cp == '(') {_cp++; double ret=addsub(); _cp++; return ret;}
      if(isdigit(*_cp)||(*_cp=='+')||(*_cp=='-')||(*_cp=='.')) {
	return strtod(_cp,(char**)&_cp);
      }
      std::string s=_cp;
      if(s.find("abs(")==0)  {return func(s,ABS);}
      if(s.find("sqrt(")==0) {return func(s,SQRT);}
      if(s.find("exp(")==0)  {return func(s,EXP);}
      if(s.find("log(")==0)  {return func(s,LOG);}
      if(s.find("log10(")==0){return func(s,LOG10);}
      if(s.find("cos(")==0)  {return func(s,COS);}
      if(s.find("acos(")==0) {return func(s,ACOS);}
      if(s.find("sin(")==0)  {return func(s,SIN);}
      if(s.find("asin(")==0) {return func(s,ASIN);}
      if(s.find("tan(")==0)  {return func(s,TAN);}
      if(s.find("atan(")==0) {return func(s,ATAN);}
      if(s.find("cosh(")==0) {return func(s,COSH);}
      if(s.find("sinh(")==0) {return func(s,SINH);}
      if(s.find("tanh(")==0) {return func(s,TANH);}
      if(s.find("floor(")==0) {return func(s,FLOOR);}
      if(s.find("pow(")==0) {return func(s,POW);}
      if(s.find("atan2(")==0) {return func(s,ATAN2);}
      for(auto &&a : _tag) {
	if(s.find(a)==0) {_cp+=a.size(); return _var_num[a];}
      }
      _not_digit=1;
      return 0;
    }
    double func(const std::string &s, enum Func ifunc) {
      Bracket bc('(',')',s);
      if(bc.size()>0) {
	char *cp_next = _cp + bc.ic(0) + 1;
	if(ifunc==POW||ifunc==ATAN2) {
	  StrSplit sp(bc.contents(0),",");
	  if(sp.size()>1) {
	    double x0 = eval(sp(0));
	    double x1 = eval(sp(1));
	    _cp = cp_next;
	    if(ifunc==POW) {return std::pow(x0,x1);}
	    if(ifunc==ATAN2) {return std::atan2(x0,x1);}
	  } else {
	    printf("pow(),atan2() should takes two arguments.\n");
	  }
	} else {
	  double x = eval(bc.contents(0));
	  _cp = cp_next;
	  if(ifunc==ABS) {return std::abs(x);}
	  if(ifunc==SQRT) {return std::sqrt(x);}
	  if(ifunc==EXP) {return std::exp(x);}
	  if(ifunc==LOG) {return std::log(x);}
	  if(ifunc==LOG10) {return std::log10(x);}
	  if(ifunc==COS) {return std::cos(x);}
	  if(ifunc==ACOS) {return std::acos(x);}
	  if(ifunc==SIN) {return std::sin(x);}
	  if(ifunc==ASIN) {return std::asin(x);}
	  if(ifunc==TAN) {return std::tan(x);}
	  if(ifunc==ATAN) {return std::atan(x);}
	  if(ifunc==COSH) {return std::cosh(x);}
	  if(ifunc==SINH) {return std::sinh(x);}
	  if(ifunc==TANH) {return std::tanh(x);}
	  if(ifunc==FLOOR) {return std::floor(x);}
	}
      }
      return 0;
    }
    double muldiv(void) {
      double ret = factor();
      while(1) {
	if(*_cp=='*') {_cp++; ret *= factor();}
	else if(*_cp=='/') {_cp++; ret /= factor();}
	else if(*_cp=='%') {_cp++; ret = fmod(ret,factor());}
	else if(*_cp==' '||*_cp=='\t') {_cp++;}
	else {return ret;}
      }
    }
    double addsub(void) {
      double ret = muldiv();
      while(1) {
	if(*_cp=='+') {_cp++; ret += muldiv();}
	else if(*_cp=='-') {_cp++; ret -= muldiv();}
	else if(*_cp==' '||*_cp=='\t') {_cp++;}
	else {return ret;}
      }
    }
  };
//-----------------------------------------------------
  class NumLogic {
  private:
    char *_cp;
    Calc _calc;
    std::vector<double> _nc; // numerical candidates in the expression {,..}
  public:
    NumLogic(void) {}
    bool eval(const std::string &expr) {
      _cp=(char*)expr.c_str(); return and_or();
    }
    void clear(void) {_calc.clear();}
    void set_var(const std::string &tag, double val) {
      _calc.set_var_num(tag,val);
    }
  private:
    double factor(void) {
      _nc.clear();
      while(*_cp == ' '||*_cp == '\t') {_cp++;}
      std::string expr=_cp;
      if(*_cp == '{') {
	Bracket bc('{','}',expr);
	if(bc.size()>0) {
	  _cp += bc.ic(0)+1;
	  StrSplit sp(bc.contents(0),",");
	  for(size_t j=0; j<sp.size(); j++) {
	    _nc.push_back(_calc.eval(sp(j)));
	  }
	} else {
	  printf("NumLogic::factor(): unbalanced bracket '{ }'.\n");
	}
	return 0;
      }
      double val = _calc.eval(expr);
      size_t n = expr.find_first_of("<>=!&|");
      if(n != expr.npos) _cp += n;
      return val;
    }
    bool compare(void) {
      bool flip=0;
      while(1) {
	if(*_cp=='!') {_cp++; flip = !flip;}
	else if(*_cp==' ' || *_cp=='\t') {_cp++;}
	else break;
      }
      double lval=factor(),rval=0;
      bool update_lval=0, ret=1;
      while(1) {
	if(*_cp=='=') {
	  if(*(_cp+1)=='=') {_cp+=2;} else {_cp++;}
	  rval=factor();
	  if(_nc.size()>0) {
	    double ret2=0;
	    for(auto && a: _nc) {ret2 = (ret2||(lval==a));}
	    ret = (ret && ret2);
	  } else {
	    ret = (ret && (lval == rval));
	  }
	  lval=rval; update_lval=1;
	} else if(*_cp=='!' && *(_cp+1)=='=') {
	  _cp+=2; rval=factor();
	  if(_nc.size()>0) {
	    double ret2=1;
	    for(auto &&a : _nc) {ret2 = (ret2&&(lval!=a));}
	    ret = (ret && ret2);
	  } else {
	    ret = (ret && (lval != rval));
	  }
	  lval=rval; update_lval=1;
	} else if(*_cp=='<' && *(_cp+1)!='=') {
	  _cp++;  rval=factor(); ret = (ret && (lval < rval));
	  lval=rval; update_lval=1;
	} else if(*_cp=='<' && *(_cp+1)=='=') {
	  _cp+=2; rval=factor(); ret = (ret && (lval <= rval));
	  lval=rval; update_lval=1;
	} else if(*_cp=='>' && *(_cp+1)!='=') {
	  _cp++;  rval=factor(); ret = (ret && (lval > rval));
	  lval=rval; update_lval=1;
	} else if(*_cp=='>' && *(_cp+1)=='=') {
	  _cp+=2; rval=factor(); ret = (ret && (lval >= rval));
	  lval=rval; update_lval=1;
	} else if(*_cp==' '||*_cp=='\t') {
	  _cp++;
	} else {
	  ret = (update_lval)? ret : (bool)lval;
	  return (flip)? (!ret) : ret;
	}
      }
    }
    bool and_or(void) {
      bool ret = compare();
      while(1) {
	if(*_cp=='&' && *(_cp+1)!='&') {_cp++; ret=(ret && compare());}
	else if(*_cp=='&' && *(_cp+1)=='&') {_cp+=2; ret=(ret && compare());}
	else if(*_cp=='|'&& *(_cp+1)!='|') {_cp++; ret=(ret || compare());}
	else if(*_cp=='|'&& *(_cp+1)=='|') {_cp+=2; ret=(ret || compare());}
	else if(*_cp==' '||*_cp=='\t') {_cp++;}
	else {return ret;}
      }
    }
  };
//-----------------------------------------------------
  class StrLogic {
  private:
    char *_cp;
    std::vector<std::string> _sc; //string candidates in the expression {,..}
    std::vector<std::string> _tag;
    std::map<std::string,std::string> _var_str;
  public:
    StrLogic(void) {}
    bool eval(const std::string &expr) {
      _cp=(char*)expr.c_str(); return and_or();
    }
    void clear(void) {
      for(auto &&a : _tag) {_var_str.erase(a);}
      _tag.clear();
    }
    void set_var(const std::string &tag, const std::string &val) {
      if(_var_str.count(tag)==0) _tag.push_back(tag);
      _var_str[tag] = val;
    }
  private:
    std::string factor(void) {
      _sc.clear();
      while(*_cp == ' '||*_cp == '\t') {_cp++;}
      if(*_cp == '(') {
	_cp++; std::string ret = and_or() ? "1" : "0"; _cp++; return ret;
      }
      std::string s=_cp;
      if(*_cp == '{') {
	Bracket bc('{','}',s);
	if(bc.size()>0) {
	  _cp += bc.ic(0)+1;
	  StrSplit sp;
	  sp.set_quot_to_skip_split('"');
	  sp.split(bc.contents(0)," ,");
	  for(auto &&a : sp) {_sc.push_back(trim(a));}
	  return "{";
	} else {
	  printf("StrLogic::factor(): unbalanced bracket '{ }'.\n");
	  return "0";
	}
      }
      if(*_cp=='"' || *_cp=='\'') {
	Bracket bc(*_cp,*_cp,s);
	if(bc.size()>0) {
	  _cp += bc.ic(0)+1;
	  return bc.contents(0);
	} else {
	  printf("StrLogic::factor(): unbalanced quotation %c.\n",*_cp);
	  return "0";
	}
      } else {
	size_t n = s.find_first_of(" ()=!&|\"");
	if(n != s.npos) _cp += n;
	for(auto &&a : _tag) {if(s.find(a)==0) {return _var_str[a];}}
	return s.substr(0,n);
      }
    }
    bool compare(void) {
      bool flip=0;
      while(1) {
	if(*_cp=='!') {_cp++; flip = !flip;}
	else if(*_cp==' ' || *_cp=='\t') {_cp++;}
	else break;
      }
      std::string lval=factor(),rval="";
      bool update=0, ret=1;
      while(1) {
	if(*_cp=='=') {
	  if(*(_cp+1)=='=') {_cp+=2;} else {_cp++;}
	  rval=factor();
	  if(rval=="{") {//compare for each candidates
	    ret=0;
	    for(size_t j=0; j<_sc.size();j++) {
	      ret = (ret || (fnmatch(_sc[j].c_str(),lval.c_str(),0)==0));
	    }
	  } else {
	    ret = (fnmatch(rval.c_str(),lval.c_str(),0)==0);
	  }
	  update=1;
	} else if(*_cp=='!' && *(_cp+1)=='=') {
	  _cp+=2; rval=factor();
	  if(rval=="{") {//compare for each candidates
	    ret=1;
	    for(size_t j=0; j<_sc.size();j++) {
	      ret = (ret && (fnmatch(_sc[j].c_str(),lval.c_str(),0)!=0));
	    }
	  } else {
	    ret = (fnmatch(rval.c_str(),lval.c_str(),0)!=0);
	  }
	  update=1;
	} else if(*_cp=='<' && *(_cp+1)!='=') {
	  _cp++;  rval=factor(); ret = (lval < rval);
	  update=1;
	} else if(*_cp=='<' && *(_cp+1)=='=') {
	  _cp+=2; rval=factor(); ret = (lval <= rval);
	  update=1;
	} else if(*_cp=='>' && *(_cp+1)!='=') {
	  _cp++;  rval=factor(); ret = (lval > rval);
	  update=1;
	} else if(*_cp=='>' && *(_cp+1)=='=') {
	  _cp+=2; rval=factor(); ret = (lval >= rval);
	  update=1;
	} else if(*_cp==' '||*_cp=='\t') {
	  _cp++;
	} else {
	  if(!update && lval=="0") ret=0;
	  return (flip)? (!ret) : ret;
	}
      }
    }
    bool and_or(void) {
      bool ret = compare();
      while(1) {
	if(*_cp=='&' && *(_cp+1)!='&') {_cp++; ret=(ret && compare());}
	else if(*_cp=='&' && *(_cp+1)=='&') {_cp+=2; ret=(ret && compare());}
	else if(*_cp=='|'&& *(_cp+1)!='|') {_cp++; ret=(ret || compare());}
	else if(*_cp=='|'&& *(_cp+1)=='|') {_cp+=2; ret=(ret || compare());}
	else if(*_cp==' '||*_cp=='\t') {_cp++;}
	else {return ret;}
      }
    }
  };
//-----------------------------------------------------
  class Logic {
  public:
    NumLogic num;
    StrLogic str;
    Logic(void) {}
    bool eval(const std::string &expr, bool debug=0) {
      std::string s = trim(expr);
      if(debug) printf("[%s] -> ",s.c_str());
      if(isdigit(s[0])||(s[0]=='+')||(s[0]=='-')||(s[0]=='.')) {
	if(debug) printf("num_logic -> [%d]\n",(int)num.eval(s));
	return num.eval(s);
      } else {
	if(debug) printf("str_logic -> [%d]\n",(int)str.eval(s));
	return str.eval(s);
      }
    }
    void clear(void) {num.clear(); str.clear();}
  };
//-----------------------------------------------------
  class Var {
    enum Type {Undef,Num,Str};
    struct Val {
      Type type;
      double num;
      std::string str;
      Val(void) : type(Undef),num(0) {}
      void print(void) {
	if(type==Str) printf("string [%s]\n",str.c_str());
	if(type==Num) printf("number [%.11g]\n",num);
      }
    };
    std::map<std::string,Val> _val;
    char _fmt[256];
  public:
    IsoTimeStr ts;
    Var(void) : ts("- :") {snprintf(_fmt,256,"%s","%.11g");}
    void reset_fmt(void) {snprintf(_fmt,256,"%s","%.11g");}
    void print_fmt(void) {printf("[%s]\n",_fmt);}
    void set_fmt(const std::string &s) {
      if(fnmatch("%*f",s.c_str(),0)==0 || fnmatch("%*e",s.c_str(),0)==0 ||
	 fnmatch("%*g",s.c_str(),0)==0) {
	snprintf(_fmt,256,"%s",s.c_str());
      } else {
	printf("invalid format [%s]\n"
	       "since numerical variable type is 'double'\n"
	       "you should specify the format 'f' or 'e' or 'g'\n"
	       ,s.c_str());
      }
    }
    double num(const std::string &tag) {return _val[tag].num;}
    std::string str(const std::string &tag) {return _val[tag].str;}
    void set_num(const std::string &tag, double x, int ope=0) {
      _val[tag].type = Num;
      if(ope==0) _val[tag].num = x;
      if(ope==1) _val[tag].num += x;
      if(ope==2) _val[tag].num -= x;
      if(ope==3) _val[tag].num += x;
      if(ope==4) _val[tag].num /= x;
      if(ope==5) _val[tag].num = fmod(_val[tag].num,x);
    }
    void set_str(const std::string &tag, std::string s, int ope=0) {
      _val[tag].type = Str;
      if(ope==0) _val[tag].str = trim(s);
      if(ope==1) _val[tag].str += trim(s);
      if(ope >1) printf("invalid operator of string\n");
    }
    bool exist_num(const std::string &tag) {
      if(_val.count(tag)) {return (_val[tag].type==Num);} else {return 0;}
    }
    bool exist_str(const std::string &tag) {
      if(_val.count(tag)) {return (_val[tag].type==Str);} else {return 0;}
    }
    bool exist(const std::string &tag) {return _val.count(tag);}
    void erase(const std::string &tag) {
      if(_val.count(tag)) _val.erase(tag);
    }
    void parse_ternary(const std::string &expr, double &x, std::string &s) {
      Calc calc;
      StrSplit sp;
      sp.set_quot_to_skip_split('"');
      sp.split(expr,"?");
      if(sp.size()<2) {
	x = calc.eval(expr);
	if(calc.not_digit()) s=expr;
      } else {
	StrSplit sp2(sp(1),":");
	if(sp2.size()<2) {
	  printf("Var::parse_ternary(): operator lack of args\n"); return;
	} else {
	  Logic logic;
	  if(logic.eval(sp(0))) {
	    x = calc.eval(sp2(0));
	    if(calc.not_digit()) s=sp2(0);
	  } else {
	    x = calc.eval(sp2(1));
	    if(calc.not_digit()) s=sp2(1);
	  }
	}
      }
    }
    void set_expr(const std::string &tag, const std::string &expr, int ope) {
      double x=0;
      std::string s;
      parse_ternary(expr,x,s);
      if(s.size()>0) {
	if(exist_num(tag)) {
	  CFormat fmt;
	  set_str(tag,fmt("%.11g",num(tag)));
	}
	set_str(tag,trim(s),ope);
      } else {
	if(exist_str(tag)) {
	  Calc calc;
	  set_num(tag,calc.eval(str(tag)));
	}
	if(!exist_num(tag)) {set_num(tag,0);}
	set_num(tag,x,ope);
      }
    }
    void set_eval(const std::string &buf) {
      size_t n = buf.find_first_of("=+-*/%");
      if(n==buf.npos) {printf("invalid argument\n"); return;}
      std::string tag = trim(buf.substr(0,n));
      std::string expr = buf.substr(n);
      size_t m = expr.find_first_not_of("=+-*/%");
      if(m==buf.npos) {printf("lack of expression\n"); return;}
      std::string ope = expr.substr(0,m);
      expr = expr.substr(m);
//    printf("tag[%s] ope[%s] expr[%s]\n",tag.c_str(),ope.c_str(),expr.c_str());
      if(ope=="=") {
	if(expr.find("time(")!=expr.npos) {
	  Bracket bc('(',')',expr);
	  StrSplit sp(bc.contents(0),",");
	  std::string tstr = (sp.size()>0) ? sp(0) : "";
	  std::string unit = (sp.size()>1) ? sp(1) : "";
	  if(unit=="str") {
	    double utime =
	      (tstr=="now") ? ts.str_to_num("now","utime") : sp.stof(0);
	    set_str(tag,ts.utime_to_str(utime,1));
	  } else {
	    size_t n = tstr.find_first_of(ts.tsd());
	    StrNum sn; sn.set_verbose(0);
	    double utime = sn.stof(tstr);
	    if(n != tstr.npos || sn.nerr()==2) {
	      set_num(tag,ts.str_to_num(tstr,unit));
	    } else {
	      set_num(tag,ts.utime_to_num(utime,unit));
	    }
	  }
	} else {
	  set_expr(tag, expr, 0);
	}
      } else {
	if(ope!="+=" && ope!="-=" && ope!="*=" && ope!="/="&& ope!="%=") {
	  printf("invalid operator [%s]\n",ope.c_str());
	  return;
	}
	if(ope=="+=") set_expr(tag, buf.substr(buf.find("+=")+2), 1);
	if(ope=="-=") set_expr(tag, buf.substr(buf.find("-=")+2), 2);
	if(ope=="*=") set_expr(tag, buf.substr(buf.find("*=")+2), 3);
	if(ope=="/=") set_expr(tag, buf.substr(buf.find("/=")+2), 4);
	if(ope=="%=") set_expr(tag, buf.substr(buf.find("%=")+2), 5);
      }
    }
    void ls(const std::string &pattern) {
      StrSplit sp(pattern,",");
      for(auto &&s : sp) {
	for(auto &&a : _val) {
	  if( fnmatch(s.c_str(),a.first.c_str(),0)==0 ) {
	    printf("%s : ",a.first.c_str()); a.second.print();
	  }
	}
      }
    }
    void rm(const std::string &pattern) {
      std::vector<std::string> tags;
      StrSplit sp(pattern,",");
      for(auto &&s : sp) {
	for(auto &&a : _val) {
	  if( fnmatch(s.c_str(),a.first.c_str(),0)==0 ) {
	    tags.push_back(a.first);
	  }
	}
	for(size_t j=0; j<tags.size(); j++) erase(tags[j]);
      }
    }
    void replace(std::string &buf) {
      CFormat fmt; 
      for(auto &&a : _val) {
	std::string tag = "["+a.first+"]";
	std::string val;
	if(a.second.type==Num) val=fmt(_fmt,a.second.num);
	if(a.second.type==Str) val=a.second.str;
	if(buf.find(tag) != buf.npos) {
	  for(size_t n=0; (n=buf.find(tag))!= buf.npos;) {
	    buf.replace(n,tag.size(),val);
	  }
	}
      }
    }
    void split(const std::string &tag, std::string fs=" \t\n") {
      if(exist_str(tag)) {
	CFormat fmt;
	StrSplit sp;
	sp.set_quot_to_skip_split('"');
	sp.split(str(tag),fs);
	for(size_t j=0; j<sp.size(); j++) {
	  set_str(tag+fmt("%lu",j+1),trim(sp(j)));
	}
      } else {
	printf("string macro variable %s is not found\n",tag.c_str());
      }
    }
    void set_arg_list(std::string arg_list, bool update=0) {
      if(arg_list.size()>0) {
	thl::CFormat fmt;
	thl::StrSplit sp;
	sp.set_quot_to_skip_split('"');
	sp.split(arg_list,",");
	if(update || !exist_num("$#")) set_num("$#",(double)sp.size());
	for(int j=0; j<(int)sp.size(); j++) {
	  thl::StrSplit sp2;
	  sp2.set_quot_to_skip_split('"');
	  sp2.split(sp(j),"=");
	  if(sp2.size()>1) {
	    std::string tag=sp2(0);
	    if(update || !exist(tag)) set_expr(tag,trim(sp2(1)),0);
	  } else {
	    std::string tag=fmt("$%d",j+1);
	    if(update || !exist(tag)) set_expr(tag,trim(sp(j)),0);
	  }
	}
      } else {
	set_num("$#",0);
      }
    }
  };
//-----------------------------------------------------
  class Loop {
    bool _init={1},_pass={0},_err={0};
    size_t _end_idx={0};
    std::string _tag;  // name of loop variable
    StrSplit _item;  // items of foreach loop
    size_t _nitem={0};    // index number of items of foreach loop
    double _n1={0},_dn={1}; // do loop _n1:end-number, _dn:increment
  public:
    Loop(void) {_item.set_quot_to_skip_split('"');}
    void reset(void) {_init=1;}
    bool pass(void) {return _pass;}
    bool err(void) {return _err;}
    size_t end_idx(void) {return _end_idx;}
    void set_end_idx(size_t n) {_end_idx=n;}
  
    void process(const std::string &buf, Var *var) {
      StrSplit sp(buf);
      if(sp.size()==0) {_err=1; return;}
      if(sp(0)=="for") { // loop for each items
	if(_init) {
	  if(sp.size()<3) {
	    printf("usage: for s (a b c ...); ...; end\n");
	    _err=1; return;
	  }
	  _tag=sp(1);
	  Bracket bc('(',')',buf);
	  if(bc.size()==0) {printf("for-loop: no items\n"); return;}
	  _item.split(bc.contents(0));
	  _nitem=0;
	  var->set_str(_tag,_item(_nitem));
	  _init=0;
	} else {
	  _nitem++;
	  if(_nitem<_item.size()) {
	    var->set_str(_tag,_item(_nitem));
	  } else {
	    var->erase(_tag);
	  }
	}
	_pass = (_nitem < _item.size());
      }
      if(sp(0)=="do") { // loop in the ranged number
	if(_init) {
	  if(sp.size()<4) {
	    printf("usage: do n N0 N1 [dN]; ...; end\n");
	    _err=1; return;
	  }
	  _tag=sp(1);
	  double n=sp.stof(2); if(sp.nerr()) {_err=1; return;}
	  var->set_num(_tag,n);
	  _n1=sp.stof(3);      if(sp.nerr()) {_err=1; return;}
	  _dn=(sp.size()>4) ? sp.stof(4) : 1;
	  if(sp.nerr() || _dn==0) {
	    printf("increment 'dN' should not be 0\n");
	    _err=1; return;
	  }
	  _init=0;
	} else {
	  double n = var->num(_tag) + _dn;
	  if(_dn > 0 && n <= _n1) {
	    var->set_num(_tag,n);
	  } else if(_dn < 0 && n >= _n1) {
	    var->set_num(_tag,n);
	  } else {
	    var->erase(_tag);
	  }
	}
	if(var->exist_num(_tag)) {
	  if(_dn > 0) {
	    _pass = (var->num(_tag) <= _n1);
	  } else {
	    _pass = (var->num(_tag) >= _n1);
	  }
	} else {
	  _pass = 0;
	}
      }
      if(sp(0)=="while") { // loop in the conditional expression
	if(sp.size()<2) {
	  printf("usage: while expression; ...; end\n");
	  _err=1; return;
	}
	std::string expr=buf.substr(sp.index(1));
	Logic logic;
	_pass = logic.eval(expr);
      }
    }
  };
//-----------------------------------------------------
  class If {
    bool _pass={0},_err={0};
    std::vector<size_t> _next_idx;
    size_t _else={0};
  public:
    If(void) {}
    bool pass(void) {return _pass;}
    bool err(void) {return _err;}
    size_t next_idx(void) {return _next_idx[_else];}
    size_t end_idx(void) {return _next_idx.back();}
    void add_next_idx(size_t n) {_next_idx.push_back(n);}

    void process(const std::string &buf) {
      StrSplit sp(buf);
      if(sp(0)=="if") {
	if(sp.size()<2) {
	  printf("if : lack of expression\n"); _err=1; return;
	}
	_else=0;
	std::string expr=buf.substr(sp.index(1));
	_pass = compare(expr);
      }
      if(sp(0)=="elif") {
	if(sp.size()<2) {
	  printf("elif : lack of expression\n"); _err=1; return;
	}
	_else++;
	std::string expr=buf.substr(sp.index(1));
	expr=expr.substr(0,expr.rfind(" "));
	_pass = compare(expr);
      }
      if(sp(0)=="else") {
	_else++;
	_pass = !_pass;
      }
    }
    bool compare(std::string &expr) { 
      Logic logic;
      return logic.eval(expr);
    }
  };
//-----------------------------------------------------
  class MacroTool {
  private:
    std::map<size_t,Loop> _loop;   // key=nline, val=Loop_object
    std::map<size_t,If> _if;       // key=nline, val=If_object
    int _break= {0};
    bool _quit = {0};
  public:
    Var var;
    MacroTool(void) {}
    bool quit(void) {return _quit;}
    int get_break(void) {return _break;}
    void set_break(int c) {_break=c;}
    void replace_esc(std::string &buf) {
      const char *s1[] = {"\\t","\\n"};
      const char *s2[] = {"\t","\n"};
      for(size_t j=0; j<2; j++) {
	std::string tag1 = s1[j];
	std::string tag2 = s2[j];
	for(size_t n=0; (n=buf.find(tag1))!= buf.npos;) {
	  buf.replace(n,tag1.size(),tag2);
	}
      }
    }
    void replace_env(std::string &buf) {
      std::string buf_org=buf;
      Bracket bc('{','}',buf_org);
      for(size_t j=0; j<bc.size(); j++) {
	if(bc.ib(j)<2) continue;
	if(buf_org[bc.ib(j)-2]=='$') {
	  char *env=0;
	  env=getenv(bc.contents(j).c_str());
	  if(env != 0) {
	    std::string tag = "${"+bc.contents(j)+"}";
	    for(size_t n=0; (n=buf.find(tag))!= buf.npos;) {
	      buf.replace(n,tag.size(),env);
	    }
	  }
	}
      }
    }
    void print_help(void) {
      const char *help =
	"macro commands:\n"
	" @     : define numerical or string variable\n"
	" args  : define default arguments of the macro file\n"
	" ++    : increment(+1) numerical variable\n"
	" --    : decrement(-1) numerical variable\n"
	" for   : foreach loop\n"
	" do    : numerical ranged loop\n"
	" if    : conditional branch\n"
	" print : print arguments (abbr. pr)\n"
	" fmt   : set output format of macro variable\n"
	" wait  : wait time or console input\n"
	" sys   : execute system command\n"
	" split : split string variable\n"
	" calc  : evaluate the numerical expression\n"
	" logic : evaluate the logical expression\n"
	" q     : terminate this program\n";
	printf("%s",help);
    }
    bool set_index(std::vector<std::string> &vbuf) {
      CFormat fmt;
      size_t nline=0; // index number of line
      std::vector<size_t> loop_index,if_index;
      _loop.clear(); _if.clear();
      for(auto &&buf : vbuf) {
	StrSplit args;
	args.set_quot_to_skip_split('"');
	args.split(buf);
	if(args.size() > 0) {
	  if(args(0)=="do" || args(0)=="for"|| args(0)=="while") {
	    loop_index.push_back(nline);
	    _loop[nline]=Loop();
	  }
	  if(args(0)=="break") {
	    buf += fmt(" %u",loop_index.back());
	  }
	  if(args(0)=="continue") {
	    buf += fmt(" %u",loop_index.back());
	  }
	  if(args(0)=="end") {
	    buf += fmt(" %u",loop_index.back());
	    _loop[loop_index.back()].set_end_idx(nline);
	    loop_index.pop_back();
	  }
	  if(args(0)=="if") {
	    if_index.push_back(nline);
	    _if[nline]=If();
	  }
	  if(args(0)=="elif"||args(0)=="else") {
	    buf += fmt(" %u",if_index.back());
	    _if[if_index.back()].add_next_idx(nline);
	  }
	  if(args(0)=="fi") {
	    _if[if_index.back()].add_next_idx(nline);
	    if_index.pop_back();
	  }
	}
	nline++;
      }
      if(loop_index.size()>0) {
	printf("loop is not closed by 'end'\n"); return 1;
      }
      if(if_index.size()>0) {
	printf("'if' is not closed by 'fi'\n"); return 1;
      }
      return 0;
    }
    int parse_vbuf(std::vector<std::string> &vbuf) {
      //      for(auto &&s : vbuf) printf("vbuf: [%s]\n",s.c_str());
      size_t nline=0; // index number of line
      while(nline < vbuf.size()) {
	if(_break=='b') {_break=0; break;}
	std::string buf=vbuf[nline];
	var.replace(buf);
	replace_env(buf);
	var.replace(buf);  // to replace nested variable [x[n]]
	StrSplit args;
	args.set_verbose(0);
	args.set_quot_to_skip_split('"');
	args.split(buf);
	if(args.size()==0) {nline++; continue;}
	if(args(0,0)=='#') {nline++; continue;}

	if(args(0)=="do" || args(0)=="for"|| args(0)=="while") {
	  if(_loop.count(nline)) {
	    Loop *ptr = &_loop[nline];
	    ptr->process(buf,&var);
	    if(ptr->err()) {
	      printf("loop error\n"); break;
	    }
	    if(!ptr->pass()) {
	      ptr->reset();
	      nline=ptr->end_idx()+1; continue;
	    }
	  }
	  nline++; continue;
	}
	if(args(0)=="break"||_break=='b') {
	  if(_break=='b') {_break=0; break;}
	  if(args.size()>1) {
	    nline=_loop[args.stoi(1)].end_idx()+1; continue;
	  }
	  nline++; continue;
	}
	if(args(0)=="end" || args(0)=="continue") {
	  if(args.size()>1) {
	    nline=args.stoi(1); continue;
	  } 
	  nline++; continue;
	}
	if(args(0)=="if") {
	  if(_if.count(nline)) {
	    If *ptr = &_if[nline];
	    ptr->process(buf);
	    if(ptr->err()) {
	      printf("if error\n"); break;
	    }
	    if(!ptr->pass()) {
	      nline=ptr->next_idx(); continue;
	    }
	  }
	  nline++; continue;
	}
	if(args(0)=="elif" || args(0)=="else") {
	  size_t n=args.stoi(args.size()-1);
	  if(_if.count(n)) {
	    If *ptr = &_if[n];
	    if(ptr->pass()) {
	      nline=ptr->end_idx(); continue;
	    } else {
	      ptr->process(buf);
	      if(ptr->err()) {
		printf("elif error\n"); break;
	      }
	      if(!ptr->pass()) {
		nline=ptr->next_idx(); continue;
	      }
	    }
	  }
	  nline++; continue;
	}
	if(args(0)=="fi") {
	  nline++; continue;
	}
	if(args(0)=="@") {
	  if(args.size()<2) {
	    printf("usage: @ x [=|+=|-=|*=|/=|%c=] expression\n"
		   "       @ t = time(s[,unit])\n"
		   " set the expression value to the macro variable x\n"
		   " convert ISO time string to unix epoch time and"
		   " vice versa\n",'%'
		   );
	  } else {
	    std::string expr = buf.substr(buf.find("@")+1);
	    var.set_eval(expr);
	  }
	  nline++; continue;
	}
	if(args(0)=="args") {
	  if(args.size() < 2) {
	    printf("usage: args [x1=v2,x2=v2,...]\n"
		   "       args [v1,v2,...]\n"
		   " set default arguments of macro variables\n"
		   " if they are specified only values,\n"
		   " variables are defined as $1=v1,$2=v2,...\n"
		   " number of arguments is defined as $#\n"
		   );
	  } else {
	    bool update = (args.size()>2 && args(2)=="update") ? 1 : 0;
	    var.set_arg_list(args(1),update);      
	  }
	  nline++; continue;
	}
	if(args(0).find("++") != buf.npos) {
	  StrSplit sp(buf," +");
	  if(sp.size()<1) {
	    printf("usage: ++var\n increment numerical macro variable\n");
	  } else {
	    std::string tag=trim(sp(0));
	    if(!var.exist(tag)) var.set_num(tag,0);
	    double x=var.num(tag)+1;
	    var.set_num(tag,x);
	  }
	  nline++; continue;
	}
	if(args(0).find("--") != buf.npos) {
	  StrSplit sp(buf," -");
	  if(sp.size()<1) {
	    printf("usage: --var\n decrement numerical macro variable\n");
	  } else {
	    std::string tag=trim(sp(0));
	    if(!var.exist(tag)) var.set_num(tag,0);
	    double x=var.num(tag)-1;
	    var.set_num(tag,x);
	  }
	  nline++; continue;
	}
	if(args(0)=="print" || args(0)=="println" ||
	   args(0)=="pr" || args(0)=="prn") {
	  if(args.size()<2) {
	    printf("usage: print args...\n"
		   "       println args...\n"
		   " print arguments with macro variables formated.\n"
		   "                 (see also 'fmt' command)\n"
		   "print  : line is not returned. (abbreviate to 'pr')\n"
		   "println: line is returned. (abbreviate to 'prn')\n"
		   );
	  } else {
	    replace_esc(buf);
	    std::string s = buf.substr(args.index(1));
	    printf("%s",s.c_str());
	    if(args(0)=="println"||args(0)=="prn") printf("\n");
	    fflush(stdout);
	  }
	  nline++; continue;
	}
	if(args(0) == "fmt") {
	  if(args.size()<2) {
	    printf("usage: fmt [\"format\"|reset|show]\n"
		   " specify output format of macro variable.\n"
		   " (it is same as printf)\n"
		   " if \"reset\", it is set to default (\"%s\")\n"
		   " if \"show\", print current format\n"
		   " example: @ x=1; fmt %s; prn [x]\n"
		   " output:  001\n","%.11g","%03.0f"
		   );
	  } else {
	    if(args(1)=="reset") {
	      var.reset_fmt();
	    } else if(args(1)=="show") {
	      var.print_fmt();
	    } else {
	      var.set_fmt(trim(args(1)));
	    }
	  }
	  nline++; continue;
	}
	if(args(0)=="sys") { // execute system command
	  if(args.size() < 2) {
	    printf("usage: sys [command]\n"
		   " execute system command\n"
		   );
	  } else {
	    size_t n = buf.find(args(0));
	    system(buf.substr(n+args(0).size()).c_str());
	  }
	  nline++; continue;
	}
	if(args(0)=="wait") {
	  if(args.size() < 2) {
	    printf("usage: wait [t]\n"
		   " wait t seconds, (t is floating point number)\n"
		   " if t=0 wait console input\n");
	  } else {
	    if(args.stof(1)==0) {
	      printf("continue? (Y/n)> ");
	      char c,s[8]; fgets(s,8,stdin); sscanf(s,"%c\n",&c);
	      _break = (c=='n'||c=='N') ? 'b' : 0;
	    } else {
	      unsigned int ut = (unsigned int)(args.stof(1)*1000000.);
	      usleep(ut);
	    }
	  }
	  nline++; continue;
	}
	if(args(0)=="calc") { // for the debug of Calc
	  if(args.size() < 2) {
	    printf("usage: calc [expression]\n");
	  } else {
	    std::string expr = buf.substr(args.index(1));
	    Calc calc;
	    printf("[%s] -> ",expr.c_str());
	    printf("[%.11g]\n",calc.eval(expr));
	  }
	  nline++; continue;
	}
	if(args(0)=="logic") { // for the debug of Logic
	  if(args.size() < 2) {
	    printf("usage: logic [expression]\n");
	  } else {
	    std::string expr = trim(buf.substr(args.index(1)));
	    Logic logic; bool debug=1;
	    logic.eval(expr,debug);
	  }
	  nline++; continue;
	}
	if(args(0)=="split") {
	  if(args.size() < 2) {
	    printf("usage: split s [fs]\n"
		   " split the string macro variable by delomiter fs\n"
		   " default delimiter is white space\n"
		   " splitted string variables are created named s1,..,sN\n"
		   " (N is number of splitted string)\n"
		   );
	  } else {
	    if(args.size() < 3) {var.split(args(1));}
	    else {var.split(args(1),args(2));} 
	  }
	  nline++; continue;
	}
	if(args(0)=="q") {
	  _quit=1; break;
	}

	int ret = add_commands(buf);
	if(ret==0) {
	  nline++; continue;
	} else if (ret==1) {
	  printf("command not found: %s\n",args(0).c_str());
	  printf("try 'help' to learn available commands\n");
	} else {
	  printf("aborted by error\n");
	}
	break;
      }
      return 0;
    }
    void exec(const std::string &fname, const std::string &arg_list) {
      std::ifstream ifs(fname.c_str());
      if(ifs) {
	std::vector<std::string> vbuf;
	std::string line;
	while(std::getline(ifs,line)) {
	  if(line.size()>0) {
	    if(line[line.find_first_not_of(" \t")]=='#') continue;
	    StrSplit sp;
	    sp.set_quot_to_skip_split('"');
	    sp.split(line,";");
	    if(sp.size()>0) {
	      for(auto &&s : sp) {vbuf.push_back(s);}
	    }
	  }
	}
	if(set_index(vbuf)==0) {
	  var.set_arg_list(arg_list);
	  parse_vbuf(vbuf);
	}
      }
    }
    void main_loop(std::string prompt="> ",
		   std::string history_fname=".macro_history") {
      ReadLine read_line(prompt,history_fname);
      read_line.set_comment('#');
      read_line.set_quot_to_skip_split('"');
      while(! quit()) {
	std::vector<std::string> vbuf;
	std::string line=read_line.get_split_string(";");
	StrSplit sp;
	sp.set_quot_to_skip_split('"');
	sp.split(line);
	if(sp.size()==0) continue;
	if(sp(0)=="do"|| sp(0)=="for"||sp(0)=="while") {
	  if(sp.size()<2) {
	    if(sp(0)=="do") printf("usage: do n N1 N2 [dN]; ...; end\n");
	    if(sp(0)=="for") printf("usage: for s (a b ...); ...; end\n");
	    if(sp(0)=="while") printf("usage: while expr; ...; end\n");
	    continue;
	  }
	  vbuf.push_back(line);
	  read_line.set_prompt("loop> ");
	  int nest=1;
	  while(nest > 0) {
	    std::string line2=read_line.get_split_string(";");
	    StrSplit sp2(line2);
	    if(sp2.size()==0) continue;
	    if(sp2(0)=="for"||sp2(0)=="do"||sp2(0)=="while") {nest++;}
	    if(sp2(0)=="end") {nest--;}
	    vbuf.push_back(line2);
	  }
	  if(set_index(vbuf)==0) {parse_vbuf(vbuf);}
	  read_line.set_prompt(prompt);
	} else if(sp(0)=="if") {
	  if(sp.size()<2) {
	    printf("usage: if expr; ...; elif expr; ...; else; ...; fi\n");
	    continue;
	  }
	  vbuf.push_back(line);
	  read_line.set_prompt("if> ");
	  int nest=1;
	  while(nest > 0) {
	    std::string line2=read_line.get_split_string(";");
	    StrSplit sp2(line2);
	    if(sp2.size()==0) continue;
	    if(sp2(0)=="if") {nest++;}
	    if(sp2(0)=="fi") {nest--;}
	    vbuf.push_back(line2);
	  }
	  if(set_index(vbuf)==0) {parse_vbuf(vbuf);}
	  read_line.set_prompt(prompt);
	} else {
	  vbuf.push_back(line);
	  parse_vbuf(vbuf);
	}
      }
    }
    virtual int add_commands(std::string buf) {return 0;}

  };//end of class MacroTool
 
}//-- namespace thl

#endif //THL_MACRO_TOOL_HH
