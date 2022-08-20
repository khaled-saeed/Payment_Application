#include "server.h"
#include<stdio.h>
#include<ctype.h>
#include<string.h>
ST_accountsDB_t DataBase[255]={ {2000.0, RUNNING, "8989374615436851"},
                                {4000.0, RUNNING, "8989374615436852"},
                                {6000.0, RUNNING, "8989374615436853"},
                                {10000.0, RUNNING, "8989374615436854"},
                                {12000.0, BLOCKED, "8989374615436855"},
                                {14000.0, RUNNING, "8989374615436856"},
                                {16000.0, RUNNING, "8989374615436857"},
                                {18000.0, RUNNING, "8989374615436858"},
                                {20000.0, BLOCKED, "8989374615436859"},
                                {22000.0, RUNNING, "8989374615436860"},
                                {24000.0, RUNNING, "8989374615436861"},
                                {26000.0, RUNNING, "8989374615436862"},
                                {28000.0, BLOCKED, "8989374615436863"},
                                {30000.0, RUNNING, "8989374615436864"},
                                {32000.0, RUNNING, "8989374615436865"},
                                {34000.0, RUNNING, "8989374615436866"},
                                {36000.0, RUNNING, "8989374615436867"},
                                {38000.0, RUNNING, "8989374615436868"},
                                {40000.0, RUNNING, "8989374615436869"},
                                {42000.0, RUNNING, "8989374615436870"},
                                 };

ST_transaction_t TransDataBase[255]={0}; 
uint8_t accountIndex; 
uint8_t transactionIndex = 0 ; 
uint8_t totalNumberOfAccounts = 20;
EN_transStat_t receiveTransactionData(ST_transaction_t *transData)
{
    ST_accountsDB_t accountReference ; 
    if (isValidAccount(&transData->cardHolderData,&accountReference) == SERVER_OK)
    {
        if (isBlockedAccount(&accountReference) == SERVER_OK)
        {
           if(isAmountAvailable(&transData->terminalData,&accountReference) == SERVER_OK)
           {
             DataBase[accountIndex].balance -= transData->terminalData.transAmount;
             saveTransaction(transData);
             transData->transState = APPROVED ;
              //printf("APPROVED\n");                       // For debugging purposes
             return APPROVED; 
           }
           else
           {
             //printf("DECLINED_INSUFFICIENT_FUND\n");          // For debugging purposes
            return DECLINED_INSUFFICIENT_FUND ;
           }
        }
        else
        {
           //  printf("DECLINED_STOLEN_CARD\n");                // For debugging purposes
            return DECLINED_STOLEN_CARD;
        }
    }
    else
    {
         //printf("FRAUD_CARD\n");                              // For debugging purposes
        return FRAUD_CARD ; 
    }

    
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountReference)
{
    int i ; 
    for(i = 0 ; i < totalNumberOfAccounts ; i++)
    {
        if(!strncmp(cardData->primaryAccountNumber , DataBase[i].primaryAccountNumber,16))
        {
            accountReference->balance = DataBase[i].balance ; 
            strcpy(accountReference->primaryAccountNumber ,DataBase[i].primaryAccountNumber); 
            accountReference->state = DataBase[i].state; 
            accountIndex = i ; 
            //printf("SERVER_OK\n");                                // For debugging purposes
            return SERVER_OK ; 
        }
    }
    //printf("ACCOUNT_NOT_FOUND\n");                                // For debugging purposes
    return ACCOUNT_NOT_FOUND ;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference)
{
    if(accountReference->state == BLOCKED)
    {
        //printf("BLOCKED_ACCOUNT\n");                              // For debugging purposes
        return BLOCKED_ACCOUNT; 
    }
    else
    {
       // printf("SERVER_OK\n");                                    // For debugging purposes
        return SERVER_OK ; 
    }
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference)
{
   if( termData->transAmount <= accountReference->balance)
   {
        //printf("SERVER_OK\n");                                        // For debugging purposes
        return SERVER_OK ; 
   }
   else
   {
        //printf("LOW_BALANCE\n");                                      // For debugging purposes
        return LOW_BALANCE ; 
   }
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    strcpy(TransDataBase[transactionIndex].cardHolderData.cardExpirationDate , transData->cardHolderData.cardExpirationDate);
    strcpy(TransDataBase[transactionIndex].cardHolderData.cardHolderName , transData->cardHolderData.cardHolderName);
    strcpy(TransDataBase[transactionIndex].cardHolderData.primaryAccountNumber , transData->cardHolderData.primaryAccountNumber);
    TransDataBase[transactionIndex].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
    strcpy(TransDataBase[transactionIndex].terminalData.transactionDate , transData->terminalData.transactionDate); 
    TransDataBase[transactionIndex].terminalData.transAmount = transData->terminalData.transAmount;
    TransDataBase[transactionIndex].transactionSequenceNumber= transactionIndex+1;  
    printf("Transaction number : %d\n",TransDataBase[transactionIndex].transactionSequenceNumber);
    printf("The remaining balance : %f\n",DataBase[accountIndex].balance); 
    printf("Transaction Saved\n"); 
    transactionIndex++ ;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
    int i ;
    for(i = 0 ; i < transactionIndex ; i++)
    {
        if(TransDataBase[i].transactionSequenceNumber == transactionSequenceNumber)
        {
            *transData = TransDataBase[i]; 
            //printf("SERVER_OK\n");                            //for debugging purposes
            return SERVER_OK ; 
        }
      
            //printf("TRANSACTION_NOT_FOUND\n");                //for debugging purposes
            
    }
    return TRANSACTION_NOT_FOUND ;
}
