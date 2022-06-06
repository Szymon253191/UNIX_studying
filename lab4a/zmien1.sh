for x in $*
do
	echo "mv $x `echo $x | tr "[A-Z]" "[a-z]"`"
done

