// Taken from http://www.geeksforgeeks.org/suffix-tree-application-5-longest-common-substring-2/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
const int MAX_CHAR = 246;

struct SuffixNode {
	struct SuffixNode* children[MAX_CHAR];

	struct SuffixNode* suffixLink;

	int start;
	int* end;

	int suffixIndex;
};

typedef struct SuffixNode Node;

char* text;//input str
Node* root = NULL;

Node* lastNewNode = NULL;
Node* activeNode = NULL;

int activeEdge = -1;
int activeLength = 0;

int remainingSuffixCount = 0;
int leafEnd = -1;
int* rootEnd = NULL;
int* splitEnd = NULL;
int size = -1; //Length of input string
int size1 = 0; //Size of 1st string

Node* newNode(int start, int* end) {
    Node* node = new Node();
    for (int i = 0; i < MAX_CHAR; i++)
          node->children[i] = NULL;
  
    /*For root node, suffixLink will be set to NULL
    For internal nodes, suffixLink will be set to root
    by default in  current extension and may change in
    next extension*/
    node->suffixLink = root;
    node->start = start;
    node->end = end;
  
    /*suffixIndex will be set to -1 by default and
      actual suffix index will be set later for leaves
      at the end of all phases*/
    node->suffixIndex = -1;
    return node;
}

int edgeLength(Node* n) {
    if(n == root)
        return 0;
    return *(n->end) - (n->start) + 1;
}

int walkDown(Node* currNode) {
    /*activePoint change for walk down (APCFWD) using
     Skip/Count Trick  (Trick 1). If activeLength is greater
     than current edge length, set next  internal node as
     activeNode and adjust activeEdge and activeLength
     accordingly to represent same activePoint*/
    if (activeLength >= edgeLength(currNode))
    {
        activeEdge += edgeLength(currNode);
        activeLength -= edgeLength(currNode);
        activeNode = currNode;
        return 1;
    }
    return 0;
}

void extendSuffixTree(int pos) {
    /*Extension Rule 1, this takes care of extending all
    leaves created so far in tree*/
    leafEnd = pos;
  
    /*Increment remainingSuffixCount indicating that a
    new suffix added to the list of suffixes yet to be
    added in tree*/
    remainingSuffixCount++;
  
    /*set lastNewNode to NULL while starting a new phase,
     indicating there is no internal node waiting for
     it's suffix link reset in current phase*/
    lastNewNode = NULL;
  
    //Add all suffixes (yet to be added) one by one in tree
    while(remainingSuffixCount > 0) {
  
        if (activeLength == 0)
            activeEdge = pos; //APCFALZ
  
        // There is no outgoing edge starting with
        // activeEdge from activeNode
        if (activeNode->children[text[activeEdge]] == NULL)
        {
            //Extension Rule 2 (A new leaf edge gets created)
            activeNode->children[text[activeEdge]] = newNode(pos, &leafEnd);
  
            /*A new leaf edge is created in above line starting
             from  an existng node (the current activeNode), and
             if there is any internal node waiting for it's suffix
             link get reset, point the suffix link from that last
             internal node to current activeNode. Then set lastNewNode
             to NULL indicating no more node waiting for suffix link
             reset.*/
            if (lastNewNode != NULL)
            {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = NULL;
            }
        }
        // There is an outgoing edge starting with activeEdge
        // from activeNode
        else
        {
            // Get the next node at the end of edge starting
            // with activeEdge
            Node* next = activeNode->children[text[activeEdge]];
            if (walkDown(next))//Do walkdown
            {
                //Start from next node (the new activeNode)
                continue;
            }
            /*Extension Rule 3 (current character being processed
              is already on the edge)*/
            if (text[next->start + activeLength] == text[pos])
            {
                //If a newly created node waiting for it's 
                //suffix link to be set, then set suffix link 
                //of that waiting node to curent active node
                if(lastNewNode != NULL && activeNode != root)
                {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = NULL;
                }
 
                //APCFER3
                activeLength++;
                /*STOP all further processing in this phase
                and move on to next phase*/
                break;
            }
  
            /*We will be here when activePoint is in middle of
              the edge being traversed and current character
              being processed is not  on the edge (we fall off
              the tree). In this case, we add a new internal node
              and a new leaf edge going out of that new node. This
              is Extension Rule 2, where a new leaf edge and a new
            internal node get created*/
            splitEnd = (int*) malloc(sizeof(int));
            *splitEnd = next->start + activeLength - 1;
  
            //New internal node
            Node* split = newNode(next->start, splitEnd);
            activeNode->children[text[activeEdge]] = split;
  
            //New leaf coming out of new internal node
            split->children[text[pos]] = newNode(pos, &leafEnd);
            next->start += activeLength;
            split->children[text[next->start]] = next;
  
            /*We got a new internal node here. If there is any
              internal node created in last extensions of same
              phase which is still waiting for it's suffix link
              reset, do it now.*/
            if (lastNewNode != NULL)
            {
            /*suffixLink of lastNewNode points to current newly
              created internal node*/
                lastNewNode->suffixLink = split;
            }
  
            /*Make the current newly created internal node waiting
              for it's suffix link reset (which is pointing to root
              at present). If we come across any other internal node
              (existing or newly created) in next extension of same
              phase, when a new leaf edge gets added (i.e. when
              Extension Rule 2 applies is any of the next extension
              of same phase) at that point, suffixLink of this node
              will point to that internal node.*/
            lastNewNode = split;
        }
  
        /* One suffix got added in tree, decrement the count of
          suffixes yet to be added.*/
        remainingSuffixCount--;
        if (activeNode == root && activeLength > 0) //APCFER2C1
        {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        }
        else if (activeNode != root) //APCFER2C2
        {
            activeNode = activeNode->suffixLink;
        }
    }
}

