#include "textProcessor.hpp"
#include "fileRead.cpp"

void textProcessor::inputDictionary() {
    fstream dictFile("dictionary.txt",ios::in);
    string temp;

    while (!dictFile.eof()) {
        dictFile >> temp;
        dictionary.push_back(temp);
    }
}

textProcessor::textProcessor(string fileName) {
	//Reads file
	FileReader fileRead;
	fileRead.readFile(fileName);
	words = fileRead.words;

	//Clears blank words
	for (unsigned int i = 0; i < words.size(); i++) {
		if (words[i] == "") {
			words.erase(words.begin() + i);
		}
	}

	modified = words;

	//Stores dictionary
	inputDictionary();
}

set<string> textProcessor::findUnique() {
    set<string> result;

    for(unsigned int i = 0; i < words.size(); i++){
        result.insert(words[i]);
    }
    return result;
}

map<string,int> textProcessor::findOccurrance() {

  set<string> tempSet = findUnique();
  map<string, int> rMap; //Return map

  for(unsigned int i = 0; i < words.size(); i++) {

    //First we check if the word exists in the file
    if (tempSet.count(words[i])) {

      //If the word exists in the map, increment the value.
      //If not, insert it and initialize the value to 1.
      if (rMap.count(words[i])) {
        rMap[words[i]]++;
      }
      else {
        rMap.insert(pair<string,int>(words[i],1));
      }
    }
  }
  return rMap;
}


map<int, string> textProcessor::spellCheck() {
	map<int, string> mispelledWords;
	bool isMispelled;
	for (unsigned int i = 0; i < words.size(); i++) {
		isMispelled = true;
		for (unsigned int j = 0; j < dictionary.size(); j++) {
			if (words[i] == dictionary[j]) {
				isMispelled = false;
				break;
			}
		}

		if (isMispelled) {
			mispelledWords.insert({i, words[i]});
		}
	}

	return mispelledWords;
}

map<string, vector<int>> textProcessor::createIndexMap()
{
	map<string, vector<int>> indexMap;
	map<string, vector<int>>::iterator mapItr;
	for(unsigned int i = 0; i < words.size(); i++){	//make the indexMap from the words
		mapItr = indexMap.find(words[i]);
		if(mapItr != indexMap.end()){		// will == .end() if target wasn't found
			mapItr->second.push_back(i);
		}
		else{	//else key value hasn't been added yet, start a new map node
			int value = i;		//convert from unsigned int to int
			indexMap.insert(pair<string, vector<int>>(words[i], {value}));
		}
	}
	return indexMap;
}

void textProcessor::findAndReplace(string find, string replace, string fileName)
{
	map<string, vector<int>> indexMap = createIndexMap();
	map<string,vector<int>>::iterator mapItr;

	mapItr = indexMap.find(find);
	if(mapItr == indexMap.end()){
		cout << "The word you're looking to replace does not exist\n";
		return;
	}
	//else
	vector<int> allIndexes = mapItr->second;		//make a vector of all the indexes

	for(unsigned int i = 0; i < allIndexes.size(); i++){
			modified[allIndexes.at(i)] = replace; //replace at correct index
		}

	//We can write this in the main file
	fstream writeFile;
	writeFile.open(fileName, ios::out);

	//writeVector == wordVector AFTER the target strings have been replaced
	//to rewrite our file with replaced values, we write the entire writeVector out to file
	int length = 0;
	for(unsigned int i = 0; i < modified.size(); i++){
		writeFile << modified[i] << ' ';
		length++;
		if (length == 12) {
			writeFile << endl;
			length = 0;
		}
	}

	writeFile.close();
}





