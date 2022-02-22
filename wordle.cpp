// wordle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool correctFormat(string word) {

    if (word.size() != 5) {
        return false;
    }
    for (auto c : word) {
        if (!isalpha(c)) {
            return false;
        }
    }

    return true;

}

bool correctFormatResult(string word) {

    if (word.size() != 5) {
        return false;
    }
    for (char const& c : word) {
        if (!(c == 't' || c == 'w'  || c == 'g')) {
            return false;
        }
    }



    return true;

}

void filterList(vector<string>& words, string guess, string result) {

    vector<string> temp;
    vector<string> updatedList = words;
    vector<string>* pointerToList = &words;

    for (std::string::size_type i = 0; i < guess.size(); i++) {

        switch (result[i]) {
            // we need to remove every word that contains this letter
        case 'w':
            for (string word : updatedList) {
                if (word.find(guess[i]) == string::npos) { // not found
                    temp.push_back(word);
                }
            }

            updatedList = temp;
            temp.clear();

            break;

            // we need to remove every word that doesn't have this char at the specified position
        case 'g':

            for (string word : updatedList) {
                if (word[i] == guess[i]) { // word contains the right letter
                    temp.push_back(word);
                }
            }

            updatedList = temp;
            temp.clear();

            break;

            // we need to remove every word that contains the char at that position or that doesn't contain the char at all
        case 't':

            for (string word : updatedList) {
                if (word.find(guess[i]) != string::npos && word[i] != guess[i]) { // word contains the letter but at different place
                    temp.push_back(word);
                }
            }

            updatedList = temp;
            temp.clear();

            break;

        default:
            break;
        }



    }

    *pointerToList = updatedList;

}

int main()
{
    cout << "welcome" << endl << endl;
    cout << "you will need to enter the word first, then enter w (wrong), t (there) " << endl << "or c (correct) for each letter of that word" << endl;
    cout << "example:" << endl;
    cout << "range" << endl;
    cout << "wttcw" << endl << "meaning that \"r\" and \"e\" are not in the word, \"a\" and \"n\" are there " << endl << "but misplaced and \"g\" is in the correct position." << endl;

    string s(60, '-');
    cout << s << endl;
    int numberOfTries;


    string word;
    int wordsToShow = 10;
    int currentWordCount = 0;

    string currentGuess;
    string currentResult;

    vector<string> allWords;



    ifstream myfile("words.txt");
    if (myfile.is_open())
    {
        while (getline (myfile, word))
        {

            if (correctFormat(word)) {
                allWords.push_back(word);
            }


            currentWordCount++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";


    cout << "how many guesses do you have?" << endl;

    cin >> numberOfTries;

    bool gaveup = false;

    for (int i = 0; i < numberOfTries; i++) {

        do {
            
            cout << "\nenter your guess (or /exit to give up):" << endl;
            cin >> currentGuess;

            if (currentGuess._Equal("/exit")) {
                gaveup = true;
                break;
            }

        
        } while (!( correctFormat(currentGuess)));
        
        if (gaveup) {
            break;
        }
      
        do {
            cout << "enter the result:" << endl;
            cin >> currentResult;

            if (currentResult._Equal("/exit")) {
                gaveup = true;
                break;
            }
        } 
        while (!(correctFormatResult(currentResult)));

        if (gaveup) {
            break;
        }


        filterList(allWords, currentGuess, currentResult);

        cout << "there are "<< allWords.size() << " possible words..." << "\n" << endl;

        if (sizeof(allWords) < 2) {
            break;
        }


    }

    cout << "\nhere are the possible " << allWords.size() << " words:" << endl;

    for (int i = 0; i < static_cast<int>(allWords.size()) - 1; i++) {

        cout << i + 1 << ": " << allWords[i] << endl;

    }


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
