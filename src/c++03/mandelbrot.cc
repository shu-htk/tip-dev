// mandelbrot : make a Mandelbrot set with specified size and range
//
// c++03
//
#include <complex>
#include <fstream>
#include "thl/ArgOpt.hh"

int divergence_thresh(std::complex<double> c) {
  std::complex<double> z(0,0);
  for(int n=0; n < 500; n++) {
    if(std::abs(z) > 2) {return n;}
    z = z*z + c;
  }
  return -100;
}

int main(int argc, const char *argv[]) {
  thl::ArgOpt arg(argc,argv,"n:,xr:,yr:");

  int n = arg.opt_def_stoi("n","1000");
  thl::StrSplit xr(arg.opt_def("xr","-2.0:0.5"),":");
  thl::StrSplit yr(arg.opt_def("yr","-1.3:1.3"),":");
  double x0 = xr.stof(0);
  double x1 = xr.stof(1);
  double y0 = yr.stof(0);
  double y1 = yr.stof(1);
  double dx = (x1-x0)/(double)n;
  double dy = (y1-y0)/(double)n;

  std::ofstream ofs("mandelbrot.dat");
  if(ofs) {
    for(int iy = 0; iy < n; iy++) {
      for(int ix = 0; ix < n; ix++) {
	double x = x0 + dx*(double)ix;
	double y = y0 + dy*(double)iy;
	std::complex<double> c(x,y);
	ofs << x << " " << y << " "
	    << divergence_thresh(c) << std::endl;
      }
      ofs << std::endl;
    }
  }
  return 0;
}

