// thl : tiny header-only library
//
// LsFit : class to make a fitting to the data by least square method
//
// -std=c++11
//
#ifndef THL_LSFIT_HH
#define THL_LSFIT_HH

#include <cstdio>
#include <cmath>
#include <cfloat>
#include "SqMatrix.hh"

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

#define VD std::vector<double>  // undefined at the end of this header file

namespace thl {
  class LsFit { // data fitting by the least square method
  private:
    VD _x; // x-axis data to fit
    VD _y; // y-axis data to fit
    VD _z; // z-axis data to fit
    VD _fx; // x-axis array to draw the fitting result
    VD _fy; // y-axis array to draw the fitting result
    Vec<double> _c; // coefficients to fit the data
    enum Type {Lin,Quad,Gaus,Exp,Log,Plane,Sin,Circ} _type;
  public:
    LsFit(void) : _type(Lin) {}
    size_t ndata(void) {return _x.size();}
    size_t dim() {return _c.dim();}  // dimension of coefficient
    void set_range(VD &x, VD &y, double x0, double x1) {
      if(x0 < x1) {
	_x.clear(); _y.clear();
	for(size_t j=0; j<x.size(); j++) {
	  if(x[j] >= x0 && x[j] <= x1) {
	    _x.push_back(x[j]);
	    _y.push_back(y[j]);
	  }
	}
	x=_x; y=_y;
      } else {
	_x=x; _y=y;
      }
    }
    double func(double x, double y=0) {
      if(_type==Lin)  return func_lin(x);
      if(_type==Quad) return func_quad(x);
      if(_type==Gaus) return func_gaus(x);
      if(_type==Exp)  return func_exp(x);
      if(_type==Log)  return func_log(x);
      if(_type==Plane)return func_plane(x,y);
      if(_type==Sin) return func_sin(x);
      if(_type==Circ) return func_circ(x);
      return 0;
    }
    void set_fx(size_t n=100) {
      double min=_x[0],max=_x[0];
      for(auto a:_x) {if(a<min) min=a; if(a>max) max=a;}
      double dx = (max-min)*1.01/(double)n;
      _fx.resize(n);
      for(size_t j=0; j < n; j++) _fx[j] = min+dx*j;
    }
    VD& fx(void) {
      if(_fx.size()==0) set_fx();
      return _fx;
    }
    VD& fy(void) {
      if(_fx.size()==0) set_fx();
      _fy.resize(_fx.size());
      for(size_t j=0; j<_fy.size(); j++) _fy[j] = func(_fx[j]);
      return _fy;
    }
    double chisq() {
      double chi2 = 0;
      if(_type==Circ) { // estimate by the difference of radius
	Vec<double> c(2); c[0]=_c[0]; c[1]=_c[1]; // center position
	for(size_t j=0; j < _y.size(); j++) {
	  Vec<double> p(2); p[0]=_x[j]; p[1]=_y[j]; // data position
	  double absC2 = std::abs(_c[2]);
	  if(absC2 > DBL_MIN) {
	    chi2 += std::pow((p-c).norm()-_c[2],2)/absC2;
	  }
	}
      } else if(_type==Plane) {
	for(size_t j=0; j < _z.size(); j++) {
	  double Z = func_plane(_x[j],_y[j]);
	  double absZ = std::abs(Z);
	  if(absZ > DBL_MIN) {
	    chi2 += std::pow(_z[j]-Z,2)/absZ;
	  }
	}
      } else {
	for(size_t j=0; j < _y.size(); j++) {
	  double Y = func(_x[j]);
	  double absY = std::abs(Y);
	  if(absY > DBL_MIN) {
	    chi2 += std::pow(_y[j]-Y,2)/absY;
	  }
	}
      }
      return chi2;
    }
    Vec<double> coef(void) {return _c;}
    double coef(size_t j) {
      if(j<0 && j>=_c.dim()) {
	fprintf(stderr,"coef out of range\n"); return 0;
      }
      return _c[j];
    }
    int ndf() { // num of degree of freedom
      return (ndata() > _c.dim()) ? ndata()-_c.dim() : 1;
    }
    double operator() (size_t j) { return coef(j);}
  //-----------------------------------------------------------------------
  // Linear Fitting :  y = c0 + c1*x
  //
    int calc_lin(VD x, VD y, double x0=0, double x1=0) {
      if(x.size() != y.size()) {fprintf(stderr,"size of x != y\n"); return -1;}
      _type=Lin; _c.resize(2); _fx.clear();
      set_range(x,y, x0,x1);
      double sx=0,sy=0,sx2=0,sxy=0, size=x.size();
      for(size_t j=0; j<x.size(); j++) {
	sx += x[j];
	sy += y[j];
	sx2 += x[j]*x[j];
	sxy += x[j]*y[j];
      }
      Vec<double> v(2); v[0]=sy; v[1]=sxy;
      Mat<double> m(2);
      m[0][0]=size; m[0][1]=sx;
      m[1][0]=sx;   m[1][1]=sx2;
      _c = m.inv() * v;
      return 0;
    }
    double func_lin(double x) {return _c[0] + _c[1]*x;}
  //-----------------------------------------------------------------------
  // Quadratic Fitting :  y = c0 + c1*x + c2*x^2
  //
    int calc_quad(VD x, VD y, double x0=0, double x1=0) {
      if(x.size() != y.size()) {fprintf(stderr,"size of x != y\n"); return -1;}
      _type=Quad; _c.resize(3); _fx.clear();
      set_range(x,y, x0,x1);
      double sx=0,sy=0,sx2=0,sx3=0,sx4=0,sxy=0,sx2y=0,size=x.size();
      for(size_t j=0; j<x.size(); j++) {
	double xx = x[j]*x[j];
	sx += x[j];
	sy += y[j];
	sx2 += xx;
	sx3 += xx*x[j];
	sx4 += xx*xx;
	sxy += x[j]*y[j];
	sx2y += xx*y[j];
      }
      Vec<double> v(3); v[0]=sy; v[1]=sxy; v[2]=sx2y;
      Mat<double> m(3);
      m[0][0]=size; m[0][1]=sx;  m[0][2]=sx2;
      m[1][0]=sx;   m[1][1]=sx2; m[1][2]=sx3;
      m[2][0]=sx2;  m[2][1]=sx3; m[2][2]=sx4;
      _c = m.inv() * v;
      return 0;
    }
    double func_quad(double x) {return _c[0] + _c[1]*x + _c[2]*x*x;}
  //-----------------------------------------------------------------------
  // Gaussian Fitting :  y = c0*exp(-(x-c1)^2/2*c2^2)
  // c0:amp, c1:mean, c2:sigma        
  //
    int calc_gaus(VD x, VD y, double x0=0, double x1=0) {
      if(x.size() != y.size()) {fprintf(stderr,"size of x != y\n"); return -1;}
      _type=Gaus; _c.resize(3); _fx.clear();
      set_range(x,y, x0,x1);
      VD x2,y2;
      for(size_t j=0; j<x.size(); j++) {
	if(y[j]>0) {x2.push_back(x[j]); y2.push_back(std::log(y[j]));}
      }
      LsFit qf; qf.calc_quad(x2, y2, x0, x1);
      if(qf(2) >= 0 || -qf(2) <= DBL_MIN || ! std::isfinite(qf(2))) {
	printf("LsFit::calc_gaus: used statistics method\n");
	calc_statistics(x,y);
	return 1;
      } else {// use quadratic fitting result
	_c[0] = std::exp(qf(0)-qf(1)*qf(1)/(qf(2)*4));
	_c[1] = -qf(1)/(qf(2)*2);
	_c[2] = std::sqrt(1./(-qf(2)*2));
	return 0;
      }
    }
    int calc_statistics(VD x, VD y, double x0=0, double x1=0) {
      if(x.size() != y.size()) {fprintf(stderr,"size of x != y\n"); return -1;}
      _type=Gaus; _c.resize(3); _fx.clear();
      set_range(x,y, x0,x1);
      double sum=0,ssum=0,n=0;
      for(size_t j=0; j<x.size(); j++) {
	sum += x[j]*y[j];
	ssum += x[j]*x[j]*y[j];
	n += y[j];
      }
      double mean = (n>0) ? sum/n : 0.;
      double rms = (n>0) ? std::sqrt((ssum-sum*sum/n)/n) : 0;
      double amp=0; n=0;
      for(size_t j=0; j<y.size(); j++) {
	if(x[j] > mean-rms && x[j] < mean+rms) {amp += y[j]; n++;}
      }
      _c[0] = (n>0) ? 1.1*amp/n : 0;
      _c[1] = mean;
      _c[2] = rms;
      return 0;
    }
    double func_gaus(double x) {
      return _c[0]*(std::exp(-(x-_c[1])*(x-_c[1])/(_c[2]*_c[2]*2)));
    }
  //-----------------------------------------------------------------------
  // Exponential Fitting : y = c0*exp(c1*x)
  //
    int calc_exp(VD x, VD y, double x0=0, double x1=0) {
      if(x.size() != y.size()) {fprintf(stderr,"size of x != y\n"); return -1;}
      _type=Exp; _c.resize(2); _fx.clear();
      set_range(x,y, x0,x1);
      VD x2,y2;
      for(size_t j=0; j<x.size(); j++) {
	bool q = (x0>=x1) ? (y[j]>0) : (x[j]>=x0 && x[j]<=x1 && y[j]>0);
	if(q) {x2.push_back(x[j]); y2.push_back(std::log(y[j]));}
      }
      LsFit lf; lf.calc_lin(x2, y2, x0, x1);
      _c[0] = std::exp(lf(0));
      _c[1] = lf(1);
      return 0;
    }
    double func_exp(double x) {return _c[0]*std::exp(_c[1]*x);}
  //-----------------------------------------------------------------------
  // Logarithm Fitting : y = c0 + log(c1+x)
  //
    int calc_log(VD x, VD y, double x0=0, double x1=0) {
      if(x.size() != y.size()) {fprintf(stderr,"size of x != y\n"); return -1;}
      _type=Log; _c.resize(2); _fx.clear();
      set_range(x,y, x0,x1);
      VD x2,y2;
      for(size_t j=0; j<x.size(); j++) {
	x2.push_back(x[j]); y2.push_back(std::exp(y[j]));
      }
      LsFit lf; lf.calc_lin(x2, y2, x0, x1);
      printf("lf(0)=%f lf(1)=%f\n",lf(0),lf(1));
      _c[0] = (lf(1)>0) ? std::log(lf(1)) : 0;
      _c[1] = (lf(1)>0) ? lf(0)/lf(1) : 0;
      return 0;
    }
    double func_log(double x) {return _c[0]+std::log(_c[1]+x);}
  //-----------------------------------------------------------------------
  // Plane Fitting : z = c0 + c1*x + c2*y
  //
    int calc_plane(VD x, VD y, VD z) {
      if(x.size() != y.size()) {fprintf(stderr,"size of x != y\n"); return -1;}
      if(x.size() != z.size()) {fprintf(stderr,"size of x != z\n"); return -1;}
      _type=Plane; _c.resize(3); _fx.clear();
      _x=x; _y=y; _z=z;
      double sx=0,sy=0,sz=0,sxx=0,syy=0,szz=0,sxy=0,sxz=0,syz=0;
      double size = x.size();
      for(size_t j=0; j<x.size(); j++) {
	sx += x[j];
	sy += y[j];
	sz += z[j];
	sxx += x[j]*x[j];
	syy += y[j]*y[j];
	szz += z[j]*z[j];
	sxy += x[j]*y[j];
	sxz += x[j]*z[j];
	syz += y[j]*z[j];
      }
      Vec<double> v(3); v[0]=sxz; v[1]=syz; v[2]=sz;
      Mat<double> m(3);
      m[0][0]=sx;   m[0][1]=sxx; m[0][2]=sxy;
      m[1][0]=sy;   m[1][1]=sxy; m[1][2]=syy;
      m[2][0]=size; m[2][1]=sx;  m[2][2]=sy;
      _c = m.inv() * v;
      return 0;
    }
    double func_plane(double x, double y) {return _c[0] + _c[1]*x + _c[2]*y;}

