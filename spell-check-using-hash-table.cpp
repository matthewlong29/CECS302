/*******************************************************************************
(5 points) Implement a spelling checker by using a hash table. Assume that the dictionary comes from two sources: an existing large dictionary and a second file containing a personal dictionary. Output all misspelled words and the line numbers on which they occur. Also, for each misspelled word, list any words in the dictionary that are obtainable by applying any of the following rules:

1. Add one character.
2. Remove one character.
3. Exchange adjacent characters

You can use words.txt from https://github.com/dwyl/english-words

(Problem 5.21 from the textbook.)
*******************************************************************************/

#include <fstream> // read contents from txt file
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm> // used to ensure words in dictionary are lowercase
                     // this is needed because very simple words such as apple are entered as Apple

using namespace std;

// #define debugReadDictionary
// #define debugGetWord
// #define debugDriver
// #define debugHash
// #define debugAddOneCharacter
// #define debugRemoveOneCharacter
// #define debugExchangeAdjacentCharacters
// #define debugCheckSpelling

/**
 * readDictionary reads the contents from files 
 * words-dictionary.txt from https://github.com/dwyl/english-words and words-personal.txt
 */
map<string, int> readDictionary()
{
  map<string, int> myMap;
  ifstream inFile;
  string url = "words-dictionary.txt";
  string word;
  inFile.open(url); // open the file stream

  if (!inFile) // check that file was opened
  {
    cout << "Unable to open file \"" << url << "\"." << endl;
    exit(1);
  }

  while (inFile >> word) // read from the stream, much like cin
  {
    transform(word.begin(), word.end(), word.begin(), ::tolower); // convert to lowercase
    hash<string> hasher;                                          // create unique hash key for each word in file
    size_t hash = hasher(word);
    myMap.insert(pair<string, int>(word, hash)); // insert word associated with hash key
  }
#ifdef debugReadDictionary // print word that was inserted and its key value
  map<string, int>::iterator itr;
  for (itr = myMap.begin(); itr != myMap.end(); itr++)
    cout << "\"" << itr->first << "\" inserted at hash key " << itr->second << ";\n";
  cout << endl;
#endif
  inFile.close(); // close the input stream

  return myMap;
} // end readDictionary

/**
 * getWord prompts user for a word
 * this word can be used to check spelling in place of other external list of words
 * i.e. this is for testing purposes 
 */
string getWord()
{
  string word;
  cout << "Enter word to check your spelling: ";
  cin >> word;

#ifdef debugGetWord // print the word being returned
  cout << "------------------------------------------------------------\n"
       << "You Entered;------------------------------------------------\n"
       << word << "\n------------------------------------------------------------" << endl;
#endif

  return word;
} // end getWord

/**
 * readPersonalDictionary
 */
vector<string> readPersonalDictionary()
{
  vector<string> words;
  ifstream inFile;
  string url = "words-personal.txt";
  string word;
  inFile.open(url); // open the file stream

  if (!inFile) // check that file was opened
  {
    cout << "Unable to open file \"" << url << "\"." << endl;
    exit(1);
  }

  while (inFile >> word) // read from the stream, much like cin
  {
    transform(word.begin(), word.end(), word.begin(), ::tolower); // convert to lowercase
    words.push_back(word);                                        // add word to vector of words
  }
  inFile.close(); // close the input stream

  return words;
} // end readPersonalDictionary

/**
 * addOneCharacter
 */
bool addOneCharacter(string words, string word)
{
  string alphabet = "abcdefghijklmnopqrstuvwxyz"; // used for adding one letter
  bool isPossibleSpellingFound;
#ifdef debugAddOneCharacter // print indicator that adding one character routine has begun
  cout << "when adding one character;----------------------------------" << endl;
#endif
  for (int i = 0; i <= word.size(); i++)
  {
    auto tempWord = word;
    for (char &a : alphabet)
    {
      tempWord.insert(i, 1, a); // insert character 'a'; at index position i; 1 time
#ifdef debugAddOneCharacter     // print check when removing one character at a time resulting in tempWord
      cout << "does " << tempWord << " == " << words << "; " << (words == tempWord ? "yes;" : "no;") << endl;
#endif
      if (words == tempWord) // if word contained in words it is spelled correctly
      {
        cout << "Did you mean to spell " << words << "?; Add " << a << " to " << word << ";" << endl;
        isPossibleSpellingFound = true;
      }
      tempWord.erase(i, 1); // erase 1 character at index position i because addition was wrong
    }
  }

  return (isPossibleSpellingFound ? true : false);
} // end addOneCharacter

