//
//  transactionLinkedList.h
//  Kata.LoanPrediction.C
//
//  Created by retroburst [Andrew D] on 2/09/2015.
//  Copyright (c) 2015 retroburst [Andrew D]. All rights reserved.
//

#ifndef __Kata_LoanPrediction_C__transactionLinkedList__
#define __Kata_LoanPrediction_C__transactionLinkedList__

#include <stdio.h>
#include <stdbool.h>
#include "transaction.h"

struct transactionNode {
    transaction *item;
    struct transactionNode *next;
};
typedef struct transactionNode transactionNode;
bool addTransactionNode(transactionNode **root, transactionNode **head, transaction *new);
void freeAllNodes(transactionNode *root, transactionNode *head);

#endif /* defined(__Kata_LoanPrediction_C__transactionLinkedList__) */
