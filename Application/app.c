#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include "app.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

void appStart(void)
{
    ST_terminalData_t myTerminal ;
    ST_cardData_t myCard ; 
    ST_transaction_t myTransaction; 
    int functionState; 
    printf("Choose an option :\n1-Make a Transaction.\n2-Get a Transaction info\n");
    int choice ; 
    scanf(" %d",&choice); 
    if(choice == 1)
    {
        while (getCardHolderName(&myCard) == WRONG_NAME)
        printf("Please Enter a valid Name \n");
        while (getCardExpiryDate(&myCard) ==WRONG_EXP_DATE )
            printf("Please Enter a valid Expiration date with the format MM/YY \n");
        while(getCardPAN(&myCard) == WRONG_PAN)
            printf("Please Enter a valid PAN number\n"); 
        while (getTransactionDate(&myTerminal) == WRONG_DATE)
            printf("Please Enter a valid date with the format dd/mm/yyyy \n");
        if( isCardExpired(&myCard,&myTerminal) == EXPIRED_CARD)
        {
            printf("Expired Card \n"); 
            return ; 
        }
        setMaxAmount(&myTerminal); 
        while (getTransactionAmount(&myTerminal) == INVALID_AMOUNT)
            printf("Please Enter a valid amount \n"); 
        while(isBelowMaxAmount(&myTerminal) == EXCEED_MAX_AMOUNT)
        {
            printf("You Exceeded the maximum amount \n");
            printf("Please Enter a value below 5000\n");
            while (getTransactionAmount(&myTerminal) == INVALID_AMOUNT)
                printf("Please Enter a valid amount \n"); 
        }
            
        myTransaction.cardHolderData = myCard ; 
        myTransaction.terminalData = myTerminal ; 
        functionState = receiveTransactionData(&myTransaction); 
    }
    else if (choice == 2)
    {

        uint32_t transactionNumber ; 
        ST_transaction_t retTransaction ; 
        printf("Please Enter the Transaction Number :"); 
        scanf(" %d",&transactionNumber); 
        if(getTransaction(transactionNumber,&retTransaction) == TRANSACTION_NOT_FOUND)
        {
            printf("Transaction Not Found\n"); 
        }
        else
        {
            printf("Transaction client name : %s\n",retTransaction.cardHolderData.cardHolderName);
            printf("Card Expiration Date: %s\n",retTransaction.cardHolderData.cardExpirationDate);
            printf("PAN Number : %s\n",retTransaction.cardHolderData.primaryAccountNumber);
            printf("Transaction amount : %f\n",retTransaction.terminalData.transAmount);
            printf("Transaction date : %s\n",retTransaction.terminalData.transactionDate);
            printf("Transaction sequence number : %d\n",retTransaction.transactionSequenceNumber);
            functionState = retTransaction.transState ;
            
        }

    }
    else
    {
        printf("Please Choose a valid number\n"); 
        return; 
    }
    switch (functionState)
        {
        case APPROVED: printf("APPROVED\n");   // / Server is Ok / Terminal is OK
            break;
        case DECLINED_INSUFFICIENT_FUND: printf("DECLINED_INSUFFICIENT_FUND\n"); 
            break;
        case DECLINED_STOLEN_CARD: printf("DECLINED_STOLEN_CARD\n"); 
            break;
        case FRAUD_CARD: printf("FRAUD_CARD \n"); 
            break;
        case INTERNAL_SERVER_ERROR: printf("INTERNAL_SERVER_ERROR \n"); 
            break;
        case EXCEED_MAX_AMOUNT: printf("EXCEED_MAX_AMOUNT\n"); 
            break;
        case INVALID_MAX_AMOUNT: printf("INVALID_MAX_AMOUNT \n"); 
            break;
        default:
            break;
        }

    
}
int main()
{
    while(1)
    {
         appStart(); 
    }
   
    return 0 ; 
}