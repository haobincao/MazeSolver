# PR3

# **2. Introduction and Background**

## **Introduction**

### **Solving a Maze**

In this programming assignment you will write a program to read a given maze (provided as text “art”) and find the shortest path from start to finish. Mazes go back to antiquity and the story of the minotaur. However, Theseus didn’t have Google Maps.

You will implement breadth-first search, a simple algorithm that finds not just any path to the exit in a maze, but actually finds a **shortest** path from the start to the finish. This algorithm was described in the late 1950s, making it one of the earliest nontrivial algorithms to follow the creation of the electronic computer.

---

In this assignment you will practice the following skills:

- Dynamic memory allocation of arrays and 2D arrays.
- Using `struct`s and `class`es .
- Implementation of a simple queue data structure.
- Implementing the breadth-first search (BFS) algorithm.

# **A Piece of Advice!**

We suggest you read through the entire description before beginning the assignment.

### **Maze Input Format**

Your program will receive the input file from a command line argument.

Below shows an example of passing in a maze input file called “maze1.in” to our maze program using a command line argument.

`./maze maze1.in`

### **The input file is structured as follows:**

The first line of the file should contain two integer numbers indicating the row and column size of the maze. The number of rows indicated will determine how many lines of text follow (1 row per line).On each line will be one character for each of the indicated number of columns followed by a newline character. The characters can be a period `.` indicating a space in the maze, a `#` sign indicating a wall in the maze, a capital `S` indicating the start location for your search, or a capital `F` for the desired finish location. You can’t go outside the grid. (i.e., you may imagine that lava surrounds the maze perimeter.)

In general the format of the maze is:

`rows cols
[row 1: cols many characters]
[row 2: cols many characters]
...
[row rows: cols many characters]`

and the possible characters are:

| Character | Meaning |
| --- | --- |
| . | Empty space |
| # | Wall |
| S | Start location |
| F | Finish location |

**We provide you with 4 mazes: `maze[1-4].in` and `maze1.in` is shown as an example on the left.** You can also find some interesting mazes in a directory called `testcases`.

### **Maze Output Format**

Your search algorithm will find a shortest path from the start cell to the finish. It will indicate this path by filling in the character locations on the path with asterisks `*`; then, it will write the resulting character maze to `cout` (standard output).

Note: We could have chosen to output the results to a file to practice with `ofstream` objects, but because they behave nearly the same as `cout`, we chose the simpler `cout` approach so you can focus on the really learning tasks of allocating the 2D array(s) and implementing the BFS algorithm.

**The correct output for `maze1.in` (below) is shown on the left (`maze1.sol`).**

maze1.in

`5 5
.S.#. 
##.#.
.....
.####
....F`

maze1.sol (this is the content that `cout` should produce)

`5 5
.S*#. 
##*#.
***..
*####
****F`

---

**However**,

1. If no path exists, your program should output

`No path could be found!`

1. If the user gives an invalid maze (more than one start or finish point), your program should output

`Invalid maze.`

1. If the input maze contains characters other than those shown above, then your program should output

`Error, input format incorrect.`

## **BFS**

Breadth First Search is a general technique with many uses including flood fill, shortest paths, and meet-in-the-middle search. The idea is to explore every possible valid location, beginning at the start location, using an ordering so that we always explore ALL close locations (i.e. those at a shorter distance from the start) before exploring any location at a further (longer) distance from the start.

In other words, first we “explore” the start, then all locations at distance 1 from the start (one at a time), then all locations at distance 2 from the start (one at a time), etc, in that order.

This property ensures that when we do find the finish cell (if one exists), we will arrive there via a shortest-length path. Of course, as we search we mark cells (as explored) that we’ve visited so that we don’t visit them again and cause an infinite cycle of exploration!

### **Ensuring the BFS propety**

To ensure we explore all **closer** locations before **further** locations, we keep a queue of locations in the maze. A queue has the property that the first item added is the first to be removed (first-in, first-out, a.k.a. **FIFO**). We can easily implement this by always adding new values to the back of a list (i.e. tail of the queue) but remove from the front (i.e. head of the queue).

