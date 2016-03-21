#include "polish.h"
#define PARANTHESIS_ERROR "Paranthesis error"
#define FUNCTION_ERROR "Function error"
#define WRONG_INPUT "Wrong input"

bool isNegativeNumber(int pos,const char* expr);

bool isOperator(int pos,const char* expr){
	char c = expr[pos];
	for(int i = 0; i < operatorsCount;i++)
		if(operators[i].sym == c)
			return true;
	return false;
}

bool isNumber(int pos,const char* expr){
	//check for negative numbers
	return isdigit(expr[pos]) || (isNegativeNumber(pos,expr));
}

bool isNegativeNumber(int pos,const char* expr){
	if(pos == 0 && expr[pos] == '-' && isNumber(pos+1,expr))
		return true;


	if(((expr[pos-1] == '(' || expr[pos-1] == ',') && expr[pos] == '-' && isNumber(pos+1,expr)))
		return true;

	return false;
}

bool isParanthesis(int pos,const char* expr){
	return expr[pos] == '(' || expr[pos] == ')';
}

char* getFunctionName(int pos,const char* expr){
	char fname[10] = "";
	int id = 0;
	while(isalpha(expr[pos])){
		fname[id++] = expr[pos];
		pos++;
	}
	fname[id] = '\0';

	char* point = new char[strlen(fname)+1];
	strcpy(point,fname);

	return point;
}

bool isFunction(int pos,const char* expr){
	char *fname = getFunctionName (pos,expr);

	for(int i = 0; i < functionsCount ;i++){
		if(strcmp(functions[i].name,fname) == 0)
			return true;
	}
	
	return false;
}

val* parseNumber(int& pos,const char* expr){
	int sign = 1;

	//finding sign
	if (isNegativeNumber(pos,expr)){
		pos++;
		sign *= -1;
	}
	
	val* temp = new val;
	double *number = new double;
	double fractionary = 1;
	bool pointFound = false;
	
	temp->t = NUMBER;
	*number = 0;
	while(isNumber(pos,expr)){
		if(pointFound){
			fractionary = fractionary/10;
			*number = *number + (fractionary * (expr[pos] - '0'));
		} else
			*number = *number * 10 + expr[pos] - '0';
		pos++;
		if(expr[pos] == '.'){
			pointFound = true;
			pos++;
		}
	}
	*number = *number * sign;
	temp->value = number;
	
	return temp;
}

val* parseOperator(int& pos,const char* expr){
	val* temp = new val;
	temp->t = OPERATOR;
	char *op = new char;
	*op = expr[pos++];
	temp->value = op;
	
	return temp;
}

val* parseParanthesis(int& pos,const char* expr){
	val* temp = new val;
	temp->t = expr[pos++] == '(' ? OPEN_PARENTHESIS : CLOSE_PARANTHESIS;
	
	return temp;
}

func* parseFunction(int& pos,const char* expr){
	char *fname = getFunctionName(pos,expr);
	pos += strlen(fname);
	for(int i = 0; i < functionsCount; i++){
		if(strcmp(functions[i].name,fname) == 0)
			return &(functions[i]);
	}

	return &(functions[0]);
}

op findOperator(char ch){
	for(int i = 0; i < operatorsCount;i++)
			if(operators[i].sym == ch)
				return operators[i];
	return operators[0];
}

std::stack<val*>* reversePolish(const char* expr){
	std::stack<val*> *temp = new std::stack<val*>();
	std::stack<val*> *operatorStack = new std::stack<val*>();
	char *str = new char[strlen(expr)+1];
	strcpy(str,expr);
	str[strlen(expr)] = '\0';
	str = reformat(str);
	
	int len = strlen(str);
	int i = 0;
	while(i < len){
		if(isNumber(i,str)){
			temp->push(parseNumber(i,str));
		} else if(isOperator(i,str)){
			val* o = parseOperator(i,str);
			op op1 = findOperator (str[i-1]);
			while(!operatorStack->empty() && operatorStack->top()->t == OPERATOR){
				val* o2 = operatorStack->top();
				op op2 = findOperator (*((char*)o2->value));
				if(op1.prec <= op2.prec && op1.as == LEFT || 
				   op1.prec < op2.prec && op1.as == RIGHT){
					temp->push(operatorStack->top());
					operatorStack->pop();
				} else
					break;
			}
			operatorStack->push(o);
			
		} else if(isParanthesis (i,str)){
			val* val = parseParanthesis (i,str);
			if(val->t == CLOSE_PARANTHESIS) {
				while(operatorStack->top()->t != OPEN_PARENTHESIS){
					temp->push(operatorStack->top());
					operatorStack->pop();
					if(operatorStack->empty()){
						throw PARANTHESIS_ERROR;
					}
				}
				operatorStack->pop();
				if (operatorStack->top()->t == FUNCTION){
					temp->push(operatorStack->top());
					operatorStack->pop();
				}
			} else {
				operatorStack->push(val);
			}
		} else if(expr[i] == ','){
			if(operatorStack->empty())
				throw FUNCTION_ERROR;
			while(operatorStack->top()->t != OPEN_PARENTHESIS){
				temp->push(operatorStack->top());
				operatorStack->pop();
				if(operatorStack->empty()){
					throw FUNCTION_ERROR;
				}
			}
			i++;
		} else if(isFunction(i,str)){
			val* value = new val;
			value->t = FUNCTION;
			value->value = parseFunction (i,str);

			operatorStack->push(value);
		} else {
			throw WRONG_INPUT;
		}
	}

	while(!operatorStack->empty()){
		if(operatorStack->top()->t == OPEN_PARENTHESIS || 
		   operatorStack->top()->t == CLOSE_PARANTHESIS)
			throw PARANTHESIS_ERROR;
		temp->push(operatorStack->top());
		operatorStack->pop();
	}
	
	return temp;
}

void printStack(std::stack<val*>* res){
	printf("Stack is : \n");
	printf("------------------------\n");
	while(!res->empty()){
		val* val = res->top();
		if(val->t == NUMBER){
			printf("%20.3f\n",*((double*)val->value));
		}
		if(val->t == OPERATOR){
			printf("%20c\n",*((char*)val->value));
		}
		if(val->t == FUNCTION){
			printf("%20s\n",((func*)val->value)->name);
		}
		res->pop();
	}
	printf("------------------------\n");
}

double compute(std::stack<val*>* res){
	if(res->empty())
		throw WRONG_INPUT;
	
	if(res->top()->t == OPERATOR){
		char sg = *((char*)(res->top()->value));
		res->pop();
		double a = compute(res);
		double b = compute(res);
		switch(sg){
			case '+': 
				return b+a;
			case '-':
				return b-a;
			case '/':
				return b/a;
			case '*':
				return b*a;
			default :
				return 0;
		}
	} else if (res->top()->t == FUNCTION){
		func *fn = (func*)res->top()->value;
		res->pop();
		double arr[fn->operandsCount];
		for(int i = 0;i < fn->operandsCount;i++){
			arr[i] = compute(res);
		}
		return fn->f(arr,fn->operandsCount);
	} else {
		double value = *((double*)(res->top()->value));
		res->pop();
		
		return value;
	}
	
	return 0;
}
