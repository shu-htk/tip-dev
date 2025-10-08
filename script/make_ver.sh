#!/bin/bash

if [ -e .git ] ; then
    git_tag=`git describe --tags --always`
    git_log=`git log -1 --pretty=format:'%h, %ad, %an' --date=iso`
    echo "$git_tag $git_log" > ver.tmp
    if [ -e version.txt ] ; then
	update=`cmp ver.tmp version.txt | grep -c .`
	if [ $update == 1 ] ; then
	    echo "upadate version.txt"
	    cp ver.tmp version.txt
	fi
    else
	echo "create version.txt"
	cp ver.tmp version.txt
    fi
    rm -f ver.tmp
fi
