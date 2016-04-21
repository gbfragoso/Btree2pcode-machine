#include "btree2rpn.h"
#include <string.h>

char* postOrder(char** btree, int treeSize, int node, char* expr){
    if(node >= treeSize || strcmp(btree[node], "0") == 0){
    	return NULL;
    }else{
    	postOrder(btree, treeSize, 2*node+1, expr);
    	postOrder(btree, treeSize, 2*node+2, expr);
    	strcat(expr,btree[node]);
    	strcat(expr, " ");
    }
}
