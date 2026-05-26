# ls
```
tip> ls
Usage: ls pattern
List macro and data variables matching pattern.
Use 'ls *' to show all variables.
```

## variable names in the argument

> variable names are separated by commas with no spaces.

example
```
tip> @ x1 = 1
tip> @ x2 = 2
tip>
tip> ls x1,x2   ;# OK: separated by commas with no spaces
x1 : number [1]
x2 : number [2]
tip>
tip> ls x1, x2  ;# NG: separated by commas with spaces
x1 : number [1] ;# only 1st argument is listed
```

## wild-card matching to the variable name

| match to           | wild card |
|:---:|:---:|
|any string          |  *           |
|any character       |  ?           |

> wild card is **not the regular expression**  

example
```
tip> rm *
tip> do n 1 5; set num[n]=[n]; end
tip> for s ("1st" "2nd" "3rd" "4th" "5th"); @ str_[s]="[s]"; end
tip>
tip> ls *
str_1st : string [1st]
str_2nd : string [2nd]
str_3rd : string [3rd]
str_4th : string [4th]
str_5th : string [5th]
num1 : data(num) : size=1
num2 : data(num) : size=1
num3 : data(num) : size=1
num4 : data(num) : size=1
num5 : data(num) : size=1
tip>
tip> ls str_?th,num4,num5
str_4th : string [4th]
str_5th : string [5th]
num4 : data(num) : size=1
num5 : data(num) : size=1
```
