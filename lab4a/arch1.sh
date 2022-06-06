files=`ls -a | find *$1`
echo "TYPE: " $1
echo "FILES: "
echo $files
echo " "
for file in $files
do
	echo cp -p $file $HOME/.arch/`echo $file | sed s/$1/_arch$1/ `
done
