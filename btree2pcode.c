#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INSTRUCTIONS 50 // Define your own

typedef struct{
    int operation;
    int level;
    int argument;
} Tinstruction;

int stack[1024] = {-1};		// Vector with only integers, used as a datastore

// List of available instructions
enum { LIT, OPR, LOD, STO, CAL, INT, JMP, JPC, WRT } instructionCode;
char * instructionString[] = { "LIT", "OPR", "LOD", "STO", "CAL", "INT", "JMP", "JPC", "WRT" };

// List of available arithmetic operations
enum { RTN, NEG, ADD, SUB, MUL, DIV, ODD, MOD, EQL, NEQ, LSS, LEQ, GTR, GEQ } operationCode;
char * operationString[] = { "RTN", "NEG", "ADD", "SUB", "MUL", "DIV", "MOD", "ODD", "EQL", "NEQ", "LSS", "LEQ", "GTR", "GEQ"};

// Prototypes
int getBase(int level, int base);
int getInstructionCode(char *c);
char * getInstructionName(int inst);
void pcode(Tinstruction inst[]);
char * postOrder(char * array[]);
char * setLeft(int father, char * array);
char * setRight(int father, char * array);
Tinstruction * toInstruction(char *epr);

int main (int argc, char **argv){
    
    char a[50] = {""};          // Reverse polish notation
    
    printf("Please enter the btree:");
    
    // Array of instructions
    Tinstruction * instructions = toInstruction(a);

    printf("\nStarting the P-code Machine.\n");
    printf("%-10s %-15s %-15s %-15s %-15s %s\n","Inst","Level","Arg","Top","Counter","Stack");
    pcode(instructions);
}

