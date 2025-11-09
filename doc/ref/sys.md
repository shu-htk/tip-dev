# sys
```
tip> sys
usage: sys [command]
 execute system command
```

`sys` execute shell command in the tip interpreter

example
```
tip> sys ls -l README.md
-rw-r--r-- 1 monitor monitor 900 Nov  7 07:27 README.md

tip> sys head README.md
# tip - tiny interactive plot

Tip is a command-line based data plotting tool.
It is written in C++ and depends on the library of
[PLPLOT](https://plplot.sourceforge.net/)
and [GNU readline](https://cgit.git.savannah.gnu.org/cgit/readline.git).
Basically it works on Linux or other Unix-like OS.
Although it has fewer functions than existing plotting tools,
it just aims ease of use over versatility.
```
