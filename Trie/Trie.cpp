#include "Trie.h"

void Trie::Insert(const std::initializer_list<std::string> &list)
{
	Insert(std::begin(list), std::end(list));
}

std::vector<std::vector<std::string> > Trie::GetAllSequences() const
{
	std::vector<std::vector<std::string>> allSequences;
	std::vector<std::string> curSequences;
	GetAllSequences(curSequences, allSequences);

	return allSequences;
}

std::optional<std::reference_wrapper<const Trie> > Trie::Subtrie(const std::initializer_list<std::string> &list) const
{
	return Subtrie(std::begin(list), std::end(list));
}

void Trie::GetAllSequences(std::vector<std::string> &curSequences, std::vector<std::vector<std::string> > &allSequences) const
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
