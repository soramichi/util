ret=`git branch --contains=HEAD --no-color 2>/dev/null`

if [ "$?" == "0" ]; then
    branch=`echo "$ret" | cut -d ' ' -f 2`
    echo " [$branch]"
fi
