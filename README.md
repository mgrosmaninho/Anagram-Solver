# Anagram-Solver
Coursework from University of Hertfordshire


## Task
Create a C++ (version 11) program that performs the functions necessary to analyse and create anagrams; we shall define and anagram as a word or phrase formed by rearranging the letters of another word (for example: spar can be formed from rasp, alert can be formed from lager, etc.).

Once run, your program should present the user with a menu that displays the title “C++ Anagram Solver Challenge” and presents the user with a number of menu choices.  Once the menu has been shown, the user must be asked to make a selection by stating “Please enter a valid option (1 – 5 or 0 to quit): ”.  

Ensure you design your program so that when initially executed it presents the user with the following options; match the layout and output as closely as possible:

```
C++ Anagram Solver Challenge

1. Enter a word or phrase (current word/phrase is: alert). 
2. Find an anagram of the word.
3. Find the largest word containing (most of) these letters.
4. Find all possible 3 letter words that are also anagrams.
5. Find all possible 5 letter words that are also anagrams.

0. Quit the program.

Time taken to complete the last function was: 0ms

Please enter a valid option (1 – 5 or 0 to quit): 
```

If the user enters any non-valid option, your program must issue the following error message: Unfortunately, ‘XX’ is not a valid option, please try again.

Ensure your program replaces XX (contained inside the two single quotes) with the invalid option entered. For example, it the user enters the letter “q”, the error message would be:
Unfortunately, ‘q’ is not a valid option, please try again.


## Program Requirements
Design your program so that each menu option calls a dedicated function; your function names must be: GetWord, FindAnagrams, LargestWordAvailable, FindAll3LetterAnagrams, FindAll5LetterAnagrams and QuitNow.  With the exception of the quit option, your program must repeatably (after each menu option has completed) return and present the user with the menu (including the title).  If the user enters a new word or phrase (e.g. used option 1 to change the default word (which must initially be: alert) then this new word is displayed (until changed again) as part of the menu option.  If the user selects the quit option (e.g. 0) the associated function must display the message:
Are you sure (Y/N)?

Your program will only terminate if the user enters either: “Y”, “Yes” or “y”; after which your function must use the C++ instruction: ”exit(EXIT_SUCCESS);” to terminate.

If the user enters any other response the program should return back to the menu function and allow them to select any other valid option (as many times as they like).

In addition, you will be expected to implement a fairly accurate timer that can be used to report the time taken to process the users request. For example once the user has selected option 2 (find an anagram) the function will initialise a timer that will count the time taken for the program to return with a result; take a look at the results summary used by Google after entering a search term – when searching the term “anagrams” it reported that it found about 72,500,000 results in 0.42 seconds. Design your program so the time taken to process each request is shown as part of the menu (specifically on the line “Time taken to complete the last function was…”). 


## Function Requirements
Each of the anagram functions (i.e. FindAnagrams(), LargestWordAvailable) must be designed to accept one argument; that argument will contain the value of the current word/phrase (e.g. shown in menu option 1).  Each of the function names should be defined using the following signature as a template (obviously you will need to use the required/actual function name:
```void FUNCTION_NAME(std::string originalString)```

However, both the functions: FindAll3LetterAnagrams() and FindAll5LetterAnagrams() must be designed not to accept or return any data:
```void FUNCTION_NAME(void)```

Depending on how you decide to design and code your program you will be expected to use the test data provided (there are two test files for you to use: Words_100_Testing.csv and Words_1K_Testing.csv).  The Words100 file contains 100 random words while the Words_1K file contains 1000 random words. You are advised to start testing your code on the 100 version before using the 1000 word test file.  Your program will be assessed using a much bigger dataset (around 75,000 words so it is important to ensure your code is optimised first to work, then for speed).  Once you are sure your functions are working it is strongly suggested that you try using the pre-submission assessment csv file (this file contains approx. 75,000 English words) to more fully test and highlight any potential issues with your algorithm, code and/or its performance.


## Function Operations
GetWord() -  this function is defined so that it does not expect any arguments, however it does return a string datatype.  Its purpose is to allow the user to enter a new word which can then be use by the other functions.  The function must return the user’s specified word or phrase; this replacement word should then be shown to the user as part of the previously defined Menu operation (specifically as part of the output line “current word/phrase is…”); ensure the function is declared appropriately.

FindAnagrams() – this function must be defined so that it expects only one string and does not return a result (the function’s input value must be named “originalString”; see the template signature discussed under the function requirements section for more detail).  A locally defined variable (called localString) should also be declared and initialised so that it is a copy of the original input value. Using the data from an appropriate test file (e.g. Words_100_Testing.csv or Words_1K_Testing.csv, etc) this function is required to scan all available words and identify and display each word that is an anagram of the string provided; the system must not include the original string as an anagram of itself.  If provided with the string “Lager” it should display all correct anagrams (e.g. regal, glare, etc); the system should (in addition to the words) also count the number of results found – in this case 2 anagrams of Lager.  You are expected to display the results in an efficient, logical, clear and organised way.  When matching anagrams you are requested to ignore case; Lager and lager are the same – this means that your system should not differentiate whether a word contains upper of lower case characters.

LargestWordAvailable() – this function must be defined so that it expects only one string and does not return a result (the function’s input value must be named “originalString”; see the template signature discussed under the function requirements section for more detail).  A locally defined variable (called localString) should also be declared and initialised so that it is a copy of the original input value. Using the data from an appropriate test file (e.g. Words_100_Testing.csv or Words_1K_Testing.csv, etc) this function is required to scan all available words and identify and display only the largest word available that contains (in any order) as many of the letters provided as possible; in essence this function should be able to solve the random words used in the gameshow “countdown” or “8 out of 10 cats does countdown”.  An example might be the letters “eshpoiexd”, your function may find the valid word “episode” or “exposed” or “epoxies”; however, in addition to finding the largest word it should also provide an indication of how many other words could be found of the same length.

FindAll3LetterAnagrams() – this function must be designed so that is scans your specified data file and identifies all entries that are examples of three letter anagrams; each sequence of anagrams must be displayed together and a clear separation must exist if a new sequence of three letter anagrams are found. 

FindAll5LetterAnagrams() – this function must be designed so that is scans your specified data file and identifies all entries that are examples of five letter anagrams; each sequence of anagrams must be displayed together and a clear separation must exist if a new sequence of three letter anagrams are found. 

QuitNow() – this function does not expect or return any data and must be declared as void.  Its purpose is to allow the user to exit the program. Once selected it must allow the user to change their mind using an “are you sure” option.  It the user is sure then the program will quit; however, if the user enters anything other than “Y”, “y” or “Yes” the user will we returned back to the menu function and allowed to select another option.

## Contact me!

For more information about this project, please email me at mgrosmaninho@hotmail.com
