# getpos
```
tip> getpos
Usage: getpos x y [nkey] [nbox]
 Get the position on the graph using the mouse cursor.
 Positon is saved to macro variables x and y.
 Mouse button or key number is saved to macro variable nkey
 where,
  - Left button number is 1.
  - Middle button number is 2.
  - Right button number is 3.
 Box number is saved to macro variable nbox.
```

> Available in version v1.2.5 and later

You should draw at least one box (subpage) to do this command.

The obtained positon (x,y) is the graph coordinate.

## Definition of key number (nkey)

### Mouse button

|Button |`Left`|`Middle`|`Right`|
|:---:  |:---: |:---:   |:---:  |
|Number | 1 | 2 | 3 |

### Keyboard button

|Button|`ESC`|
|:-:   |:-:  |
|Number|9    |

|Button|`1`|`2`|`3`|`4`|`5`|`6`|`7`|`8`|`9`|`0`|`-`|`^`|`BS`|
|:-:   |:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|Number|10 |11 |12 |13 |14 |15 |16 |17 |18 |19 |20 |21 |22 |

|Button|`TAB`|`q`|`w`|`e`|`r`|`t`|`y`|`u`|`i`|`o`|`p`|`@`|`[`|`ENTER`|
|:-:   |:-:  |:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|Number|23   |24 |25 |26 |27 |28 |29 |30 |31 |32 |33 |34 |35 |36|

|Button|`CTR`|`a`|`s`|`d`|`f`|`g`|`h`|`j`|`k`|`l`|`;`|`:`|
|:-:   |:-:  |:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|Number|37   |38 |39 |40 |41 |42 |43 |44 |45 |46 |47 |48 |

|Button|`SHIFT`|`]`|`z`|`x`|`c`|`v`|`b`|`n`|`m`|`,`|`.`|`/`|
|:-:   |:-:    |:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|Number|50     |51 |52 |53 |54 |55 |56 |57 |58 |59 |60 |61 |

|Button|`ALT`|`SPACE`|
|:-:   |:-:  |:-:    |
|Number|64   |65     |

|Button|`F1`|`F2`|`F3`|`F4`|`F5`|`F6`|`F7`|`F8`|`F9`|`F10`|`F11`|`F12`|
|:-:   |:-: |:-: |:-: |:-: |:-: |:-: |:-: |:-: |:-: |:-:  |:-:  |:-:  |
|Number|67  |68  |69  |70  |71  |72  |73  |74  |75  |76   |95   |96   |

|Button|`UP`|`LEFT`|`RIGHT`|`DOWN`|
|:-:   |:-: |:-:   |:-:    |:-:   |
|Number|111 |113   |114    |116   |


## Definition of box number (nbox)

If it is not devided boxes (subpages) nbox=0.

If it is devided multi boxes (subpages), nbox is counted from 0.

For example,
```
tip> div 2 2
tip> do n 1 4; box 0 1 0 1; end

tip> getpos x y nkey nbox; ls nbox ;# click mouse on the 1st box
nbox : number [0]

tip> getpos x y nkey nbox; ls nbox ;# click mouse on the 2nd box
nbox : number [1]

tip> getpos x y nkey nbox; ls nbox ;# click mouse on the 3rd box
nbox : number [2]

tip> getpos x y nkey nbox; ls nbox ;# click mouse on the 4th box
nbox : number [3]
```

macro examples:
[ex34](../ex/ex34.md)







