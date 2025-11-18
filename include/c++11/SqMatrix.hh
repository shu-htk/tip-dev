// thl : tiny header-only library
//
// Vec : class of the vector as linear algebra 
// Mat : class of the square matrix as linear algebra
//
// c++11
//
#ifndef THL_SQ_MATRIX_HH
#define THL_SQ_MATRIX_HH

#include <cstdio>
#include <cmath>
#include <vector>

#define tcT template<class T> //local macro (undefined at the end of this file)

namespace thl {
  tcT class Vec {
  private:
    std::vector<T> _v;
  public:
    Vec(void) {}
    Vec(size_t n, T x=0) : _v(n,x) {}
    size_t dim(void) {return _v.size();} // dimension
    void resize(size_t n, T x=0) {_v.resize(n,x);}
    std::vector<T> &data() {return _v;}

    void set_all(T x) { // set all element x
//    for(size_t j=0; j<dim(); j++) {_v[j] = x;}
      for(auto &&v : _v) {v=x;}
    }
    void set_single(size_t n, T x) { // set n-th element x, others are zero
      if(n >= dim()) {
	fprintf(stderr,"Vec::set_single(): out of range\n");
      } else {
	for(size_t j=0; j<dim(); j++) {
	  _v[j] = (j==n) ? x : 0;
	}
      }
    }
    T &operator [](size_t j) { // reference of j-th element T
      if(j >= dim()) {
	fprintf(stderr,"Vec::[size_t]: out of range\n");
	return _v[0];
      } else {
	return _v[j];
      }
    }
    T norm(void) {return std::sqrt(square());}

    T square(void) {
      T s=0;
//    for(size_t j=0; j<dim(); j++) {s += _v[j]*_v[j];}
      for(auto &&v : _v) {s += v*v;}
      return s;
    }
    Vec<T> &flip_sign(void) {
//    for(size_t j=0; j<dim(); j++) {_v[j]=-_v[j];}
      for(auto &&v : _v) {v = -v;}
      return *this;
    }
    Vec<T> &operator +=(Vec<T> &v) {
      if(v.dim() != dim()) {
	fprintf(stderr,"Vec::+=: different dimensions\n");
      } else {
	for(size_t j=0; j<dim(); j++) _v[j] += v[j];
      }
      return *this;
    }
    Vec<T> &operator -=(Vec<T> &v) {
      if(v.dim() != dim()) {
	fprintf(stderr,"Vec::-=: different dimensions\n");
      } else {
	for(size_t j=0; j<dim(); j++) _v[j] -= v[j];
      }
      return *this;
    }
    Vec<T> &operator *=(T &x) {
//    for(size_t j=0; j<dim(); j++) {_v[j] *= x;}
      for(auto &&v : _v) {v *= x;}
      return *this;
    }
    Vec<T> &operator /=(T &x) {
//    for(size_t j=0; j<dim(); j++) {_v[j] /= x;}
      for(auto &&v : _v) {v /= x;}
      return *this;
    }
    T dot(Vec<T> &v) { // inner product
      T s=0;
      if(v.dim() != dim()) {
	fprintf(stderr,"Vec::dot: different dimensions\n");
      } else {
	for(size_t j=0; j<dim(); j++) s += _v[j]*v[j];
      }
      return s;
    }
    Vec<T> cross(Vec<T> &v) { // outer product
      if(dim() != 3) {
	fprintf(stderr,"Vec::cross: dimension should be 3\n"); return *this;
      }
      Vec<T> x;
      x[0] = _v[1]*v[2] - _v[2]*v[1];
      x[1] = _v[2]*v[0] - _v[0]*v[2];
      x[2] = _v[0]*v[1] - _v[1]*v[0];
      return x;
    }
    void print(void) {
      //      for(size_t j=0; j<dim(); j++) {printf(" %g",_v[j]);}
      for(auto &&v : _v) {printf(" %g",v);}
    }
    
    T back(void) {return _v.back();}
    T* begin() {return &_v[0];}
    T* end() {return &_v[_v.dim()];}
  }; //class Vec

