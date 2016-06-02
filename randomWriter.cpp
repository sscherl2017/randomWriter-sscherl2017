//
//  main.cpp
//  randomWriter
//
//  Created by Sam Scherl on 5/25/16.
//  Copyright © 2016 Sam Scherl. All rights reserved.
//

// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

/*
* Replaces any "special" characters within a line with a space
*/
string processLine(string line)
{
	string newLine = "";

	for(int i = 0; i < line.length(); i++)
	{

		char c = line.at(i);

		int ascii = c - 0;

		//Check to see if it's a letter or an apostrophe
		if (ascii >= 32 && ascii <= 125) 
		{
			newLine = newLine + c;
		}
		else
			newLine = newLine + " ";

	}
	return newLine;

}

/*
* Parses through the input text file and converts it into a String.
*/
string read () {
    string line;
    string fullText;
    ifstream myfile ("tenderButtons.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile, line) )
            fullText += processLine(line);
        myfile.close();
    }
    else cout << "Unable to open file";
    return fullText;
}

/*
* Iterates through the text, and chooses a character from the String of characters that follows
* a given seed, appends that character to the ouput String, and shifts the seed over to include this new character.
*/
int main () {
	srand(time(0));
	int seedLength = 5;
	string outputText = "";
	int outputLength = 200;
	string possibleFollowing;
	string fullText = read();
	int startingPosition = rand() % (fullText.length() - outputLength);
	string seed = fullText.substr(startingPosition, seedLength);
	
	for (int i = 0; i < outputLength; i++)
	{
		possibleFollowing = "";
		for (int j = 0; j < fullText.length() - seedLength - 1; j++)
		{
			if (fullText.substr(j, seedLength) == seed)
				possibleFollowing = possibleFollowing + fullText.substr(j + seedLength, 1);
		}
		int randomNum = (rand() % possibleFollowing.length());
		
		/*	
		cout << "seed:" << seed << "\n";
		cout << "possFollowing:" << possibleFollowing << "\n";
		cout << "randomNun:" << randomNum << "\n";
		cout << "followingCharacter:" << possibleFollowing.substr(randomNum, 1) << "\n";
		*/
		
		seed = seed.substr(1, seedLength - 1) + possibleFollowing.substr(randomNum, 1);
		
		outputText = outputText + possibleFollowing.substr(randomNum, 1);
			
		//cout << "outputText: " << outputText << "\n\n" ;
	}
	cout << outputText;
	cout << endl;
	return 0;
}