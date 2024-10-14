#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem {
  struct TItem * m_Next;
  char * m_Name;
  char m_Secret[24];
} TITEM;

int cmpName ( const TITEM * a, const TITEM * b ) {
    return strcmp ( a -> m_Name, b -> m_Name );
}

int cmpNameInsensitive ( const TITEM * a, const TITEM * b ) {
    return strcasecmp ( a -> m_Name, b -> m_Name );
}

int cmpNameLen ( const TITEM * a, const TITEM * b ) {
    size_t la = strlen ( a -> m_Name ), lb = strlen ( b -> m_Name );
    return ( lb < la ) - ( la < lb );
}
#endif /* __PROGTEST__ */

TITEM * newItem ( const char * name, TITEM * next ) {
    TITEM * item = (TITEM*) malloc ( sizeof (TITEM) );
    item -> m_Name = (char*) malloc ( strlen (name) + 1 );
    strcpy ( item -> m_Name, name );
    item -> m_Secret[0] = '\0';
    item -> m_Next = next;
    return item;
}

TITEM * sortListCmp ( TITEM * l, int ascending, int (* cmpFn) ( const TITEM *, const TITEM *) ) {
    TITEM * current = l;
    TITEM * head = NULL;   
    int direction = ( ascending == 0 ) ? -1 : 1;

    while ( current != NULL ) {
        TITEM * nextNode = current -> m_Next;

        if ( head == NULL || cmpFn ( head, current ) * direction > 0 ) {
            current -> m_Next = head;
            head = current;
        } else {
            TITEM * ptr = head;
    
            while ( ptr -> m_Next && cmpFn ( ptr -> m_Next, current ) * direction <= 0 ) {
                ptr = ptr -> m_Next;
            }

            current -> m_Next = ptr -> m_Next;
            ptr -> m_Next = current;
        }
        
        current = nextNode;
    }
    return head;
}

void freeList ( TITEM * src ) {
    for ( TITEM * node = src; node; ) {
        TITEM * next = node -> m_Next;
        free ( node -> m_Name );
        free ( node );
        node = next;
    }
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] ) {
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */