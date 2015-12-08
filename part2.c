#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*int findlargest(int *numbers, int size) {
  int largestint = -1;
  for (int i = 0; i < size; ++i)
    if (largestint < numbers[i])
      largestint = numbers[i];
  return largestint;
}*/

void radixSort(int *array, int size) {
  int *halfSorted = malloc(sizeof(int)*size);
  for (int sigDigit = 1; sigDigit <= 1000000; sigDigit *= 10) {
    int bucket[10] = { 0 };
    for (int i = 0; i < size; ++i) 
      bucket[(array[i]/sigDigit) % 10]++;
    for (int i = 1; i < 10; ++i)
      bucket[i] += bucket[i-1];
    for (int i = size - 1; i >=0; --i)
      halfSorted[--bucket[(array[i]/sigDigit) % 10]] = array[i];
    for (int i = 0; i < size; ++i)
      array[i] = halfSorted[i];
  }
  free(halfSorted);
}

int main(int argc, char const *argv[])
{
  if (argc != 3)
  {
    fprintf(stderr, "Incorrect number of arguments! Please use 'part2 <# of items> <filename>'\n");
  } else if (access(argv[2], F_OK) == -1) {
    fprintf(stderr, "%s was not found! Make sure this file exists and can be read from.\n", argv[2]);
  } else {
    FILE *fp;
    fp = fopen(argv[2], "r");
    int size = atof(argv[1]);
    int *numbers = malloc(sizeof(int)*size);
    for (int i = 0; i < size; ++i)
    {
      fscanf(fp, "%d", &numbers[i]);
    }

    // Do a radix sort
    radixSort(&numbers[0], size);

    // Find the number at the start of the 90th %ile
    int i = (int)(0.9*size);
    int ninetithnum = numbers[i];
    // Find the next number larger than that number
    if (i != size - 1)
      while (ninetithnum == numbers[i]) 
        i++;

    printf("%d\n", numbers[i]);

    free(numbers);
    fclose(fp);
  }
  return 0;
}