# logic
```
usage: logic [expression]
```
this command show the result of "logic expression"

where "logic expression" is appear in

- [if](if_fi.md) expr
- [elif](if_fi.md) expr
- [while](loop.md) expr
- [@](var.md) a = expr ? : b : c
- [cut](cut.md) a,b,c,... "expr"  

## the notation of logic expression

|function       |standard notation|simplified notation|
|---------------|--------------|------------|
|equal          | A == B       |A = B       |
|not equal      | A != B       |            |
|less than      | A < B        |            |
|less than equal| A <= B       |            |
|more than      | A > B        |            |
|more than equal| A >= B       |            |
|logic and      |expr1 && expr2|expr1 & expr2|
|logic or       |expr1 \|\| expr2|expr1 \| expr2|

example
```
tip> logic 1<2
expression: [1<2]
bool_by_num: 1

tip> logic 1=2 & 3=3
expression: [1=2 & 3=3]
bool_by_num: 0

tip> logic 1=2 | 3=3
expression: [1=2 | 3=3]
bool_by_num: 1

tip> logic A=B
expression: [A=B]
bool_by_str: 0

tip> logic A=B | B=B
expression: [A=B | B=B]
bool_by_str: 1
```

## extension of the notation (numerical)

|function       |extension notation| standard notation|
|---------------|---------------|---------------------|
|equal          | A=B=C ...     |(A==B) && (B==C) && ...|
|not equal      | A!=B!=C ...   |(A!=B) && (B!=C) && ...|
|less than      | A<B<C ...     |(A<B) && (B<c) && ...  |
|less than equal| A<=B<=C ...   |(A<=B) && (b<=C) && ...|
|more than      | A>B>C ...     |(A>B) && (B>c) && ...  |
|more than equal| A>=B>=C ...   |(A>=B) && (b>=C) && ...|

example
```
tip> logic 1<2<3<4
expression: [1<2<3<4]
bool_by_num: 1

tip> logic 1<5<3<4
expression: [1<5<3<4]
bool_by_num: 0

tip> logic A=A!=B
expression: [A=A!=B]
bool_by_str: 1
```
## wild card matching (string)

wild cards can be used for the right value of expression

| match to          | notation      |
|-------------------|---------------|
|any string         |  *            |
|any character       |  ?            |
|one of list of char|[abc..], [a-z] |
|one of list of string |{str1,str2,...}|

example
```
tip> @ s=ABC

tip> logic [s]=A*
expression: [ABC=A*]
bool_by_str: 1

tip> logic [s]=?BC
expression: [ABC=?BC]
bool_by_str: 1

tip> logic [s]=B*
expression: [ABC=B*]
bool_by_str: 0

tip> logic [s]=[A-Z]*
expression: [ABC=[A-Z]*]
bool_by_str: 1

tip> logic [s]={AAA,BBB,ABC}
expression: [ABC={AAA,BBB,ABC}]
bool_by_str: 1

tip> logic [s]={AAA,BBB,CCC}
expression: [ABC={AAA,BBB,CCC}]
bool_by_str: 0

tip> logic [s]!={AAA,BBB,CCC}
expression: [ABC!={AAA,BBB,CCC}]
bool_by_str: 1

tip> logic [s]!={AAA,BBB,ABC}
expression: [ABC!={AAA,BBB,ABC}]
bool_by_str: 0
```

