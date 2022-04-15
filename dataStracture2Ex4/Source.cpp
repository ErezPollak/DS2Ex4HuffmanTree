//Erez Polak 322768995
//Mordechay cohen 206958035
//lecturer: David Kidron.
//Data structurs: Running Exercise 4.


#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <cmath>
#include "huffmanClasses.h"

using namespace std;


int main()
{
	char choice;
	string word;

	HuffmanTree* t;
	cout << "enter E to encode a text\n";
	cout << "enter D to decode a text\n";
	cout << "enter X to exit\n";

	do
	{
		cin >> choice;
		switch (choice)
		{
		case 'E':

			cout << "enter the original text" << endl;
			cin >> word;

			
			//Build Huffman tree given the data inside "word".
		    t = new HuffmanTree(word);
			//Then find the code of each letter.
			t->setCodeForEveryLetter();
			//Then print the output - number of leaves, order of letters, tree structure and the encoded text - according to the explanation in the exercise.
			cout << "The encoded string is\n";
			t->encodedString();

			break;
		case 'D': 
			
			//input the number of leaves, the  order of letters, tree structure and the encoded text.
			cout << "enter n" << endl;
			int n;
			cin >> n;
			cout << "enter the letters" << endl;
			string letters;
			cin >> letters;
			cout << "enter the encoded structure" << endl;
			string encodedStrscture;
			cin >> encodedStrscture;
			cout << "enter the encoded text" << endl;
			string encodedText;
			cin >> encodedText;

			
			//build the Huffman Tree according to the tree strcture. put the letters in the leaves according to the given order. 
			t = new HuffmanTree(n, letters, encodedStrscture, encodedText);

			bool b = t->buildDecodingTree();

            //only if there was no problem with building the tree. 
			if (b) {
				//Given the Huffman Tree and the encoded text, find the original text, and print it. 
				cout << "The decoded string is" << endl;
				cout << t->decodeWord() << endl;
			}
			break;
		}

	} while (choice != 'X');
	
	cout << "bye";

	return 0;
}