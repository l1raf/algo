#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class Bitmap
{
public:
//	~Bitmap();
	Bitmap();
	Bitmap(int count);
	void set(unsigned int i);
	bool get(unsigned int i);

private:
	int count_;
	unsigned int* bits;
};

//Bitmap::~Bitmap()
//{
//	delete[] bits;
//}

Bitmap::Bitmap()
{
	bits = new unsigned int[0]();
	count_ = 0;
}

Bitmap::Bitmap(int count)
{
	bits = new unsigned int[count >> 5]{ 0 };
	count_ = count >> 5;
}

// adds the element i to a bitmap
void Bitmap::set(unsigned int i)
{
	bits[i >> 5] |= 1u << i;
}

// checks if bitmap contains the element i
bool Bitmap::get(unsigned int i)
{
	return (bits[i >> 5] & (1 << i)) != 0;
}

class BloomFilter
{
private:
	Bitmap bitmap;
	int hash1(string s);
	int hash2(string s);
	int hash3(string s);
	int m_;

public:
	double fps = 0.01;
	BloomFilter();
	BloomFilter(int m);
	void insert(string key);
	bool contains(string key);
};

BloomFilter::BloomFilter()
{
	m_ = 0;
}

BloomFilter::BloomFilter(int m)
{
	m_ = m;
	Bitmap bt(m);
	bitmap = bt;
}

int BloomFilter::hash1(string s)
{
	long long hash = 0;
	long long p_pow = 1;
	const int m = 1e9 + 9;
	int p = 53;

	for (auto c : s)
	{
		hash = (hash + (c - 'a' + 1) * p_pow) % m;
		p_pow = (p_pow * p) % m;
	}

	return hash % m_;
}

int BloomFilter::hash2(string s)
{
	long long hash = 0;

	for (auto c : s)
		hash = hash * 31 + c;

	return hash % m_;
}

int BloomFilter::hash3(string s)
{
	unsigned long hash = 5381;

	for (auto c : s)
		hash = ((hash << 5) + hash) + c; // hash * 33 + c 

	return hash % m_;
}

// inserts string value into set
void BloomFilter::insert(string key)
{
	int hashes[3] = { hash1(key), hash2(key), hash3(key) };

	for (auto h : hashes)
		bitmap.set(abs(h));
}

// checks if string value is a member of a set
bool BloomFilter::contains(string key)
{
	int hashes[3] = { hash1(key), hash2(key), hash3(key) };

	for (auto h : hashes)
		if (!bitmap.get(abs(h)))
			return false;

	return true;
}

// adds videos from file to filter and checks if user watched them
map<string, BloomFilter> process(string test_path, string output_path)
{
	map<string, BloomFilter> filters;
	fstream in(test_path, ios::in);
	ofstream out(output_path, ios::out);

	if (in.is_open() && out.is_open())
	{
		int n;
		int m;
		string str;
		string cmd;
		string user;
		string video_id;

		in >> str >> n;
		out << "Ok" << endl;
		m = round(n * 9.585);

		while (in >> cmd >> user >> video_id)
		{
			if (cmd._Equal("watch"))
			{
				if (filters.find(user) == filters.end())
				{
					BloomFilter new_bloom_filter(m);
					new_bloom_filter.insert(video_id);
					filters[user] = new_bloom_filter;
					out << "Ok" << endl;
				}
				else
				{
					BloomFilter old_bloom_filter = filters[user];
					old_bloom_filter.insert(video_id);
					filters[user] = old_bloom_filter;
					out << "Ok" << endl;
				}
			}
			else if (cmd._Equal("check"))
			{
				if (filters.find(user) != filters.end())
				{
					BloomFilter filter = filters[user];

					if (filter.contains(video_id))
						out << "Probably" << endl;
					else
						out << "No" << endl;
				}
				else
				{
					out << "No" << endl;
				}
			}
		}

		in.close();
		out.close();
	}

	return filters;
}

int main(int argc, char** argv)
{
	if (argc < 3)
		return -1;

	process(argv[1], argv[2]);
}
