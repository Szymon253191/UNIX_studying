echo "Dzis jest $(date "+%A")"
dayOfWeek=$(date +"%u") 
if [ "${dayOfWeek}" -gt 5 ]
then
	echo "To oznacza weekendzik"
else
	echo "Niestety jest to tydzien roboczy :("
fi
