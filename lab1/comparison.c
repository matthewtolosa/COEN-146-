/* Matthew Tolosa
 Date: 9/25/20 
Title: Lab 1, Part 2
Description: Demonstrating the quantitative comparisons btwn packet and circuit switching */


/* Factorial function, for part 7g */ 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


double factorial(double n) {
	if (n <= 1){
		return 1;
	}
	else {
		return n * factorial(n-1);
	}
}



int main(int argc, char *argv[]) {
	/* Variables */
	int nPSusers, linkBandwidth, userBandwidth, nCSusers,i;
	double tPSusers, pPSusersBusy, pPSusersNotBusy, pPSusers; 

	linkBandwidth = atoi(argv[1]);
	userBandwidth = atoi(argv[2]);
	nPSusers= atoi(argv[3]);
	tPSusers = atof(argv[4]);
	//matty = atoi(argv[5]);	
	
	//printf("Argumnent count: %d \n",argc);
	printf("linkBandwidth: %d \n", linkBandwidth);
	printf("userBandwidth: %d \n", userBandwidth);
	printf("nPSusers: %d \n", nPSusers);
	printf("tPSusers: %f \n", tPSusers);
	//printf("Argument 3 passed to tPSusers: %s \n",argv[3]);	
	//printf("Argument 4 passed to nPSusers: %s \n", argv[4]);
	
	
	//6a: Circuit Switching Scenario 
	nCSusers = linkBandwidth / userBandwidth; 
	printf("6a: The number of circuit-switched users that can be supported: %d \n", nCSusers);

	
	//Question 7 and its parts 
	
	//7. Packet Switching Scenarios
	
	//7a. 
	pPSusers = tPSusers; 
	printf("7a: The probability that a given (specific) user is busy transmitting: %f \n", pPSusers);
	
	//7b.
	pPSusersNotBusy = 1 - pPSusers; 
	printf("7b: The probability that one specific other user is not busy: %f \n", pPSusersNotBusy);

	//7c. 
	double pAllNotBusy = pow((1 - pPSusers), nPSusers - 1);
	printf("7c: The probability that all of the other specific other users are not busy: %e \n", pAllNotBusy);

	//7d. 
	double pOneBusy = pow(pPSusers, 1) * pow(pPSusersNotBusy, nPSusers - 1); 
	printf("7d: The probability that one specific user is transmitting and the remaining users are not transmitting: %e \n", pOneBusy);

	//7e. 
	double pExactlyOne = nPSusers * (pow(pPSusers, 1) * pow(pPSusersNotBusy, nPSusers - 1));
	printf("7e: The probability that exactly one (any one) of the nPSusers users is busy: %le \n", pExactlyOne);

	//7f.
	double pTenBusy = pow(pPSusers, 10) * pow(pPSusersNotBusy, nPSusers - 10);
	printf("7f: The probability that 10 specific users of nPSusers are transmitting: %lg \n", pTenBusy);

	//7g. 
	double pAnyTen =((factorial(nPSusers))/(factorial(10)) * (factorial(nPSusers - 10))) * ((pow(pPSusers, 10)) * (pow(pPSusersNotBusy, nPSusers - 10))) ;
	printf("7g: The probability that any 10 users of nPSusers are transmitting: %lg \n", pAnyTen);  
	 
	//7h. 
	double pTenMoreBusy = 0.0;
	for (i = 11; i < nPSusers; i++){
		pTenMoreBusy += factorial(nPSusers)/(factorial(i)*factorial(nPSusers - i)) * pow(pPSusers, i) * pow(pPSusersNotBusy, nPSusers - i);
	}
	printf("7h: The probability that more than 10 users of nPSusers are transmitting and the others are idle: %lg \n", pTenMoreBusy);

	return 0;
}


	

	
