//***********************************************************************************************
//4COM1037 – Anagram Solver Challenge
//Student ID: 17065628
//This program including all the code is my own work and has been tested fully before submission
// **********************************************************************************************

#include <iostream> //declares the standard devices cin, cout, clog, cerr; http://www.cplusplus.com/reference/iostream/

#include <string> //declares string types and conventions including begin & end iterator; http://www.cplusplus.com/reference/string/

#include <algorithm> //declares a collection of ranged functions; http://www.cplusplus.com/reference/algorithm/

#include <random> //declares random number generation facilities; http://www.cplusplus.com/reference/random/

#include <fstream> //declares a set of standard file stream devices that can be used to to create, read and use files; http://www.cplusplus.com/reference/fstream/

#include <ctime> //declares a set of functions, macros and types to work with date and time information, e.g. the time() function is used to get the current time; http://www.cplusplus.com/reference/ctime/

#include<iomanip> //declares header providing parametric manipulators; http://www.cplusplus.com/reference/iomanip/

#include<cstdio> //declare this library to perform Input/Output operations; http://www.cplusplus.com/reference/cstdio/

#include<vector> //vectors are sequence containers representing arrays that can change in size; http://www.cplusplus.com/reference/vector/vector/

#include<cstdlib> //declares this library to perform pseudo-random sequence generation and macro constants; http://www.cplusplus.com/reference/cstdlib/


//create a fixed identifier (a bit like an unchangeable global variable) with a string value; the compiler will automatically use the string for each instance of the identifier
//#define cDATAFILE "Words_100_Testing.csv"
//#define cDATAFILE "Words_1K_Testing.csv"
#
define cDATAFILE "Words_75K_PreSubmissionTesting.csv"

using namespace std; //tell the compiler that by default to use the “std” – this means that we don’t need to keep saying “std::cout” we can just use: “cout”

//this block of code contains the variables for the Timer
int startTicks, stopTicks, totalTicks; //declare variables to hold the values for the Timer; startTicks - hold the start value for the clock; stopTicks - hold the stop value for the clock; totalTicks - hold the value of the subtraction between stopTicks and startTicks
float timeSeconds; //declare and initialise the variable to hold the current value for the 'Timer'

//this block of code contains a function that starts a clock
void StartTimer() { //this function starts the clock time
  startTicks = clock(); //get the number of clock ticks consumed by the processor since the program started
}

//this block of code contains a function to stop the clock and calculate the time consumed and return the value
float StopTimer() { //this function stop the clock time and returns the value
  stopTicks = clock(); //get the number of clock ticks consumed by the processor since the program started; more times will have happened since we last took the time
  totalTicks = stopTicks - startTicks; //work out the difference in ticks
  timeSeconds = totalTicks / double(CLOCKS_PER_SEC) * 1000; //convert the ticks into seconds
  return timeSeconds; //return the value contained in the timeSeconds global variable
}

//this block of code contains a function that allows the user to exit the program
void QuitNow(void) { //this function allow the user to exit the program
  string quitOption; //declare and initialise the variable to hold the current word ready to be manipulated
  cout << endl << "Are you sure (Y/N)? "; //ask the user for confirmation about quit the program
  cin >> quitOption; //store the choice made by the user in the variable "quitOption"

  if (quitOption == "Y" || quitOption == "y" || quitOption == "yes" || quitOption == "YES" || quitOption == "Yes") { //if statement to compare the value of the variable "quitOption" - if its true execute the command below, if its false it keep the user in the "Menu" function
    cout << "\033c"; //this instruction clear the screen
    cout << endl << endl << "Thank you for using C++ Anagram Solver Challenge - please come back soon" << endl; //display the requires message to the user
    exit(EXIT_SUCCESS); //execute the c++ exit function and pass it c++ contant value called EXIT_SUCCESS; EXIT_SUCCESS is actually 0 - for more info see: http://www.cplusplus.com/reference/cstdlib/exit/
  }

}

