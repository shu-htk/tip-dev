// my_macro : simple example to use MacroTool
//
// -std=c++03
//
#include "thl/MacroTool.hh"

class MyMacro : public thl::MacroTool {
private:
  int _debug;
public:
  MyMacro() : _debug(0) {}
  int add_commands(std::string buf) {// called in MacroTool::parse_vbuf()
    thl::StrSplit words(buf);
    if(words(0)=="help") {
      printf("additional commands:\n"
	     " exe  : execute a macro file.\n"
	     " ls   : print macro variables.\n"
	     " rm   : remove macro variables.\n"
	     );
      print_help(); // help for preset commands
      return 0;
    }
    if(words(0)=="exe") {
      if(words.size() < 2) {
	printf("usage: exe [macro_file] [debug]\n"
	       " execute macro_file.\n");
	return 0;
      }
      _debug = (words.size()>2) ? 1 : 0;
      if(_debug) printf("debug mode\n");
      exec(words(1));
      return 0;
    }
    if(words(0)=="ls") {
      if(words.size() < 2) {
	printf("usage: ls [pattern]\n"
	       " print macro variables which matches pattern.\n"
	       " example: 'ls *' show all defined macro variables.\n");
	return 0;
      }
      var.ls(words(1));
      return 0;
    }
    if(words(0)=="rm") {
      if(words.size() < 2) {
	printf("usage: rm [pattern]\n"
	       " remove macro variables which matches pattern.\n"
	       " example: 'rm *'  remvoe all macro variables.\n");
	return 0;
      }
      var.rm(words(1));
      //      clear_var();
      return 0;
    }
    return 1;
  }
};

int main() {
  MyMacro macro;
  macro.main_loop();
  return 0;
}