Tinstruction * toInstruction(char *epr){
	int i;
	int aux = 0; // Array position
	int totalInstructions = 1;
	static Tinstruction instructions[MAX_INSTRUCTIONS];
	
	// Solution from dasblinkenlight - Stackoverflow
	// Catch numbers from string
	char *p = epr;
	
	// Reserve space
	Tinstruction intInst;
	intInst.operation = 5;
	intInst.level = 0;
	intInst.argument = strlen(p);
	instructions[0] = intInst;
	
	while (*p) { // While there are more characters to process...
	    if (isdigit(*p)) { // Upon finding a digit, ...
	        int val = (int)strtol(p, &p, 10); // Read a number, ...
	        Tinstruction instruction;
	        instruction.operation = 0;
	        instruction.level = 0;
	        instruction.argument = val;
	        
	        Tinstruction instruction2;
	        instruction2.operation = 3;
	        instruction2.level = 0;
	        instruction2.argument = aux;
	        
	        // Store instructions
	        instructions[totalInstructions] = instruction;
	        instructions[totalInstructions+1] = instruction2;
	        totalInstructions += 2;
	        
	        // Points next array position
	        aux++;
	    }else { // Otherwise, move on to the next character.
	        switch(*p){
	        	case '+':{
	        		Tinstruction plusLod;
	        		plusLod.operation = 2;
	        		plusLod.level = 0;
	        		plusLod.argument = aux - 1;
	        		
	        		Tinstruction plusLod2;
	        		plusLod2.operation = 2;
	        		plusLod2.level = 0;
	        		plusLod2.argument = aux - 2;
	        		
	        		Tinstruction plusOpr;
	        		plusOpr.operation = 1;
	        		plusOpr.level = 0;
	        		plusOpr.argument = 2;
	        		
	        		Tinstruction plusSto;
	        		plusSto.operation = 3;
	        		plusSto.level = 0;
	        		plusSto.argument = aux;
	        		
	        		instructions[totalInstructions] = plusLod;
	        		instructions[totalInstructions+1] = plusLod2;
	        		instructions[totalInstructions+2] = plusOpr;
	        		instructions[totalInstructions+3] = plusSto;
	        		
	        		totalInstructions += 4;
	        		aux++;
	        		break;
	        	}
	        	case '-':{
	        		Tinstruction subLod;
	        		subLod.operation = 2;
	        		subLod.level = 0;
	        		subLod.argument = aux - 1;
	        		
	        		Tinstruction subLod2;
	        		subLod2.operation = 2;
	        		subLod2.level = 0;
	        		subLod2.argument = aux - 2;
	        		
	        		Tinstruction subOpr;
	        		subOpr.operation = 1;
	        		subOpr.level = 0;
	        		subOpr.argument = 3;
	        		
	        		Tinstruction subSto;
	        		subSto.operation = 3;
	        		subSto.level = 0;
	        		subSto.argument = aux;
	        		
	        		instructions[totalInstructions] = subLod;
	        		instructions[totalInstructions+1] = subLod2;
	        		instructions[totalInstructions+2] = subOpr;
	        		instructions[totalInstructions+3] = subSto;
	        		
	        		totalInstructions += 4;
	        		aux++;
	        		break;
	        	}
	        	case '*':{
	        		Tinstruction multLod;
	        		multLod.operation = 2;
	        		multLod.level = 0;
	        		multLod.argument = aux - 1;
	        		
	        		Tinstruction multLod2;
	        		multLod2.operation = 2;
	        		multLod2.level = 0;
	        		multLod2.argument = aux - 2;
	        		
	        		Tinstruction multOpr;
	        		multOpr.operation = 1;
	        		multOpr.level = 0;
	        		multOpr.argument = 4;
	        		
	        		Tinstruction multSto;
	        		multSto.operation = 3;
	        		multSto.level = 0;
	        		multSto.argument = aux;
	        		
	        		instructions[totalInstructions] = multLod;
	        		instructions[totalInstructions+1] = multLod2;
	        		instructions[totalInstructions+2] = multOpr;
	        		instructions[totalInstructions+3] = multSto;
	        		
	        		totalInstructions += 4;
	        		aux++;
	        		break;
	        	}
	        	case '/':{
	        		Tinstruction divLod;
	        		divLod.operation = 2;
	        		divLod.level = 0;
	        		divLod.argument = aux - 1;
	        		
	        		Tinstruction divLod2;
	        		divLod2.operation = 2;
	        		divLod2.level = 0;
	        		divLod2.argument = aux - 2;
	        		
	        		Tinstruction divOpr;
	        		divOpr.operation = 1;
	        		divOpr.level = 0;
	        		divOpr.argument = 5;
	        		
	        		Tinstruction divSto;
	        		divSto.operation = 3;
	        		divSto.level = 0;
	        		divSto.argument = aux;
	        		
	        		instructions[totalInstructions] = divLod;
	        		instructions[totalInstructions+1] = divLod2;
	        		instructions[totalInstructions+2] = divOpr;
	        		instructions[totalInstructions+3] = divSto;
	        		
	        		totalInstructions += 4;
	        		aux++;
	        		break;
	        	}
	        	case '~':{
	        		Tinstruction neqLod;
	        		neqLod.operation = 2;
	        		neqLod.level = 0;
	        		neqLod.argument = aux-1;
	        		
	        		Tinstruction neqOpr;
	        		neqOpr.operation = 1;
	        		neqOpr.level = 0;
	        		neqOpr.argument = 1;
	        		
	        		Tinstruction neqSto;
	        		neqSto.operation = 3;
	        		neqSto.level = 0;
	        		neqSto.argument = aux-1;
	        		
	        		instructions[totalInstructions] = neqLod;
	        		instructions[totalInstructions+1] = neqOpr;
	        		instructions[totalInstructions+2] = neqSto;
	        		
	        		totalInstructions += 3;
	        		break;
	        	}
	        }
	        p++;
	    }
	}
	
	// Last Instruction
	Tinstruction rtn;
	rtn.operation = 1;
	rtn.level = 0;
	rtn.argument = 0;
	
	instructions[totalInstructions] = rtn;
	
	return instructions;
}

