#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Epsilon 1.0e-11

double AccuracyCheck ( double num )
{
	if ((fabs(num) - floor(num)) >= Epsilon) {
		num = ceil(num);
	} else {
		num = floor(num);
	}
	
	return num;
}

double FindMiddlePoint ( double a, double b, double c ) 
{
	double point;
	
	if ((a < b && a > c) || (a < c && a > b)) {
		point = a;
	} else if ((a > b && b > c) || (b < c && b > a)) {
		point = b;
	} else {
		point = c;
	}	
		
	return point;
}

double CheckVectors ( double x, double a, double u ) 
{
	double t;
	t = AccuracyCheck( (x - a) / u );
	return t;
}

int main ( void )
{
    int oneline_true = 0;
    double a1, a2, b1, b2, c1, c2, t1_b, t2_b, t1_c, t2_c, u1, u2;
    
    printf("Bod A:\n");
    if (scanf("%lf %lf", &a1, &a2) != 2) {
    	printf("Nespravny vstup.\n");
    	return 1;
    }
    
    printf("Bod B:\n");
    if (scanf("%lf %lf", &b1, &b2) != 2) {
    	printf("Nespravny vstup.\n");
    	return 1;
    }
    
    printf("Bod C:\n");
    if (scanf("%lf %lf", &c1, &c2) != 2) {
    	printf("Nespravny vstup.\n");
    	return 1;
    }
    
    if ((a1 == b1 && a2 == b2) || (a1 == c1 && a2 == c2) || (b1 == c1 && b2 == c2)) {
    	printf("Nektere body splyvaji.\n");
    } else {
		if ((a1 == b1 && a1 == c1 && b1 == c1) || (a2 == b2 && a2 == c2 && b2 == c2))
		{
            oneline_true = 1;
			printf("Body lezi na jedne primce.\n");
		} else {
			u1 = AccuracyCheck( fabs(b1 - a1) );
			u2 = AccuracyCheck( fabs(b2 - a2) );
			
			t1_b = CheckVectors( b1, a1, u1 );
			t2_b = CheckVectors( b2, a2, u2 );
			t1_c = CheckVectors( c1, a1, u1 );
			t2_c = CheckVectors( c2, a2, u2 );
			
			if (( t1_b == t2_b && t1_c == t2_c )) {
                oneline_true = 1;
				printf("Body lezi na jedne primce.\n");
			} else {
				printf("Body nelezi na jedne primce.\n");
			}
		}

        if (oneline_true) {
            double mid1 = FindMiddlePoint ( a1, b1, c1 );
            double mid2 = FindMiddlePoint ( a2, b2, c2 );

            if (mid1 == a1 && mid2 == a2) {
                printf("Prostredni je bod A.\n");
            } else if (mid1 == b1 && mid2 == b2) {
                printf("Prostredni je bod B.\n");
            } else if (mid1 == c1 && mid2 == c2) {
                printf("Prostredni je bod C.\n");
            }
        }
    }
    	
	return 0;
}