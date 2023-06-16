#include <stellar3.arg_parser.hpp>

namespace stellar::app
{

struct float_in_range_validator
{
    using option_value_type = double; // used for all arithmetic types

    option_value_type min;
    option_value_type max;

    float_in_range_validator(option_value_type min_value, option_value_type max_value) : min{min_value}, max{max_value} {}

    void operator()(option_value_type const & val) const
    {
        if ((min >= val) || (val >= max))
        {
            throw sharg::validation_error{"Value must be in range [" + std::to_string(min) +
                                          ", " + std::to_string(max) + "]."};
        }
    }

    std::string get_help_page_message() const
    {
        return "Value must be in range [" + std::to_string(min) +
                ", " + std::to_string(max) + "].";
    }
};

struct sequence_vector_validator
{
    using el_value_type = size_t; // used for all arithmetic types
    using option_value_type = std::vector<el_value_type>;

    el_value_type min;
    el_value_type max;

    sequence_vector_validator(el_value_type min_value, el_value_type max_value) : min{min_value}, max{max_value} {}

    void operator()(option_value_type const & val_vec) const
    {
        // sharg::validator can't accept std::unordered_set type arguments directly
        std::unordered_set<el_value_type> unique_set{};
        for (auto val : val_vec)
        {
            unique_set.emplace(val);
            if ((val < min || val > max))
            {
                throw sharg::validation_error{"Sequence indices must be in range [" + std::to_string(min) +
                                              ", " + std::to_string(max) + "]."};
            }
        }

        if (unique_set.size() < val_vec.size())
            throw sharg::validation_error{"Sequence indices must be unique."};
    }

