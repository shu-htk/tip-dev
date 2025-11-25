#include <iostream>
#include <string>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>
#include <cstring> // for strdup

using namespace std;

const char* commands[] = {
    "arc", "box", "box3", "cat", "cut", "div", "elem", "exe",
    "fbox", "ffit", "fit", "fit3", "fill", "font", "fplot",
    "help", "hfit", "hplot", "hplot2", "line", "ls", "mplot",
    "mread", "mset", "mwrite", "opt", "plot", "plot3", "read",
    "rm", "set", "sort", "stat", "symb", "text", "title", "tfmt",
    "vp", "viewport", "write", "xerr", "xlab", "yerr", "ylab", "zlab",
    //--macro  
    "do", "for", "while", "end", "if", "elif", "else", "fi",
    "@", "args", "print", "pr", "println", "prn", "fmt", "sys",
    "wait", "calc", "logic", "split", "q",
#if USE_EPICS_CA
    "cainfo", "caget", "caput", "camon", "cacheck", "caclose",
#endif
    nullptr
};

char* command_generator(const char* text, int state) {
    static int list_index, len;
    const char* name;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }
    while ((name = commands[list_index++]) != nullptr) {
        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }
    return nullptr;
}

char** command_completion(const char* text, int start, int end) {
    rl_attempted_completion_function = nullptr;
    rl_attempted_completion_function = command_completion; 
    return rl_completion_matches(text, command_generator);
}

void initialize_readline() {
    rl_attempted_completion_function = command_completion;
    rl_completion_append_character = ' ';
}

int main() {
    initialize_readline();

    char* line;
    while ((line = readline(">> ")) != nullptr) {
        if (strlen(line) > 0) {
            add_history(line);
        }
        cout << "input: [" << line << "]" << endl;
        free(line);
    }
    return 0;
}
