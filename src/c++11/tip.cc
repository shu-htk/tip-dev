// tip : tiny interactive plot
//
// -std=c++11
//
#include <algorithm> // std::sort
#include <numeric>   // std::iota
#include "thl/ArgOpt.hh"
#include "thl/ReadLine.hh"
#include "thl/PLPlot.hh"
#include "thl/LsFit.hh"
#include "thl/Histogram.hh"
#include "thl/FFT.hh"
#include "thl/Random.hh"
#include "thl/MovAve.hh"
#include "thl/MacroTool.hh"
#if USE_EPICS_CA 
#include "thl/EpicsCA.hh"
#endif

class Tip : public thl::MacroTool {
private:
  enum class DataType {Num,Str,Mesh};
  struct Data {
    DataType type;
    std::vector<double> num;
    std::vector<std::string> str;
    std::vector<std::vector<double> > mesh;
    Data(void) {}
    void clear(void) {
      if(num.size()>0) num.clear();
      if(str.size()>0) str.clear();
      if(mesh.size()>0) mesh.clear();
    }
    size_t size(void) {
      if(type==DataType::Str) return str.size();
      if(type==DataType::Mesh) return mesh.size();
      if(type==DataType::Num) return num.size();
      return 0;
    }
    void print(size_t j) {
      if(type==DataType::Str) printf("%s",str[j].c_str());
      if(type==DataType::Num) printf("%.11g",num[j]);
    }
    const char *type_name(void) {
      if(type==DataType::Num) return "num";
      if(type==DataType::Str) return "str";
      if(type==DataType::Mesh) return "mesh";
      else return "unknown";
    }
  };
  struct Option {
    double cx={0},cy={0},x0={0},x1={0},y0={0},y1={0},z0={0},z1={0},
           fx0={0},fx1={0},dt={1},fq={1};
    int n0={0},n1={-1},nb={100},nx={20},ny={20},bp={0},dm={0},mv={1},ae={0};
    bool rp={0}, cr={1}, rc={0}, fl={1}, nf={0};
    std::string fs={" \t\n"},fw={"rc"},cf={""},cc={""},sd={"clock"},
                gt={"slope"},ht={"bin1"},mt={"mesh1"},tf={""},td={"- :"};
    thl::PLAtt att;
    Option(void) {}
    void print(const std::string &s) {
      if(s=="ae"||s=="*") printf("ae: arrow edge(0=non,1=end,2=begin,3=both):"
				 " [%d]\n", att.asty);
      if(s=="al"||s=="*") printf("al: altitude: [%g]\n", att.alt);
      if(s=="az"||s=="*") printf("az: azimuth: [%g]\n", att.az);
      if(s=="bo"||s=="*") printf("bo: box drawing order : [%d]\n",att.divo);
      if(s=="bp"||s=="*") printf("bp: box position : [%d]\n",bp);
      if(s=="cc"||s=="*") printf("cc: cut condition: [%s]\n",cc.c_str());
      if(s=="cf"||s=="*") printf("cf: tag of fit.coeff: [%s]\n",cf.c_str());
      if(s=="cp"||s=="*") printf("cp: comment position: [%g,%g]\n",cx,cy);
      if(s=="cr"||s=="*") printf("cr: clear flag : [%d]\n",cr);
      if(s=="dm"||s=="*") printf("dm: debug mode : [%d]\n",dm);
      if(s=="dt"||s=="*") printf("dt: time tick of FFT: [%g]\n",dt);
      if(s=="fc"||s=="*") printf("fc: fill area color: [%s]\n",
				 att.index_to_color(att.fcol));
      if(s=="fl"||s=="*") printf("fl: flush flag: [%d]\n",fl);
      if(s=="fq"||s=="*") printf("fq: freq of sin.fit: [%.11g]\n",fq);
      if(s=="fr"||s=="*") printf("fr: fitting range: [%g,%g]\n",fx0,fx1);
      if(s=="fs"||s=="*") printf("fs: field separator : [%s]\n",
				 (fs==" \t\n") ? "white space" : fs.c_str());
      if(s=="ft"||s=="*") printf("ft: fill area style: [%s]\n",
				 att.index_to_fill(att.fsty));
      if(s=="fw"||s=="*") {
	printf("fw: FFT window func (rc,hn,hm,bk,bh): [%s]\n",fw.c_str());
      }
      if(s=="gc"||s=="*") printf("gc: gradient of contour : [%d]\n",att.grad);
      if(s=="gd"||s=="*") printf("gd: grid flag : [%d]\n",att.grid);
      if(s=="gt"||s=="*") {
	printf("gt: graph type (slope,bin1,bin2): [%s]\n",gt.c_str());
      }
      if(s=="ht"||s=="*") {
	printf("ht: histogram type (bin1,bin2,slope): [%s]\n",ht.c_str());
      }
      if(s=="lc"||s=="*") printf("lc: line color : [%s]\n",
				 att.index_to_color(att.lcol));
      if(s=="lt"||s=="*") printf("lt: line style : [%s]\n",
				 att.index_to_line(att.lsty));
      if(s=="lw"||s=="*") printf("lw: line width : [%d]\n",att.lwid);
      if(s=="mt"||s=="*") {
	printf("mt: mesh graph type (mesh1,mesh2,cont1,cont2): [%s]\n",
	       mt.c_str());
      }
      if(s=="mv"||s=="*") printf("mv: moving average number: [%d]\n",mv);
      if(s=="nb"||s=="*") printf("nb: histogram bin: [%d]\n",nb);
      if(s=="nf"||s=="*") printf("nf: take null field: [%d]\n",nf);
      if(s=="nr"||s=="*") printf("nr: numbers range: [%d,%d]\n",n0,n1);
      if(s=="nx"||s=="*") printf("nx: 2D-histogram xbin: [%d]\n",nx);
      if(s=="ny"||s=="*") printf("ny: 2D-histogram ybin: [%d]\n",ny);
      if(s=="rc"||s=="*") printf("rc: relative coordinate flag: [%d]\n",rc);
      if(s=="rp"||s=="*") printf("rp: replot flag: [%d]\n",rp);
      if(s=="sc"||s=="*") printf("sc: symbol color: [%s]\n",
				 att.index_to_color(att.scol));
      if(s=="sd"||s=="*") printf("sd: random seed: [%s]\n",sd.c_str());
      if(s=="st"||s=="*") printf("st: symbol type : [%s]\n",
				 att.index_to_symbol(att.symb));
      if(s=="ss"||s=="*") printf("ss: symbol size : [%g]\n",att.ssiz);
      if(s=="tc"||s=="*") printf("tc: text color : [%s]\n",
				 att.index_to_color(att.tcol));
      if(s=="td"||s=="*") {
	printf("td: time-format-delimiters : [%s]\n",td.c_str());
      }
      if(s=="tf"||s=="*") {
	printf("tf: x-axis time format: [%s]\n", tf.c_str());
      }
      if(s=="tl"||s=="*") printf("tl: graph title : [%s]\n",att.title);
      if(s=="tp"||s=="*") printf("tp: text pos(0:L to 1:R) : [%g]\n",att.tpos);
      if(s=="tr"||s=="*") printf("tr: text rotation(deg) : [%g]\n",att.trot);
      if(s=="ts"||s=="*") printf("ts: text size : [%g]\n",att.tsiz);
      if(s=="xl"||s=="*") printf("xl: x-axis label: [%s]\n",att.xlab);
      if(s=="xm"||s=="*") printf("xm: x margin factor: [%g]\n",att.ascx);
      if(s=="xn"||s=="*") printf("xn: x-subtick num: [%d]\n",att.nxsub);
      if(s=="xr"||s=="*") printf("xr: x-axis range: [%g,%g]\n",x0,x1);
      if(s=="xs"||s=="*") printf("xs: x-axis scale: [%s]\n",
				 att.logx ? "log" : "lin");
      if(s=="xt"||s=="*") printf("xt: x-tick interval: [%g]\n",att.xtick);
      if(s=="yl"||s=="*") printf("yl: y-axis label: [%s]\n",att.ylab);
      if(s=="ym"||s=="*") printf("ym: y margin factor: [%g]\n",att.ascy);
      if(s=="yn"||s=="*") printf("yn: y-subtick num: [%d]\n",att.nysub);
      if(s=="ys"||s=="*") printf("ys: y-axis scale: [%s]\n",
				 att.logy ? "log" : "lin");
      if(s=="yt"||s=="*") printf("yt: y-tick interval: [%g]\n",att.ytick);
      if(s=="yr"||s=="*") printf("yr: y-axis range: [%g,%g]\n",y0,y1);
      if(s=="zl"||s=="*") printf("zl: z-axis label: [%s]\n",att.zlab);
      if(s=="zm"||s=="*") printf("zm: z margin factor: [%g]\n",att.ascz);
      if(s=="zr"||s=="*") printf("zr: z-axis range: [%g,%g]\n",z0,z1);

//-- the following tags just show the available names (not set anything)
      if(s=="color"||s=="c") {
	printf("color names of the symbol/line/fill :\n"
	     " red(1), yellow(ylw,2), green(grn,3), aqua(aqu,4), pink(pnk,5)\n"
	     " wheat(wht,6), gray(gry,7), brown(brn,8), blue(blu,9), "
	       "violet(vio,10)\n cyan(cyn,11), turquoise(tqs,12), "
	       "magenta(mgt,13), salmon(smn,14)\n black(blk,15)\n"
	       );
      }
      if(s=="line"||s=="l") {
	printf("names of line style:\n"
	       " solid(sld,1),dot(2),dash(dsh,3)\n"
	       );
      }
      if(s=="symbol"||s=="s") {
	printf("names of the symbol :\n"
	       " non(0), dot(1), plus(pls,2), star(str,3), arc(4),"
	       " cross(crs,5), square(sqr,6),\n triangle(tri,7),"
	       " arccross(acc,8), arcdot(acd,9), square2(sq2,10),\n"
	       " diamond(dia,11), star2(st2,12), square3(sq3,13),"
	       " cross2(cr2,14), star3(st3,15),\n blacksqr,(bsq,16)\n"
	       );
      }
      if(s=="fill"||s=="f") {
	printf("names of the fill area style:\n"
	       " null(-1), solid(s,0), hor(1), ver(2), p45(3), n45(4),"
	       " p30(5), n30(6), hv(7), pn45(8)\n"
	       );
      }
    }
  };
  thl::PLPlot* _pl;
  std::map<std::string,Data> _dat; // data tagged by string
  Option _gopt; // global option
#if USE_EPICS_CA
  std::map<std::string,thl::EpicsCA> _ca;
#endif
public:
  Tip(thl::PLPlot* pl) {_pl=pl; _pl->divide(1,1);}
  template<class T> void get_pair(const std::string &s, T &left, T &right) {
    thl::StrSplit sp(s,",");
    if(sp.size() < 2) {
      printf("[%s] should be 2 values separated by \",\"\n",s.c_str());
    }
    left  = (T)sp.stof(0);
    right = (T)sp.stof(1);
  }
  Option get_opt(const std::string &s) {
    thl::Bracket bc('(',')',s);
    if(bc.size()==0) return _gopt;
    Option opt = _gopt;
    thl::StrSplit items;
    items.set_quot_to_skip_split('"');
    items.split(bc.last_contents());
    for(auto &&item : items) {
      thl::StrSplit sp;
      sp.set_quot_to_skip_split('"');
      sp.split(item,":");
      if(sp.size() < 2) {continue;}  //invalid option ignored
      if(sp(0)=="ae") {opt.att.asty = sp.stoi(1);}
      if(sp(0)=="al") {opt.att.alt = sp.stof(1);}
      if(sp(0)=="az") {opt.att.az = sp.stof(1);}
      if(sp(0)=="bo") {opt.att.divo = sp.stoi(1);}
      if(sp(0)=="bp") {opt.bp = sp.stoi(1);}
      if(sp(0)=="cc") {opt.cc = thl::trim(sp(1));}
      if(sp(0)=="cf") {opt.cf = sp(1);}
      if(sp(0)=="cp") {get_pair(sp(1), opt.cx, opt.cy);}
      if(sp(0)=="cr") {opt.cr = sp.stoi(1);}
      if(sp(0)=="dm") {opt.dm = sp.stoi(1);}
      if(sp(0)=="dt") {opt.dt = sp.stof(1);}
      if(sp(0)=="fc") {opt.att.fcol = opt.att.color_to_index(sp(1));}
      if(sp(0)=="fl") {opt.fl = sp.stoi(1);}
      if(sp(0)=="fq") {opt.fq = sp.stof(1);}
      if(sp(0)=="fr") {get_pair(sp(1), opt.fx0, opt.fx1);}
      if(sp(0)=="fs") {
	opt.fs = thl::trim(sp(1)); replace_esc(opt.fs);
	if(opt.fs=="WS") {opt.fs=" \t\n";}
      }
      if(sp(0)=="ft") {opt.att.fsty = opt.att.fill_to_index(sp(1));}
      if(sp(0)=="fw") {opt.fw = sp(1);}
      if(sp(0)=="gc") {opt.att.grad = sp.stoi(1);}
      if(sp(0)=="gd") {opt.att.grid = sp.stoi(1);}
      if(sp(0)=="gt") {opt.gt = sp(1);}
      if(sp(0)=="ht") {opt.ht = sp(1);}
      if(sp(0)=="lc") {opt.att.lcol = opt.att.color_to_index(sp(1));}
      if(sp(0)=="lt") {opt.att.lsty = opt.att.line_to_index(sp(1));}
      if(sp(0)=="lw") {opt.att.lwid = sp.stoi(1);}
      if(sp(0)=="mt") {opt.mt = sp(1);}
      if(sp(0)=="mv") {opt.mv = sp.stoi(1);}
      if(sp(0)=="nb") {opt.nb = sp.stoi(1);}
      if(sp(0)=="nf") {opt.nf = sp.stoi(1);}
      if(sp(0)=="nr") {get_pair(sp(1), opt.n0, opt.n1);}
      if(sp(0)=="nx") {opt.nx = sp.stoi(1);}
      if(sp(0)=="ny") {opt.ny = sp.stoi(1);}
      if(sp(0)=="rc") {opt.rc = sp.stoi(1);}
      if(sp(0)=="rp") {opt.rp = sp.stoi(1);}
      if(sp(0)=="sc") {opt.att.scol = opt.att.color_to_index(sp(1));}
      if(sp(0)=="sd") {opt.sd = sp(1);}
      if(sp(0)=="ss") {opt.att.ssiz = sp.stof(1);}
      if(sp(0)=="st") {opt.att.symb = opt.att.symbol_to_index(sp(1));}
      if(sp(0)=="tc") {opt.att.tcol = opt.att.color_to_index(sp(1));}
      if(sp(0)=="td") {opt.td=thl::trim(sp(1)); var.ts.set_delimiters(opt.td);}
      if(sp(0)=="tf") {opt.tf=thl::trim(sp(1)); set_tfmt(opt);}
      if(sp(0)=="tl") {opt.att.set_title(thl::trim(sp(1)).c_str());}
      if(sp(0)=="tp") {opt.att.tpos = sp.stof(1);}
      if(sp(0)=="tr") {opt.att.trot = sp.stof(1);}
      if(sp(0)=="ts") {opt.att.tsiz = sp.stof(1);}
      if(sp(0)=="xl") {opt.att.set_xlab(thl::trim(sp(1)).c_str());}
      if(sp(0)=="xm") {opt.att.ascx = sp.stof(1);}
      if(sp(0)=="xn") {opt.att.nxsub = sp.stoi(1);}
      if(sp(0)=="xr") {get_pair(sp(1), opt.x0, opt.x1);}
      if(sp(0)=="xs") {opt.att.logx = (sp(1)=="log")? 1 : 0;}
      if(sp(0)=="xt") {opt.att.xtick = sp.stof(1);}
      if(sp(0)=="yl") {opt.att.set_ylab(thl::trim(sp(1)).c_str());}
      if(sp(0)=="ym") {opt.att.ascy = sp.stof(1);}
      if(sp(0)=="yn") {opt.att.nysub = sp.stoi(1);}
      if(sp(0)=="yr") {get_pair(sp(1), opt.y0, opt.y1);}
      if(sp(0)=="ys") {opt.att.logy = (sp(1)=="log")? 1 : 0;}
      if(sp(0)=="yt") {opt.att.ytick = sp.stof(1);}
      if(sp(0)=="zl") {opt.att.set_zlab(thl::trim(sp(1)).c_str());}
      if(sp(0)=="zm") {opt.att.ascz = sp.stof(1);}
      if(sp(0)=="zr") {get_pair(sp(1), opt.z0, opt.z1);}
    }
    return opt;
  }
  void set_tfmt(Option &opt) {
    if(opt.tf.size()>0) {
      opt.att.set_time_fmt(opt.tf.c_str());
      opt.att.time_xaxis = 1;
    } else {
      opt.att.time_xaxis = 0;
    }
  }
  double str_to_val(const std::string &s,  DataType &type) {
    thl::StrNum sn;
    sn.set_verbose(0);
    double x = sn.stof(s);
    if(sn.nerr()==1 || sn.nerr()==3) {
      type=DataType::Num; return x;
    }
    if(var.ts.distinguish_time_string(s) > 0 || sn.nerr()==2) {
      type=DataType::Str; return 0;
    }
    type=DataType::Num; return x;
  }
  int check_data1(const std::string &v, int quiet=0) {
    if(_dat.count(v)==0) {
      if(!((quiet>>4)&1)) printf("%s is not defined\n",v.c_str());
      return 4;
    }
    if(_dat[v].type==DataType::Mesh) {
      if(!((quiet>>3)&1))printf("%s type=%s\n", v.c_str(),_dat[v].type_name());
      return 3;
    }
    if(_dat[v].type==DataType::Str) {
      if(!((quiet>>2)&1)) printf("%s type=%s\n",v.c_str(),_dat[v].type_name());
      return 2;
    }
    if(_dat[v].num.size()==0) {
      if(!((quiet>>1)&1)) printf("%s no data\n",v.c_str());
      return 1;
    }
    return 0;
  }
  int check_data2(const std::string &vx, const std::string &vy, int quiet=0) {
    int retx = check_data1(vx,quiet); if(retx) return retx;
    int rety = check_data1(vy,quiet); if(rety) return rety;
    if(_dat[vx].num.size()!=_dat[vy].num.size()) {
      if(!((quiet>>1)&5))
	printf("size of %s != size of %s\n", vx.c_str(),vy.c_str());
      return 5;
    }
    return 0;
  }
  int data_set_list(const std::string &v, const std::string &expr) {
    thl::Bracket bc('{','}',expr); if(bc.size()<1) return 1;
    _dat[v].clear();
    thl::Calc calc;
    thl::StrSplit sp;
    sp.set_quot_to_skip_split('"');
    sp.split(bc.contents(0),", ");
    for(auto && s :sp) {
      double x = calc.eval(s);
      _dat[v].type = calc.not_digit() ? DataType::Str : DataType::Num;
      if(_dat[v].type==DataType::Str) {
	_dat[v].str.push_back(thl::trim(s));
      } else {
	_dat[v].num.push_back(x);
      }
    }
    return 0;
  }
  int data_set_range(const std::string &v, const std::string &expr) {
    thl::Bracket bc('(',')',expr); if(bc.size()<1) return 1;
    thl::StrSplit sp(bc.contents(0),",");
    if(sp.size()<3) {
      printf("range() should have at least 3 arguments\n"
	     " N:number of data, x0:initial value, x1:final value\n");
      return 1;
    } else {
      DataType type0, type1;
      int ndata = sp.stoi(0);
      double x0 = str_to_val(sp(1),type0);
      double x1 = str_to_val(sp(2),type1);
      if(type0 != DataType::Num || type1 != DataType::Num) {
	printf("data type should be numerical\n"); return 1;
      }
      if(ndata < 1) {
	printf("N > 0 required\n"); return 1;
      } 
      _dat[v].type = type0;
      _dat[v].clear();
      if(ndata==1) {
	_dat[v].num.push_back(x0);
      } else {
	double dx = (x1-x0)/(double)(ndata-1);
	for(int j=0; j<ndata; j++) {
	  _dat[v].num.push_back(x0+dx*j);
	}
      }
      return 0;
    }
  }
  int data_set_random(const std::string &v, const std::string &expr,
		     Option &opt) {
    thl::Bracket bc('(',')',expr); if(bc.size()<1) return 1;
    _dat[v].clear(); _dat[v].type = DataType::Num;
    thl::StrSplit sp(bc.contents(0),",");
    if(sp.size()<2) {
      printf("random() should have at least 2 arguments\n"); return 1;
    } else {
      thl::Random rdm;
      thl::StrNum sn;
      if(opt.sd=="utime") rdm.set_seed_by_utime();
      else if(opt.sd=="clock") rdm.set_seed_by_clock();
      else rdm.set_seed((unsigned long)sn.stol(opt.sd));
      int ndata = sp.stoi(0);
      if(sp(1)=="uni" || sp(1)=="u") {
	double x0 = (sp.size()>2) ? sp.stof(2) : 0;
	double x1 = (sp.size()>3) ? sp.stof(3) : x0+1;
	for(int n=0; n<ndata; n++) {
	  _dat[v].num.push_back(rdm.uniform(x0,x1));
	}
      } else if(sp(1)=="gaus" || sp(1)=="g") {
	double sgm = (sp.size()>2) ? sp.stof(2) : 1;
	double mean = (sp.size()>3) ? sp.stof(3) : 0;
	for(int n=0; n<ndata; n++) {
	  _dat[v].num.push_back(rdm.gaus(sgm,mean));
	}
      } else if(sp(1)=="exp" || sp(1)=="e") {
	double tau = (sp.size()>2) ? sp.stof(2) : 1;
	for(int n=0; n<ndata; n++) {
	  _dat[v].num.push_back(rdm.exp(tau));
	}
      } else {
	printf("data_set_random(): undefined random name %s\n",sp(1).c_str());
      }
      return 0;
    }
  }
  int data_set_time(const std::string &v, const std::string &expr,
		    Option &opt) {
    var.ts.set_delimiters(opt.td);
    thl::Bracket bc('(',')',expr); if(bc.size()<1) return 1;
    thl::StrSplit sp(bc.contents(0),",");
    if(sp.size()==0) {
      printf("time(): lack of arguments.\n"); return 1;
    }
    std::string tag = sp(0);
    std::string unit = (sp.size()>1) ? sp(1) : "";
    if(tag=="now") {
      double utime = var.ts.str_to_num("now","utime");
      std::string ts = var.ts.utime_to_str(utime,1);
      if(unit=="str") {
	_dat[v].type = DataType::Str; _dat[v].clear();
	_dat[v].str.push_back(ts);
      } else {
	_dat[v].type = DataType::Num; _dat[v].clear();
	_dat[v].num.push_back(var.ts.str_to_num(ts,unit));
      }
    } else {
      if(_dat.count(tag)==0) {
	printf("[%s] not found.\n",tag.c_str()); return 1;
      }
      if(_dat[tag].type == DataType::Str) {
	_dat[v].type = DataType::Num; _dat[v].clear();
	for(auto &&s : _dat[tag].str) {
	  _dat[v].num.push_back(var.ts.str_to_num(s,unit));
	}
      }
      if(_dat[tag].type == DataType::Num) {
	if(unit=="str") {
	  _dat[v].type = DataType::Str; _dat[v].clear();
	  for(auto x : _dat[tag].num) {
	    _dat[v].str.push_back(var.ts.utime_to_str(x,1));
	  }
	} else {
	  _dat[v].type = DataType::Num; _dat[v].clear();
	  for(auto x : _dat[tag].num) {
	    _dat[v].num.push_back(var.ts.utime_to_num(x,unit));
	  }
	}
      }
    }
    return 0;
  }
  void find_tags(std::vector<std::string> &tags, const std::string &expr) {
    thl::StrSplit sp(expr,"()+-*/%<>=!, \t");
    for(auto &&s : sp) {
      if(_dat.count(s)>0) {
	if(_dat[s].type==DataType::Mesh) {
	  printf("'%s': type[mesh] : ignored.\n",s.c_str());
	} else {
	  bool exist=0;
	  for(auto &&tag : tags) {if(s==tag) exist=1;}
	  if(!exist) tags.push_back(s);
	}
      }
    }
  }
  int data_set_eval(const std::string &v, const std::string &expr) {
    thl::Calc calc;
    std::vector<std::string> tags;
    find_tags(tags,expr);
    _dat[v].clear();
    if(tags.size()>0) {
      for(auto &&tag : tags) {
	if(check_data2(tags[0],tag)) return 1;
      }
      for(size_t j=0; j<_dat[tags[0]].num.size(); j++) {
	for(auto &&tag : tags) {
	  calc.set_var_num(tag,_dat[tag].num[j]);
	}
	_dat[v].num.push_back(calc.eval(expr));
      }
      _dat[v].type = _dat[tags[0]].type;
      return 0;
    } else {
      double x = calc.eval(expr);
      if(calc.not_digit()) {
	_dat[v].str.push_back(expr);
	_dat[v].type=DataType::Str;
      } else {
	_dat[v].num.push_back(x);
	_dat[v].type=DataType::Num;
      }
      return 1;
    }
  }
  int data_make_cut(const std::string vlist, const std::string &expr) {
    thl::StrSplit sp(vlist,",");
    thl::Logic logic;
    std::vector<std::string> tags;
    std::vector<bool> vbool;
    bool flag_s=0; // =1 if it is string data
    find_tags(tags,expr);
    if(tags.size()>0) {
      int quiet=1<<2;
      for(auto &&tag : tags) {
	if(check_data1(tag,quiet) == 2) flag_s=1;
      }
      for(auto &&tag : tags) {
	if(check_data2(sp(0),tag,quiet) > 2) return 1;
      }
      for(size_t j=0; j<_dat[tags[0]].size(); j++) {
	if(flag_s) {
	  for(auto &&tag : tags) {
	    logic.str.set_var(tag,_dat[tag].str[j]);
	  }
	  vbool.push_back(logic.str.eval(expr));
	} else {
	  for(auto &&tag : tags) {
	    logic.num.set_var(tag,_dat[tag].num[j]);
	  }
	  vbool.push_back(logic.num.eval(expr));
	}
      }
      size_t ncut=0;
      for(auto &&s : sp) {
	if(_dat.count(s+"_cut")>0) _dat[s+"_cut"].clear(); 
	_dat[s+"_cut"].type = _dat[s].type;
	for(size_t j=0; j<_dat[s].size(); j++) {
	  if(vbool[j]) {
	    if(_dat[s+"_cut"].type==DataType::Str) {
	      _dat[s+"_cut"].str.push_back(_dat[s].str[j]);
	    } else {
	      _dat[s+"_cut"].num.push_back(_dat[s].num[j]);
	    }
	    ncut++;
	  }
	}
      }
      if(ncut==0) {
	printf("no data after the cut\n");
	return 1;
      } else {
	return 0;
      }
    } else {
      printf("data tags are not in the expression\n"
	     "data is not cut\n");
      return 1;
    }
  }
  int data_make_mave(const std::string vlist, int nave) {
    thl::StrSplit sp(vlist,",");
    for(auto &&s : sp) {
      if(check_data2(sp(0),s)) return 1;
    }
    for(auto &&s : sp) {
      thl::MovAve<double> mave(_dat[s].num, nave);
      thl::CFormat fmt;
      std::string tag = s+"_m"+fmt("%d",nave);
      _dat[tag].type = DataType::Num;
      _dat[tag].num = mave.data();
    }
    return 0;
  }
  void check_data_file(const std::string &fname, Option &opt) {
    std::ifstream ifs(fname.c_str());
    if(ifs) {
      int nline=1;
      std::string buf;
      while(std::getline(ifs,buf)) {
	if(nline <opt.n0 ) {nline++; continue;}
	break;
      }
      if(buf.find(",")!=buf.npos) {
	if(opt.fs==" \t\n") {
	  opt.fs=",";
	  printf("check_data_file: field separator is set to \",\"\n");
	}
      }
      int n=0;
      for(auto c: buf) {if(c=='/') n++;}
      if(n>1) {
	printf("check_data_file: date,time delimiters are set to \"/ :\"\n");
	_gopt.td="/ :";
      }
    }
  }
  int data_read(const std::string &v_str, const std::string &fname,
	       Option &opt) {
    std::ifstream ifs(fname.c_str());
    if(ifs) {
      thl::CFormat fmt;
      thl::StrSplit v_list(v_str,","); // get list of variables
      std::map<std::string,bool> first;
      int nline=1;
      thl::StrSplit sp;
      sp.take_null_field(opt.nf);
      sp.set_quot_to_skip_split('"');
      check_data_file(fname,opt);
      std::string buf;
      while(std::getline(ifs,buf)) {
	if(buf.size()==0) continue;
	if(nline <opt.n0 ) {nline++; continue;}
	if(opt.n1 > 0 && nline >opt.n1) {break;}
	sp.split(buf,opt.fs);
	if(sp(0,0)=='#') continue;
	for(size_t j=0; j<sp.size(); j++) {
	  size_t n = v_list.size();
	  std::string v_n = (j<n) ? v_list(j) : v_list.back()+fmt("%d",j-n+2);
	  if(n!=sp.size() && j==n-1) v_n += "1";
	  DataType type;
	  double val = sp(j).size() ? str_to_val(sp(j),type) : 0;
	  if(first.count(v_n)==0) {
	    first[v_n]=1; _dat[v_n].clear();
	    _dat[v_n].type = type;
	  }
	  if(_dat[v_n].type==DataType::Str) {
	    _dat[v_n].str.push_back(thl::trim(sp(j)));
	  } else {
	    _dat[v_n].num.push_back(val);
	  }
	}
	nline++;
      }
    } else {
      printf("can't open %s\n",fname.c_str());
      return 1;
    }
    return 0;
  }
  int data_write(const std::vector<std::string> vlist,
		 const std::string &fname, Option &opt) {
    std::ofstream ofs(fname.c_str());
    if(ofs) {
      std::string fs = (opt.fs==" \t\n") ? " " : opt.fs;
      if(vlist.size() > 0) {
	size_t size=_dat[vlist[0]].size();
	for(auto &&v : vlist) {
	  if(_dat[v].size() < size) size=_dat[v].size();
	}
	if(size != _dat[vlist[0]].size()) {
	  printf("warning: data size is arranged to %lu\n",size);
	}
	thl::CFormat fmt;
	for(size_t j=0; j < size; j++) {
	  for(size_t k=0; k<vlist.size(); k++) {
	    std::string v=vlist[k];
	    if(_dat[v].type==DataType::Str) {
	      ofs << fmt("\"%s\"",_dat[v].str[j].c_str());
	    } else {
	      ofs << fmt("%.11g",_dat[v].num[j]);
	    }
	    if(k<vlist.size()-1) ofs << fs;
	  }
	  ofs << std::endl;
	}
      }
    } else {
      printf("can't open %s\n",fname.c_str());
      return 1;
    }
    return 0;
  }
  int data_make_sort(const std::string &v_str, const std::string &v) {
    std::vector<size_t> idx(_dat[v].size());
    std::iota(idx.begin(),idx.end(),0);
    if(_dat[v].type==DataType::Num) {
      std::sort(idx.begin(),idx.end(),
		[&](size_t j,size_t k){return _dat[v].num[j]<_dat[v].num[k];}
		);
    }
    if(_dat[v].type==DataType::Str) {
      std::sort(idx.begin(),idx.end(),
		[&](size_t j,size_t k){return _dat[v].str[j]<_dat[v].str[k];}
		);
    }
    thl::StrSplit sp(v_str,",");
    int quiet=1<<2;
    for(auto &&s : sp) {
      int ret=check_data2(v,s,quiet);
      if(ret > 0 && ret != 2) return 1;
    }    
    for(auto &&s : sp) {
      std::string s2=s+"_sort";
      if(_dat[s].type==DataType::Num) {
	_dat[s2].type=DataType::Num;
	_dat[s2].num.resize(idx.size());
	for(size_t j=0; j<idx.size(); j++) {
	  _dat[s2].num[j]=_dat[s].num[idx[j]];
	}
      }
      if(_dat[s].type==DataType::Str) {
	_dat[s2].type=DataType::Str;
	_dat[s2].str.resize(idx.size());
	for(size_t j=0; j<idx.size(); j++) {
	  _dat[s2].str[j]=_dat[s].str[idx[j]];
	}
      }
    }
    return 0;
  }
  std::vector<std::string> get_vlist(const std::string &pattern) {
    std::vector<std::string> vlist;
    thl::StrSplit sp(pattern,",");
    for(auto &&s : sp) {
      for(auto &&a : _dat) {
	if( fnmatch(s.c_str(),a.first.c_str(),0)==0 ) {
	  vlist.push_back(a.first);
	}
      }
    }
    return vlist;
  }
  void data_ls(const std::vector<std::string> vlist, Option &opt) {
    for(auto &&v : vlist) {
      if(_dat[v].type==DataType::Mesh) {
	printf("%s : data(mesh) : ",v.c_str());
	if(_dat[v].mesh.size() == 0) {
	  printf("no data\n");
	} else {
	  printf("size_x=%lu size_y=%lu\n",
		 _dat[v].mesh.size(),_dat[v].mesh[0].size());
	}
      } else {
	printf("%s : data(%s) : ",v.c_str(),_dat[v].type_name());
	if(_dat[v].size() == 0) {
	  printf("no data\n");
	} else {
	  printf("size=%lu\n",_dat[v].size());
	}
      }
    }
  }
  void data_show(const std::vector<std::string> vlist, Option &opt) {
    for(auto &&v : vlist) {
      int size = (int)_dat[v].size();
      int start = (opt.n0 > 0) ? opt.n0-1 : 0;
      int end = (0 < opt.n1 && opt.n1 < size) ? opt.n1 : size;
      if(_dat[v].type==DataType::Mesh) {
	if(size != 0) {
	  printf("%s : data(mesh) : \n",v.c_str());
	  for(int j=start; j<end; j++) {
	    for(size_t k=0; k<_dat[v].mesh[j].size(); k++) {
	      printf("%d %lu [%.11g]\n",j,k,_dat[v].mesh[j][k]);
	    }
	  }
	}
      } else {
	if(size != 0) {
	  printf("%s : data(%s) : ",v.c_str(),_dat[v].type_name());
	  if(opt.fs == "\n") printf("\n");
	  for(int j=start; j<end; j++) {
	    if(opt.fs == " \t\n") {
	      printf(" "); _dat[v].print(j);
	    } else {
	      printf("%s",(j==start) ? "" : opt.fs.c_str()); _dat[v].print(j);
	    }
	  }
	  printf("\n");
	}
      }
    }
  }
  void data_cat(const std::vector<std::string> vlist, const std::string &mode,
	       const std::string &vout,	Option &opt) {
    if(mode == ">") _dat[vout].clear();
    
    if(_dat[vlist[0]].type==DataType::Mesh) {
      printf("mesh type can not be concatenate.\n"); return;
    }
    _dat[vout].type = _dat[vlist[0]].type;
    for(auto &&v : vlist) {
      if(_dat[v].type != _dat[vout].type) {
	printf("incompatible type [%s]!=[%s] skipped.\n",
	       _dat[v].type_name(),_dat[vout].type_name());
	continue;
      }
      int end = (int)_dat[v].size();
      if(0<=opt.n1 && opt.n1<=end) {end=opt.n1;}
      if(_dat[vout].type==DataType::Str) {
	for(int k=0; k<end; k++) {
	  if(k < opt.n0) continue;
	  _dat[vout].str.push_back(_dat[v].str[k]);
	}
      } else {
	for(int k=0; k<end; k++) {
	  if(k < opt.n0) continue;
	  _dat[vout].num.push_back(_dat[v].num[k]);
	}
      }
    }
  }
  void data_rm(const std::vector<std::string> vlist) {
    for(auto &&v : vlist) _dat.erase(v);
  }
  void save_graph_range(void) {
    _gopt.att.x0 = _pl->att.x0;
    _gopt.att.x1 = _pl->att.x1;
    _gopt.att.y0 = _pl->att.y0;
    _gopt.att.y1 = _pl->att.y1;
    _gopt.att.z0 = _pl->att.z0;
    _gopt.att.z1 = _pl->att.z1;
    _gopt.att.logx = _pl->att.logx;
    _gopt.att.logy = _pl->att.logy;
  }
  void flush(void) {_pl->flush();}
  void auto_label(const std::string &vx, const std::string &vy, Option &opt) {
    if(_dat.count(vx)>0 && opt.att.xlab[0]==0) {
      opt.att.set_xlab(vx.c_str());
    }
    if(_dat.count(vy)>0 && opt.att.ylab[0]==0) {
      opt.att.set_ylab(vy.c_str());
    }
  }
  void auto_label3d(const std::string &vx, const std::string &vy,
		    const std::string &vz, Option &opt) {
    if(_dat.count(vx)>0 && opt.att.xlab[0]==0) {
      opt.att.set_xlab(vx.c_str());
    }
    if(_dat.count(vy)>0 && opt.att.ylab[0]==0) {
      opt.att.set_ylab(vy.c_str());
    }
    if(_dat.count(vz)>0 && opt.att.zlab[0]==0) {
      opt.att.set_zlab(vz.c_str());
    }
  }
  int data_plot(const std::string &v, Option &opt) {
    if(check_data1(v)) return 1;
    std::string vn = v + "_n";
    _dat[vn].type = DataType::Num;
    _dat[vn].num.resize(_dat[v].num.size());
    for(size_t j=0; j<_dat[v].num.size(); j++) _dat[vn].num[j]=j+1;
    data_plot(vn,v,opt);
    return 0;
  }
  int data_plot(std::string vx, std::string vy, Option &opt) {
    if(check_data2(vx,vy)) return 1;
    if(opt.cc.size()>0) {
      if(data_make_cut(vx+","+vy, opt.cc)!=0) return 1;
      vx = vx+"_cut";
      vy = vy+"_cut";
    }
    if(opt.mv > 1) {
      thl::CFormat fmt;
      data_make_mave(vy, opt.mv);
      vy = vy+"_m"+fmt("%d",opt.mv);
    }
    auto_label(vx,vy,opt);
    _pl->att = opt.att;
    if(!opt.rp) {
      _pl->att.box(opt.x0,opt.x1, opt.y0,opt.y1);
      _pl->auto_scale(_dat[vx].num,_dat[vy].num);
      _pl->draw_box(opt.bp,opt.cr);
      save_graph_range();
    }
    if(opt.gt == "bin1") {
      _pl->att.hsty=0;
      _pl->draw_bin(_dat[vx].num,_dat[vy].num);
    } else if(opt.gt == "bin2") {
      _pl->att.hsty=1;
      _pl->draw_bin(_dat[vx].num,_dat[vy].num);
    } else if(opt.gt == "slope") {
      _pl->draw_graph(_dat[vx].num,_dat[vy].num);
    }
    if(opt.fl) _pl->flush();
    return 0;
  }
  int data_plot3d(std::string vx, std::string vy, std::string vz, Option &opt) {
    if(check_data2(vx,vy)) return 1;
    if(check_data2(vx,vz)) return 1;
    if(opt.cc.size()>0) {
      if(data_make_cut(vx+","+vy+","+vz, opt.cc)!=0) return 1;
      vx = vx+"_cut";
      vy = vy+"_cut";
      vz = vz+"_cut";
    }
    auto_label3d(vx,vy,vz,opt);
    _pl->att = opt.att;
    if(!opt.rp) {
      _pl->att.box3d(opt.x0,opt.x1, opt.y0,opt.y1, opt.z0,opt.z1);
      _pl->auto_scale3d(_dat[vx].num, _dat[vy].num, _dat[vz].num);
      _pl->draw_box3d(opt.bp,opt.cr);
      save_graph_range();
    }
    _pl->draw_graph3d(_dat[vx].num, _dat[vy].num, _dat[vz].num);
    if(opt.fl) _pl->flush();
    return 0;
  }
  int data_xerr(const std::string &vx, const std::string &vy,
	       const std::string &ex, Option &opt) {
    if(check_data2(vx,vy)) return 1;
    if(check_data2(vx,ex)) return 1;
    _pl->att = opt.att;
    _pl->draw_error_x(_dat[vx].num,_dat[vy].num,_dat[ex].num);
    if(opt.fl) _pl->flush();
    return 0;
  }
  int data_yerr(const std::string &vx, const std::string &vy,
	       const std::string &ey, Option &opt) {
    if(check_data2(vx,vy)) return 1;
    if(check_data2(vx,ey)) return 1;
    _pl->att = opt.att;
    _pl->draw_error_y(_dat[vx].num,_dat[vy].num,_dat[ey].num);
    if(opt.fl) _pl->flush();
    return 0;
  }
  double get_freq_by_fft(const std::vector<double> &vecx,
			 const std::vector<double> &vecy) {
    double dt = vecx[1] - vecx[0];
    thl::FFT fft(vecy.size(),dt); fft.wid = fft.BH;
    for(size_t j=0; j<vecy.size(); j++) fft.set(j,vecy[j]);
    fft.calc();
    std::vector<double> x,y;
    double df = fft.df();
    for(size_t j=0; j<fft.size()/2; j++) {
      x.push_back(df*j);
      y.push_back(fft.amp_norm(j));
    }
    double ymax=y[1];
    size_t ipeak=1;
    for(size_t j=1; j<y.size();j++) {
      if(y[j]>ymax) {ymax=y[j]; ipeak=j;}
    }
    double thresh = y[ipeak]/4;
    double xysum=0,ysum=0;
    for(size_t j=ipeak-10; j<ipeak+10; j++) {
      if(j<1 || j>=y.size()-1) continue;
      if(y[j]>thresh && y[j]<=y[ipeak]) {
	xysum += x[j]*y[j]; ysum += y[j];
      }
    }
    //    printf("ipeak=%d x=%f xmean=%f\n",ipeak,x[ipeak],xysum/ysum);
    return xysum/ysum;
  }
  int data_fit(const std::string &vx, const std::string &vy,
	      const std::string &func, Option &opt) {
    if(check_data2(vx,vy)) return 1;
    _pl->att = opt.att;
    _pl->att.lwid=1; _pl->att.symb=0;
    std::vector<double> &vecx = _dat[vx].num;
    std::vector<double> &vecy = _dat[vy].num;
    thl::CFormat fmt;
    thl::LsFit fit;
    if(func=="l"||func=="lin") {
      fit.calc_lin(vecx,vecy,opt.fx0,opt.fx1);
      _pl->draw_graph(fit.fx(), fit.fy());
      fmt("@ Linear Fitting:\n y = c0 + c1*x \n"
	  " c0=%g\n c1=%g\n chi2/ndf= %.3g/%d"
	  ,fit(0), fit(1), fit.chisq(), fit.ndf());
    }
    if(func=="q"||func=="quad") {
      fit.calc_quad(vecx,vecy,opt.fx0,opt.fx1);
      _pl->draw_graph(fit.fx(), fit.fy());
      fmt("@ Quadratic Fitting:\n y = c0 + c1*x + c2*x^2 \n"
	  " c0=%g\n c1=%g\n c2= %g\n chi2/ndf= %.3g/%d"
	  ,fit(0), fit(1), fit(2), fit.chisq(), fit.ndf());
    }
    if(func=="g"||func=="gaus") {
      char c=' ';
      if(opt.fx0 == opt.fx1) {
	fit.calc_statistics(vecx,vecy);
	opt.fx0 = fit(1)-fit(2)*3;
	opt.fx1 = fit(1)+fit(2)*3; c = '*';
      }
      fit.calc_gaus(vecx,vecy,opt.fx0,opt.fx1);
      _pl->draw_graph(fit.fx(), fit.fy());
      fmt("@ Gaussian Fitting%c:\n y = c0*exp(-(x-c1)^2/2*c2^2) \n"
	  " c0:amp=%g\n c1:mean=%g\n c2:sgm=%g\n chi2/ndf= %.3g/%d"
	  ,c,fit(0), fit(1), fit(2), fit.chisq(), fit.ndf());
    }
    if(func=="e"||func=="exp") {
      fit.calc_exp(vecx,vecy,opt.fx0,opt.fx1);
      _pl->draw_graph(fit.fx(), fit.fy());
      fmt("@ Exponential Fitting:\n y = c0*exp(c1*x) \n"
	  " c0=%g\n c1=%g\n chi2/ndf= %.3g/%d"
	  ,fit(0), fit(1), fit.chisq(), fit.ndf());
    }
    if(func=="log") {
      fit.calc_log(vecx,vecy,opt.fx0,opt.fx1);
      _pl->draw_graph(fit.fx(), fit.fy());
      fmt("@ Logarithm Fitting:\n y = c0+log(c1+x) \n"
	  " c0=%g\n c1=%g\n chi2/ndf= %.3g/%d"
	  ,fit(0), fit(1), fit.chisq(), fit.ndf());
    }
    if(func=="s"||func=="sin"||func=="s2") {
      if(func=="s2") opt.fq = get_freq_by_fft(vecx,vecy);
      fit.calc_sin(vecx,vecy,opt.fq,opt.fx0,opt.fx1);
      _pl->draw_graph(fit.fx(), fit.fy());
      fmt("@ Sinusoidal Fitting:\n y = c0+c1*sin(2PI*c3*x)+c2*cos(2PI*c3*x)\n"
	  " c0=%g\n c1=%g\n c2=%g\n c3=%g\n chi2/ndf= %.3g/%d"
	  ,fit(0), fit(1), fit(2), fit(3), fit.chisq(), fit.ndf());
    }
    if(func=="c"||func=="circ") {
      fit.calc_circ(vecx,vecy);
      _pl->draw_circle(fit(0), fit(1), fit(2), 0);
      fmt("@ Circular Fitting:\n (x-c0)^2 + (y-c1)^2 = c2^2 \n"
	  " c0:dx=%g\n c1:dy=%g\n c2:r=%g\n chi2/ndf= %.3g/%d"
	  ,fit(0), fit(1), fit(2), fit.chisq(), fit.ndf());
    }
    printf("%s\n",fmt());  // print fitting info to the console
    if(opt.cx!=0 && opt.cy!=0) { // draw fitting info into the graph 
      _pl->draw_text(opt.cx, opt.cy, fmt(), opt.rc);
    }
    if(opt.cf.size() > 0) {
      for(size_t j=0; j<fit.dim(); j++) {
	var.set_num(opt.cf+fmt("%u",j), fit(j));
      }
    }
    if(opt.fl) _pl->flush();
    return 0;
  }
  int data_fit3d(const std::string &vx, const std::string &vy,
		const std::string &vz, const std::string &func, Option &opt) {
    if(check_data2(vx,vy)) return 1;
    if(check_data2(vx,vz)) return 1;
    _pl->att = opt.att;
    _pl->att.lwid=1; _pl->att.symb=0;
    thl::CFormat fmt;
    thl::LsFit fit;
    if(func=="p"||func=="plane") {
      fit.calc_plane(_dat[vx].num,_dat[vy].num,_dat[vz].num);
      size_t ngrid=21;
      double dx=(_pl->att.x1-_pl->att.x0)/(ngrid-1);
      double dy=(_pl->att.y1-_pl->att.y0)/(ngrid-1);
      std::vector<double> fx(2),fy(2),fz(2);
      for(size_t xy=0; xy<2; xy++) {
	for(size_t n=0; n<ngrid; n++) {
	  fx[0] = (xy) ? _pl->att.x0+dx*n : _pl->att.x0;
	  fx[1] = (xy) ? _pl->att.x0+dx*n : _pl->att.x1;
	  fy[0] = (xy) ? _pl->att.y0 : _pl->att.y0+dy*n;
	  fy[1] = (xy) ? _pl->att.y1 : _pl->att.y0+dy*n;
	  fz[0] = fit.func_plane(fx[0],fy[0]);
	  fz[1] = fit.func_plane(fx[1],fy[1]);
	  _pl->draw_graph3d(fx, fy, fz);
	}
      }
      fmt("@ Plane Fitting:\n z = c0+c1*x+c2*y\n"
	  " c0=%g\n c1=%g\n c2=%g\n chi2/ndf= %.3g/%d"
	  ,fit(0), fit(1), fit(2), fit.chisq(), fit.ndf());
    }
    printf("%s\n",fmt());  // print fitting info to the console
    if(opt.cx!=0 && opt.cy!=0) { // draw fitting info into the graph 
      _pl->draw_text(opt.cx, opt.cy, fmt(), opt.rc);
    }
    if(opt.cf.size() > 0) {
      for(size_t j=0; j<fit.dim(); j++) {
	var.set_num(opt.cf+fmt("%u",j), fit(j));
      }
    }
    if(opt.fl) _pl->flush();
    return 0;
  }
  int hist_plot(std::string v, Option &opt) {
    if(check_data1(v)) return 1;
    if(opt.cc.size()>0) {
      if(data_make_cut(v, opt.cc)!=0) return 1;
      v = v+"_cut";
    }
    if(opt.mv > 1) {
      thl::CFormat fmt;
      data_make_mave(v, opt.mv);
      v = v+"_m"+fmt("%d",opt.mv);
    }
    _pl->calc_scale(_dat[v].num, opt.x0, opt.x1, opt.att.ascx);
    auto_label(v," ",opt);
    _pl->att = opt.att;
    thl::Hist1D hist(opt.nb, opt.x0, opt.x1);
    for(auto x : _dat[v].num) {hist.fill(x);}
    if(hist.nentry()==0) {printf("no entry\n"); return 2;}
    std::string hx = v + "_hx";
    std::string hy = v + "_hy";
    _dat[hx].type = _dat[hy].type = DataType::Num;
    _dat[hx].num = std::vector<double>(opt.nb);
    _dat[hy].num = std::vector<double>(opt.nb);
    for(int j=0; j<opt.nb; j++) {
      _dat[hx].num[j] = hist.x(j);
      _dat[hy].num[j] = hist.y(j);
    }
    if(!opt.rp) {
      _pl->att.box(opt.x0,opt.x1, opt.y0,opt.y1);
      _pl->auto_scale(_dat[hx].num, _dat[hy].num);
      _pl->draw_box(opt.bp);
      save_graph_range();
    }
    if(opt.ht == "bin1") {
      _pl->att.hsty=0;
      _pl->draw_bin(_dat[hx].num,_dat[hy].num);
    } else if(opt.ht == "bin2") {
      _pl->att.hsty=1;
      _pl->draw_bin(_dat[hx].num,_dat[hy].num);
    } else if(opt.ht == "slope") {
      _pl->draw_graph(_dat[hx].num,_dat[hy].num);
    }
    if(opt.fl) _pl->flush();
    return 0;
  }
  int hist_fit(const std::string &v, const std::string &func, Option &opt) {
    std::string hx = v + "_hx";
    std::string hy = v + "_hy";
    data_fit(hx, hy, func, opt);
    return 0;
  }
  int hist2d_plot(std::string vx, std::string vy,  Option &opt) {
    if(check_data2(vx,vy)) return 1;
    if(opt.cc.size()>0) {
      if(data_make_cut(vx+","+vy, opt.cc)!=0) return 1;
      vx = vx+"_cut";
      vy = vy+"_cut";
    }
    _pl->calc_scale(_dat[vx].num, opt.x0, opt.x1, opt.att.ascx);
    _pl->calc_scale(_dat[vy].num, opt.y0, opt.y1, opt.att.ascy);
    auto_label(vx,vy,opt);
    _pl->att = opt.att;

    thl::Hist2D h2(opt.nx, opt.ny, opt.x0, opt.x1, opt.y0, opt.y1);
    for(size_t j=0; j<_dat[vx].num.size(); j++) {
      h2.fill(_dat[vx].num[j],_dat[vy].num[j]);
    }
    if(h2.nentry()==0) {printf("no entry\n"); return 2;}

    std::string mx = vx + "_mx"; _dat[mx].clear();
    std::string my = vy + "_my"; _dat[my].clear();
    std::string mz = vx+"_"+vy+"_mz"; _dat[mz].clear();
    if(opt.ht=="bin1" || opt.ht=="bin2") {
      Option opt2 = opt;
      opt2.nx = opt.nx*2+2;
      opt2.ny = opt.ny*2+2;
      _dat[mx].num.resize(opt2.nx); _dat[mx].type=DataType::Num;
      _dat[my].num.resize(opt2.ny); _dat[my].type=DataType::Num;
      _dat[mz].mesh.resize(opt2.nx); _dat[mz].type=DataType::Mesh;
      for(int j=0; j<opt2.nx; j++) {_dat[mz].mesh[j].resize(opt2.ny);}
      
      double xwid=h2.xwid()/2;
      double ywid=h2.ywid()/2;
      _dat[mx].num[0]=h2.x(0)-xwid;
      _dat[mx].num[opt.nx*2+1]=h2.x(opt.nx-1)+xwid*1.01;
      for(int j=0; j<opt.nx; j++) {
	_dat[mx].num[j*2+1] = h2.x(j) - xwid*0.99;
	_dat[mx].num[j*2+2] = h2.x(j) + xwid;
      }
      _dat[my].num[0]=h2.y(0)-ywid;
      _dat[my].num[opt.ny*2+1]=h2.y(opt.ny-1)+ywid*1.01;
      for(int j=0; j<opt.ny; j++) {
	_dat[my].num[j*2+1] = h2.y(j) - ywid*0.99;
	_dat[my].num[j*2+2] = h2.y(j) + ywid;
      }
      _dat[mz].mesh[0][0]=0;
      _dat[mz].mesh[0][opt.ny*2+1]=0;
      for(int j=0; j<opt.nx; j++) {
	_dat[mz].mesh[j*2+1][0]=0;
	_dat[mz].mesh[j*2+2][0]=0;
	_dat[mz].mesh[j*2+1][opt.ny*2+1]=0;
	_dat[mz].mesh[j*2+2][opt.ny*2+1]=0;
	for(int k=0; k<opt.ny; k++) {
	     _dat[mz].mesh[j*2+1][k*2+1]
	    =_dat[mz].mesh[j*2+1][k*2+2] = (double)h2.z(j,k);
	     _dat[mz].mesh[j*2+2][k*2+1]
	    =_dat[mz].mesh[j*2+2][k*2+2] = (double)h2.z(j,k);
	}
      }
      mesh_plot(mx,my,mz,opt2);
    } else {
      _dat[mx].num.resize(opt.nx); _dat[mx].type=DataType::Num;
      _dat[my].num.resize(opt.ny); _dat[my].type=DataType::Num;
      for(int j=0; j<opt.nx; j++) {_dat[mx].num[j]=h2.x(j);}
      for(int j=0; j<opt.ny; j++) {_dat[my].num[j]=h2.y(j);}
      _dat[mz].mesh.resize(opt.nx); _dat[mz].type=DataType::Mesh;
      for(int j=0; j<opt.nx; j++) {
	_dat[mz].mesh[j].resize(opt.ny);
	for(int k=0; k<opt.ny; k++) {
	  double z = h2.z(j,k);
	  _dat[mz].mesh[j][k] = z;
	}
      }
      mesh_plot(mx,my,mz,opt);
    }
    if(opt.fl) _pl->flush();
    return 0;
  }
  int fft_plot(const std::string &vx, const std::string &vy, Option &opt) {
    if(check_data2(vx,vy)) return 1;
    opt.dt = _dat[vx].num[1]-_dat[vx].num[0]; // estimate the time-tick
    fft_plot(vy,opt);
    return 0;
  }
  int fft_plot(std::string v, Option &opt) {
    if(check_data1(v)) return 1;
    if(opt.cc.size()>0) {
      if(data_make_cut(v, opt.cc)!=0) return 1;
      v = v+"_cut";
    }
    auto_label(v," ",opt);
    _pl->att = opt.att;
    thl::FFT fft(_dat[v].num.size(),opt.dt);
    if(opt.fw=="rc") fft.wid = fft.Rectangle;
    if(opt.fw=="hn") fft.wid = fft.Hann;
    if(opt.fw=="hm") fft.wid = fft.Hamming;
    if(opt.fw=="bk") fft.wid = fft.Blackman;
    if(opt.fw=="bh") fft.wid = fft.BH;
    for(size_t j=0; j<_dat[v].num.size(); j++) {
      fft.set(j,_dat[v].num[j]);
    }
    fft.calc();
    std::string fx = v + "_fx";
    std::string fy = v + "_fy";
    _dat[fx].type = DataType::Num;
    _dat[fy].type = DataType::Num;
    _dat[fx].num=std::vector<double>(fft.size()/2);
    _dat[fy].num=std::vector<double>(fft.size()/2);

    double df = fft.df();
    for(size_t j=0; j<fft.size()/2; j++) {
      _dat[fx].num[j] = df*j;
      _dat[fy].num[j] = fft.amp_norm(j);
    }
    if(!opt.rp) {
      _pl->att.box(opt.x0,opt.x1, opt.y0,opt.y1);
      _pl->auto_scale(_dat[fx].num,_dat[fy].num);
      _pl->att.y0 = (_pl->att.y0<=0) ? _pl->att.y1*1e-5 : _pl->att.y0;
      _pl->draw_box(opt.bp);
      save_graph_range();
    }
    _pl->draw_graph(_dat[fx].num, _dat[fy].num);
    if(opt.fl) _pl->flush();
    return 0;
  }
  int fft_fit(const std::string &v, const std::string &func, Option &opt) {
    std::string fx = v + "_fx";
    std::string fy = v + "_fy";
    data_fit(fx, fy, func, opt);
    return 0;
  }
  int mesh_set_list(const std::string &v, const std::string &expr) {
    thl::Bracket bc('{','}',expr); if(bc.size()<1) return 1;
    _dat[v].clear();
    thl::Bracket bc2('{','}',bc.contents(0));
    _dat[v].type=DataType::Mesh;
    _dat[v].mesh.resize(bc2.size());
    for(size_t j=0; j<bc2.size(); j++) {
      thl::StrSplit sp(bc2.contents(j),",");
      _dat[v].mesh[j].resize(sp.size());
      for(size_t k=0; k<sp.size(); k++) {
	DataType type;
	_dat[v].mesh[j][k] = str_to_val(sp(k),type);
      }
    }
    return 0;
  }
  int mesh_set_eval(const std::string &v, const std::string &expr) {
    _dat[v].clear();
    thl::Calc calc;
    std::vector<std::string> tags;
    find_tags(tags,expr);
    if(tags.size()!=2) {
      printf("number of variables should be 2 [%s]\n",expr.c_str());
      return 1;
    } else {
      std::string vx = tags[0];
      std::string vy = tags[1];
      if(check_data1(vx)) return 1;
      if(check_data1(vy)) return 1;
      size_t nx = _dat[vx].num.size();
      size_t ny = _dat[vy].num.size();
      _dat[v].mesh.resize(nx);
      for(size_t j=0; j<nx; j++) {
	_dat[v].mesh[j].resize(ny);
	for(size_t k=0; k<ny; k++) {
	  calc.set_var_num(vx,_dat[vx].num[j]);
	  calc.set_var_num(vy,_dat[vy].num[k]);
	  double z = calc.eval(expr);
	  _dat[v].mesh[j][k]=z;
	}
      }
      _dat[v].type=DataType::Mesh;
      return 0;
    }
  }
  int mesh_read(const std::string &v_str, const std::string &fname,
		Option &opt) {
    thl::StrSplit v(v_str,",");
    if(v.size() !=3 ) {
      printf("argument should have 3 variables like x,y,z\n");
      return 1;
    }
    std::string vx=v(0); _dat[vx].type=DataType::Num; _dat[vx].clear();
    std::string vy=v(1); _dat[vy].type=DataType::Num; _dat[vy].clear(); 
    std::string vz=v(2); _dat[vz].type=DataType::Mesh; _dat[vz].clear();
    std::ifstream ifs(fname.c_str());
    if(!ifs) {printf("can't open %s\n",fname.c_str()); return 1;}
    thl::StrSplit sp;
    opt.ny=0;
    double yy=0;
    while(sp.getline(ifs,opt.fs)) {
      if(sp.size()==0) {_dat[vy].num.push_back(yy); opt.ny++; continue;}
      if(sp(0,0)=='#') continue;
      yy = sp.stof(1);
      if(opt.ny==0) _dat[vx].num.push_back(sp.stof(0));
    }
    opt.nx = _dat[vx].num.size();
    printf("nx=%d ny=%d\n",opt.nx,opt.ny);
    ifs.clear(); ifs.seekg(0,std::ios_base::beg);
    _dat[vz].mesh.resize(opt.nx);
    for(int j=0; j<opt.nx; j++) _dat[vz].mesh[j].resize(opt.ny);
    size_t ix=0,iy=0;
    opt.z0=1e20; opt.z1=0;
    while(sp.getline(ifs,opt.fs)) {
      if(sp.size()==0) {iy++; ix=0; continue;}
      if(sp(0,0)=='#') continue;
      double z = sp.stof(2);
      _dat[vz].mesh[ix][iy]=z;
      if(z <= opt.z0) opt.z0=z;
      if(z >= opt.z1) opt.z1=z;
      ix++;
    }
    return 0;
  }
  int check_mesh_data(const std::string &vx, const std::string &vy,
		      const std::string &vz) {
    if(_dat[vx].type == DataType::Mesh) {
      printf("%s should not be mesh data\n",vx.c_str()); return 1;
    }
    if(_dat[vy].type == DataType::Mesh) {
      printf("%s should not be mesh data\n",vy.c_str()); return 1;
    }
    if(_dat[vz].type != DataType::Mesh) {
      printf("%s should be mesh data\n",vz.c_str()); return 1;
    }
    if(_dat[vx].num.size() != _dat[vz].mesh.size()) {
      printf("%s size != %s x-size\n",vx.c_str(),vz.c_str()); return 1;
    }
    if(_dat[vy].num.size() != _dat[vz].mesh[0].size()) {
      printf("%s size != %s y-size\n",vy.c_str(),vz.c_str()); return 1;
    }
    return 0;
  }
  int mesh_write(const std::string &v_str, const std::string &fname,
		 Option &opt) {
    thl::StrSplit v(v_str,",");
    if(v.size() !=3 ) {
      printf("argument should have 3 variables like x,y,z\n");
      return 1;
    }
    std::string vx=v(0),vy=v(1),vz=v(2);
    if(check_mesh_data(vx,vy,vz)) return 1;
    std::ofstream ofs(fname.c_str());
    if(ofs) {
      const char *fs = (opt.fs==" \t\n") ? " " : opt.fs.c_str();
      size_t nx=_dat[vx].num.size();
      size_t ny=_dat[vy].num.size();
      thl::CFormat fmt;
      for(size_t k=0; k < ny; k++) {
	for(size_t j=0; j < nx; j++) {
	  ofs << fmt("%e%s %e%s %e\n",
		     _dat[vx].num[j],fs,
		     _dat[vy].num[k],fs,
		     _dat[vz].mesh[j][k]);
	}
	ofs << std::endl;
      }
    } else {
      printf("can't open %s\n",fname.c_str());
      return 1;
    }
    return 0;
  }
  int mesh_plot(const std::string &vx, const std::string &vy,
		const std::string &vz, Option &opt) {
    if(check_mesh_data(vx,vy,vz)) return 1;
    size_t nx=_dat[vx].num.size();
    size_t ny=_dat[vy].num.size();
    _pl->alloc_mesh(nx, ny);
    opt.z0=1e20; opt.z1=0;
    for(size_t j=0; j<nx; j++) {
      for(size_t k=0; k<ny; k++) {
	double z = _dat[vz].mesh[j][k];
	_pl->set_mesh(j,k, z);
	if(z <= opt.z0) opt.z0=z;
	if(z >= opt.z1) opt.z1=z;
      }
    }
    auto_label3d(vx,vy,vz,opt);
    _pl->att = opt.att;
    if(opt.mt=="mesh1"||opt.mt=="mesh2") {
      if(!opt.rp) {
	_pl->att.box3d(opt.x0,opt.x1, opt.y0,opt.y1, opt.z0, opt.z1);
	_pl->auto_scale(_dat[vx].num,_dat[vy].num);
	_pl->draw_box3d(opt.bp,opt.cr);
	save_graph_range();
      }
      bool color = (opt.mt=="mesh2") ? 1 : 0;
      _pl->draw_mesh(_dat[vx].num,_dat[vy].num, color);
    } else if(opt.mt=="cont1"||opt.mt=="cont2") {
      _pl->att.z0=opt.z0; _pl->att.z1=opt.z1;
      if(!opt.rp) {
	_pl->att.box(opt.x0,opt.x1, opt.y0,opt.y1);
	_pl->auto_scale(_dat[vx].num,_dat[vy].num);
	_pl->set_frame(opt.bp,opt.cr);
	save_graph_range();
      }
      bool color = (opt.mt=="cont2") ? 1 : 0;
      _pl->draw_contour(_dat[vx].num,_dat[vy].num, color);
    }
    if(opt.fl) _pl->flush();
    _pl->free_mesh(nx, ny);
    return 0;
  }
  int data_statistics(const std::string &v, Option &opt, bool print_flag=1) {
    if(check_data1(v)) return 1;
    double max=_dat[v].num[0], min=_dat[v].num[0];
    double nentry=0, sum=0, ssum=0;
    for(auto x : _dat[v].num) {
      if(x >= DBL_MAX || x <= -DBL_MAX) continue;
      if(! std::isfinite(x)) continue;
      nentry++;
      if(x > max) max = x;
      if(x < min) min = x;
      sum += x;
      ssum += x*x;
    }
    double mean = (nentry > 0) ? sum/nentry : 0;
    double rms = (nentry > 0) ? ssum/nentry - mean*mean : 0;
    rms = (rms > 0) ? std::sqrt(rms) : 0;
    var.set_num(v+"_entry",nentry);
    var.set_num(v+"_max",max);
    var.set_num(v+"_min",min);
    var.set_num(v+"_mean",mean);
    var.set_num(v+"_rms",rms);
    if(print_flag) {
      _pl->att = opt.att;
      thl::CFormat fmt;
      fmt("@ Statistics:\n"
	  " entry=%g\n max= %g\n min= %g\n mean= %g\n rms= %g",
	  nentry,max,min,mean,rms);
      printf("%s\n",fmt());  // print info to the console
      if(opt.cx!=0 && opt.cy!=0) { // draw info into the graph 
	_pl->draw_text(opt.cx, opt.cy, fmt(), opt.rc);
	if(opt.fl) _pl->flush();
      }
    }
    return 0;
  }
  int draw_fill_area(const std::string &vx, const std::string &vy,
		     Option &opt) {
    if(check_data2(vx,vy)) return 0;
    _pl->att = opt.att;
    if(!opt.rp) {
      _pl->att.box(opt.x0,opt.x1, opt.y0,opt.y1);
      _pl->auto_scale(_dat[vx].num,_dat[vy].num);
      _pl->draw_box(opt.bp,opt.cr);
      save_graph_range();
    }
    _pl->fill_area(_dat[vx].num,_dat[vy].num);
    if(opt.fl) _pl->flush();
    return 0;
  }
#if USE_EPICS_CA
  void epics_ca_setval(thl::EpicsCA &ca, std::string tag) {
    _dat[tag].clear();
    if(ca.dbr_type()==DBR_STRING) {
      _dat[tag].type=DataType::Str;
      _dat[tag].str.push_back(ca.val_string());
      var.set_str(tag,ca.val_string());
    } else {
      _dat[tag].type=DataType::Num;
      for(int j=0; j<ca.n_elems(); j++) {
	_dat[tag].num.push_back((double)ca.val(j));
      }
      var.set_num(tag,(double)ca.val(0));
    }
    //    var.set_num(tag+".size",ca.n_elems());
  }
  void epics_ca_get(std::string rec, std::string tag) {
    thl::EpicsCA ca(rec.c_str());
    ca.get();   
    if(tag.size()==0) {
      ca.print_val();
    } else {
      epics_ca_setval(ca,tag);
    }
  }
  void epics_ca_put(std::string rec, std::string tag) {
    thl::EpicsCA ca(rec.c_str());
    thl::CFormat fmt;
    if(_dat.count(tag)==0) {
      std::string expr=thl::trim(tag);
      thl::Calc calc;
      double x = calc.eval(expr);
      if(calc.not_digit()) {
	fmt("%s",expr.c_str());
      } else {
	fmt("%.11g",x);
      }
      ca.set_val_by_string(0,fmt());
    } else {
      if(_dat[tag].type==DataType::Str) {
	ca.set_val_by_string(0,_dat[tag].str[0].c_str());
      } else {
	for(size_t j=0; j<_dat[tag].size(); j++) {
	  if(j<(size_t)ca.n_elems()) {
	    ca.set_val_by_string(j,fmt("%.11g",_dat[tag].num[j]));
	  }
	}
      }
    }
    ca.put();
  }
  void epics_ca_mon(std::string rec, std::string tag) {
    if(!_ca[tag].is_connected()) {
      _ca[tag].connect(rec.c_str(),"md");
    }
  }
  void epics_ca_check(std::string tags) {
    thl::StrSplit sp(tags,",");
    ca_poll();
    usleep(1000);
    for(auto &&tag : sp) {
      if(_ca[tag].is_connected()) {
	if(_ca[tag].mon_flag()) {
	  epics_ca_setval(_ca[tag],tag);
	  var.set_num(tag+".update",1);
	  _ca[tag].reset_mon_flag();
	} else {
	  var.set_num(tag+".update",0);
	}
      } else {
	printf("data '%s' is not related to EPICS_record\n",tags.c_str());
      }
    }
  }
  void epics_ca_close(std::string tags) {
    thl::StrSplit sp(tags,",");
    for(auto &&tag : sp) {
      if(_ca[tag].is_connected()) {
	_ca[tag].disconnect();
      }
    }
  }
#endif  
  int add_commands(std::string buf) {// called in MacroTool::parse_vbuf()
    thl::StrSplit args;
    args.set_quot_to_skip_split('"');
    args.split(buf);
    if(args(0)=="help") { // help
      const char *help =
	"list of commands:\n"
	" arc   : draw a circle in 2D-graph\n"
	" box   : draw the axis of 2D-graph in the box shape\n"
	" box3  : draw the axes of 3D-graph\n"
	" cat   : show data contents / concatenate data\n"
	" cut   : set cut condition\n"
	" div   : divide the drawing area\n"
	" elem  : copy data element to macro variable\n"
	" exe   : execute macro file\n"
	" fbox  : draw a filled pattern box in 2D-graph\n"
	" ffit  : fit the frequency domain graph\n"
	" fit   : fit the data in 2D-graph\n"
	" fit3  : fit the data in 3D-graph\n"
	" fill  : draw a filled pattern object in 2D-graph\n"
	" font  : set text font\n"
	" fplot : plot the frequency domain graph from the data\n"
	" help  : show help message\n"
	" hfit  : fit the histogram\n"
	" hplot : plot the histogram from the data\n"
	" hplot2: plot the 2D-histogram from the couple of data\n"
	" line  : draw a line in 2D-graph\n"
	" ls    : list macro/data variables\n"
	" mplot : plot mesh-graph(3D) or contour-graph(2D)\n"
	" mread : read the mesh data from the file\n"
	" mset  : set mesh data\n"
	" mwrite: write the mesh data to the file\n"
	" opt   : set/show global options\n"
	" plot  : plot the data in the 2D-graph\n"
	" plot3 : plot the data in the 3D-graph\n"
	" read  : read the data from the file\n"
	" rm    : remove macro/data variables\n"
	" set   : set the data\n"
	" sort  : sort the data in ascending order\n"
	" stat  : calc statistics from the data\n"
	" symb  : draw a symbol in 2D-graph\n"
	" text  : draw a text in 2D-graph\n"
	" title : set the graph title\n"
	" tfmt  : set the x-axis time format\n"
	" viewport : set drawing area in the window (abbr. vp)\n"
	" write : write the data to the file\n"
	" xerr  : plot the x-error-bars in 2D-graph\n"
	" xlab  : set the x-axis label\n"
	" yerr  : plot the y-error-bars in 2D-graph\n"
	" ylab  : set the y-axis label\n"
	" zlab  : set the z-axis label in 3D-graph\n"
	" def   : set default arguments of macro file\n"
#if USE_EPICS_CA
	"EPICS CA commands:\n"	
	" cainfo : show information of record\n"
	" caget  : get value of record\n"
	" caput  : put value of record\n"
	" camon  : open monitored record\n"
	" cacheck: check if monitored record is updated\n"
	" caclose: close monitored record\n"
#endif
	;
      printf("%s",help);
      print_help(); // help of MacroTool
      printf("\n without arguments, you get usage of the above commands\n");
      return 0;
    }
    if(args(0)=="opt") {
      if(args.size() < 2) {
	printf("usage: opt (item1:value1 item2:value2 ...)\n"
	       "     : opt item1 item2 ...\n"
	       "     : opt color|line|symbol|fill|reset\n"
	       "set or show the global options\n"
	       " if items are in the bracket (), the item values are set\n"
	       " if not in (), the item values are shown\n"
	       " if item is '*', all of the item names and values are shown\n"
	       " others,\n"
	       "  color(c)  : show list of the color names\n"
	       "  line(l)   : show list of the line-style names\n"
	       "  symbol(s) : show list of the symbol names\n"
	       "  fill(f)   : show list of the fill-area-style names\n"
	       "  reset     : set the default value for all items\n"
	       ); return 0;
      }
      if(args(1,0)=='(') {
	_gopt = get_opt(buf);
      } else if(args(1)=="reset") {
	_gopt = Option(); // init global options as default values
	var.reset_fmt(); // set macro variable output format "%.11g"
      } else {
	for(size_t j=1; j<args.size(); j++) {
	  _gopt.print(args(j));
	}
      }
      return 0;
    }
    if(args(0)=="div") {
      if(args.size() < 3) {
	printf("usage: div nx ny [(bo:0|1)]\n"
	       "divide graph area by horizontal(nx) and vertical(ny)\n"
	       "option:\n"
	       " bo:0  : horizontal box ordered (default)\n"
	       " bo:1  : vertical box ordered\n"
	       ); return 0;
      }
      _gopt=get_opt(buf);
      _pl->divide(args.stoi(1),args.stoi(2)); return 0;
    }
    if(args(0)=="tfmt") {
      if(args.size() < 2) {
	printf("usage: tfmt \"time format\"\n"
	       "       tfmt reset\n"
	       " set x-axis time format.\n"
	       " equivalent to 'opt (tf:\"time format\")'\n"
	       " tags in the format:\n"
	       "         %s, %s, %s, %s, %s, %s\n"
	       " reset : x-axis is reset to normal format.\n ",
	       "%Y(year)","%m(month)","%d(day)",
	       "%H(hour)","%M(min)","%S(sec)"
	       ); return 0;
      }
      _gopt = get_opt(buf);
      if(args(1)=="reset") {_gopt.att.time_xaxis = 0; return 0;}
      std::string tfmt=thl::trim(args(1));
      if(tfmt.size()) {
	_gopt.att.set_time_fmt(tfmt.c_str());
	_gopt.att.time_xaxis = 1;
      } else {
	_gopt.att.time_xaxis = 0;
      }
      return 0;
    }
    if(args(0)=="title") {
      if(args.size() < 2) {
	printf("usage: title \"strings\"\n"
	       " set graph top label\n"
	       " equivalent to 'opt (tl:\"strings\")'\n"
	       ); return 0;
      }
      _gopt.att.set_title(thl::trim(args(1)).c_str());
      return 0;
    }
    if(args(0)=="xlab") {
      if(args.size() < 2) {
	printf("usage: xlab \"strings\"\n"
	       " set x-axis label\n"
	       " equivalent to 'opt (xl:\"strings\")'\n"
	       ); return 0;
      }
      _gopt.att.set_xlab(thl::trim(args(1)).c_str());
      return 0;
    }
    if(args(0)=="ylab") {
      if(args.size() < 2) {
	printf("usage: ylab \"strings\"\n"
	       " set y-axis label\n"
	       " equivalent to 'opt (yl:\"strings\")'\n"
	       ); return 0;
      }
      _gopt.att.set_ylab(thl::trim(args(1)).c_str());
      return 0;
    }
    if(args(0)=="zlab") {
      if(args.size() < 2) {
	printf("usage: zlab \"strings\"\n"
	       " set z-axis label\n"
	       " equivalent to 'opt (zl:\"strings\")'\n"
	       ); return 0;
      }
      _gopt.att.set_zlab(thl::trim(args(1)).c_str());
      return 0;
    }
    if(args(0)=="box") {
      if(args.size() < 5) {
	printf("usage: box x0 x1 y0 y1 [(opt)]\n"); return 0;
      }
      Option opt=get_opt(buf);
      double x0=args.stof(1),x1=args.stof(2);
      double y0=args.stof(3),y1=args.stof(4);
      _pl->att=opt.att;
      _pl->att.box(x0,x1,y0,y1);
      if(opt.att.lwid==0) {
	_pl->set_frame(opt.bp,opt.cr);
      } else {
	_pl->draw_box(opt.bp,opt.cr);
      }
      save_graph_range();
      if(opt.fl) _pl->flush();
      return 0;
    }
    if(args(0)=="box3") {
      if(args.size() < 7) {
	printf("usage: box3 x0 x1 y0 y1 z0 z1 [(opt)]\n"); return 0;
      }
      Option opt=get_opt(buf);
      double x0=args.stof(1),x1=args.stof(2);
      double y0=args.stof(3),y1=args.stof(4);
      double z0=args.stof(5),z1=args.stof(6);
      _pl->att=opt.att;
      _pl->att.box3d(x0,x1,y0,y1,z0,z1);
      _pl->draw_box3d(opt.bp,opt.cr);
      save_graph_range();
      if(opt.fl) _pl->flush();
      return 0;
    }
    if(args(0)=="fill") {
      if(args.size() < 3) {
	printf("usage: fill vx vy [(opt)]\n"
	       " fill a color or pattern in the area which is specified\n"
	       " by the data vx and vy.\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      draw_fill_area(args(1),args(2),opt);
      return 0;
    }
    if(args(0)=="fbox") {
      if(args.size() < 3) {
	printf("usage: fbox x0 x1 y0 y1 [(opt)]\n"
	       " draw filled box.\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      double x0=args.stof(1),x1=args.stof(2);
      double y0=args.stof(3),y1=args.stof(4);
      _pl->att = opt.att;
      _pl->fill_box(x0,x1,y0,y1, opt.rc);
      if(opt.fl) _pl->flush();
      return 0;
    }
    if(args(0)=="line") {
      if(args.size() < 5) {
	printf("usage: line x0 x1 y0 y1 [(opt)]\n"); return 0;
      }
      Option opt=get_opt(buf);
      double x0=args.stof(1),x1=args.stof(2);
      double y0=args.stof(3),y1=args.stof(4);
      _pl->att=opt.att;
      _pl->draw_line(x0,x1,y0,y1, opt.rc);
      if(opt.fl) _pl->flush();
      return 0;
    }
    if(args(0)=="arc") {
      if(args.size() < 4) {
	printf("usage: arc x y r [(opt)]\n"); return 0;
      }
      Option opt=get_opt(buf);
      double x=args.stof(1),y=args.stof(2),r=args.stof(3);
      _pl->att=opt.att;
      _pl->draw_circle(x,y,r, opt.rc);
      if(opt.fl) _pl->flush();
      return 0;
    }
    if(args(0)=="text") {
      if(args.size() < 4) {
	printf("usage: text x y \"strings\" [(opt)]\n"
	       "escape sequences in the text strings:\n"
	       " #u  : switch to the superscript (ended with #d)\n"
	       " #d  : switch to the subscript (ended with #u)\n"
	       " #g  : next one character become Greek\n"
	       " #fn : switch to normal (sans-serif) font\n"
	       " #fr : switch to Roman (serif) font\n"
	       " #fi : switch to Italic font\n"
	       );
	return 0;
      }
      Option opt=get_opt(buf);
      double x=args.stof(1),y=args.stof(2);
      _pl->att=opt.att;
      std::string s=thl::trim(args(3));
      replace_esc(s);
      _pl->draw_text(x,y, s.c_str(), opt.rc);
      if(opt.fl) _pl->flush();
      return 0;
    }
    if(args(0)=="symb") {
      if(args.size() < 3) {
	printf("usage: symb x y [(opt)]\n"); return 0;
      }
      Option opt=get_opt(buf);
      double x=args.stof(1),y=args.stof(2);
      _pl->att=opt.att;
      _pl->draw_symbol(x,y, opt.rc);
      if(opt.fl) _pl->flush();
      return 0;
    }
    if(args(0)=="seed") {
      if(args.size() < 3) {
	printf("usage: seed N|utime|clock\n"
	       "  N     : set random seed N (an integer number).\n"
	       "  utime : set seed by unix time (sec).\n"
	       "  clock : set seed by clock (usec) (this is default).\n"
	       " equivalent to 'opt (sd:N)'\n"
	       ); return 0;
      }
      _gopt.sd = args(1);
    }
    if(args(0)=="set") {
      thl::StrSplit sp(buf,"= ");
      if(sp.size() < 3) {
	printf("usage: set v = {x0,x1,x2,...}\n"
	       "       set v = range(N,x0,x1)\n"
	       "       set v = random(N,uni|gaus|exp[,params...]) [(opt)]\n"
	       "       set v = time(t[,unit]) \n"
	       "       set v = expression\n"
	       " set the data v by some expressions.\n"
	       " see 'range', 'random', 'time' for more information.\n"
	       ); return 0;
      }
      std::string tag = sp(1);
      std::string expr = buf.substr(sp.index(2));
      if(expr.find("{") == 0) {
	data_set_list(tag,buf);
      } else if(expr.find("range(") == 0) {
	data_set_range(tag,buf);
      } else if(expr.find("random(") == 0) {
	Option opt=get_opt(buf);
	data_set_random(tag,buf,opt);
      } else if(expr.find("time(") == 0) {
	Option opt=get_opt(buf);
	data_set_time(tag,buf,opt);
      } else {
	data_set_eval(tag,expr);
      }
      return 0;
    }
    if(args(0)=="range") {
      printf("usage: set v = range(N,x0,x1)\n"
	     "  set N-size data starting from x0 and ending at x1.\n"
	     "  data elements interval dx = (x1-x0)/(N-1)\n"
	     "  ex.) range(5,0,2) set the data {0, 0.5, 1, 1.5, 2}.\n" 
	     ); return 0;
    }
    if(args(0)=="random") {
      printf("usage: set v = random(N,uni[,x0,x1]) [(opt)]\n"
	     "       set v = random(N,gaus[,sgm,mean]) [(opt)]\n"
	     "       set v = random(N,exp[,tau]) [(opt)]\n"
	     " set N-size data with random numbers.\n"
	     "  uni,x0,x1 : uniform distribution [x0:x1] (default x0=0,x1=1)\n"
	     "  gaus,sgm,mean : gauss distribution (default sgm=1,mean=0)\n"
	     "  exp,tau   : exponential distribution (default tau=1)\n"
	     " option:\n"
	     "  sd:n   : set integer value n as random seed\n"
	     "  sd:utime : set unix time(sec) as random seed\n"
	     "  sd:clock : set clock(nsec) as random seed (this is default)\n"
	     ); return 0;
    }
    if(args(0)=="time") {
      printf("usage: set vn = time([vn|vs][,unit])\n"
	     "usage: set vs = time([vn|vs],str)\n"
	     " convert the time data\n"
	     " vs is the string data of ISO time-format.\n"
	     " vn is numerical data of unix-epoch time.\n"
	     " if 1st argument is \"now\" it returns the current local time\n"
	     " unit:\n"
	     "   utime : return unix-epoch time in usec precision (UTC)\n"
	     "   year  : return years with decimal (local time)\n"
	     "   mon   : return months with decimal (local time)\n"
	     "   day   : return days with decimal (local time)\n"
	     "   hour  : return hours with decimal (local time)\n"
	     "   min   : return minutes with decimal (local time)\n"
	     "   sec   : return seconds with decimal (local time)\n"
	     "   usec  : return micro-seconds\n"
	     "   str   : return ISO time format string (local time)\n"
	     "                  like \"Year-Mon-Day Hour:Min:Sec[.Usec]\"\n"
	     " if unit is not specified, it returns unix-epoch time.\n"
	     ); return 0;
    }
    if(args(0)=="read") {
      if(args.size() < 3) {
	printf("usage: read v1,v2,... file_name [(opt)]\n"
	       "       read v1,v2,... `command` [(opt)]\n"
	       " where v1,v2,... are list of data to read\n"
	       " if `command` specified instead of file_name,\n"
	       " data are read from the out put of the system command\n"
	       ); return 0;
      }
      thl::Bracket bc('`','`',buf);
      Option opt=get_opt(buf);
      if(bc.size()) {
	thl::CFormat tmpfile,fmt;
	tmpfile("/tmp/tip.%d",getpid());
	system(fmt("%s > %s",bc.contents(0).c_str(), tmpfile()));
	data_read(args(1),tmpfile(),opt);
	system(fmt("rm -f %s",tmpfile()));
      } else {
	data_read(args(1),args(2),opt);
      }
      return 0;
    }
    if(args(0)=="write") {
      if(args.size() < 3) {
	printf("usage: write v1,v2,... file_name ([opt])\n"
	       " where v1,v2,... is list of data to write\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      data_write(get_vlist(args(1)),args(2),opt);
      return 0;
    }
    if(args(0)=="ls") {
      if(args.size() < 2) {
	printf("usage: ls pattern\n"
	       " print list of both macro and data variables"
	       " which matches pattern\n"
	       " 'ls *' show all data or macro variables\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      var.ls(args(1));
      data_ls(get_vlist(args(1)),opt);
      return 0;
    }
    if(args(0)=="cat") {
      if(args.size() < 2) {
	printf("usage: cat v1,v2,... [>|>>] [v] [(opt)]\n"
	       " concatenate data v1,v2,.. and print contents\n"
	       " redirect to the data v:\n"
	       "   >  : over write\n"
	       "   >> : append\n"
	       " option:\n"
	       "   nr:N0,N1 : choose index number range from N0 to N1\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      if(buf.find(">") != buf.npos) {
	if(args.size()>=3) data_cat(get_vlist(args(1)),args(2),args(3),opt);
      } else {
	data_show(get_vlist(args(1)),opt);
      }
      return 0;
    }
    if(args(0)=="rm") {
      if(args.size() < 2) {
	printf("usage: rm pattern\n"
	       " remove data or macro variables which matches pattern\n"
	       " example: 'rm *'  remove all data or macro variables\n"
	       ); return 0;
      }
      var.rm(args(1));
      data_rm(get_vlist(args(1)));
      return 0;
    }
    if(args(0)=="clear") {
      if(args.size() < 2) {
	printf("usage: clear N|all\n"
	       " clear the Nth box-area.\n"
	       " if N is 0, current box-area is cleared.\n"
	       " if N is 'all', all box-areas are cleared.\n"
	       ); return 0;
      }
      if(args(1)=="all") {
	_pl->next_page();
      } else {
	_pl->set_frame(args.stoi(1),1);
      }
      _pl->flush();
      return 0;
    }
    if(args(0)=="plot") {
      if(args.size() < 2) {
	printf("usage: plot [x] y [(opt)]\n"
	       " plot the 2D-graph of data x and y.\n"
	       " if data x is not specified the index data 'y_n' is created\n"
	       " then 'plot y_n y' is done.\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      if(args.size() < 3) {
	data_plot(args(1),opt);
      } else {
	if(args(2,0)=='(') {
	  data_plot(args(1),opt);
	} else {
	  data_plot(args(1),args(2),opt);
	}
      }
      return 0;
    }
    if(args(0)=="plot3") {
      if(args.size() < 4) {
	printf("usage: plot3 x y z [(opt)]\n"
	       " plot the 3d-graph of data x, y and z.\n"
	       " those three data should be the same size.\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      data_plot3d(args(1),args(2),args(3),opt);
      return 0;
    }
    if(args(0)=="mset") {
      thl::StrSplit sp(buf,"= ");
      if(sp.size() < 3) {
	printf("usage: mset v = {{v00,..,v0M},{v10,..,v1M},..,{vN0,..,vNM}}\n"
	       "       mset v = expression\n"
	       " set mesh data v which size is N*M.\n"
	       " in the expression, there should be 2 variables\n"
	       " of data which size are N and M.\n"
	       ); return 0;
      }
      std::string tag = sp(1);
      std::string expr = buf.substr(sp.index(2));
      if(expr.find("{") == 0) {
	mesh_set_list(tag,expr);
      } else {
	mesh_set_eval(tag,expr);
      }
      return 0;
    }
    if(args(0)=="mread") {
      if(args.size() < 3) {
      printf("usage: mread x,y,z mesh-file [(opt)]\n"
	     " read data and mesh-data\n"
	     " where x is data of size N.\n"
	     "       y is data of size M.\n"
	     "       z is mesh-data of size N*M.\n"
	     ); return 0;
      }
      Option opt=get_opt(buf);
      mesh_read(args(1),args(2),opt);
      return 0;
    }
    if(args(0)=="mwrite") {
      if(args.size() < 3) {
      printf("usage: mwrite x,y,z mesh-file [(opt)]\n"
	     " write data and mesh-data\n"
	     " where x is data of size N.\n"
	     "       y is data of size M.\n"
	     "       z is mesh-data of size N*M.\n"
	     ); return 0;
      }
      Option opt=get_opt(buf);
      mesh_write(args(1),args(2),opt);
      return 0;
    }
    if(args(0)=="mplot") {
      if(args.size() < 4) {
	printf("usage: mplot x y z [(opt)]\n"
	       " plot the mesh-3d-graph.\n"
	       " where x is data of size N.\n"
	       "       y is data of size M.\n"
	       "       z is mesh-data of size N*M.\n"
	       " option of graph type (default is 'mesh1')\n"
	       "  mt:mesh1  plot 3D-mesh with single color.\n"
	       "  mt:mesh2  plot 3D-mesh with gradation color.\n"
	       "  mt:cont1  plot 2D-mesh with gray-scaled contour.\n"
	       "  mt:cont2  plot 2D-mesh with gradation colored contour.\n"
	       " \n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      mesh_plot(args(1),args(2),args(3),opt);
      return 0;
    }
    if(args(0)=="fit") {
      if(args.size() < 3) {
	printf("usage: fit x y [lin|quad|exp|log|gaus|sin|circ] [(opt)]\n"
	       " do fitting to the data x and y and draw the result.\n"
	       " you should do 'plot x y' before this command.\n"
	       " available fitting functions:\n"
	       "   l[in] : y = c0 + c1*x \n"
	       "   q[uad]: y = c0 + c1*x + c2*x^2 \n"
	       "   e[xp] : y = c0*exp(c1*x) \n"
	       "   log   : y = c0 + log(c1*x) \n"
	       "   g[aus]: y = c0*exp(-(x-c1)^2/2*c2^2) \n"
	       "   s[in] : y = c0 + c1*sin(2*PI*c3*x) + c2*cos(2*PI*c3*x) \n"
	       "   c[irc]: (x-c0)^2 + (y-c1)^2 = c2^2 \n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      std::string func = "lin";
      if(args.size()>3) {if(args(3,0)!='(') func=args(3);}
      data_fit(args(1),args(2),func,opt);
      return 0;
    }
    if(args(0)=="fit3") {
      if(args.size() < 4) {
	printf("usage: fit3 x y z [plane] [(opt)]\n"
	       " do fitting to the data x,y,z by plane function.\n"
	       " you should do 'plot3 x y z' before this command.\n"
	       " available fitting functions:\n"
	       "   p[lane] : z = c0 + c1*x + c2*y\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      std::string func = "plane";
      if(args.size()>4) {if(args(4,0)!='(') func=args(4);}
      data_fit3d(args(1),args(2),args(3),func,opt);
      return 0;
    }
    if(args(0)=="xerr") {
      if(args.size() < 4) {
	printf("usage: xerr x y ex [(opt)]\n"
	       " plot x-error-bars of the data ex.\n"
	       " you should do 'plot x y' before this command.\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      data_xerr(args(1),args(2),args(3),opt);
      return 0;
    }
    if(args(0)=="yerr") {
      if(args.size() < 4) {
	printf("usage: yerr x y ey [(opt)]\n"
	       " plot y-error-bars of the data ey\n"
	       " you should do 'plot x y' before this command.\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      data_yerr(args(1),args(2),args(3),opt);
      return 0;
    }
    if(args(0)=="hplot") {
      if(args.size() < 2) {
	printf("usage: hplot v [(opt)]\n"
	       " make and plot the histogram of the data v,\n"
	       " it is created the bin data v_hx and the entry data v_hy\n"
	       " then plot the 2D-graph of v_hx and v_hy\n"
	       " options:\n"
	       "  nb:N      number of the histogram bins\n"
	       "  xr:x0,x1  x-range of the histogram\n"
	       " if there are no options, nb is set to 100, and x0 and x1\n"
	       " are calculated to include all values of v.\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      hist_plot(args(1),opt);
      return 0;
    }
    if(args(0)=="hplot2") {
      if(args.size() < 3) {
	printf("usage: hplot2 x y [(opt)]\n"
	       " make and plot the 2D-histogram of data x and y\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      hist2d_plot(args(1),args(2),opt);
      return 0;
    }
    if(args(0)=="hfit") {
      if(args.size() < 3) {
	printf("usage: hfit v func [(opt)]\n"
	       " you should do the 'hplot' before this command.\n"
	       " 'hplot' create a bin data v_hx, an entry data v_hy\n"
	       " then 'fit v_hx v_hy func' is done.\n"
	       " see the command 'fit' for the fitting functions.\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      hist_fit(args(1),args(2),opt);
      return 0;
    }
    if(args(0)=="fplot") {
      if(args.size() < 2) {
	printf("usage: fplot [t] v [(opt)]\n"
	       " do FFT with the time data t and the amplitude v.\n"
	       " it is created the frequency data v_fx and the power"
	       " spectrum v_fy.\n"
	       " then 'plot v_fx v_fy' is done.\n"
	       " if data t is not specified you should set the option 'dt:'\n"
	       "options:\n"
	       " dt:x   the time tick of FFT. (default is 1.0)\n"
	       " fw:s   FFT window function. (default is 'rc'(Rectangle))\n"
	       " name of window functions are\n"
	       "  rc  : Rectangle (default)\n"
	       "  hn  : Hann\n"
	       "  hm  : Hamming\n"
	       "  bk  : Blackman\n"
	       "  bh  : Blackman-Haris\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      if(args.size() < 3) {
	fft_plot(args(1),opt);
      } else {
	if(args(2,0)=='(') {
	  fft_plot(args(1),opt);
	} else {
	  fft_plot(args(1),args(2),opt);
	}
      }
      return 0;
    }
    if(args(0)=="ffit") {
      if(args.size() < 3) {
	printf("usage: ffit v [func] [(opt)]\n"
	       " you should do the 'fplot' before this command.\n"
	       " then 'fit v_fx v_fy [func]' is done.\n"
	       " see the command 'fit' for the fitting functions.\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      fft_fit(args(1),args(2),opt);
      return 0;
    }
    if(args(0)=="stat") {
      if(args.size() < 2) {
	printf("usage: stat v [(opt)]\n"
	       " make the statistics information of data v.\n"
	       " the macro variables [v_max] [v_min] [v_mean] [v_rms]\n"
	       " and [v_entry] are created.\n"
	       " if option 'cp:' is specified they are drawn"
	       " in the current graph.\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      data_statistics(args(1),opt);
      return 0;
    }
    if(args(0)=="cut") {
      if(args.size() < 3) {
	printf("usage: cut v1,v2,... \"expression\"\n"
	       " where v1,v2,... are data to cut\n"
	       " new data v1_cut,v2_cut,... are created\n"
	       "example:\n"
	       " cut x,y \"0<x<1 & 1<y<2\"\n"
	       " plot x_cut y_cut\n"
	       "using option 'cc:' it is also done by\n"
	       " plot x y (cc:\"0<x<1 & 1<y<2\")\n"
	       ); return 0;
      }
      thl::StrSplit v_list(args(1),",");
      std::string expr = thl::trim(buf.substr(args.index(2)));
      if(v_list.size()>0 && expr.size()>0) {
	for(auto &&v : v_list) {data_make_cut(v, expr);}
      }
      return 0;
    }
    if(args(0)=="vp"||args(0)=="viewport") {
      if(args.size() < 2) {
	printf("usage: vp x0 x1 y0 y1 aspect \n"
	       "       vp show|reset\n"
	       " where x0,x1 is x-range [0:1] of viewport\n"
	       "       y0,y1 is y-range [0:1] of viewport\n"
	       "       aspect is ratio: y-width/x-width\n"
	       ); return 0;
      }
      if(args(1)=="show") {
	_pl->print_viewport();
	// double x0,x1,y0,y1;
	// plgvpd(&x0,&x1,&y0,&y1);
	// printf("x0=%g x1=%g y0=%f y1=%g\n",x0,x1,y0,y1);
      } else if(args(1)=="reset") {
	_gopt.att.viewport(0,0,0,0, 0);
      } else if(args.size() > 5) {
	_gopt.att.viewport(args.stof(1),args.stof(2),
			   args.stof(3),args.stof(4), args.stof(5));
      }
      return 0;
    }
    if(args(0)=="exe") {
      if(args.size() < 2) {
	printf("usage: exe [macro_file] [arg1,arg2,...] [(opt)]\n"
	       " execute macro_file\n"
	       " reference of arguments:\n"
	       "  [$#] : number of argumnts\n"
	       "  [$N] : Nth argument (N=1,2,..)\n"
	       ); return 0;
      }
      Option opt=get_opt(buf);
      std::string arg_list=(args.size()>2 && args(2,0)!='(') ? args(2) : "";
      tip_exec(args(1),arg_list,opt.dm);
      return 0;
    }
    if(args(0)=="def") {
      if(args.size() < 2) {
	printf("usage: def [arg1,arg2,...]\n"
	       " set default argument of macro_file\n"
	       " reference of arguments:\n"
	       "  [$#] : number of argumnts\n"
	       "  [$N] : Nth argument (N=1,2,..)\n"
	       ); return 0;
      }
      set_macro_arg(args(1));      
      return 0;
    }
    if(args(0)=="elem") {
      thl::StrSplit sp(buf,"= ");
      if(sp.size() < 3) {
	printf("usage: elem x = v(N)\n"
	       " copy Nth element of daat v to the macro variable x.\n"
	       " (N begin from 1)\n"
	       ); return 0;
      }
      std::string x = thl::trim(sp(1));
      thl::Bracket bc('(',')',buf.substr(sp.index(2)));
      if(bc.size()==0) {printf("unbalanced '(' and ')'\n"); return 0;}
      std::string v = thl::trim(bc.before(0));
      thl::Calc calc;
      int index = (int)calc.eval(bc.contents(0));
      if(_dat.count(v)>0) {
	if(index > 0 && index <= (int)_dat[v].size()) {
	  if(_dat[v].type==DataType::Str) {
	    var.set_str(x,_dat[v].str[index-1]);
	  } else {
	    var.set_num(x,_dat[v].num[index-1]);
	  }
	} else {
	  printf("index %d is out of range\n",index);
	}
      } else {
	printf("%s not found\n",v.c_str());
      }      
      return 0;
    }
    if(args(0)=="font") {
      if(args.size() < 2) {
	printf("usage: font [N]\n"
	       "set global font\n"
	       " N=1 : Sans-Serif\n"
	       " N=2 : Serif\n"
	       " N=3 : Italic\n"
	       ); return 0;
      }
      _pl->set_font(args.stoi(1));
      return 0;
    }
    if(args(0)=="sort") {
      if(args.size() < 4) {
	printf("usage: sort v1,v2,... by v\n"
	       " sort data v1,v2,... by v in ascending order.\n"
	       " it is created sorted data v1_sort,v2_sort,...\n"
	       ); return 0;
      }
      data_make_sort(args(1),args(3));
      return 0;
    }
#if USE_EPICS_CA 
    if(args(0)=="cainfo") {
      if(args.size() < 2) {
	printf("usage: cainfo EPICS_record\n"
	       " show information of EPICS_record.\n"
	       ); return 0;
      }
      std::string rec = args(1);
      thl::EpicsCA ca(rec.c_str());
      ca.print_info();
      return 0;
    }
    if(args(0)=="caget") {
      if(args.size() < 2) {
	printf("usage: caget EPICS_record [> v]\n"
	       " get the value from EPICS_record and print contents.\n"
	       " if '>' is specified the value is redirected to the data v.\n"
	       " also the following macro variable related to the data v is"
	       " created.\n"
	       "macro variable:\n"
	       "   v : the 1st element of data v\n"
	       ); return 0;
      }
      std::string rec = args(1);
      std::string tag = (args.size()>3 && args(2)==">") ? args(3) : "";
      epics_ca_get(rec,tag);
      return 0;
    }
    if(args(0)=="caput") {
      if(args.size() < 4 || (args.size() > 2 && args(2) != "<")) {
	printf("usage: caput EPICS_record < v\n"
	       "usage: caput EPICS_record < expression\n"
	       " put the value to EPICS_record.\n"
	       " if data v exist, the value of v is put to EPICS_record,\n"
	       " if not exist, the expression value is put to EPICS_record.\n"
	       ); return 0;
      }
      std::string rec = args(1);
      std::string expr = buf.substr(args.index(3));
      epics_ca_put(rec,expr);
      return 0;
    }
    if(args(0)=="camon") {
      if(args.size() < 4 || (args.size() > 2 && args(2) != ">")) {
	printf("usage: camon EPICS_record > v\n"
	       " monitor the value of EPICS_record and redirected to"
	       " the data v.\n"
	       ); return 0;
      }
      std::string rec = args(1);
      std::string tag = args(3);
      epics_ca_mon(rec,tag);
      return 0;
    }
    if(args(0)=="cacheck") {
      if(args.size() < 2) {
	printf("usage: cacheck v1,v2,...\n"
	       " check if EPICS records related to data v1,v2,..."
	       " are updated.\n (v1,v2,... should be defeined by 'camon')\n"
	       " also the following macro variables related to the data"
	       " v1,v2,... are created.\n"
	       "macro variables:\n"
	       "  v1        : the 1st element of data v1\n"
	       "  v1.update : 1 if v1 updated, 0 if not updated\n"
	       "  v2        : the 1st element of data v2\n"
	       "  v2.update : 1 if v2 updated, 0 if not updated\n"
	       "  ... and so on ...\n"
	       ); return 0;
      }
      epics_ca_check(args(1));
      return 0;
    }
    if(args(0)=="caclose") {
      if(args.size() < 2) {
	printf("usage: caclose [v1,v2,...]\n"
	       " close the connection of the EPICS record related to"
	       " the data v1,v2,...\n"
	       ); return 0;
      }
      epics_ca_close(args(1));
      return 0;
    }
#endif
    return 1;
  }
  void set_macro_arg(std::string arg_list) {
    if(arg_list.size()>0) {
      thl::CFormat fmt;
      thl::StrSplit sp;
      sp.set_quot_to_skip_split('"');
      sp.split(arg_list,",");
      if(!var.exist_num("$#")) var.set_num("$#",(double)sp.size());
      for(int j=0; j<(int)sp.size(); j++) {
	thl::StrSplit sp2(sp(j),"=");
	if(sp2.size()>1) {
	  std::string tag=sp2(0);
	  if(!var.exist_str(tag)) var.set_str(tag,sp2(1));
	} else {
	  std::string tag=fmt("$%d",j+1);
	  if(!var.exist_str(tag)) var.set_str(tag,sp(j));
	}
      }
    } else {
      var.set_num("$#",0);
    }
  }
  void tip_exec(std::string fname, std::string arg_list, int mode=0) {
    Tip tip(_pl);
    std::ifstream ifs(fname.c_str());
    if(ifs) {
      std::vector<std::string> vbuf;
      std::string line;
      while(std::getline(ifs,line)) {
	if(line.size()>0) {
	  if(line[line.find_first_not_of(' ')]=='#') continue;
	  thl::StrSplit sp;
	  sp.set_quot_to_skip_split('"');
	  sp.split(line,";");
	  if(sp.size()>0) {
	    for(size_t j=0; j<sp.size(); j++) {vbuf.push_back(sp(j));}
	  }
	}
      }
      if(mode==1) {           // in debug mode(=1)
	if(set_index(vbuf)==0) {
	  set_macro_arg(arg_list);
	  parse_vbuf(vbuf);
   	}
      } else if (mode==0) {                // in normal mode(=0)
	if(tip.set_index(vbuf)==0) {
	  tip.set_macro_arg(arg_list);
	  tip.parse_vbuf(vbuf);
   	}
      }
    } else {
      printf("can't open %s\n",fname.c_str());
    }
  }
};

int main(int argc, const char *argv[]) {
  thl::ArgOpt arg(argc,argv,"h,-help,v,-version,t:,g:,d:,e:,-pdf:,-png:",0);
  if(arg.find_opt("h") || arg.find_opt("-help")) {
    printf("\n"
	   "usage: tip [options]\n"
	   "\n"
	   "options:(where arg is option's argument)\n"
	   " -h : show help message (also '--help')\n"
	   " -v : show version (also '--version')\n"
	   " -t arg: set window title (default is \"tip\")\n"
	   " -g arg: set window geometry size (default is \"800x600\")\n"
	   " -d arg: set drawing device (default is \"xcairo\")\n"
	   " -e arg : execute a macro file\n"
	   " --pdf arg : graph is drawn in pdf file (window is not open)\n"
	   " --png arg : graph is drawn in png file (window is not open)\n"
	   "\n"
	   ); return 1;
  }
  std::string title = arg.opt_def("t","tip");
  std::string geom = arg.opt_def("g","800x600");
  std::string dev = arg.opt_def("d","xcairo");

  thl::PLPlot pl;
  if(arg.find_opt("v") || arg.find_opt("-version")) {
    printf("tip (c++11) version: %s\n",GIT_VER);
    printf("PLPlot version: %s\n",pl.ver_str());
#if USE_EPICS_CA 
    printf("EPICS version: %s\n", EPICS_VER);
#endif
    return 1;
  }
  if(arg.find_opt("-pdf")) {
    pl.init("",geom.c_str(),"pdfcairo",arg.opt("-pdf").c_str());
  } else if(arg.find_opt("-png")) {
    pl.init("",geom.c_str(),"pngcairo",arg.opt("-png").c_str());
  } else {
    pl.init(title.c_str(),geom.c_str(),dev.c_str());
  }

  Tip tip(&pl);
  if(arg.find_opt("e")) {
    thl::StrSplit sp;
    sp.set_quot_to_skip_split('"');
    sp.split(arg.opt("e"));
    std::string arg_list=(sp.size()>1) ? sp(1) : "";
    tip.tip_exec(sp(0),arg_list);
    if((!arg.find_opt("-pdf")) && (!arg.find_opt("-png"))) {
      usleep(100000); tip.flush(); getchar();
    }
  } else {
    tip.main_loop("tip> ",".tip_history");
  }
  return 0;
}
