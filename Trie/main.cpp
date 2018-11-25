#include <iostream>
#include <optional>
#include <algorithm>
#include <iterator>
#include <functional>
#include <map>
#include <vector>
#include <string>

template <typename T>
class Trie
{
public:
	void Insert(const std::initializer_list<T>& list)
	{
		Insert(std::begin(list), std::end(list));
	}

	std::vector<std::vector<T>> GetAllSequences() const
	{
		std::vector<std::vector<T>> allSequences;
		std::vector<T> curSequences;
		GetAllSequences(curSequences, allSequences);

		return allSequences;
	}

	std::optional<std::reference_wrapper<const Trie>> Subtrie(const std::initializer_list<T>& list) const
	{
		return Subtrie(std::begin(list), std::end(list));
	}

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
			return ref(*this);

		const auto found = m_tries.find(*itBegin);
		if (found == std::end(m_tries))
			return {};

		return found->second.Subtrie(std::next(itBegin), itEnd);
	}

	void GetAllSequences(std::vector<T>& curSequences, std::vector<std::vector<T>>& allSequences) const
	{
		if (m_tries.empty())
			allSequences.push_back(curSequences);

		for (const auto& p : m_tries)
		{
			curSequences.push_back(p.first);
			p.second.GetAllSequences(curSequences, allSequences);
			curSequences.pop_back();
		}
	}


private:
	std::map<T, Trie> m_tries;
};

int main()
{
	Trie<std::string> t;

	t.Insert({"hi", "how", "are", "you"});
	t.Insert({"what", "are", "you", "doing"});
	t.Insert({"i", "am", "watching", "a", "movie"});
	t.Insert({"hi", "i", "am", "great", "thanks"});

	const auto subTrie = t.Subtrie({"hi"});

	if (subTrie)
	{
		const auto allSequences = subTrie->get().GetAllSequences();
		for (const auto& sequences : allSequences)
		{
			std::copy(std::cbegin(sequences), std::cend(sequences), std::ostream_iterator<std::string>{std::cout, " "});
			std::cout << std::endl;
		}
	}

	return 0;
}
