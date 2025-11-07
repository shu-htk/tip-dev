# logic
```
tip> logic
usage: logic [expression]
```
this command show the result of logical expression

where logical expression is appear in

- [if](if_fi.md) expr
- [elif](if_fi.md) expr
- [while](loop.md) expr
- [@](var.md) a = expr ? : b : c
- [cut](cut.md) a,b,c,... "expr"  

## Logical Expression

|function       |standard expr |simplified  expr|
|:---:|:---:|:---:|
|equal          | A == B       |A = B       |
|not equal      | A != B       |            |
|less than      | A < B        |            |
|less than equal| A <= B       |            |
|more than      | A > B        |            |
|more than equal| A >= B       |            |
|logical and    |expr1 && expr2|expr1 & expr2|
|logical or     |expr1 \|\| expr2|expr1 \| expr2|

example
```
tip> logic 1<2
[1<2] -> num_logic -> [1]

tip> logic 1==2 && 3==3     ;# standard expr
[1==2 && 3==3] -> num_logic -> [0]

tip> logic 1=2 & 3=3        ;# simplified expr
[1=2 & 3=3] -> num_logic -> [0]

tip> logic 1=2 | 3=3
[1=2 | 3=3] -> num_logic -> [1]

tip> logic A=B
[A=B] -> str_logic -> [0]

tip> logic A=B | B=B
[A=B | B=B] -> str_logic -> [1]
```

## Extended Logical Expression

|function       |extended expr| standard expr|
|:---:|:---:|:---:|
|series equal          | A=B=C ...     |(A==B) && (B==C) && ...|
|series not equal      | A!=B!=C ...   |(A!=B) && (B!=C) && ...|
|series less than      | A<B<C ...     |(A<B) && (B<c) && ...  |
|series less than equal| A<=B<=C ...   |(A<=B) && (b<=C) && ...|
|series more than      | A>B>C ...     |(A>B) && (B>c) && ...  |
|series more than equal| A>=B>=C ...   |(A>=B) && (b>=C) && ...|

example
```
tip> logic 1<2<3<=3     ;# same to 1<2 && 2<3 && 3<=3
[1<2<3<=3] -> num_logic -> [1]

tip> logic 1<5<3<=3     ;# same to 1<5 && 5<3 && 3<=3
[1<5<3<=3] -> num_logic -> [0]

tip> logic A=A!=B       ;# same to A==A && A!=B
[A=A!=B] -> str_logic -> [1]
```
## Wild Card Matching (for string logic only)

| match to           | wild card | usage|
|:---:|:---:|:---:|
|any string          |  *           | string = str*|
|any character       |  ?           | string = s?ring|
|one of the list of chars|[abc..], [a-z] | string = [a-z]trin[efg]|

**note 1)**
> wild cards should be **at the right part** of the comparison

**note 2)**
> wild card is **not the regular expression**  
> actually it is implemented by `fnmatch()` function

example
```
tip> @ s=ABC

tip> logic [s]=A*
[ABC=A*] -> str_logic -> [1]

tip> logic A*=[s]   ;# NG : wild card should be at the right
[A*=ABC] -> str_logic -> [0]

tip> logic [s]=B*
[ABC=B*] -> str_logic -> [0]

tip> logic [s]=?BC
[ABC=?BC] -> str_logic -> [1]

tip> logic [s]=[A-Z]*
[ABC=[A-Z]*] -> str_logic -> [1]
```

## List Matching (for both of numerical and string logic)

| match to       | usage |standard expr|
|:---:|:---:|:---:|
|one of the list of exprs|x = {expr1, expr2, ...}|(x == expr1) \|\| (x == expr2) \|\| ...|

| not match to       | usage |standard expr|
|:---:|:---:|:---:|
|all of the list of exprs|x != {expr1, expr2, ...}|(x != expr1) && (x != expr2) && ...|


**note 3)**
> the list of exprs should be **at the right part** of the comparison

**note 4)**
> the list of exprs **can not be concatenate** to the other exprs

example
```
tip> logic 6 = {1+2, 2*3}
[6 = {1+2, 2*3}] -> num_logic -> [1]

tip> logic {1+2, 2*3} = 6
[{1+2, 2*3} = 6] -> str_logic -> [0]  ;# NG : list of expr should be at the right

tip> logic abc == {a?, b*, [a-z]??}
[abc == {a?, b*, [a-z]??}] -> str_logic -> [1]

tip> logic aaabbb = aaa{bbb,ccc}    ;# NG : list can not be concatenate to the other
[aaabbb = aaa{bbb,ccc}] -> str_logic -> [0]
```
