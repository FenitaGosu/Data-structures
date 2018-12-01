#pragma once

#include <optional>
#include <algorithm>
#include <iterator>
#include <functional>
#include <map>
#include <vector>
#include <string>

class Trie
{
public:
	void Insert(const std::initializer_list<std::string>& list);
	std::vector<std::vector<std::string>> GetAllSequences() const;
	std::optional<std::reference_wrapper<const Trie>> Subtrie(const std::initializer_list<std::string>& list) const;

private:
	template <typename It>
	void Insert(It itBegin, It itEnd)
	{
		if (itBegin == itEnd)
			return;

		m_tries[*itBegin].Insert(next(itBegin), itEnd);
	}

	template <typename It>
	std::optional<std::reference_wrapper<const Trie>> Subtrie(It itBegin, It itEnd) const
	{
		if (itBegin == itEnd)
			return std::ref(*this);

		const auto found = m_tries.find(*itBegin);
		if (found == std::end(m_tries))
			return {};

		return found->second.Subtrie(std::next(itBegin), itEnd);
	}

	void GetAllSequences(std::vector<std::string>& curSequences, std::vector<std::vector<std::string>>& allSequences) const;

private:
	std::map<std::string, Trie> m_tries;
};
