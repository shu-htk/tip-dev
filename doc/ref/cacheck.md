# cacheck
```
tip> cacheck
Usage: cacheck v1,v2,...
Check whether EPICS records linked to v1,v2,... have updated.
(v1,v2,... must be created by 'camon')
Macro variables created:
  v1        : first element of v1
  v1.update : update time (epoch), or 0 if not updated
```

If the value of EPICS record is updated, all elements are
copied to the linked data variable.

example:
```
tip> camon monitor:ai1 > x
EpicsCA [monitor:ai1] opened.
EpicsCA [monitor:ai1] monitor with default handler.

tip> cacheck x              ;# not updated at this time

tip> prn [x.update] [x]
0 [x]

tip> caput monitor:ai1 < 7  ;# updated to 7

tip> cacheck x

tip> prn [x.update] [x]
1774104620.7 7

tip> caclose x
EpicsCA [monitor:ai1] closed.
```

see also [camon](camon.md) and [caclose](caclose.md) 
