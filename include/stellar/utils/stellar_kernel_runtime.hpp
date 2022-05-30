
#pragma once

#include <stellar/utils/stellar_runtime.hpp>

namespace stellar
{

struct stellar_kernel_runtime : public stellar_runtime
{
    stellar_runtime swift_filter_time{};
    stellar_runtime verification_time{};

    stellar_runtime total_time() const
    {
        stellar_runtime total{};
        total.manual_timing(
            swift_filter_time._runtime +
            verification_time._runtime);

        return total;
    }
};

} // namespace stellar
