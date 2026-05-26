// thl : tiny header-only library
//
// wc_match : non-recursive wild-card-matching
//  '*' any string (include null string)
//  '?' any character
//
// c++03
//
#ifndef THL_WILDCARD_HH
#define THL_WILDCARD_HH

namespace thl {
  bool wc_match_c_str(const char *pattern, const char *text) {
    const char *p_save = NULL;
    const char *t_save = NULL;
    while(*text) {
      if(*pattern == '*') {
	p_save = ++pattern;
	t_save = text;
      } else if(*pattern == '?' || *pattern == *text) {
	pattern++;
	text++;
      } else if(p_save) {
	pattern = p_save;
	text = ++t_save;
      } else {
	return false;
      }
    }
    while(*pattern == '*') {
      pattern++;
    }
    return !*pattern;
  }

  bool wc_match_str(const std::string& pattern, const std::string& text) {
    return wc_match_c_str(pattern.c_str(), text.c_str());
  }

}//-- namespace thl

#endif //THL_WILDCARD_HH