void print(int i, int j) {
    int k;
    for (k=i; k<=j && text[k] != '#'; k++)
        printf("%c", text[k]);
    if(k<=j)
        printf("#");
}

void setSuffixIndexByDFS(Node* n, int labelHeight) {
    if (n == NULL)  return;
  
    if (n->start != -1) //A non-root node
    {
        //Print the label on edge from parent to current node
        //Uncomment below line to print suffix tree
        //print(n->start, *(n->end));
    }
    int leaf = 1;
    int i;
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (n->children[i] != NULL)
        {
            //Uncomment below two lines to print suffix index
         //   if (leaf == 1 && n->start != -1)
           //     printf(" [%d]\n", n->suffixIndex);
  
            //Current node is not a leaf as it has outgoing
            //edges from it.
            leaf = 0;
            setSuffixIndexByDFS(n->children[i], labelHeight + edgeLength(n->children[i]));
        }
    }
    if (leaf == 1)
    {
        for(i= n->start; i<= *(n->end); i++)
        {
            if(text[i] == '#')
            {
                n->end = (int*) malloc(sizeof(int));
                *(n->end) = i;
            }
        }
        n->suffixIndex = size - labelHeight;
        //Uncomment below line to print suffix index
       // printf(" [%d]\n", n->suffixIndex);
    }
}
  
void freeSuffixTreeByPostOrder(Node* n) {
    if (n == NULL)
        return;
    int i;
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (n->children[i] != NULL)
        {
            freeSuffixTreeByPostOrder(n->children[i]);
        }
    }
    if (n->suffixIndex == -1)
        free(n->end);
    free(n);
}
  
/*Build the suffix tree and print the edge labels along with
suffixIndex. suffixIndex for leaf edges will be >= 0 and
for non-leaf edges will be -1*/
void buildSuffixTree() {
    size = strlen(text);
    int i;
    rootEnd = new int;
    *rootEnd = - 1;
  
    /*Root is a special node with start and end indices as -1,
    as it has no parent from where an edge comes to root*/
    root = newNode(-1, rootEnd);
  
    activeNode = root; //First activeNode will be root
    for (i=0; i<size; i++)
        extendSuffixTree(i);
    int labelHeight = 0;
    setSuffixIndexByDFS(root, labelHeight);
}
 