  tcT inline Vec<T> operator -(Vec<T> v) {return v.flip_sign();}
  tcT inline Vec<T> operator +(Vec<T> v1, Vec<T> v2) {return v1 += v2;}
  tcT inline Vec<T> operator -(Vec<T> v1, Vec<T> v2) {return v1 -= v2;}
  tcT inline Vec<T> operator *(Vec<T> v, T x) {return v *= x;}
  tcT inline Vec<T> operator *(T x, Vec<T> v) {return v *= x;}
  tcT inline Vec<T> operator /(Vec<T> v, T x) {return v /= x;}
  tcT inline T operator *(Vec<T> v1, Vec<T> v2) {return v1.dot(v2);}

  //------------------------------------------------------------
  tcT class Mat {
  private:
    std::vector<Vec<T> > _m;
  public:
    Mat(void) {}
    Mat(size_t n, T x=0) : _m(n,Vec<T>(n,x)) {}
    size_t dim(void) {return _m.size();} // dimension
    void resize(size_t n, T x=0) {_m.resize(n,Vec<T>(n,x));}
    std::vector<Vec<T> > &data(void) {return _m;}

    void set_all(T x) { // set all element x
//      for(size_t j=0; j<dim(); j++) {_m[j].set_all(x);}
      for(auto &&m : _m) {m.set_all(x);}
    }
    void set_diagonal(T x) { // set diagonal element x, others zero
      for(size_t j=0; j<dim(); j++) {_m[j].set_single(j,x);}
    }
    void set_unit(void) {set_diagonal(1);}
    
    Mat<T> &operator =(T x) { // set diagonal element x, others zero
      set_diagonal(x);
      return *this;
    }
    Vec<T> &operator [](size_t j) {  // reference of j-th element Vec<T>
      if(j >= dim()) {
	fprintf(stderr,"Mat::[size_t]: out of range");
	return _m[0];
      } else {
	return _m[j];
      }
    }
    T trace(void) {
      T s=1;
      for(size_t j=0; j<dim(); j++) {s *= _m[j][j];}
      return s;
    }
    Mat<T> make_lu(void) { // LU decomposition
      Mat<T> lu(*this);
      for(size_t j=0; j<dim(); j++) {
	for(size_t k=j+1; k<dim(); k++) {
	  lu[k][j] /= lu[j][j];
	  for(size_t l=j+1; l<dim(); l++) lu[k][l] -= lu[k][j]*lu[j][l];
	}
      }
      return lu;
    }
    void solve_lu(Vec<T> &v) {        // L*U * y = v : solve y 
      for(size_t j=0; j<dim(); j++) { // L*b = v : solve b
	T s = v[j];
	for(size_t k=0; k<j; k++) {s -= _m[j][k]*v[k];}
	v[j] = s;
      }
      for(size_t j=dim()-1; 0<=j && j<dim(); j--) { // U*y = b : solve y
	T s = v[j];
	for(size_t k=dim()-1; j<k && k<dim(); k--) {s -= _m[j][k]*v[k];}
	v[j] = s /_m[j][j];
      }
    }
    T det(void) { // determinant
      if(dim() == 2) {
	return _m[0][0]*_m[1][1] - _m[0][1]*_m[1][0];
      } else {
	Mat<T> lu = make_lu();
	return lu.trace();
      }
    }
    Mat<T> inv(void) { // inverse matrix
      Mat<T> m(dim());
      if(dim() == 2) {
	T d = det();
	if(std::abs(d) != 0) {
	  m[0][0] =  _m[1][1]/d;
	  m[0][1] = -_m[0][1]/d;
	  m[1][0] = -_m[1][0]/d;
	  m[1][1] =  _m[0][0]/d;
	} else {
	  fprintf(stderr,"Mat::inv: determinant is 0\n");
	}
      } else {
	Mat<T> lu = make_lu();
	Vec<T> v(dim());
	for(size_t j=0; j<dim(); j++) {
	  v.set_single(j,1);
	  lu.solve_lu(v);
	  for(size_t k=0; k<dim(); k++) {m[k][j] = v[k];}
	}
      }
      return m;
    }
    Mat<T> trans(void) {
      Mat<T> m;
      for(size_t j=0; j<dim(); j++) {
	for(size_t k=0; k<dim(); k++) {
	  m[j][k]=_m[k][j];
	}
      }
      return m;
    }
    Mat<T> &flip_sign(void) {
//      for(size_t j=0; j<dim(); j++) {_m[j].flip_sign();}
      for(auto &&m : _m) {m.flip_sign();}
      return *this;
    }
    Mat<T> &operator +=(Mat<T> &m) {
      for(size_t j=0; j<dim(); j++) {_m[j] += m[j];}
      return *this;
    }
    Mat<T> &operator -=(Mat<T> &m) {
      for(size_t j=0; j<dim(); j++) {_m[j] -= m[j];}
      return *this;
    }
    Mat<T> &operator *=(T x) {
//      for(size_t j=0; j<dim(); j++) {_m[j] *= x;}
      for(auto &&m : _m) {m *= x;}
      return *this;
    }
    Mat<T> &operator /=(T x) {
//      for(size_t j=0; j<dim(); j++) {_m[j] /= x;}
      for(auto &&m : _m) {m /= x;}
      return *this;
    }
    Mat<T> &operator *=(Mat<T> &m) {
      Mat<T> tmp(*this);
      for(size_t j=0; j<dim(); j++) {
	for(size_t k=0; k<dim(); k++) {
	  T s=0;
	  for(size_t l=0; l<dim(); l++) {
	    s += tmp[j][l]*m[l][k];
	  }
	  _m[j][k] = s;
	}
      }
      return *this;
    }
    Mat<T> &operator /=(Mat<T> &m) {
      Mat<T> mi=m.inv();
      return (*this) *= mi;
    }
    Vec<T> product(Vec<T> &v) {
      Vec<T> tmp(dim());
      if(v.dim() != dim()) {
	fprintf(stderr,"Mat::product: different dimensions\n");
      } else {
	for(size_t j=0; j<dim(); j++) {tmp[j] = _m[j]*v;}
      }
      return tmp;
    }
    void print(void) {
//      for(size_t j=0; j<dim(); j++) {_m[j].print(); printf("\n");}
      for(auto &&m : _m) {m.print(); printf("\n");}
    }
    Vec<T> back(void) {return _m.back();}
    Vec<T>* begin() {return &_m[0];}
    Vec<T>* end() {return &_m[_m.dim()];}
  }; //class Mat

  tcT inline Mat<T> operator -(Mat<T> m) {return m.flip_sign();}
  tcT inline Mat<T> operator +(Mat<T> m1, Mat<T> m2) {return m1 += m2;}
  tcT inline Mat<T> operator -(Mat<T> m1, Mat<T> m2) {return m1 -= m2;}
  tcT inline Mat<T> operator *(Mat<T> m, T x) {return m *= x;}
  tcT inline Mat<T> operator *(T x, Mat<T> m) {return m *= x;}
  tcT inline Mat<T> operator /(Mat<T> m, T x) {return m /= x;}
  tcT inline Mat<T> operator *(Mat<T> m1, Mat<T> m2) {return m1 *= m2;}
  tcT inline Mat<T> operator /(Mat<T> m1, Mat<T> m2) {return m1 /= m2;}
  tcT inline Vec<T> operator *(Mat<T> m, Vec<T> v) {return m.product(v);}
  //------------------------------------------------------------

} // namespace thl

#undef tcT  // undefine local macro

#endif // THL_SQ_MATRIX_HH

