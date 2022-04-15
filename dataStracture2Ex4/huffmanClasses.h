//Erez Polak 322768995
//Mordechay cohen 206958035
//lecturer: David Kidron.
//Data structurs: Running Exercise 4.


//ducomantatiom in the cpp file.

#pragma once
#include <iostream>
#include <queue>
#include <list>
#include <string>

using namespace std;

class CompareNode;
class HuffmanNode;

class HuffmanTree
{
public:
	
	HuffmanTree(string decodedText)
	{
		this->word = decodedText;
		this->numberOfLeafs = 0;
		this->lettersByOrder = "";
		this->treeStracture = "";

		this->encode();
	}

	HuffmanTree(int n , string letters , string stracture , string encodedText)
	{
		this->numberOfLeafs = n;
		this->lettersByOrder = letters;
		this->treeStracture = stracture;
		this->word = encodedText;

		//this->buildDecodingTree();
	}
	
	//dtor that will release all the dynamic memmory alocations.
	~HuffmanTree(){
	    deleteTree(this->root);
	}

	void encodedString();

private:

	int numberOfLeafs;
	string lettersByOrder;
	string treeStracture;
	string word;

	HuffmanNode* root;

	void deleteTree(HuffmanNode* node);

#pragma region Encoding

public:


	bool buildDecodingTree();

	void setCodeForEveryLetter() {
		printsTheCodeForEveryLetter(root , "");
	}

private:

	vector<HuffmanNode*> letterNodes;

	void encode();

	string findTreeShape(HuffmanNode* node);

	void printsTheCodeForEveryLetter(HuffmanNode* node, string code);

	int find(const string str);
	
	string encodeWord();

	

#pragma endregion

#pragma region Decodeing
public:

	string decodeWord() {
		return decodeWord(root, this->word, 0);
	}

private:

	//void buildDecodingTree();

	void buildTreeFromDtructureText(HuffmanNode* current, string stracture , int& index);
		
	void insertCodesToLetters(HuffmanNode* node , string letters , int& index);

	string decodeWord(HuffmanNode* node, string str, int index);

	int coutZiros(const string str);

#pragma endregion

};


class HuffmanNode 
{
public:
	string key;
	int frequency;
	HuffmanNode* left;
	HuffmanNode* right;
	string code;

	friend class CompareNode;

	HuffmanNode(string str , int fr , HuffmanNode* left , HuffmanNode* right)
	{
		this->key = str;
		this->frequency = fr;
		this->left = left;
		this->right = right;
	}

};


class CompareNode
{
public:
	bool operator()(HuffmanNode* const& n1, HuffmanNode* const& n2)
	{
		return n1->frequency > n2->frequency;
	}

};

