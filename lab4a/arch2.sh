files=`ls -a | find *$1`
echo "TYPE: " $1
echo "FILES:"
echo $files
echo " "
for file in $files
do
	echo cp -p $file $HOME/.arch/`basename -s $1 $file`_arch$1
done