Put simply, a queue mimics a line of people waiting. New arrivals enter at the back and leave from the front when they are served. The longest/oldest item will be at the front of the queue and the newest at the back.

In our maze search the queue is initially empty and we begin by putting the **start** location into it. In each iteration, we remove the oldest remaining location from the queue, and we add all of its new neighbors to the end of the list. This simple algorithm successfully implements the BFS.

We keep the BFS going until the queue is exhausted because all reachable locations were explored or we find our goal location.

What is left is to actually mark out the shortest path in `*` characters (i.e., trace your path back from the finish point to start point). But this requires that we record which location found each subsequent location during the outward (BFS) exploration. We will track a **predecessor** for each location (which is simply the coordinates of the location that found this one). Think of a predecessor as a pointer to take one step backward. Once we find the *Finish* location, we can just walk from the predecessor of the *Finish* to that location’s predecessor, and then to that location’s predecessor, and so on until we reach the start, marking each of those locations with `*`.

## **Coding Considerations**

### **`Location` Struct**

The maze in this assignment is a 2D grid. Therefore, each location in the maze is identified by two index values: a row index and a column index. The approach that we will use for solving the maze will involve keeping track of a list of these locations. It will be extremely convenient if we are able to create a structure that contains both a number for the row and a number for the column.We can accomplish this by creating a simple new data type.We will call it `Location`.

**`struct** **Location** { *// define a new data type***int** row;
  **int** col;
};`

## **Put Simply**

A Location object is simply a package with two numbers that can be manipulated using the dot (membership) operator.

Here is an artificial example.

`Location start;*//create a location called 'start'*
start.row = 3 ;*//set the row of `start` to be 3*
start.col = 5 ;*//set the column of `start` to be 5*

Location one_below = start; *// make a copy of the start location called `one_below`*
one_below.row += 1 ;*//add one to the row of `one_below`*cout<<"Start:"<< start.row <<","<< start.col <<endl; *// Start: 3,5*cout<<"One Below:"<< one_below.row <<","<< one_below.col <<endl; *// One Below: 4,5*`

This will be convenient because we can have an array (or queue) of Locations, have functions that take a Location as input or output, etc.

In the next page, we will talk about another data type that you will have to complete, the `Queue` class.

---

Question that you should be asking yourself:

1. What are the differences between a struct and a class?
2. When should I use a class vs a struct?

### **The Queue class**

You will be required to complete the definition of another new data type, the `Queue` class, that will be useful in implementing the search. The `Queue` class will store the list of `Location`s waiting to be searched. The Queue class should support the following operations:

- create an empty queue (but with a given maximum capacity of how many Locations it can store)
- add a new Location to the back of the queue
- Remove the oldest Location from the front of the queue
- check if the queue is empty

We use objects (classes and structs) to abstract our software design and implementation. By first writing the `Queue` class, you do not have to worry about those implementation details when you write your higher level BFS algorithm. This allows you to focus on the larger BFS algorithm and not the data management aspects.

Every time you find a new, unexplored `Location` you will call the `Queue`'s `add_to_back(Location)` function. Every time you want to get the next location to explore from, you will call the `Queue`'s `remove_from_front()` function.

Internally, the `Queue` class should just create an array to hold the maximum number of `Locations` that could ever be entered into the queue and use integer index variables to remember where it should place new values (i.e. where the back is located) and where it should remove old values (i.e. where the front is located).

Remember that our Queue class needs to support the following operations:

*`// returns true if the queue is empty.***bool** **is_empty**();

*// insert a new Location at the end of our queue*  **void** **add_to_back**(Location loc);

*// returns the oldest Location in the queue and "removes" it.*Location **remove_from_front**();`

Here is an example of how it should behave:

