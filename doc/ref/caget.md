# caget
```
tip> caget
Usage: caget EPICS_record [> v]
Get the value of the EPICS record and print it.
If '>' is specified, store the value into data v.
Macro variable created:
  v : first element of data v
```

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

