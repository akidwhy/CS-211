//
#include <stdio.h> 
#include <stdlib.h>
//each line of input is less than 300 characters long
#define MAXIMUM 301

//--------------------------------------------------------------------------------
typedef struct {
  char * stk;
  int sizeOfStack;
  int last;
}
stack;
typedef stack * stack_ptr;

//--------------------------------------------------------------------------------
char pop(stack * stk) {
  if (stk -> last <= -1)
    return '\0';
  return stk -> stk[(stk -> last) --];
}

//--------------------------------------------------------------------------------
void push(stack_ptr stk, char symbol) {
  if (stk -> last >= MAXIMUM) {
    char * temp = (char * ) malloc(sizeof(char) * (stk -> sizeOfStack + 2));
    free(stk -> stk);
    stk -> stk = temp;
    stk -> stk += 2;
  }
  stk -> stk[++(stk -> last)] = symbol;
}

//--------------------------------------------------------------------------------
stack * stkCreate(int n) {
  stack * temp;
  temp = malloc(sizeof(stack) + 2);
  if (temp == NULL) {
    exit(1);
  }
  temp -> stk = malloc(sizeof(char) * n + 2);
  if (temp -> stk == NULL) {
    exit(1);
  }
  temp -> last = -1;
  return temp;
}

//--------------------------------------------------------------------------------
main(int argc, char * argv[]) {
  char input[MAXIMUM];
  int debug = 0;
  int i = 0;
  int error = 0;
  char temp;
  char symbol = '\0';
  stack * stk;
  stk = stkCreate(MAXIMUM);


  if (argc > 2) {
    printf("Please use: %s[-d]\n", argv[0]);
    exit(0);
  }
  if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'd') {
    printf("\nDebuging information\n");
    debug = 1;
  }
  
  while (1) {
    printf("Enter your expression or type 'q' to leave: ");
    fgets(input, MAXIMUM, stdin);
    if (input[0] == 'q') {
      exit(0);
    }

    while (input[i] != '\0') {
      symbol = input[i];
      if (symbol == '(' || symbol == '{' || symbol == '[' || symbol == '<')
        push(stk, symbol);
      else if (symbol == ')' || symbol == '}' || symbol == ']' || symbol == '>') {
        temp = pop(stk);
        if (!((temp == '(' && symbol == ')') || (temp == '{' && symbol == '}') || (temp == '[' && symbol == ']') || (temp == '<' && symbol == '>'))) {
          error = 1;
          break;
        }  
      }
      i++;
    }
    
    if (error == 1) {
      printf("\nExpression are balance:\n");
    } else {
      printf("\nExpression is not balance:\n");
    }
  }
  return 0;
}
