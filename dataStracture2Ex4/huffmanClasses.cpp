//Erez Polak 322768995
//Mordechay cohen 206958035
//lecturer: David Kidron.
//Data structurs: Running Exercise 4.




#include "huffmanClasses.h"



void HuffmanTree::deleteTree(HuffmanNode* node)
{
	if (node->left == NULL || node->right == NULL) { // meaning that this is a leaf if the tree
		delete node;
	}
	else {
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}

}



#pragma region Encoding

//prints every thing needed for the tree, the number of leafs the letters by order and the encoded text itself.
void HuffmanTree::encodedString()
{
	cout << this->numberOfLeafs << endl;
	cout << this->lettersByOrder << endl;
	cout << this->treeStracture << endl;
	cout << encodeWord() << endl;
}

//the function encode the text, and initilze the values in the intended proprties.
void HuffmanTree::encode()
{
	//build the array of the letters.
	for (int i = 0; i < this->word.size(); i++) {

		int index = find(string(1, this->word.at(i)));

		if (index != -1) {
			letterNodes[index]->frequency++;
		}
		else {
			letterNodes.push_back(new HuffmanNode(string(1, this->word.at(i)) + "", 1, NULL, NULL));
		}
	}

    //initilze the number of leafs.
	this->numberOfLeafs = letterNodes.size();

	//defining the priority queue.
	priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNode> pQueue;

    //inserting all the letters to the queue.
	for (int i = 0; i < letterNodes.size(); i++) {
		pQueue.push(letterNodes[i]);
	}

    //sets the right sons in the tree.
	while (pQueue.size() > 1) {
		HuffmanNode* lowest = pQueue.top();
		pQueue.pop();
		HuffmanNode* secondLowest = pQueue.top();
		pQueue.pop();
		pQueue.push(new HuffmanNode(lowest->key + secondLowest->key, lowest->frequency + secondLowest->frequency, lowest, secondLowest));
	}

	//update the root if the tree to be the last element that remian in the tree.
	this->root = pQueue.top();

    //building the structur of the tree.
	this->treeStracture = findTreeShape(root);

}

//sets the code in every leaf of the tree according to the given order.
void HuffmanTree::printsTheCodeForEveryLetter(HuffmanNode* node, string code)
{
	if (node->left == NULL || node->right == NULL) { // meaning that this is a leaf if the tree
		//Writing the code of that leaf.
		node->code = code;
		lettersByOrder += node->key;
	}
	else {
		printsTheCodeForEveryLetter(node->left, code + "0");
		printsTheCodeForEveryLetter(node->right, code + "1");
	}
}


// create the complete eord encosded.
string HuffmanTree::encodeWord()
{
	string encodedWord;

	//for (char ch : this->word) {
	for (int i = 0; i < this->word.size(); i++)
	{
		encodedWord += this->letterNodes[find(string(1, this->word[i]))]->code + "";
	}

	return encodedWord;
}

//encodes the shape of the tree.
string HuffmanTree::findTreeShape(HuffmanNode* node)
{
	if (node->left == NULL || node->right == NULL) {
		return "1";
	}
	else {
		return "0" + findTreeShape(node->left) + findTreeShape(node->right);
	}
}


// returns the index of the 
int HuffmanTree::find(const string str)
{
	int index = 0;

	for (int i = 0; i < this->letterNodes.size(); i++)
	{
		if (this->letterNodes[i]->key == str)
		{
			return index;
		}
		index++;
	}
	return -1;
}


#pragma endregion

#pragma region Decoding


// calling the functions that building the tree.
bool HuffmanTree::buildDecodingTree() {
	
	if (this->lettersByOrder.size() != coutZiros(this->treeStracture) + 1) {
		cout << "ERROR" << endl;
		return false;
	}

	this->root = new HuffmanNode("" , 0 , NULL , NULL);
	
	int index = 0;
	buildTreeFromDtructureText(root, this->treeStracture, index);

	index = 0;
	insertCodesToLetters(root, this->lettersByOrder, index);

	return true;
}

//building the tree frm the given encoded tree structure.
void HuffmanTree::buildTreeFromDtructureText(HuffmanNode* current, string stracture, int& index)
{
	if (stracture[index] == '1') {

		index++;

		return;
	}
	else {

		index++;

		current->left = new HuffmanNode("", 0, NULL, NULL);
		current->right = new HuffmanNode("", 0, NULL, NULL);
		buildTreeFromDtructureText(current->left, stracture, index);
		buildTreeFromDtructureText(current->right, stracture, index);
	}
}

//inserting the letters in the right places of the tree.
void HuffmanTree::insertCodesToLetters(HuffmanNode* current , string letters, int& index)
{
	if (current->left == NULL || current->right == NULL) {
		current->code = letters[index];
		index++;
	}
	else {
		insertCodesToLetters(current->left, letters, index);
		insertCodesToLetters(current->right, letters, index);
	}
}

//after the tree was formed and inisilized the function goes through all the letters in the encoded text and decoding it.
string HuffmanTree::decodeWord(HuffmanNode* node , string str , int index)
{
	if (node->left == NULL || node->right == NULL) {
		if (index < str.size())
			return node->code + decodeWord(root, str, index);
		else
			return node->code;
	}
	else {
		if (str[index] == '0'){
			return decodeWord(node->left, str, index + 1);
		}
		else {
			return decodeWord(node->right, str, index + 1);
		}
	}
}

//counting the number of zeros in the string
int HuffmanTree::coutZiros(const string str)
{
	int counter = 0;
	for (int i = 0 ; i < str.size() ; i++) {
		if (str[i] == '0') counter++;
	}
	return counter;
}



#pragma endregion
