/*#include <stdio.h>*/
/*#include <stdlib.h>*/
/*#include <sys/socket.h>*/
/*#include <strings.h>*/
/*#include <string.h>*/
/*#include <arpa/inet.h>*/
/*#include <sys/types.h>*/
/*#include <netdb.h>*/
/*#include <unistd.h>*/

#include <stdio.h>
#include <stdlib.h>
/*#include <sys/socket.h>*/
/*#include <strings.h>*/
/*#include <string.h>*/
/*#include <arpa/inet.h>*/
/*#include <sys/types.h>*/
/*#include <netdb.h>*/
#include "Commands.h"


void AUTHOR(void) {
	printf("[AUTHOR:SUCCESS]\n");
	printf("I, %s, have read and understood the course academic integrity policy.\n", "JaretLyn");
	printf("[AUTHOR:END]\n");
}




void IP(char argument[256]){
	printf("[IP:SUCCESS]\n");
	printf("IP:%s\n", argument);
	printf("[IP:END]\n");
}




void PORT(unsigned int num){
	printf("[PORT:SUCCESS]\n");
	printf("PORT:%u\n", num);
	printf("[PORT:END]\n");
	

	
}





/*void LIST(void){*/
/*	printf("[%s:SUCCESS]\n", Message);*/
/*	printf("Port:%u\n", ntohs(localAddr.sin_port));*/
/*	printf("[%s:END]\n", Message);*/
/*}*/




/*void STATISTICS(void){*/
/*	printf("[%s:SUCCESS]\n", Message);*/
/*	printf("Port:%u\n", ntohs(localAddr.sin_port));*/
/*	printf("[%s:END]\n", Message);*/
/*}*/




/*void BLOCKED(void){*/
/*	printf("[%s:SUCCESS]\n", Message);*/
/*	printf("Port:%u\n", ntohs(localAddr.sin_port));*/
/*	printf("[%s:END]\n", Message);*/
/*}*/




/*void REFRESH(void){*/
/*	printf("[%s:SUCCESS]\n", Message);*/
/*	printf("Port:%u\n", ntohs(localAddr.sin_port));*/
/*	printf("[%s:END]\n", Message);*/
/*}*/




/*void SEND(void){*/
/*	printf("[%s:SUCCESS]\n", Message);*/
/*	printf("Port:%u\n", ntohs(localAddr.sin_port));*/
/*	printf("[%s:END]\n", Message);*/
/*}*/




/*void BROADCAST(void){*/
/*	printf("[%s:SUCCESS]\n", Message);*/
/*	printf("Port:%u\n", ntohs(localAddr.sin_port));*/
/*	printf("[%s:END]\n", Message);*/
/*}*/

/*void BLOCK(void){*/
/*	printf("[%s:SUCCESS]\n", Message);*/
/*	printf("Port:%u\n", ntohs(localAddr.sin_port));*/
/*	printf("[%s:END]\n", Message);*/
/*}*/



/*void UNBLOCK(void){*/
/*	printf("[%s:SUCCESS]\n", Message);*/
/*	printf("Port:%u\n", ntohs(localAddr.sin_port));*/
/*	printf("[%s:END]\n", Message);*/
/*}*/




/*void LOGOUT(void){*/
/*	printf("[%s:SUCCESS]\n", Message);*/
/*	printf("Port:%u\n", ntohs(localAddr.sin_port));*/
/*	printf("[%s:END]\n", Message);*/
/*}*/






/*void EXIT(void){*/
/*	printf("[%s:SUCCESS]\n", Message);*/
/*	printf("Port:%u\n", ntohs(localAddr.sin_port));*/
/*	printf("[%s:END]\n", Message);*/
/*}*/




