#!/bin/bash

STELLAR=../../build/bin/stellar

# ============================================================
# Varying error rates
# ============================================================

rm *_*_*.gff
rm *_*_*.stdout
rm full.gff
rm full.stdout

errRate=0.05

call_stellar () {
   ${STELLAR} -e $errRate -l 50 -v -k 15 --sequenceOfInterest 0 --segmentBegin $1 --segmentEnd $2 --suppress-runtime-printing -o 0_$1_$2.gff ref.fasta query_e${errRate}.fasta > 0_$1_$2.stdout
}

${STELLAR} -e $errRate -l 50 -v -k 15 --suppress-runtime-printing -o full.gff ref.fasta query_e${errRate}.fasta > full.stdout

############################################################
# Extend left
############################################################

# Stellar	eps-matches	28	203
# overlap match by 24 (extend left)
call_stellar 179 300
# overlap match by 25 (extend left)
call_stellar 178 300

# Stellar	eps-matches	126	302
# overlap match by 31 (extend left)
call_stellar 271 400
# overlap match by 32 (extend left)
call_stellar 270 400

# Stellar	eps-matches	177	356
# overlap match by 14 (extend left)
call_stellar 342 450
# overlap match by 15 (extend left)
call_stellar 341 450


############################################################
# Extend right
############################################################

# From beginning
call_stellar 0 400

# Stellar	eps-matches	628	813
# overlap match by 15 (extend right)
call_stellar 500 643
# overlap match by 16 (extend right)
call_stellar 500 644

# Stellar	eps-matches	708	761
# overlap match by 13 (extend right)
call_stellar 600 721
# overlap match by 14 (extend right)
call_stellar 600 722

# Stellar	eps-matches	749	943
# overlap match by 13 (extend right)
call_stellar 600 762
# overlap match by 14 (extend right)
call_stellar 600 763