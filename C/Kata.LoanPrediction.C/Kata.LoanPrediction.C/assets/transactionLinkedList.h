//
//  transactionLinkedList.h
//  Kata.LoanPrediction.C
//
//  Created by Andrew Dowding on 2/09/2015.
//  Copyright (c) 2015 a.j.dowding. All rights reserved.
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
bool AddTransactionNode(transactionNode **root, transactionNode **head, transaction *new);

#endif /* defined(__Kata_LoanPrediction_C__transactionLinkedList__) */
