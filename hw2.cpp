#include <iostream>
#include "AVLTree.h"
#include <string>
#include <vector>
#include "fstream"
#include "sstream"

using namespace std;

struct DocumentItem {
	string documentName;
	int count;
};

struct WordItem {
	string word;
	vector<DocumentItem> DocumentVector;
};

bool isnumber(string str) //checks if given string is a number
{
	for (int i = 0; i < str.length(); i++)
	{
		char ch = str.at(i);
		if(ch>= 48 && ch<=57)
			return true;
	}
	return false;
}

string upperCase(string & s) //uppercases all letters, since our program is case insensitive
{

	for (int i = 0; i < s.length(); i++) 
	{
		if (s[i] >= 65 && s[i] <= 90) //if lowecase
		{
			s[i]+= 32;  //make its uppercase version
		}
	}
	return s;
}

bool occurence (string & str,AvlTree<string, WordItem > myTree ) //checks if that node already exists
{
	if (myTree.find(str) == "")
		return false;
	else
		return true;
}

void PrintFinal(vector<WordItem*> print, vector<string> files)
{
	if(print.size() != 0)
	{
		for(int k=0 ; k<files.size(); k++)
		{
			cout <<"in Document " << files[k] << ", ";
			for (int i = 0; i < print.size(); i++)
			{
				for (int j = 0; j< print[i]->DocumentVector.size(); j++)
				{
					if(print[i]->DocumentVector[j].documentName == files[k])
					{
						cout << print[i]->word << " found ";
						cout << print[i]->DocumentVector[j].count << " times";
						if(i !=  print.size()-1)
							cout << ", ";
					}
				}
			}
			cout<< "." << endl;
		}
	}
}
int main()
{
	WordItem ITEM_NOT_FOUND;
	string THESTRING = "";

	AvlTree<string, WordItem > myTree(THESTRING, ITEM_NOT_FOUND);

	int fileNum;
	string FileName, line, word,wordlist, wrd;
	vector<string> files;
	vector<string> words;
	vector<WordItem*> print;
	ifstream file;

	cout<< "Enter the number of input files: ";
	cin >> fileNum;

	for (int i = 0; i < fileNum; i++)
	{
		cout << "Enter " << i+1 << ". file name:  ";
		cin >> FileName;
		files.push_back(FileName);
	}

	for (int i = 0; i<fileNum; i++)
	{
		string FileName = files[i];
		file.open(FileName.c_str()); //open file

		while (getline(file,line))
		{
			istringstream iss(line);
			while(iss>>word)
			{
				if(isnumber(word) == false)
				{
					word = upperCase(word);
					if (occurence(word, myTree)) // word already occures in tree
					{
						bool IsSameFile = false ;

						WordItem *nodey =  myTree.FindDet(word);
						for (int i = 0; i <nodey->DocumentVector.size() ; i++)
						{
							if (nodey->DocumentVector[i].documentName == FileName ) //check vector if has the same document name
							{
								IsSameFile = true; // means that this document has occured before , we just need to update the count
								nodey->DocumentVector[i].count++;
								break;
							}
						}

						if (IsSameFile == false) // means we are on a different document
						{
							DocumentItem Docum;
							Docum.count = 1;
							Docum.documentName = FileName;
							nodey->DocumentVector.push_back(Docum);
						}
					}
					//FindandInsert(myTree, word, FileName); //search and insert occurence

					else //word doesnt occur
					{
						WordItem addNode;
						addNode.word = upperCase(word);
						DocumentItem doc;
						doc.count = 1;
						doc.documentName = FileName;
						//vector<DocumentItem> VectorWords;
						addNode.DocumentVector.push_back(doc);
						//addNode.DocumentVector = VectorWords;
						myTree.insert(word,addNode);
					}
				}
				else
					;
			}
		}
		file.close();
	}

	cout << "Enter queried words in one line: ";
	cin.ignore();

	getline(cin,wordlist);
	istringstream boo(wordlist);
	while(boo >> wrd) // take words 
	{
		upperCase(wrd); 
		if (!occurence(wrd, myTree)) 
		{
			cout << "No document contains the given query" ;
			return 1;
		}

		else // exists, find node
		{
			WordItem *temp = myTree.FindDet(wrd); // found the word and return its details
			print.push_back(temp);
		}
	}

	PrintFinal(print, files);

	return 0;
}