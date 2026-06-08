# legend
```
tip> legend
Usage: legend [command] [(opt)]
Draw legend on the existing graph. (alias: leg)
command:
 show [xpos,ypos]
   xpos: right(r), middle(m), left(l) : (default is right)
   ypos: top(t), middle(m), bottom(b) : (default is top)
 add [string]
   add legend string.
 ls
   list legend strings.
 rm
   remove legend strings.
Example:
   plot x y (st:plus lg:*)
   legent show l,m
It draws plus marker '+' and text 'x : y' at left,middle of the grapgh
```

> Available in version **v1.2.1** and later

Set and display legends.

Example:
```
tip> box 0 1 0 1         ;# Draw the graph frame
tip> legend add "Hello"  ;# Add legend (1st line)
tip> legend add "World"  ;# Add legend (2nd line)
tip> legend show         ;# Display legend (default position: top‑right)
```

---

## `lg:` option

For the following commands:

`plot`, `fit`, `hplot`, `hfit`, `fplot`, `ffit`

the string specified by the `lg:` option is added to the legend together with the line style and symbol of that graph.

If the legend string is `*`, it is automatically converted to the following:

| Command example | Converted string |
|---|---|
| `plot x y (lg:*)` | `x : y` (variable name of x : variable name of y) |
| `fit x y lin (lg:*)` | `lin fit` (function name + “fit”) |
| `hfit x gaus (lg:*)` | `gaus fit` (function name + “fit”) |
| `fplot x y (lg:*)` | `y : FFT` (variable name of y + “FFT”) |

Example:
```
tip> set x = range(10,1,10)
tip> set y = x
tip> plot x y (lw:0 st:plus sc:red lg:*) ;# Default legend (symbol + variable names)
tip> legend show left,top                ;# Display legend at top‑left
```

---

## Special tags available inside the `lg:` option

| Tag | Displayed information | Example |
|---|---|---|
| `%stat` | Statistical information | `hplot x (lg:*%stat)` |
| `%fit`  | Fitting coefficients    | `fit x y lin (lg:*%fit)` |
| `%win`  | Window function name    | `fplot v (lg:*%win)` |

macro examples:
[ex28](../ex/ex28.md),
[ex29](../ex/ex29.md),
[ex30](../ex/ex30.md)

