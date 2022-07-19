
#pragma once

namespace stellar
{

struct DatabaseSplitOptions
{
    // Whether the database sequences should be split into multiple parts.
    // This can result into a slight increase in the number of Swift verifications.
    bool splitDatabase{false};

    // How many parts each database sequence should be split into.
    unsigned splitNSegments{1u};
};

} // namespace stellar
