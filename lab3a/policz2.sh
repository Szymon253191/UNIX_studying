if  test "$1" = "-a" 
then
ls -al | wc -l
else
ls -l | wc -l
fi

