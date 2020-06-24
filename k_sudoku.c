#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <klee/klee.h>
#include <assert.h>
#include <string.h>

/** defining the sudoku puzzle **/

#define HEIGHT 9
#define WIDTH 9

//int puzzle[HEIGHT][WIDTH] = {{0, 0, 0, 2, 6, 0, 7, 0, 1},
  //                           {6, 8, 0, 0, 7, 0, 0, 9, 0},
    //                         {1, 9, 0, 0, 0, 4, 5, 0, 0},
      //                       {8, 2, 0, 1, 0, 0, 0, 4, 0},
        //                     {0, 0, 4, 6, 0, 2, 9, 0, 0},
          //                   {0, 5, 0, 0, 0, 3, 0, 2, 8},
            //                 {0, 0, 9, 3, 0, 0, 0, 7, 4},
              //               {0, 4, 0, 0, 5, 0, 0, 3, 6},
                //             {7, 0, 3, 0, 1, 8, 0, 0, 0}};
int puzzle[HEIGHT][WIDTH] = {{0, 0, 0, 2, 6, 0, 7, 0, 1},
			     {6, 8, 0, 0, 7, 0, 4, 9, 3},
			     {1, 9, 7, 8, 3, 4, 5, 6, 2},
			     {8, 2, 6, 1, 9, 5, 3, 4, 7},
			     {3, 7, 4, 6, 8, 2, 9, 1, 5},
			     {9, 5, 1, 7, 4, 3, 6, 2, 8},
			     {5, 1, 9, 3, 2, 6, 8, 7, 4},
			     {2, 4, 8, 9, 5, 7, 1, 3, 6},
			     {7, 6, 3, 4, 1, 8, 2, 5, 9}};

   

int count;

void draw();
bool checkRow(int r, int start, int end, int num);
bool checkColumn(int c, int start, int end, int num);
bool checkGrid (int c, int r, int num);


int main () {
        draw();

        int i = 0;
        int x = count;

        printf("Enter the list of numbers to replace the 0\n");
//      char input[c+1];
        int input[8];
        klee_make_symbolic(&input, sizeof(input), "input");
                for (int r = 0; r < 9; r++ ) {
                        for (int c = 0; c < 9; c++ ) {
                                if (puzzle[r][c] == 0 ) {
                                        //printf("Row %d and Column %d\n", r, c);
                                        int num = input[i];
                                        if (checkRow(r, 0, 9, num) && checkColumn(c, 0, 9,num) && checkGrid(c-c%3, r-r%3, num)) {
                                                puzzle[r][c] =num;

                                               
                                                i+=1;
                                        } else {
                                             
                                                return -1;
                                        }

                                }
				if (i==x) {
					break;
				}
                        }
			if (i==x) break;
                }
        printf("Successfully completed grid");
	klee_assert(0);
	return 0;
	


}
void draw() {
        int i, j;
        for (i = 0; i < HEIGHT; i++) {
                for (j = 0; j < WIDTH; j++) {
                        if (j== 0 || j==3 || j==6) {
                                printf("|");
                        }
                        printf("%d  ", puzzle[i][j]);
                        if( puzzle[i][j] == 0) {
                                count +=1;
                        }


                }
                printf("\n");
                if (i == 2 || i == 5|| i ==8) {
                        printf("------------------------------\n");
                }
        }
        printf("\n");
}

bool checkRow(int r, int start, int end, int num) {
        for (int i = start; i < end; i++ ) {
                if (puzzle[r][i] == num) {
                        return false;
                }

        }
        return true;
}

bool checkColumn(int c, int start, int end, int num) {
        for (int i = start; i < end; i++ ) {
                if (puzzle[i][c] == num) {
                        return false;
                }
        }
        return true;
}

bool checkGrid (int c, int r, int num) {
 for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                        if( puzzle[i+r][j+c] == num) {
                                return false;
                        }
                }
        }
        return true;
}

