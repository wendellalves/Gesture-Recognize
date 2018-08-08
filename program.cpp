#include <list>
#include "program.h"

void pulaAteC(int& PC, std::list<char> CMDs){
	int cont = -1;    
	while(1){ 
		if(CMDs[PC] == 'L' || CMDs[PC] == 'I'){
			cont ++;
		}else if(CMDs[PC] == 'C' && cont > 0){
			cont --;
		}else if(CMDs[PC] == 'C' && cont == 0){
			break;
		}
		PC++;
	}
} 	
bool ifLOOP(char COND){
    switch(COND){
        case 'Y':
            return true;
        break;
        case 'N':
            return false;
        break;
    }
}
bool ifIF(char COND){
    switch(COND){
        case 'Y':
            return true;
        break;
        case 'N':
            return false;
        break;
    }
}