#include "a6.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

Node* newNodePoint(NodeType type, int num, int x, int y) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data.pointData.width = x;
    node->data.pointData.height = y;
    node->data.pointData.number = num;
    node->data.pointData.x = 0; 
    node->data.pointData.y = 0; 
    node->type = point;
    node->left = node->right = NULL;
    return node;
}
Node* newNodeSplit(NodeType type, char letter) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = type;
    if(node->type == split) { 
    node->data.splitData.splitChar = letter;
    }
     node->data.pointData.height=0;
     node->data.pointData.width=0;
     node->data.pointData.x=0;
     node->data.pointData.y=0;
     node->data.pointData.number=letter;
    node->left = node->right = NULL;

    return node;
}

Node* buildTree(Node* postOrder, int* postIndex) {
    if (*postIndex < 0) {
        return NULL;
    }
    Node currentNode = postOrder[*postIndex];
    (*postIndex)--;  

    Node* root = NULL;
    if (currentNode.type == split) {
        root = newNodeSplit(currentNode.type, currentNode.data.splitData.splitChar);
       // printf("%c",currentNode.data.splitData.splitChar);
        root->right = buildTree(postOrder, postIndex);
        root->left = buildTree(postOrder, postIndex);
    } else {
        root = newNodePoint(currentNode.type, currentNode.data.pointData.number, 
               currentNode.data.pointData.width, currentNode.data.pointData.height);
    }
    return root;
}
void findDimV(Node* root){ 
    if(root == NULL) { 
        return;
    }
    root->data.pointData.width += root->left->data.pointData.width;
    root->data.pointData.width += root->right->data.pointData.width;

    root->data.pointData.height = MAX(root->right->data.pointData.height,root->left->data.pointData.height);
}

void findDimH(Node* root){ 
    if(root == NULL) { 
        return;
    }
    root->data.pointData.width = MAX(root->right->data.pointData.width,root->left->data.pointData.width);
    root->data.pointData.height += root->left->data.pointData.height;
    root->data.pointData.height += root->right->data.pointData.height;

}
void part2(FILE* file, Node* root){
    if(root != NULL) { 
        part2(file, root->left);
        part2(file, root->right);
        if(root->type == split) { 
            //call function 
            if(root->data.splitData.splitChar == 'V'){
                findDimV(root);
                fprintf(file, "%c(%d,%d)\n", root->data.splitData.splitChar, root->data.pointData.width, root->data.pointData.height);
            }
            if(root->data.splitData.splitChar == 'H'){
                findDimH(root);
                fprintf(file, "%c(%d,%d)\n", root->data.splitData.splitChar, root->data.pointData.width, root->data.pointData.height);
            }
        }
        else{ 
            fprintf(file,"%d(%d,%d)\n", root->data.pointData.number,root->data.pointData.width,root->data.pointData.height);
        }
    }
}

void part3(FILE* file, Node* root) { 
    if(root == NULL) {
        return;
    }


    if(root->type == split) { 
        if(root->data.splitData.splitChar == 'H') { 

            root->left->data.pointData.y = root->right->data.pointData.height + root->data.pointData.y ;
            root->left->data.pointData.x = root->data.pointData.x;
            root->right->data.pointData.x =  root->data.pointData.x;
            root->right->data.pointData.y = root->data.pointData.y;
        }
        if(root->data.splitData.splitChar =='V') {             
            root->left->data.pointData.y = root->data.pointData.y;
            root->left->data.pointData.x = root->data.pointData.x;
            root->right->data.pointData.y = root->data.pointData.y;
            root->right->data.pointData.x = root->left->data.pointData.width + root->data.pointData.x;
        }
       part3(file, root->left);
        part3(file, root->right);
        }   
             

        // if(root == NULL) {    
 
        // }

    }
    

void print_part3(FILE* file, Node* root) { 
        if(root != NULL) { 
        print_part3(file, root->left);
        print_part3(file, root->right);
        if(root->type == point) { 
      fprintf(file,"%d((%d,%d)(%d,%d))\n", root->data.pointData.number, root->data.pointData.width, root->data.pointData.height, root->data.pointData.x, root->data.pointData.y); 
        }

    }
}
void preOrder(FILE* file, Node* root) {
    if(root == NULL){ 
        return;
    }
    //preOrderList[(*index)++] = root->data.pointData;
   if(root->type == split){
    fprintf(file,"%c\n",root->data.splitData.splitChar);
    //printf("%c\n",root->data.splitData.splitChar);
   }
   else{ 
    fprintf(file,"%d(%d,%d)\n", root->data.pointData.number, root->data.pointData.width, root->data.pointData.height);
   }
    preOrder(file, root->left);
    preOrder(file, root->right);
}

void free_tree(Node* tree) {
    if (tree != NULL) { 
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree);
    }
}
int filelength (FILE* file) { 
    int counter = 0; 
    int x,y,z; 
    char ch;
    while (1) {
        int result = fscanf(file, "%d(%d,%d)", &x, &y, &z);
        if (result == 3) {  
            counter++;
        } else {
            result = fscanf(file, " %c", &ch);
            if (result == 1) {  
                counter++;
            } else {
                break;  
            }
        }
    }
    fseek(file, 0L, SEEK_SET);
    return counter; 
}
int main(int argc, char* argv[]){
   // struct Node* head = NULL;
    char val[30];

 
    // Open the file for reading 
    FILE* file = fopen(argv[1], "r");
    FILE* out1 = fopen(argv[2], "w");
    FILE* out2 = fopen(argv[3], "w");
    FILE* out3 = fopen(argv[4], "w");

   Node arr[filelength(file)];
    int i = 0; 
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    // Read each line from the file
    while (fgets(val, sizeof(val), file) != NULL) {
        int weight, x, y; 
        if(sscanf(val, "%d(%d,%d)", &weight, &x, &y)==3){
            struct Node newNode;
            newNode.type = point; 
            newNode.data.pointData.width = x;
            newNode.data.pointData.height = y; 
            newNode.data.pointData.number = weight; 
            arr[i]=newNode; 
        }        
        if((strcmp(val, "H")==0)||(strcmp(val, "H\n")==0)){

            struct Node hNode; 
            hNode.type = split;
            hNode.data.splitData.splitChar = 'H'; 
            arr[i] = hNode;
        }
        if((strcmp(val, "V")==0)||(strcmp(val, "V\n")==0)){
            struct Node vNode; 
            vNode.type = split;
            vNode.data.splitData.splitChar = 'V'; 
            arr[i] = vNode;
        }
        i++;
         }
         int tempi = i;
         for(;i>0; i--){
            
         }
        // for (int j = 0; j < tempi; j++) {
      //  printf("arr[%d] = %d\n", j, arr[j].type);
    //}
    int index = tempi -1;  
    Node* built = buildTree(arr, &index);

    //preOrder(out1, built); 
    part2(out2, built);
    part3(out3, built);
    print_part3(out3, built);
  //  printf("part three:\n");
    // Close the file after reading
    free_tree(built);

    fclose(file);
    fclose(out1);
    fclose(out2);
    fclose(out3);
    return 0;
}