//this block of code contains a function must change the original string to all lowercase characters
string ToLower(string originalString) { //this function is designed to expect one argument (called originalString) and returns a string, the function has been declared as a type 'string'
  string localString = originalString; //declate a local variable called localString and load into it the content of the variable "originalString"

  for (int i = 0; i < originalString.length(); i++) { //loop 'for' with the length of 'originalString'
    localString[i] = tolower(localString[i]); //convert uppercase letter to lowercase
  }

  return localString; //return the value contained in the localstring local variable
}

//this block of code contains a function to reorder all the characters in the "originalString"
string OrderWord(string originalString) { //this function is designed to expect one argument (called originalString) and returns a string, the function has been declared as a type 'string'
  string localString = originalString; //declate a local variable called localString and load into it the content of the variable "originalString"
  sort(localString.begin(), localString.end()); //Sorts the elements in the range [first,last) into ascending order
  return localString; //return the value contained in the localstring local variable
}

//this block of code contains a function allows the user to enter a new word to be manipulated
string GetWord(void) { //this function should allow the user to enter a new word that can then be later manipulated, the function has been declared as a type 'string'
  string localString; //declare and initialise a local string, used to store the new string
  cout << "\nPlease enter a new word or phrase: "; //by not including an end of line the input will be on the same line as the output message
  getline(cin >> ws, localString); //get the input value from the user and store it in the local variable 'localstring'
  return localString; //pass the value stored in 'localstring' back to the calling instruction
}

//this block of code constains a function to scan all available words and identify and display each word that is an anagram
void FindAnagrams(string originalString) { //this function is designed to expect one argument (called originalString)
  string localString = originalString; //declare and initialise a local string, used to store the new string
  string currentWord; //declare a variable of type string that can be used to hold each line as the file is read
  string anagramList; //declare and initialise a local string to store all values for anagrams found
  int anagramCounter = 0; //declare and initialise a local integer to store the number of anagrams found
  ifstream dbFile; //create a special variable (actually a class (e.g. object with its own functions) that is defined in the <fstream> header that can be used to "stream" (read) info from files
  dbFile.open(cDATAFILE); //use the 'special' variable (object's) method (a.k.a. function) called 'open' with the name of the file to access; in this case use the value defined as cDATAFILE 
  //once opened the computer will put a lock of the file meaning that if someone tries to open 'this' specific file they will be told it is already in use

  while (!dbFile.eof()) { //this sets up a loop that repeats until we have read every line in the opened file; line by line
    getline(dbFile, currentWord); //use getline function to access/put the current line of dbFile into the variable 'currentword', see http://www.cplusplus.com/reference/string/string/getline/ for more info
    currentWord.erase(remove_if(currentWord.begin(), currentWord.end(), [](unsigned char x) {
      return isspace(x);
    }), currentWord.end()); //this line of code removes all spaces from a string 'currentWord' by shifting all non-space characters to the left and then erasing the extra

    //this block of code is to make all strings lowercase
    string localStringLower = ToLower(localString); //declare and initialise a local string 'localStringLower', used to store the value of the 'localString' in lowercase calling the function ToLower
    string currentWordLower = ToLower(currentWord); //declare and initialise a local string 'currentWordLower', used to store the value of the 'currentWord' in lowercase calling the function ToLower

    if (localString.length() == currentWord.length() && localStringLower != currentWordLower) { //this if statement check the condition of the lengths 'localString' with 'currentWord' AND check the strings 'localStringLower' and 'currentWordLower'; if all conditions are met stays in the if statement
      string localSorted = OrderWord(localStringLower); //declare and initialise a local string, used to store the new ordered string calling the function OrderWord
      string currentSorted = OrderWord(currentWordLower); //declare and initialise a local string, used to store the new ordered string calling the function OrderWord

      if (localSorted == currentSorted) { //this if statement check the condition of the 'localSorted' with 'currentSorted', if equal stay in the if statement
        anagramList.append(currentWord + ", "); //extends the string "anagramList" by appending the "currentWord" at the end of its current value plus append a ", " (comma and space) to separate the strings
        anagramCounter++; //add 1 to the value of the integer "anagramCounter"
      }

    }

  }

  //if we are here there the program has read each line until it got to the end of the file
  dbFile.close(); //close the connection to the file

  anagramList = anagramList.substr(0, anagramList.length() - 2); //returns a newly constructed string without an extra ', ' (comma and space) at the end of the string

  //an if statement to check if we found an anagram, if don’t (anagramCounter == 0), add the message
  if (anagramCounter == 0) {
    anagramList = "No anagrams for the requested word were found. Please, enter a new word."; //store the message in the variable "anagramList"
  }

  //this block of code is to display the information to the user
  cout << "\033c"; //this instruction clear the screen
  cout << "\nAnagram(s) for the word: " << localString << endl; //display a message with the value of the variable "localString"
  cout << "\nNumber of anagram(s) found: " << anagramCounter << endl; //display a message with the value of the variable "anagramCounter"
  cout << "\nList of anagram(s) found: " << anagramList << endl; //display a message with the value of the variable "anagramList"
  cout << "\n\nPress [Enter] to return to Menu"; //display a message for the user
  cin.ignore(); //extracts characters from the input sequence and discards them
  cin.get(); //wait for a input from a standard input device i.e. keyboard
}

