#include "card.h"
#include<stdio.h>
#include<ctype.h>
#include<string.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    printf("Please Enter Your name :");
    char name[26] = "\0"; 
    scanf("%26s",name) ;                
    int len = strlen(name);
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
    printf("Please Enter  the card expiration date : ");
    char Ex_date[7] = "\0"; 
    scanf("%7s",Ex_date) ;                
    int len = strlen(Ex_date);
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
    printf("Please enter the card's Primary Account Number : ") ; 
    char PAN[21] = "\0"; 
    scanf("%21s",PAN) ;                
    int len = strlen(PAN);
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