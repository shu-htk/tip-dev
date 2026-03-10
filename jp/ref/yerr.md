# yerr
```
tip> yerr
usage: yerr x y ey [(opt)]
 plot y-error-bars of the data ey
 you should do 'plot x y' before this command.
```

example
```
@ num_of_data_set = 20

set x = range([num_of_data_set],1,10)

do n 1 [num_of_data_set]
  @ num_of_trial = 100
  @ sigma = 0.1
  set measure = random([num_of_trial],gaus,[sigma]) 
  stat measure
  set mean = [measure_mean] ;# error of center value
  set sigma = [measure_sigma]   ;# error of root mean square
  cat mean >> err_mean          ;# append to data array
  cat sigma >> err_sigma        ;# append to data array
end

@ pi = 3.14159265
@ freq = 0.2
set y = sin([freq]*2*[pi]*x) + err_mean  ;# measured data

opt (gd:1 xt:1)
plot x y (lw:0 st:star sc:red)  ;# plot measured data
yerr x y err_sigma              ;# plot error of measured data
fit x y s (lc:blue fq:[freq])   ;# fitting to measured data
```