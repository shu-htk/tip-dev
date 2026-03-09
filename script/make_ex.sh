#!/bin/bash

if [ $# -eq 0 ] ; then
    echo "usage: ./script/make_ex.sh [macro_name]"
    echo "ex) ./script/make_ex.sh ex01"
    exit 1
fi
dir=doc/ex
mkdir -p $dir

if [ ! -e doc/examples.md ] ; then
    echo "# Macro Examples" > doc/examples.md
    echo "" >> doc/examples.md
fi

#for f in doc/macro/ex*.tip
for f in doc/macro/$1.tip
do
    if [ -e $f ] ; then
	file=`basename $f`
	ex=${file%.*}
	echo $ex
	tip -g 600x450 -e $f --png doc/fig/$ex.png
	item=`head -1 $f | sed 's/# //g'`
	echo "- [$item](ex/$ex.md)" >> doc/examples.md
	head -1 $f > doc/ex/$ex.md
	echo '```' >>  doc/ex/$ex.md
	tail -n +3 $f >>  doc/ex/$ex.md
	echo '```' >>  doc/ex/$ex.md
	echo "![](../fig/$ex.png)" >>  doc/ex/$ex.md
    else
	echo "not found $f"
    fi
done
