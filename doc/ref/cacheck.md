# cacheck
```
tip> cacheck
usage: cacheck v1,v2,...
 check if EPICS records connected to data v1,v2,... are updated.
 (v1,v2,... should be defeined by 'camon')
 also the following macro variables are created.
macro variables:
  v1        : the 1st element of data v1
  v1.update : unix time if v1 updated, 0 if not updated
  ...
```

Check if the EPICS_record is updated.  

If it is updated the following variables are set.

- **data varaible :**  `set v = (all elements of EPICS_record)`
- **macro variable :** `@ v = (1st element of EPICS_record)`
- **macro variable :** `@ v.update = updated unix time (sec)`

If it is not updated the following variable is set.

- **macro variable :** `@ v.update = 0`

see also [camon](camon.md) and [caclose](caclose.md) 
