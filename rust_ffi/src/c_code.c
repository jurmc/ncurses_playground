#include<stdio.h>

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

typedef struct SomeStruct {
    int *fields;
    size_t len;
} SomeStructType;

void dump_c_array(SomeStructType *some_struct)
{
    printf("[C] some_struct->len: %i\n", some_struct->len);
    for (size_t idx = 0; idx < some_struct->len; ++idx) {
        printf(" [C] some_struct[%i]: %i\n", idx, some_struct->fields[idx]);
    }
}

void modify_c_array(SomeStructType *some_struct)
{
    for (size_t idx = 0; idx < some_struct->len; ++idx) {
        some_struct->fields[idx] = some_struct->fields[idx] * 2;
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

void dump_all(void)
{
    dump_c_char(97);
    dump_c_unsigned_char(97);
    dump_c_short(97);
}
