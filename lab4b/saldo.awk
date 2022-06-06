num=1;
while IFS= read -r line
do
	echo awk '{print $6}' $1S

	echo $saldo;
done < $1
########################################################
#
#	if (saldo(x+1) == operacja(x+1) + saldo(x))
#
#	saldo = $6
#	shift
#	if $6 = saldo + $4
#		print blad
#	shift
#
#########################################################
