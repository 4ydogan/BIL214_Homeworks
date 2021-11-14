#include <stdio.h>

struct node {
    char data;
    int layer;
    struct node *child;
};

struct node newNode(int layer, char data){

    struct node new;
    new.data = data;
    new.layer = layer;

    new.child = (struct node*)malloc(sizeof(struct node)*(layer+1));


};