#!/bin/sh

set -ex

# Output generation script for stellar

STELLAR=../../../../build/bin/stellar

# ============================================================
# Varying error rates
# ============================================================

call_stellar_reverse()
{
    ${STELLAR} -e $1 -l 50 -x 10 -k 7 -n 5000 -s 10000 -r -v -o $2.gff ../../512_simSeq1_$2.fa ../../512_simSeq2_$2.fa > $2.gff.stdout
    ${STELLAR} -e $1 -l 50 -x 10 -k 7 -n 5000 -s 10000 -r -v -o $2.txt ../../512_simSeq1_$2.fa ../../512_simSeq2_$2.fa > $2.txt.stdout
}

eps="e-1"
errRate=0.1
call_stellar_reverse $errRate $eps

eps="75e-3"
errRate=0.075
call_stellar_reverse $errRate $eps

eps="5e-2"
errRate=0.05
call_stellar_reverse $errRate $eps

eps="25e-3"
errRate=0.025
call_stellar_reverse $errRate $eps

eps="e-4"
errRate=0.0001
call_stellar_reverse $errRate $eps

# ============================================================
# Varying minimal lengths
# ============================================================

call_stellar_minlen()
{
    ${STELLAR} -e 0.05 -l $1 -x 10 -k 7 -n 5000 -s 10000 -r -v -o minLen$1.gff ../../512_simSeq1_5e-2.fa ../../512_simSeq2_5e-2.fa > minLen$1.gff.stdout
    ${STELLAR} -e 0.05 -l $1 -x 10 -k 7 -n 5000 -s 10000 -r -v -o minLen$1.txt ../../512_simSeq1_5e-2.fa ../../512_simSeq2_5e-2.fa > minLen$1.txt.stdout
}

minLen="20"
call_stellar_minlen $minLen

minLen="150"
call_stellar_minlen $minLen
