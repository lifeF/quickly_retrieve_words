/*
Rathnayake R.M.K.D 
University of Peradeniya 
E 14 287

Trie Tree  Structure for Text Auto-complete

INTRUDUCTION :

 Tries are data structures that provide fast data retrieval,
 at the cost of high space consumption. Typically, data values are associated 
 with edges rather than with nodes in Tries, although this may depend on implementation. 
 In this lab you will be implementing a Trie data structure in C to store a dictionary of 
 English words, and use it to quickly retrieve words for an text auto-complete application.
*/

// include library
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct trienode TrieNode;
TrieNode* createNode(char * character);
TrieNode *root ;
char *sample_word;
void FindLeaf(TrieNode * root_Nodes, TrieNode *Start_Node);
int find(char *first_word, char *second_word);

    // Node struct  start-----
    typedef struct trienode
{
    // for store charactor 
    char * data ;
    //  point to parent node
    TrieNode * parent ;
    // to point child node array
    TrieNode * child[26];
    int isLeaf;
    // to hold number of child
    int length;
}TrieNode;// node stract end ------

//Create function start-----
TrieNode* createNode(char * word){
    //create new node 
    TrieNode* NewNode = (TrieNode*)malloc(sizeof(TrieNode));
    char * new_word = malloc(sizeof(char)*(strlen(word)+1));
    NewNode->data = strcpy(new_word, word);
    NewNode->length = 0;
    NewNode->isLeaf= 1;
    for(int i=0;i<26;i++){
        NewNode->child[i]=NULL;
    }
    return NewNode;
}//create function end----

//Insert function Start----
void insertWord(char * word,TrieNode * insert_node){
    TrieNode * tmp_root = insert_node;
    TrieNode **tmp_child = insert_node->child;
    // while (*word != '\0'){ 
        int index =(int)tolower(*word)- (int)'a';
        if(tmp_child[index] == NULL){
            tmp_child[index] = createNode(word);
            printf("%p add %s\n", tmp_child[index], word);
            tmp_root->isLeaf = 0;
            tmp_child[index]->parent = tmp_root;

            // break;
        }
        else{
            printf("to sparate %s\n", word);
            // take data  
            char * store_word = tmp_child[index]->data;
            //choice what is the larage one  
            char * long_word = strlen(store_word)>=strlen(word)? store_word: word;
            char *short_word = strlen(store_word) >= strlen(word) ? word : store_word;
            //find break point 
            int break_index = find(long_word,short_word);
            printf("%d  \n", break_index);
            // allocate memory for word part 
            char * word_1= malloc(sizeof(char)*break_index);
            char *word_2 = malloc(sizeof(char) * (strlen(long_word) - break_index));
            char *word_3=NULL;
            //copy word part
            memcpy(word_1, word, break_index);
            char *word_to_child = malloc(sizeof(char) * break_index);
            //set new value to the data 
            tmp_child[index]->data = strcpy(word_to_child,word_1);
            memcpy(word_2, &long_word[break_index], strlen(long_word) - break_index);
            insertWord(word_2, tmp_child[index]);

            // if break_index smaller then short word
            if(break_index<strlen(short_word)){
                word_3 = malloc(sizeof(char) * (strlen(short_word) - break_index));
                memcpy(word_3, &short_word[break_index], strlen(short_word) - break_index);
                insertWord(word_3,tmp_child[index]);
            }
            
        //     break;
        // }
       
    }
}// End Insert function-----
int find(char * Long_word,char * short_word){
    int index;
    for(index=0;index<strlen(short_word);index++){
        if(tolower(Long_word[index])!=tolower(short_word[index]))
            break;
    }
    return index;
}


//  main fuction ----------------------------------------------------
int main(int argc, char *argv[])
{
    root = createNode("root");
    
    // char * word = "kalana";
    // 
   
    // insertWord("year",root);
    // insertWord("yard", root);
    // insertWord("yesterday", root);

    //create root of tree 
   
    //read  file  and add word to the tree 
           char word[51];
           FILE *file;
           file = fopen("Sample Word List.txt", "r");
           if (file) {
               while (fscanf(file, " %50s", word) == 1){
                   insertWord(word,root);
               }
                fclose(file);
            }
            else{
                fprintf(stderr,"file connot read , or \" Sample Word List.txt\" file not exit ");
                return 0;
            }
    //read file end
    // if(argc>1){
    //     char *word = argv[1];
    //     printSuggestions(word);
    // } 
    // else{
    //     fprintf(stderr, "Please input word \n \t Usage :  %s  <Your Word > \n ", argv[0]);
    // }
    
    return 0;
}
// end main function --------------------------------------------------

