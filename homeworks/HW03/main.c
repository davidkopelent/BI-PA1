#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int LeapYear ( int y )
{   
    int days_in_month;

    if ( (y % 4 == 0) && ((y % 400 == 0) || (y % 100 != 0)) ) {
        if (y % 4000 == 0) {
            days_in_month = 28;
        } else {  
            days_in_month = 29;
        }
    } else {
        days_in_month = 28;
    }

    return days_in_month;
}

int CountDaysInMonth ( int y, int m )
{
    int days_in_month;

    if ( m == 4 || m == 6 || m == 9 || m == 11 ) {
        days_in_month = 30;
    } else if ( m == 2 ) {
        days_in_month = LeapYear ( y );
    } else {
        days_in_month = 31;
    }

    return days_in_month;
}

int CheckDay ( int y, int m, int d )
{
    int weekday = (d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;

    if (weekday == 0) {
        return 0;
    } else {
        return 1;
    }
}

int CountMinutes ( int min, int max, int k )
{
    int t = 0;

    for ( int i = min; i <= max; i += 15 ) {
        t = t + k;

        if ( k % 4 == 0 ) {
            k = 0;
        }
        
        k = k + 1;
    }

    return t;
}

int CountHours ( int min, int max, int k )
{
    int t = 0;

    for ( int i = min; i <= max; i++ ) {
        t = t + k;

        if ( k % 12 == 0 ) {
            k = 0;
        }
        
        k = k + 1;
    }

    return t;
}

int Validation ( int y1, int m1, int d1, int h1, int i1, int y2, int m2, int d2, int h2, int i2 ) {
    if ( y1 < 1600 || y2 < 1600 ) {
        return 0;
    } else if ( m1 > 12 || m2 > 12 || m1 < 1 || m2 < 1 || d1 < 1 || d2 < 1 || d1 > CountDaysInMonth ( y1, m1 ) || d2 > CountDaysInMonth ( y2, m2 ) ) {
        return 0;
    } else if ( h1 > 23 || h2 > 23 || h1 < 0 || h2 < 0 || i1 > 59 || i2 > 59 || i1 < 0 || i2 < 0 ) {
        return 0;
    } else {
        return 1;
    }
}

int bells ( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2,
            long long int * b1, long long int * b2 )
{
    /* todo */
    int days = 0;
    
    if ( Validation ( y1, m1, d1, h1, i1, y2, m2, d2, h2, i2 ) == 1 ) {
        if ( y1 == y2 && m1 == m2 && d1 == d2 && h1 == h2 && i1 == i2 ) {
            if ( CheckDay ( y1, m1, d1 ) == 1 ) {
                *b1 = 4;
                *b2 = 12;
            } else {
                *b1 = 0;
                *b2 = 0;
            }
        } else { 
            if (y1 > y2) 
                return 0;

            if (y1 == y2) {
                if (m1 > m2)
                    return 0;

                if (m1 == m2) {
                    if (d1 > d2)
                        return 0;

                    if (d1 == d2) {
                        if (h1 > h2)
                            return 0;

                        if (h1 == h2 && i1 > i2)
                            return 0;

                        if ( CheckDay ( y1, m1, d1 ) == 1 ) {
                            days = 0;
                        }
                    } else {
                        for ( int i = (d1 + 1); i < d2; i++ ) {
                            days += CheckDay ( y1, m1, i );
                        }
                        
                        if ( ((24 - h1) + h2) < 24 ) {
                            days = 0;
                        }
                    }
                } else {
                    for ( int i = (d1 + 1); i <= CountDaysInMonth ( y1, m1 ); i++ ) {
                        days += CheckDay ( y1, m1, i );
                    }
                    
                    for ( int i = 1; i < d2; i++ ) {
                        days += CheckDay ( y1, m2, i );
                    }

                    for ( int i = (m1 + 1); i < m2; i++ ) {
                        for ( int j = 1; j <= CountDaysInMonth ( y1, i ); j++ ) {
                            days += CheckDay ( y1, i, j );
                        }
                    }
                }
            } else {
                for ( int i = (y1 + 1); i < y2; i++ ) {
                    for ( int j = 1; j <= 12; j++ ) {
                        for ( int k = 1; k <= CountDaysInMonth ( i, j ); k++ ) {
                            days += CheckDay ( i, j, k );
                        }
                    }
                }

                for ( int i = d1; i <= CountDaysInMonth ( y1, m1 ); i++ ) {
                    days += CheckDay ( y1, m1, i );
                }

                for ( int i = 1; i < d2; i++ ) {
                    days += CheckDay ( y1, m2, i );
                }

                for ( int i = (m1 + 1); i <= (m2 - 1); i++ ) {
                    for ( int j = 1; j <= CountDaysInMonth ( y1, i ); j++ ) {
                        days += CheckDay ( y1, j, i );
                    }
                }
            }
        
            int min_1 = h1 * 60 + i1;
            int max_1 = (d1 == d2) ? (h2 * 60 + i2) : 1440 + (h2 * 60 + i1);
            int k_1 = (i1 == 0) ? 4 : i1 / 15;
            
            if ( CheckDay ( y1, m1, d1 ) == 0 ) {
                min_1 = 0;
                max_1 = h2 * 60 + i2;
                k_1 = 4;
            }

            if ( CheckDay ( y2, m2, d2 ) == 0 ) {
                max_1 = (d2 > d1 + 1) ? h1 * 60 + i1 : 1440 - 15;
            }
        
            *b1 = days * 240 + CountMinutes ( min_1, max_1, k_1 );

            int min_2 = (i1 > 0) ? h1 + 1 : h1;
            int max_2 = (d1 == d2) ? h2 : 24 + h2;
            int k_2 = (min_2 > 12) ? min_2 - 12 : min_2;
            k_2 = (k_2 == 0) ? 12 : k_2;

            if ( CheckDay ( y1, m1, d1 ) == 0 ) {
                min_2 = 0;
                max_2 = h2;
                k_2 = (h2 == 0) ? 12 : (i2 > 0) ? h2 + 1 : h2;
            }

            if ( CheckDay ( y2, m2, d2 ) == 0 ) {
                max_2 = (d2 > d1 + 1) ? 0 : 23;
            }

            *b2 = days * 156 + CountHours ( min_2, max_2, k_2 );
        }
        
        return 1;
    } else {
        return 0;
    }
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int b1, b2;

  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  1, 18, 45, &b1, &b2 ) == 1
           && b1 == 56
           && b2 == 20 );
  assert ( bells ( 2022, 10,  3, 13, 15,
                   2022, 10,  4, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  2, 11, 20, &b1, &b2 ) == 1
           && b1 == 106
           && b2 == 65 );
  assert ( bells ( 2022, 10,  2, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 115
           && b2 == 78 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022,  1,  1, 13, 15,
                   2022, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 56861
           && b2 == 36959 );
  assert ( bells ( 2019,  1,  1, 13, 15,
                   2019, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 );
  assert ( bells ( 2024,  1,  1, 13, 15,
                   2024, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57341
           && b2 == 37271 );
  assert ( bells ( 1900,  1,  1, 13, 15,
                   1900, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 );
  assert ( bells ( 2022, 10,  1,  0,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 124
           && b2 == 90 );
  assert ( bells ( 2022, 10,  1,  0, 15,
                   2022, 10,  1,  0, 25, &b1, &b2 ) == 1
           && b1 == 1
           && b2 == 0 );
  assert ( bells ( 2022, 10,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 11,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 10, 32, 12,  0,
                   2022, 11, 10, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2100,  2, 29, 12,  0,
                   2100,  2, 29, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2000,  2, 29, 12,  0,
                   2000,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2004,  2, 29, 12,  0,
                   2004,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 0
           && b2 == 0 );
  assert ( bells ( 2004,  2, 30, 12,  0,
                   2004,  2, 29, 12,  0, &b1, &b2 ) == 0
           && b1 == 0
           && b2 == 0 );
  assert ( bells ( 2005,  1, 1, 0,  0,
                   2005,  1, 1, 1,  0, &b1, &b2 ) == 1
           && b1 == 14
           && b2 == 13 );
  assert ( bells ( 2100, 12, 19, 0, 0, 
                   2100, 12, 24, 0, 0, &b1, &b2 ) == 1
           && b1 == 964
           && b2 == 636 );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */ 