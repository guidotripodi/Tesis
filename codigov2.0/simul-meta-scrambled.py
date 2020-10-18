#!/usr/bin/python
import sys
from Bio import SeqIO
from random import randint

scrambled = bool(sys.argv[1])
readlen = int(sys.argv[1])
totalbp = int(sys.argv[2])
genomes = [ ( genome.split(".")[0], str(list(SeqIO.parse(genome, "fasta"))[0].seq) ) for genome in list(sys.argv[3:]) ]

i=0
while totalbp>0:
	gname, genome = genomes[randint(0,len(genomes)-1)]
	randpos = randint(0,len(genome))

	print ">READ%s %s %s" % ( str(i).zfill(8), str(randpos).zfill(8), gname )
	read = genome[randpos:randpos+readlen]
	read = list(read)
	read.sort(key=lambda x: randint(1000, 10000))
	read = "".join(read)
	print read

	totalbp -= readlen
	i+=1
