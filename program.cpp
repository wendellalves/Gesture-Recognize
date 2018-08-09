#include "program.h"

void Program::pulaAteC(int& PC, char CMDs[]){
	int cont = -1;    
	while(1){ 
		if(CMDs[PC] == 'l' || CMDs[PC] == 'i'){
			cont ++;
		}else if(CMDs[PC] == 'c' && cont > 0){
			cont --;
		}else if(CMDs[PC] == 'c' && cont == 0){
			break;
		}
		PC++;
	}
} 	
bool Program::ifLOOP(char COND){
    switch(COND){
        case 'Y':
            return true;
        break;
        case 'N':
            return false;
        break;
    }
}
bool Program::ifIF(char COND){
    switch(COND){
        case 'Y':
            return true;
        break;
        case 'N':
            return false;
        break;
    }
}