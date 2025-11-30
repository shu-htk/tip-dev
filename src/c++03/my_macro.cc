// my_macro : simple example how to use thl::MacroTool
//
// c++03
//
#include "thl/MacroTool.hh"

class MyMacro : public thl::MacroTool {
public:
  MyMacro() {}
  int add_commands(std::string buf) {// called from thl::MacroTool::parse_vbuf()
    thl::StrSplit args;
    args.set_quot_to_skip_split('"');
    args.split(buf);
    if(args(0)=="help") {
      printf("additional commands:\n"
	     " exe  : execute a macro file.\n"
	     " ls   : print macro variables.\n"
	     " rm   : remove macro variables.\n"
	     );
      print_help();
      return 0;
    }
    if(args(0)=="exe") {
      if(args.size() < 2) {
	printf("usage: exe [macro_file] [arg1,arg2,..]\n"
	       " execute macro_file.\n");
	return 0;
      }
      std::string arg_list=(args.size()>2) ? args(2) : "";
      exec(args(1),arg_list);
      return 0;
    }
    if(args(0)=="ls") {
      if(args.size() < 2) {
	printf("usage: ls [pattern]\n"
	       " print macro variables which matches pattern.\n"
	       " example: 'ls *' show all defined macro variables.\n");
	return 0;
      }
      var.ls(args(1));
      return 0;
    }
    if(args(0)=="rm") {
      if(args.size() < 2) {
	printf("usage: rm [pattern]\n"
	       " remove macro variables which matches pattern.\n"
	       " example: 'rm *'  remvoe all macro variables.\n");
	return 0;
      }
      var.rm(args(1));
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
