#include <stdio.h>
#include <unistd.h>
int main (void)
{
 int i = 999; 
 int j = 1000;
 i = fork();
 printf ("A. i,j: %d,%d\n",i,j);
 j = fork();
 printf ("B. i,j: %d,%d\n",i,j);
 if ( i == 0 )
 {
 if ( j == 0 ) while (1);
 else while (1);
 }
 else
 {
 sleep(1);
 printf ("C. i,j: %d,%d\n",i,j);
 if ( j == 0 )
 {
 sleep(3);
 execlp("ps", "ps", NULL);
 printf ("Embedded\n");
 }
 else
 {
 wait(NULL);
 printf ("System\n");
 } 
 }
}