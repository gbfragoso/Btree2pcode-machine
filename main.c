#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "pcode.h"
#include "rpn2pci.h"
#include "btree2rpn.h"

typedef char * string;

/*
	This program aim to convert a binary tree into pcode instructions. The convert process is compound of 3 steps
	Btree -> RPN -> PCI. 
	
	Author: Gustavo B. Fragoso
*/
int main (int argc, char **argv){
	
	int stack[1024] = {-1};		// Vector with only integers, used as a datastore
    int treeSize = 0;			// Number of values at input file
    string *btree;				// Dynamic allocated Binary Tree (Array of char*)
    
    FILE *file;
    
    if (argc == 3){
    	// Open file
    	string fileName = argv[1];
    	file = fopen(fileName,"r");
    	
    	// Reserve memory
    	treeSize = atoi(argv[2]);
    	btree = (string*) malloc(treeSize * sizeof(string));
    	
    	if(file != NULL){
    		int i = 0;
    		char buffer[200];
    		char expr[100]={""};
    		string token = NULL;
    		
    		printf("%s open ... Reading data\n", fileName);
    		
    		// Get input
    		fgets(buffer, sizeof(buffer), file);

    		// Tokenizing
    		token = strtok(buffer,",");
    		btree[0] = malloc (sizeof(token)+1);
    		strcpy(btree[0],token);
    		
    		while(token != NULL){
    			token = strtok(NULL,",");
    			if(token != NULL){
    				i++;
    				btree[i] = malloc (sizeof(token)+1);
    				strcpy(btree[i],token);	
    			}
    		}
    		
	    	fclose(file);
	    	printf("\nTranslating to reverse polish notation ...\n");
	    	
	    	// B-tree -> Reverse Polish Notation
	    	postOrder(btree,treeSize, 0, expr);
	    	
	    	printf("Reverse polish notation: %s\n", expr);
	    	
	    	for(i = 0; i<treeSize; i++){
	    		free(btree[i]);
	    	}
	    	free(btree);

	    	// Array of instructions
		    Tinstruction * instructions = toInstruction(expr, treeSize);
		    printf("\nStarting the P-code Machine.\n");
		    printf("%-10s %-15s %-15s %-15s %-15s %s\n","Inst","Level","Arg","Top","Counter","Stack");
		    pcode(instructions, stack);
    	}
    }
    return 0;
}
