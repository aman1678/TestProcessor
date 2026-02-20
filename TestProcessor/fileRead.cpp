#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>

class FileReader {
public:

    std::vector<std::string> words;

    void readFile(const std::string& fileName) {
        std::ifstream inputFile(fileName);

        std::string word;
        while (inputFile >> word) {
            word = processWord(word);
            words.push_back(word);
        }

        inputFile.close();
    }

private:
    std::string processWord(std::string& word) {
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        return word;
    }
};



