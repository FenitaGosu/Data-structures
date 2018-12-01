#include <iostream>
#include <optional>
#include <algorithm>
#include <string>

#include "Trie.h"

int main()
{
	Trie t;

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
