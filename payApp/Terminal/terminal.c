#include <stdio.h>
#include <string.h>
#include "terminal.h"

#pragma warning(disable:4996) //to allow for the use of scanf
/*
int main() {
    getTransactionDateTest();
    isCardExpiredTest();
    getTransactionAmountTest();
    isBelowMaxAmountTest();
    setMaxAmountTest();
    
}
*/


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
    printf("\nEnter transaction Date (DD/MM/YYYY):\t");
    scanf(" %[^\n]%*c", &termData->transactionDate);
    if ((termData->transactionDate == NULL) || (strlen(termData->transactionDate) != 10) || (termData->transactionDate[2] != '/') || (termData->transactionDate[5] != '/')) {
        return WRONG_DATE;
    }
    return TERMINAL_OK;
}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
    uint8_t* expirationDateMonths = &cardData->cardExpirationDate[0];
    uint8_t* expirationDateYears = &cardData->cardExpirationDate[3];
    uint8_t* terminalDateMonths = &termData->transactionDate[3];
    uint8_t* terminalDateYears = &termData->transactionDate[8];
    uint32_t expirationDateInt = 100 * atoi(expirationDateYears) + atoi(expirationDateMonths);
    uint32_t terminalDateInt = 100 * atoi(terminalDateYears) + atoi(terminalDateMonths);
    if (terminalDateInt > expirationDateInt) {
        return EXPIRED_CARD;
    }
    return TERMINAL_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
    printf("\nEnter the transaction Amount:\t");
    scanf(" %f", &termData->transAmount);
    if (termData->transAmount <= 0) {
        return INVALID_AMOUNT;
    }
    return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
    if (termData->transAmount > termData->maxTransAmount) {
        return EXCEED_MAX_AMOUNT;
    }
    return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
    termData->maxTransAmount = maxAmount;
    if (termData->maxTransAmount <= 0) {
        return INVALID_MAX_AMOUNT;
    }
    return TERMINAL_OK;
}

void getTransactionDateTest(void){
    ST_terminalData_t tone;
    ST_terminalData_t* ptrtone;
    ptrtone = &tone;
    int x;
    printf("Tester Name:\tMarwan Sallam\n");
    printf("Function Name:\tgetTransactionDate\n");
    printf("Result: 0 = TERMINAL_OK; 1 = WRONG_DATE\n");
    printf("Test Case 1:\n");
    printf("Input Data: 1/2/2023\n");
    printf("Expected Result: 1");
    x = getTransactionDate(ptrtone);
    printf("Actual Result: %d\n", x);

    printf("Test Case 2:\n");
    printf("Input Data: 01/02-2023\n");
    printf("Expected Result: 1");
    x = getTransactionDate(ptrtone);
    printf("Actual Result: %d\n", x);

    printf("Test Case 3:\n");
    printf("Input Data: 01-02/2023\n");
    printf("Expected Result: 1");
    x = getTransactionDate(ptrtone);
    printf("Actual Result: %d\n", x);
    
    printf("Test Case 4:\n");
    printf("Input Data: 01/02/2023\n");
    printf("Expected Result: 0");
    x = getTransactionDate(ptrtone);
    printf("Actual Result: %d\n", x);
}

void isCardExpiredTest(void){
    ST_terminalData_t tone = {0,0,"01/12/2022"};
    ST_cardData_t one = {"","","12/21"};
    ST_terminalData_t* ptrtone;
    ST_cardData_t* ptrone;
    ptrtone = &tone;
    ptrone = &one;
    int x;
    printf("Tester Name:\tMarwan Sallam\n");
    printf("Function Name:\tisCardExpired\n");
    printf("Result: 0 = TERMINAL_OK; 2 = EXPIRED_CARD\n");
    printf("Test Case 1:\n");
    printf("Input Data: cardExpirationDate:12/21; transactionDate:01/12/2022\n");
    printf("Expected Result: 2\n");
    x = isCardExpired(ptrone,ptrtone);
    printf("Actual Result: %d\n", x);

    ST_terminalData_t ttwo = { 0,0,"01/12/2022" };
    ST_cardData_t two = { "","","12/23" };
    ptrtone = &ttwo;
    ptrone = &two;
    printf("Test Case 2:\n");
    printf("Input Data: cardExpirationDate:12/23; transactionDate:01/12/2022\n");
    printf("Expected Result: 0\n");
    x = isCardExpired(ptrone, ptrtone);
    printf("Actual Result: %d\n", x);
}

void getTransactionAmountTest(void){
    ST_terminalData_t tone;
    ST_terminalData_t* ptrtone;
    ptrtone = &tone;
    int x;
    printf("Tester Name:\tMarwan Sallam\n");
    printf("Function Name:\tgetTransactionAmount\n");
    printf("Result: 0 = TERMINAL_OK; 4 = INVALID_AMOUNT\n");
    printf("Test Case 1:\n");
    printf("Input Data: -200\n");
    printf("Expected Result: 4");
    x = getTransactionAmount(ptrtone);
    printf("Actual Result: %d\n", x);

    printf("Test Case 2:\n");
    printf("Input Data: 200\n");
    printf("Expected Result: 0");
    x = getTransactionAmount(ptrtone);
    printf("Actual Result: %d\n", x);
}

void isBelowMaxAmountTest(void){
    ST_terminalData_t tone = { 200,100,"" };
    ST_terminalData_t* ptrtone;
    ptrtone = &tone;
    int x;
    printf("Tester Name:\tMarwan Sallam\n");
    printf("Function Name:\tisBelowMaxAmount\n");
    printf("Result: 0 = TERMINAL_OK; 5 = EXCEED_MAX_AMOUNT\n");
    printf("Test Case 1:\n");
    printf("Input Data: transAmount: 200; maxTransAmount: 100\n");
    printf("Expected Result: 5\n");
    x = isBelowMaxAmount(ptrtone);
    printf("Actual Result: %d\n", x);

    ST_terminalData_t ttwo = { 200,400,"" };
    ptrtone = &ttwo;
    printf("Test Case 2:\n");
    printf("Input Data: transAmount: 200; maxTransAmount: 400\n");
    printf("Expected Result: 0\n");
    x = isBelowMaxAmount(ptrtone);
    printf("Actual Result: %d\n", x);
}

void setMaxAmountTest(void){
    ST_terminalData_t tone;
    ST_terminalData_t* ptrtone;
    ptrtone = &tone;
    int x;
    printf("Tester Name:\tMarwan Sallam\n");
    printf("Function Name:\tsetMaxAmount\n");
    printf("Result: 0 = TERMINAL_OK; 6 = INVALID_MAX_AMOUNT\n");
    printf("Test Case 1:\n");
    printf("Input Data: -200\n");
    printf("Expected Result: 6\n");
    x = setMaxAmount(ptrtone,-200);
    printf("Actual Result: %d\n", x);

    printf("Test Case 2:\n");
    printf("Input Data: 200\n");
    printf("Expected Result: 0\n");
    x = setMaxAmount(ptrtone,200);
    printf("Actual Result: %d\n", x);
}