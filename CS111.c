// CS111.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXRANGE 1000
// prototypes
void heap_sort(int array[],int size);
void heapify(int array[],int size);
void adjust(int array[],int size);
void insertion_sort(int array[], int size);
void merge_sort(int i, int j, int array[], int aux[]);
void printArray(int array[], int size);

FILE *fptr;
int main()
{
    int size, i;
    clock_t start, end, elapsed1, elapsed2, elapsed3;
    fptr = fopen("output.txt","w");

    printf("Enter N: ");
    scanf("%d", &size);
    int array[size];
    int aux[size];

    if(size <= 0)
    {
        printf("\n Error!\n");
    }
    for (i = 0; i < size; i++)
    {
        array[i] = rand() % MAXRANGE;

    }
    fprintf(fptr, "Unsorted Array: ");
    for (i = 0; i < size; i++)
    {
        fprintf(fptr, "%d ", array[i]);

    }
    start = clock();
    merge_sort(0, size - 1, array, aux);
    elapsed1 = clock() - start;
    printf("Merge sort time: %f second(s).\n",
           ((double)elapsed1) / CLOCKS_PER_SEC);
    fprintf(fptr, "\n\nMerge Sorted: ");
    printf("Array has been sorted using Merge Sort.\n");
    printArray(array, size);

    start = clock();
    insertion_sort(array, size);
    elapsed2 = clock() - start;
    printf("\n\nInsertion sort time: %f second(s).\n",
           ((double)elapsed2) / CLOCKS_PER_SEC);
    fprintf(fptr, "\n\nInsertion Sorted: ");
    printf("Array has been sorted using Insertion Sort.\n");
    printArray(array, size);

    start = clock();
    heap_sort(array, size);
    elapsed3 = clock() - start;
    printf("\n\nHeap sort time: %f second(s).\n",
           ((double)elapsed3) / CLOCKS_PER_SEC);
    fprintf(fptr, "\n\nHeap Sorted: ");
    printf("Array has been sorted using Heap Sort.");
    printArray(array, size);
    printf("\n");

    return 0;
}

void heap_sort(int array[], int size)
{
  int i, t;
  heapify(array, size);
  // swaps max element with rightmost leaf element
  for (i = size - 1; i > 0; i--)
  {
    t = array[0];
    array[0] = array[i];
    array[i] = t;
    adjust(array,i);
  }
}
// create MAX heap array
void heapify(int array[], int size)
{
  int k, i, j, item;
  for (k = 1; k < size; k++)
  {
    item = array[k];
    i = k;
    j = (i - 1) / 2;
    while((i > 0) && (item > array[j]))
    {
      array[i] = array[j];
      i = j;
      j = (i - 1) / 2;
    }
    array[i] = item;
   }
}
// to heapify or rearrange again to max heap array
void adjust(int array[], int size)
{
	int i, j = 0, item;

	item = array[j];
  i = 2 * j + 1;
  while(i <= size - 1)
  {
    if(i + 1 <= size - 1)
      if(array[i] < array[i + 1])
        i++;
        if(item < array[i])
        {
          array[j] = array[i];
          j = i;
          i = 2 * j + 1;
        }
        else
          break;
  }
  array[j] = item;
}

void insertion_sort(int array[], int size)
{
    int i, element, j;

    for (i = 1; i < size; i++)
    {
        element = array[i]; j = i - 1;
        while (j >= 0 && array[j] > element)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = element;
    }

}

void merge_sort(int i, int j, int array[], int aux[])
{
    int mid, pointer_left, pointer_right, loop_ctr;

    if (j <= i) {
      // if the subsection is empty or a single element
      return;
    }
    mid = (i + j) / 2;

    // left sub-array is a[i .. mid]
    // right sub-array is a[mid + 1 .. j]
    merge_sort(i, mid, array, aux);             // sort the left sub-array recursively
    merge_sort(mid + 1, j, array, aux);         // sort the right sub-array recursively

    pointer_left = i;                           // pointer_left points to the beginning of the left sub-array
    pointer_right = mid + 1;                    // pointer_right points to the beginning of the right sub-array

    // we loop from i to j to fill each element of the final merged array
    for (loop_ctr = i; loop_ctr <= j; loop_ctr++)
    {
        if (pointer_left == mid + 1) {           // left pointer has reached the limit
            aux[loop_ctr] = array[pointer_right];
            pointer_right++;
        } else if (pointer_right == j + 1) {     // right pointer has reached the limit
            aux[loop_ctr] = array[pointer_left];
            pointer_left++;
        } else if (array[pointer_left] < array[pointer_right]) {    // pointer left points to smaller element
            aux[loop_ctr] = array[pointer_left];
            pointer_left++;
        } else {                                 // pointer right points to smaller element
            aux[loop_ctr] = array[pointer_right];
            pointer_right++;
        }
    }
    // copy the elements from aux[] to a[]
    for (loop_ctr = i; loop_ctr <= j; loop_ctr++)
    {
        array[loop_ctr] = aux[loop_ctr];
    }
}
// function to print the elements of an array
void printArray(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        // printf("%d ", array[i]);
        fprintf(fptr, "%d ", array[i]);
    }
}