//this block of code constains a function to scan all available words and identify and display only the largest word available that contains (in any order) as many of the letters provided as possible
void LargestWordAvailable(string originalString) { //this function is designed to expect one argument (called originalString) and returns a string, the function has been declared as a type 'string'
  string localString = originalString; //declare and initialise a local string, used to store the new string
  string currentWord; //declare a variable of type string that can be used to hold each line as the file is read
  string largestWord; //declare a variable of type string that can be used to hold the value of the largestWord found
  vector < string > largestWordVector; //declare and initialise a vector type string to store all values for the largest word found
  int countWords = 0; //declare and initialise a local integer to store the number of largest words found
  ifstream dbFile; //create a special variable (actually a class (e.g. object with its own functions) that is defined in the <fstream> header that can be used to "stream" (read) info from files
  dbFile.open(cDATAFILE); //use the 'special' variable (object's) method (a.k.a. function) called 'open' with the name of the file to access; in this case use the value defined as cDATAFILE 
  //once opened the computer will put a lock of the file meaning that if someone tries to open 'this' specific file they will be told it is already in use

  while (!dbFile.eof()) { //this sets up a loop that repeats until we have read every line in the opened file; line by line
    getline(dbFile, currentWord); //use getline function to access/put the current line of dbFile into the variable 'currentword', see http://www.cplusplus.com/reference/string/string/getline/ for more info
    currentWord.erase(remove_if(currentWord.begin(), currentWord.end(), [](unsigned char x) {
      return isspace(x);
    }), currentWord.end()); //this line of code removes all spaces from a string 'currentWord' by shifting all non-space characters to the left and then erasing the extra

    //this block of code is to make all strings lowercase
    string localStringLower = ToLower(localString); //declare and initialise a local string 'localStringLower', used to store the value of the 'localString' in lowercase calling the function ToLower
    string currentWordLower = ToLower(currentWord); //declare and initialise a local string 'currentWordLower', used to store the value of the 'currentWord' in lowercase calling the function ToLower

    //this block of code is to sort all strings
    string localStringLowerSorted = OrderWord(localStringLower); //declare and initialise a local string, used to store the new ordered string calling the function OrderWord
    string currentWordLowerSorted = OrderWord(currentWordLower); //declare and initialise a local string, used to store the new ordered string calling the function OrderWord

    //this block of code constructs a sorted range formed only by the elements that are present in both strings
    string string_intersection; //declare a variable of type string that can be used to hold the value of the intersection found
    set_intersection(localStringLowerSorted.begin(), localStringLowerSorted.end(), currentWordLowerSorted.begin(), currentWordLowerSorted.end(), back_inserter(string_intersection)); //this line of code compares localStringLowerSorted with currentWordLowerSorted and all elements that are found in both sorted ranges will be copied to string_intersection

    if (string_intersection == currentWordLowerSorted && largestWord.length() < currentWordLowerSorted.length()) { //this if statement check the condition of the 'string_intersection' is equal to 'currentWordLowerSorted' AND check the lengths 'largestWord' is less than 'currentWordLowerSorted'; if all conditions are met stays in the if statement
      largestWordVector.clear(); //clear the vector
      largestWordVector.push_back(currentWord); //add the value of the string "currentWord" to the vector "largestWordVector"
      largestWord = currentWord; //make the string largestWord with the same value as currentWord
      countWords = 0; //make the integer countWords with the value 0
    }

    if (string_intersection == currentWordLowerSorted && largestWord.length() == currentWordLowerSorted.length()) { //this if statement check the condition of the 'string_intersection' is equal to 'currentWordLowerSorted' AND check the lengths 'largestWord' is equal to 'currentWordLowerSorted'; if all conditions are met stays in the if statement
      largestWordVector.push_back(currentWord); //add the value of the string "currentWord" to the vector "largestWordVector"
      countWords++; //add 1 to the value of the integer "countWords"
    }

  }

  //if we are here there the program has read each line until it got to the end of the file
  dbFile.close(); //close the connection to the file

  //this block of code initialises a random integer to possible display different results each time the function runs
  srand(time(0)); //initialises random number generator
  int x = rand() % largestWordVector.size(); //generate random integer with the size of the string 'largestWordVector'
  largestWord = largestWordVector[x]; //make the string largestWord with the same value as largestWordVector

  //this block of code is to display the information to the user
  cout << "\033c"; //this instruction clear the screen
  cout << "\nThe largest word available for the word: " << localString << endl; //display a message with the value of the variable "localString"
  cout << "\nNumber of the word could be found of the same length: " << countWords << endl; //display a message with the value of the variable "anagramList"
  cout << "\nLargest word found: " << largestWord << endl;
  cout << "\n\nPress [Enter] to return to Menu"; //display a message for the user
  cin.ignore(); //extracts characters from the input sequence and discards them
  cin.get(); //wait for a input from a standard input device i.e. keyboard
}

