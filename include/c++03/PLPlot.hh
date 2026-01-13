// thl : tiny header-only library
//
// PLAtt  : attribute for class PLPlot
// PLPlot : another wrapper class of plplot.h
//
// c++03
//
#ifndef THL_PLPLOT_HH
#define THL_PLPLOT_HH

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <plplot/plplot.h>
//#include <plplot/plevent.h>
#include <unistd.h>
#include "StrSplit.hh"

#ifndef plwidth
#define plwidth plwid
#endif

// "PLFLT" is defined as "double" for most of 32/64bit systems

namespace thl {

  bool PLPlotReverseVideo=0;
  bool PLPlotDoubleBufferXwin=0;

  struct PLAtt {// attribute of graph
    short lwid; // line width (if 0 not drawn)
    short lcol; // line color
    short lsty; // line style
    short symb; // symbol type (if 0 not drawn)
    short scol; // symbol color
    short twid; // text width
    short tcol; // text color
    short font; // font 1:Fiexd, 2:Serif, 3:Italic, 4:Script
    short fcol; // fill area color
    short fsty; // fill area style
    short bwid; // box(graph frame) line width
    short logx; // flag of logscale for x-axis
    short logy; // flag of logscale for y-axis
    short logz; // flag of logscale for z-axis
    short errx; // flag to plot x-error-bars
    short erry; // flag to plot y-error-bars
    short hsty; // histogram style
    short divo; // divided frame drawing order
    short nxsub, nysub, nzsub; // x,y,z-axis number of sub-ticks
    short grad; // gradation of contour plot
    short asty; // arrow style : 0:non, 1:end-edge, 2:start-edge, 3:both-edge
    PLFLT ssiz; // symbol size
    PLFLT tsiz; // text size
    PLFLT trot; // text rotation (degree)
    PLFLT tpos; // text positon (0.0:left - 1.0:right)
    PLFLT x0, x1, y0, y1, z0, z1; // x,y,z-axis range
    PLFLT vx0, vx1, vy0, vy1;     // view port region [0.0:1.0]
    PLFLT vasp;  // view port aspect ratio (y/x) : if 0 automatic aspect
    PLFLT ascx;  // x-axis auto scale margin factor(default=0.1)
    PLFLT ascy;  // y-axis auto scale margin factor(default=0.1)
    PLFLT ascz;  // z-axis auto scale margin factor(default=0.1)
    PLFLT alt; // altitude in degree above the xy plane of 3d-plot
    PLFLT az;  // azimuth in degree of 3d-plot
    PLFLT xtick, ytick,ztick; // x,y,z-axis major-tick interval
    bool grid;       // flag to draw grid lines
    bool time_xaxis; // flag of time format for x-axis
    char time_fmt[32]; // time format buffer: %Y %m %d %H %M %S ...
    char title[128]; // title buffer for each graph
    char xlab[64];  // x-axis label buffer
    char ylab[64];  // y-axis label buffer
    char zlab[64];  // z-axis label buffer

