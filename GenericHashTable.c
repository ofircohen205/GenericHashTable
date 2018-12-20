/* NAME: Ofir Cohen
*  ID: 312255847
*  DATE: 15/12/2018
*
* This program is an implementation of generic hash table
*/

#include "GenericHashTable.h"


/**
* The function gets the original size and the type of the data in the table elements.
* it initializes the Table struct members. 
* On success, the function returns a pointer to the new created Table, otherwise, it return NULL.
*/
Table* createTable(int size, int dType, int listLength)
{
    if(size <= 0 || listLength <= 0 || (dType != STR_TYPE && dType != INT_TYPE))
    {
        return NULL;
    }

    Table* table = (Table*)malloc(sizeof(Table));
    if(table == NULL)
    {
        return NULL;
    }
    table->dType = dType;
    table->list_length = listLength;
    table->original_size = size;
    table->curr_size = size;
    table->arr = (Object**)malloc(sizeof(Object*)*size);
    if(table->arr == NULL)
    {
        return NULL;
    }

    int i;
    for(i = 0; i < size; i++)
    {
        table->arr[i] = createObject(NULL);
    }

    return table;
}


/**
* The function release all the allocated members of struct Table.
*/
void freeTable(Table* table)
{
    if(table == NULL)
    {
        perror("Error: one of the parameters you have entered is NULL\n");
        return;
    }

    
    int i;
    for(i = 0; i < table->curr_size; i++)
    {
        Object *curr = table->arr[i];
        while(curr)
        {
            #if defined(DEBUG)
                printf("freed object\n");
            #endif
            Object* next = curr->next;
            freeObject(curr, table->dType);
            curr = next;
        }
    }
    free(table->arr);
    free(table);
    #if defined(DEBUG)
        printf("freed array & table\n");
    #endif
}


/**
* The function adds data to the hashtable (as described in the exe definition)
* On success, the function returns the array index of the added data, otherwise, it return -1.
*/
int add(Table* table, void* data)
{
    if(table == NULL || data == NULL)
    {
        perror("Error: one of the parameters you have entered is NULL\n");
        return FAILED;
    }


    // createObject
    Object* obj = NULL;
    if(table->dType == STR_TYPE)
    {
        char* tmp = (char*)malloc(sizeof(data)+1);
        if(tmp == NULL)
        {
            return FAILED;
        }
        strcpy(tmp, (char*)data);
        obj = createObject((void*)tmp);
    }
    else if(table->dType == INT_TYPE)
    {
        obj = createObject(data);
    }

    if(obj == NULL)
    {
        return FAILED;
    }
    // get index index from Hash function * d (d == curr_size / original_size)
    int index = hash_func(table, data);
    // go to index in Obejct** arr and check if there is place in list
    // if there is place (return 0 from function) then insert element
    if(add_element(table, obj, index) == SUCCESS)
    {
        return index;
    }
        // there is no place in the linked list
    else
    {
        // double the size of Object** arr
        // reallocate elements in Object** arr
        if(array_expansion(table) == FAILED)
        {
            return FAILED;
        }

        // and insert the element to the new index value
        if(add_element(table, obj, 2*index+1) == SUCCESS)
        {
            return index;
        }
    }
    return FAILED;
}


/**
* The function removes the Object which its data equals to data, if there are more than one, it removes the first one.
* On success, the function returns the array index of the removed data, otherwise, it returns -1.
* -1 is also returned in the case where there is no such object.
*/
int removeObj(Table* table, void* data)
{
    if(table == NULL || data == NULL)
    {
        perror("Error: one of the parameters you have entered is NULL\n");
        return FAILED;
    }

    int index = hash_func(table, data);
    int d = table->curr_size / table->original_size;

    while(d != 0)
    {
        Object* ptr = table->arr[index]->next;
        if(ptr)
        {
            Object* prev = table->arr[index]->next;
            if(isEqual(table->dType, ptr->data, data) == SUCCESS)
            {
                table->arr[index]->next = ptr->next;
                freeObject(ptr, table->dType);
                //free(ptr);
                return index;
            }

            while(ptr)
            {
                if(isEqual(table->dType, ptr->data, data) == 0)
                {
                    prev->next = ptr->next;
                    freeObject(ptr, table->dType);
                    //free(ptr);
                    return index;
                }
                ptr = ptr->next;
            }
        }
        d--;
        index++;
    }

    return FAILED;
}


