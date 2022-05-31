
#pragma once

#include <stellar/utils/stellar_runtime.hpp>

namespace stellar
{

struct stellar_verification_time : public stellar_runtime
{
    stellar_runtime next_local_alignment_time;
    stellar_runtime split_at_x_drops_time;
    stellar_runtime extension_time;

    stellar_runtime total_time() const
    {
        stellar_runtime total{};
        total.manual_timing(
            next_local_alignment_time._runtime +
            split_at_x_drops_time._runtime +
            extension_time._runtime);

        return total;
    }

    void mergeIn(stellar_verification_time const & other)
    {
        _runtime += other._runtime;

        next_local_alignment_time._runtime += other.next_local_alignment_time._runtime;
        split_at_x_drops_time._runtime += other.split_at_x_drops_time._runtime;
        extension_time._runtime += other.extension_time._runtime;
    }
};

struct stellar_kernel_runtime : public stellar_runtime
{
    stellar_runtime swift_filter_time{};
    stellar_verification_time verification_time{};

    stellar_runtime total_time() const
    {
        stellar_runtime total{};
        total.manual_timing(
            swift_filter_time._runtime +
            verification_time._runtime);

        return total;
    }

    void mergeIn(stellar_kernel_runtime const & other)
    {
        _runtime += other._runtime;

        swift_filter_time._runtime += other.swift_filter_time._runtime;
        verification_time.mergeIn(other.verification_time);
    }
};

} // namespace stellar