//this block of code constains a function to scan all available words and identify and display all entries that are examples of 3 letters anagram
void FindAll3LetterAnagrams(void) {
  string currentWord; //declare a variable of type string that can be used to hold each line as the file is read
  string anagramList; //declare and initialise a local string to store all values for anagrams found
  int threeLettersCounter; //declare and initialise a local integer to store the number of 3 letters words found
  int anagramCounter = 0; //declare and initialise a local integer to store the number of anagrams found
  vector < string > threeLettersVector; //declare and initialise a vector type string to store all values for 3 letters found to be manipulated
  vector < string > threeLettersVectorSorted; //declare and initialise a vector type string to store all values for sorted 3 letters found to be manipulated
  ifstream dbFile; //create a special variable (actually a class (e.g. object with its own functions) that is defined in the <fstream> header that can be used to "stream" (read) info from files
  dbFile.open(cDATAFILE); //use the 'special' variable (object's) method (a.k.a. function) called 'open' with the name of the file to access; in this case use the value defined as cDATAFILE 
  //once opened the computer will put a lock of the file meaning that if someone tries to open 'this' specific file they will be told it is already in use

  while (!dbFile.eof()) { //this sets up a loop that repeats until we have read every line in the opened file; line by line
    getline(dbFile, currentWord); //use getline function to access/put the current line of dbFile into the variable 'currentword', see http://www.cplusplus.com/reference/string/string/getline/ for more info
    currentWord.erase(remove_if(currentWord.begin(), currentWord.end(), [](unsigned char x) {
      return isspace(x);
    }), currentWord.end()); //this line of code removes all spaces from a string 'currentWord' by shifting all non-space characters to the left and then erasing the extra

    //this block of code check the length of the string "currentWord" and compare with the value "3"
    if (currentWord.length() == 3) {
      threeLettersVector.push_back(currentWord); //add the value of the string "currentWord" to the vector "threeLettersVector"
      sort(currentWord.begin(), currentWord.end()); //sort the value of the string "currentWord"
      threeLettersVectorSorted.push_back(currentWord); //add the value of the string "currentWord" to the vector "threeLettersVectorSorted"
    }

  }
  //if we are here there the program has read each line until it got to the end of the file
  dbFile.close(); //close the connection to the file

  //this block of code compare all values of the vector to find anagrams
  string tempAnagramList; //declare and initialise a local string to store values for anagrams found to add to the final list
  for (threeLettersCounter = 0; threeLettersCounter < threeLettersVector.size(); threeLettersCounter++) { //loop 'for' with the size of 'threeLettersVector'
    for (int x = 0; x < threeLettersVector.size(); x++) { //loop 'for' with the size of 'threeLettersVector'
      if (threeLettersVectorSorted[threeLettersCounter] == threeLettersVectorSorted[x] && threeLettersCounter != x && threeLettersVectorSorted[x] != "") { //this if statement check the condition of the 'threeLettersVectorSorted[threeLettersCounter]' is equal to 'threeLettersVectorSorted[x]' AND check the integers 'threeLettersCounter' is not equal to 'x' AND check the string 'threeLettersVectorSorted[x]' is not equal to '""'(empty); if all conditions are met stays in the if statement
        tempAnagramList.append(threeLettersVector[x] + ", "); //extends the string "tempAnagramList" by appending the "threeLettersVector[x]" at the end of its current value plus append a ", " (comma and space) to separate the strings
        threeLettersVectorSorted[x] = ""; //change the value of 'threeLettersVectorSorted[x]' to '""'(empty)
        anagramCounter++; //add 1 to the value of the counter "anagramCounter"
      }
    }
    if (tempAnagramList != "") { //this if statement check the condition of the 'tempAnagramList' is not equal to ""'(empty); if all conditions are met stays in the if statement
      tempAnagramList.append(threeLettersVector[threeLettersCounter]); //extends the string "tempAnagramList" by appending the "threeLettersVector[threeLettersCounter]" at the end of its current value
      anagramCounter++; //add 1 to the value of the counter "anagramCounter"
      anagramList.append(tempAnagramList + "\n"); //extends the string "anagramList" by appending the "tempAnagramList" at the end of its current value plus append a "\n" (new line) to insert the next value in the next line
    }
    tempAnagramList = ""; //clear the string 'tempAnagramList'
  }

  //this block of code is to display the information to the user
  cout << "\033c"; //this instruction clear the screen
  cout << "\nAll 3 letters anagrams" << endl; //display the requires message to the user
  cout << "\nNumber of anagrams found: " << anagramCounter << endl; //display a message with the value of the variable "anagramCounter"
  cout << "\nList of anagrams found: " << endl; //display the requires message to the user
  cout << anagramList; //display a message with the value of the variable "anagramList"
  cout << "\n\nPress [Enter] to return to Menu"; //display a message for the user
  cin.ignore(); //extracts characters from the input sequence and discards them
  cin.get(); //wait for a input from a standard input device i.e. keyboard
}

