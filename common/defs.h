#ifndef __DEFS_H__
#define __DEFS_H__

#ifndef SUCCESS
#define SUCCESS 0
#endif
#ifndef FAILURE
#define FAILURE -1
#endif
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif


/**
 * Macro to pointer increment by __size bytes
 */
#define PTR_INCREMENT(__ptr, __size) \
    __ptr = (void *)((size_t)__ptr + (__size))

/**
 * Macro to pointer swap
 */
#define PTR_SWAP(__ptr1, __ptr2) do { \
    elem_t __temp = __ptr1; \
    __ptr1 = __ptr2; \
    __ptr2 = __temp; \
} while (false)

#define ARRAY_RESIZE(__ptr, __n_elems) do { \
    elem_t *realloc_res = realloc(__ptr->elems, sizeof(elem_t) * (__ptr->size + __n_elems)); \
    if (!realloc_res) return NULL; \
    __ptr->elems = realloc_res; \
    __ptr->capacity = __ptr->size + __n_elems; \
} while (false)

/**
 * Macro to grow capacity
 */
#define ARRAY_GROW(__ptr) do { \
    elem_t *realloc_res = NULL; \
    size_t new_capacity = __ptr->capacity<<1; \
    do { \
        realloc_res = realloc(__ptr->elems, sizeof(elem_t) * new_capacity); \
        if (!realloc_res) { \
            new_capacity = (new_capacity + __ptr->capacity)>>1; \
        } \
    } while (!realloc_res); \
    if (new_capacity == __ptr->capacity) return FAILURE; \
    __ptr->elems = realloc_res; \
    __ptr->capacity = new_capacity; \
} while (false)

/**
 * Macro to shrink capacity
 */
#define ARRAY_SHRINK(__ptr, __n_elems) do { \
    elem_t *realloc_res = realloc(__ptr->elems, sizeof(elem_t) * (__n_elems)); \
    if (realloc_res) { \
        __ptr->elems = realloc_res; \
        __ptr->capacity = (__n_elems); \
    } \
} while (false)

/**
 * Macro to array shuffle from __start to __end
 */
#define ARRAY_SHUFFLE(__ptr, __start, __end) do { \
    for (size_t i = (__start); i < __end; i++) { \
        a = ((__start) + (size_t)(rand() % (int)((__start) + (__end)))); \
        b = ((__start) + (size_t)(rand() % (int)((__start) + (__end)))); \
        PTR_SWAP(__ptr[a], __ptr[b]); \
    } \
} while (false)

/**
 * Macro to clean NULL elements in array from __start to __end
 */
#define CLEAN_NULL_ELEMS(__ptr, __start, __end) \
    size_t k = 0; \
    for (size_t i = (__start); i < (__end); i++) { \
        if (__ptr->elems[i]) { \
            __ptr->elems[k] = __ptr->elems[i]; \
            k++; \
        } \
    } \
    __ptr->size = k

/**
 * Macro to free internal memory used by elements in the structure
 */
#define FREE_ELEMS(__ptr, __start, __end) do { \
    if (__ptr->operator_delete && __ptr->elems) { \
        for (size_t i = (__start); i < (__end); i++) { \
            __ptr->operator_delete(__ptr->elems[i]); \
        } \
    } \
} while (false)

/**
 * Generical element type
 */
typedef void * elem_t;

/**
 * Function pointer required to copy an entity within the structure
 */
typedef elem_t (*copy_operator_t)(elem_t);

/**
 * Function pointer required to delete an entity within the structure
 */
typedef void (*delete_operator_t)(elem_t);

/**
 * Function pointer for lambda applying
 */
typedef void (*applying_func_t)(elem_t, void *);

/**
 * Function pointer for element comparison
 */
typedef int (*compare_func_t)(const void *, const void *);

#endif
