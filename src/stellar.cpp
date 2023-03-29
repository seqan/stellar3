// ==========================================================================
//                    STELLAR - SwifT Exact LocaL AligneR
//                   http://www.seqan.de/projects/stellar/
// ==========================================================================
// Copyright (C) 2010-2012 by Birte Kehr
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your options) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// ==========================================================================
// Author: Birte Kehr <birte.kehr@fu-berlin.de>
// ==========================================================================

#include <sharg/all.hpp>

#include <seqan/arg_parse.h>
#include <seqan/index.h>
#include <seqan/seq_io.h>

#include <stellar/stellar.hpp>
#include <stellar/stellar_output.hpp>

#include <stellar/app/stellar.diagnostics.hpp>
#include <stellar/app/stellar.main.hpp>

#include <stellar3.arg_parser.hpp>
#include "stellar/stellar.diagnostics.cpp"

// TODO(holtgrew): Move this into a SeqAn misc module.

// not supported anymore in vc2015
// https://msdn.microsoft.com/en-us/library/bb531344.aspx
class ScientificNotationExponentOutputNormalizer
{
public:
    unsigned _oldExponentFormat;

    ScientificNotationExponentOutputNormalizer() :
        _oldExponentFormat(0)
    {
    }

    ~ScientificNotationExponentOutputNormalizer()
    {
    }
};

///////////////////////////////////////////////////////////////////////////////
// Program entry point.
int main(int argc, const char * argv[])
{
    // Makes sure that printing doubles in scientific notation is normalized on all platforms.
    ScientificNotationExponentOutputNormalizer scientificNotationNormalizer;

    // command line parsing
    try
    {
        stellar::StellarOptions options{};
        sharg::parser parser{"stellar3", argc, argv};
        stellar::app::run_stellar(parser);
    }
    catch(sharg::parser_error const & ext)
    {
        std::cerr << "[Error] " << ext.what() << "\n";
    }
    catch(std::exception const& e)
    {
        std::cerr << "[Error] " << e.what() << '\n';
        std::exit(-1);
    }
    catch(...)
    {
        std::cerr << "[Error] unknown exception type\n";
        std::exit(-1);
    }

    return 0;
}