//this block of code constains a function to scan all available words and identify and display all entries that are examples of 5 letters anagram
void FindAll5LetterAnagrams(void) {
  string currentWord; //declare a variable of type string that can be used to hold each line as the file is read
  string anagramList; //declare and initialise a local string to store all values for anagrams found
  int fiveLettersCounter; //declare and initialise a local integer to store the number of 5 letters words found
  int anagramCounter = 0; //declare and initialise a local integer to store the number of anagrams found
  vector < string > fiveLettersVector; //declare and initialise a vector type string to store all values for 5 letters found to be manipulated
  vector < string > fiveLettersVectorSorted; //declare and initialise a vector type string to store all values for sorted 5 letters found to be manipulated
  ifstream dbFile; //create a special variable (actually a class (e.g. object with its own functions) that is defined in the <fstream> header that can be used to "stream" (read) info from files
  dbFile.open(cDATAFILE); //use the 'special' variable (object's) method (a.k.a. function) called 'open' with the name of the file to access; in this case use the value defined as cDATAFILE 
  //once opened the computer will put a lock of the file meaning that if someone tries to open 'this' specific file they will be told it is already in use

  while (!dbFile.eof()) { //this sets up a loop that repeats until we have read every line in the opened file; line by line
    getline(dbFile, currentWord); //use getline function to access/put the current line of dbFile into the variable 'currentword', see http://www.cplusplus.com/reference/string/string/getline/ for more info
    currentWord.erase(remove_if(currentWord.begin(), currentWord.end(), [](unsigned char x) {
      return isspace(x);
    }), currentWord.end()); //this line of code removes all spaces from a string 'currentWord' by shifting all non-space characters to the left and then erasing the extra

    //this block of code check the length of the string "currentWord" and compare with the value "5"
    if (currentWord.length() == 5) {
      fiveLettersVector.push_back(currentWord); //add the value of the string "currentWord" to the vector "fiveLettersVector"
      sort(currentWord.begin(), currentWord.end()); //sort the value of the string "currentWord"
      fiveLettersVectorSorted.push_back(currentWord); //add the value of the string "currentWord" to the vector "fiveLettersVectorSorted"
    }

  }
  //if we are here there the program has read each line until it got to the end of the file
  dbFile.close(); //close the connection to the file

  //this block of code compare all values of the vector to find anagrams
  string tempAnagramList; //declare and initialise a local string to store values for anagrams found to add to the final list
  for (fiveLettersCounter = 0; fiveLettersCounter < fiveLettersVector.size(); fiveLettersCounter++) { //loop 'for' with the size of 'fiveLettersVector'
    for (int x = 0; x < fiveLettersVector.size(); x++) { //loop 'for' with the size of 'fiveLettersVector'
      if (fiveLettersVectorSorted[fiveLettersCounter] == fiveLettersVectorSorted[x] && fiveLettersCounter != x && fiveLettersVectorSorted[x] != "") { //this if statement check the condition of the 'fiveLettersVectorSorted[fiveLettersCounter]' is equal to 'fiveLettersVectorSorted[x]' AND check the integers 'fiveLettersCounter' is not equal to 'x' AND check the string 'fiveLettersVectorSorted[x]' is not equal to '""'(empty); if all conditions are met stays in the if statement
        tempAnagramList.append(fiveLettersVector[x] + ", "); //extends the string "tempAnagramList" by appending the "fiveLettersVector[x]" at the end of its current value plus append a ", " (comma and space) to separate the strings
        fiveLettersVectorSorted[x] = ""; //change the value of 'fiveLettersVectorSorted[x]' to '""'(empty)
        anagramCounter++; //add 1 to the value of the counter "anagramCounter"
      }
    }
    if (tempAnagramList != "") { //this if statement check the condition of the 'tempAnagramList' is not equal to ""'(empty); if all conditions are met stays in the if statement
      tempAnagramList.append(fiveLettersVector[fiveLettersCounter]); //extends the string "tempAnagramList" by appending the "fiveLettersVector[fiveLettersCounter]" at the end of its current value
      anagramCounter++; //add 1 to the value of the counter "anagramCounter"
      anagramList.append(tempAnagramList + "\n"); //extends the string "anagramList" by appending the "tempAnagramList" at the end of its current value plus append a "\n" (new line) to insert the next value in the next line
    }
    tempAnagramList = ""; //clear the string 'tempAnagramList'
  }

  //this block of code is to display the information to the user
  cout << "\033c"; //this instruction clear the screen
  cout << "\nAll 5 letters anagrams" << endl; //display the requires message to the user
  cout << "\nNumber of anagrams found: " << anagramCounter << endl; //display a message with the value of the variable "anagramCounter"
  cout << "\nList of anagrams found: " << endl; //display the requires message to the user
  cout << anagramList; //display a message with the value of the variable "anagramList"
  cout << "\n\nPress [Enter] to return to Menu"; //display a message for the user
  cin.ignore(); //extracts characters from the input sequence and discards them
  cin.get(); //wait for a input from a standard input device i.e. keyboard
}

