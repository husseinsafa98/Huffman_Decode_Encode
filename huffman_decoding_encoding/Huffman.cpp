#include "Huffman.h"
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

// the constructor
HuffmanNode::HuffmanNode(char c, int frequency)
{
    // set the character and the frequency
    this->c = c;
    this->frequency = frequency;
    
    // set the left and the right to null
    left = nullptr;
    right = nullptr;
}

// the method to construct tree
void HuffmanTree::constructTree()
{
    // set priority queue of all the nodes
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, LessThanByFrequency> pq;
    
    // add nodes to the priority queue
    for( map<char, int>::iterator it = frequncies.begin(); it!=frequncies.end(); it++ )
        pq.push(new HuffmanNode(it->first, it->second));
    
    // as long as the pq size is greater than 1
    while( pq.size() > 1 )
    {
        // get the left
        HuffmanNode * left = pq.top();
        pq.pop();
        
        // get the right
        HuffmanNode * right = pq.top();
        pq.pop();
        
        // create new node
        HuffmanNode * newNode = new HuffmanNode(0, left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }
    
    // set the root
    root = pq.top();
    pq.pop();
}

// the method to generate codes
void HuffmanTree::generateCodes()
{
    // use the helper
    generateCodes(root, "");
}

// the helper to generate codes
void HuffmanTree::generateCodes(HuffmanNode * node, string code)
{
    // if there is a left subtree
    if( node->left )
    {
        // recur left
        generateCodes(node->left, code + "0");
    }
    
    // if there is a right
    if( node->right )
    {
        // recur right
        generateCodes(node->right, code + "1");
    }
    
    // add code if this is a leaf
    if( node->left == nullptr && node->right == nullptr )
        codes[node->c] = code;
}

// the constructor
HuffmanTree::HuffmanTree(map<char, int> frequncies)
{
    // add all the values from the map
    for( map<char, int>::iterator it = frequncies.begin(); it!=frequncies.end(); it++ )
    {
        this->frequncies[it->first] = it->second;
    }
    
    // costruct tree and generate codes
    constructTree();
    generateCodes();
}

// the method to get the code for this
string HuffmanTree::getCode(char c)
{
    // return blank if this character is not encoded
    if( frequncies.find(c) == frequncies.end() )
        return "";
        
    // else return the code for this
    return codes[c];
}

// the method to traverse
void HuffmanTree::traverse()
{
    // print the header
    std::cout << std::setw(11) << std::left << "character" << std::setw(11) << std::left << "frequncy" << "code" << "\n";
    
    // for each of the character in the tree
    for( map<char, int>::iterator it = frequncies.begin(); it!=frequncies.end(); it++ )
    {
        // print the
        std::cout << std::setw(11) << std::left << it->first << std::setw(11) << std::left << it->second << getCode(it->first) << "\n";
    }
    std::cout << std::endl;
}

// the method to decode
string HuffmanTree::decode(string encodedText)
{
    // the string to return
    string decodedText = "";
    
    // the reference to the root node
    HuffmanNode * curr = root;
    
    // for each of the character in the encoded text
    for( size_t i=0; i<encodedText.size(); i++ )
    {
        // get this char
        char c = encodedText[i];
        
        // if this is 0
        if( c=='0' )
        {
            // move left
            curr = curr->left;
        }
        // else
        else
        {
            // move right
            curr = curr->right;
        }
        
        // if this is a leaf node
        if( curr->left == nullptr && curr->right == nullptr )
        {
            // add this char to decoded text
            decodedText.push_back(curr->c);
            curr = root;
        }
    }
    
    // return the decoded text
    return decodedText;
}

