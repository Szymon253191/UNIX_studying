echo "----------------------------------"
echo "      WYBIERZ NUMER ZADANIA:      "
echo "(parametry podawac przy wywolaniu)"
echo "----------------------------------"
read zad;
clear;
case $zad in

"1")

# ZADANIE 1
while [ $# -gt 0 ]
do
	echo \"$1\"
	shift
done

;;

"2")

# ZADANIE 2
while (true)
do
	echo "--- WYBIERZ OPCJE: ---"
	echo "a) informacja o nazwie biezacego systemu i typie systemu operacyjnego"
	echo "b) nazwa uzytkownika i sciezka biezaczego katalogu"
	echo "c) aktualna data oraz czas"
	echo "d) wyjscie z programu"
	echo "----------------------"
	read choice;
	clear;
	case $choice in
	"a")
		uname -n
		uname -o
		echo " "
	;;
	"b")
		logname
		pwd
		echo " "
	;;
	"c")
		date +%F
		date +%T
		echo " "
	;;
	"d")
		break
	;;
	*)
		echo "\" $choice jest \" niepoprawnym wyborem"
		echo " "
	;;
	esac
done;

;;

"3")

#ZADANIE 3
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

;;
esac