/**
* The function search for an object that its data is equal to data and returns a pointer to that object.
* If there is no such object or in a case of an error, NULL is returned.
*/
Object* search(Table* table, void* data)
{
    if(table == NULL || data == NULL)
    {
        perror("Error: one of the parameters you have entered is NULL\n");        
        return NULL;
    }

    int index = hash_func(table, data);
    int d = table->curr_size / table->original_size;

    while(d != 0)
    {
        Object* ptr = table->arr[index]->next;
        while(ptr)
        {
            if(isEqual(table->dType, ptr->data, data) == 0)
            {
                return ptr;
            }
            ptr = ptr->next;
        }
        d--;
        index++;
    }
    return NULL;
}


/**
* The function print the table (the format is in the exe definition)
*/
void printTable(Table* table)
{
    if(table == NULL)
    {
        perror("Error: one of the parameters you have entered is NULL\n");        
        return;
    }

    int i;
    for(i = 0; i < table->curr_size; i++)
    {
        Object* ptr = table->arr[i]->next;
        printf("[%d]", i);
        while(ptr)
        {
            printf("\t");
            if(table->dType == INT_TYPE)
            {
                printf("%d", *(int*)ptr->data);
            }
            else if(table->dType == STR_TYPE)
            {
                printf("%s", (char*)ptr->data);
            }
            printf("\t-->");
            ptr = ptr->next;
        }
        printf("\n");
    }
}


/**
* This function creates an object and return the pointer to it or NULL if there is some error.
*/
Object* createObject(void* data)
{
    Object* object = (Object*)malloc(sizeof(Object));
    if(object == NULL)
    {
        return NULL;
    }
    object->data = data;
    object->next = NULL;

    return object;
}


/**
* This function frees an object,  note the in the case of STR_TYPE, the data
* of the object should also be freed.
*/
void freeObject(Object* obj, int type)
{
    if(type == STR_TYPE)
    {
        free(obj->data);
    }
    free(obj);
}


/**
* check the equality of the data of two objects. The implementation is different depending the type of the data.
* the function returns 0 if they are equal or some other value if they are not equal.
*/
int isEqual(int type, void* data1, void* data2)
{
    if(type != STR_TYPE && type != INT_TYPE)
    {
        perror("Error: one of the parameters you have entered is NULL\n");        
        return FAILED;        
    }
    
    if(type == INT_TYPE)
    {
        return ((*(int*)data1) == (*(int*)data2)) ? SUCCESS : FAILED;
    }
    else if(type == STR_TYPE)
    {
        return strcmp((char*)data1, (char*)data2);
    }
    return FAILED;
}


/**
* returns the hash value of an integer, which is key mod origSize 
*/
int intHashFun(int* key, int origSize)
{
    return *(key) % origSize;
}


/**
* returns the hash value of an string, which is m mod origSize, where m is the sum of the ascii value of all the 
* character in key. 
*/
int strHashFun(char* key, int origSize)
{
    int sum = 0, i = 0;
    for(i = 0; key[i] != '\0'; i++)
    {
        sum += key[i];
    }
    return sum % origSize;
}


/* adds element to linked list, if succeed return 0, else 1 */
int add_element(Table* table, Object* obj, int index)
{
    int d = table->curr_size/table->original_size;
    int i;
    for(i = d; i > 0; i--)
    {
        int count = 0;
        Object* ptr = table->arr[index];
        while(ptr && ptr->next)
        {
            count++;
            ptr = ptr->next;
        }

        if(count < table->list_length)
        {
            ptr->next = obj;
            return SUCCESS;
        }
        index++;
    }

    return FAILED;
}


/* expands the length of the array and reallocates the elements in the array */
int array_expansion(Table* table)
{
    int new_size = table->curr_size * 2;
    table->arr = (Object**)realloc(table->arr, new_size*sizeof(Object*));
    if(table->arr == NULL)
    {
        return FAILED;
    }
    table->curr_size = new_size;

    int i;
    for(i = table->curr_size/2; i < table->curr_size; i++)
    {
        #if defined(DEBUG)
            printf("\n************\n");
            printf("added object\n");
        #endif
        table->arr[i] = createObject(NULL);
    }

    for(i = table->curr_size/2 - 1; i >= 0; i--)
    {
        table->arr[i*2]->next = table->arr[i]->next;
    }

    for(i = 1; i < table->curr_size; i++)
    {
        if(i % 2 != 0)
        {
            table->arr[i]->next = NULL;
        }
    }

    return SUCCESS;
}


/* generates the index from hash function */
int hash_func(Table* table, void* data)
{
    int hash_val = -1;
    int m = table->original_size;
    int d = table->curr_size / m;
    if(table->dType == INT_TYPE)
    {
        hash_val = d * intHashFun((int*)data, m);
    }
    else if(table->dType == STR_TYPE)
    {
        hash_val = d * strHashFun((char*)data, m);
    }
    int index = hash_val;

    return index;
}