/**
 * removeOneCharacter
 */
bool removeOneCharacter(string words, string word)
{
  bool isPossibleSpellingFound;
#ifdef debugRemoveOneCharacter // print indicator that removing one character routine has begun
  cout << "when removing one character;--------------------------------" << endl;
#endif
  for (int i = 0; i < word.size(); i++)
  {
    auto tempWord = word;
    tempWord.erase(i, 1);
#ifdef debugRemoveOneCharacter // print check when removing one character at a time resulting in tempWord
    cout << "does " << tempWord << " == " << words << "; " << (words == tempWord ? "yes;" : "no;") << endl;
#endif
    if (words == tempWord) // if word contained in words it is spelled correctly
    {
      cout << "Did you mean to spell " << words << "?; Remove " << word[i] << " from " << word
           << ";" << endl;
      isPossibleSpellingFound = true;
    }
  } // end remove one character

  return (isPossibleSpellingFound ? true : false);
} // end removeOneCharacter

/**
 * exchangeAdjacentCharacters
 */
bool exchangeAdjacentCharacters(string words, string word)
{
  bool isPossibleSpellingFound;
#ifdef debugExchangeAdjacentCharacters // print indicator that swapping adjacent characters routine has begun
  cout << "when swapping adjacent characters;--------------------------" << endl;
#endif
  for (int i = 0; i < word.size(); i++)
  {
    for (int j = 1; j < word.size(); j++)
    {
      auto tempWord = word;
      swap(tempWord[i], tempWord[j]);
#ifdef debugExchangeAdjacentCharacters // print check when swapping adjacent characters in word
      cout << "swapping " << tempWord[j] << " and " << tempWord[i] << ";\n"
           << "does " << tempWord << " == " << words << "; " << (words == tempWord ? "yes;" : "no;") << endl;
#endif
      if (tempWord == words)
      {
        cout << "Did you mean to spell " << words << "?; Swap characters " << tempWord[j] << " and "
             << tempWord[i] << " in " << word << ";" << endl;
        isPossibleSpellingFound = true;
      }
    }
  }

  return (isPossibleSpellingFound ? true : false);
} // end exchangeAdjacentCharacters

/**
 * checkSpelling returns true if it is found in the dictionary and false otherwise
 */
bool checkSpelling(map<string, int> myMap, string word)
{
  bool isPossibleSpellingFound; // used to indicate if a possible correct spelling is found
#ifdef debugCheckSpelling       // print size and indicator that checkSpelling routine has begun
  cout << "------------------------------------------------------------\n"
       << "checking for correct spelling;------------------------------" << endl;
#endif

  map<string, int>::iterator itrOne;
  for (itrOne = myMap.begin(); itrOne != myMap.end(); itrOne++) // check for correct spelling
    if (itrOne->first == word)                                  // if a correct spelling for the word is found
    {
      cout << "You spelled " << word << " correctly!" << endl;
      return true;
    }

  map<string, int>::iterator itrTwo;
  for (itrTwo = myMap.begin(); itrTwo != myMap.end(); itrTwo++) // check for possible spellings
  {
#ifdef debugCheckSpelling // check if word is spelled correctly
    cout << "does " << word << " == " << itrTwo->first << "; "
         << (itrTwo->first == word ? "yes;" : "no;") << endl;
#endif
    if (addOneCharacter(itrTwo->first, word))
      isPossibleSpellingFound = true;
    if (removeOneCharacter(itrTwo->first, word))
      isPossibleSpellingFound = true;
    if (exchangeAdjacentCharacters(itrTwo->first, word))
      isPossibleSpellingFound = true;
  }

  if (!isPossibleSpellingFound)
    cout << "Word not found, or spelling is very incorrect.." << endl;

  return false;
} // end checkSpelling

/**
 * driver function
 */
int main()
{
  vector<string> words;        // personal words
  map<string, int> dictionary; // container used to store key value pairs
  cout << "Spell checker using hash table;-----------------------------" << endl;
  dictionary = readDictionary();
  words = readPersonalDictionary();
#ifdef debugDriver // prompt user for word to be checked
  string testWord;
  while (1) // until control - c...
  {
    testWord = getWord();
    checkSpelling(dictionary, testWord);
  }
#endif
  for (int i = 0; i < words.size(); i++) // test each word in personal dictionary versus real dictionary
  {
    cout << "------------------------------------------------------------" << endl;
    cout << "Spell checking \"" << words[i] << "\" on line " << i + 1 << ";" << endl;
    checkSpelling(dictionary, words[i]);
  }
  return 0;
} // end main