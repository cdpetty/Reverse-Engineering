#include <vector>
#include <iostream>
#include <fstream>

int longest_common_substring(char* s1, int s1_len, char* s2, int s2_len) {

	int L[s1_len][s2_len] = {{0}};
	int z = 0;
	std::vector<int> ret;
	for (int i = 1; i < s1_len; i++) {
		for (int j = 1; j < s1_len; j++) {
			if (s1[i-1] == s2[j-1]) {
				if (i == 1 || j == 1) {
					L[i][j] = 1;
				}
				else {
					L[i][j] = L[i][j] + 1;
				}

				if (L[i][j] > z) {
					z = L[i][j];
					ret.push_back(z);
				}
			}
		}
	}

	return z;
}

int get_file_size(char* file_name) {
	std::streampos begin, end;
	std::ifstream myfile(file_name, ios::binary);
	myfile.seekg (0, ios::end);
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

	std::cout<<"Reading in files...";
	char s1[f1_size];
    ifstream f1(argv[1], ios::in | ios::binary);
    f1.read (s1, f1_size);
    f1.close();

    char s2[f1_size];
    ifstream f2(argv[2], ios::in | ios::binary);
    f2.read (s2, f2_size);
    f2.close();
    std::cout<<"done.\nCalculating LCS\n";

    std::cout<<"length of LCS: "<<longest_common_substring(s1, f1_size, s2, f2_size) << "\n";
    
}