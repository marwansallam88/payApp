#include <stdio.h>
#include <string.h>
#include "app.h"

#pragma warning(disable:4996) //to allow for the use of scanf

int main(){
	unsigned char cont = 'y';
	while(cont == 'y'){ 
		appStart();
		do {
			printf("\nWant to continue (y/n):\t");
			scanf(" %[^\n]%*c", &cont);
		} while (cont != 'y' && cont != 'n');
		}
	}

void appStart(void) {
	ST_cardData_t cardData;
	ST_cardData_t* ptrcardData;
	ptrcardData = &cardData;
	ST_terminalData_t termData;
	ST_terminalData_t* ptrtermData;
	ptrtermData = &termData;
	ST_transaction_t transData;
	ST_transaction_t* ptrtransData;
	ptrtransData = &transData;
	int check = 10;
	while( check != CARD_OK){
		check = getCardHolderName(ptrcardData);
	}
	check = 10;
	while (check != CARD_OK) {
		check = getCardExpiryDate(ptrcardData);
	}
	check = 10;
	while (check != CARD_OK) {
		check = getCardPAN(ptrcardData);
	}
	check = 10;
	while (check != TERMINAL_OK) {
		check = getTransactionDate(ptrtermData);
	}
	if (isCardExpired(ptrcardData, ptrtermData) == EXPIRED_CARD){
		printf("Declined Expired Card");
		return;
	}
	check = 10;
	while (check != TERMINAL_OK) {
		check = getTransactionAmount(ptrtermData);
	}
	check = setMaxAmount(ptrtermData, 100000.0);
	if (isBelowMaxAmount(ptrtermData) == EXCEED_MAX_AMOUNT) {
		printf("Declined Amount Exceeding Limit");
		return;
	}
	transData.cardHolderData = cardData;
	transData.terminalData = termData;
	check = recieveTransactionData(ptrtransData);


	
	
	


}