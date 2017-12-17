#!/bin/bash
echo 'Compilation'
gcc -o ./life_game.out ./src/*.c
echo 'Execution'
if [[ $1 -lt 20 ]]; then
	BOARD=20
else
	BOARD=$1
fi
if [[ $2 -lt 1 ]]; then
	TIME=60
else
	TIME=$2
fi
if [[ $TIME -lt 100 ]]; then
	LOOP=0
	SPEED=20
elif [[ $TIME -lt 1000 ]]; then
	LOOP=1
	SPEED=10
else
	LOOP=1
	SPEED=1
fi
./life_game.out $BOARD $TIME
echo 'GIF creation'
CMD="convert -delay $SPEED -loop $LOOP `ls -v *.pgm` life_game.gif"
eval $CMD
echo 'Cleaning repo'
rm -R *.pgm
echo 'Terminated'