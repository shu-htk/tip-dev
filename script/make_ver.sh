#!/bin/bash

git_tag=`git describe --tags --always`
git_log=`git log -1 --pretty=format:'%h, %ad, %an' --date=iso`

echo $git_tag $git_log > version.txt
