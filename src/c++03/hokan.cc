#include <iostream>
#include <string>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>
#include <cstring> // for strdup

using namespace std;

const char* commands[] = {
    "help",
    "quit",
    "hello",
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
