#!/bin/bash

cat testfile | \
	awk '
		BEGIN {
			line = 1;
			MushEaten = 0;
			MushOnPlate = 0;
		}
		{
			if(line % 2 != 0 && line != 1)
			{
				MushOnPlate = $1;
				for(i = 2; i <= NF ; ++i)
				{
					if($i < MushOnPlate){
						MushEaten += (MushOnPlate - $i);
					}
					MushOnPlate = $i;
				}
				printf "%d\n",MushEaten;
				MushEaten = 0;MushOnPlate = 0;
			}
			++line;
		}
		END {
			printf "done"
		}'
