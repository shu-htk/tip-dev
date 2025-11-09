# caget
```
tip> caget
usage: caget EPICS_record [> v]
 get the value from EPICS_record and print contents.
 if '>' is specified the value is redirected to the data v.
 also the following macro variable related to the data v is created.
macro variable:
   v : the 1st element of data v
```

Get the all elements of EPICS_record and print them.

If it is redirected to "> v", the following variables are created.

- **data varaible :**  `set v = (all elements of EPICS_record)`
- **macro variable :** `@ v = (1st element of EPICS_record)`

exmaple
```
tip> caget monitor:wf.NELM
monitor:wf.NELM 2025-11-09 15:56:40.736024  100

tip> caget monitor:wf.NELM > nelm
tip> ls nelm
nelm : number [100]        ;# created macro variable
nelm : data(num) : size=1  ;# created data variable

tip> set t=range([nelm],1,[nelm])
tip> set v=sin(t)
tip> cat v (nr:1,2)
v : data(num) :  0.84147098481 0.90929742683

tip> caput monitor:wf < v

tip> caget monitor:wf > v2
tip> ls v2
v2 : number [0.84147098481]   ;# created macro variable (1st elemrnt of wf)  
v2 : data(num) : size=100     ;# created data variable (all elements of wf)

tip> cat v2 (nr:1,2)
v2 : data(num) :  0.84147098481 0.90929742683
```

