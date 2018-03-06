/*akidwa2proj1.c
Write a C program (not a C++ program!) that will contain the following:
-Write a function that will make a copy of the values from one array to another array.

-Write your own function that will sort an array in ascending order. You may use
whatever sorting algorithm you wish. 

-Write your own function that will perform a linear search on the unsorted array.
The function is to “return” two values. The first should be the position in the array
where the value was found or -1 if the value was not found. The second is the
number of comparisons needed to determine if/where the value is located in the
array. 

-Write your own function that will perform a binary search on the sorted array.
The function is to “return” two values. The first should be the position in the array
where the value was found or -1 if the value was not found. The second is the
number of comparisons needed to determine if/where the value is located in the
array.

*/
//--------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------
//Copies the values from one array to another array.
void arrayCopy(int fromArray[], int toArray[], int size) {
    int i;
    for (i = 0; i < size; i++) {
      toArray[i] = fromArray[i];
    }
  } //end arrayCopy

//--------------------------------------------------------------------------------
//Sorts an array in ascending order.
void sort(int arr[], int size) {
    int i; //used for the loop condition
    int arrCounter; //used for the nested for loop
    int temp; //temporarily hold the value being looked at

    for (i = 0; i < size; ++i) {
      for (arrCounter = i + 1; arrCounter < size; ++arrCounter) {
        if (arr[i] > arr[arrCounter]) {
          temp = arr[i];
          arr[i] = arr[arrCounter];
          arr[arrCounter] = temp;
        }
      }
    }
  } //end sort

//--------------------------------------------------------------------------------
//Performs a linear search on the unsorted array
int linSearch(int arr[], int size, int target, int * numComparisons) {
    int i; //used for the for loop condition
    int targetPosition; //holds the position of the array being searched

    for (i = 0; i < size; i++) {
      if (arr[i] == target) {
        targetPosition = i;
        return targetPosition;
      }
      ( * numComparisons) ++; //increase the number of comparisons every time the loop runs
    }

  } //end linSearch

//--------------------------------------------------------------------------------
//Performs a binary search on the sorted array
//This function was taken from a program created in CS141
int binSearch(int arr[], int size, int target, int * numComparisons) {
    int first = arr[0]; //starts with the first array
    int last = size - 1;
    int middle = (first + last) / 2; //gets the middle array
    ( * numComparisons) = 0; //restart the comparisons

    while (first <= last) {
      if (arr[middle] == target) { //checks to see if the target and the middle array are the same
        ( * numComparisons) ++;
        return middle;
      } else if (arr[middle] < target) { //checks to see if the middle array is less than the target
        ( * numComparisons) ++;
        first = middle + 1;
      } else {
        ( * numComparisons) ++;
        last = middle - 1;

      }

      middle = (first + last) / 2;
    }
    if (first > last) {
      return -1;
    }

  } //end binSearch

//--------------------------------------------------------------------------------
int main() {
    int i; //used for the counter in loops 
    int * darr; //the initial array
    int * arr2; //stores the copy of the initial array
    int numComparisons = 0; //stores the number of comparisons
    int target; //stores the user input 
    int size = 100; //sets the size of the array
    darr = (int * ) malloc(size * sizeof(int)); //allocates the memory for the array
    int val; //stores the numbers that will be put into the array
    int position = 0;

    //get user input
    printf("Enter numbers:\n");
    scanf("%d", & val);

    //increase the size of the array if need be
    while (val != -999) {
      if (position >= size) {
        int * temp;
        temp = (int * ) malloc(size * 2 * sizeof(int));
        int i;
        for (i = 0; i < size; i++)
          temp[i] = darr[i];
        free(darr);
        darr = temp;
        size = size * 2;
      }

      darr[position] = val;
      position++;
      scanf("%d", & val);

    }
    //allocates memory for the coppied array
    arr2 = (int * ) malloc(size * sizeof(int));

    //calls the function to copy one array to another
    arrayCopy(darr, arr2, position);

/*    	//DEBUG: uncomment to see if the arrayCopy function worked
        printf("The copied array is :");
        for (i = 0; i < position; i++)
          printf("\narr2[%d] = %d", i, arr2[i]);
*/
    
    //calls the function sort to sort the array
    sort(arr2, position);

/*    	//DEBUG: uncomment to see if the array is being sorted properly
        printf("\nThe numbers arranged in ascending order are given below \n");
        for (i = 0; i < position; i++) {
          printf("narr2[%d] = %d\n", i, arr2[i]);
        }
*/    

    //get users input for the number they want to find using linear search
    printf("\nEnter the number you want to find using linear search:");
    scanf("%d", & target);

    //call the function linSearch and print the results
    int linSearchResult = linSearch(darr, position, target, & numComparisons);
    printf("The position of your target is: %d\n", linSearchResult);
    printf("Number of comparisons: %d\n", numComparisons + 1);

    //get users input for the number they want to find using binary search
    printf("\nEnter the number you want to find using binary search:");
    scanf("%d", & target);

    //call the function binSearch and print the results
    int binSearchResult = binSearch(arr2, position, target, & numComparisons);
    printf("The position of your target is: %d\n", binSearchResult);
    printf("Number of comparisons: %d\n", numComparisons);

    return 0;
  } //end main
