dayOfWeek=$(date +"%u") 
if [ "${dayOfWeek}" == 1 ]
then
	echo "Poniedzialek"
elif [ "${dayOfWeek}" == 2 ]
then
        echo "Wtorek"
elif [ "${dayOfWeek}" == 3 ]
then
        echo "Sroda"
elif [ "${dayOfWeek}" == 4 ]
then
        echo "Czwartek"
elif [ "${dayOfWeek}" == 5 ]
then
        echo "Piatek"
elif [ "${dayOfWeek}" == 6 ]
then
        echo "Sobota"
elif [ "${dayOfWeek}" == 7 ]
then
	echo "Niedziela"
else
	echo "error"
fi
