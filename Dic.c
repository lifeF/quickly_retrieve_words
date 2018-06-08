/*
Rathnayake R.M.K.D 
University of Peradeniya 

Radix Tree (Trie) Structure for Text Auto-complete

INTRUDUCTION :

 Radix Trees or Tries are data structures that provide fast data retrieval,
 at the cost of high space consumption. Typically, data values are associated 
 with edges rather than with nodes in Tries, although this may depend on implementation. 
 In this lab you will be implementing a Trie data structure in C to store a dictionary of 
 English words, and use it to quickly retrieve words for an text auto-complete application.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct trienode TrieNode;
TrieNode* createNode(char character);
TrieNode *root ;
char *sample_word;
void Preorder(TrieNode * root_Nodes, TrieNode *Start_Node);
//test Function
void test_CreateNode();
// end test function 

// Node struct  start-----
typedef struct trienode{
    // for store charactor 
    char data ;
    //  point to parent node
    TrieNode * parent ;
    // to point child node array
    TrieNode * child[26];
    int isLeaf;
    // to hold number of child
    int length;
}TrieNode;// node stract end ------


//Create function start-----
TrieNode* createNode(char character){
    //create new node 
    TrieNode* NewNode = (TrieNode*)malloc(sizeof(TrieNode));
    NewNode->data = character;
    NewNode->length=0;
    NewNode->isLeaf= 1;
    for(int i=0;i<26;i++){
        NewNode->child[i]=NULL;
    }
    
    return NewNode;
}//create function end----

//Insert function Start----
void insertWord(char * word){
    TrieNode * tmp_root = root;
    TrieNode **tmp_child = root->child;
    
    while (*word != '\0'){ // check end charactor
        int index =(int)tolower(*word)- (int)'a';
        if(tmp_child[index] == NULL){
           // printf("add %c\n", *word);
           tmp_child[index]=createNode(*word);
           tmp_root->isLeaf=0;
           tmp_child[index]->parent=tmp_root;
           tmp_root=tmp_child[index];
           tmp_child= tmp_root->child;
           word ++;
        }
        else{
           // printf("Have same  %c\n", *word);
            tmp_root = tmp_child[index];
            tmp_child = tmp_root->child;
            word++;
        }
       
    }
}// End Insert function-----

//print Suggestion 
void printSuggestions( char * word  ){
    sample_word = word;
    TrieNode *tmp_root = root;
    TrieNode **tmp_child = root->child;
    int state=0;
    while (*word != '\0')
    { // check end charactor
        int index = (int)tolower(*word) - (int)'a';
        if (tmp_child[index] == NULL){
            printf("have No suggestions\n");
            break;
        }
        tmp_root = tmp_child[index];
        tmp_child = tmp_root->child;
        word++;
            
        if (*word == '\0'){
            printf("Suggession for Your input  \'%s\'\n",sample_word);
            FindLeaf(tmp_root, tmp_root);
        }   
    }
    
}//end print Suggesion 
void printWord( TrieNode *Start_Node, TrieNode *Leaf_Node)
{
    char word[50]="";
    int i=0;
    TrieNode * tmp_node = Leaf_Node;
    while (tmp_node != Start_Node){
        word[i] = tmp_node->data;
        tmp_node = tmp_node->parent;
        i++;
    }

    for(int j = --i; j>=0;j--){
        printf("%c", word[j]);
    }
}

void FindLeaf(TrieNode * Nodes,TrieNode *  Start_Node){
    
    TrieNode **t_child = Nodes->child;
    for(int i=0 ; i<26 ;i++){
        if (t_child[i]!=NULL)
            FindLeaf(t_child[i], Start_Node);
    }
    if(Nodes->isLeaf==1){
        printf(" >  %s",sample_word);
        printWord(Start_Node, Nodes);
        printf("\n");
    }
    
}

int main(int argc, char const *argv[])
{
//     //create root of tree 
   root = createNode('r');
    //read  file 
           char word[51];
           FILE *file;
           file = fopen("Sample Word List.txt", "r");
           if (file) {
               while (fscanf(file, " %50s", word) == 1){
                   insertWord(word);
               }
                fclose(file);
            }
            else{
                fprintf(stderr,"file connot read , or \" Sample Word List.txt\" file not exit ");
                return 0;
            }
    //read file end
    if(argc>1){
        char *word = argv[1];
        printSuggestions(word);
    } 
    else{
        fprintf(stderr, "Please input word \n \t Usage :  %s  <Your Word > \n ", argv[0]);
    }
        
    return 0;
}

// test function for test each function used in the source code 

void test_CreateNode(){
    TrieNode* NewNode = createNode('k');
    TrieNode* temp_child = createNode('t');
    char c = NewNode->data;
    // temp_child =NewNode->child;
    // char tmp_data = temp_child->data;
    char k = 'k';
    if(c==k)
        printf("%c",c);
}

// end test function;