  //-----------------------------------------------------------------------
  // Sinusoidal Fitting : with known frequency
  // y = c0 + c1*sin(2*PI*c3*x) + c2*cos(2*PI*c3*x)
  //   = c0 + c1*X + c2*Y  (-> calculated by plane fitting)
  // c0 : y offset
  // c1 : amplitude of sine
  // c2 : amplitude of cosine
  // c3 : frequency (this coefficient is provided by user)
  //
    int calc_sin(VD x, VD y, double freq, double x0=0, double x1=0) {
      if(x.size() != y.size()){fprintf(stderr,"size of x != y\n"); return -1;}
      _type=Sin; _c.resize(4); _fx.clear();
      if(freq==0) {
	_c.set_all(0);
      } else {
	set_range(x,y, x0,x1);
	LsFit pf; // plane fitting
	VD X(x.size()),Y(x.size());
	int ntry=5, nbest=0;
	double df=freq*1e-6, chi2_min=0;
	Vec<double> c_best(_c.dim());
	for(int n=-ntry; n<ntry; n++) {
	  double f=freq+df*n;
	  double omega = f*M_PI*2;
	  for(size_t j=0; j < x.size(); j++) {
	    X[j] = std::sin(omega*x[j]);
	    Y[j] = std::cos(omega*x[j]);
	  }
	  pf.calc_plane(X,Y,y);
	  double chi2 = pf.chisq();
	  if(n == -ntry) chi2_min = chi2;
	  if(chi2 <= chi2_min && chi2 != 0) {
	    chi2_min = chi2; nbest = n;
	    c_best[0] = pf.coef(0);
	    c_best[1] = pf.coef(1);
	    c_best[2] = pf.coef(2);
	    c_best[3] = f;
	  }
	  //	  printf("%3d chi2=%e f=%f\n",n,chi2,f);
	  _c = c_best;
	}
	printf("calc_sin(): nbest=%d chi2_min=%f fbest=%f\n"
	       ,nbest,chi2_min,c_best[3]);
      }
      return 0;
    }
    double func_sin(double x) {
      double omega = M_PI*2*_c[3];
      return _c[0] + _c[1]*std::sin(omega*x) + _c[2]*std::cos(omega*x);
    }

