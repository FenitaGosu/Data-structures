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

	void Print() const
	{
		std::vector<T> v;
		Print(v);
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

	void Print(std::vector<T>& v) const
	{
		if (m_tries.empty())
		{
			std::copy(std::begin(v), std::end(v), std::ostream_iterator<T>{std::cout, " "});
			std::cout << std::endl;
		}

		for (const auto& p : m_tries)
		{
			v.push_back(p.first);
			p.second.Print(v);
			v.pop_back();
		}
	}

private:
	std::map<T, Trie> m_tries;
};

int main()
{
	Trie<std::string> t;

	t.Insert({"hi", "how", "are", "you"});
	t.Insert({"hi", "i", "am", "great", "thanks"});
	t.Insert({"what", "are", "you", "doing"});
	t.Insert({"i", "am", "watching", "a", "movie"});

	if (auto st (t.Subtrie({"hi"})); st)
		st->get().Print();
}
