#pragma once

#include <functional>
#include <vector>
#include <algorithm>
#include <string>

class BloomFilter
{
public:
	using HashFunction = std::function<unsigned int(const std::string&)>;

public:
	BloomFilter(size_t size, const std::vector<HashFunction>& hashFunctions);

	void AddElement(const std::string& str);

	bool PossiblyContains(const std::string& str) const;

private:
	std::vector<bool> m_data;
	std::vector<HashFunction> m_hashFunctions;
};
