#!/bin/bash

list1=(var incr loop if_fi)
list2=(print fmt wait sys calc logic)
list3=(arc box box3 cut div elem exe fbox ffit fit fit3 fill font fplot help hfit hplot hplot2 line mplot mread mset mwrite opt plot plot3 read set sort sqar stat symb text title tfmt vp write xerr xlab yerr ylab zlab)

dir=doc/ref
mkdir -p $dir

for cmd in ${list1[@]}
do
    if [ ! -e $dir/$cmd.md ] ; then
	echo "making $dir/$cmd.md"
	if [ $cmd == var ] ; then
	    echo "# @" > $dir/$cmd.md
	fi
	if [ $cmd == incr ] ; then
	    echo "# ++, --" > $dir/$cmd.md
	fi
	if [ $cmd == loop ] ; then
	    echo "# for, do, while, end" > $dir/$cmd.md
	fi
	if [ $cmd == if_fi ] ; then
	    echo "# if, elif, else, fi" > $dir/$cmd.md
	fi
    else
	echo "$dir/$cmd.md is already exist"
    fi
done

for cmd in ${list2[@]}
do
    if [ ! -e $dir/$cmd.md ] ; then
	echo "making $dir/$cmd.md"
	echo "# $cmd" > $dir/$cmd.md
	echo $cmd > tmp.tip
	echo '```' >> $dir/$cmd.md
	tip -e tmp.tip --png /dev/null >> $dir/$cmd.md
	echo '```' >> $dir/$cmd.md
    else
	echo "$dir/$cmd.md is already exist"
    fi
done

for cmd in ${list3[@]}
do
    if [ ! -e $dir/$cmd.md ] ; then
	echo "making $dir/$cmd.md"
	echo "# $cmd" > $dir/$cmd.md
	echo $cmd > tmp.tip
	echo '```' >> $dir/$cmd.md
	tip -e tmp.tip --png /dev/null >> $dir/$cmd.md
	echo '```' >> $dir/$cmd.md
    else
	echo "$dir/$cmd.md is already exist"
    fi
done

rm -f tmp.tip
