// thl : tiny header-only library
//
// trim : a function to remove the edge spaces and quotations from the string
//
// -std=c++03
//
#ifndef THL_TRIM_HH
#define THL_TRIM_HH

namespace thl {

  std::string trim(const std::string &s, char c='"') {
    if(s.size()==0) return "";
    size_t n=s.find_first_not_of(" \t");  // skip forward spaces
    if(n==s.npos) return s;
    size_t m=s.find_last_not_of(" \t");   // skip backward spaces
    if(c > 0) {
      if(s[n]==c && s[m]==c) {n++; m--;}
    }
    return s.substr(n,m-n+1);
  }

}//-- namespace thl

#endif //THL_TRIM_HH
