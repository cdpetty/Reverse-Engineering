#include <vector>
#include <cstring>
#include <iostream>

char* s1 = "adcdmmpmpmpmplpmpmpmmmplmplmppllp";
char* s2 = "ygvygvygvygvygvabcdhbuhbuhbuhbuuhb";

int longest = 0;

struct Node {
	std::vector<Node*> children;
	char ch;
	int leaf;

	Node* getChild(char ch) {
		Node* ret = nullptr;
		for (int i = 0; i < children.size(); i++) {
			if (children[i]->ch == ch) {
				ret = children[i];
				break;
			}
		}

		if (ret == nullptr) {
			ret = new Node();
			ret->ch = ch;
			children.push_back(ret);
		}

		return ret;
	}

};

void addToTree(Node* root, char* str) {
	int str_len = strlen(str);

	for (int i = str_len - 1; i >= 0; i--) {
		Node* current_node = root;
		char* suffix = str+i;
		int suffix_len = strlen(suffix);
		for (int j = 0; j < suffix_len; j++) {
			current_node = current_node->getChild(suffix[j]);
		}
		if (++current_node->leaf > 1) {
			std::cout<<suffix<<std::endl;
		}
	}
}


int main() {
	Node* root = new Node();
	addToTree(root, s1);
	addToTree(root, s2);
	return 0;
}
