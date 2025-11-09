# caput
```
tip> caput
usage: caput EPICS_record < v
usage: caput EPICS_record < expression
 put the value to EPICS_record.
 if data v exist, the value of v is put to EPICS_record,
 if not exist, the expression value is put to EPICS_record.
```

example
```
tip> cainfo monitor:str
monitor:str
    State:         connected
    Host:          some.user.host
    Access:        read=1, write=1
    Data type:     DBR_STRING (native: DBF_STRING)
    Element count: 1

tip> set s = Good morning
tip> caput monitor:str < s
tip> caget monitor:str
monitor:str 2025-11-09 16:35:33.955544  Good morning

tip> @ s1 = Hello
tip> @ s2 = World
tip> caput monitor:str < [s1] [s2]
tip> caget monitor:str
monitor:str 2025-11-09 16:42:22.081168  Hello World

tip> caput monitor:str < exp(1)
tip> caget monitor:str
monitor:str 2025-11-09 16:42:34.160567  2.7182818285
```

 see also [caget](caget.md).
 