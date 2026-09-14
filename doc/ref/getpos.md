# getpos
```
tip> getpos
Usage: getpos x y [key] [nbox]
 Get the position on the graph using the mouse cursor.
 Positon is saved to macro variables x and y.
 Mouse or keyboard label is saved to macro variable key
 key strings:
   Mouse_L, Mouse_M, Mouse_R
   BackSpace, Enter, Escape, Tab, Space, A, B, ... and so on.
 Box number is saved to macro variable nbox.
```

> Available in version v1.2.5 and later

You should draw at least one box (subpage) to do this command.

The obtained positon (x,y) is the graph coordinate.

## Definition of key string

### Mouse button

|Button        |key string|
|:-:           |:-:       |
|Left Button   | `Mouse_L` |
|Middle Button | `Mouse_M` |
|Right Button  | `Mouse_R` |

### Keyboard button

|Key Label     |key string  |
|:-:           |:-:         |
|Back Space    | `BackSpace`|
|Enter (Return)| `Enter`    |
|Esc           | `Escape`   |
|Tab           | `Tab`      |
|Space         | `Space`    |
|←             | `Arrow_L`  |
|↑             | `Arrow_U`  |
|→             | `Arrow_R`  |
|↓             | `Arrow_D`  |
|F1            | `F1`       |
|F2            | `F2`       |

The key string of single character is same as itself.

|Key Label |key string|
|:-:       |:-:       |
|0         | `0`      |
|1         | `1`      |
|A         | `A`      |
|B         | `B`      |
|a         | `a`      |
|b         | `b`      |
|@         |`@`       |
|/         |`/`       |

Undefined key string is represented as a code number.

## Definition of box number (nbox)

If it is not devided boxes (subpages) nbox=0.

If it is devided multi boxes (subpages), nbox is counted from 0.

For example,
```
tip> div 2 2
tip> do n 1 4; box 0 1 0 1; end

tip> getpos x y key nbox; ls nbox ;# click mouse on the 1st box
nbox : number [0]

tip> getpos x y key nbox; ls nbox ;# click mouse on the 2nd box
nbox : number [1]

tip> getpos x y key nbox; ls nbox ;# click mouse on the 3rd box
nbox : number [2]

tip> getpos x y key nbox; ls nbox ;# click mouse on the 4th box
nbox : number [3]
```

macro examples:
[ex34](../ex/ex34.md)