*`// create some locations;*
Location three_one;
three_one.row = 3; three_one.col = 1;
Location two_two;
two_two.row = 2; two_two.col = 2;

*// create a queue with max capacity 5*Queue **q**(5);

cout << boolalpha;
cout << q.is_empty() << endl; *// true*
q.add_to_back(three_one);

cout << q.is_empty() << endl; *// false*
q.add_to_back(two_two);

Location loc = q.remove_from_front();
cout << loc.row << "," << loc.col << endl; *// 3,1*

loc = q.remove_from_front();
cout << loc.row << "," << loc.col << endl; *// 2,2*cout << q.is_empty() << endl; *// true*`

As you can see, the queue gave us back the oldest location (the one add_to_back added earliest) first.

### **The Queue class under the hood**

The `Queue` implementation we provide you is almost complete. It is based on the idea of using a long array/pointer called `contents` that holds Locations, as well as two counters:

- `tail` counts the number of `add_to_back` calls so far. Equivalently, its value is the next unused index in the contents array.
- `head` counts the number of `remove_from_front` calls so far. Equivalently, its value is the oldest index that has not yet been extracted.

For instance, this is what the internal variables of the Queue should look like for the example above before the two locations are added:

`tail: 0
head: 0
contents[0..4]: garbage`

Here is what it looks like after both locations are added:

`tail: 2
head: 0
contents[0]: Location(row 3, col 1)
contents[1]: Location(row 2, col 2)
contents[2..4]: garbage`

currently, `head` is 0.

When we make the first call to `remove_from_front`, it should both return the Location at `contents[head]` which is `Location(row 3 , col 1)` and increment the `head` counter by one.

`head` is now 1.

After that, when we make the second call to `remove_from_front`, it again should return the Location at `contents[head]` which is `Location(row 2, col 2)` and increment `head` counter by one.

After that, because head and tail are now equal, the Queue knows it is empty.

## **Tip**

You may have to create a temporary variable to hold the Location at `contents[head]` so that you can increment the head counter before returning that Location. This is because any statement that comes after a return statement will not be executed.

**Note:** when you delete a Location from the queue (`remove_from_front`), you do not technically remove the Location. You simply move the head counter forwards (i.e., incrementing the head counter and leaving the old Locations sitting in their original Locations). Actually, the expense of removing a Location and shifting other Locations forward would make your program much slower.

Here are some additional notes about the Queue class:

1. The `Queue` constructor takes an integer `max_size`. For our BFS application, you should pass `rows*cols` as this maximum size, since that it the maximum number of locations that our queue could be used to explore. **Hint:** When you write your code do you know the exact value of `rows*cols`? If not, how should you allocate that array?
2. the constructor syntax is `Queue q(5);` similar to how a file stream is created.
3. C++ calls the destructor automatically. We should not see the code `~Queue()` anywhere in maze.cpp.

### **2D Array Allocation**

You will not know the size of the maze until runtime, when you read the maze data. Thus we will need to dynamically allocate an array to hold the maze data. Remember that a single call to `new` can only allocate a 1D array. Thus you will need to allocate each row of the 2D array as a separate 1D array. And, beyond that, we need not just **one** 2D array but several:

- one for the maze data,
- one for the predecessors, and
- one to remember which cells have been visited.

The way to allocate a 2D array in C++ is: use `new[]` once to allocate a 1D array of **pointers**, then using a loop containing `new[]` to allocate many 1D arrays whose starting addresses are stored in the pointer array elements. See the dynamic memory exercise `nxmboard` and `deepnames` on the website (in class exercises).

# **Memory leaks**

Remember that you need to deallocate everything that you allocate. This means that every call to `new[]` needs a matching call to `delete[]`. Otherwise, your program will have a memory leak!

Typically, the pattern you use to **allocate** is the same pattern you will use to **deallocate**, but just in reverse order.

# ***3. Procedure***

## **Files and Required Functions / Classes**

In order to create some modularity, your program will be written in several files and should utilize several functions. We will give you skeletons for them.

- `maze.cpp`: the main maze-solving program.
- `mazeio.cpp` and `mazeio.h`: routines for input and output.
- `queue.cpp` and `queue.h`: the definition of the `Location` structure and `Queue` class.

### **mazeio.cpp**

our mazeio.cpp must define the following functions:

**`char**** **read_maze**(**char*** filename, **int** *rows, **int** *cols);`

Use file streams to read the maze from the given filename. Return `NULL` if the file does not exist, or you are unable to read two numbers from the start of the file. **Dynamically allocates** a 2D array for the maze and returns it. The rows and cols arguments should point to variables (check maze.cpp line 16) that can be filled in with the dimensions of the maze read in.

**`void** **print_maze**(**char** **maze, **int** rows, **int** cols);`

Prints the maze dimensions and maze contents to `cout` in a two dimensional format. (Your completed program will call this after filling the shortest path with asterisks.)

### **queue.cpp**

our `queue.cpp/queue.h` files will define the `Location` structure as well as the following API for the `Queue` class:

`Queue( **int** max_size); *// constructor*
~Queue(); *// destructor***void** Queue::add_to_back(Location loc); *// add new location*
Location Queue::remove_from_front(); *// get oldest location***bool** Queue::is_empty(); *// am I empty?*`

Most of the class definition will be provided for you. You will have to fill in the body of the `add_to_back` and `remove_from_front` functions.

### **maze.cpp**

Your maze.cpp should be broken modularly into two functions:

First,

**`int** **main**(**int** argc, **char*** argv[])`

Starts the program, calls the input function, solves the maze, prints the output. **Note:** the main function is not yet complete.

Second,

**`int** **maze_search**(**char****maze, introws, intcols)`

Given a maze, performs the BFS search for a valid path, filling in the path with `*` if found. Returns `1` if a valid path was found, `0` if no path was found, and `-1` if the input is of the wrong format. Specifically, it should check that the input contains exactly one start (`S`) cell and exactly one finish (`F`) cell.

Keep in mind the following restrictions:

- You **must** exclusively use dynamically-allocated arrays of exactly the right size for this assignment. If you do not use dynamic memory, it is unlikely you will pass all of the test cases.
- A valid path consists of steps north, west, south, and east but no diagonals. Thus we only need to explore neighbors of a cell in those 4 directions, not along diagonals.

## **BFS Pseudocode**

Here is the review of BFS description given earlier:

`mark the start location as explored
add start location to q

**while** q is **not** empty **do**:
  set loc = extract the item from the front of q
  **for** each neighbor (i.e., N,W,S, **and** E) of loc **do**:
    **if** the neighbor is valid, open, **and** **not** yet explored **do**:
      mark the neighbor as explored
      add the neighbor to the back of q
      set predecessor of the neighbor = loc`

# **Simplification**

While the order of exploration doesn’t matter, to help the course staff debug your code (in case you need help) and to ensure we all get the SAME shortest path if many exist, you should explore a cell’s neighbors in the following order: North, West, South, East.

### **The ‘Explored’ Array**

You need to avoid adding any location to the queue more than once. Otherwise, your search can cycle infinitely or exceed the maximum queue size. We do this by creating a data structure that remembers, for each cell, if it’s already been added to the queue or not. This data structure should let you look up, for a given location (row/col indices), whether that cell has already been explored, or not yet explored.

What type of structure could you use for this?

In your code, you will need to **dynamically allocate** and initialize this structure before you start the BFS algorithm.

### **The ‘Predecessor’ Array**

The final step is actually locating the optimal path and marking it with `*`. This requires a little more bookkeeping, like a “trail of breadcrumbs” that you can follow from the finish back to the start.

This is the predecessor array referred to earlier. It should be a 2D array of Locations, so that for a given `[row][col]`, you can lookup the Location (row/column) of which neighbor **caused it to be added to the queue** (i.e. was its predecessor.)

The predecessor is utilized to find the actual path when your algorithm is complete: we trace it from the finish back to the start. **In other words, the predecessor of the finish cell will tell us how to go back one step, then that cell’s predecessor will tell us how to go back another step, and so on until we reach the start cell.**

Essentially, as we walk back the next step backward can be found from our `curr` (current) location by accessing `pred[curr.row][curr.col]`

