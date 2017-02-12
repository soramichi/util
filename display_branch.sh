ret=`git branch 2>/dev/null | grep "*"`

if [ "$?" == "0" ]; then
    branch=`echo "$ret" | cut -d ' ' -f 2-`
    echo " [$branch]"
fi
