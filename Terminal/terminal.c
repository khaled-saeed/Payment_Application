#include "terminal.h"
#include<stdio.h>
#include<ctype.h>
#include<string.h>
/*********************** try to use date from the OS ******************/ 
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    printf("Please Enter the transaction data : ");
    char date[11] = "\0"; 
    scanf("%11s",date) ; 
    int len = strlen(date);
    strcpy(termData->transactionDate , date); 
    //printf("len: %d\n",len);                  // for debugging purposes 
    //printf("string : %s",date);               // Foe debugging purposes

    if(*termData->transactionDate == '\0'|| len <10 || !checkDateFormat(date,len))
    {
        return WRONG_NAME ;
    }
    else
    {
        return TERMINAL_OK ;
    }
}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    int EX_date_month = (cardData->cardExpirationDate[0]-'0') * 10 + (cardData->cardExpirationDate[1] -'0'); 
    int EX_date_year = (cardData->cardExpirationDate[3]-'0') * 10 + (cardData->cardExpirationDate[4]-'0');
    int Curr_date_month = (termData->transactionDate[3]-'0') * 10 + (termData->transactionDate[4] -'0'); 
    int Curr_date_year = (termData->transactionDate[8]-'0' )* 10 + (termData->transactionDate[9] -'0'); 
    printf("Expiration date : %d/%d\n",EX_date_month,EX_date_year);         // Foe debugging purposes
    printf("current date : %d/%d",Curr_date_month,Curr_date_year);          // Foe debugging purposes
    if(EX_date_year < Curr_date_year)
    {
        return EXPIRED_CARD ; 
    }
    else if (EX_date_year == Curr_date_year)
    {
        if(EX_date_month < Curr_date_month)
        {
            return EXPIRED_CARD ; 
        }
    }
    return TERMINAL_OK ; 
}
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{

}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("Please Enter the  transaction amount :") ;
    float amount ; 
    scanf("%f",&amount); 
    termData->transAmount = amount ; 
    if(termData->transAmount <= 0)
    {
        return INVALID_AMOUNT ; 
    }
    return TERMINAL_OK; 
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if(termData->transAmount > termData->maxTransAmount )
    {
        return EXCEED_MAX_AMOUNT ; 
    }
    return TERMINAL_OK ; 
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    // printf( "Enter the maximum amount for transaction :");
    // float max ; 
    // scanf("%d",&max); 
    termData->maxTransAmount = 5000 ; 
    if(termData->maxTransAmount <= 0)
    {
        return INVALID_MAX_AMOUNT ; 
    }
    return TERMINAL_OK ; 
}
bool checkDateFormat(char * date, int len)
{
    int i = 0 ; 
    while(i< len)
    {
        if( i == 2 || i == 5)
        {
            if( date[i] == '/')
                i++; 
            else
            {
                //printf("false at %d at %c",i , date[i]);      // Foe debugging purposes
                return false ; 
            }   
        }
        else
        {
            if(date[i] - '0' >=0 &&date[i] - '0' <= 9 )
                i++; 
            else
            {
                //printf("false at %d at %c",i , date[i]);      // Foe debugging purposes
                return false ; 
            }  
        }
    }
    return true ; 
}