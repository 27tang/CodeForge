#!/bin/bash

cat A-large-practice.in | \
	awk '
		BEGIN {
			count = 1;
			line = 1;
			MushEaten_1 = 0;
			MushOnPlate_1 = 0;
			MushOnPlate_2 = 0;
			MushEaten_1 = 0;
			mostRate = 0;
		}
		{
			if(line % 2 != 0 && line != 1)
			{
				MushOnPlate_1 = $1;
				for(i = 2; i <= NF ; ++i)
				{
					if($i < MushOnPlate_1){
						MushEaten_1 += (MushOnPlate_1 - $i);
					}
					MushOnPlate_1 = $i;
				}

				for(i = 1; i < NF ; ++i)
				{
					if($i > $(i+1)){
						rate = ($i - $(i+1));
						if ( rate > mostRate )
							mostRate = rate;
					}
				}

				for(i = 1; i < NF ; ++i)
				{
					if($i <= mostRate)
					{
						MushEaten_2 += $i;
					}
					else
						MushEaten_2 += mostRate;
				}
				printf "Case #%d: %d %d\n",count,MushEaten_1,MushEaten_2;
				MushEaten_1 = 0;MushOnPlate_1 = 0;mostRate=0;MushEaten_2 = 0;
				++count;
			}
			++line;
		}
		END {
		}'
