#!/bin/bash

STELLAR=../../build/bin/stellar

mkdir -p segment
mkdir -p subset
mkdir -p er_edge_case
rm segment/*
rm subset/*
rm er_edge_case/*

minLen=50
for errRate in 0 0.05
do
   ############################################################
   # SEGMENT SEARCH
   ############################################################

   call_stellar_on_segment () {
      ${STELLAR} -e $errRate -l $minLen -v --sequenceOfInterest 0 --segmentBegin $1 --segmentEnd $2 -o segment/0_$1_$2_e$errRate.gff ref.fasta query_e$errRate.fasta > segment/0_$1_$2_e$errRate.stdout
   }

   call_stellar_on_segment 0 400
   call_stellar_on_segment 500 800

   ${STELLAR} -e $errRate -l $minLen -v -o segment/all_e$errRate.gff ref.fasta query_e$errRate.fasta > segment/all_e$errRate.stdout

   ############################################################
   # SUBSET SEARCH
   ############################################################

   ${STELLAR} -e $errRate -l $minLen -v --sequenceOfInterest 1 -o subset/1_e$errRate.gff multi_seq_ref.fasta query_e$errRate.fasta > subset/1_e$errRate.stdout

   ${STELLAR} -e $errRate -l $minLen -v --sequenceOfInterest 0 --sequenceOfInterest 1 -o subset/0_1_e$errRate.gff multi_seq_ref.fasta query_e$errRate.fasta > subset/0_1_e$errRate.stdout

   ${STELLAR} -e $errRate -l $minLen -v --sequenceOfInterest 1 --sequenceOfInterest 2 -o subset/1_2_e$errRate.gff multi_seq_ref.fasta query_e$errRate.fasta > subset/1_2_e$errRate.stdout

   ${STELLAR} -e $errRate -l $minLen -v --sequenceOfInterest 0 --sequenceOfInterest 1 --sequenceOfInterest 2 -o subset/0_1_2_e$errRate.gff multi_seq_ref.fasta query_e$errRate.fasta > subset/0_1_2_e$errRate.stdout

   ${STELLAR} -e $errRate -l $minLen -v -o subset/all_e$errRate.gff multi_seq_ref.fasta query_e$errRate.fasta > subset/all_e$errRate.stdout
done

############################################################
# ZERO ERRORS EDGE CASE
############################################################
minLen=1000
simulationErrRate=0.0009
searchErrRate=0
${STELLAR} -e $searchErrRate -l $minLen -v -o er_edge_case/e$searchErrRate.gff ref.fasta query_e$simulationErrRate.fasta > er_edge_case/e$searchErrRate.stdout
${STELLAR} -e $simulationErrRate -l $minLen -v -o er_edge_case/e$simulationErrRate.gff ref.fasta query_e$simulationErrRate.fasta > er_edge_case/e$simulationErrRate.stdout
