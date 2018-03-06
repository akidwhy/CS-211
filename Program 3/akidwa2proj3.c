#include <stdio.h> #include <string.h> #include <stdlib.h> 
#define FALSE 0
#define TRUE 1

//--------------------------------------------------------------------------------
typedef int bool;
typedef struct Node {
  int x;
  int y;
  struct Node * next;
}
NODE;

//--------------------------------------------------------------------------------
typedef struct mazeStruct {
  char * arr;
  int rows;
  int columns;
  int x_start;
  int y_start;
  int end_x;
  int end_y;
  int size_of_x;
  int size_of_y;
}
MAZE;

//--------------------------------------------------------------------------------
typedef NODE * NodePointer;
void printMaze(MAZE);
void freeMaze(MAZE);
int debug = FALSE;
NodePointer innitialize_stack(MAZE);
MAZE make_a_Maze(char * );

//--------------------------------------------------------------------------------
void push(NodePointer * top, int x, int y) {
    NodePointer temp = (NodePointer) malloc(sizeof(NODE));
    temp -> x = x;
    temp -> y = y;
    temp -> next = * top; * top = temp;
  }

//--------------------------------------------------------------------------------
void pop(NodePointer * top) {
    if ( * top != NULL) {
      NodePointer temp = * top; * top = ( * top) -> next;
      free(temp);
    }
  }

//--------------------------------------------------------------------------------
void top(NodePointer t, int * x, int * y) {
    if (t != NULL) { * x = t -> x; * y = t -> y;
    } else {
      printf("Stack is Empty\n");
      exit(-1);
    }
  }

//--------------------------------------------------------------------------------
void clearStack(NodePointer * top) {
    while ( * top != NULL) {
      pop(top);
    }
  }

//--------------------------------------------------------------------------------
bool isEmpty(NodePointer top) {
    return (top == NULL);
  }

//--------------------------------------------------------------------------------
void printStack(NodePointer top) {
    int n;
    if (top != NULL) {
      printStack(top -> next);
      printf("(%d, %d)\n", top -> x, top -> y);
    }
  }

//--------------------------------------------------------------------------------
NodePointer innitialize_stack(MAZE m) {
    NodePointer stack = NULL;
    bool end = FALSE;
    char * temp = (char * ) malloc(sizeof(char) * m.rows * m.columns);
    memcpy(temp, m.arr, (m.rows * m.columns));
    push( & stack, m.x_start, m.y_start);
    while (!isEmpty(stack) && !end) {
      if (debug == TRUE) {
        printf("List stack:");
        printStack(stack);
        printf("\n");
      }
      int x = -1, y = -1;
      top(stack, & x, & y);
      if (m.end_x == x && m.end_y == y) {
        end = TRUE;
        break;
      }
      if (m.arr[(x * m.columns + y) + 1] == '.' || m.arr[(x * m.columns + y) + 1] == 'E') {
        push( & stack, (((x * m.columns + y) + 1) / m.columns),
          (((x * m.columns + y) + 1) % m.columns));
        m.arr[(x * m.columns + y) + 1] = 'x';
      } else if (m.arr[(x * m.columns + y) + m.columns] == '.' || m.arr[(x * m.columns + y) + m.columns] == 'E') {
        push( & stack, (((x * m.columns + y) + m.columns) / m.columns),
          (((x * m.columns + y) + m.columns) % m.columns));
        m.arr[(x * m.columns + y) + m.columns] = 'x';
      } else if (m.arr[(x * m.columns + y) - 1] == '.' || m.arr[(x * m.columns + y) - 1] == 'E') {
        push( & stack, (((x * m.columns + y) - 1) / m.columns),
          (((x * m.columns + y) - 1) % m.columns));
        m.arr[(x * m.columns + y) - 1] = 'x';
      } else if (m.arr[(x * m.columns + y) - m.columns] == '.' || m.arr[(x * m.columns + y) - m.columns] == 'E') {
        push( & stack, (((x * m.columns + y) - m.columns) / m.columns),
          (((x * m.columns + y) - m.columns) % m.columns));
        m.arr[(x * m.columns + y) - m.columns] = 'x';
      } else {
        pop( & stack);
      }
    }
    memcpy(m.arr, temp, (m.rows * m.columns));
    return stack;
  }