//this block of code contains a function with all options for the Menu
void Menu(void) { //this function is used to control the overall logic of the program
  string currentString = "alert"; //declare and initialise the variable to hold the current word ready to be manipulated; When the program initialises the value of this variable is "alert"
  char menuOption; //declare a variable to hold the user's menu choice

  do { //start an endless loop - this is so the associated code block repeats forever
    cout << "\033c"; //this instruction clear the screen
    cout << "\n\nC++ Anagram Solver Challenge" << endl << endl; //display a title for the menu
    cout << "\t1. Enter a word or phrase (current word/phrase is: " << currentString << ")." << endl; //display an option for the menu with the value of the variable "currentString"
    cout << "\t2. Find an anagram of the word." << endl; //display an option for the menu
    cout << "\t3. Find the largest word containing (most of) these letters." << endl; //display an option for the menu
    cout << "\t4. Find all possible 3 letter words that are also anagrams." << endl; //display an option for the menu
    cout << "\t5. Find all possible 5 letter words that are also anagrams." << endl; //display an option for the menu
    cout << "\n\t0. Quit the program." << endl; //display an option for the menu
    cout << "\n\tTime taken to complete the last function was: " << timeSeconds << "ms" << endl; //display a message with the value of the variable "timeSeconds"
    cout << "\nPlease enter a valid option (1 - 5 or 0 to quit): "; //display a message for the user
    cin >> menuOption; //store the choice made by the user in the variable menuOption

    switch (menuOption) { //a 'switch' statement is similar to multiple if's; see https://en.cppreference.com/w/cpp/language/switch

    case '1': //this basically "if the menuOption = 1", option 1 should call the function GetWord 
      currentString = GetWord(); //call the function and store any returned value in the local variable currentString
      break; //this keyword is optional, however, if not used all the following "cases" are automatically true and the instructions will all be executed

    case '2': //this basically "if the menuOption = 2", option 2 should call the function FindAnagrams
      StartTimer(); //call the function to start the clock
      FindAnagrams(currentString); //call the function and send the value of the currentString to be manipulated
      timeSeconds = StopTimer(); //call the function to stop the clock and store returned value in the variable timeSeconds
      break; //this keyword is optional, however, if not used all the following "cases" are automatically true and the instructions will all be executed

    case '3': //this basically "if the menuOption = 3", option 3 should call the function LargestWordAvailable
      StartTimer(); //call the function to start the clock
      LargestWordAvailable(currentString); //call the function and send the value of the currentString to be manipulated
      timeSeconds = StopTimer(); //call the function to stop the clock and store returned value in the variable timeSeconds
      break; //this keyword is optional, however, if not used all the following "cases" are automatically true and the instructions will all be executed

    case '4': //this basically "if the menuOption = 4", option 4 should call the function FindAll3LetterAnagrams
      StartTimer(); //call the function to start the clock
      FindAll3LetterAnagrams(); //call the function FindAll3LetterAnagrams
      timeSeconds = StopTimer(); //call the function to stop the clock and store returned value in the variable timeSeconds
      break; //this keyword is optional, however, if not used all the following "cases" are automatically true and the instructions will all be executed

    case '5': //this basically "if the menuOption = 5", option 5 should call the function FindAll5LetterAnagrams
      StartTimer(); //call the function to start the clock
      FindAll5LetterAnagrams(); //call the function FindAll5LetterAnagrams
      timeSeconds = StopTimer(); //call the function to stop the clock and store returned value in the variable timeSeconds
      break; //this keyword is optional, however, if not used all the following "cases" are automatically true and the instructions will all be executed

    case '0': //this basically "if the menuOption = 0", option 0 should call the function QuitNow
      QuitNow(); //call the function QuitNow
      break; //this keyword is optional, however, if not used all the following "cases" are automatically true and the instructions will all be executed

    default: //if the value of expression did not match any of the previously specified constants, the program executes the statements below
      cout << "\n\nUnfortunately, " << menuOption << " is not a valid option, please try again."; //display a message for the user with the inputed "character"
      cout << "\nPress [Enter] to continue..."; //display a message for the user
      cin.ignore(); //extracts characters from the input sequence and discards them
      cin.get(); //wait for a input from a standard input device i.e. keyboard
      break; //this keyword is optional, however, if not used all the following "cases" are automatically true and the instructions will all be executed
    }
  } while (true); //this tells the computer the conditions to break the "do" loop - while true is always true and therefore will continue forever; in essence and endless loop
}

