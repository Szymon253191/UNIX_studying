for x in $*
do
	if expr $x : '.*\.txt' > /dev/null
	then
		echo mv $x `echo $x | sed s/.txt/_org.txt/`
	else
		echo "rozszerzeniem pliku nie jest txt"
	fi
done
