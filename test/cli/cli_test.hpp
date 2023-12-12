#include <gtest/gtest.h>

#include <cstdlib>               // system calls
#include <filesystem> // test directory creation
#include <sstream>               // ostringstream
#include <string>                // strings

#include <seqan3/core/debug_stream.hpp>

#pragma once

// Provides functions for CLI test implementation.
struct cli_test : public ::testing::Test
{
private:

    // Holds the original work directory where Gtest has been started.
    std::filesystem::path original_workdir{};

protected:

    // Result struct for captured streams and exit code.
    struct cli_test_result
    {
        std::string out{};
        std::string err{};
        int exit_code{};
        std::string command{};
    };

    // Invoke the app execution. The command line call should be given as separate parameters.
    template <typename... CommandItemTypes>
    cli_test_result execute_app(CommandItemTypes &&... command_items)
    {
        cli_test_result result{};

        // Assemble the command string and disable version check.
        result.command = [&command_items...]()
        {
            std::ostringstream command{};
            command << "SEQAN3_NO_VERSION_CHECK=1 " << BINDIR;
            (void)((command << command_items << ' '), ...);
            return command.str();
        }();   // from raptor

        // Always capture the output streams.
        testing::internal::CaptureStdout();
        testing::internal::CaptureStderr();

        // Run the command and return results.
        result.exit_code = std::system(result.command.c_str());
        result.out = testing::internal::GetCapturedStdout();
        result.err = testing::internal::GetCapturedStderr();
        return result;
    }

    // Generate the full path of a test input file that is provided in the data directory.
    static std::string data(std::string const & filename)
    {
        return std::filesystem::path{std::string{DATADIR}}.concat(filename).string();
    }

    // Create an individual work directory for the current test.
    void SetUp() override
    {
        // Assemble the directory name.
        ::testing::TestInfo const * const info = ::testing::UnitTest::GetInstance()->current_test_info();
        std::filesystem::path const test_dir{std::string{OUTPUTDIR} +
                                             std::string{info->test_case_name()} +
                                             std::string{"."} +
                                             std::string{info->name()}};
        try
        {
            std::filesystem::remove_all(test_dir);              // delete the directory if it exists
            std::filesystem::create_directories(test_dir);      // create the new empty directory
            original_workdir = std::filesystem::current_path(); // store original work dir path
            std::filesystem::current_path(test_dir);            // change the work dir
        }
        catch (std::exception const & exc)
        {
            FAIL() << "Failed to set up the test directory " << test_dir << ":\n" << exc.what();
        }
    }

    // Switch back to the initial work directory.
    void TearDown() override
    {
        try
        {
            std::filesystem::current_path(original_workdir);    // restore the original work dir
        }
        catch (std::exception const & exc)
        {
            FAIL() << "Failed to set the work directory to " << original_workdir << ":\n" << exc.what();
        }
    }
};

struct stellar_base : public cli_test
{
    static inline std::filesystem::path const out_path(size_t const seq, size_t const begin, size_t const end, 
                                                       std::string const er, std::string const extension) noexcept
    {
        std::string name{};
        name += std::to_string(seq);
        name += "_";
        name += std::to_string(begin);
        name += "_";
        name += std::to_string(end);
        name += "_";
        name += er;
        name += ".";
        name += extension;
        return cli_test::data(name);
    }

    static inline std::filesystem::path const out_path(std::vector<size_t> const seqVec, std::string const er, 
                                                       std::string const extension) noexcept
    {
        std::string name{};
        for (auto id : seqVec)
        {
            name += std::to_string(id);
            name += "_";
        }
        name += er;
        name += ".";
        name += extension;
        return cli_test::data(name);
    }

    static inline std::string const string_from_file(std::filesystem::path const & path, std::ios_base::openmode const mode = std::ios_base::in)
    {
        std::ifstream file_stream(path, mode);
        if (!file_stream.is_open())
            throw std::logic_error{"Cannot open " + path.string()};
        std::stringstream file_buffer;
        file_buffer << file_stream.rdbuf();
        return {file_buffer.str()};
    }
};

struct search_subset : public stellar_base, public testing::WithParamInterface<std::tuple<std::vector<size_t>, float>> {};
struct search_segment : public stellar_base, public testing::WithParamInterface<std::tuple<std::vector<size_t>, std::pair<size_t, size_t>, float>> {};
struct search_small_error: public stellar_base, public testing::WithParamInterface<float> {};
