#include <vector>
#include <iostream>
#include <fstream>
#include <string>

const int NUM_LONGEST_STRINGS = 5;

int longest_common_substring(char* s1, int s1_len, char* s2, int s2_len, char* s3, int s3_len) {

	std::vector<std::string> longest;
	for(int i = 0; i < NUM_LONGEST_STRINGS; i++) {//<--quality
		longest.push_back("");
	}

	int*** L = new int**[s1_len];
	for(int i = 0; i < s1_len; ++i) {
		L[i] = new int*[s2_len];
		for (int j = 0; j < s2_len; j++) {
			L[i][j] = new int[s3_len];
		}
		L[i][0][0] = 0;
	}
	for(int i = 0; i < s3_len; ++ i){
		L[0][0][i] = 0;
	}
	for(int i = 0; i < s2_len; i++) {
		L[0][i][0] = 0;
	}

	int z = 0;
	std::vector<int> ret;
	int apple = 0;
	for (int i = 1; i < s1_len; i++) {
		if (apple % 1000 == 0){
			std::cout << apple << std::endl;
		}
		apple++;
		for (int j = 1; j < s2_len; j++) {
			for (int l = 0; l < s3_len; l++) {
				if (s1[i-1] == s2[j-1] && s1[j-1] == s3[l-1]) {
					if (i == 1 || j == 1 || l == 1) {
						L[i][j][l] = 1;
					}
					else {
						L[i][j][l] = L[i-1][j-1][l-1] + 1;
					}

					if (L[i][j][l] > z) {
						z = L[i][j][l];
						ret.push_back(z);

						int minIndex = 0;
						int minLength = longest[0].size();
						for(int k = 1; k < NUM_LONGEST_STRINGS; ++k){
							if (longest[k].size() < minLength){
								minIndex = k;
								minLength = longest[k].size();
							}
						}
						longest.erase(longest.begin() + minIndex, longest.begin() + minIndex + 1);
						std::string finalString = "";
						for (int k = i - z + 1; k <= i; k++){
							finalString += s1[k];
						}
						longest.push_back(finalString);

					}
				}
			}
		}
	}

	std::ofstream outfile("Longest_Common_Substrings.txt", std::ios::binary);
	std::ofstream outfile2("Longest_Common_Substring_lengths.txt");
	std::string delimeter = "\n\n\n\n";
	for(int i = 0; i < NUM_LONGEST_STRINGS; ++i){
		outfile.write(longest[i].c_str(), longest[i].size());
		outfile.write(delimeter.c_str(), delimeter.size());
		std::string size = std::to_string(longest[i].size());
		std::cout << "Size: " << size << std::endl;
		outfile2.write(size.c_str(), size.size());
		outfile2.write(delimeter.c_str(), delimeter.size());
	}

	outfile.close();
	outfile2.close();


	return z;
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
		std::cout<<"Need atleast 3 files\n";
		return 1;
	}

	std::cout<<"Getting file size...";
	int f1_size = get_file_size(argv[1]);
	int f2_size = get_file_size(argv[2]);
	int f3_size = get_file_size(argv[3]);
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

    char s3[f3_size];
    std::ifstream f3(argv[3], std::ios::in | std::ios::binary);
    f3.read (s3, f3_size);
    f3.close();
    std::cout<<"done.\nCalculating LCS\n";

    std::cout<<"length of LCS: "<<longest_common_substring(s1, f1_size, s2, f2_size, s3, f3_size) << "\n";
    
}