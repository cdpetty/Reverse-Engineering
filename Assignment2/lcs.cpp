#include <vector>

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

int main() {

}