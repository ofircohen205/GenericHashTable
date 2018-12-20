ofirce
312255847 Ofir Cohen

ex1 - Computer Communication Course

This program implements generic hash table - for integer type and string type

list of files:
GenericHashTable.h
GenericHashTable.c
readme.md
makefile
tester.c (added by the tester)

how to install the program:
open linux terminal, navigate to the folder containing ex1
using the "cd" command (confirm it by using ls command)
incase you have makefile, type make and the program will
automaticily be compiled, if you don't, type 
gcc -c GenericHashTable.h GenericHashTable.c main.c -o main -Wvla -g -Wall

and your program will automaticily be compiled

to activate program:
open linux terminal, navigate to ex1 executeable file
location using "cd" command (confirm it using ls command) and type
valgrind ./main

there are 2 structs - Object is the element in the hash table, Table represents the hash table


******************** PROGRAM FUNCTIONS *************************
/**
* The function gets the original size and the type of the data in the table elements.
* it initializes the Table struct members. 
* On success, the function returns a pointer to the new created Table, otherwise, it return NULL.
*/
Table* createTable(int size, int dType, int listLength);
input: size of table, type of table, length of list elements
output: returns pointer to the hash table

/**
* The function release all the allocated members of struct Table.
*/
void freeTable(Table* table);
input: pointer of hash table
output: frees the tables from memory

/**
* The function adds data to the hashtable (as described in the exe definition)
* On success, the function returns the array index of the added data, otherwise, it return -1.
*/
int add(Table* table, void* data);
input: pointer to hash table, data to add
output: returns the array index of the added data, else return -1


/**
* The function removes the Object which its data equals to data, if there are more than one, it removes the first one.
* On success, the function returns the array index of the removed data, otherwise, it returns -1.
* -1 is also returned in the case where there is no such object.
*/
int removeObj(Table* table, void* data);
input: pointer to hash table, data to add
output: returns the array index of the removed data, else return -1


/**
* The function search for an object that its data is equal to data and returns a pointer to that object.
* If there is no such object or in a case of an error, NULL is returned.
*/
Object* search(Table* table, void* data);
input: pointer to hash table, data to search
output: return the object with the specific data we search


/**
* The function print the table (the format is in the exe definition)
*/
void printTable(Table* table);
input: pointer to hash table
output: prints the table with the specific format (the format is [idx]\t*data*\t-->\t for each index)


/**
* This function creates an object and return the pointer to it or NULL if there is some error.
*/
Object* createObject(void* data);
input: data to add
output: pointer to Object with the entered data


/**
* This function frees an object,  note the in the case of STR_TYPE, the data
* of the object should also be freed.
*/
void freeObject(Object* obj, int type);
input: pointer to the Object, type of Table
output: frees the object, if the type is string then frees the string


/**
* check the equality of the data of two objects. The implementation is different depending the type of the data.
* the function returns 0 if they are equal or some other value if they are not equal.
*/
int isEqual(int type, void* data1, void* data2);
input: type of Table, data1 and data2 are the variables we compare
output: return 0 if the datas are equal, else return -1


/**
* returns the hash value of an integer, which is key mod origSize 
*/
int intHashFun(int* key, int origSize);
input: pointer to key, original size of table
output: return the index of the key, else returns -1


/**
* returns the hash value of an string, which is m mod origSize, where m is the sum of the ascii value of all the 
* character in key. 
*/
int strHashFun(char* key, int origSize);
input: pointer to key, original size of table
output: return the index of the key, else returns -1


/* adds element to linked list, if succeed return 0, else -1 */
int add_element(Table* table, Object* obj, int index);
input: pointer to Table, pointer to Ojbect we want to add, index where we are adding the Object
output: retruns 0 if succeed, else -1


/* expands the length of the array and reallocates the elements in the array */
int array_expansion(Table* table);
input: pointer to Table
output: returns 0 if succeed to epxand the array and reallocte the elements, else -1


/* generates the index from hash function */
int hash_func(Table* table, void* data);
input: pointer to Table, data to add
output: returns the index of where we need to add the data, else returns -1


int main() command:
input: none
output: This program simulates access to the physical memory while using paging mechanism
that has been fully tested with valgrind to test for memory
leak, no leak was found.