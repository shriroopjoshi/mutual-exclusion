#!/bin/bash

# This script adds the job to the SLURM queue.

#SBATCH -J mutex-algorithms		# job name
#SBATCH -o out.o%j			# output and error filename (%j expands to jobID)
#SBATCH -N 1				# number of nodes
#SBATCH -n 48				# number of tasks/threads
#SBATCH -p development			# queue -- normal, development
#SBATCH -t 02:00:00			# run time - maxed to 2 hrs

#SBATCH --mail-user=shriroop.joshi@utdallas.edu
#SBATCH --mail-type=begin		# email me when job starts
#SBATCH --mail-type=end			# email me when job ends

# execute the binary for both algorithms
./mutex bakery 512 bakery.csv
./mutex tournament 512 tournament.csv

