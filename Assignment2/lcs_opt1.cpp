#include <vector>
#include <iostream>
#include <fstream>
#include <string>

int NUM_LONGEST_STRINGS = 5;


//  Based on https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Longest_common_substring#C.2B.2B
int longest_common_substring(char* s1, int s1_len, char* s2, int s2_len) {

	int* curr = new int[s2_len];
	int* prev = new int[s2_len];
	int* swap = nullptr;
	int maxSubstr = 0;

	for (int i = 0; i < s1_len; i++) {
		for (int j = 0; j < s2_len; j++) {
			if (s1[i] != s2[j]) {
				curr[j] = 0;
			}
			else {
				if (i == 0 || j == 0) {
					curr[j] = 0;
				}
				else {
					curr[j] = 1 + prev[j-1];
				}

				if (maxSubstr < curr[j]) {
					maxSubstr = curr[j];
				}
			}
		}
		swap = curr;
		curr = prev;
		prev = swap;
	}

	delete [] curr;
	delete[] prev;
	return maxSubstr;
}

int get_file_size(char* file_name) {
	std::streampos begin, end;
	std::ifstream myfile(file_name, std::ios::binary);
	myfile.seekg (0, std::ios::end);
	end = myfile.tellg();
	myfile.close();
	return end - begin;
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		std::cout<<"Need atleast 2 files\n";
		return 1;
	}

	std::cout<<"Getting file size...";
	int f1_size = get_file_size(argv[1]);
	int f2_size = get_file_size(argv[2]);
	std::cout<<"done.\n";
	std::cout << "\n\n f1 size: " << f1_size << " f2 size: " << f2_size << std::endl;

	std::cout<<"Reading in files...";
	char s1[f1_size];
    std::ifstream f1(argv[1], std::ios::in | std::ios::binary);
    f1.read (s1, f1_size);
    f1.close();

    char s2[f2_size];
    std::ifstream f2(argv[2], std::ios::in | std::ios::binary);
    f2.read (s2, f2_size);
    f2.close();
    std::cout<<"done.\nCalculating LCS\n";

    std::cout<<"length of LCS: "<<longest_common_substring(s1, f1_size, s2, f2_size) << "\n";
    
}
