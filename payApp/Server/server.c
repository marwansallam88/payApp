#include <stdio.h>
#include <string.h>
#include "server.h"

ST_accountsDB_t accountsDB[255] = {
	{2000.0, RUNNING, "8989374615436851"},
	{100000.0, BLOCKED, "5807007076043875"},
	{500.0, RUNNING,"13241235253452547"},
	{300.0,RUNNING,"63425787683425906"},
	{700.0,BLOCKED,"237459862345875342"},
	{60000.0,RUNNING,"23412341234876535"}
};

ST_transaction_t transaction[255] = { 0 };
int sequenceNumber = 0;
ST_accountsDB_t currentAccount;
/*
int main(){
	//isValidAccountTest();
	//isBlockedAccountTest();
	//isAmountAvailableTest();
	//saveTransactionTest();
	//recieveTransactionDataTest();
	//listSavedTransactionsTest();
}
*/



EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	ST_accountsDB_t* ptrcur;
	ptrcur = &currentAccount;
	if (isValidAccount(&transData->cardHolderData,ptrcur) == 3) {
		printf("Declined Invalid account\n");
		transData->transState = FRAUD_CARD;
		saveTransaction(transData);
		return FRAUD_CARD;
	}
	if (isAmountAvailable(&transData->terminalData, ptrcur) == 4) {
		printf("Declined Insuffecient funds\n");
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		saveTransaction(transData);
		return DECLINED_INSUFFECIENT_FUND;
	}
	if (isBlockedAccount(ptrcur) == 5) {
		printf("Declined Stolen Card\n");
		transData->transState = DECLINED_STOLEN_CARD;
		saveTransaction(transData);
		return DECLINED_STOLEN_CARD;
	}
	transData->transState = APPROVED;
	if (saveTransaction(transData) == 1) {
		printf("Declined INTERNAL SERVER ERROR\n");
		transData->transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}
	printf("\nOld Balance:\t%f", currentAccount.balance);
	currentAccount.balance = currentAccount.balance - transData->terminalData.transAmount;
	printf("\nNew Balance:\t%f", currentAccount.balance);
	printf("\nApproved\n");
	return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	for (int i = 0; i < 6; i++) {
		if (strcmp(accountsDB[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0) {
			*accountRefrence = accountsDB[i];
			return SERVER_OK;
		}
	}
	accountRefrence = NULL;
	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (accountRefrence->state == 1) {
		return BLOCKED_ACCOUNT;
	}
	return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	if (termData->transAmount > accountRefrence->balance) {
		return LOW_BALANCE;
	}
	return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	transData->transactionSequenceNumber = sequenceNumber;
	transaction[sequenceNumber].cardHolderData = transData->cardHolderData;
	transaction[sequenceNumber].terminalData = transData->terminalData;
	transaction[sequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber;
	transaction[sequenceNumber].transState = transData->transState;
	sequenceNumber++;
	listSavedTransactions();
	return SERVER_OK;
}

void listSavedTransactions(void) {
		for (int i = 0; i < sequenceNumber; i++) {
			printf("\n#########################\nTransaction Sequence Number:\t%u", transaction[i].transactionSequenceNumber);
			printf("\nTransaction Date:\t%s", transaction[i].terminalData.transactionDate);
			printf("\nTransaction Amount:\t%f", transaction[i].terminalData.transAmount);
			printf("\nTransaction State:\t%d", transaction[i].transState);
			printf("\nTerminal Max Amount:\t%f", transaction[i].terminalData.maxTransAmount);
			printf("\nCardholder Name:\t%s", transaction[i].cardHolderData.cardHolderName);
			printf("\nPAN:\t%s", transaction[i].cardHolderData.primaryAccountNumber);
			printf("\nCard Expiration:\t%s", transaction[i].cardHolderData.cardExpirationDate);
			printf("\n#########################\n");
		}
}


void recieveTransactionDataTest(void){
	ST_transaction_t tone = { {"Marwan Mohammed Sallam","898937461543685","01/26"},
			{200,100000,"01/01/2023"},APPROVED,0 };
	ST_transaction_t ttwo = { {"Marwan Mohammed Sallam","8989374615436851","01/26"},
		{20000,100000,"01/01/2023"},APPROVED,0 };
	ST_transaction_t tthree = { {"Marwan Mohammed Sallam","5807007076043875","01/26"},
		{20,100000,"01/01/2023"},APPROVED,0 };
	ST_transaction_t tfour = { {"Marwan Mohammed Sallam","8989374615436851","01/26"},
		{1000,100000,"01/01/2023"},APPROVED,0 };
	ST_transaction_t* ptrtone;
	ptrtone = &tone;
	int x;
	printf("Tester Name:\tMarwan Sallam\n");
	printf("Function Name:\trecieveTransactionData\n");
	printf("Result: 0 = APPROVED; 1 = DECLINED_INSUFFECIENT_FUND; 2 = DECLINED_STOLEN_CARD; 3 = FRAUD_CARD; 4 = INTERNAL_SERVER_ERROR\n");
	printf("Test Case 1: FRAUD_CARD \n");
	printf("Input Data: UNAVAILABLE PAN\n");
	printf("Expected Result: 3\n");
	x = recieveTransactionData(ptrtone);
	printf("Actual Result: %d\n", x);
	ptrtone = &ttwo;
	printf("Test Case 2: \n");
	printf("Input Data:NOT ENOUGH MONEY IN BALANCE\n");
	printf("Expected Result: 1\n");
	x = recieveTransactionData(ptrtone);
	printf("Actual Result: %d\n", x);
	ptrtone = &tthree;
	printf("Test Case 3: \n");
	printf("Input Data:BLOCKED ACCOUNT\n");
	printf("Expected Result: 2\n");
	x = recieveTransactionData(ptrtone);
	printf("Actual Result: %d\n", x);
	ptrtone = &tfour;
	printf("Test Case 4: \n");
	printf("Input Data:APPROVED TRANSACTION\n");
	printf("Expected Result: 0\n");
	x = recieveTransactionData(ptrtone);
	printf("Actual Result: %d\n", x);
}




void isValidAccountTest(void){
	ST_cardData_t one = { "","898937461543685","" };
	ST_cardData_t two = { "","8989374615436851","" };
	ST_cardData_t three = { "","23412341234876535","" };
	ST_cardData_t* ptrone;
	ptrone = &one;
	ST_accountsDB_t* ptrcur;
	ptrcur = &currentAccount;
	int x;
	printf("Tester Name:\tMarwan Sallam\n");
	printf("Function Name:\tisValidAccount\n");
	printf("Result: 0 = SERVER_OK; 3 = ACCOUNT_NOT_FOUND\n");
	printf("Test Case 1:\n");
	printf("Input Data: Unavailable PAN \n");
	printf("Expected Result: 3\n");
	x = isValidAccount(ptrone, ptrcur);
	printf("Actual Result: %d\n", x);
	printf("%f    %d     %s\n", currentAccount.balance, currentAccount.state, currentAccount.primaryAccountNumber);

	ptrone = &two;
	printf("Test Case 2:\n");
	printf("Input Data: Available PAN\n");
	printf("Expected Result: 0\n");
	x = isValidAccount(ptrone, ptrcur);
	printf("Actual Result: %d\n", x);
	printf("%f    %d     %s\n", currentAccount.balance, currentAccount.state, currentAccount.primaryAccountNumber);
	
	ptrone = &three;
	printf("Test Case 3:\n");
	printf("Input Data: Available PAN\n");
	printf("Expected Result: 0\n");
	x = isValidAccount(ptrone, ptrcur);
	printf("Actual Result: %d\n", x);
	printf("%f    %d     %s\n", currentAccount.balance, currentAccount.state, currentAccount.primaryAccountNumber);
}

void isBlockedAccountTest(void){
	ST_accountsDB_t* ptrcur;
	ptrcur = &currentAccount;
	*ptrcur = accountsDB[1];
	int x;
	printf("Tester Name:\tMarwan Sallam\n");
	printf("Function Name:\tisBlockedAccount\n");
	printf("Result: 0 = SERVER_OK; 5 = BLOCKED_ACCOUNT\n");
	printf("Test Case 1:\n");
	printf("Input Data: Blocked Account = 1 \n");
	printf("%f    %d     %s\n", currentAccount.balance, currentAccount.state, currentAccount.primaryAccountNumber);
	printf("Expected Result: 5\n");
	x = isBlockedAccount(ptrcur);
	printf("Actual Result: %d\n", x);
	
	*ptrcur = accountsDB[0];
	printf("Test Case 2:\n");
	printf("Input Data: Running Account = 0 \n");
	printf("%f    %d     %s\n", currentAccount.balance, currentAccount.state, currentAccount.primaryAccountNumber);
	printf("Expected Result: 0\n");
	x = isBlockedAccount(ptrcur);
	printf("Actual Result: %d\n", x);
}


void isAmountAvailableTest(void){
	ST_accountsDB_t* ptrcur;
	ST_terminalData_t* ptrtone;
	ST_terminalData_t tone = { 20000,0,"01/12/2022" };
	ST_terminalData_t ttwo = { 200,0,"01/12/2022" };
	ptrcur = &currentAccount;
	*ptrcur = accountsDB[0];
	ptrtone = &tone;
	int x;
	printf("Tester Name:\tMarwan Sallam\n");
	printf("Function Name:\tisAmountAvailable\n");
	printf("Result: 0 = SERVER_OK; 4 = LOW_BALANCE\n");
	printf("Test Case 1:\n");
	printf("Input Data: BalanceAvailable < transactionAmount \n");
	printf("%f    %f     %f\n", currentAccount.balance, ptrtone->transAmount, currentAccount.balance - ptrtone->transAmount);
	printf("Expected Result: 4\n");
	x = isAmountAvailable(ptrtone, ptrcur);
	printf("Actual Result: %d\n", x);

	ptrtone = &ttwo;
	printf("Test Case 2:\n");
	printf("Input Data: BalanceAvailable > transactionAmount \n");
	printf("%f    %f     %f\n", currentAccount.balance, ptrtone->transAmount, currentAccount.balance - ptrtone->transAmount);
	printf("Expected Result: 0\n");
	x = isAmountAvailable(ptrtone, ptrcur);
	printf("Actual Result: %d\n", x);
}


void saveTransactionTest(void){
	ST_transaction_t tone = { {"Marwan Mohammed Sallam","8989374615436851","01/26"},
		{200,100000,"01/01/2023"},APPROVED,0};
	ST_transaction_t ttwo = { {"Mohammed Sallah Aloska","8989374615436851","10/31"},
		{20000,5000000,"20/05/2023"},DECLINED_STOLEN_CARD,0 };
	ST_transaction_t* ptrtone;
	ptrtone = &tone;
	int x;
	printf("Tester Name:\tMarwan Sallam\n");
	printf("Function Name:\tsaveTransaction\n");
	printf("Result: 0 = SERVER_OK\n");
	printf("Test Case 1: First Save\n");
	printf("Input Data:\n");
	printf("Expected Result: 0\n");
	x = saveTransaction(ptrtone);
	printf("Actual Result: %d\n", x);
	ptrtone = &ttwo;
	printf("Test Case 2: Second Save\n");
	printf("Input Data:\n");
	printf("Expected Result: 0\n");
	x = saveTransaction(ptrtone);
	printf("Actual Result: %d\n", x);
}

void listSavedTransactionsTest(void) {
	ST_transaction_t tone = { {"Marwan Mohammed Sallam","8989374615436851","01/26"},
		{200,100000,"01/01/2023"},APPROVED,0 };
	ST_transaction_t ttwo = { {"Mohammed Sallah Aloska","8989374615436851","10/31"},
		{20000,5000000,"20/05/2023"},DECLINED_STOLEN_CARD,0 };
	ST_transaction_t* ptrtone;
	ptrtone = &tone;
	int x;
	printf("Tester Name:\tMarwan Sallam\n");
	printf("Function Name:\tlistSavedTransactions\n");
	printf("Result: 0 = SERVER_OK\n");
	printf("Test Case 1:\n");
	printf("Input Data:\n");
	printf("Expected Result: 0\n");
	x = saveTransaction(ptrtone);;
	ptrtone = &ttwo;
	x = saveTransaction(ptrtone);
	printf("Actual Result: %d\n", x);
	listSavedTransactions();

}