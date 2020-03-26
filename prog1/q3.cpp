#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std::chrono;
using namespace std;
//NOTHING HAS CHANGED ABOUT VARIABLES, SAME FROM QUESTION 1
int lcs3(string s1, string s2, int i, int j, vector<vector<int>> & mem){
	char cs1[s1.size()]; copy(s1.begin(), s1.end(), cs1);
	char cs2[s2.size()]; copy(s2.begin(), s2.end(), cs2);

	if(i == -1 || j == -1)
		return 0;
	if(mem[i][j] != -1)
		return mem[i][j];
	else if(cs1[i] == cs2[j])
		return 1 + lcs3(s1, s2, i-1, j-1, mem);
	else
		mem[i][j] = max(lcs3(s1, s2, i, j-1, mem), lcs3(s1, s2, i-1, j, mem));
		return mem[i][j];
}

int main(int argc, char *argv[]){
	if(argc > 4)
		cout << "wrong arg amt" << endl;

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

	for(int i = 0; i < str1.size(); i++){
		vector<int> temp;
		for(int j = 0; j < str2.size(); j++){
			temp.push_back(-1);
		}
		mem.push_back(temp);
	}

	auto start = high_resolution_clock::now();
        string res = to_string(lcs3(str1, str2, str1.size()-1, str2.size()-1, mem));
	auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

	writeFile << "Result: " << res << '\n';
        writeFile << "Runtime: " << duration.count() << "microseconds" << '\n';

        writeFile.close(); readFile1.close(); readFile2.close();
        return 0;
}
