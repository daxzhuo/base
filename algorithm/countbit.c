#include <stdio.h>

int countbit(int *a) {
  int count = 0;
  for (int n = *a; n!= 0; ++a) {
    n &= n-1;
    count++;
  }
  return count;
}

int main() {
  short a[] = { 100, 101 };
  printf("%d\n",countbit((int*)a));
}
  
