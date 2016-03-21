#ifndef polish_h
#define polish_h

#include <cstring>
#include <cctype>
#include <stack>
#include <cstdio>
#include "strings.h"
#include "functions.h"

enum type {
	NUMBER,
	OPERATOR,
	OPEN_PARENTHESIS,
	CLOSE_PARANTHESIS,
	FUNCTION
};

enum associativity {
	LEFT,RIGHT
};

struct val {
	type t;
	void *value;
};

struct op {
	char sym;
	int prec;
	associativity as;
};

static op operators[5] = {
	{'-',2,LEFT},
	{'+',2,LEFT},
	{'*',3,LEFT},
	{'/',3,LEFT},
	{'^',4,RIGHT}
};
static int operatorsCount = 5;

std::stack<val*>* reversePolish(const char* expr);
void printStack(std::stack<val*>* res);
double compute(std::stack<val*>* res);

#endif