int main() { //this function is required by C programs and is automatically executed when the program is run
  Menu(); //execute the required function to start the main logic of the program
}

/*
Test Log
*********************************************************************************************
Test Date, Cores, Description, What did I test?, Results, Reflections
********************************************************************************************

05/03/2019 - Since I did Task 1, I was able to copy and paste it into my Task 2 because the main functions requested in Task 2 were already done in Task 1 only requiring refactoring the code and cleaning-up unused lines - No tests were execute

07/03/2019 - GetWord, QuitNow, Menu - I have refactored the previews Functions Operations (Cores) to the ones were solicited in the Programming Assignment - I have tested all functions, and all of them worked as I expected - PASSED

11/03/2019 - FindAnagrams - I have created a function to find anagrams - I have tested with different inputs, and the program was able to find anagrams as I expected - PASSED

16/03/2019 - FindAnagrams - I have improved the function with the lowercase option in case the user input any uppercase character to my program could find anagrams - PASSED

17/03/2019 - FindAnagrams - I have improved the function with a better output of the results for the user - PASSED

19/03/2019 - StartTimer, StopTimer - I have created these functions to be able to refactor my code and reuse them to reduce duplicate code in my program. I have used these new functions to reduce the lines in the functions "FindAnagrams", "LargestWordAvailable", "FindAll3LetterAnagrams" and "FindAll5LetterAnagrams" - PASSED

20/03/2019 - FindAll3LetterAnagrams, FindAll5LetterAnagrams - I have created functions to find 3 letters and 5 letters anagrams - I have tested the function "FindAll3LetterAnagrams", and I have got the correct result. The function was able to find 3 letters anagrams as I expected - PASSED

22/03/2019 - FindAll3LetterAnagrams - I have improved the function with a better output of the results for the user - PASSED

24/03/2019 - FindAll5LetterAnagrams - I have refactored the function "FindAll3LetterAnagrams" to "FindAll5LetterAnagrams". I have changed the name of the variables to match with this function - I have tested function and worked as I expected - PASSED

28/03/2019 - LargestWordAvailable - I have created a function to find the largest word available containing, in any order, as many of the letters provided as possible - I have tested with different inputs, and the program was able to return strings as I expected - I have to do further tests to guarantee that the function is giving the right result - FAILED

29/03/2019 - LargestWordAvailable - I have done further tests, and the function gave the result as I expect - PASSED

30/03/2019 - ToLower, OrderWord - Since I did Task 1, I was able to refactor my code using some functions that were created in the previews task and reuse them to reduce duplicate code in my program. I have used these new functions to reduce the lines in the functions "FindAnagrams" and "LargestWordAvailable" - PASSED

31/03/2019 - LargestWordAvailable - I have improved the function with a random option for the result of the string - I have sent an email to Mike on March 30th asking about if every time the function runs, the function should return a different string when it is possible. As I do not have any answer up to the end of the time, I have decided to implement this option to the function - I have done further tests and the function switch between 2 results as I expect - PASSED

31/03/2019 - All Functions - I have tested and reviewed all the functions of the program and read all the comments made to release the Assignment to the teacher - PASSED

*/
