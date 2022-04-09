#include <stdlib.h>
#include <string.h>
#include "message.h"

struct int_msg_message* int_msg_message_create(){
    struct int_msg_message* new_msg = (struct int_msg_message*)malloc(sizeof(struct int_msg_message));
    new_msg->value = 0;
    return new_msg;
}
void int_msg_message_free(struct int_msg_message* msg){
    if(msg == NULL) return;
    free(msg);
}
void int_msg_message_get_value(int64_t* value, struct int_msg_message* msg){
    *value = msg->value;
    return;

}
void int_msg_message_set_value(struct int_msg_message* msg, int64_t value){
    msg->value = value;
    return;
}

struct float_msg_message* float_msg_message_create(){
    struct float_msg_message* new_msg = (struct float_msg_message*)malloc(sizeof(struct float_msg_message));
    new_msg->value = 0.0;
    return new_msg;
}
void float_msg_message_free(struct float_msg_message* msg){
    if(msg == NULL) return;
    free(msg);
}
void float_msg_message_get_value(double* value, struct float_msg_message* msg){
    *value = msg->value;
    return;
}
void float_msg_message_set_value(struct float_msg_message* msg, double value){
    msg->value = value;
    return;
}

struct string_msg_message* string_msg_message_create(){
    struct string_msg_message* new_msg = (struct string_msg_message*)malloc(sizeof(struct string_msg_message));
    new_msg->value = NULL;
    return new_msg;
}
void string_msg_message_free(struct string_msg_message* msg){
    if(msg == NULL) return;
    if(msg->value != NULL) free(msg->value);
    free(msg);
}
void string_msg_message_get_value(char** value, struct string_msg_message* msg){
    *value = msg->value;

    return;
}
void string_msg_message_set_value(struct string_msg_message* msg, char* value){
    int len = strlen(value);
    if( msg->value != NULL ){
        free(msg->value);
    }
    msg->value = (char*)malloc(len + 1);
    strcpy(msg->value, value);
    return;
}

struct array_int64* array_int64_create(int size){
    struct array_int64* new_array = (struct array_int64*)malloc(sizeof(struct array_int64));
    new_array->size = size;
    new_array->value = (int64_t*)malloc(sizeof(int64_t) * (new_array->size));
    return new_array;
}
int array_int64_get(int64_t* value, struct array_int64* array, int index){
    int64_t* vvalue = (int64_t*)value;
    if( index >= array->size ){
        return -1;
    }
    *vvalue = (array->value)[index];
    return 0;
}
int array_int64_set(struct array_int64* array, int64_t value, int index){
    if( index >= array->size ){
        return -1;
    }
    array->value[index] = value;
    return 0;
}
void array_int64_free(struct array_int64* array){
    if( array != NULL && array->value != NULL ){
        free(array->value);
    }
    if( array != NULL ){
        free(array);
    }
}
int array_int64_size(struct array_int64* array){
    if( array != NULL ){
        return array->size;
    }
    return -1;
}

struct array_int_message* array_int_message_create(){
    struct array_int_message* new_msg = (struct array_int_message*)malloc(sizeof(struct array_int_message));
    new_msg->value = array_int64_create(5);
    return new_msg;
}
void array_int_message_free(struct array_int_message* msg){
    if(msg == NULL) return;
    array_int64_free(msg->value);
    free(msg);
}
int array_int_message_get_value(int64_t* value, int index, struct array_int_message* msg){
    return array_int64_get(value, msg->value, index);
}
int array_int_message_set_value(struct array_int_message* msg, int64_t value, int index){
    return array_int64_set(msg->value, value, index);
}

struct array_float64* array_float64_create(int size){
    struct array_float64* new_array = (struct array_float64*)malloc(sizeof(struct array_float64));
    new_array->size = size;
    new_array->value = (double*)malloc(sizeof(double) * (new_array->size));
    return new_array;
}
int array_float64_get(double* value, struct array_float64* array, int index){
    double* vvalue = (double*)value;
    if( index >= array->size ){
        return -1;
    }
    *vvalue = (array->value)[index];
    return 0;
}
int array_float64_set(struct array_float64* array, double value, int index){
    if( index >= array->size ){
        return -1;
    }
    array->value[index] = value;
    return 0;
}
void array_float64_free(struct array_float64* array){
    if( array != NULL && array->value != NULL ){
        free(array->value);
    }
    if( array != NULL ){
        free(array);
    }
}
int array_float64_size(struct array_float64* array){
    if( array != NULL ){
        return array->size;
    }
    return -1;
}