int doTraversal(Node *n, int labelHeight, int* maxHeight, int* substringStartIndex) {
    if(n == NULL)
    {
        return 0;
    }
    int i=0;
    int ret = -1;
    if(n->suffixIndex < 0) //If it is internal node
    {
        for (i = 0; i < MAX_CHAR; i++)
        {
            if(n->children[i] != NULL)
            {
                ret = doTraversal(n->children[i], labelHeight + 
                    edgeLength(n->children[i]), 
                    maxHeight, substringStartIndex);
                 
                if(n->suffixIndex == -1)
                    n->suffixIndex = ret;
                else if((n->suffixIndex == -2 && ret == -3) ||
                    (n->suffixIndex == -3 && ret == -2) || 
                    n->suffixIndex == -4)
                {
                    n->suffixIndex = -4;//Mark node as XY
                    //Keep track of deepest node
                    if(*maxHeight < labelHeight)
                    {
                        *maxHeight = labelHeight;
                        *substringStartIndex = *(n->end) - 
                            labelHeight + 1;
                    }
                }
            }
        }
    }
    else if(n->suffixIndex > -1 && n->suffixIndex < size1)//suffix of X
        return -2;//Mark node as X
    else if(n->suffixIndex >= size1)//suffix of Y
        return -3;//Mark node as Y
    return n->suffixIndex;
}
 
void getLongestCommonSubstring()
{
    int maxHeight = 0;
    int substringStartIndex = 0;
    doTraversal(root, 0, &maxHeight, &substringStartIndex);
     
    int k;
    for (k=0; k<maxHeight; k++)
        printf("%c", text[k + substringStartIndex]);
    if(k == 0)
        printf("No common substring");
    else
        printf(", of length: %d",maxHeight);
    printf("\n");
}

int get_file_size(char* file_name) {
	std::streampos begin, end;
	std::ifstream myfile(file_name, std::ios::binary);
	myfile.seekg (0, std::ios::end);
	end = myfile.tellg();
	myfile.close();
	return end - begin;
}

int main(int argc, char *argv[])
{
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

	text = new char[f1_size + f2_size + 2];
	strcpy(text, s1);
	strcat(text, "#");
	strcat(text, s2);
	strcat(text, "$");
	buildSuffixTree();
	getLongestCommonSubstring();
	freeSuffixTreeByPostOrder(root);

	/*size1 = 7;
    printf("Longest Common Substring in xabxac and abcabxabcd is: ");
    strcpy(text, "xabxac#abcabxabcd$"); buildSuffixTree();
    getLongestCommonSubstring();
    //Free the dynamically allocated memory
    freeSuffixTreeByPostOrder(root);
 
    size1 = 10;
    printf("Longest Common Substring in xabxaabxa and babxba is: ");
    strcpy(text, "xabxaabxa#babxba$"); buildSuffixTree();
    getLongestCommonSubstring();
    //Free the dynamically allocated memory
    freeSuffixTreeByPostOrder(root);
 
    size1 = 14;
    printf("Longest Common Substring in GeeksforGeeks and GeeksQuiz is: ");
    strcpy(text, "GeeksforGeeks#GeeksQuiz$"); buildSuffixTree();
    getLongestCommonSubstring();
    //Free the dynamically allocated memory
    freeSuffixTreeByPostOrder(root);
 
    size1 = 26;
    printf("Longest Common Substring in OldSite:GeeksforGeeks.org");
    printf(" and NewSite:GeeksQuiz.com is: ");
    strcpy(text, "OldSite:GeeksforGeeks.org#NewSite:GeeksQuiz.com$");
    buildSuffixTree();
    getLongestCommonSubstring();
    //Free the dynamically allocated memory
    freeSuffixTreeByPostOrder(root);
 
    size1 = 6;
    printf("Longest Common Substring in abcde and fghie is: ");
    strcpy(text, "abcde#fghie$"); buildSuffixTree();
    getLongestCommonSubstring();
    //Free the dynamically allocated memory
    freeSuffixTreeByPostOrder(root);
 
    size1 = 6;
    printf("Longest Common Substring in pqrst and uvwxyz is: ");
    strcpy(text, "pqrst#uvwxyz$"); buildSuffixTree();
    getLongestCommonSubstring();
    //Free the dynamically allocated memory
    freeSuffixTreeByPostOrder(root);*/
	return 0;
}