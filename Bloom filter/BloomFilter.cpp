#include "BloomFilter.h"

BloomFilter::BloomFilter(size_t size, const std::vector<BloomFilter::HashFunction> &hashFunctions)
	: m_data(size)
	, m_hashFunctions(hashFunctions)
{
}

void BloomFilter::AddElement(const std::string &str)
{
	const auto size = m_data.size();
	for (const auto& hashFunc: m_hashFunctions)
		m_data[hashFunc(str) % size] = true;
}

bool BloomFilter::PossiblyContains(const std::string &str) const
{
	return std::all_of(m_hashFunctions.cbegin(), m_hashFunctions.cend(), [&str, &data = m_data, size = m_data.size()](const auto& hashFunc){ return data[hashFunc(str) % size]; });
}
