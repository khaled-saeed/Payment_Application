#include "card.h"
#include<stdio.h>
#include<ctype.h>
#include<string.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
printf("Please Enter Your name ");
    gets(cardData->cardHolderName);
    int len = strlen(cardData->cardHolderName);
    if(*cardData->cardHolderName == '\0'|| len <20 || len>24)
    {
        return WRONG_NAME ;
    }
    else
    {
        return OK ;
    }
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    printf("Please enter the card's expiry date ? ") ; 
    gets(cardData->cardExpirationDate);
    int len = strlen(cardData->cardExpirationDate);
    if(*cardData->cardExpirationDate == '\0'|| len <5 || len>5)
    {
        return WRONG_EXP_DATE ;
    }
    else
    {
        return OK ;
    }

}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    printf("Please enter the card's Primary Account Number ? ") ; 
    gets(cardData->cardExpirationDate);
    int len = strlen(cardData->cardExpirationDate);
    if(*cardData->cardExpirationDate == '\0'|| len <16 || len>19)
    {
        return WRONG_PAN ;
    }
    else
    {
        return OK ;
    }
}