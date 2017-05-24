#! /bin/bash
#	Alex Hortin
#	10/15/2007
#	Lab5
# 	CPTS 360

# MyRecursiveCopy
myRecursiveCopy()
{
	for NAME in $*
	do
		LAST=$NAME
	done

	for ARGITER in $*
	do
		if [ $ARGITER != $LAST ]		#checking to make sure the final argument is not included in file operations
		then
			if [ -e $ARGITER ]			#test whether file name exists
			then
				######test whether name is a (REG) file######
				if [ -f $ARGITER ]     
				then			
					$(cp $ARGITER $LAST)
				######test whether name is a DIR######
				elif [ -d $ARGITER ] 
				then
					mkdir $LAST$ARGITER
					for LSD in  $(ls $ARGITER)
					do
						DIRCONTENTS="$DIRCONTENTS $ARGITER$LSD"
					done		
					pwd
					#echo $DIRCONTENTS
					myRecursiveCopy "myrcp.sh $DIRCONTENTS $LAST$ARGITER"
				######test whether or not it is a link######
				elif [ -L $ARGITER ]		
				then 
					echo link
				fi
			else	
				echo $1 does not exist cannot copy
				exit 1
			fi
		fi
	done
}
