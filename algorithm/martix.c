
#include <stdio.h>
#include <stdlib.h>
// exchange row r and row j
int* getMerge(int a[], int b[], int m, int n) {
	// allocate a array to store the result
	int *result = malloc((m+n)*sizeof(int));

	int i, j, k;
	i = j = k = 0;
	for (; j < m && k < n; ++i) {
		if (a[j]<b[k]) {
			result[i] = a[j];
			++j;
		}
		else {
			result[i] = b[k];
			++k;
		}
	}

	if (j < m)
	{
		/* code */
		for (; j < m; ++j, ++i)
			result[i] = a[j];
	}
	if (k < n) {
		for (; k < n; ++k, ++i)
			result[i] = b[k];
	}

	return result;
}

int getMedian(int* arr, int n) {
	if (n == 0)
		return 0;
	if (n % 2 == 0)
		return (arr[n/2]+arr[n/2-1])/2;
	else
		return arr[n/2];
}

int main()
{
    int ar1[] = {1, 12, 15, 26, 38};
    int ar2[] = {2, 13, 19, 30, 45};
 
    int n1 = sizeof(ar1)/sizeof(ar1[0]);
    int n2 = sizeof(ar2)/sizeof(ar2[0]);
    printf("Median is %d", getMedian(getMerge(ar1, ar2, n1, n2), n1 + n2));
   
    return 0;
}