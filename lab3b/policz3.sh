if [ -z "$1" ]
then
	echo "Folder not found. Here: "
	ls | wc -l

elif [ $1 = "-a" ]
then
	echo "Parameter '-a' active"
	if [ -z "$2" ]
	then
		echo "Folder not found. Here: "
		ls -a | wc -l
	fi
	shift
	for i in $(seq 1 $#)
	do
		if [ -z "$1" ]
		then
			echo "Folder not found. Here: "
			ls -a | wc -l

		elif [ -d "$1" ]
		then
			echo $1": "
			ls $1 -a | wc -l
		else
			echo "Folder not found. Here: "
			ls -a | wc -l
		fi
	shift
	done
else
	for i in $(seq 1 $#)
	do
		if [ -z "$1" ]
		then
			echo "Folder not found. Here: "
			ls | wc -l

		elif [ -d "$1" ]
		then
			echo $1": "
			ls $1 | wc -l
		else
			echo "Folder not found. Here: "
			ls | wc -l
		fi
	shift
	done
fi
