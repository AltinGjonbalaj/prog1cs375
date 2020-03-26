#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
using namespace std::chrono;
using namespace std;
//NOTHING HAS CHANGED ABOUT VARIABLES, SAME FROM QUESTION 1
int lcs2(string s1, string s2, int i, int j){
	char cs1[s1.size()]; copy(s1.begin(), s1.end(), cs1);
	char cs2[s2.size()]; copy(s2.begin(), s2.end(), cs2);

	if(i == -1 || j == -1) 
		return 0;
	else if(cs1[i] == cs2[j])
		return 1 + lcs2(s1, s2, i-1, j-1); 
	else
		return max(lcs2(s1, s2, i, j-1), lcs2(s1, s2, i-1, j));
}

int main(int argc, char *argv[]){
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


	auto start = high_resolution_clock::now();
        string res = to_string(lcs2(str1, str2, str1.size()-1, str2.size()-1));
	auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

	writeFile << "Result: " << res << '\n';
        writeFile << "Runtime: " << duration.count() << "microseconds" << '\n';

        writeFile.close(); readFile1.close(); readFile2.close();
        return 0;
}
