//
//  transactionLinkedList.c
//  Kata.LoanPrediction.C
//
//  Created by A.J.Dowding on 2/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
//

#include <stdbool.h>
#include <stdlib.h>
#include "transactionLinkedList.h"
#include "transaction.h"

static bool CheckAllocation(transactionNode *target);

/*
 ***************************************
 ** Adds a new transaction node to the 
 ** linked list.
 ***************************************
 */
bool AddTransactionNode(transactionNode **root, transactionNode **head, transaction *new)
{
    if(*root == NULL)
    {
        *root = malloc(sizeof(transactionNode));
        if(CheckAllocation(*root) == false) return(false);
        (*root)->item = new;
        (*root)->next = NULL;
        *head = *root;
        return(true);
    }
    else
    {
        transactionNode *tmp = malloc(sizeof(transactionNode));
        if(CheckAllocation(tmp) == false) return(false);
        tmp->item = new;
        tmp->next = NULL;
        (*head)->next = tmp;
        *head = tmp;
        return(true);
    }
}

/*
 ***************************************
 ** Checks the memory allocation
 ** for the node was successful.
 ***************************************
 */
static bool CheckAllocation(transactionNode *target)
{
    if(target != NULL) return (true);
    else {
        printf("Out of memory, could not allocate for transactionNode.");
        return(true);
    }
}