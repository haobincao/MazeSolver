/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// Add other prototypes here for any functions you wish to use


// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
    int rows, cols;
    //int result;
    char** mymaze=NULL;
    const char* invalid_char_message = "Error, invalid character.";
    const char* invalid_maze_message = "Invalid maze.";
    const char* no_path_message = "No path could be found!";

    if(argc < 2)
    {
        cout << "Please provide a maze input file" << endl;
        return 1;
    }

    mymaze = read_maze(argv[1],&rows,&cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 1

    // For checkpoint 2 you should check the validity of the maze
    // You may do so anywhere you please and can abstract that
    // operation with a function or however you like.
    int nS = 0;
    int nF = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (mymaze[i][j] == 'S') {
                nS++;
            }
            else if (mymaze[i][j] == 'F') {
                nF++;
            }
            else if (mymaze[i][j] != '#' && mymaze[i][j] != '.') {
              //check for invalid character
                cout << invalid_char_message;
                for (int k = 0; k < rows; k++) {
                  delete [] mymaze[k];
                }
                delete [] mymaze;
                return 0;
            }
        }
    }
    //check for the number of 'S's and 'F's
    if (nS != 1 || nF != 1) {
        cout << invalid_maze_message;
        for (int i = 0; i < rows; i++) {
          delete [] mymaze[i];
        }
        delete [] mymaze;
        return 0;
    }

    //use maze_search to determine if a path is found; if found, print the updated maze; if not, print no path msg
    if (maze_search(mymaze,rows,cols) == 1) {
      print_maze(mymaze,rows,cols);
    }
    else {
      cout << no_path_message;
      for (int i = 0; i < rows; i++) {
        delete [] mymaze[i];
      }
      delete [] mymaze;
      return 0;
    }



    //================================
    // When working on Checkpoint 4, you will need to call maze_search
    // and output the appropriate message or, if successful, print
    // the maze.  But for Checkpoint 1, we print the maze, regardless.

    //================================
    // ADD CODE BELOW 
    // to delete all memory that read_maze allocated: CHECKPOINT 2
    for (int i = 0; i < rows; i++) {
        delete [] mymaze[i];
    }
    delete [] mymaze;





    return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols)
{
    // *** You complete **** CHECKPOINT 4
    //initialize some variables and two 2D arrays with dynamic allocation
    Location s,def;
    def.row = -1;
    def.col = -1;
    bool found = false;
    Location** predecessor = new Location*[rows];
    int** explored = new int*[rows];
    for (int i = 0; i < rows; i++) {
      explored[i] = new int[cols];
      predecessor[i] = new Location[cols];
      for (int j = 0; j < cols; j++) {
        explored[i][j] = 0;
        predecessor[i][j] = def;
        if (maze[i][j] == 'S') {
          s.row = i;
          s.col = j;
        }
      }
    }

    //initialize queue and add the starting point to it
    Queue q(rows*cols);
    explored[s.row][s.col] = 1;
    q.add_to_back(s);
    Location curr;
    while (!q.is_empty()) {
      curr = q.remove_from_front();
      Location next;
      //if not on the top row, then check the square on top(N direction)
      if (curr.row != 0) {
        next.row = curr.row-1;
        next.col = curr.col;
        if (maze[next.row][next.col] == 'F') {
          predecessor[next.row][next.col] = curr;
          found = true;
          break;
        }
        if (maze[next.row][next.col] == '.' && explored[next.row][next.col] == 0) {
          predecessor[next.row][next.col] = curr;
          explored[next.row][next.col] = 1;
          q.add_to_back(next);
        }
      }
      //if not on the left column, then check for the square on left(E direction)
      if (curr.col != 0) {
        next.row = curr.row;
        next.col = curr.col-1;
        if (maze[next.row][next.col] == 'F') {
          predecessor[next.row][next.col] = curr;
          found = true;
          break;
        }
        if (maze[next.row][next.col] == '.' && explored[next.row][next.col] == 0) {
          predecessor[next.row][next.col] = curr;
          explored[next.row][next.col] = 1;
          q.add_to_back(next);
        }
      }
      //if not on the bottom row, then check for the square below(S direction)
      if (curr.row != rows-1) {
        next.row = curr.row+1;
        next.col = curr.col;
        if (maze[next.row][next.col] == 'F') {
          predecessor[next.row][next.col] = curr;
          found = true;
          break;
        }
        if (maze[next.row][next.col] == '.' && explored[next.row][next.col] == 0) {
          predecessor[next.row][next.col] = curr;
          explored[next.row][next.col] = 1;
          q.add_to_back(next);
        }
      }
      //if not on the right column, then check for the column on right(W direction)
      if (curr.col != cols-1) {
        next.row = curr.row;
        next.col = curr.col+1;
        if (maze[next.row][next.col] == 'F') {
          predecessor[next.row][next.col] = curr;
          found = true;
          break;
        }
        if (maze[next.row][next.col] == '.' && explored[next.row][next.col] == 0) {
          predecessor[next.row][next.col] = curr;
          explored[next.row][next.col] = 1;
          q.add_to_back(next);
        }
      }

    }

    //if not found, then delete allocated arrays and return 0
    if (!found) {
      for (int i  = 0; i < rows; i++) {
        delete [] predecessor[i];
        delete [] explored[i];
      }
      delete [] explored;
      delete [] predecessor;
      return 0;
    }
    else {
      //if found, then backtrace the path using predecessor and change the path to '*'
      while (maze[curr.row][curr.col] != 'S') {
        maze[curr.row][curr.col] = '*';
        curr = predecessor[curr.row][curr.col];
      }
      
      for (int i  = 0; i < rows; i++) {
        delete [] predecessor[i];
        delete [] explored[i];
      }
      delete [] explored;
      delete [] predecessor;
      return 1;
    }
    





    
    // DELETE this stub, it's just for Checkpoint 1 to compile.
    //return 0;
}
