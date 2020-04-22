// スコロネック　聖治
// bb35317018


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double ave_online(double val, double previousAverage);
extern double var_online(double val, double ave, double square_ave);


int count = 0;


double ave_online(double val, double previousAverage)
{
    double newAverage = ((double)(count - 1) / (double)count) * previousAverage + (1 / (double)count) * val;

    return newAverage;
}

double var_online(double val, double ave, double square_ave)
{
    double std_dev1 = (((double)(count - 1) / (double)count) * square_ave) + ((1 / (double)count) * pow(val, 2));
    double std_dev2 = pow((((double)(count - 1) / (double)count) * ave) + ((1 / (double)count) * val), 2); 
    double std_dev = std_dev1 - std_dev2;
    
    return std_dev;
}



int main(void)
{
    double val;
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;

    // Initial values of average and standard deviation are set to 0
    double moving_average = 0;
    double moving_std_dev = 0;

    // Have user input a filename to open and read from
    printf("input the filename of sample:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';
    printf("the filename of sample: %s\n",fname);

    // Open up file 
    fp = fopen(fname,"r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }

    while(fgets(buf,sizeof(buf),fp) != NULL){
        // Get every value of file line by line as a double and store it to val
        sscanf(buf,"%lf",&val);

        // Counter to keep track of N
        count ++;

        // Gets the average for N-1 and prints to console
        moving_average = ave_online(val, moving_average);
        printf("Current average: %f\n", moving_average);

        // Gets the moving standard deviation and prints to console
        moving_std_dev = var_online(val, moving_average, pow(moving_average, 2));
        printf("Current standard deviation: %f\n", moving_std_dev);

    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }


    return 0;


}

