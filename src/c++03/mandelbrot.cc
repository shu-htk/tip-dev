#include <complex>
#include <fstream>
#include "thl/ArgOpt.hh"

int divergence_thresh(int ntry, std::complex<double> c) {
  std::complex<double> z(0,0);
  for(int n=0; n < ntry; n++) {
    if(std::abs(z) > 2) return n;
    z = z*z + c;
  }
  return ntry;
}

int main(int argc, const char *argv[]) {
  thl::ArgOpt arg(argc,argv,"ndiv:,ntry:,xr:,yr:");

  int ndiv = arg.opt_def_stoi("ndiv","500");  // num of divide of x and y
  int ntry = arg.opt_def_stoi("ntry","1000"); // num of try to find divergence
  thl::StrSplit xr(arg.opt_def("xr","-2.0:0.5"),":"); // x-range
  thl::StrSplit yr(arg.opt_def("yr","-1.3:1.3"),":"); // y-range
  double x0 = xr.stof(0);
  double x1 = xr.stof(1);
  double y0 = yr.stof(0);
  double y1 = yr.stof(1);
  double dx = (x1-x0)/(double)ndiv;
  double dy = (y1-y0)/(double)ndiv;

  std::ofstream ofs("mandelbrot.dat");
  if(ofs) {
    for(int iy = 0; iy < ndiv; iy++) {
      for(int ix = 0; ix < ndiv; ix++) {
        double x = x0 + dx*(double)ix;
        double y = y0 + dy*(double)iy;
        std::complex<double> c(x,y);
        ofs << x << " " << y << " "
            << divergence_thresh(ntry,c) << std::endl;
      }
      ofs << std::endl;
    }
  }
  return 0;
}

