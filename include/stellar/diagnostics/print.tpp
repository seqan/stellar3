#pragma once

#include <stellar/diagnostics/print.hpp>

namespace stellar
{

///////////////////////////////////////////////////////////////////////////////
// Writes file name from options object to std::cout
template <typename TStream>
void _writeFileNames(StellarOptions const & options, TStream & outStr)
{
//IOREV _notio_
    outStr << "I/O options:" << std::endl;
    outStr << "  database file   : " << options.databaseFile << std::endl;
    outStr << "  query file      : " << options.queryFile << std::endl;
    outStr << "  alphabet        : " << options.alphabet << std::endl;
    outStr << "  output file     : " << options.outputFile << std::endl;
    outStr << "  output format   : " << options.outputFormat << std::endl;
    if (options.disableThresh != std::numeric_limits<size_t>::max())
    {
        outStr << "  disabled queries: " << options.disabledQueriesFile << std::endl;
    }
    outStr << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// Calculates parameters from parameters in options object and from sequences and writes them to std::cout
template <typename TStringSet, typename TSize>
void _writeMoreCalculatedParams(StellarOptions const & options, TSize const & refLen, TStringSet const & queries)
{
//IOREV _notio_
    typedef typename Value<typename Value<TStringSet>::Type>::Type TAlphabet;

    if (options.qgramAbundanceCut != 1)
    {
        std::cout << "Calculated parameters:" << std::endl;
    }

    TSize queryLength = length(concat(queries));
    if (options.qgramAbundanceCut != 1)
    {
        std::cout << "  q-gram expected abundance : ";
        std::cout << queryLength / (double)((long)1 << (options.qGram << 1)) << std::endl;
        std::cout << "  q-gram abundance threshold: ";
        std::cout << _max(100, (int)(queryLength * options.qgramAbundanceCut)) << std::endl;
        std::cout << std::endl;
    }

    if (IsSameType<TAlphabet, Dna5>::VALUE || IsSameType<TAlphabet, Rna5>::VALUE)
    {
        // Computation of maximal E-value for this search

        TSize maxLengthQueries = 0;

        typename Iterator<TStringSet const>::Type queriesIt = begin(queries);
        typename Iterator<TStringSet const>::Type queriesEnd = end(queries);
        while (queriesIt != queriesEnd)
        {
            if (length(*queriesIt) > maxLengthQueries)
            {
                maxLengthQueries = length(*queriesIt);
            }
            ++queriesIt;
        }

        TSize errors = static_cast<TSize>(options.minLength * options.epsilon);
        TSize minScore = options.minLength - 3 * errors; // #matches - 2*#errors // #matches = minLenght - errors,

        std::cout << "All matches resulting from your search have an E-value of: " << std::endl;
        std::cout << "        " << _computeEValue(minScore, maxLengthQueries, refLen) << " or smaller";
        std::cout << "  (match score = 1, error penalty = -2)" << std::endl;

        std::cout << std::endl;
    }
}

} // namespace stellar
