#include "stellar.diagnostics.hpp"

namespace stellar
{

namespace app
{

///////////////////////////////////////////////////////////////////////////////
// Calculates parameters from parameters in options object and writes them to std::cout
void _writeCalculatedParams(StellarOptions & options)
{
//IOREV _notio_
    int errMinLen = (int) floor(options.epsilon * options.minLength);
    int n = (int) ceil((errMinLen + 1) / options.epsilon);
    int errN = (int) floor(options.epsilon * n);
    unsigned smin = (unsigned) _min(ceil((double)(options.minLength - errMinLen) / (errMinLen + 1)),
                                    ceil((double)(n - errN) / (errN + 1)));

    std::cout << "Calculated parameters:" << std::endl;
    if (options.qGram == (unsigned)-1)
    {
        options.qGram = (unsigned)_min(smin, 32u);
        std::cout << "  k-mer length : " << options.qGram << std::endl;
    }

    int threshold = (int) _max(1, (int) _min((n + 1) - options.qGram * (errN + 1),
                                             (options.minLength + 1) - options.qGram * (errMinLen + 1)));
    int overlap = (int) floor((2 * threshold + options.qGram - 3) / (1 / options.epsilon - options.qGram));
    int distanceCut = (threshold - 1) + options.qGram * overlap + options.qGram;
    int logDelta = _max(4, (int) ceil(log((double)overlap + 1) / log(2.0)));
    int delta = 1 << logDelta;

    std::cout << "  s^min        : " << smin << std::endl;
    std::cout << "  threshold    : " << threshold << std::endl;
    std::cout << "  distance cut : " << distanceCut << std::endl;
    std::cout << "  delta        : " << delta << std::endl;
    std::cout << "  overlap      : " << overlap << std::endl;
    std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// Writes user specified parameters from options object to std::cout
void _writeSpecifiedParams(StellarOptions const & options)
{
//IOREV _notio_
    // Output user specified parameters
    std::cout << "User specified parameters:" << std::endl;
    std::cout << "  minimal match length             : " << options.minLength << std::endl;
    std::cout << "  maximal error rate (epsilon)     : " << options.epsilon << std::endl;
    std::cout << "  maximal x-drop                   : " << options.xDrop << std::endl;
    if (options.qGram != (unsigned)-1)
        std::cout << "  k-mer (q-gram) length            : " << options.qGram << std::endl;
    std::cout << "  search forward strand            : " << ((options.forward) ? "yes" : "no") << std::endl;
    std::cout << "  search reverse complement        : " << ((options.reverse) ? "yes" : "no") << std::endl;
    std::cout << std::endl;

    std::cout << "  verification strategy            : " << options.fastOption << std::endl;
    if (options.disableThresh != (unsigned)-1)
    {
        std::cout << "  disable queries with more than   : " << options.disableThresh << " matches" << std::endl;
    }
    std::cout << "  maximal number of matches        : " << options.numMatches << std::endl;
    std::cout << "  duplicate removal every          : " << options.compactThresh << std::endl;
    if (options.maxRepeatPeriod != 1 || options.minRepeatLength != 1000)
    {
        std::cout << "  max low complexity repeat period : " << options.maxRepeatPeriod << std::endl;
        std::cout << "  min low complexity repeat length : " << options.minRepeatLength << std::endl;
    }
    if (options.qgramAbundanceCut != 1)
    {
        std::cout << "  q-gram abundance cut ratio       : " << options.qgramAbundanceCut << std::endl;
    }
    std::cout << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// Writes file name from options object to std::cout
void _writeFileNames(StellarOptions const & options)
{
//IOREV _notio_
    std::cout << "I/O options:" << std::endl;
    std::cout << "  database file   : " << options.databaseFile << std::endl;
    std::cout << "  query file      : " << options.queryFile << std::endl;
    std::cout << "  alphabet        : " << options.alphabet << std::endl;
    std::cout << "  output file     : " << options.outputFile << std::endl;
    std::cout << "  output format   : " << options.outputFormat << std::endl;
    if (options.disableThresh != (unsigned)-1)
    {
        std::cout << "  disabled queries: " << options.disabledQueriesFile << std::endl;
    }
    std::cout << std::endl;
}

} // namespace stellar::app

} // namespace stellar