    PLAtt(void) : lwid(1), lcol(15), lsty(1), symb(0), scol(15),
		  twid(1), tcol(15), font(1), fcol(0), fsty(-1),
		  bwid(1), logx(0), logy(0), logz(0), errx(0), erry(0), hsty(0),
		  divo(0), nxsub(0), nysub(0), nzsub(0), grad(32), asty(0),
		  ssiz(1), tsiz(1), trot(0), tpos(0),
		  x0(0), x1(0), y0(0), y1(0), z0(0), z1(0),
		  vx0(0), vx1(0), vy0(0), vy1(0), vasp(0),
		  ascx(0.02), ascy(0.1), ascz(0.1), alt(45), az(45),
		  xtick(0), ytick(0), ztick(0), grid(0), time_xaxis(0) {
      memset(title,0,sizeof(title));
      memset(xlab,0,sizeof(xlab));
      memset(ylab,0,sizeof(ylab));
      memset(zlab,0,sizeof(zlab));
      memset(time_fmt,0,sizeof(time_fmt));// "%Y/%m/%d %H:%M:%S"
    }
    void set_time_fmt(const char *str) {snprintf(time_fmt,32,"%s",str);}
    void set_title(const char *str) {snprintf(title,128,"%s",str);}
    void set_xlab(const char *str) {snprintf(xlab,64,"%s",str);}
    void set_ylab(const char *str) {snprintf(ylab,64,"%s",str);}
    void set_zlab(const char *str) {snprintf(zlab,64,"%s",str);}
    void box(PLFLT xs, PLFLT xe, PLFLT ys, PLFLT ye){x0=xs;x1=xe;y0=ys;y1=ye;}
    void box3d(PLFLT xs, PLFLT xe, PLFLT ys, PLFLT ye, PLFLT zs, PLFLT ze){
      x0=xs; x1=xe; y0=ys; y1=ye; z0=zs; z1=ze;
    }
    void viewport(PLFLT x0, PLFLT x1, PLFLT y0, PLFLT y1, PLFLT aspect=0) {
      vx0=x0; vx1=x1; vy0=y0; vy1=y1; vasp=aspect;
    }
    int color_to_index(const std::string &s) {
      if(s=="0" ||s=="whi"||s=="white") return 0;
      if(s=="1" ||s=="red") return 1;
      if(s=="2" ||s=="ylw"||s=="yellow") return 2;
      if(s=="3" ||s=="grn"||s=="green") return 3;
      if(s=="4" ||s=="aqu"||s=="aqua") return 4;
      if(s=="5" ||s=="pnk"||s=="pink") return 5;
      if(s=="6" ||s=="wht"||s=="wheat") return 6;
      if(s=="7" ||s=="gry"||s=="gray") return 7;
      if(s=="8" ||s=="brn"||s=="brown") return 8;
      if(s=="9" ||s=="blu"||s=="blue") return 9;
      if(s=="10"||s=="vio"||s=="violet") return 10;
      if(s=="11"||s=="cyn"||s=="cyan") return 11;
      if(s=="12"||s=="tqs"||s=="turquoise") return 12;
      if(s=="13"||s=="mgt"||s=="magenta") return 13;
      if(s=="14"||s=="smn"||s=="salmon") return 14;
      if(s=="15"||s=="blk"||s=="black") return 15;
      printf("unknown color %s, use black\n",s.c_str()); return 15;
    }
    const char* index_to_color(int index, bool shortname=0) {
      if(index==0) return shortname ? "whi" : "white";
      if(index==1) return "red";
      if(index==2) return shortname ? "ylw" : "yellow";
      if(index==3) return shortname ? "grn" : "green";
      if(index==4) return shortname ? "aqu" : "aqua";
      if(index==5) return shortname ? "pnk" : "pink";
      if(index==6) return shortname ? "wht" : "wheat";
      if(index==7) return shortname ? "gry" : "gray";
      if(index==8) return shortname ? "brn" : "brown";
      if(index==9) return shortname ? "blu" : "blue";
      if(index==10) return shortname ? "vio" : "violet";
      if(index==11) return shortname ? "cyn" : "cyan";
      if(index==12) return shortname ? "tqs" : "turquoise";
      if(index==13) return shortname ? "mgt" : "magenta";
      if(index==14) return shortname ? "smn" : "salmon";
      if(index==15) return shortname ? "blk" : "black";
      printf("unknown color index %d, use black\n",index); return "black";
    }
    int symbol_to_index(const std::string &s) {
      if(s.size() > 0) {
	if(isdigit(s[0])) {
	  int n = strtol(s.c_str(),0,10);
	  return n%126;
	}
	if(s=="non") return 0;
	if(s=="dot") return 1;
	if(s=="pls"||s=="plus") return 2;
	if(s=="str"||s=="star") return 3;
	if(s=="arc") return 4;
	if(s=="crs"||s=="cross") return 5;
	if(s=="sqr"||s=="square") return 6;
	if(s=="tri"||s=="triangle") return 7;
	if(s=="acc"||s=="arccross") return 8;
	if(s=="acd"||s=="arcdot") return 9;
	if(s=="sq2"||s=="square2") return 10;
	if(s=="dia"||s=="diamond") return 11;
	if(s=="st2"||s=="star2") return 12;
	if(s=="sq3"||s=="square3") return 13;
	if(s=="cr2"||s=="cross2") return 14;
	if(s=="st3"||s=="star3") return 15;
	if(s=="bsq"||s=="blacksqr") return 16;
      }
      printf("unknown symbol %s, used dot\n",s.c_str()); return 1;
    }
    const char* index_to_symbol(int index, bool shortname=0) {
      index = index%126;
      if(index==0) return "non";
      if(index==1) return "dot";
      if(index==2) return shortname ? "pls" : "plus";
      if(index==3) return shortname ? "str" : "star";
      if(index==4) return "arc";
      if(index==5) return shortname ? "crs" : "cross";
      if(index==6) return shortname ? "sqr" : "square";
      if(index==7) return shortname ? "tri" : "triangle";
      if(index==8) return shortname ? "acc" : "arccross";
      if(index==9) return shortname ? "acd" : "arcdot";
      if(index==10) return shortname ? "sq2" : "square2";
      if(index==11) return shortname ? "dia" : "diamond";
      if(index==12) return shortname ? "st2" : "star2";
      if(index==13) return shortname ? "sq3" : "square3";
      if(index==14) return shortname ? "cr2" : "cross2";
      if(index==15) return shortname ? "st3" : "star3";
      if(index==16) return shortname ? "bsq" : "blacksqr";
      printf("use unnamed symbol index %d\n",index); return "unnamed";
    }
    int line_to_index(const std::string &s) {
      if(s=="1"||s=="sld"||s=="solid") return 1;
      if(s=="2"||s=="dot") return 2;
      if(s=="3"||s=="dsh"||s=="dash") return 3;
      printf("unknown line %s, used solid\n",s.c_str()); return 1;
    }
    const char* index_to_line(int index, bool shortname=0) {
      if(index==1) return shortname ? "sld" : "solid";
      if(index==2) return "dot";
      if(index==3) return shortname ? "dsh" : "dash";;
      printf("unknown line index %d, use solid\n",index); return "solid";
    }
    int fill_to_index(const std::string &s) {
      if(s=="-1"||s=="nul"||s=="null") return -1;
      if(s=="0"||s=="sld"||s=="solid") return 0;
      if(s=="1"||s=="hor") return 1;
      if(s=="2"||s=="ver") return 2;
      if(s=="3"||s=="p45") return 3;
      if(s=="4"||s=="n45") return 4;
      if(s=="5"||s=="p30") return 5;
      if(s=="6"||s=="n30") return 6;
      if(s=="7"||s=="hv")  return 7;
      if(s=="8"||s=="pn45") return 8;
      printf("unknown fill style %s, used solid\n",s.c_str()); return 0;
    }
    const char* index_to_fill(int index, bool shortname=0) {
      if(index==-1) return shortname ? "nul" : "null";
      if(index==0) return shortname ? "sld" : "solid";
      if(index==1) return "hor";
      if(index==2) return "ver";
      if(index==3) return "p45";
      if(index==4) return "n45";
      if(index==5) return "p30";
      if(index==6) return "n30";
      if(index==7) return "hv";
      if(index==8) return "pn45";
      printf("unknown line index %d, use solid\n",index); return "solid";
    }
  };//-- struct PLAtt

//---------------------------------------------------------------------------
  class PLPlot {
   private:
    std::vector<PLFLT> _errx[2]; // arrays for x error bar's edges
    std::vector<PLFLT> _erry[2]; // arrays for y error bar's edges
    std::vector<PLFLT> _lx; // arrays for logx
    std::vector<PLFLT> _ly; // arrays for logy
    std::vector<PLFLT> _lz; // arrays for logz
    std::vector<PLFLT> _hx; // arrays for histogram x-axis
    std::vector<PLFLT> _hy; // arrays for histogram y-axis
    char _ver_str[80];
    PLFLT **_mesh_z; // pointer of 2d-array of mesh
    PLcGrid2 _cgrid2; // 2d-coordinate trans arrays for contour plot
    int _nx,_ny; // division of box
    int _nc;     // current box number
   public:
    PLAtt att;

