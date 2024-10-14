#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct plane {
    double x;
    double y;
    char name[200];
} plane;

void FreeMemory1 ( plane * ptr, int cnt ) {
    free(ptr);
}

void FreeMemory2 ( char ** planes, int count ) {
    for ( int i = 0; i < 2 * count; i++ ) { 
        free(planes[i]);
    }
    free(planes);
}

double CountDistance ( double x1, double x2, double y1, double y2 ) {
    double vector1 = (double) pow ( (x2 - x1), 2 );
    double vector2 = (double) pow ( (y2 - y1), 2 );
    double distance = (double) sqrt ( vector1 + vector2 );
    return distance;
}

double CountClosestDistance ( plane * ptr, int cnt ) {
    double distance, shortest_distance = 0;
    for ( int i = 0; i < cnt; i++ ) {
        for ( int j = i + 1; j < cnt; j++ ) {
            distance = CountDistance ( ptr[i].x, ptr[j].x, ptr[i].y, ptr[j].y );

            if ( i == 0 && j == 1 ) {
                shortest_distance = distance;
            } else if ( distance < shortest_distance ) {
                shortest_distance = distance;
            }
        }
    }

    return shortest_distance;
}

void PrintResults ( char ** planes, int count ) {
    int index1 = 0, index2 = 1;

    printf("Nalezenych dvojic: %d\n", count);
    for ( int i = 0; i < count; i++ ) {
        printf("%s - %s\n", planes[index1], planes[index2]);
        index1 += 2; index2 += 2;
    }

    FreeMemory2 ( planes, count );
}

void FindPlanesByDistance ( plane * ptr, int cnt, double dst ) {
    int count = 0, index1 = 0, index2 = 1;
    double distance;
    char ** planes = (char**) malloc ( sizeof (char*) * 100 );
    
    double Epsilon = (dst < 0.1) ? 1.0e-34 : 1.0e-08;
    for ( int i = 0; i < cnt; i++ ) {
        for ( int j = i + 1; j < cnt; j++ ) {
            distance = CountDistance ( ptr[i].x, ptr[j].x, ptr[i].y, ptr[j].y );

            if ( distance == dst || distance - dst <= Epsilon ) {
                if ( count % 50 == 0 ) {
                    planes = (char**) realloc ( planes, sizeof (char*) * (100 + 2 * count) );
                }

                planes[index1] = (char*) malloc( strlen(ptr[i].name) + 1 );
                strcpy(planes[index1], ptr[i].name);

                planes[index2] = (char*) malloc( strlen(ptr[j].name) + 1 );
                strcpy(planes[index2], ptr[j].name);

                index1 += 2; index2 += 2; count++;
            }
        }
    }

    PrintResults ( planes, count );
}

int CheckInput ( int input, char delimiter1, char delimiter2, char * plane ) {
    if ( input != 5 || delimiter1 != ',' || delimiter2 != ':' || strlen(plane) > 199 )
        return 0;
    return 1;
}

int main ( int argc, char * argv[] ) {
    int count = 0;
    int input;
    char delimiter1, delimiter2;

    plane * ptr;
    ptr = (plane*) malloc ( sizeof (plane*) + (2 * sizeof(double) + 200 * sizeof(char)) * 100 );

    printf("Pozice letadel:\n");
    while ( (input = scanf("%lf %c %lf %c %s", 
             &ptr[count].x, &delimiter1, &ptr[count].y, &delimiter2, ptr[count].name)) != EOF ) {  

        if ( ! CheckInput ( input, delimiter1, delimiter2, ptr[count].name ) ) {
            printf("Nespravny vstup.\n");
            FreeMemory1 ( ptr, count );
            return 1;
        }

        if ( count % 50 == 0) {
            ptr = (plane*) realloc ( ptr, sizeof (plane*) + (2 * sizeof(double) + 200 * sizeof(char)) * (100 + 2 * count) );
        }

        count++;
    }

    if ( count < 2 ) {
        printf("Nespravny vstup.\n");
        FreeMemory1 ( ptr, count );
        return 1;
    }

    if ( !feof(stdin) ) {
        printf("Nespravny vstup.\n");
        FreeMemory1 ( ptr, count );
        return 1;
    }

    double distance = CountClosestDistance ( ptr, count );
    printf("Vzdalenost nejblizsich letadel: %lf\n", distance);

    FindPlanesByDistance ( ptr, count, distance );
    FreeMemory1 ( ptr, count );
    return 0;
}