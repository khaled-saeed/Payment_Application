#include "card.h"
#include<stdio.h>
#include<ctype.h>
#include<string.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    printf("Please Enter Your name :");
    char name[26] = "\0"; 
    scanf(" %26[^\n]",name) ;                
    int len = strlen(name);
    strcpy(cardData->cardHolderName , name); 
    //printf("len: %d\n",len);                                  // For debugging purposes
    //printf("string : %s\n",cardData->cardHolderName);  

    if(*cardData->cardHolderName == '\0'|| len <20 || len>24)
    {
        //printf("WRONG_NAME\n");                       // For debugging purposes
        return WRONG_NAME ;
    }
    else
    {
       // printf("CARD_OK\n");                          // For debugging purposes
        return CARD_OK ;
    }
}
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData) 
{
    printf("Please Enter  the card expiration date in the formate MM/YY : ");
    char Ex_date[7] = "\0"; 
    scanf(" %7[^\n]",Ex_date) ;                
    int len = strlen(Ex_date);
    strcpy(cardData->cardExpirationDate, Ex_date); 
    if(*cardData->cardExpirationDate == '\0'|| len <5 || len>5)
    {
        //printf("WRONG_EXP_DATE\n");               // For debugging purposes
        return WRONG_EXP_DATE ;
    }
    else
    {
        //printf("CARD_OK\n");                      // For debugging purposes
        return CARD_OK ;
    }

}
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    printf("Please enter the card's Primary Account Number : ") ; 
    char PAN[21] = "\0"; 
    scanf(" %21[^\n]",PAN) ;                
    int len = strlen(PAN);
    strcpy(cardData->primaryAccountNumber, PAN); 
    if(*cardData->primaryAccountNumber == '\0'|| len <16 || len>19)
    {
      //  printf("WRONG_PAN\n");                            // For debugging purposes
        return WRONG_PAN ;
    }
    else
    {
        //printf("CARD_OK\n");                              // For debugging purposes
        return CARD_OK ;
    }
}