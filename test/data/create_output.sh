#!/bin/bash

STELLAR=../../debug/bin/stellar

# ============================================================
# Varying error rates
# ============================================================

rm *_*_*.gff
rm *_*_*.stdout
rm full.gff
rm full.stdout

errRate=0.05
${STELLAR} -e $errRate -l 50 -v --suppress-runtime-printing -o full.gff ref.fasta query_e${errRate}.fasta > full.stdout
${STELLAR} -e $errRate -l 50 -v --sequenceOfInterest 0 --segmentBegin 0 --segmentEnd 400 --suppress-runtime-printing -o 0_0_400.gff ref.fasta query_e${errRate}.fasta > 0_0_400.stdout
${STELLAR} -e $errRate -l 50 -v --sequenceOfInterest 0 --segmentBegin 200 --segmentEnd 600 --suppress-runtime-printing -o 0_200_600.gff ref.fasta query_e${errRate}.fasta > 0_200_600.stdout
${STELLAR} -e $errRate -l 50 -v --sequenceOfInterest 0 --segmentBegin 400 --segmentEnd 700 --suppress-runtime-printing -o 0_400_700.gff ref.fasta query_e${errRate}.fasta > 0_400_700.stdout
