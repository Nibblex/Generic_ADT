#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "../common/defs.h"

/**
 * Implementation of a FIFO Abstract Data Type
 *
 * Notes :
 * 1) You have to correctly implement copy, delete and debug operators
 * by handling NULL value, otherwise you can end up with an undefined behaviour.
 * The prototypes of these functions are :
 * elem_t (*copy_op)(elem_t)
 * void (*delete_op)(elem_t)
 * void (*debug_op)(void *)
 *
 * 2) queue__front() and queue_back() return a dynamically allocated pointer to an element of
 * the queue in order to make it survive independently of the queue life cycle.
 * The user has to manually free the return pointer after usage.
 */
typedef struct QueueSt * Queue;

/**
 * generical element type
 */
typedef void * elem_t;

/**
 * data types used in 'queue__from_array' function as a parameter
 */
typedef enum  { CHAR = 0, INT, FLOAT, STRING, GENERAL} DataType;

/**
 * function pointer for lambda applying
 */
typedef elem_t (*copy_operator_t)(elem_t);

/**
 * function pointer for lambda applying
 */
typedef void (*delete_operator_t)(elem_t);

/**
 * function pointer for lambda applying
 */
typedef void (*applying_func_t)(elem_t, void *);

/**
 * function pointer for element comparison
 */
typedef int (*compare_func_t)(const void *, const void *);


/**
 * @brief Create an empty queue with copy enabled
 * @note Complexity: O(1)
 * @param copy_op copy operator
 * @param delete_op delete operator
 * @return a newly created queue, NULL on error
 */
Queue queue__empty_copy_enabled(const copy_operator_t copy_op, const delete_operator_t delete_op);


/**
 * @brief Create an empty queue with copy disabled
 * @note Complexity: O(1)
 * @return a newly created queue, NULL on error
 */
Queue queue__empty_copy_disabled(void);


/**
 * @brief Push an element in the queue
 * @note Complexity: O(1)
 * @param q the queue
 * @param element the element to add
 * @return 0 on success, 1 otherwise
 */
char queue__enqueue(const Queue q, const elem_t element);


/**
 * @brief Pop the front element out of the queue
 * @note Complexity: O(1)
 * @param q the queue
 * @return 0 on success, 1 otherwise
 */
char queue__dequeue(const Queue q);


/**
 * @brief Retrieve a copy of the front element (similar to 'queue__front' but the element is dequeued)
 * @details The element must be manually freed by user afterward
 * @note Complexity: O(1)
 * @param q the queue
 * @param front pointer to storage variable
 * @return 0 on success, 1 otherwise
 */
char queue__pop(const Queue q, elem_t *front);


/**
 * @brief Retrieve a copy of the front element
 * @details The element must be manually freed by user afterward
 * @note Complexity: O(1)
 * @param q the queue
 * @param front pointer to storage variable
 * @return 0 on success, 1 otherwise
 */
char queue__front(const Queue q, elem_t *front);


/**
 * @brief Retrieve a copy of the back element
 * @details The element must be manually freed by user afterward
 * @note Complexity: O(1)
 * @param q the queue
 * @param back pointer to storage variable
 * @return 0 on success, 1 otherwise
 */
char queue__back(const Queue q, elem_t *back);


/**
 * @brief Verify if the queue is empty
 * @note Complexity: O(1)
 * @param q the queue
 * @return 1 if empty, 0 otherwise
 */
char queue__is_empty(const Queue q);


/**
 * @brief Count the number of elements in the queue
 * @note Complexity: O(1)
 * @param q the queue
 * @return an unsigned integer corresponding to the number of elements in the queue
 */
size_t queue__size(const Queue q);


/**
 * @brief Verify if the element's copy is enabled for the given queue
 * @note Complexity: O(1)
 * @param q the queue
 * @return 1 if copy is enabled, 0 otherwise
 */
char queue__is_copy_enabled(const Queue q);

/**
 * @brief Enqueues the first 'n_elems' elements of the given array in the given queue
 * @details If the queue already has elements they are kept in that queue
 * @note Complexity: O(n)
 * @param q the queue, if q == NULL creates a new one with copy disabled by default
 * @param A the array, if A == NULL returns the queue received unaltered
 * @param n_elems number of elements to enqueue, must be less than the array length
 * @param type type of array elements, available types: 'CHAR', 'INT', 'FLOAT', 'STRING', 'GENERAL'
 * @return a queue containing all the elements of the array, NULL on error
 */
Queue queue__from_array(Queue q, void *A, size_t n_elems, DataType type);


/**
 * @brief Retrieves a copy of all items in a queue stored in array
 * @details The array must be manually freed by user afterward
 * @note Complexity: O(n)
 * @param q the queue
 * @return a dynamically allocated array which contains all the elements from the given queue, NULL on error
 */
elem_t *queue__to_array(const Queue q);


/**
 * @brief Uses qsort to sort the queue using the comparison criteria given by the received compare function
 * @note Complexity: O(n*log(n))
 * @param q the queue
 * @param f the compare function
 */
void queue__sort(const Queue q, const compare_func_t f);


/**
 * @brief Maps a function to the given queue
 * @note Complexity: O(n) with copy enabled, O(n²) with copy disabled
 * @param q the queue
 * @param f the applying function
 * @param user_data optional data to be used as an additional argument of the application function
 */
void queue__foreach(const Queue q, const applying_func_t f, void *user_data);


/**
 * @brief If copy is enabled frees all allocated memory used by the elements in the queue, the queue is still usable afterwards
 * @note Complexity: O(n) with copy enabled, O(1) with copy disabled
 * @param q the queue to clear
 */
void queue__clear(const Queue q);


/**
 * @brief Free all allocated memory used by the queue including memory used by queue elements in case of having the copy enabled
 * @note Complexity: O(n) with copy enabled, O(1) with copy disabled
 * @param q the queue to free
 */
void queue__free(const Queue q);


/**
 * @brief Prints the queue's content
 * @note Complexity: O(n)
 * @param q the queue to debug
 * @param debug_op debug operator
 */
void queue__debug(const Queue q, void (*debug_op) (void *));


#endif