struct array_float_message* array_float_message_create(){
    struct array_float_message* new_msg = (struct array_float_message*)malloc(sizeof(struct array_float_message));
    new_msg->value = array_float64_create(5);
    return new_msg;
}
void array_float_message_free(struct array_float_message* msg){
    if(msg == NULL) return;
    array_float64_free(msg->value);
    free(msg);
}
int array_float_message_get_value(double* value, int index, struct array_float_message* msg){
    return array_float64_get(value, msg->value, index);
}
int array_float_message_set_value(struct array_float_message* msg, double value, int index){
    return array_float64_set(msg->value, value, index);
}

struct array_string* array_string_create(int size){
    struct array_string* new_array = (struct array_string*)malloc(sizeof(struct array_string));
    new_array->size = size;
    new_array->value = (char**)malloc(sizeof(char*) * (new_array->size));
    memset(new_array->value, 0, sizeof(char*) * (new_array->size));
    return new_array;
}
int array_string_get(char** value, struct array_string* array, int index){
    char** vvalue = (char**)value;
    if( index >= array->size ){
        return -1;
    }
    *vvalue = (array->value)[index];
    return 0;
}
int array_string_set(struct array_string* array, char* value, int index){
    if( index >= array->size ){
        return -1;
    }
    if( array->value[index] != NULL ){
        free(array->value[index]);
    }
    array->value[index] = (char*)malloc(strlen(value) + 1);
    strcpy(array->value[index], value);
    return 0;
}
void array_string_free(struct array_string* array){
    int i = 0;
    if( array != NULL ){
        for( i = 0; i < array->size; i++ ){
        }
        free(array->value);
        free(array);
    }
}
int array_string_size(struct array_string* array){
    if( array != NULL ){
        return array->size;
    }
    return -1;
}

struct array_string_message* array_string_message_create(){
    struct array_string_message* new_msg = (struct array_string_message*)malloc(sizeof(struct array_string_message));
    new_msg->value = array_string_create(5);
    return new_msg;
}
void array_string_message_free(struct array_string_message* msg){
    if(msg == NULL) return;
    array_string_free(msg->value);
    free(msg);
}
int array_string_message_get_value(char** value, int index, struct array_string_message* msg){
    return array_string_get(value, msg->value, index);
}
int array_string_message_set_value(struct array_string_message* msg, char* value, int index){
    return array_string_set(msg->value, value, index);
}

struct array_bool* array_bool_create(int size){
    int buffer_size = size / 8;
    if( size % 8 != 0 ){
        buffer_size++;
    }
    struct array_bool* new_array = (struct array_bool*)malloc(sizeof(struct array_bool));
    new_array->size = size;
    new_array->value = (char*)malloc(buffer_size);
    memset(new_array->value, 0, buffer_size);
    return new_array;
}
int array_bool_get(char* value, struct array_bool* array, int index){
    if( index >= array->size ){
        return -1;
    }
    int offset = index / 8;
    int offset_bit = index % 8;
    char one_byte = (array->value)[offset];
    *value = (0x80 >> offset_bit) & one_byte;
    return 0;
}
int array_bool_set(struct array_bool* array, char value, int index){
    if( index >= array->size ){
        return -1;
    }
    int offset = index / 8;
    int offset_bit = index % 8;
    if( value ){
        array->value[offset] |= 0x80 >> offset_bit;
    }
    else{
        array->value[offset] &= ~(0x80 >> offset_bit);
    }
    return 0;
}
void array_bool_free(struct array_bool* array){
    if( array != NULL && array->value != NULL ){
        free(array->value);
    }
    if( array != NULL ){
        free(array);
    }
}
int array_bool_size(struct array_bool* array){
    if( array != NULL ){
        return array->size;
    }
    return -1;
}

struct array_bool_message* array_bool_message_create(){
    struct array_bool_message* new_msg = (struct array_bool_message*)malloc(sizeof(struct array_bool_message));
    new_msg->value = array_bool_create(5);
    return new_msg;
}
void array_bool_message_free(struct array_bool_message* msg){
    if(msg == NULL) return;
    array_bool_free(msg->value);
    free(msg);
}
int array_bool_message_get_value(char* value, int index, struct array_bool_message* msg){
    return array_bool_get(value, msg->value, index);
}
int array_bool_message_set_value(struct array_bool_message* msg, char value, int index){
    return array_bool_set(msg->value, value, index);
}

struct bool_msg_message* bool_msg_message_create(){
    struct bool_msg_message* new_msg = (struct bool_msg_message*)malloc(sizeof(struct bool_msg_message));
    new_msg->value = 0;
    return new_msg;
}
void bool_msg_message_free(struct bool_msg_message* msg){
    if(msg == NULL) return;
    free(msg);
}
void bool_msg_message_get_value(char* value, struct bool_msg_message* msg){
    *value = msg->value;
    return;
}
void bool_msg_message_set_value(struct bool_msg_message* msg, char value){
    msg->value = value;
    return;
}
