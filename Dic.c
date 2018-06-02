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

typedef struct trienode TrieNode;
TrieNode* createNode(char character);
 TrieNode* root;
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
    TrieNode * child  ;
    // to hold number of child
    int length;
}TrieNode;// node stract end ------


//Create function start-----
TrieNode* createNode(char character){
    //create new node 
    TrieNode* NewNode = (TrieNode*)malloc(sizeof(TrieNode));
    NewNode->data = character;
    NewNode->length=0;
    NewNode->parent=NULL;
    NewNode->child=NULL;
    return NewNode;
}//create function end----

//Insert function Start----
void insertWord(char word []){
    int i =0;
    char temp_character=word[i];
    TrieNode* temp_root= root;
    TrieNode* temp_child = root->child ;
    while(word[i]!='\0'){
        while(temp_child!=NULL){
           char node_char=temp_child->data;
           if(temp_character==node_char){
               printf("have same -> %c \n " ,word[i]);
               i++;
               temp_character=word[i];
               if(temp_character=='\0')
                    break;
               temp_root=temp_child;
               temp_child=temp_child->child;
               continue;
           }
            else{
                temp_child++;
            }    
           

        }
        if(temp_child==NULL){
            temp_child=temp_root->child; 
            int length = temp_root->length;
            TrieNode* child_List_point = (TrieNode*)malloc(sizeof(TrieNode)*(length+1));
            TrieNode* child_List=child_List_point;
            for(int k=0; k<length;k++){
                child_List->data = temp_child->data;
                child_List->length=(temp_child->length)+1;
                child_List->parent=temp_root;
                child_List->child=temp_child->child;

                child_List++;
                temp_child++;
            }
            printf("add -> %c \n " ,word[i]);
            child_List= createNode(word[i]);
            child_List->parent=temp_root;
            temp_root->child=child_List_point;
            temp_root=child_List;
            temp_child= temp_root->child;
            
            i++;
        }
            
        
            
    }   

}// End Insert function----


int main(int argc, char const *argv[])
{
    //create root of tree 
   root = createNode('r');
    //test_CreateNode();
    insertWord("kalana");
    insertWord("kalaba");
    //read  file 
        //    int c;
        //    FILE *file;
        //    file = fopen("Sample Word List.txt", "r");
        //    if (file) {
        //         while ((c = getc(file)) != EOF)
        //             putchar(c);
        //         fclose(file);
        //     }
        //     else{
        //         fprintf(stderr,"file connot read , or \" Sample Word List.txt\" file not exit ");
        //     }
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

