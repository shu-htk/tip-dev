# fplot
```
usage: fplot [t] v [(opt)]
 do FFT with the time data t and the amplitude v.
 it is created the frequency data v_fx and the power spectrum v_fy.
 then 'plot v_fx v_fy' is done.
 if data t is not specified you should set the option 'dt:'
options:
 dt:x   the time tick of FFT. (default is 1.0)
 fw:s   FFT window function. (default is 'rc'(Rectangle))
 name of window functions are
  rc  : Rectangle (default)
  hn  : Hann
  hm  : Hamming
  bk  : Blackman
  bh  : Blackman-Haris
```
