#pragma once

#include <stellar/app/stellar.diagnostics.hpp>

namespace stellar
{

namespace app
{

///////////////////////////////////////////////////////////////////////////////
// Calculates parameters from parameters in options object and writes them to std::cout
void _writeCalculatedParams(StellarOptions & options)
{
//IOREV _notio_
    StellarStatistics statistics{options};

    std::cout << "Calculated parameters:" << std::endl;
    if (statistics.kMerComputed)
    {
        options.qGram = (unsigned)statistics.kMerLength;
        std::cout << "  k-mer length : " << statistics.kMerLength << std::endl;
    }

    std::cout << "  s^min        : " << statistics.smin << std::endl;
    std::cout << "  threshold    : " << statistics.threshold << std::endl;
    std::cout << "  distance cut : " << statistics.distanceCut << std::endl;
    std::cout << "  delta        : " << statistics.delta << std::endl;
    std::cout << "  overlap      : " << statistics.overlap << std::endl;
    std::cout << std::endl;
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

} // namespace stellar::app

} // namespace stellar