  //-----------------------------------------------------------------------
  // Circular Fitting : (x-c0)**2 + (y-c1)**2 = c2**2
  //                c0:dx, c1:dy, c2:r
  //
    int calc_circ(VD x, VD y) {
      if(x.size() != y.size()) {fprintf(stderr,"size of x != y\n"); return -1;}
      _type=Circ; _c.resize(3); _fx.clear();
      set_range(x,y, 0,0);
      double sx=0,sy=0,sx2=0,sy2=0,sxy=0,size=x.size();
      double sx3_xy2=0,sx2y_y3=0,sx2_y2=0;
      for(size_t j=0; j<x.size(); j++) {
	double xx = x[j]*x[j];
	double yy = y[j]*y[j];
	double xx_yy = xx + yy;
	sx += x[j];
	sy += y[j];
	sx2 += xx;
	sy2 += yy;
	sxy += x[j]*y[j];
	sx3_xy2 += (xx_yy)*x[j];
	sx2y_y3 += (xx_yy)*y[j];
	sx2_y2  += xx_yy;
      }
      Vec<double> v(3);
      v[0]=-sx3_xy2; v[1]=-sx2y_y3; v[2]=-sx2_y2;
      Mat<double> m(3);
      m[0][0]=sx2; m[0][1]=sxy; m[0][2]=sx;
      m[1][0]=sxy; m[1][1]=sy2, m[1][2]=sy;
      m[2][0]=sx;  m[2][1]=sy;  m[2][2]=size;
      Vec<double> a(3);
      a = m.inv() * v;
      _c[0] = -a[0]/2;
      _c[1] = -a[1]/2;
      double r = _c[0]*_c[0] + _c[1]*_c[1] - a[2];
      _c[2] = (r > 0) ? std::sqrt(r) : 0;
      return 0;
    }
    double func_circ(double x) {
      double t = std::acos((x-_c[0])/_c[2]);
      return _c[2]*std::sin(t) + _c[1];
    }
    void func_circ(double rad, double &x, double &y) {
      x = _c[2]*std::cos(rad) + _c[0];
      y = _c[2]*std::sin(rad) + _c[1];
    }
  };

}//-- namespace thl

#undef VD

#endif // THL_LSFIT_HH
