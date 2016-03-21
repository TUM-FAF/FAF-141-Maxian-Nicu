#include "polish.h"

int main(int argc,char** argv){
	try {
		if(argc > 1)
			printf("%f",compute(reversePolish(argv[1])));		
		else
			printf("No input");
	} catch(const char* msg){
		printf("Error : %s",msg);
	}
	return 0;
}

