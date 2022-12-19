#include <stdio.h>
#include <string.h>
#include "card.h"

#pragma warning(disable:4996) //to allow for the use of scanf
/*
int main() {
	getCardHolderNameTest();
	getCardExpiryDateTest();
	getCardPANTest();
}
*/





EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {

	printf("\nEnter card holder name:\t");
	scanf(" %[^\n]%*c", &cardData->cardHolderName);
	if ((cardData->cardHolderName == NULL) || (strlen(cardData->cardHolderName) > 24) || (strlen(cardData->cardHolderName) < 20)) {
		return  WRONG_NAME;
	}
	return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {

	printf("\nEnter card Expiry Date (MM/YY):\t");
	scanf(" %[^\n]%*c", &cardData->cardExpirationDate);
	if ((cardData->cardExpirationDate == NULL) || (strlen(cardData->cardExpirationDate) != 5) || (cardData->cardExpirationDate[2] != '/')) {
		return  WRONG_EXP_DATE;
	}
	return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {

	printf("\nEnter account number:\t");
	scanf(" %[^\n]%*c", &cardData->primaryAccountNumber);
	if ((cardData->primaryAccountNumber == NULL) || (strlen(cardData->primaryAccountNumber) > 19) || (strlen(cardData->primaryAccountNumber) < 16)) {
		return  WRONG_PAN;
	}
	return CARD_OK;
}

void getCardHolderNameTest(void) {
	ST_cardData_t one;
	ST_cardData_t* ptrone;
	ptrone = &one;
	int x;
	printf("Tester Name:\tMarwan Sallam\n");
	printf("Function Name:\tgetCardHolderName\n");
	printf("Result: 0 = CARD_OK; 1 = WRONG_NAME\n");
	printf("Test Case 1:\n");
	printf("Input Data: Marwan\n");
	printf("Expected Result: 1");
	x = getCardHolderName(ptrone);
	printf("Actual Result: %d\n", x);
	
	printf("Test Case 2:\n");
	printf("Input Data: Marwan Mohammed Ali Sallam\n");
	printf("Expected Result: 1");
	x = getCardHolderName(ptrone);
	printf("Actual Result: %d\n", x);

	printf("Test Case 3:\n");
	printf("Input Data: Marwan Moahmmed Sallam\n");
	printf("Expected Result: 0");
	x = getCardHolderName(ptrone);
	printf("Actual Result: %d\n", x);
}

void getCardExpiryDateTest(void){
	ST_cardData_t one;
	ST_cardData_t* ptrone;
	ptrone = &one;
	int x;
	printf("Tester Name:\tMarwan Sallam\n");
	printf("Function Name:\tgetCardExpiryDate\n");
	printf("Result: 0 = CARD_OK; 2 = WRONG_EXP_DATE\n");
	printf("Test Case 1:\n");
	printf("Input Data: 12/2023\n");
	printf("Expected Result: 2");
	x = getCardExpiryDate(ptrone);
	printf("Actual Result: %d\n", x);

	printf("Test Case 2:\n");
	printf("Input Data: 11/1\n");
	printf("Expected Result: 2");
	x = getCardExpiryDate(ptrone);
	printf("Actual Result: %d\n", x);

	printf("Test Case 3:\n");
	printf("Input Data: 12-23\n");
	printf("Expected Result: 2");
	x = getCardExpiryDate(ptrone);
	printf("Actual Result: %d\n", x);

	printf("Test Case 4:\n");
	printf("Input Data: 12/23\n");
	printf("Expected Result: 0");
	x = getCardExpiryDate(ptrone);
	printf("Actual Result: %d\n", x);
}

void getCardPANTest(void){
	ST_cardData_t one;
	ST_cardData_t* ptrone;
	ptrone = &one;
	int x;
	printf("Tester Name:\tMarwan Sallam\n");
	printf("Function Name:\tgetCardPAN\n");
	printf("Result: 0 = CARD_OK; 3 = WRONG_PAN\n");
	printf("Test Case 1:\n");
	printf("Input Data: 1111\n");
	printf("Expected Result: 3");
	x = getCardPAN(ptrone);
	printf("Actual Result: %d\n", x);

	printf("Test Case 2:\n");
	printf("Input Data: 1234567891234567891234\n");
	printf("Expected Result: 3");
	x = getCardPAN(ptrone);
	printf("Actual Result: %d\n", x);

	printf("Test Case 3:\n");
	printf("Input Data: 12345678912345678\n");
	printf("Expected Result: 0");
	x = getCardPAN(ptrone);
	printf("Actual Result: %d\n", x);
}