//--------------------------------------------------------------------------------
MAZE make_a_Maze(char * fileName) {
    MAZE m1;
    int x_position;
    int y_position;
    int i, j;
    FILE * src;
    if ((src = fopen(fileName, "r")) == NULL) {
      printf("Cannot open input file: %s\n", fileName);
      exit(-1);
    }
    /* read in the size, starting and ending positions in the maze */
    fscanf(src, "%d %d", & m1.size_of_x, & m1.size_of_y);
    fscanf(src, "%d %d", & m1.x_start, & m1.y_start);
    fscanf(src, "%d %d", & m1.end_x, & m1.end_y);
    m1.rows = m1.size_of_x + 2;
    m1.columns = m1.size_of_y + 2;
    /* Allocate memory for the maze array */
    int size = m1.rows * m1.columns;
    m1.arr = (char * ) malloc(sizeof(char) * size);
    /* initialize the maze to empty */
    for (i = 0; i < m1.size_of_x + 2; i++)
      for (j = 0; j < m1.size_of_y + 2; j++)
        m1.arr[i * m1.columns + j] = '.';
    /* mark the borders of the maze with *'s */
    for (i = 0; i < m1.size_of_x + 2; i++) {
      m1.arr[i * m1.columns + 0] = '*';
      m1.arr[i * m1.columns + m1.size_of_y + 1] = '*';
    }
    for (i = 0; i < m1.size_of_y + 2; i++) {
      m1.arr[i] = '*';
      m1.arr[(m1.size_of_x + 1) * m1.columns + i] = '*';
    }
    /* mark the starting and ending positions in the maze */
    m1.arr[m1.x_start * m1.columns + m1.y_start] = 'S';
    m1.arr[m1.end_x * m1.columns + m1.end_y] = 'E';
    /* mark the blocked positions in the maze with *'s */
    while (fscanf(src, "%d %d", & x_position, & y_position) != EOF) {
      m1.arr[x_position * m1.columns + y_position] = '*';
    }
    return m1;
  }

//--------------------------------------------------------------------------------
void printMaze(MAZE m1) {
    int i, j;
    for (i = 0; i < m1.size_of_x + 2; i++) {
      for (j = 0; j < m1.size_of_y + 2; j++)
        printf("%c", m1.arr[i * m1.columns + j]);
      printf("\n");
    }
  }

//--------------------------------------------------------------------------------
void freeMaze(MAZE m) {
    free(m.arr);
  }

//--------------------------------------------------------------------------------
int main(int argc, char * * argv) {
  int i, j;
  debug = FALSE;
  char * fileName = NULL;
  if (argc > 3) {
    printf("Usage: %s [-d] <maze data file>\n", argv[0]);
    exit(-1);
  }
  if (2 == argc) {
    fileName = argv[1];
  }
  if (3 == argc) {
    fileName = argv[2];
    if (argv[1][0] == '-' && argv[1][1] == 'd') {
      debug = TRUE;
    }
  }
  MAZE m1 = make_a_Maze(fileName);
  printf("Input Maze\n");
  printf("size : %d, %d\n", m1.size_of_x, m1.size_of_y);
  printf("start: %d , %d\n", m1.x_start, m1.y_start);
  printf("end  : %d, %d\n", m1.end_x, m1.end_y);
  printMaze(m1);
  NodePointer stack = innitialize_stack(m1);
  if (isEmpty(stack)) {
    printf("\nSorry there is no way to reach the end\n");
  } else {
    printf("\nHere is a path through the Maze \n");
    int old_x = -1;
    int old_y = -1;
    NodePointer temp = stack;
    while (NULL != temp) {
      int x = temp -> x;
      int y = temp -> y;
      if (m1.arr[x * m1.columns + y] != 'E' && m1.arr[x * m1.columns + y] != 'S') {
        if ((x + 1) == old_x) {
          m1.arr[x * m1.columns + y] = '#';
        } else if ((x - 1) == old_x) {
          m1.arr[x * m1.columns + y] = '#';
        } else if ((y + 1) == old_y) {
          m1.arr[x * m1.columns + y] = '#';
        } else if ((y - 1) == old_y) {
          m1.arr[x * m1.columns + y] = '#';
        } else {
          printf("\n Stack corrdinates: (%d, %d)\n", x, y);
          exit(-1);
        }
      }
      old_x = x;
      old_y = y;
      temp = temp -> next;
    }
    printMaze(m1);
    printf("\nCoordinates in the path are:\n");
    printStack(stack);
    printf("\n");
  }
  clearStack( & stack);
  freeMaze(m1);
  return 0;
}
