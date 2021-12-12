
#pragma once

#include "../stellar_types.h"

///////////////////////////////////////////////////////////////////////////////
// Parses and outputs parameters, calls _stellarOnAll().
template <typename TAlphabet>
int mainWithOptions(StellarOptions & options, String<TAlphabet>);