    std::string get_help_page_message() const
    {
        return "Sequence indices must be unique and in range [" + std::to_string(min) +
                ", " + std::to_string(max) + "].";
    }
};

void init_parser(sharg::parser & parser, StellarOptions & options)
{
    parser.info.app_name = "stellar3";
    parser.info.author = "Birte Kehr";
    parser.info.email = "birte.kehr@fu-berlin.de";

    parser.info.short_copyright = "BSD 3-Clause License";
    parser.info.short_description = "Stellar3 is a local aligner for distributed computing.";
    parser.info.url = "https://github.com/seqan/stellar3";
    parser.info.version = "1.0";
    parser.info.description.emplace_back("Kehr, B., Weese, D., Reinert, K.: STELLAR: fast and exact local alignments. BMC Bioinformatics, "
                                         "12(Suppl 9):S15, 2011.");

    parser.info.examples = {"./valik split --help", "./valik build --help", "./valik search --help", "./valik consolidate --help"};

    parser.add_positional_option(options.databaseFile,
                    sharg::config{.description = "The database of sequences. "
                                                "Each database sequence will be compared to each query sequence.",
                                 .validator = sharg::input_file_validator{{"fa", "fasta"}}});
    parser.add_positional_option(options.queryFile,
                    sharg::config{.description = "Query sequences.",
                                 .validator = sharg::input_file_validator{{"fa", "fasta"}}});
    parser.add_option(options.numEpsilon,
                    sharg::config{.short_id = 'e',
                                    .long_id = "epsilon",
                                    .description = "Maximal error rate (max 0.25).",
                                    .validator = float_in_range_validator{0, 0.25}});
    parser.add_option(options.minLength,
                    sharg::config{.short_id = 'l',
                                    .long_id = "minLength",
                                    .description = "Maximal error rate (max 0.25).",
                                    .validator = sharg::arithmetic_range_validator{20, 1000}});
    parser.add_flag(options.onlyForward,
                    sharg::config{.short_id = 'f',
                                    .long_id = "forward",
                                    .description = "Search only in forward strand."});
    parser.add_flag(options.onlyReverse,
                    sharg::config{.short_id = 'r',
                                    .long_id = "reverse",
                                    .description = "Search only in reverse strand."});
    parser.add_option(options.alphabet,
                    sharg::config{.short_id = 'a',
                                    .long_id = "alphabet",
                                    .description = "Alphabet type of input sequences. One of {dna, rna, dna5, rna5, protein, char}",
                                    .validator = sharg::value_list_validator{"dna", "rna", "dna5", "rna5", "protein", "char"}});
    parser.add_flag(options.verbose,
                    sharg::config{.short_id = 'v',
                                    .long_id = "verbose",
                                    .description = "Set verbose output"});


    // DREAM options
    parser.add_option(options.referenceLength,
                sharg::config{.short_id = '\0',
                                .long_id = "referenceLength",
                                .description = "Reference database length.",
                                .validator = sharg::arithmetic_range_validator{(uint64_t) 0, std::numeric_limits<uint64_t>::max()}});
                                // numeric limits results in different int types between macOS or linux compilers
    parser.add_option(options.binSequences,
                sharg::config{.short_id = '\0',
                                .long_id = "sequenceOfInterest",
                                .description = "Database sequences (0-based).",
                                .validator = sequence_vector_validator{0u, std::numeric_limits<size_t>::max()}});
    parser.add_option(options.segmentBegin,
                sharg::config{.short_id = '\0',
                                .long_id = "segmentBegin",
                                .description = "Segment begin in (single) database sequence.",
                                .validator = sharg::arithmetic_range_validator{0u, std::numeric_limits<uint32_t>::max()}});
    parser.add_option(options.segmentEnd,
                sharg::config{.short_id = '\0',
                                .long_id = "segmentEnd",
                                .description = "Segment end in (single) database sequence.",
                                .validator = sharg::arithmetic_range_validator{0u, std::numeric_limits<uint32_t>::max()}});

    // Filtering options
    parser.add_option(options.qGram,
                sharg::config{.short_id = 'k',
                                .long_id = "kmer",
                                .description = "Length of the q-grams.",
                                .validator = sharg::arithmetic_range_validator{1, 32}});
    parser.add_option(options.maxRepeatPeriod,
                sharg::config{.short_id = '\0',
                                .long_id = "repeatPeriod",
                                .description = "Maximal period of low complexity repeats to be filtered.",
                                .validator = sharg::arithmetic_range_validator{1, 32}});
    parser.add_option(options.minRepeatLength,
                sharg::config{.short_id = '\0',
                                .long_id = "repeatLength",
                                .description = "Minimal length of low complexity repeats to be filtered.",
                                .validator = sharg::arithmetic_range_validator{1u, std::numeric_limits<uint32_t>::max()}});
    parser.add_option(options.qgramAbundanceCut,
                sharg::config{.short_id = 'c',
                                .long_id = "abundanceCut",
                                .description = "k-mer overabundance cut ratio.",
                                .validator = float_in_range_validator{0, 1}});

    // Verification options
    parser.add_option(options.xDrop,
                sharg::config{.short_id = 'x',
                                .long_id = "xDrop",
                                .description = "Maximal x-drop for extension."});
    parser.add_option(options.strVerificationMethod,
                sharg::config{.short_id = '\0',
                                .long_id = "verification",
                                .description = "Verification strategy: exact or bestLocal or bandedGlobal.",
                                .validator = sharg::value_list_validator{"exact", "bestLocal", "bandedGlobal", "bandedGlobalExtend"}});
    parser.add_option(options.disableThresh,
                sharg::config{.short_id = '\0',
                                .long_id = "disableThresh",
                                .description = "Maximal number of verified matches before disabling verification for one query sequence (default infinity).",
                                .validator = sharg::arithmetic_range_validator{1, 10000}});
    parser.add_option(options.numMatches,
                sharg::config{.short_id = 'n',
                                .long_id = "numMatches",
                                .description = "Maximal number of kept matches per query and database. If STELLAR finds more matches, only the longest ones are kept."});
    parser.add_option(options.compactThresh,
                sharg::config{.short_id = 's',
                                .long_id = "sortThresh",
                                .description = "Number of matches triggering removal of duplicates. Choose a smaller value for saving space."});

    // Output options
    parser.add_option(options.outputFile,
                sharg::config{.short_id = 'o',
                                .long_id = "out",
                                .description = "Name of output file.",
                                .validator = sharg::output_file_validator{sharg::output_file_open_options::open_or_create, {"gff", "txt"}}});
    parser.add_option(options.disabledQueriesFile,
                sharg::config{.short_id = '\0',
                                .long_id = "disabledQueriesFile",
                                .description = "Name of output file for disabled query sequences.",
                                .validator = sharg::output_file_validator{sharg::output_file_open_options::open_or_create, {"fa", "fasta"}}});
    parser.add_flag(options.write_time,
                sharg::config{.short_id = '\0',
                                .long_id = "time",
                                .description = "Write running time."});
}

void run_stellar(sharg::parser & parser)
{
    StellarOptions options{};
    init_parser(parser, options);
    parser.parse();

    if (options.onlyForward && !options.onlyReverse)
        options.reverse = false;
    if (options.onlyReverse && !options.onlyForward)
        options.forward = false;

    if ( parser.is_option_set("sequenceOfInterest") )
    {
        options.prefilteredSearch = true;

        if (options.binSequences.size() > 1 && (parser.is_option_set("segmentBegin") || parser.is_option_set("segmentEnd")))
            throw sharg::parser_error{"Invalid parameter value: can't pick segment from list of sequences\n"};

        if (options.binSequences.size() == 1 && parser.is_option_set("segmentBegin") && parser.is_option_set("segmentEnd"))
            options.searchSegment = true;
    }

    options.outputFormat = options.outputFile.substr(options.outputFile.size() - 3);    // file extension previously validated
    options.epsilon = stellar::utils::fraction::from_double(options.numEpsilon).limit_denominator();

    if (options.strVerificationMethod == to_string(StellarVerificationMethod{AllLocal{}}))
        options.verificationMethod = StellarVerificationMethod{AllLocal{}};
    else if (options.strVerificationMethod == to_string(StellarVerificationMethod{BestLocal{}}))
        options.verificationMethod = StellarVerificationMethod{BestLocal{}};
    else if (options.strVerificationMethod == to_string(StellarVerificationMethod{BandedGlobal{}}))
        options.verificationMethod = StellarVerificationMethod{BandedGlobal{}};
    else if (options.strVerificationMethod == to_string(StellarVerificationMethod{BandedGlobalExtend{}}))
        options.verificationMethod = StellarVerificationMethod{BandedGlobalExtend{}};
    else
        throw sharg::parser_error{"Invalid parameter value: Please choose one of the --verification={exact, bestLocal, bandedGlobal, bandedGlobalExtend}\n"};

    if (parser.is_option_set("kmer") && options.qGram >= 1 / options.epsilon)
        throw sharg::parser_error{"Invalid parameter value: Please choose q-gram length lower than 1/epsilon.\n"};

    if (options.numMatches > options.compactThresh)
        throw sharg::parser_error{"Invalid parameter values: Please choose numMatches <= sortThresh.\n"};

    if (options.alphabet == "dna")
        stellar::app::mainWithOptions(options, seqan2::String<seqan2::Dna>());
    else if (options.alphabet == "dna5")
        stellar::app::mainWithOptions(options, seqan2::String<seqan2::Dna5>());
    else if (options.alphabet == "rna")
        stellar::app::mainWithOptions(options, seqan2::String<seqan2::Rna>());
    else if (options.alphabet == "rna5")
        stellar::app::mainWithOptions(options, seqan2::String<seqan2::Rna5>());
    else if (options.alphabet == "protein")
        stellar::app::mainWithOptions(options, seqan2::String<seqan2::AminoAcid>());
    else if (options.alphabet == "char")
        stellar::app::mainWithOptions(options, seqan2::String<char>());
}

} // namespace stellar::app
