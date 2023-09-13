# STELLAR3 - the SwifT Exact LocaL AligneR
This is similar to [STELLAR](https://github.com/seqan/seqan/tree/master/apps/stellar) but uses the [sharg parser](https://docs.seqan.de/seqan3/3-master-user/tutorial_argument_parser.html) and can be used to narrow the search to only a segment of the reference database.

## Building Stellar3:
1. clone this repository: `git clone --recurse-submodules https://github.com/seqan/stellar3`
2. create a build directory and visit it: `mkdir stellar3/build && cd $_`
3. run cmake: `cmake ..`
4. build the application: `make`
5. show the help page: `./bin/stellar --help`

## Running Stellar3:
The `example` folder contains example data for a test run. Stellar3 can be used to produce soft-clipped read alignments or to find all local alignments between two genomes.

Searching the reference sequences for local alignments with a minimum length of 50 and a maximum error rate of 0.02:
`./bin/stellar -e 0.02 -l 50 -o mapped.reads.gff ../example/NC_001477.fasta ../example/reads.fasta`

Searching only a segment of the reference for local alignments:
`./bin/stellar --sequenceOfInterest 0 --segmentBegin 5000 --segmentEnd 7500 -e 0.02 -l 50 -o segment.mapped.reads.gff ../example/NC_001477.fasta ../example/reads.fasta`

Finding all local alignments between two related genomes:
`./bin/stellar -e 0.1 -l 50 -o alignments.gff ../example/NC_001474.fasta ../example/NC_001477.fasta`

See the original [documentation](https://github.com/seqan/seqan/tree/main/apps/stellar) for details on the Stellar output formats.
