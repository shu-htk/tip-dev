# camon
```
tip> camon
usage: camon EPICS_record > v
 monitor the value of EPICS_record and redirected to the data v.
```

Assign the EPICS_record to the data varaible and the macro variable.

- **data varaible :**  `set v = (all elements of EPICS_record)`
- **macro variable :** `@ v = (1st element of EPICS_record)`

see also [cacheck](cacheck.md) and [caclose](caclose.md) 

an example of the remote control using EPICS CA
```
caput monitor:str < null ;# initialize command string
camon monitor:str > cmd  ;# assign the string-record to the variable
camon monitor:wf > wf    ;# assign the waveform-record to the variable

while [cmd] != exit      ;# if command is "exit" break the loop
   cacheck cmd,wf        ;# check if cmd,wf is updated
   if [cmd.update]
      prn recived [cmd]
   fi
   if [wf.update]
      plot wf
   fi
   wait 0.1              ;# put wait to reduce cpu load
end

caclose cmd,wf
```

the above script will be stopped when you do
`$ caput monitor:str exit`
from the shell of another terminal.

for more example see [ex101](../ex/ex101.md)

