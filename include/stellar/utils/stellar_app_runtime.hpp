
#pragma once

#include <stellar/utils/stellar_kernel_runtime.hpp>
#include <stellar/utils/stellar_runtime.hpp>

namespace stellar
{

struct stellar_strand_time : public stellar_runtime
{
    stellar_kernel_runtime parallel_prefiltered_stellar_time{};
    stellar_runtime post_process_eps_matches_time{};
    stellar_runtime output_eps_matches_time{};

    stellar_runtime total_time() const
    {
        stellar_runtime total{};
        total.manual_timing(
            parallel_prefiltered_stellar_time._runtime +
            post_process_eps_matches_time._runtime +
            output_eps_matches_time._runtime);

        return total;
    }
};

struct stellar_app_runtime : public stellar_runtime
{
    stellar_runtime input_queries_time{};
    stellar_runtime input_databases_time{};
    stellar_runtime swift_index_construction_time{};
    stellar_strand_time forward_strand_stellar_time{};
    stellar_runtime reverse_complement_database_time{};
    stellar_strand_time reverse_strand_stellar_time{};
    stellar_runtime output_disabled_queries_time{};

    stellar_runtime total_time() const
    {
        stellar_runtime total{};
        total.manual_timing(
            input_queries_time._runtime +
            input_databases_time._runtime +
            swift_index_construction_time._runtime +
            forward_strand_stellar_time._runtime +
            reverse_complement_database_time._runtime +
            reverse_strand_stellar_time._runtime +
            output_disabled_queries_time._runtime);

        return total;
    }
};

} // namespace stellar