    PLPlot(void) : _mesh_z(0),_nx(1),_ny(1),_nc(0) {}
    PLPlot(const char* title, const char* geom="600x400+1+1",
	   const char *device="xwin") : _mesh_z(0),_nx(1),_ny(1),_nc(0) {
      init(title,geom,device);
    }
    void set_device(const std::string devname, const std::string filename="") {
      plsdev(devname.c_str());
      if(filename.size() > 0) plsfnam(filename.c_str());
    }
    const char *ver_str(void) {
      plgver(_ver_str); return _ver_str;
    }
    void set_aspect_from_geom(const char *geom) {
      StrSplit sp1(geom,"+");
      StrSplit sp2(sp1(0),"x");
      PLFLT dx=sp2.stof(0);
      PLFLT dy=sp2.stof(1);
      att.vasp = (dx>0) ? dy/dx : 0; 
    }
    void init(const char *title, const char *geom, const char *device,
	      const char *fname="") {
// device: "xwin", "xcairo", "pdfcairo" and so on
      const char *arg[] = {title,"-geometry",geom,"-np",""};
      int narg=4;
      if(PLPlotDoubleBufferXwin) {arg[4]="-db"; narg=5;}
#if PLPLOT_OPTION_NEW
      //#if __cplusplus >= 201103L
      plparseopts(&narg, (char **)arg, PL_PARSE_FULL);
#else
      plparseopts(&narg, (const char **)arg, PL_PARSE_FULL);
#endif
      if( ! PLPlotReverseVideo ) {
	plspal0("cmap0_white_bg.pal");
      }
      plsdev(device);
      if(strlen(fname) > 0) plsfnam(fname);
      plinit();
      plfontld(0); // standard font set
      //      plfontld(1); // extended font set
      divide(1,1);
      memset(&_cgrid2,0,sizeof(_cgrid2));
      set_aspect_from_geom(geom);
    }
    ~PLPlot(void) {plend();}
    void clear(void) {plclear();}
    void flush(void) {plflush();}
    void divide(int nx, int ny) {plssub(nx,ny); _nx=nx; _ny=ny; _nc=0;}
    int nx(void) {return _nx;}
    int ny(void) {return _ny;}
    void bop(void) {plbop();}
    void eop(void) {pleop();}
    void end(void) {plend();}
    void next_page(void) {pleop(); plbop(); plssub(_nx,_ny);}
    void update(void) {pladv(0);}
    void draw_null_box(const std::vector<PLFLT>& x,
		       const std::vector<PLFLT>& y, int sub=0) {
      auto_scale(x,y);
      draw_box(sub);
    }
    void set_font(int font) {att.font=font;  plfont(att.font);}
    void set_auto_aspect(bool flag_3d=0) {
      if(flag_3d) {
	plvpas(0, 1, -0.1, 0.85, att.vasp);
      } else {
	if(att.vx1==0 || att.vy1==0) {
	  PLFLT x0,x1,y0,y1;
	  if(_nx==1) {x0=0.12; x1=0.92;}
	  if(_nx==2) {x0=0.15; x1=0.92;}
	  if(_nx>=3) {x0=0.30; x1=0.92;}
	  if(_ny==1) {
	    y0=0.10; y1=0.90;
	    if(_nx==1) {x0=0.12; x1=0.92;}
	    if(_nx==2) {x0=0.20; x1=0.92;}
	    if(_nx>=3) {x0=0.20; x1=0.92;}
	  }
	  if(_ny==2) {y0=0.15; y1=0.85;}
	  if(_ny>=3) {y0=0.20; y1=0.80;}
	  plvpas(x0, x1, y0, y1, att.vasp);
	} else {
	  plvpas(att.vx0, att.vx1, att.vy0, att.vy1, att.vasp);
	}
      }
    }
    void print_viewport(void) {
      printf("x0=%g, x1=%g, ",att.vx0, att.vx1);
      printf("y0=%g, y1=%g, ",att.vy0, att.vy1);
      printf("aspect=%g\n",att.vasp);
    }
    void set_div_order(int n) {att.divo=n;}
    int calc_advance(int sub) {
      int ret=sub;
      if(sub==0) {
	if(att.divo!=0) ret = (_nc/_ny)+1+(_nc%_ny)*_nx; // vertical order
	if(_nc < _nx*_ny-1) _nc++; else _nc=0;
      } else {
	_nc = sub-1;
      }
      return ret;
    }
    void set_window(PLFLT x0, PLFLT x1, PLFLT y0, PLFLT y1) {
      plwind(x0, x1, y0, y1);
    }
    void set_frame(int sub=0, bool flag_clear=1, bool flag_3d=0) {
      pladv(calc_advance(sub));
      plvsta();
      set_auto_aspect(flag_3d);
      if(flag_clear) clear();
      PLFLT x0=(att.logx) ? ((att.x0>0) ? log10(att.x0) : 0) : att.x0;
      PLFLT x1=(att.logx) ? ((att.x1>0) ? log10(att.x1) : 0) : att.x1;
      PLFLT y0=(att.logy) ? ((att.y0>0) ? log10(att.y0) : 0) : att.y0;
      PLFLT y1=(att.logy) ? ((att.y1>0) ? log10(att.y1) : 0) : att.y1;
      plwind(x0, x1, y0, y1);
    }
    void draw_box_sub(int sub=0) {
// options:
// b:bottom+left-frame, c:top+right-frame, n:num-label, g:grid
// s:sub-tick, t:major-tick, v:vertical-label, d:date, l:logscale
// i:ivert-tick(outside) m:inside-label
      plwidth(att.bwid);
      if(att.time_xaxis) pltimefmt(att.time_fmt);
      std::string ox="bcnst",oy="bcnstv";  // options(x,y-axis)
      std::string gx="g",gy="g";           // options(x,y-axis) for grid
      //      if(att.invtick) {ox += "i"; oy += "i";}
      if(att.time_xaxis) {gx += "d"; ox += "d";}
      if(att.logx) {ox += "l";}
      if(att.logy) {gy += "l"; oy += "l";}
      if(att.grid) {
	pllsty(2); plcol0(7);  // grid lines are dot(2) and gray(7)
	plbox(gx.c_str(),att.xtick,att.nxsub, gy.c_str(),att.ytick,att.nysub);
      }
      pllsty(1); plcol0(15); // frame lines are solid(1) and black(15)
      plschr(0,att.tsiz);
      plbox(ox.c_str(),att.xtick,att.nxsub, oy.c_str(),att.ytick,att.nysub);
      pllab(att.xlab, att.ylab, att.title);
      plschr(0,1);
    }
    void draw_box(int sub=0, bool flag_clear=1) {
      set_frame(sub,flag_clear);
      draw_box_sub(sub);
    }
    void draw_graph(const std::vector<PLFLT>& x,
		    const std::vector<PLFLT>& y, int n=0) {
      if(n == 0) n = (int)x.size();
      draw_graph(x.data(),y.data(),n);
    }
    void draw_graph(const PLFLT* x, const PLFLT* y, int n) {
      const PLFLT *px=x,*py=y;
      if(att.logx) {
	_lx.resize(n);
	for(int j=0; j<n; j++) _lx[j] = (x[j]>0) ? log10(x[j]) : 0;
	px=&_lx[0];
	if( att.errx ) {
	  for(int k=0; k<2; k++)
	    for(int j=0; j<n; j++)
	      _errx[k][j] = (_errx[k][j]>0) ? log10(_errx[k][j]) : 0;
	}
      }
      if(att.logy) {
	_ly.resize(n);
	for(int j=0; j<n; j++) _ly[j] = (y[j]>0) ? log10(y[j]) : 0;
	py=&_ly[0];
	if( att.erry ) {
	  for(int k=0; k<2; k++)
	    for(int j=0; j<n; j++)
	      _erry[k][j] = (_erry[k][j]>0) ? log10(_erry[k][j]) : 0;
	}
      }
      if( att.lwid ) {
	plcol0(att.lcol);
	plwidth(att.lwid);
	pllsty(att.lsty);
	plline(n, px, py);
      }
      if( att.symb ) {
	plcol0(att.scol);
	plssym(0,att.ssiz);
	plpoin(n, px, py, att.symb);
      }
      if( att.errx ) {
	plerrx(n, &_errx[0][0], &_errx[1][0], py);
      }
      if( att.erry ) {
	plerry(n, px, &_erry[0][0], &_erry[1][0]);
      }
    }
    void draw_error_x(const std::vector<PLFLT>& x, 
		      const std::vector<PLFLT>& y,
		      const std::vector<PLFLT>& errx, int n=0) {
      if(n == 0) n = (int)x.size();
      PLAtt att_save = att; att.errx=1; att.lwid=0;
      for(int k=0; k<2; k++) {
	_errx[k].resize(n);
	for(int j=0; j<n; j++)
	  if(k==0) _errx[k][j] =  x[j] + errx[j];
	  else     _errx[k][j] =  x[j] - errx[j];
      }
      draw_graph(x,y,n);  att=att_save;
    }
    void draw_error_y(const std::vector<PLFLT>& x,
		      const std::vector<PLFLT>& y,
		      const std::vector<PLFLT>& erry, int n=0) {
      if(n == 0) n = (int)y.size();
      PLAtt att_save = att; att.erry=1; att.lwid=0;
      for(int k=0; k<2; k++) {
	_erry[k].resize(n);
	for(int j=0; j<n; j++)
	  if(k==0) _erry[k][j] =  y[j] + erry[j];
	  else     _erry[k][j] =  y[j] - erry[j];
      }
      draw_graph(x,y,n);  att=att_save;
    }
    void draw_bin(const std::vector<PLFLT>& x,
		  const std::vector<PLFLT>& y, int n=0) {
      if(n == 0) n = (int)x.size();
      draw_bin(x.data(),y.data(),n);
    }
    void draw_bin(const PLFLT* x, const PLFLT* y, int n) {
      const PLFLT *px=x,*py=y;
      if(att.logx) {
	_lx.resize(n);
	for(int j=0; j<n; j++) _lx[j] = (x[j]>0) ? log10(x[j]) : 0;
	px=&_lx[0];
      }
      if(att.logy) {
	_ly.resize(n);
	for(int j=0; j<n; j++) _ly[j] = (y[j]>0) ? log10(y[j]) : 0;
	py=&_ly[0];
      }
      if( att.symb ) {
	plcol0(att.scol);
	plssym(0,att.ssiz);
	plpoin(n, px, py, att.symb);
      }
      if( att.lwid ) {
	plcol0(att.lcol);
	plwidth(att.lwid);
	pllsty(att.lsty);
	_hx.resize(n*2+2); _hy.resize(n*2+2);
	PLFLT xwid = (px[1]-px[0])/2;
	_hx[0]=px[0]-xwid; _hy[0]=0;
	_hx[n*2+1]=px[n-1]+xwid; _hy[n*2+1]=0;
	for(int j=0; j<n; j++) {
	  _hx[j*2+1]   = px[j] - xwid;
	  _hx[j*2+2] = px[j] + xwid;
	  _hy[j*2+1] = _hy[j*2+2] =  py[j];
	}
	fill_area(_hx, _hy);
	if(att.hsty == 1) {
	  for(int j=0; j<n; j++) {
	    PLFLT x1[2] = {px[j]-xwid,px[j]-xwid};
	    PLFLT x2[2] = {px[j]+xwid,px[j]+xwid};
	    PLFLT y[2] = {py[j],0};
	    plline(2,x1,y);
	    plline(2,x2,y);
	  }
	}
      }
    }
    void relative_to_absolute(PLFLT *x, PLFLT *y) {
      double x0,x1,y0,y1;
      plgvpw(&x0,&x1,&y0,&y1);
      *x = x0 + (x1-x0)*(*x);
      *y = y0 + (y1-y0)*(*y);
    }
    void rotation_to_dx_dy(PLFLT rot, PLFLT *dx, PLFLT *dy) {
      if(rot==90.) {
	*dx=0; *dy=1;
      } else if(rot==-90.) {
	*dx=0; *dy=-1;
      } else {
	double x0,x1,y0,y1;
	plgvpw(&x0,&x1,&y0,&y1);
	*dx=(x1-x0);
	*dy=(y1-y0)*tan(att.trot*M_PI/180.);
      }
    }
    void draw_text(PLFLT x, PLFLT y, const char *text, bool rc=0) {
      if(rc) {
	relative_to_absolute(&x,&y);
      } else {
	if(att.logx) x=log10(x);
	if(att.logy) y=log10(y);
      }
      PLFLT dx=0,dy=0;
      rotation_to_dx_dy(att.trot,&dx,&dy);
      plschr(0,att.tsiz);
      plcol0(att.tcol);
      plwidth(att.twid);
      StrSplit sp(text,"\n");
      //      PLFLT dyy=(att.y1-att.y0)*att.tsiz*0.08;
      PLFLT dyy=(att.y1-att.y0)*att.tsiz*0.04*_ny;
      for(size_t j=0; j<sp.size(); j++) {
	plptex(x, y-dyy*j, dx, dy, att.tpos, sp(j).c_str());
      }
      plschr(0,1);
    }
    void draw_line(PLFLT x0, PLFLT x1, PLFLT y0, PLFLT y1, bool rc=0) {
      plwidth(att.lwid);
      plcol0(att.lcol);
      pllsty(att.lsty);
      if(rc) {
	relative_to_absolute(&x0,&y0);
	relative_to_absolute(&x1,&y1);
      } else {
	if(att.logx) {x0=log10(x0); x1=log10(x1);}
	if(att.logy) {y0=log10(y0); y1=log10(y1);}
      }
      PLFLT x[2] = {x0,x1};
      PLFLT y[2] = {y0,y1};
      plline(2,x,y);
      double dx=x1-x0, dy=y1-y0;
      plschr(0,1.0+0.5*(att.lwid-1));
      if((att.asty>>0)&1) plptex(x1, y1, dx, dy, 1, ">");
      if((att.asty>>1)&1) plptex(x0, y0, dx, dy, 0, "<");
      plschr(0,1);
    }
    void draw_square(PLFLT x0, PLFLT x1, PLFLT y0, PLFLT y1, bool rc=0) {
      draw_line(x0,x0,y0,y1,rc);
      draw_line(x0,x1,y1,y1,rc);
      draw_line(x1,x1,y0,y1,rc);
      draw_line(x0,x1,y0,y0,rc);
    }
    void draw_circle(PLFLT cx, PLFLT cy, PLFLT r, bool rc=0) {
      plwidth(att.lwid);
      plcol0(att.lcol);
      pllsty(att.lsty);
      double rx=r,ry=r;
      if(rc) {
	relative_to_absolute(&cx,&cy);
	relative_to_absolute(&rx,&ry);
      } else {
	if(att.logx) {cx=log10(cx); rx=log10(rx);}
	if(att.logy) {cy=log10(cy); ry=log10(ry);}
      }
      plarc(cx,cy,rx,ry,0.,360.,0.,false);
    }
    void draw_symbol(PLFLT x, PLFLT y, bool rc=0) {
      plcol0(att.scol);
      plssym(0,att.ssiz);
      if(rc) {
	relative_to_absolute(&x,&y);
      } else {
	if(att.logx) x=log10(x);
	if(att.logy) y=log10(y);
      }
      plpoin(1,&x,&y,att.symb);
    }
    void fill_box(PLFLT x0, PLFLT x1, PLFLT y0, PLFLT y1, bool rc=0) {
      if(rc) {
	relative_to_absolute(&x0,&y0);
	relative_to_absolute(&x1,&y1);
      } else {
	if(att.logx) {x0=log10(x0); x1=log10(x1);}
	if(att.logy) {y0=log10(y0); y1=log10(y1);}
      }
      PLFLT x[5] = {x0, x1, x1, x0, x0};
      PLFLT y[5] = {y0, y0, y1, y1, y0};
      fill_area(x,y,5);
    }
    void fill_area(const std::vector<PLFLT> &x, const std::vector<PLFLT> &y) {
      fill_area(x.data(), y.data(), x.size());
    }
    void fill_area(const PLFLT* x, const PLFLT* y, int n) {
      if(att.fsty >= 0) {
	plcol0(att.fcol);
	plpsty(att.fsty);
	plfill(n, x, y);
	plpsty(0); // reset to default(solid)
      }
      plcol0(att.lcol);
      pllsty(att.lsty);
      plline(n, x, y);
    }
    void calc_scale(const std::vector<PLFLT>& x,
		    PLFLT& x0, PLFLT& x1, PLFLT ascx, int n=0) {
      if( x0 == x1 ) {
	x0=x[0]; x1=x[0];
	if (n==0) n = x.size();
	for(size_t j=1; j<(size_t)n; j++) {
	  if(x[j] < x0) x0=x[j];
	  if(x[j] > x1) x1=x[j];
	}
	PLFLT dx = (x1==x0) ? 1 : (x1-x0)*ascx;
	x0 -= dx; x1 += dx;
      }
    }
    void auto_scale(const std::vector<PLFLT>& x,
		    const std::vector<PLFLT>& y, int n=0) {
      calc_scale(x, att.x0, att.x1, att.ascx, n);
      calc_scale(y, att.y0, att.y1, att.ascy, n);
    }
    void auto_rescale(const std::vector<PLFLT>& x,
		      const std::vector<PLFLT>& y, int n=0) {
      PLAtt att2;      
      calc_scale(x, att2.x0, att2.x1, att.ascx, n);
      calc_scale(y, att2.y0, att2.y1, att.ascy, n);
      if( att2.x0 < att.x0 ) att.x0 = att2.x0;
      if( att2.x1 > att.x1 ) att.x1 = att2.x1;
      if( att2.y0 < att.y0 ) att.y0 = att2.y0;
      if( att2.y1 > att.y1 ) att.y1 = att2.y1;
    }
    void plot(const std::vector<PLFLT>& x,
	      const std::vector<PLFLT>& y, int sub=0, int n=0){
      auto_scale(x,y,n);
      draw_box(sub);
      draw_graph(x,y,n);
    }
    void plot_bin(const std::vector<PLFLT>& x,
		  const std::vector<PLFLT>& y, int sub=0,
		   int n=0){
      auto_scale(x,y,n);
      draw_box(sub);
      draw_bin(x,y,n);
    }
    // void wait_key_or_click(void) {
    //   static PLGraphicsIn gin;
    //   while(1) {
    // 	if(plGetCursor(&gin)) break;
    // 	if(gin.keysym == PLK_Escape) break;
    // 	plgra();
    // 	usleep(1000);
    //   }
    // }
    void draw_box3d(int sub=0, bool flag_clear=1) {
      set_frame(sub,flag_clear,1);
      draw_box3d_sub(sub);
    }
    void draw_box3d_sub(int sub=0) {
      std::string ox="bcnstu",oy="bcnstu",oz="bcnstuv";
      if(att.logx) {ox += "l";}
      if(att.logy) {oy += "l";}
      if(att.logz) {oz += "l";}
      plschr(0,att.tsiz);
      plwind(-1, 1, -1, 1.35);
      plwidth(att.bwid);
      if(att.time_xaxis) pltimefmt(att.time_fmt);
      pllsty(1); plcol0(15);
      PLFLT x0=(att.logx) ? ((att.x0>0) ? log10(att.x0) : 0) : att.x0;
      PLFLT x1=(att.logx) ? ((att.x1>0) ? log10(att.x1) : 0) : att.x1;
      PLFLT y0=(att.logy) ? ((att.y0>0) ? log10(att.y0) : 0) : att.y0;
      PLFLT y1=(att.logy) ? ((att.y1>0) ? log10(att.y1) : 0) : att.y1;
      PLFLT z0=(att.logz) ? ((att.z0>0) ? log10(att.z0) : 0) : att.z0;
      PLFLT z1=(att.logz) ? ((att.z1>0) ? log10(att.z1) : 0) : att.z1;
      plw3d(1.,1.,1., x0,x1, y0,y1, z0,z1,
	    att.alt, att.az);
      // plw3d(1.,1.,1., att.x0,att.x1, att.y0,att.y1, att.z0,att.z1,
      // 	    att.alt, att.az);
      pllab("","", att.title);
      plbox3(ox.c_str(), att.xlab, att.xtick, att.nxsub,
	     oy.c_str(), att.ylab, att.ytick, att.nysub,
	     oz.c_str(), att.zlab, att.ztick, att.nzsub );
      // plbox3( "bcnstu", att.xlab, att.xtick, att.nxsub,
      // 	      "bcnstu", att.ylab, att.ytick, att.nysub,
      // 	      "bcdmnstuv", att.zlab, 0.0, 0 );
      plschr(0,1);
    };
    void draw_graph3d(const std::vector<PLFLT>& x,
		      const std::vector<PLFLT>& y,
		      const std::vector<PLFLT>& z, int n=0) {
      if(n == 0) n = (int)x.size();
      draw_graph3d(x.data(),y.data(),z.data(),n);
    }
    void draw_graph3d(const PLFLT* x, const PLFLT* y, const PLFLT* z, int n) {
      const PLFLT *px=x,*py=y,*pz=z;
      if(att.logx) {
	_lx.resize(n);
	for(int j=0; j<n; j++) _lx[j] = (x[j]>0) ? log10(x[j]) : 0;
	px=&_lx[0];
      }
      if(att.logy) {
	_ly.resize(n);
	for(int j=0; j<n; j++) _ly[j] = (y[j]>0) ? log10(y[j]) : 0;
	py=&_ly[0];
      }
      if(att.logz) {
	_lz.resize(n);
	for(int j=0; j<n; j++) _lz[j] = (z[j]>0) ? log10(z[j]) : 0;
	pz=&_lz[0];
      }
      if( att.lwid ) {
	plcol0(att.lcol);
	plwidth(att.lwid);
	pllsty(att.lsty);
	plline3(n,px,py,pz);
      }
      if( att.symb ) {
	plcol0(att.scol);
	plssym(0,att.ssiz);
	plpoin3(n,px,py,pz,att.symb);
      }
    }
    void auto_scale3d(const std::vector<PLFLT>& x,
		      const std::vector<PLFLT>& y,
		      const std::vector<PLFLT>& z, int n=0) {
      calc_scale(x, att.x0, att.x1, att.ascx, n);
      calc_scale(y, att.y0, att.y1, att.ascy, n);
      calc_scale(z, att.z0, att.z1, att.ascz, n);
    }
    void auto_rescale3d(const std::vector<PLFLT>& x,
			const std::vector<PLFLT>& y,
			const std::vector<PLFLT>& z, int n=0) {
      PLAtt att2;      
      calc_scale(x, att2.x0, att2.x1, att.ascx, n);
      calc_scale(y, att2.y0, att2.y1, att.ascy, n);
      calc_scale(z, att2.z0, att2.z1, att.ascz, n);
      if( att2.x0 < att.x0 ) att.x0 = att2.x0;
      if( att2.x1 > att.x1 ) att.x1 = att2.x1;
      if( att2.y0 < att.y0 ) att.y0 = att2.y0;
      if( att2.y1 > att.y1 ) att.y1 = att2.y1;
      if( att2.z0 < att.z0 ) att.z0 = att2.z0;
      if( att2.z1 > att.z1 ) att.z1 = att2.z1;
    }
    void plot3d(const std::vector<PLFLT>& x,
		const std::vector<PLFLT>& y,
		const std::vector<PLFLT>& z, int sub=0, int n=0) {
      auto_scale3d(x,y,z,n);
      draw_box3d(sub);
      draw_graph3d(x,y,z,n);
    }
    void alloc_mesh(int nx, int ny) {
      if(_mesh_z==0) {
	plAlloc2dGrid(&_mesh_z, nx, ny);
	for(int j=0; j<nx; j++) for(int k=0; k<ny; k++) _mesh_z[j][k]=0;
      }
    }
    void free_mesh(int nx, int ny) {
      if(_mesh_z!=0) {plFree2dGrid(_mesh_z, nx, ny); _mesh_z=0;}
    }
    void set_mesh(int j, int k, PLFLT z) {
      if(att.logz) {
	_mesh_z[j][k] = (z>0) ? log10(z) : 0;
      } else {
	_mesh_z[j][k] = z;
      }
    }
    PLFLT get_mesh(int j, int k) {return _mesh_z[j][k];}
    void draw_mesh(const std::vector<PLFLT> &x, const std::vector<PLFLT> &y,
		   bool color=1) {
      draw_mesh(x.data(),y.data(),x.size(),y.size(),color);
    }
    void draw_mesh(const PLFLT* x, const PLFLT* y, int nx, int ny,
		   bool color) {
      plcol0(att.lcol);
      plwidth(att.lwid);
      pllsty(att.lsty);
      if(color) {
	plspal1("cmap1_blue_red.pal", 1);
	plmesh(x,y,(const PLFLT **)_mesh_z, nx,ny, DRAW_LINEXY|MAG_COLOR);
	plspal1("",1);
      } else {
	plmesh(x,y,(const PLFLT **)_mesh_z, nx,ny, DRAW_LINEXY);
      }
    }
    void alloc_grid(int nx, int ny,
		    PLFLT xmin, PLFLT xmax, PLFLT ymin, PLFLT ymax) {
      if(_cgrid2.xg==0) plAlloc2dGrid(&_cgrid2.xg, nx, ny);
      if(_cgrid2.yg==0) plAlloc2dGrid(&_cgrid2.yg, nx, ny);
      _cgrid2.nx = nx;
      _cgrid2.ny = ny;
      PLFLT dx = (xmax-xmin)/(nx-1);
      PLFLT dy = (ymax-ymin)/(ny-1);
      for (int i = 0; i < nx; i++ ) {
        for (int j = 0; j < ny; j++ ) {
	  _cgrid2.xg[i][j] = xmin + dx*i;
	  _cgrid2.yg[i][j] = ymin + dy*j;
        }
      }
    }
    void free_grid(int nx, int ny) {
      if(_cgrid2.xg!=0) {plFree2dGrid(_cgrid2.xg, nx, ny); _cgrid2.xg=0;}
      if(_cgrid2.yg!=0) {plFree2dGrid(_cgrid2.yg, nx, ny); _cgrid2.yg=0;}
    }
    void calc_min_max(const PLFLT* x, int n, PLFLT& min, PLFLT& max) {
      min=x[0]; max=x[0];
      for(int j=1; j<n; j++) {
	if(x[j] < min) min=x[j];
	if(x[j] > max) max=x[j];
      }
    }
    void draw_contour(const std::vector<PLFLT> &x, const std::vector<PLFLT> &y,
		      bool color) {
      draw_contour(x.data(),y.data(),x.size(),y.size(),color);
    }
    void draw_contour(const PLFLT* x, const PLFLT* y, int nx, int ny,
		      bool color) {
      if(color) {
	plspal1("cmap1_blue_red.pal", 1);
      } else {
	plspal1("cmap1_gray.pal", 1);
      }
      plwind(att.x0,att.x1, att.y0,att.y1);
      PLFLT xmin,xmax,ymin,ymax;
      calc_min_max(x,nx,xmin,xmax);
      calc_min_max(y,ny,ymin,ymax);
      std::vector<PLFLT> shedge(att.grad+1);
      PLFLT z0=(att.logz) ? ((att.z0>0) ? log10(att.z0) : 0) : att.z0;
      PLFLT z1=(att.logz) ? ((att.z1>0) ? log10(att.z1) : 0) : att.z1;
      PLFLT fill_width=2, dz=(z1-z0)/att.grad;
      for (int j=0; j < att.grad+1; j++) {shedge[j] = z0 + dz*j;}
      // PLFLT fill_width=2, dz=(att.z1-att.z0)/att.grad;
      // for (int j=0; j < att.grad+1; j++) {shedge[j] = att.z0 + dz*j;}
      alloc_grid(nx, ny, xmin, xmax, ymin, ymax);
      plshades((const PLFLT **)_mesh_z, nx,ny, NULL,
	       xmin, xmax, ymin, ymax,
	       shedge.data(), att.grad+1, fill_width,
	       0, 0, plfill, 0, pltr2, (void *)&_cgrid2);
      draw_box_sub(0);
      plschr(0,0.6); plsmaj(0,0.5); plsmin(0,0.5);//set smaller text and ticks
#if 1 // simple color bar
      PLFLT aspect = 36.0*_nx/_ny;
      PLFLT x0 = 0.95-0.03*_nx/_ny;
      PLFLT x1 = x0 + 0.015;
      plvpas(x0, x1, 0, 1, aspect);
      plwind(0, 1, z0, z1);
      //      plwind(0, 1, att.z0, att.z1);
      PLFLT xg[5] = {0,1,1,0,0};
      PLFLT yg[5] = {z0,z0,z1,z1,z0};
      //      PLFLT yg[5] = {att.z0,att.z0,att.z1,att.z1,att.z0};
      plgradient(5,xg,yg,90);
      plcol0(att.lcol);
      if(att.logz) {
	plbox("bc",0, 0, "bcmstvl", 0, 0);
      } else {
	plbox("bc",0, 0, "bcmstv", 0, 0);
      }
#else // the following way is too complicated so not used
      const int NAXIS 1
      PLINT n_axis_opts = NAXIS;
      const char *axis_opts[] = {"bcvtm"};
      PLINT num_values[NAXIS];
      PLFLT colorbar_width, colorbar_height;
      PLFLT *values[NAXIS];
      PLFLT axis_ticks[NAXIS] = {0};
      PLINT axis_subticks[NAXIS] = {0};
      PLINT n_labels = NAXIS;
      PLINT label_opts[] = {PL_COLORBAR_LABEL_BOTTOM};
      const char *labels[] = {""};
      num_values[0] = att.grad + 1;
      values[0] = shedge.data();
      plcolorbar(&colorbar_width, &colorbar_height,
		 PL_COLORBAR_SHADE | PL_COLORBAR_SHADE_LABEL,
		 //		 PL_COLORBAR_GRADIENT,
		 PL_POSITION_VIEWPORT | PL_POSITION_RIGHT,
		 0.01,-0.02, // x,y offset
		 0.03, 0.99, // x,y length
		 0,  // bg color (white)
		 15, // box color (black)
		 1,  // box style
		 0.0, // color of cap at the bottom of box
		 0.0, // color of cap at the top of box
		 cont_color, cont_width,
		 n_labels, label_opts, labels,
		 n_axis_opts, axis_opts,
		 axis_ticks, axis_subticks,
		 num_values, (const PLFLT * const *)values);
#endif
      plschr(0,1); plsmaj(0,1.0); plsmin(0,1.0); //reset text and tick
      plspal1("",1);
      free_grid(nx, ny);
    }
  };//-- class PLPlot

}//-- namespace thl

#endif //THL_PLPLOT_HH
