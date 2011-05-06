/***********************************************************/
/*                                                         */
/*               Executor of SP codes                      */
/*               (for usual Dijkstra)                      */
/*                                                         */
/***********************************************************/
/*****THIS CODE HAS BEEN MODIFIED TO PRODUCE PRORITY QUEUE **/
/*****TRACES FOR DIMACS CHALLENGE 5. LOOK FOR challenge5   **/
/*****COMMENTS IN THE CODE.  C. McGeoch 7/96                */



#include <stdio.h>
#include <stdlib.h>

/* statistical variables */
long n_scans = 0;
long n_impr = 0;

/* definitions of types: node & arc */

#include "types_dh.h"

/* parser for getting extended DIMACS format input and transforming the
   data to the internal representation */

#include "parser_dh.c"

/* function 'timer()' for mesuring processor time */

#include "timer.c"

/* function for constructing shortest path tree */

#include "dikh.c"


main ()

{

float t;
arc *arp, *ta;
node *ndp, *source, *k;
long n, m, nmin, i; 
char name[21];
double sum_d = 0;

 parse( &n, &m, &ndp, &arp, &source, &nmin, name );
/*
printf ( "%s\nn= %ld, m= %ld, nmin= %ld, source = %ld\n",
        name,
        n,m,nmin, (source-ndp)+nmin );

printf ("\nordered arcs:\n");
for ( k = ndp; k< ndp + n; k++ )
  { i = (k-ndp)+nmin;
    for ( ta=k -> first; ta != (k+1)-> first; ta++ )
      printf ( " %2ld %2ld %4ld\n",
               i, ((ta->head)-ndp)+nmin, ta->len
             );

  }
*/
t = timer();

dikh ( n, ndp, source );

t = timer() - t;

for ( k= ndp; k< ndp + n; k++ )
  if ( k -> parent != (node*) NULL )
   sum_d += (double) (k -> dist);

/***challenge5 print statement modified to make  comment lines */ 
printf ("\ncom Dijkstra with heap -> problem name: %s\n\n\
com Nodes: %ld    Arcs: %ld\n\
com Number of scans: %ld\n\
com Number of improveness: %ld\n\
com Sum of distances: %.0f\n\n\
com Running time of SP computation: %.2f\n\n",
         name, n, m, n_scans, n_impr, sum_d, t ); 
 
#define nd(ptr) (int)(ptr-ndp+nmin)

/*
for ( k=ndp; k< ndp+n; k++ )
printf (" %d %d %d\n", nd(k), nd(k->parent), k->dist);
*/
}