Here are some more questions to consider:

- Where should the backtracking start and finish?
- What kind of loop should you use for backtracking?

## **Writing your code**

The following is just a set of suggestions as to how you can develop the code while keeping the debugging work as simple as possible.

### **Checkpoint 1: Input/Output**

Complete the `mazeio.cpp` code so that you can read/write mazes. In `main()` of `maze.cpp`, write a program that simply reads the input and prints it to the screen without trying to solve it. Again, don’t forget that your maze has to be **dynamically allocated.**

Compile and run your program:

`make maze
./maze maze1.in`

should produce

`5 5
.S.#.
##.#.
.....
.####
....F`

Check that the printed output looks correct.

### **Checkpoint 2: Deallocate the mymaze array in main.cpp**

After we are done with our mymaze array, don’t forget to deallocate it at the end of main(), so that we don’t get memory leak errors.

At this point you can also decide where you want to implement basic format checking of the input maze. Don’t forget to deallocate what has been allocated when you encounter an error. Thinking about where and how to do that can lead to varying amounts of code that need be written.

We have defined several messages that you can print out to ensure your formatting is correct:

    `**const** **char*** invalid_char_msg = "Error, invalid character.";
    **const** **char*** invalid_maze_msg = "Invalid maze.";
    **const** **char*** no_path_msg = "No path could be found!";`

Note: The last message is when the maze has no solution.

You should also test your program with valgrind and ensure there are no errors.

`valgrind --tool=memcheck --leak-check=yes ./maze maze1.in`

### **Checkpoint 3: Queue**

You will need to implement the constructor, destructor, `add_to_back()`, and `remove_from_front()` member functions of the `Queue` class in `queue.cpp`. Each function requires only 1-2 lines. `add_to_back()` should add the incoming `Location` to the end of the list. `remove_from_front()` should return the `Location` that has been waiting the longest to be removed. Each of these functions should update the appropriate counter. For help with the syntax, see the description of the member variables in `queue.h` and also look at how `is_empty` is defined in `queue.cpp`.

For some hints, go back to Queue section on the previous page in the guide!!

Execute the following two commands in terminal.

`make queue_test
./queue_test`

It should print out:

`true
false
3 1
2 2
true`

### **Checkpoint 4: Core BFS algorithm**

**Prerequisites:**

1. Add the `#include "queue.h"` header to `maze.cpp`.
2. complete the main function to call this the `maze_search()` function correctly.

**In maze_search():**

1. Find the start and finish cells and check that the maze is valid. Return `1` for a badly-formatted maze.
2. Create your queue with an appropriate size i.e., `rows*cols`
3. Dynamically allocate the `predecessor` and `explored` arrays. If applicable, you may also need to initialize them.
4. Perform the breadth-first search algorithm described earlier.
5. When the algorithm is done and the finish cell is found, add the code to walk the predecessor array backwards from the finish location to the start location, filling in the intermediate locations of the maze with ``.
6. Make sure all dynamically allocated memory is deallocated (for the predecessor and explored arrays).
7. Return the correct status code: `1` for success, `0` for no path exists.
8. Compile and run your program on all available sample cases, as well as the one you created yourself. The more testing, the better.

Does your program successfully distinguish mazes where a path exists, from ones where a path does not? You should be able to run it on all of the test cases.

# **Debugging Tip**

If need be, print out the location (its row and column) of each item you add or remove to the queue so that you know that the order of exploration is correct and that it makes sense to you. Trace through the input manually and see if your code works the same way.

Here is one sample run:

`make maze
./maze maze1.in`

should produce

`5 5
.S*#.
##*#.
***..
*####
****F`

### **Common Question**

- **Q: Do I have to account for empty mazes, or wrongly-shaped mazes?**
- A: No, you can assume the maze data forms a rectangle with dimensions matching the given integers. You can assume the number of rows and columns is a positive integer. You should ensure the only characters used are: `.#SF` and that there is exclusively one start and one finish. These requirements are described earlier in the guide.