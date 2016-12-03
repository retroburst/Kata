//
//  transactionLinkedList.c
//  Kata.LoanPrediction.C
//
//  Created by retroburst [Andrew D] on 2/09/2015.
//  Copyright (c) 2015 retroburst [Andrew D]. All rights reserved.
//

#include <stdbool.h>
#include <stdlib.h>
#include "transactionLinkedList.h"
#include "transaction.h"

static bool checkAllocation(transactionNode *target);

/*
 ***************************************
 ** Adds a new transaction node to the 
 ** linked list.
 ***************************************
 */
bool addTransactionNode(transactionNode **root, transactionNode **head, transaction *new)
{
    if(*root == NULL)
    {
        *root = malloc(sizeof(transactionNode));
        if(checkAllocation(*root) == false) return(false);
        (*root)->item = new;
        (*root)->next = NULL;
        *head = *root;
        return(true);
    }
    else
    {
        transactionNode *tmp = malloc(sizeof(transactionNode));
        if(checkAllocation(tmp) == false) return(false);
        tmp->item = new;
        tmp->next = NULL;
        (*head)->next = tmp;
        *head = tmp;
        return(true);
    }
}

/*
 ***************************************
 ** Frees memory used by all nodes in
 ** the linked list.
 ***************************************
 */
void freeAllNodes(transactionNode *root, transactionNode *head)
{
    if(root == NULL) return;
    transactionNode *current = root;
    transactionNode *next = NULL;
    while(current != NULL)
    {
        next = current->next;
        free(current->item);
        free(current);
        current = next;
    }
    head = NULL;
}

/*
 ***************************************
 ** Checks the memory allocation
 ** for the node was successful.
 ***************************************
 */
static bool checkAllocation(transactionNode *target)
{
    if(target != NULL) {
        return (true);
    } else {
        printf("Out of memory, could not allocate for transactionNode.");
        return(false);
    }
}
