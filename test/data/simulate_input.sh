#!/bin/bash
cd "$(dirname "$0")"
set -Eeuo pipefail

# might need to move mason_genome binary
REF_SEED=42 # was 20181406 before, but was hardcoded to 42 in seqan
QUERY_SEED=43
BIN_NUMBER=8
HAPLOTYPE_COUNT=2

execs=(stellar generate_local_matches mason_genome)
for exec in "${execs[@]}"; do
    if ! which ${exec} &>/dev/null; then
        echo "${exec} is not available"
        echo ""
        echo "make sure \"${execs[@]}\" are reachable via the \${PATH} variable"
        echo ""

        # trying to do some guessing here:
        paths+=(../../lib/raptor_data_simulation/build/bin)
        paths+=(../../lib/raptor_data_simulation/build/src/mason2/src/mason2-build/bin)
        paths+=(../../build/bin)

        p=""
        for pp in ${paths[@]}; do
            p=${p}$(realpath -m $pp):
        done
        echo "you could try "
        echo "export PATH=${p}\${PATH}"

        exit 127
    fi
done

length=2000
match_length=50
match_count=10
echo "Simulating genome with $length"
mason_genome -l $length -o ref.fasta -s $REF_SEED &>/dev/null
echo "Simulating genome with $length"
mason_genome -l $length -o query.fasta -s $QUERY_SEED &>/dev/null

for error_rate in 0 0.05
do
    #----------- Sample reads from reference sequence -----------
    echo "Generating $match_count reads of length $match_length with error rate $error_rate"
    generate_local_matches \
        --matches-out matches_e$error_rate.fasta \
        --genome-out query_e$error_rate.fasta \
        --max-error-rate $error_rate \
        --num-matches $match_count \
        --min-match-length $match_length \
        --max-match-length $match_length \
        --verbose-ids \
        --reverse \
        --ref-len $length \
        --query query.fasta \
        --seed $REF_SEED \
        ref.fasta 
done

# Low error rate edge case
error_rate=0.0009
match_count=1
match_length=1150
echo "Generating $match_count reads of length $match_length with error rate $error_rate"
generate_local_matches \
        --matches-out matches_e$error_rate.fasta \
        --genome-out query_e$error_rate.fasta \
        --max-error-rate $error_rate \
        --num-matches $match_count \
        --min-match-length $match_length \
        --max-match-length $match_length \
        --verbose-ids \
        --ref-len $length \
        --query query.fasta \
        --seed $REF_SEED \
        ref.fasta 

rm query.fasta
rm matches_e*.fasta

echo "Divide reference sequence into chromosomes"

awk '/^>/ {printf("\n%s\n",$0);next; } { printf("%s",$0);}  END {printf("\n");}' < ref.fasta | grep -v ">" | cut -c 1-560 > single_line.fasta
sed -i "1s/.*/>chr1/" single_line.fasta
fold -w 70 single_line.fasta > chr1.fasta 

awk '/^>/ {printf("\n%s\n",$0);next; } { printf("%s",$0);}  END {printf("\n");}' < ref.fasta | grep -v ">" | cut -c 560-1200 > single_line.fasta
sed -i "1s/.*/>chr2/" single_line.fasta
fold -w 70 single_line.fasta > chr2.fasta

awk '/^>/ {printf("\n%s\n",$0);next; } { printf("%s",$0);}  END {printf("\n");}' < ref.fasta | grep -v ">" | cut -c 776-1000 > single_line.fasta
sed -i "1s/.*/>chr3/" single_line.fasta
fold -w 70 single_line.fasta > chr3.fasta

rm single_line.fasta
cat chr*.fasta > multi_seq_ref.fasta
rm chr*.fasta