void pcode(Tinstruction inst[]){
	int base = 1;				// Points to the base address in the stack for the current invocation of a given procedure
    int top = 0; 				// Points to the current top of the stack
    int counter = 0;  			// Points to an instruction in the program area
	
	int aux;
	int stop = 0;
	
	do{
    	Tinstruction instruction = inst[counter];
    	counter++;
    	switch (instruction.operation){
    		case LIT:
    			top++;
    			stack[top] = instruction.argument;
    			break;
    		case OPR:
    			switch(instruction.argument){
    				case RTN:
    					top = base - 1;
    					counter = stack[top+3];
    					base = stack[top+2];
    					break;
    				case NEG:
    					stack[top]= -1*stack[top];
    					break;
    				case ADD:
    					top--;
    					stack[top] += stack[top+1];
    					break;
    				case SUB:
    					top--;
    					stack[top] -= stack[top+1];
    					break;
    				case MUL:
    					top--;
    					stack[top] *= stack[top+1];
    					break;
    				case DIV:
    					top--;
    					stack[top] /= stack[top+1];
    					break;
    				case MOD:
    					top--;
    					stack[top] %= stack[top+1]; 
    					break;
    				case ODD:
    					stack[top] = (stack[top]%2 == 1);
    					break;
    				case EQL:
    					top--;
    					stack[top] = (stack[top] == stack[top+1]);
    					break;
    				case NEQ:
    					top--;
    					stack[top] = (stack[top] != stack[top+1]);
    					break;
    				case LSS:
    					top--;
    					stack[top] = (stack[top] < stack[top+1]);
    					break;
    				case LEQ:
    					top--;
    					stack[top] = (stack[top] <= stack[top+1]);
    					break;
    				case GTR:
    					top--;
    					stack[top] = (stack[top] > stack[top+1]);
    					break;
    				case GEQ:
    					top--;
    					stack[top] = (stack[top] >= stack[top+1]);
    					break;
    				default:
    					printf("Unknown OPR subfunction");
    					break;
    				}
    			break;
    		case LOD:
    			top++;
    			stack[top] = stack[ getBase(instruction.level, base) + instruction.argument ];
    			break;
    		case STO:
    			stack[ getBase(instruction.level, base) + instruction.argument ] = stack[top];
    			top--;
    			break;
    		case CAL:
    			stack[top+1] = getBase(instruction.level, base);
    			stack[top+2] = base;
    			stack[top+3] = counter;
    			base = top+1;
    			counter = instruction.argument;
    			break;
    		case INT:
    			top += instruction.argument;
    			break;
    		case JMP:
    			counter = instruction.argument-1;
    			break;
    		case JPC:
    			if (stack[top] == 0){
    				counter = instruction.argument-1;
    			}
    			top--;	
    			break;
    		default:
    			printf("Unknown function");
    	}
    		
    	// PrintStackTrace
    	printf("%-10s %-15d %-15d %-15d %-15d ", getInstructionName(instruction.operation),instruction.level, instruction.argument, stack[top], counter);
    
    	for (aux = base; aux<top+1;aux++){
    		printf("%d ", stack[aux]);
    	}
    	printf("\n");
    	
    	// If RTN, stop
    	stop = (instruction.operation == 1 && instruction.argument == 0);
	}while(stop == 0);
}

int getBase(int level, int base){
    int newBase;
	newBase = base;
	while (level>0){
		newBase = stack[newBase];
		level--;
	}
	return newBase;
}

int getIntructionCode(char *c){
	int i;
	for (i = 0; i<9;i++){
		if(strcmp(c, instructionString[i]) == 0){
			return i;
		}
	}
	return -1;
}

char * getInstructionName(int inst){
	return instructionString[inst];
}

char * postOrder(char * array[]){
    printf("%s %s %s",array[0], array[1], array[2]);
}

char * setLeft(int father, char * array){
    
}

char * setRight(int father, char * array){
    
}
