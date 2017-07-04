/*Machine Problem 5
Author: Mark Keranen CPS171 07/03/2017

The method of encryption used here is a simple substitution cipher that depends on the sender and receiver of the message 
agreeing on a keyword, which is usually just one word that will be easy to remember. Thus the key for decrypting the message 
will not have to be written down and is less likely to fall into enemy hands!

First, the program must read in a keyword, which will be all capital letters. The letters of the keyword must be inserted in 
the order in which they occur into a 5x5 two dimensional array by rows, but if a letter is repeated in the keyword it is only 
used once in the two-dimensional array. Then the array is filled up with the remaining letters of the alphabet in order 
(excluding the 'Z'). 

Ex: Keyword HAPPINESS results in a key matrix:
	0	1	2	3	4
---------------------
0| H | A | P | I | N |
---------------------
1| E | S | B | C | D |
---------------------
2| F | G | J | K | L |
---------------------
3| M | O | Q | R | T |
---------------------
4| U | V | W | X | Y |

Next, the program will read in a series of lines containing either messages to encrypt or decrypt.

A plain text message will be encrypted as follows:

Each letter in the message will be found in the table, and the row and column will be noted. It will then be encrypted by reversing 
the row and column values. Spaces between words will be maintained exactly as they appear in the message. A message that is already 
encrypted can be decrypted using exactly the same algorithm – the only difference is that the incoming message will be in upper case 
and the decrypted message will be in lower case.

*/

//Include statements
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Main code loop
int main() {

	//Initialized string variable for keyword
	string key;

	//Function prototype statements
	void encryptionDecryption(string, ifstream&);

	//Open file and extract keyword from first line, assign it to string variable 'key'
	ifstream fin;
	fin.open("MP5_encrypt_decrypt_message.txt");
	fin >> key;
	
	//Function call to analyze input file, and proceed with encryption or decryption
	encryptionDecryption(key, fin);	

	//Close the opened file
	fin.close();
}

/*****************************************************************************************************************

FUNCTIONS

*****************************************************************************************************************/

/*
Function: Takes in keyword for encryption / decryption and creates keyword array. Then outputs said array to standard output.
Next, the remaining lines from the file are read in and encrypted or decrypted. 
*/
void encryptionDecryption(string keyword, ifstream& fin) {
	//Initialize counters, constants, etc. to be used in creation of initial encryption / decryption array
	int i, j, index;
	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXY";
	string keyArrayString, decryptionString, encryptionString;
	char encryptOrDecrypt;
	
	//Initialize 5x5 key array
	const int row = 5;
	const int column = 5;
	char keyArray[row][column];

	//Checks for and removes duplicate letters in 'keyword'
	for (i = 0; i < keyword.size(); i++) {
		for (j = 0; j < i; j++) {
			if (keyword[i] == keyword[j]) {
				keyword.erase(j, 1);
			}
		}
	}

	//Checks for and removes duplicates in "alphabet"
	for (i = 0; i < keyword.size(); i++) {
		for (j = 0; j < alphabet.size(); j++) {
			if (keyword[i] == alphabet[j]) {
				alphabet.erase(j, 1);
			}
		}
	}

	//Appends modified alphabet to keyArrayString, prepping for building of key array
	keyArrayString = keyword.append(alphabet);

	//Builds 5x5 array from modified keyword string
	index = 0;
	for (i = 0; i < row; i++) {
		for (j = 0; j < column; j++) {
			keyArray[i][j] = keyArrayString[index];
			index++;
		}
	}

	//Prints out keyArray that will be used for encrypting & decrypting
	cout << "Key Array: \n" << endl;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			cout << keyArray[i][j] << ' ';
		}

		cout << endl;
	}
	cout << "\n************************************************************\n" << endl;

	//Loop for reading in encryption / decryption file
	while (fin.good()) {

		//Reads first char of input file to determine whether the line should be decrypted or encrypted
		fin >> encryptOrDecrypt;

		//Decryption
		if (encryptOrDecrypt == 'D') {												//Check whether should encrypt or decrypt
			cout << "DECRYPT: ";														
			getline(fin, decryptionString);											//Get line to be decrypted, assign to 'decryptionString
			cout << decryptionString << endl;										//Output line to be decrypted
			
			//Loop through each char in 'decryption string' and compare to each element in 'keyArray'. If a match is found in decryption
			//string, the index of the keyArray is flipped, and the element with the new index replaces the old char in decryptionString
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					for (index = 0; index < decryptionString.length(); index++) {
						if (decryptionString[index] == keyArray[i][j]) {
							decryptionString[index] = tolower(keyArray[j][i]);
						}
						
					}
				}
			}
			
			//Output results of decryption
			cout << "Decrypted: " << decryptionString << endl << endl;
			cout << "\n************************************************************\n" << endl;
		}

		//Encryption
		else if (encryptOrDecrypt == 'E'){											//Check whether to encrypt or decrypt
			cout << "ENCRYPT: ";							
			getline(fin, encryptionString);											//Get line to be encrypted, assign to 'encryptionString
			cout << encryptionString << endl;										//Output line to be encrypted

			//Loop through each char in 'encryptionString' and compare to each element in 'keyArray'. If a match is found in encryption
			//string, the index of the keyArray is flipped, and the element with the new index replaces the old char in encryptionString
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					for (index = 0; index < encryptionString.length(); index++) {
						if (encryptionString[index] == tolower(keyArray[i][j])) {	//when comparing, make sure chars have the same case..
							encryptionString[index] = toupper(keyArray[j][i]);
						}
					}
				}
			}
			
			//Output results of encryption
			cout << "Encrypted: " << encryptionString << endl << endl;
			cout << "\n************************************************************\n" << endl;
		}
		
	}
}
