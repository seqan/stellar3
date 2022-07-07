
#pragma once

#include <stellar/prefilter/prefilter_agent.hpp>

namespace stellar
{

template <typename TAlphabet_>
struct prefilter_agents
{
    using TPrefilterAgentBase = prefilter_agent<TAlphabet_>;

    template <typename TPrefilterAgentDerived>
    prefilter_agents(std::vector<TPrefilterAgentDerived> agents)
    {
        static_assert(std::is_base_of_v<TPrefilterAgentBase, TPrefilterAgentDerived>);

        _agents_ptr.reserve(agents.size());
        for (auto & agent : agents)
        {
            emplace_back<TPrefilterAgentDerived>(std::move(agent));
        }
    }

    prefilter_agents() = default;
    prefilter_agents(prefilter_agents &&) = default;
    prefilter_agents(prefilter_agents const &) = delete;
    prefilter_agents & operator=(prefilter_agents &&) = default;
    prefilter_agents & operator=(prefilter_agents const &) = delete;

    ~prefilter_agents()
    {
        for (TPrefilterAgentBase * _agent_ptr : _agents_ptr)
            delete _agent_ptr;
    }

    template <typename TPrefilterAgentDerived, typename... TArgs>
    void emplace_back(TArgs && ...args)
    {
        _agents_ptr.push_back(new TPrefilterAgentDerived{std::forward<TArgs>(args)...});
    }

    void reserve(size_t new_cap)
    {
        _agents_ptr.reserve(new_cap);
    }

    struct iterator;

    iterator begin()
    {
        return iterator{_agents_ptr.begin()};
    }

    iterator end()
    {
        return iterator{_agents_ptr.end()};
    }

    size_t size() const
    {
        return _agents_ptr.size();
    }

    struct iterator
    {
        using difference_type = std::ptrdiff_t;
        using value_type = TPrefilterAgentBase;
        using reference_type = TPrefilterAgentBase &;

        iterator & operator++()
        {
            ++base;
            return *this;
        }

        iterator operator++(int)
        {
            return {base++};
        }

        iterator & operator--()
        {
            --base;
            return *this;
        }

        iterator operator--(int)
        {
            return {base--};
        }

        iterator & operator+=(difference_type const n)
        {
            base += n;
            return *this;
        }

        iterator & operator-=(difference_type const n)
        {
            base -= n;
            return *this;
        }

        iterator operator+(difference_type const n) const
        {
            return {base + n};
        }

        iterator operator-(difference_type const n) const
        {
            return {base - n};
        }

        friend iterator operator+(difference_type const n, iterator const & self)
        {
            return self + n;
        }

        friend difference_type operator-(iterator const & a, iterator const & b)
        {
            return a.base - b.base;
        }

        reference_type operator*() const
        {
            return **base;
        }

        reference_type operator[](size_t const i) const
        {
            return *base[i];
        }

        friend bool operator==(iterator const & a, iterator const & b)
        {
            return a.base == b.base;
        }

        friend bool operator!=(iterator const & a, iterator const & b)
        {
            return a.base != b.base;
        }

        friend auto operator<(iterator const & a, iterator const & b)
        {
            return a.base < b.base;
        }

        friend auto operator<=(iterator const & a, iterator const & b)
        {
            return a.base <= b.base;
        }

        friend auto operator>(iterator const & a, iterator const & b)
        {
            return a.base > b.base;
        }

        friend auto operator>=(iterator const & a, iterator const & b)
        {
            return a.base >= b.base;
        }

        typename std::vector<TPrefilterAgentBase*>::iterator base;
    };

    std::vector<TPrefilterAgentBase*> _agents_ptr{};
};

} // namespace stellar
