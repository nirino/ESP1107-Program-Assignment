#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI acos(-1.0)

#define L2 0.12
#define L3 0.26
#define W2 1.6

double fprime(int time_int)		/*Functions, derivation of theta 2*/
{
	double y = W2;
	return y;
}

double f2prime(double f_prev, double f2_prev)		/* Functions, derivation of theta 3*/
{
	if (f2_prev == 0) 				/*An error that will never happen at given L2 and L3, triggers when theta 3 = 0/division by zero*/
	{
		f2_prev += 1e-304;
	}
	double y = -(L2)*(W2)*cos(f_prev)/(L3)/cos(f2_prev);
	return y;
}

double modulo(double x, double y)  	/*general fn to create modulus for doubles. works with negative numbers. */
{									/*May introduce err, albeit minimal*/
	if (y<0)
	{
		y = -y;
	}
	x = x - (floor(x/y)) * y;
	return x;
}
/* ========================================================================================== */
int main (void)
{
	double * val, * val2;												/*Declarations, memory*/
	double fprime(int),f2prime(double,double), modulo(double,double);	/*Declarations, functions*/
	double val_init = -42.4242, time_step = -0.044224422;				/*Declarations, input defaults*/
	FILE * spam;														/*Declarations, file I/O*/
	int qa, time_max = -424242;											/*Declarations, dummy var and input default*/
	char empty_char = '\0';												/*Declarations, dummy var*/
	
	/*================================================================================================== */
	printf("Inputs:\n  1) Initial Theta2 (degrees)\n  2) Time step (second)\n  3) No. of Intervals.\n");
	printf("Time step of = 0.0010 is recommended\n");
	
	printf("====================================\n");					/*Input: Theta2, time (step*interval)*/
	scanf("%lf",&val_init);
	scanf("%lf",&time_step);
	scanf("%d%c",&time_max, &empty_char);
	
	
	/* ============================================================================================ */
	if ((time_max == -424242) || (empty_char != '\n') || (val_init == -42.4242)	|| (time_step == -0.044224422))	
	/*Error Handling, invalid input*/
	{
		spam = fopen("ESP1107_assignment_nicolas.dat","a");
		fprintf(spam,"Error: Incorrect Input Type");
		printf("Error: Incorrect Input Type");
		fprintf(spam,"\n\n\n====================================\n");
		fclose(spam);
		return 0;
	}
	if (time_step == 0)
	{
		spam = fopen("ESP1107_assignment_nicolas.dat","a");
		fprintf(spam,"Error: One does not simply stop entropy");
		printf("Error: One does not simply stop entropy");
		fprintf(spam,"\n\n\n====================================\n");
		fclose(spam);
		return 0;
	}
	if (time_max == 0)
	{
		spam = fopen("ESP1107_assignment_nicolas.dat","a");
		fprintf(spam,"Error: Why do you even need this program?");
		printf("Error: Why do you even need this program?");
		fprintf(spam,"\n\n\n====================================\n");
		fclose(spam);
		return 0;
	}
	if (((time_step < 0.0) ^ (time_max < 0.0)) == 1)					/*Error Handling, negative time*/
	{
		spam = fopen("ESP1107_assignment_nicolas.dat","a");
		fprintf(spam,"Error: Does not support turning back time");
		printf("Error: Does not support turning back time");
		fprintf(spam,"\n\n\n====================================\n");
		fclose(spam);
		return 0;
	}
	if (((time_max < 0.0) && (time_max < 0.0)) == 1)
	{
		spam = fopen("ESP1107_assignment_nicolas.dat","a");
		fprintf(spam,"Error: Travelling backwards in counter-time flow can cause harm for mental health");
		printf("Error: Travelling backwards in counter-time flow can cause harm for mental health");
		fprintf(spam,"\n\n\n====================================\n");
		fclose(spam);
		return 0;
	}
	/*=================================================================================================== */
	val = (double *) malloc((time_max+1)*sizeof(double));			/*Memory Alloc*/
	if (val == NULL)												/*Memory Alloc - Error, Memory unavailable*/
	{
		spam = fopen("ESP1107_assignment_nicolas.dat","a");
		fprintf(spam,"Error: Unable to allocate memory");
		printf("Error: Unable to allocate memory");
		fprintf(spam,"\n\n\n====================================\n");
		fclose(spam);
		return 0;
	}
	val_init = modulo(val_init,360) * PI / 180;
	val[0] = val_init;
	val2 = (double *) malloc((time_max+1)*sizeof(double));
	if (val == NULL)												/*Memory Alloc - Error, Memory unavailable*/
	{
		spam = fopen("ESP1107_assignment_nicolas.dat","a");
		fprintf(spam,"Error: Too much memory needed from my tiny brain");
		printf("Error: Too much memory needed from my tiny brain");
		fprintf(spam,"\n\n\n====================================\n");
		fclose(spam);
		return 0;
	}
	val2[0] = 2 * PI - asin(0.12/0.26*sin(val_init));
	val2[0] = modulo(val2[0], 2*PI);

	/* ============================================================================================================ */
	for (qa = 1; qa <= time_max; qa++)								/*Processes next values*/
	{
		val[qa] = val[qa-1] + fprime(time_step)* time_step;
		val[qa] = modulo(val[qa],2*PI);
		val2[qa] = val2[qa-1] + f2prime(val[qa-1],val2[qa-1]) * time_step;
		val2[qa] = modulo(val2[qa],2*PI);
	}
	/*============================================================================================================= */
	spam = fopen("ESP1107_assignment_nicolas.dat","w");				/*Output*/
	fprintf(spam, "F(0) = %G \n", val_init* 180/PI);
	fprintf(spam, "Time step = %G \n", time_step);
	fprintf(spam, "Time intervals = %i\n\n", time_max);
	fprintf(spam, "t.......w2.............w3.............\n");		/*8 lines for t, 15 for f(t) and g(t)*/

	for (qa = 0; qa <= time_max; qa++)
	{
		fprintf(spam, " %7f %+-14.6e %+-14.6e\n", (qa*time_step),val[qa]*180/PI, val2[qa]*180/PI);
	}
	
	fprintf(spam,"\n====================================\neof");	/*marks end of file with eof*/
	fclose(spam);

	return 0;
}

