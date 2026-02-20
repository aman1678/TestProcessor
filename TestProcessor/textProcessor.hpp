#ifndef TEXTPROCESSOR_HPP_
#define TEXTPROCESSOR_HPP_

#include <vector>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <list>

using namespace std;

class textProcessor {

private:

	vector<string> words;
	vector<string> dictionary;
	vector<string> modified;

	//Helper functions
	void inputDictionary();

	map<string,vector<int>> createIndexMap();

public:

	textProcessor(string fileName);

	set<string> findUnique();

	map<string, int> findOccurrance();

	map<int, string> spellCheck();

	void findAndReplace(string,string,string);
};



#endif /* TEXTPROCESSOR_HPP_ */
