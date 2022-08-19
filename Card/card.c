#include "card.h"
#include<stdio.h>
#include<ctype.h>
#include<string.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
printf("Please Enter Your name ");
    char name[25] = "\0"; 
    fgets(name,25,stdin) ;                
    int len = strlen(name);
    len--;                                      // because fgets() adds a new line character at the end of the string 
    strcpy(cardData->cardHolderName , name); 
    //printf("len: %d\n",len);
    //printf("string : %s",name);  

    if(*cardData->cardHolderName == '\0'|| len <20 || len>24)
    {
        return WRONG_NAME ;
    }
    else
    {
        return CARD_OK ;
    }
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    printf("Please Enter  the card expiration date ");
    char Ex_date[6] = "\0"; 
    fgets(Ex_date,6,stdin) ;                
    int len = strlen(Ex_date);
    len--; 
    strcpy(cardData->cardExpirationDate, Ex_date); 
    if(*cardData->cardExpirationDate == '\0'|| len <5 || len>5)
    {
        return WRONG_EXP_DATE ;
    }
    else
    {
        return CARD_OK ;
    }

}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    printf("Please enter the card's Primary Account Number ? ") ; 
   char PAN[20] = "\0"; 
    fgets(PAN,20,stdin) ;                
    int len = strlen(PAN);
    len-- ; 
    strcpy(cardData->primaryAccountNumber, PAN); 
    if(*cardData->primaryAccountNumber == '\0'|| len <16 || len>19)
    {
        return WRONG_PAN ;
    }
    else
    {
        return CARD_OK ;
    }
}