#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include<stdio.h>
#include<stdlib.h>

struct node{
        int data;
        struct node *next;
    };
struct BigInteger{
    struct node *head;
    int length;
    int sign;
};

struct BigInteger initialize(char *);
struct BigInteger sub(struct BigInteger , struct BigInteger );
struct BigInteger add(struct BigInteger , struct BigInteger );
void truncate(struct node *);
int compare(struct BigInteger , struct BigInteger );
void trav(struct node *head);
void display(struct BigInteger);
int length(struct node *);
struct BigInteger mul(struct BigInteger , struct BigInteger );
int zero(struct BigInteger ,struct node *);
struct BigInteger div1(struct BigInteger ,struct BigInteger );

#endif
