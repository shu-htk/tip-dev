# camon
```
tip> camon
Usage: camon EPICS_record > v
Monitor the EPICS record and store updates into data v.
```

see also [cacheck](cacheck.md) and [caclose](caclose.md) 

example:
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

see also [ex101](../../doc/ex/ex101.md)

