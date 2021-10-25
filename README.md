Computer Programming Course \
HOMEWORK 2 - Star Dust 

December, 2019 

Bianca Necula \
Faculty of Automatic Control and Computer Science \
315CA 

# Info
```bash
git clone https://github.com/BiancaNecula/Star-dust-Homework2.git
```
See README.check.pdf for informations about checker and testing. \
See "Programare_2019__Tema_2.pdf" for information about the homework. \
Tasks with dynamic allocation in C language.

# About the code:

To solve the tasks, I read the necessary data in the main function and I wrote specific functions for each task as follows:

- reading data - I read the map in a char matrix to keep the data in bytes to make processing easier. I kept their order according to the little endian system and I processed without altering the order (exception: swap),

* Task 1: I wrote the function task1 (char **, int *, int) to solve task 1. I calculated the sum and number of bytes on the edge of the array (all on the first and last line + the first and last on each line ) and I made the arithmetic mean with an accuracy of 8 decimals.

* Task 2: I wrote the task2 function (char **, int *, int) with the included functions: modify, swp, del corresponding to each operation. Thus, I read from STDIN the data necessary to solve and depending on the type of data (char, short, int) I found out the size of the data blocks we will work on.
- modify () - the function modifies a block of data of a certain type, with another data. If it is not in the memory area, reallocate the memory to that line in the array and add it. Between the old memory area and the newly added data, the area is zeroed. Indexing starts at 1.
- swap () - the function interchanges the values ​​in a certain data block: in char nothing happens, in short the 2 bytes are exchanged, in int the bytes are exchanged 2 by 2. Indexing starts from 0.
- del () - the function zeroes a block of data from a certain position. Indexing starts at 1.

* Task3: I wrote the fill and num_holes_black functions with a fill recursive algorithm that displays the minimum row-column index and the number of zeros in a black hole.
