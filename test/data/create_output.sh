#!/bin/bash

STELLAR=../../build/bin/stellar

rm *_*_*_*.gff
rm full_*.gff
rm multi_all_*.gff
rm *_*_*_*.stdout
rm full_*.stdout
rm multi_all_*.stdout

minLen=50
for errRate in 0 0.05
do
   ############################################################
   # SEGMENT SEARCH
   ############################################################

   call_stellar_on_segment () {
      ${STELLAR} -e $errRate -l $minLen -v --sequenceOfInterest 0 --segmentBegin $1 --segmentEnd $2 -o 0_$1_$2_$errRate.gff ref.fasta query_e$errRate.fasta > 0_$1_$2_$errRate.stdout
   }

   call_stellar_on_segment 0 400
   call_stellar_on_segment 500 800

   ${STELLAR} -e $errRate -l $minLen -v -o full_e$errRate.gff ref.fasta query_e$errRate.fasta > full_e$errRate.stdout

   ############################################################
   # SUBSET SEARCH
   ############################################################

   ${STELLAR} -e $errRate -l $minLen -v --sequenceOfInterest 1 -o 1_$errRate.gff multi_seq_ref.fasta query_e$errRate.fasta > 1_$errRate.stdout

   ${STELLAR} -e $errRate -l $minLen -v --sequenceOfInterest 0 --sequenceOfInterest 1 -o 0_1_$errRate.gff multi_seq_ref.fasta query_e$errRate.fasta > 0_1_$errRate.stdout

   ${STELLAR} -e $errRate -l $minLen -v --sequenceOfInterest 1 --sequenceOfInterest 2 -o 1_2_$errRate.gff multi_seq_ref.fasta query_e$errRate.fasta > 1_2_$errRate.stdout

   ${STELLAR} -e $errRate -l $minLen -v --sequenceOfInterest 0 --sequenceOfInterest 1 --sequenceOfInterest 2 -o 0_1_2_$errRate.gff multi_seq_ref.fasta query_e$errRate.fasta > 0_1_2_$errRate.stdout

   ${STELLAR} -e $errRate -l $minLen -v -o multi_all_$errRate.gff multi_seq_ref.fasta query_e$errRate.fasta > multi_all_$errRate.stdout
done

# Very small error rate edge case
minLen=1000
simulationErrRate=0.0009
searchErrRate=0
${STELLAR} -e $searchErrRate -l $minLen -v -o edge_case_e$searchErrRate.gff ref.fasta query_e$simulationErrRate.fasta > edge_case_e$searchErrRate.stdout
${STELLAR} -e $simulationErrRate -l $minLen -v -o edge_case_e$simulationErrRate.gff ref.fasta query_e$simulationErrRate.fasta > edge_case_e$simulationErrRate.stdout
