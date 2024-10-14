#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

void FreeMemory ( char ** subs, int count ) {
    for ( int i = 0; i < count; i++ ) {
        free ( subs[i] );
    }
    free ( subs );
}

int getLinesOfArray ( const char * (*replace)[2] ) {
    int lines = 0;
    for ( int i = 0; replace[i][0] != NULL; i++ ) {
        lines++;
    }

    return lines;
}

bool prefixCheck ( const char * replace1, const char * replace2 ) {
    return strncmp ( replace1, replace2, strlen ( replace1 ) ) == 0;
}

int checkPrefixes ( const char * (*replace)[2], int lines ) {
    for ( int i = 0; i < lines; i++ ) {
        for ( int j = i + 1; j < lines; j++ ) {
            if ( prefixCheck ( replace[i][0], replace[j][0] ) ) 
                return 0;
        }
    }
    
    return 1;
}

int checkUsedSubstitution ( const char * replace, char ** subs, int max ) {
    for ( int i = 0; i < max; i++ ) {
        if ( strstr ( subs[i], replace ) != NULL )
            return 0;
    }
    return 1;
}

char * substitute ( char * newspeak, int * newspeak_length, int * newspeak_length_new, const char * string_to_add, int string_length ) {
    if ( *newspeak_length + string_length >= *newspeak_length_new ) {
        *newspeak_length_new = *newspeak_length + string_length;
        newspeak = ( char * ) realloc ( newspeak, *newspeak_length_new * sizeof ( char * ) );
    }
    memcpy ( newspeak + *newspeak_length, string_to_add, string_length );
    *newspeak_length += string_length;
    return newspeak;
}

char * wordSubstitution ( char * newspeak, char * speak, const char * replace, const char * substitution ) {
    char * occurence;
    int newspeak_length = 0;
    int newspeak_length_new = 0;
    int replace_length = strlen ( replace );
    int substitution_length = strlen ( substitution );

    while ( 1 ) {
        occurence = strstr ( speak, replace );
        
        if ( occurence ) {
            newspeak = substitute ( newspeak, &newspeak_length, &newspeak_length_new, speak, occurence - speak );
            newspeak = substitute ( newspeak, &newspeak_length, &newspeak_length_new, substitution, substitution_length );
            speak = occurence + replace_length;
        } else {
            newspeak = substitute ( newspeak, &newspeak_length, &newspeak_length_new, speak, strlen ( speak ) + 1 );
            return newspeak;
        }
    }
}

char * newSpeak ( const char * text, const char * (*replace)[2] ) {
    char * newspeak = ( char* ) malloc ( strlen ( text ) * sizeof ( char* ) + 1 );
    char * speak = NULL;
    int lines = getLinesOfArray ( replace );
    char ** subs = ( char ** ) malloc ( lines * sizeof ( char** ) );
    int cnt = 0;

    strcpy ( newspeak, text );
    
    for ( int i = lines - 1; i >= 0; i-- ) {
        if ( ! checkPrefixes ( replace, lines ) ) {
            free ( newspeak );
            free ( speak );
            FreeMemory ( subs, cnt );

            return NULL;
        }
        
        const char * check = strstr ( newspeak, replace[i][0] );
        if ( check && check[0] == replace[i][0][0] && checkUsedSubstitution ( replace[i][0], subs, cnt ) ) {
            speak = ( char* ) realloc ( speak, strlen ( newspeak ) * sizeof ( char* ) + 1 );
            strcpy ( speak, newspeak );

            subs[cnt] = ( char * ) malloc ( strlen ( replace[i][1] ) * sizeof ( char * ) + 1 );
            strcpy ( subs[cnt], replace[i][1] );

            newspeak = wordSubstitution ( newspeak, speak, replace[i][0], replace[i][1] );
            cnt++;
        }
    }

    free ( speak );
    FreeMemory ( subs, cnt );
    return newspeak;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] ) {
    char * res;

    const char * d1 [][2] =
    {
        { "murderer", "termination specialist" },
        { "failure", "non-traditional success" },
        { "specialist", "person with certified level of knowledge" },
        { "dumb", "cerebrally challenged" },
        { "teacher", "voluntary knowledge conveyor" },
        { "evil", "nicenest deprived" },
        { "incorrect answer", "alternative answer" },
        { "student", "client" },
        { NULL, NULL }
    };

    const char * d2 [][2] =
    {
        { "fail", "suboptimal result" },
        { "failure", "non-traditional success" },
        { NULL, NULL }
    };

    res = newSpeak ( "Everybody is happy.", d1 );
    assert ( ! strcmp ( res, "Everybody is happy." ) );
    free ( res );

    res = newSpeak ( "The student answered an incorrect answer.", d1 );
    assert ( ! strcmp ( res, "The client answered an alternative answer." ) );
    free ( res );

    res = newSpeak ( "He was dumb, his failure was expected.", d1 );
    assert ( ! strcmp ( res, "He was cerebrally challenged, his non-traditional success was expected." ) );
    free ( res );

    res = newSpeak ( "The evil teacher became a murderer.", d1 );
    assert ( ! strcmp ( res, "The nicenest deprived voluntary knowledge conveyor became a termination specialist." ) );
    free ( res );

    res = newSpeak ( "Devil's advocate.", d1 );
    assert ( ! strcmp ( res, "Dnicenest deprived's advocate." ) );
    free ( res );

    res = newSpeak ( "Hello.", d2 );
    assert ( ! res );

    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */