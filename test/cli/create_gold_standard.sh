#!/bin/bash

set -ex

# hack to stop seqan.app_tests from complaining about relative paths
for eps in "e-1" "75e-3" "5e-2" "25e-3" "e-4"
do
    ln -s ../512_simSeq1_$eps.fa gold_standard/512_simSeq1_$eps.fa
    ln -s ../512_simSeq2_$eps.fa gold_standard/512_simSeq2_$eps.fa
done

com_file=commands.txt
echo "./gold_standard_for.sh both dna" > $com_file
echo "./gold_standard_for.sh both dna5" >> $com_file
echo "./gold_standard_for.sh both char" >> $com_file
echo "./gold_standard_for.sh both protein" >> $com_file

echo "./gold_standard_for.sh forward dna" >> $com_file
echo "./gold_standard_for.sh forward dna5" >> $com_file
echo "./gold_standard_for.sh forward char" >> $com_file
echo "./gold_standard_for.sh forward protein" >> $com_file

echo "./gold_standard_for.sh reverse dna" >> $com_file
echo "./gold_standard_for.sh reverse dna5" >> $com_file
echo "./gold_standard_for.sh reverse char" >> $com_file
echo "./gold_standard_for.sh reverse protein" >> $com_file

parallel --jobs 6 < $com_file
rm $com_file

for eps in "e-1" "75e-3" "5e-2" "25e-3" "e-4"
do
    rm gold_standard/512_simSeq1_$eps.fa
    rm gold_standard/512_simSeq2_$eps.fa
done