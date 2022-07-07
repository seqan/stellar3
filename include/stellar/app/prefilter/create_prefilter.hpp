
#pragma once

namespace stellar
{

namespace app
{

template <typename TPrefilter>
struct CreatePrefilter
{
#if 0
    static std::unique_ptr<stellar::prefilter<TAlphabet>>
    create(
        StellarOptions const & options,
        StringSet<String<TAlphabet> > const & databases,
        StringSet<String<TAlphabet> > const & queries,
        StellarSwiftPattern<TAlphabet> & swiftPattern);
#endif
};

} // namespace app

} // namespace stellar
