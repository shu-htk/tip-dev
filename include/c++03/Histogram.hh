// thl : tiny header-only library
//
// Hist1D : class to make 1-dimensional histogram
// Hist2D : class to make 2-dimensional histogram
//
// -std=c++03
//
#ifndef THL_HISTOGRAM_HH
#define THL_HISTOGRAM_HH

#include <vector>

namespace thl {

  class Hist1D {
  private:
    std::vector<unsigned long> _bin;
    double _x0,_x1,_xwid;
    unsigned long _nentry;
  public:
    Hist1D() {}
    Hist1D(int nbin, double x0, double x1) {
      init(nbin,x0,x1);
    }
    void init(int nbin, double x0, double x1) {
      _nentry=0;
      _x0=x0; _x1=x1;
      _xwid=(_x1-_x0)/nbin;
      _bin.resize(nbin,0);
    }
    void fill(double x) {
      if(_x0<x && x<_x1) {
	int ix = (int)((x-_x0)/_xwid);
	_bin[ix]++;
	_nentry++;
      }
    }
    unsigned long nentry() {return _nentry;}
    int nbin() {return (int)_bin.size();}
    double x0() {return _x0;};
    double x1() {return _x1;};
    double xwid() {return _xwid;}
    double x(int ix) {return _x0+_xwid*ix+_xwid/2;}
    double x_low(int ix) {return _x0+_xwid*ix;}
    double x_up(int ix) {return _x0+_xwid*(ix+1);}
    double y(int ix) {return (double)_bin[ix];}
  };//-- class Hist1D

  class Hist2D {
  private:
    std::vector<std::vector<unsigned long> > _bin;
    double _x0,_x1,_y0,_y1,_xwid,_ywid;
    unsigned long _nentry;
  public:
    Hist2D() {}
    Hist2D(int nx, int ny, double x0, double x1, double y0, double y1) {
      init(nx,ny,x0,x1,y0,y1);
    }
    void init(int nx, int ny, double x0, double x1, double y0, double y1) {
      _nentry=0;
      _x0=x0; _x1=x1; _y0=y0; _y1=y1;
      _xwid=(_x1-_x0)/nx; _ywid=(_y1-_y0)/ny;
      _bin.resize(nx);
      for(int j=0; j<nx; j++) _bin[j].resize(ny,0);
    }
    void fill(double x, double y) {
      if(_x0<x && x<_x1 && _y0<y && y<_y1) {
	int ix = (int)((x-_x0)/_xwid);
	int iy = (int)((y-_y0)/_ywid);
	_bin[ix][iy] ++;
	_nentry++;
      }
    }
    unsigned long nentry() {return _nentry;}
    int nx() {return (int)_bin.size();}
    int ny() {return (int)_bin[0].size();}
    double x0() {return _x0;};
    double x1() {return _x1;};
    double y0() {return _y0;};
    double y1() {return _y1;};
    double xwid() {return _xwid;}
    double ywid() {return _ywid;}
    double x(int ix) {return _x0+_xwid*ix+_xwid/2;}
    double y(int iy) {return _y0+_ywid*iy+_ywid/2;}
    double z(int ix, int iy) {return (double)_bin[ix][iy];}
    double x_low(int ix) {return _x0+_xwid*ix;}
    double x_up(int ix) {return _x0+_xwid*(ix+1);}
    double y_low(int iy) {return _y0+_ywid*iy;}
    double y_up(int iy) {return _y0+_ywid*(iy+1);}
  };//-- class Hist2D

}//-- namespace thl

#endif //THL_HISTOGRAM_HH
