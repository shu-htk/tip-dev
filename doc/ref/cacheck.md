# cacheck
```
tip> cacheck
usage: cacheck v1,v2,...
 check if EPICS records related to data v1,v2,... are updated.
 (v1,v2,... should be defeined by 'camon')
 also the following macro variables related to the data v1,v2,... are created.
macro variables:
  v1        : the 1st element of data v1
  v1.update : 1 if v1 updated, 0 if not updated
  v2        : the 1st element of data v2
  v2.update : 1 if v2 updated, 0 if not updated
  ... and so on ...
```

Check if the EPICS_record is updated.  

If it is updated the following variables are set.

- **data varaible :**  `set v = (all elements of EPICS_record)`
- **macro variable :** `@ v = (1st element of EPICS_record)`
- **macro variable :** `@ v.update = 1`

If it is not updated the following variables are set.

- **macro variable :** `@ v.update = 0`

see also [camon](camon.md) and [caclose](caclose.md) 
