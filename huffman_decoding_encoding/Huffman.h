#pragma once

#ifndef Huffman_hpp
#define Huffman_hpp

#include <map>
#include <string>
#include <unordered_map>
using std::unordered_map;
using std::map;
using std::string;

// the class to store a huffman node
class HuffmanNode
{
	// the public data members of the class
public:

	// the data at this node
	char c;
	int frequency;

	// the left and the right subtree
	HuffmanNode* left;
	HuffmanNode* right;

	// the constructor
	HuffmanNode(char c, int frequency);
};


// to compare two nodes
struct LessThanByFrequency
{
	bool operator()(const HuffmanNode* lhs, const HuffmanNode* rhs) const
	{
		// compare the frequencies
		return lhs->frequency > rhs->frequency;
	}
};



// the Huffman Tree class
class HuffmanTree
{
	// the private data members of the class
private:

	// the map for the frequncies of characters
	map<char, int> frequncies;

	// the codes
	map<char, string> codes;

	// the root node of the huffman tree
	HuffmanNode* root;

	// the method to construct tree
	void constructTree();

	// the method to generate codes
	void generateCodes();

	// the helper to generate codes
	void generateCodes(HuffmanNode* node, string code);

	// the public data members of the class
public:
	// the constructor
	HuffmanTree(map<char, int> frequncies);

	// the method to get the code for this
	string getCode(char c);

	// the method to traverse
	void traverse();

	// the method to decode
	string decode(string encodedText);
};
#endif 
