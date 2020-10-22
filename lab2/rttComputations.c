/*Matthew Tolosa
Date: 10/02/20 
Description: To compute the RTT based on diff. scenarios */

#include <stdlib.h>
#include <stdio.h> 
#include <math.h>

int main (int argc,char *argv[]) {

     double numObj = atoi(argv[1]);
     double numParallel = atoi(argv[2]);
     double n; /*number of RTTHTTP required */
     int RTT0 = 3;
     int RTT1 = 20;
     int RTT2 = 26;
     int RTTHTTP = 47;

     int totalRTT = RTT0 + RTT1 + RTT2;

     printf("Time elapsed to receive HTML object = %d msec \n", totalRTT + (2*RTTHTTP)); /* part a */

     printf("Time elapsed to receive HTML object and six small objects = %d msec \n", totalRTT + (2*RTTHTTP) + (6*(2*RTTHTTP))); /* part b */

     printf("numObj: %f \n", numObj);
     printf("numParallel: %f \n", numParallel);
     //printf("n: %f \n", n);
     n = ceil(numObj / numParallel); 
     printf("n after computation: %f \n", n);
     //printf("n after ceil function: %f \n", n);

     printf("%f Parallel Connections - Persistent  = %f msec \n", numParallel , totalRTT + (2*RTTHTTP) + (n*RTTHTTP));
     printf("%f Parallel Connections - Non-Persistent  = %f msec \n", numParallel , totalRTT + (2*RTTHTTP) + (2*n*RTTHTTP));

     return 0;

}
