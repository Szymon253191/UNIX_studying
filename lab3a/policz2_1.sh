if [ -d "$@" ]
then
	ls "$@" | wc -l
else
	. policz2.sh
fi
