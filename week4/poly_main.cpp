#define _CRT_SECURE_NO_WARNINGS

#define BUFFSIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct polyTerm {
	int exp;
	int coeff;
	polyTerm* next;
} polyTerm;

typedef struct poly {
	polyTerm* head;
} poly;

void clearPoly(poly* A);
void addTerm(poly* A, int exp, int coeff);
poly multiPoly(poly A, poly B);

void printPoly_impl(poly A, char* buffer);
void printPoly(poly A);

poly createPoly();

int main() {
	poly A = createPoly();
	poly B = createPoly();

	addTerm(&A, 1, 1);
	addTerm(&A, 0, 1);
	printPoly(A);
	printf("\n");

	addTerm(&B, 1, 1);
	addTerm(&B, 0, -1);
	printPoly(B);
	printf("\n");

	poly C = multiPoly(A, B);
	printPoly(C);
	printf("\n");

	return 0;
}

void clearPoly(poly* A) {
	polyTerm* pTmpTerm = NULL;
	polyTerm* pDelTerm = NULL;

	pTmpTerm = A->head;
	while (pTmpTerm->next != NULL) {
		pDelTerm = pTmpTerm->next;
		pTmpTerm->next = pDelTerm->next;
		free(pDelTerm);
	}

}
void addTerm(poly* A, int exp, int coeff) {
	polyTerm* pTmpTerm = NULL;
	polyTerm* pNewTerm = NULL;

	pNewTerm = new polyTerm;
	pNewTerm->exp = exp;
	pNewTerm->coeff = coeff;
	pNewTerm->next = NULL;

	pTmpTerm = A->head;
	while (pTmpTerm->next != NULL) {
		if (pTmpTerm->next->exp > exp)
			pTmpTerm = pTmpTerm->next;
		else if (pTmpTerm->next->exp == exp) {
			pTmpTerm->next->coeff += coeff;
			break;
		}
		else {
			pNewTerm->next = pTmpTerm->next;
			pTmpTerm->next = pNewTerm;
			break;
		}
	}

	if (pTmpTerm->next == NULL) {
		pNewTerm->next = pTmpTerm->next;
		pTmpTerm->next = pNewTerm;
	}
}
poly multiPoly(poly A, poly B) {
	poly multiPoly;
	int exp, coeff;
	multiPoly.head = new polyTerm;
	multiPoly.head->next = NULL;

	polyTerm* ATerm = A.head->next;
	while (ATerm != NULL) {
		polyTerm* BTerm = B.head->next;
		while (BTerm != NULL) {
			exp = ATerm->exp + BTerm->exp;
			coeff = ATerm->coeff * BTerm->coeff;
			addTerm(&multiPoly, exp, coeff);
			BTerm = BTerm->next;
		}
		ATerm = ATerm->next;
	}
	return multiPoly;
}

void printPoly_impl(poly A, char* buffer) {
	char temp[10];
	int isFirst = 0;
	polyTerm* pTmpTerm = NULL;
	pTmpTerm = A.head->next;

	if (pTmpTerm == NULL) {
		strcat(buffer, "0");
		return;
	}

	while (pTmpTerm != NULL) {
		if (pTmpTerm->coeff == 0) {
			pTmpTerm = pTmpTerm->next;
			if (pTmpTerm == NULL)
				strcat(buffer, "0");
			continue;
		}
		else if (pTmpTerm->coeff > 0) {
			if (isFirst)
				strcat(buffer, "+");
		}
		sprintf(temp, "%dx^%d",
			pTmpTerm->coeff, pTmpTerm->exp);
		strcat(buffer, temp);
		pTmpTerm = pTmpTerm->next;
		isFirst = 1;
	}
}
void printPoly(poly A) {
	char buffer[BUFFSIZE] = "";
	printPoly_impl(A, buffer);
	printf(buffer);
}

poly createPoly() {
	poly pPoly;
	pPoly.head = new polyTerm;
	pPoly.head->next = NULL;
	return pPoly;
}