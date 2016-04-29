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
    
    FILE *input;
    
    if (argc == 3){
    	// Open file
    	string fileName = argv[1];
    	input = fopen(fileName,"r");
    	
    	// Reserve memory
    	treeSize = atoi(argv[2]);
    	btree = (string*) malloc(treeSize * sizeof(string));
    	
    	if(input != NULL){
    		
    		FILE *output = fopen("output.txt", "w");
	    	if(output!=NULL){
	    		
	    		int i = 0;
	    		char buffer[200] = {""};
	    		string expr = NULL;
	    		string token = NULL;
	    		
	    		expr = (string) malloc(100*sizeof(string));
	
	    		// Get input
	    		fgets(buffer, sizeof(buffer), input);
				fprintf(output,"Running: %s %s %s\n", argv[0],argv[1],argv[2]);
		    	fprintf(output,"Input: %s\n", buffer);
		    	
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
		    	
		    	// B-tree -> Reverse Polish Notation
		    	postOrder(btree,treeSize, 0, expr);
		    	
		    	fprintf(output,"Reverse polish notation: %s\n", expr);
	
		    	// Array of instructions
			    Tinstruction * instructions = toInstruction(expr, treeSize);
			    fprintf(output,"\nOutput:\n");
			    fprintf(output,"%-10s %-15s %-15s %-15s %-15s %-15s %s\n","Inst","Level","Arg","Top","Counter","Base","Stack");
			    pcode(instructions, stack, output);

	    		// Free memory
			    for(i = 0; i<treeSize; i++){
		    		free(btree[i]);
		    	}
		    	free(btree);
		    	free(expr);
		    	
		    	// Closing Files
		    	fclose(input);
	    		fclose(output);
	    		
	    	}else{
	    		printf("Error when opening the output file.");
	    		fclose(input);
	    	}
    	}else{
	    	printf("Error when opening the input file.");
	    }
    }else{
    	printf("Insuficient params");
    }
    return 0;
}
