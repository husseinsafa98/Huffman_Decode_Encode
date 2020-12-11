//to run enter file name "tx1.txt
#include <bitset>
#include <iostream>
#include <fstream>
#include "Huffman.h"
using namespace std;
//convert to bit
class OBitStream
{
public:
	OBitStream(std::ostream& output) : output_(output) {}

	~OBitStream()
	{
		forceUpdate();
	}

	void writeBit(unsigned b)
	{
		buf_ = buf_ | ((b & 1u) << nBits_);
		if (++nBits_ == 8) {
			forceUpdate();
		}
	}

	void forceUpdate()
	{
		if (nBits_) {
			output_.write(reinterpret_cast<const char*>(&buf_), 1);
			buf_ = 0;
			nBits_ = 0;
		}
	}

private:
	std::ostream& output_;
	uint8_t buf_{ 0u };
	unsigned nBits_{ 0u };
};

//read bits
class IBitStream
{
public:
	IBitStream(std::istream& input) : input_(input) {}

	bool readBit(unsigned& bit)
	{
		if (nBits_ == 8) {
			nBits_ = 0;
			input_.read(reinterpret_cast<char*>(&buf_), 1);
			if (!input_) {
				return false;
			}
		}
		bit = (buf_ & (1 << nBits_)) >> nBits_;
		++nBits_;
		return true;
	}

private:
	std::istream & input_;
	uint8_t buf_{ 0u };
	unsigned nBits_{ 8u };
};


// the method to read the file and generate frequencies
bool readFile(string filename, map<char, int>& m)
{
	// open the file
	ifstream input(filename, ios::binary | ios::in);

	// return false if cannot open file
	if (!input)
		return false;

	// read all characters
	char c;
	while (input >> std::noskipws >> c)
	{
		// update their freuquency
		if (m.find(c) == m.end())
		{
			m[c] = 1;
		}
		else
		{
			m[c]++;
		}
	}

	// close the file
	input.close();

	// return true
	return true;
}

//function to compress the file
bool compressFile(string filename, HuffmanTree& tree)
{
	// open file to write
	ofstream output(filename.substr(0, filename.find('.')) + "_compress.txt");
	// open file to read
	ifstream input(filename, ios::binary | ios::in);
	// return false if cannot open file
	if (!input)
		return false;

	// return false if cannot open file
	if (!output)
		return false;

	OBitStream obs(output);
	// read all characters

	char c;
	while (input >> std::noskipws >> c)
	{
		unsigned b = (int)c - 48; // to get a 1 or 0
		obs.writeBit(b); // write bit to file

		// get code for this char
		string code = tree.getCode(c);
	}

	// close the files
	output.close();
	input.close();

	// return true
	return true;
}

// the method to encode file
bool encodeFile(string filename, HuffmanTree& tree)
{
	// open file to write
	ofstream output(filename.substr(0, filename.find('.')) + "_encoded.txt");
	// open file to read
	ifstream input(filename, ios::binary | ios::in);
	// return false if cannot open file
	if (!input)
		return false;

	// return false if cannot open file
	if (!output)
		return false;
	// read all characters

	char c;
	while (input >> std::noskipws >> c)
	{

		// get code for this char
		string code = tree.getCode(c);

		// add to the file
		output << code;
	}

	// close the files
	output.close();
	input.close();

	// return true
	return true;
}

// the method to decode file
bool decodeFile(string filename, HuffmanTree& tree, string& decodedText)
{
	// open file to read
	ifstream input(filename,ios::binary | ios::in);
	//IBitStream ibs(input);

	// return false if cannot open file
	if (!input)
		return false;

	// the string to decode
	string encodedText = "";

	// read all characters
	char c;
	while (input >> std::noskipws >> c)
	{

		// add to string
		encodedText.push_back(c);
	}

	// close the files
	input.close();

	// set the decoded text
	decodedText = tree.decode(encodedText);


	// return true
	return true;
}

int main()
{

	// ask for the file name to open
	cout << "Enter the filename to read : ";
	string filename;
	getline(cin, filename);

	// the map to store the frequencies
	map<char, int> m;

	// if cannot read file
	if (!readFile(filename, m))
	{
		// show error message
		cout << "Cannot open file " << filename << endl;
		return 1;
	}

	// create a tree
	HuffmanTree tree(m);
	// traverse tree
	tree.traverse();

	// compress the file
	if (compressFile(filename, tree))
	{
		// show message
		cout << "Compressed file " << filename << " into file " << (filename.substr(0, filename.find('.')) + "_compress.txt") << endl;
	}

	// change line
	cout << endl;

	// encode the file
	if (encodeFile(filename, tree))
	{
		// show message
		cout << "Encoded file " << filename << " into file " << (filename.substr(0, filename.find('.')) + "_encoded.txt") << endl;
	}

	// change line
	cout << endl;

	// decode the file
	string decodedText;
	if (decodeFile(filename.substr(0, filename.find('.')) + "_encoded.txt", tree, decodedText))
	{
		// show decoded text
		cout << "Decoded text : " << endl;
		cout << decodedText << endl;
	}

	return 0;
}






