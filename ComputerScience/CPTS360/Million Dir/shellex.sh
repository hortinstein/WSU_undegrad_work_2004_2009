I=1
while [ $I -le 1000000 ]
do
	mkdir omg$I
	I=`expr $I + 1` 
done
