
#include <stdlib.h>
 #include <stdio.h>

 
 int main(int argc, char *argv[])
 {
   int a[50][50];
   printf("%ld\n", sizeof(a)/sizeof(a[0][0]));
}
