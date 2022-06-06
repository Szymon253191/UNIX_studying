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
