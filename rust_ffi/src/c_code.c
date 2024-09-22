#include<stdio.h>
#include<stdlib.h>

/* c_char Equivalent to C’s char type */
void dump_c_char(char v)
{
    printf("[C] char: c: %c d: %d\n", v, v);
}

/* c_uchar Equivalent to C’s unsigned char type */
void dump_c_unsigned_char(unsigned char v)
{
    printf("[C] unsigned char: c: %c d: %d\n", v, v);
}

/* c_short Equivalent to C’s signed short (short) type. */
void dump_c_short(signed short v)
{
    printf("[C] signed short: hi: %hi\n", v);
}

void dump_c_string(char *s) {
    printf("[C] char *: s: %s\n", s);
}

typedef struct StructWithArray {
    int *fields;
    size_t len;
} SomeStructType;

void dump_c_struct_containing_array(SomeStructType *struct_with_array)
{
    printf("[C] struct_with_array->len: %zu\n", struct_with_array->len);
    for (size_t idx = 0; idx < struct_with_array->len; ++idx) {
        printf(" [C] struct_with_array[%zu]: %i\n", idx, struct_with_array->fields[idx]);
    }
}

void modify_c_struct_containing_array(SomeStructType *struct_with_array)
{
    for (size_t idx = 0; idx < struct_with_array->len; ++idx) {
        struct_with_array->fields[idx] = struct_with_array->fields[idx] * 2;
    }
}

void dump_p_c_char(const char *const v)
{
    printf("[C ptr] char: c: %c d: %d\n", *v, *v);
}

void dump_p_c_unsigned_char(const unsigned char *const v)
{
    printf("[C ptr] unsigned char: c: %c d: %d\n", *v, *v);
}

void dump_p_c_short(const signed short *const v)
{
    printf("[C ptr] signed short: hi: %hi\n", *v);
}


int *allocate_array_in_c(size_t len, int val)
{
    int *retval = calloc(len, sizeof(int));

    for (size_t i = 0; i < len; ++i) {
        retval[i] = val++;
    }

    for (size_t i = 0; i < len; ++i) {
        printf("[C} allocate_array_in_c: %i\n", retval[i]);
    }

    return retval;
}

void deallocate_array_in_c(int *p) {
    free(p);
}
