
## Syntax of the tip interpreter

### Commands are executed line by line

```
tip> title "x vs y1 and y2"
tip> plot x y1
tip> plot x y2 (rp:1) 
```

### Multiple commands on a single line

You can execute multiple commands by separating them with semicolons `;`

```
tip> title "x vs y1 and y2"; plot x y1; plot x y2 (rp:1) 
```

### Comment out the line

Put the "#" at the head of the line
```
tip> # comment out this line
```

Comment out in the middle of the line, put ";" before "#"
```
tip> plot x y ;# plotting data x and y  
```

### Variable

- **Data variable**

The data variable is array of number (or string) which is defined by
[set](ref/set.md) command.
```
tip> set n={1,2,3}
tip> set x=sin(n)
```
Describing the above example by C-like, it is doing like,
```
double n[]={1,2,3};
double x[sizeof(n)]; for(int i=0; i<sizeof(n); i++) x[i]=sin(n[i]);
```

The information of data variable is shown by [ls](ref/ls.md) command,
and the element values are shown by [cat](ref/cat.md) command.

```
tip> ls *
n : data(num) : size=3
x : data(num) : size=3
tip> cat *
n : data(num) :  1 2 3
x : data(num) :  0.84147098481 0.90929742683 0.14112000806
```

- **Macro variable**

The macro variable is scalar of number (or string) which is defined by
[@](ref/var.md) command.  
Enclosing the macro variable in the brackets `[ ]`,
it is replaced to the string which is formatted by it's value.  
It's information and value is shown by [ls](ref/ls.md) command.

```
tip> @ n=1
tip> @ x=sin([n])  ;# this is parsed as "@ x=sin(1)"
tip> ls *
n : number [1]
x : number [0.84147098481]
```
Actually, macro variable is replaced to the string before
parsing the command, you can do like,
```
tip> @ n=1
tip> @ func=sin
tip> @ ret=x
tip> @ [ret]=[func]([n])  ;# this is parsed as "@ x=sin(1)"
tip> ls *
n : number [1]
x : number [0.84147098481]
func : string [sin]
ret : string [x]
```
- **Environment variable**

Environment variables defined in the shell are referenced by ${ }.

```
tip> prn ${SHELL}
/bin/bash
```
