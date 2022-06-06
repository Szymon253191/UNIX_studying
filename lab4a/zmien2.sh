for x in $*
do
	echo "mv $x `printf $x | tr -c '[:alnum:]' "_"`"
done
