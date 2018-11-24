#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

class BloomFilter
{
public:
	using HashFunction = std::function<unsigned int(const std::string&)>;

public:
	BloomFilter(size_t size, const std::vector<HashFunction>& hashFunctions)
		: m_data(size)
		, m_hashFunctions(hashFunctions)
	{
	}

	void AddElement(const std::string& str)
	{
		const auto size = m_data.size();
		for (const auto& hashFunc: m_hashFunctions)
			m_data[hashFunc(str) % size] = true;
	}

	bool PossiblyContains(const std::string& str) const
	{
		return std::all_of(m_hashFunctions.cbegin(), m_hashFunctions.cend(), [&str, &data = m_data, size = m_data.size()](const auto& hashFunc){ return data[hashFunc(str) % size]; });
	}

private:
	std::vector<bool> m_data;
	std::vector<HashFunction> m_hashFunctions;
};

unsigned int djb2(const std::string& str)
{
	unsigned int hash = 5381;

	for (const auto c : str)
		hash = ((hash << 5) + hash) + static_cast<unsigned int>(c);

	return hash;
}

unsigned int jenkins(const std::string& str)
{
	unsigned int hash = 0;
	for (const auto c : str)
	{
		hash += static_cast<unsigned int>(c);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

int main()
{
	std::vector<BloomFilter::HashFunction> hashFunctions =
	{
		djb2,
		jenkins,
	};

	BloomFilter filter(1024, hashFunctions);

	std::vector<std::string> data =
	{
		"Hello World!",
		"SOLID",
		"C++",
		"JAVA",
		"C#",
	};

	for (const auto& str : data)
		filter.AddElement(str);

	for (const auto& str : data)
		std::cout << str << std::endl;

	std::vector<std::string> testData =
	{
		"Hello World!",
		"PYTON",
		"C++",
		"PROLOG",
		"JAVA",
		"F#",
		"C#",
	};

	for (const auto& str : testData)
		std::cout << str << " " << filter.PossiblyContains(str) << std::endl;

	return 0;
}
