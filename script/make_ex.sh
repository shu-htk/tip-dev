#!/bin/bash

dir=doc/ex
mkdir -p $dir

echo "# Macro Examples" > doc/examples.md
echo "" >> doc/examples.md

for f in doc/macro/ex*.tip
do
    file=`basename $f`
    ex=${file%.*}
    echo $ex
#    tip -g 600x450 -e $f --png doc/fig/$ex.png
    item=`head -1 $f | sed 's/# //g'`
    echo "- [$item](ex/$ex.md)" >> doc/examples.md
    head -1 $f > doc/ex/$ex.md
    echo '```' >>  doc/ex/$ex.md
    tail -n +3 $f >>  doc/ex/$ex.md
    echo '```' >>  doc/ex/$ex.md
    echo "![](../fig/$ex.png)" >>  doc/ex/$ex.md

done
