
#pragma once

#include <stellar/stellar_types.hpp>

namespace stellar
{

namespace app
{

///////////////////////////////////////////////////////////////////////////////
// Parses and outputs parameters, calls _stellarMain().
template <typename TAlphabet>
int mainWithOptions(StellarOptions & options, String<TAlphabet>);

} // namespace stellar::app

} // namespace stellar
