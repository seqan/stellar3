
#pragma once

#include <seqan/arg_parse.h>

#include <stellar/stellar_types.hpp>

namespace stellar
{

namespace app
{

ArgumentParser::ParseResult
_parseOptions(ArgumentParser const & parser, StellarOptions & options);

void _setParser(ArgumentParser & parser);

} // namespace stellar::app

} // namespace stellar
