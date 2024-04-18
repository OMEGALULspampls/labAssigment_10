#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 30

// Trie structure
struct Trie
{	
    int count;
    struct Trie* children[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* new_trie = malloc(sizeof(struct Trie));
    if(new_trie == NULL){ // check for error
        printf("Allocation Error\n");
        exit(-1);
    }
    new_trie->count = 0; // set flag to 0
    for(int i=0; i<26; i++){
        new_trie->children[i] = NULL; // set children to NULL
    }
    return new_trie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int len = strlen(word);
    struct Trie* temp = pTrie;
    for(int i=0; i<len; i++){
        if(temp->children[word[i]-'a'] == NULL){
            temp->children[word[i]-'a'] = createTrie();  
        }
        temp = temp->children[word[i]-'a'];
    }
    temp->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int len = strlen(word);
    struct Trie* temp = pTrie;
    for(int i=0; i<len; i++){
        if(temp->children[word[i]-'a']==NULL){
            return 0;
        }
        temp = temp->children[word[i]-'a'];
    }
    return temp->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for(int i=0; i<26; i++){
        if(pTrie->children[i]!=NULL){
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
}


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    int n;
    FILE* input = fopen(filename, "r");
    fscanf(input, "%d", &n);
    for(int i=0; i<n; i++){
        pInWords[i] = malloc(sizeof(char)*MAX_STR);
        fscanf(input, "%s", pInWords[i]);
    }
    fclose(input);
    return n;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}