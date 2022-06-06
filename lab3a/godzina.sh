if [ -z "$1" ]
then
	while true
	do
		clear
		date
		sleep 5
	done
else
	while true
	do
		clear
		date
		sleep $1
	done
fi
