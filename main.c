#include <stdio.h>
#include "Card\card.h"
#include "Terminal/terminal.h"

int main()
{
    ST_cardData_t C1; 
    ST_terminalData_t T1 ; 
    printf("%d",getCardExpiryDate(&C1));
    getTransactionDate(&T1);
    printf("%d",isCardExpired(C1,T1)); 

}