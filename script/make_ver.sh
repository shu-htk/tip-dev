#!/bin/bash

if [ -e .git ] ; then
    if command -v git > /dev/null ; then
	git_tag=`git describe --tags --always`
	git_log=`git log -1 --pretty=format:'%ad, %an' --date=iso`
	echo "$git_tag $git_log" > ver.tmp
	echo "$git_tag $git_log"
	if [ -e version.txt ] ; then
	    update=`cmp ver.tmp version.txt | grep -c .`
	    read -p "do you update version file ? (y/N)> " ans
	    if [ $update == 1 ] && [ ${ans:-"n"} == "y" ] ; then
		echo "version.txt is updated"
		cp ver.tmp version.txt
	    else
		echo "version.txt is not updated"
	    fi
	else
	    echo "create version.txt"
	    cp ver.tmp version.txt
	fi
	rm -f ver.tmp
    fi
fi
