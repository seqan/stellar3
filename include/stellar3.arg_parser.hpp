#pragma once

#include <sharg/all.hpp>

#include <stellar/app/stellar.main.tpp>
#include <stellar/options/verifier_options.hpp>

#include <stellar3.shared.hpp>

namespace stellar::app
{

void init_parser(sharg::parser & parser, StellarOptions & options);
void run_stellar(sharg::parser & parser);

} // namespace stellar::app
