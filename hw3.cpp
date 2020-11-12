#include <iostream>

#include "BST.h"
#include "HashTable.h"

#include <string>
#include "fstream"
#include "sstream"
#include "chrono"

using namespace std;

struct DocumentItem {
	string documentName;
	int count;
};

struct WordItem {
	string word;
	vector<DocumentItem> DocumentVector;
};

bool isPrime( int n )
{

	if ( n == 2 || n == 3 )
		return true;

	if ( n == 1 || n % 2 == 0 )
		return false;

	for ( int i = 3; i * i <= n; i += 2 )
		if ( n % i == 0 )
			return false;

	return true;

}

int nextPrime( int n )
{
	if ( n % 2 == 0 )
		n++;

	for ( ; ! isPrime( n ); n += 2 )
		;

	return n;

}

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
			s[i]+= 32;  //make its uppercase version
	}
	return s;
}

bool occurence (string & str,BinarySearchTree<string, WordItem > myTree ) //checks if that node already exists
{
	if (myTree.find(str) == "")
		return false;
	else
		return true;
}

bool occurenceTable (string & str,HashTable<string, WordItem > &myTable ) //checks if that node already exists
{
	if (myTable.find(str).word == "")
		return false;
	else
		return true;
}

string alph(string & word)
{

	for (int i = 0; i < word.length(); i++)
	{
		if (word.at(i) < 97 || word.at(i) > 122) // means its not a letter
			word.at(i) =  ' ';


	}
	return word;
}

void PrintFinal(vector<WordItem*> print, vector<string> files)
{
	
	for(int yeter = 0 ; yeter<2 ; yeter++)
	{
		if(print.size() != 0)
		{
			for(int k=0 ; k<files.size(); k++)
			{

				//if((print[i]->DocumentVector[j].documentName == files[k])
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
}


void FormHashTable(const string & filename, HashTable<string, WordItem > &myTable)
{
	ifstream file;
	file.open(filename.c_str()); // File is opened


	string line;
	while(getline(file, line)) // read each line , then process it
	{
		istringstream iss(line);
		string word;


		while (iss>>word)
		{
			upperCase(word);
			// seperator
			string templine = alph(word);

			istringstream iss2(templine);
			string tempword;
			while(iss2 >> tempword)
			{
				// if the word exists , update the corresponding hashnode
				//else , insert it to the hashtable
				bool exist = occurenceTable(tempword, myTable);
				if (exist == true) // means the word exists
				{
					bool flag =false;
					WordItem * mynode = myTable.FindDetTable(tempword);
					for (int i = 0; i < mynode->DocumentVector.size(); i++)
					{
						// check whether file exists
						if ( mynode->DocumentVector[i].documentName == filename) {
							mynode->DocumentVector[i].count++;
							flag =true;
						}
					}

					if(flag==false)
					{
						DocumentItem temp;
						temp.documentName = filename;
						temp.count = 1;
						mynode->DocumentVector.push_back(temp);
					}
				}
				else // means the word does not exist
				{
					WordItem tempitem;
					tempitem.word = tempword;
					DocumentItem docitem;
					docitem.count = 1;
					docitem.documentName = filename;
					tempitem.DocumentVector.push_back(docitem);
					myTable.insert(tempword, tempitem);
				}

			}
		}

	}
	file.close();
}


void  TreeF(vector<WordItem*> &queries,BinarySearchTree<string, WordItem > &myTree )
{
	int count = 0;
	for (int i = 0; i<queries.size(); i++)
	{
		if(occurence(queries[i]->word, myTree)==false)
		{
			; // do nothing
		}
		else
			count++;
	}
}


int main()
{
	WordItem ITEM_NOT_FOUND;
	string THESTRING = "";

	BinarySearchTree<string, WordItem > myTree(THESTRING, ITEM_NOT_FOUND);
	HashTable<string, WordItem> mytable(THESTRING, ITEM_NOT_FOUND, 101);

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
					word = alph(word);
					istringstream iss3(word);
					while(iss3>>word)
					{
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
				}
				else
					;
			}
		}
		file.close();
	}

	for (int i = 0; i < files.size() ; i++)
	{
		FormHashTable(files[i], mytable);
	}

	mytable.AfterPreporcessing();

	cout << "Enter queried words in one line: ";
	cin.ignore();

	getline(cin,wordlist);
	wrd = alph(wordlist);
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

	int k = 100000;
	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < k; i++)
	{
		//TreeF(print, myTree);
		for (int j = 0; j < print.size(); j++)
		{
			myTree.find(print[j]->word);
		}
	}
	auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds> 
		(std::chrono::high_resolution_clock::now() - start);
	cout << "\nTime: " << BSTTime.count() / k << "\n";
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
	{
		//TableF(print, mytable);
		/*for (int j = 0; j < print.size(); j++)
		{
		TableF(print[j]->word, mytable);
		}*/
		int count = 0;
		for (int i = 0; i<print.size(); i++)
		{
			if(mytable.find(print[i]->word).word == "")
			{
				; // do nothing
			}
			else
				count++;
		}
	}
	auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds> 
		(std::chrono::high_resolution_clock::now() - start);
	cout << "\nTime: " << HTTime.count() / k << "\n";

	double TableTime = HTTime.count();
	double kk = k+0.0;
	cout << "\nSpeed Up: " << (BSTTime.count() / k) / (TableTime / kk) << "\n";

	return 0;
}