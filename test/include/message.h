#pragma once
#include <stdint.h>

struct int_msg_message{
        int64_t value;
};
struct int_msg_message* int_msg_message_create();
void int_msg_message_free(struct int_msg_message* msg);
void int_msg_message_set_value(struct int_msg_message* msg, int64_t value);
void int_msg_message_get_value(int64_t* value, struct int_msg_message* msg);

struct float_msg_message{
        double value;
};
struct float_msg_message* float_msg_message_create();
void float_msg_message_free(struct float_msg_message* msg);
void float_msg_message_set_value(struct float_msg_message* msg, double value);
void float_msg_message_get_value(double* value, struct float_msg_message* msg);

struct string_msg_message{
        char* value;
};
struct string_msg_message* string_msg_message_create();
void string_msg_message_free(struct string_msg_message* msg);
void string_msg_message_set_value(struct string_msg_message* msg, char* value);
void string_msg_message_get_value(char** value, struct string_msg_message* msg);

struct array_int64{
    int size;
    int64_t* value;
};
struct array_int64* array_int64_create(int size);
int array_int64_get(int64_t* value, struct array_int64* array, int index);
int array_int64_set(struct array_int64* array, int64_t value, int index);
void array_int64_free(struct array_int64* array);
int array_int64_size(struct array_int64* array);

struct array_int_message{
        struct array_int64* value;
};
struct array_int_message* array_int_message_create();
void array_int_message_free(struct array_int_message* msg);
int array_int_message_set_value(struct array_int_message* msg, int64_t value, int index);
int array_int_message_get_value(int64_t* value, int index, struct array_int_message* msg);

struct array_float64{
    int size;
    double* value;
};
struct array_float64* array_float64_create(int size);
int array_float64_get(double* value, struct array_float64* array, int index);
int array_float64_set(struct array_float64* array, double value, int index);
void array_float64_free(struct array_float64* array);
int array_float64_size(struct array_float64* array);

struct array_float_message{
        struct array_float64* value;
};
struct array_float_message* array_float_message_create();
void array_float_message_free(struct array_float_message* msg);
int array_float_message_set_value(struct array_float_message* msg, double value, int index);
int array_float_message_get_value(double* value, int index, struct array_float_message* msg);

struct array_string{
    int size;
    char** value;
};
struct array_string* array_string_create(int size);
int array_string_get(char** value, struct array_string* array, int index);
int array_string_set(struct array_string* array, char* value, int index);
void array_string_free(struct array_string* array);
int array_string_size(struct array_string* array);

struct array_string_message{
        struct array_string* value;
};
struct array_string_message* array_string_message_create();
void array_string_message_free(struct array_string_message* msg);
int array_string_message_set_value(struct array_string_message* msg, char* value, int index);
int array_string_message_get_value(char** value, int index, struct array_string_message* msg);

struct array_bool{
    int size;
    char* value;
};
struct array_bool* array_bool_create(int size);
int array_bool_get(char* value, struct array_bool* array, int index);
int array_bool_set(struct array_bool* array, char value, int index);
void array_bool_free(struct array_bool* array);
int array_bool_size(struct array_bool* array);

struct array_bool_message{
        struct array_bool* value;
};
struct array_bool_message* array_bool_message_create();
void array_bool_message_free(struct array_bool_message* msg);
int array_bool_message_set_value(struct array_bool_message* msg, char value, int index);
int array_bool_message_get_value(char* value, int index, struct array_bool_message* msg);

struct bool_msg_message{
        char value;
};
struct bool_msg_message* bool_msg_message_create();
void bool_msg_message_free(struct bool_msg_message* msg);
void bool_msg_message_set_value(struct bool_msg_message* msg, char value);
void bool_msg_message_get_value(char* value, struct bool_msg_message* msg);
