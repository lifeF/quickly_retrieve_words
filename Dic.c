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
void Preorder(TrieNode *Nodes);

    //tree Root create

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
    TrieNode* child[26];
    
    // to hold number of child
    int length;
}TrieNode;// node stract end ------


//Create function start-----
TrieNode* createNode(char character){
    //create new node 
    TrieNode* NewNode = (TrieNode*)malloc(sizeof(TrieNode));
    NewNode->data = character;
    NewNode->length=0;
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

//print Sugession 
void printSuggestions( char * word  ){
    char * word_sample = word;
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
            for (int i = 0; i < 26; i++)
            {
                if (tmp_child[i] != NULL){
                    printf("%s", word_sample);
                    Preorder(tmp_root);
                    printf("\n");
        
                }
            }      
            
            
        }   
    }
    
}
//end print sugession 

void Preorder(TrieNode * Nodes){
    printf("%c",Nodes->data);
    TrieNode **t_child = Nodes->child;
    for(int i=0 ; i<26 ;i++){
        if (t_child[i]!=NULL)
            Preorder(t_child[i]);
           
    }
}

int main(int argc, char const *argv[])
{
    //create root of tree 
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
            }
    //read file end
    
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

