#include <iostream>
#include <iomanip>
#include <set>
#include <map>
#include "textProcessor.hpp"
using namespace std;

//Helper functions
void display(set<string> argSet) {
    int maxNum = 40;
    int currentNum = 0;
    int startIndex = 0;
    int stopIndex = 0;

    string setString;
    vector<string> myVec;

    set<string>::iterator setItr;
    for(set<string>::iterator setItr = argSet.begin();
            setItr != argSet.end(); setItr++)
    {
        myVec.push_back(*setItr);
    }

    for(unsigned int i = 0; i < myVec.size(); i++)
    {
        setString = myVec[i];
        currentNum += setString.size() + 1;        //add 1 for the ',' char

        if(currentNum == maxNum)
        {
            stopIndex = i + 1;
            for(int j = startIndex; j < stopIndex; j++){
                cout << myVec[j] << ',';
            }
            cout << endl;                    //then write to the next line
            startIndex = stopIndex;            //start by displaying on the index you stopped before
            currentNum = 0;                    //restart counter
        }
        else if(currentNum > maxNum)
        {
            stopIndex = i;
            for(int w = startIndex; w < stopIndex; w++){
                cout << myVec[w] << ',';
            }
            cout << endl;                    //then write to the next line
            startIndex = stopIndex;
            currentNum = 0;
        }
        // else continue to read until we've found enough strings for a full line
    }    //outer vector for loop
}

void display(map<string, int> argMap) {
    map<string,int>::iterator mapItr;        //create an iterator for the map
    cout << setw(15) << "Word" << setw(15) << "Occurrences" << endl;
    for(mapItr = argMap.begin(); mapItr != argMap.end(); mapItr++)
    {
        cout << setw(25) << mapItr->first << setw(25) << mapItr->second << '\n';
    }
}

void display(map<int, string> argMap) {
    map<int, string>::iterator mapItr;        //create an iterator for the map
    cout << setw(15) << "Word" << setw(15) << "Position" << endl;
    for(mapItr = argMap.begin(); mapItr != argMap.end(); mapItr++)
    {
        cout << setw(25) << mapItr->first << setw(25) << mapItr->second << '\n';
    }
}

void clearScreen(){
    for(int i =0; i < 100; i++){
        cout << '\n';
    }
}

void pause() {
	int junk;
	cout << "Press any key and ENTER to continue... ";
	cin >> junk;
	cin.clear();
	cin.ignore(1000000, '\n' );
}

int main() {

	//Input loop that checks if a given file exists, if the user enters BS it loops back
	string fileName;
	while (true) {
		cout << "Please enter a file name: ";
		cin >> fileName;
		ifstream in(fileName);
		if (!in.good()) {
			cout << endl << "Invalid file" << endl << endl;
		} else {
			break;
		}
	}

	//Creates file processor
	textProcessor text(fileName);
	cout << endl;

	//Presents a menu with options
	int selection;
	bool end = true;
	while (end) {
		cout << "(1) Display every unique word" << endl;
		cout << "(2) Display how many times each word appears in the file" << endl;
		cout << "(3) Spell check every word in the text file" << endl;
		cout << "(4) Find and replace" << endl;
		cout << "(5) to exit" << endl;
		cout << "Please select an option:" << endl;

		if (cin >> selection) {
			switch (selection) {
				case 1:
				{
					cout << endl;
					set<string> uniques = text.findUnique();
					display(uniques);

					//Holds before moving on
					cout << endl;
					pause();
					clearScreen();
					break;
				}
				case 2:
				{
					cout << endl;
					map<string, int> occurances = text.findOccurrance();
					display(occurances);

					//Holds before moving on
					cout << endl;
					pause();
					clearScreen();
					break;
				}
				case 3:
				{
					cout << endl;
					map<int, string> misspelled = text.spellCheck();
					if (misspelled.empty()) {
						cout << "No misspelled words" << endl;
					} else {
						display(misspelled);
					}

					//Holds before moving on
					cout << endl;
					pause();
					clearScreen();
					break;
				}
				case 4:
				{
					cout << endl;

					string input1;
					cout << "Please enter the word you want to replace: ";
					cin >> input1;

					string input2;
					cout << "Please enter the word you want to replace it with: ";
					cin >> input2;

					text.findAndReplace(input1, input2, "output.txt");

					cout << endl;
					break;
				}
				case 5:
				{
					end = false;
					break;
				}
			}
		} else {
			clearScreen();
			cout << "Invalid selection, please try again" << endl << endl << endl;
			cin.clear();
			cin.ignore(100000, '\n');
		}
	}

	cout << "Program ending";
	return 0;
}
