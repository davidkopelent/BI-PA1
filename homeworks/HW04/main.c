#include <stdio.h>
#include <stdlib.h>

int Factorial ( int x ) {
    int factorial = (x == 1 || x == 0) ? 1 : x * Factorial ( x - 1 );
    return factorial;
}

int CountCombination ( int x ) {
    int combinations = Factorial ( x ) / (2 * Factorial ( x - 2 ));
    return combinations;
}

int CountFrequency ( int sums[], int n ) {
    int count;
    int total = 0;

    for ( int i = 0; i < n; i++ ) {
        count = 1;
        if ( sums[i] != -1 ) {
            for ( int j = i + 1; j < n; j++ ) {
                if ( sums[i] == sums[j] ) {
                    count++;
                    sums[j] = -1;
                }
            }
		}   
    
        if ( count > 1 ) { 
            total += CountCombination ( count );
        }   
    }
    return total;
}

int Sort ( int * a, int * b ) {
    return ( *b < *a ) - ( *a < *b );
}

int CountSums ( int sequence[], int cnt ) {
    int sums[1000000];
    int n = 0;
    
    for ( int i = 0; i < (cnt - 1); i++ ) {
        int x = i + 1;  

        for ( int j = (cnt - (i + 1)); j > 1; j-- ) {
            int sum = 0;

            for ( int k = i; k <= x; k++ ) {
                sum = sum + sequence[k];
            }

            sums[n] = sum;
            n++; x++;
        }
    }

    qsort ( sums, n, sizeof ( *sums ), (int(*)(const void *, const void *))Sort );
    return CountFrequency ( sums, n );
}

int main ( int argc, char * argv[] ) {
    int sequence[2000];
    int x, input;
    int cnt = 1;
    int i = 0;

    printf("Posloupnost:\n");
    while ( (input = scanf("%d", &x)) != EOF ) {
        if ( input != 1 || i > 1999 ) {
            printf ("Nespravny vstup.\n");
            return 1;
        }
        sequence[i] = x;
        i++;
        cnt++;
    }
    
    if ( !feof(stdin) ) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    
    if ( !sequence[0] ) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Pocet dvojic: %d\n", CountSums ( sequence, cnt ));
    return 0;
}