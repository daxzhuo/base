#include <assert.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
  int values[] = { 2, 1, 3, 4};
  int elements[] = { 0, 0, 1, 1 };
  const size_t N = sizeof(elements)/sizeof(elements[0]);
  assert(N == sizeof(values)/sizeof(values[0]));
  std::vector<int> selectors(elements, elements+N);

  int count = 0;
  
	  do
	  {
	    std::cout << ++count << ": ";
	    for (size_t i = 0; i < selectors.size(); ++i)
	    {
	      if (!selectors[i])
	      {
	        std::cout << values[i] << ", ";
	      }
	    }
	    std::cout << std::endl;
	  } while (next_permutation(selectors.begin(), selectors.end()));
	
}