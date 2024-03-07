#include <iostream>
#include <map>
#include <fstream>
#include <regex>
#include <string>
#include <set>

using namespace std;

string clean(const string&);
void convert_lower(string&);

class MisspelledWords
{
private:
	map<string, int>misspelled;
public:
	void add(string key){
		misspelled[key]++; //increments 1 for each key's value
	}
	void print() const
	{
		cout << "Misspelled words: (" << misspelled.size() << ")" << endl;
		for (auto pos = misspelled.begin(); pos != misspelled.end(); pos++){
			cout << (*pos).first << " - " << (*pos).second << endl;
		}
	}
};

int main()
{
	MisspelledWords Misspelled;
	set<string> dictionary;
	string word;
	//regex reg("(^[a-z]+)+(\'?[a-z]+|(-?[a-z]+)*)"); //"can't, ex-x, not cant' can't-- etc
	regex reg("(^[a-z]+)+(\'?[a-z]*)*((-*[a-z]+)*)"); //only one (') and infinite (-)

	//load dictionary
	ifstream dictFile("american-english");
	while (getline(dictFile,word)) {
		convert_lower(word);
		dictionary.insert(word);
	}
	word = "";
	//load book
	ifstream bookFile("flatland.txt");
	while (bookFile >> word) {
		word = clean(word);
		//check valid word
		if (regex_match(word, reg)) {
			//if word not in dictionary
			if (dictionary.count(word) == 0) 
				Misspelled.add(word);
		}
	}
	//output
	Misspelled.print();

	return 0;
}
void convert_lower(string& str)
{
	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
	}
}
string clean(const string& s)
{
	//ignores punctuation and capitalization, keeps apostrophe and hyphens 
	string r = "";
	for (int i = 0; i < s.length(); i++) {
		char c = s[i];
		if ('a' <= c && c <= 'z') // Append lowercase letters
			r = r + c;
		else if ('A' <= c && c <= 'Z') { //make lowercase
			c = c - 'A' + 'a';
			r = r + c;
		}
		else if (c == '\'') //add apostrophe
			r = r + c;
		else if (c == '-') //add hyphen 
			r = r + c;
	}
	return r;
}






