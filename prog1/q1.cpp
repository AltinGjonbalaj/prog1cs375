#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std::chrono;
using namespace std;


/*string1 is one of the strings passed
 *int i is length of strng1
 *int j is length of string2
 *mem is the vector that stores the array
 *cs1 is the char version of the string passed
 *write is the file to write to
 *@return this function write the lcs in the file
*/
void  printStr(string string1, int i, int j, vector<vector<int>> mem, ofstream &write){
	char cs1[string1.size()]; copy(string1.begin(), string1.end(), cs1);
	
	if(i == 0 || j == 0)
		return ;
	if(mem[i][j] == mem[i-1][j]){ //go up
		printStr(string1, i-1, j, mem, write);
	}
	else if(mem[i][j] == mem[i][j-1]){ //go left
		printStr(string1, i, j-1, mem, write);
	}
	else if(mem[i][j] == mem[i-1][j-1]){ //go diagonal
		printStr(string1, i-1, j-1, mem, write);
	}
	else{//not equal to any of the three therefore the letter is in the lcs
		write << string1[i-1];	
		printStr(string1, i-1, j-1, mem, write);
	}
}

/*s1 is one of the strings passed
 *s2 is the other string passed
 *mem is the vector of lengths
 *writefile is the output file
 *@return is void, this function writes the array if necessary and the length or results
 *cs1 and cs2 are char versions of the strings passed
*/
void lcs1(string s1, string s2, vector<vector<int>> & mem, ofstream &writeFile){
	char cs1[s1.size()]; copy(s1.begin(), s1.end(), cs1);
	char cs2[s2.size()]; copy(s2.begin(), s2.end(), cs2);

	for(int i = 1; i < s1.size() + 1; i++){
		for(int j = 1; j < s2.size() + 1; j++){
			if(cs1[i-1] == cs2[j-1])
				mem[i][j] = mem[i-1][j-1]+1;
			else if (mem[i-1][j] >= mem[i][j-1])
				mem[i][j] = mem[i-1][j];
			else
				mem[i][j] = mem[i][j-1];	
		}
	}


	if(s1.size() <= 10 && s2.size() <= 10){
		for(int i = 0; i < s1.size()+ 1; i++){
			for(int j = 0; j < s2.size() + 1; j++){
				writeFile<< mem[i][j];
			}
			writeFile<< endl;
		}
		writeFile << "Result: ";
		printStr(s1, s1.size(), s2.size(), mem, writeFile);
		writeFile << endl;
	}
	else
		writeFile << "Result: " << mem[s1.size()][s2.size()] << endl;
}
/*writefile is the file to writeto
 *readfile 1 and 2 are the two files to read from
 *str1 and str2 arethe strings taken from the readfiles
 *mem is the vector to store the length matrix
 *start and stop are for time calculation
 */
int main(int argc, char* argv[]){
	if(argc > 4)
		cout << "wrong amt of args" << endl;

	ofstream writeFile;
	writeFile.open(argv[3]);

	ifstream readFile1;
	ifstream readFile2;

	string str1;
	string str2;

	readFile1.open(argv[2]);
	readFile2.open(argv[1]);

	getline(readFile1, str1, '\n');
	getline(readFile2, str2, '\n');

	vector<vector<int>> mem;

	for(int i = 0; i < str1.size()+1; i++){
		vector<int> temp;
		for(int j = 0; j < str2.size()+1; j++){
			temp.push_back(0);
		}
		mem.push_back(temp);
	}

	auto start = high_resolution_clock::now();
	lcs1(str1, str2, mem, writeFile);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	writeFile << "Runtime: " << duration.count() << "microseconds" << '\n';

	
	writeFile.close(); readFile1.close(); readFile2.close();
	return 0;
}
