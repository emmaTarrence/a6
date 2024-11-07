#ifndef A6
#define A6
#include <stdbool.h>

typedef enum {
    split, 
    point
} NodeType;

 struct point {
    int number;
    int width;
    int x;
    int y;
    int height;
};

typedef struct Node {
    NodeType type;
    union { 
        struct point pointData;
        struct{
            char splitChar;
    }splitData;
}data;
struct Node* left;
struct Node* right; 
}Node;

#endif // A6
