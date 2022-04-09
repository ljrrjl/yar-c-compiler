#include "client.h"
#include "yar.h"
#include "msgpack.h"

void* yar_protoc_call(char* hostname, char* group, char* func, void* input){
    yar_client *client = NULL;
    yar_packager* packager = NULL;
    if( strcmp(group, "Test") == 0 ){
        if( strcmp(func, "test_int_int_1") == 0 ){
            struct int_msg_message* input_msg = (struct int_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            int64_t value = 0;
            int_msg_message_get_value(&value, input_msg);
            yar_pack_push_long(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_int_int_1_handler", 1, &packager);
                if( response ){
                    struct int_msg_message* output_msg = int_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            int_msg_message_set_value(output_msg, kv_data->val.via.i64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_int_float_2") == 0 ){
            struct int_msg_message* input_msg = (struct int_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            int64_t value = 0;
            int_msg_message_get_value(&value, input_msg);
            yar_pack_push_long(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_int_float_2_handler", 1, &packager);
                if( response ){
                    struct float_msg_message* output_msg = float_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            float_msg_message_set_value(output_msg, kv_data->val.via.f64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_int_string_3") == 0 ){
            struct int_msg_message* input_msg = (struct int_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            int64_t value = 0;
            int_msg_message_get_value(&value, input_msg);
            yar_pack_push_long(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_int_string_3_handler", 1, &packager);
                if( response ){
                    struct string_msg_message* output_msg = string_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            uint32_t val_strlength = kv_data->val.via.str.size;
                            char* str = (char*)malloc(val_strlength + 1);
                            memset(str, 0, val_strlength + 1);
                            memcpy(str, kv_data->val.via.str.ptr, val_strlength);
                            string_msg_message_set_value(output_msg, str);
                            free(str);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_int_array_int_4") == 0 ){
            struct int_msg_message* input_msg = (struct int_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            int64_t value = 0;
            int_msg_message_get_value(&value, input_msg);
            yar_pack_push_long(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_int_array_int_4_handler", 1, &packager);
                if( response ){
                    struct array_int_message* output_msg = array_int_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                int64_t value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                yar_unpack_data_value(array_value, &value);
                                array_int_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_int_array_float_5") == 0 ){
            struct int_msg_message* input_msg = (struct int_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            int64_t value = 0;
            int_msg_message_get_value(&value, input_msg);
            yar_pack_push_long(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_int_array_float_5_handler", 1, &packager);
                if( response ){
                    struct array_float_message* output_msg = array_float_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_int_array_string_6") == 0 ){
            struct int_msg_message* input_msg = (struct int_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            int64_t value = 0;
            int_msg_message_get_value(&value, input_msg);
            yar_pack_push_long(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_int_array_string_6_handler", 1, &packager);
                if( response ){
                    struct array_string_message* output_msg = array_string_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char* value = NULL;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                msgpack_object* obj = (msgpack_object*)array_value;
                                int length = obj->via.str.size;
                                value = (char*)malloc(length + 1);
                                memset(value, 0, length + 1);
                                memcpy(value, obj->via.str.ptr, length);
                                array_string_message_set_value(output_msg, value, index);
                                free(value);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_int_array_bool_7") == 0 ){
            struct int_msg_message* input_msg = (struct int_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            int64_t value = 0;
            int_msg_message_get_value(&value, input_msg);
            yar_pack_push_long(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_int_array_bool_7_handler", 1, &packager);
                if( response ){
                    struct array_bool_message* output_msg = array_bool_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                struct msgpack_object* obj = (struct msgpack_object*)array_value;
                                value = obj->via.boolean;
                                array_bool_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_int_bool_8") == 0 ){
            struct int_msg_message* input_msg = (struct int_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            int64_t value = 0;
            int_msg_message_get_value(&value, input_msg);
            yar_pack_push_long(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_int_bool_8_handler", 1, &packager);
                if( response ){
                    struct bool_msg_message* output_msg = bool_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            bool_msg_message_set_value(output_msg, kv_data->val.via.boolean);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_float_int_1") == 0 ){
            struct float_msg_message* input_msg = (struct float_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            double value = 0;
            float_msg_message_get_value(&value, input_msg);
            yar_pack_push_double(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_float_int_1_handler", 1, &packager);
                if( response ){
                    struct int_msg_message* output_msg = int_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            int_msg_message_set_value(output_msg, kv_data->val.via.i64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_float_float_2") == 0 ){
            struct float_msg_message* input_msg = (struct float_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            double value = 0;
            float_msg_message_get_value(&value, input_msg);
            yar_pack_push_double(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_float_float_2_handler", 1, &packager);
                if( response ){
                    struct float_msg_message* output_msg = float_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            float_msg_message_set_value(output_msg, kv_data->val.via.f64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_float_string_3") == 0 ){
            struct float_msg_message* input_msg = (struct float_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            double value = 0;
            float_msg_message_get_value(&value, input_msg);
            yar_pack_push_double(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_float_string_3_handler", 1, &packager);
                if( response ){
                    struct string_msg_message* output_msg = string_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            uint32_t val_strlength = kv_data->val.via.str.size;
                            char* str = (char*)malloc(val_strlength + 1);
                            memset(str, 0, val_strlength + 1);
                            memcpy(str, kv_data->val.via.str.ptr, val_strlength);
                            string_msg_message_set_value(output_msg, str);
                            free(str);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_float_array_int_4") == 0 ){
            struct float_msg_message* input_msg = (struct float_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            double value = 0;
            float_msg_message_get_value(&value, input_msg);
            yar_pack_push_double(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_float_array_int_4_handler", 1, &packager);
                if( response ){
                    struct array_int_message* output_msg = array_int_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                int64_t value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                yar_unpack_data_value(array_value, &value);
                                array_int_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_float_array_float_5") == 0 ){
            struct float_msg_message* input_msg = (struct float_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            double value = 0;
            float_msg_message_get_value(&value, input_msg);
            yar_pack_push_double(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_float_array_float_5_handler", 1, &packager);
                if( response ){
                    struct array_float_message* output_msg = array_float_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_float_array_string_6") == 0 ){
            struct float_msg_message* input_msg = (struct float_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            double value = 0;
            float_msg_message_get_value(&value, input_msg);
            yar_pack_push_double(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_float_array_string_6_handler", 1, &packager);
                if( response ){
                    struct array_string_message* output_msg = array_string_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char* value = NULL;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                msgpack_object* obj = (msgpack_object*)array_value;
                                int length = obj->via.str.size;
                                value = (char*)malloc(length + 1);
                                memset(value, 0, length + 1);
                                memcpy(value, obj->via.str.ptr, length);
                                array_string_message_set_value(output_msg, value, index);
                                free(value);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_float_array_bool_7") == 0 ){
            struct float_msg_message* input_msg = (struct float_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            double value = 0;
            float_msg_message_get_value(&value, input_msg);
            yar_pack_push_double(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_float_array_bool_7_handler", 1, &packager);
                if( response ){
                    struct array_bool_message* output_msg = array_bool_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                struct msgpack_object* obj = (struct msgpack_object*)array_value;
                                value = obj->via.boolean;
                                array_bool_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_float_bool_8") == 0 ){
            struct float_msg_message* input_msg = (struct float_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            double value = 0;
            float_msg_message_get_value(&value, input_msg);
            yar_pack_push_double(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_float_bool_8_handler", 1, &packager);
                if( response ){
                    struct bool_msg_message* output_msg = bool_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            bool_msg_message_set_value(output_msg, kv_data->val.via.boolean);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_string_int_1") == 0 ){
            struct string_msg_message* input_msg = (struct string_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char* value = NULL;
            string_msg_message_get_value(&value, input_msg);
            yar_pack_push_string(packager, value, strlen(value));
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_string_int_1_handler", 1, &packager);
                if( response ){
                    struct int_msg_message* output_msg = int_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            int_msg_message_set_value(output_msg, kv_data->val.via.i64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_string_float_2") == 0 ){
            struct string_msg_message* input_msg = (struct string_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char* value = NULL;
            string_msg_message_get_value(&value, input_msg);
            yar_pack_push_string(packager, value, strlen(value));
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_string_float_2_handler", 1, &packager);
                if( response ){
                    struct float_msg_message* output_msg = float_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            float_msg_message_set_value(output_msg, kv_data->val.via.f64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_string_string_3") == 0 ){
            struct string_msg_message* input_msg = (struct string_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char* value = NULL;
            string_msg_message_get_value(&value, input_msg);
            yar_pack_push_string(packager, value, strlen(value));
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_string_string_3_handler", 1, &packager);
                if( response ){
                    struct string_msg_message* output_msg = string_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            uint32_t val_strlength = kv_data->val.via.str.size;
                            char* str = (char*)malloc(val_strlength + 1);
                            memset(str, 0, val_strlength + 1);
                            memcpy(str, kv_data->val.via.str.ptr, val_strlength);
                            string_msg_message_set_value(output_msg, str);
                            free(str);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_string_array_int_4") == 0 ){
            struct string_msg_message* input_msg = (struct string_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char* value = NULL;
            string_msg_message_get_value(&value, input_msg);
            yar_pack_push_string(packager, value, strlen(value));
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_string_array_int_4_handler", 1, &packager);
                if( response ){
                    struct array_int_message* output_msg = array_int_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                int64_t value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                yar_unpack_data_value(array_value, &value);
                                array_int_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_string_array_float_5") == 0 ){
            struct string_msg_message* input_msg = (struct string_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char* value = NULL;
            string_msg_message_get_value(&value, input_msg);
            yar_pack_push_string(packager, value, strlen(value));
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_string_array_float_5_handler", 1, &packager);
                if( response ){
                    struct array_float_message* output_msg = array_float_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_string_array_string_6") == 0 ){
            struct string_msg_message* input_msg = (struct string_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char* value = NULL;
            string_msg_message_get_value(&value, input_msg);
            yar_pack_push_string(packager, value, strlen(value));
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_string_array_string_6_handler", 1, &packager);
                if( response ){
                    struct array_string_message* output_msg = array_string_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char* value = NULL;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                msgpack_object* obj = (msgpack_object*)array_value;
                                int length = obj->via.str.size;
                                value = (char*)malloc(length + 1);
                                memset(value, 0, length + 1);
                                memcpy(value, obj->via.str.ptr, length);
                                array_string_message_set_value(output_msg, value, index);
                                free(value);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_string_array_bool_7") == 0 ){
            struct string_msg_message* input_msg = (struct string_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char* value = NULL;
            string_msg_message_get_value(&value, input_msg);
            yar_pack_push_string(packager, value, strlen(value));
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_string_array_bool_7_handler", 1, &packager);
                if( response ){
                    struct array_bool_message* output_msg = array_bool_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                struct msgpack_object* obj = (struct msgpack_object*)array_value;
                                value = obj->via.boolean;
                                array_bool_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_string_bool_8") == 0 ){
            struct string_msg_message* input_msg = (struct string_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char* value = NULL;
            string_msg_message_get_value(&value, input_msg);
            yar_pack_push_string(packager, value, strlen(value));
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_string_bool_8_handler", 1, &packager);
                if( response ){
                    struct bool_msg_message* output_msg = bool_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            bool_msg_message_set_value(output_msg, kv_data->val.via.boolean);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_int_int_1") == 0 ){
            struct array_int_message* input_msg = (struct array_int_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            int64_t value;
            for( int i = 0; i < 5; i++ ){
                array_int_message_get_value(&value, i, input_msg);
                yar_pack_push_long(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_int_int_1_handler", 1, &packager);
                if( response ){
                    struct int_msg_message* output_msg = int_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            int_msg_message_set_value(output_msg, kv_data->val.via.i64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_int_float_2") == 0 ){
            struct array_int_message* input_msg = (struct array_int_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            int64_t value;
            for( int i = 0; i < 5; i++ ){
                array_int_message_get_value(&value, i, input_msg);
                yar_pack_push_long(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_int_float_2_handler", 1, &packager);
                if( response ){
                    struct float_msg_message* output_msg = float_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            float_msg_message_set_value(output_msg, kv_data->val.via.f64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_int_string_3") == 0 ){
            struct array_int_message* input_msg = (struct array_int_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            int64_t value;
            for( int i = 0; i < 5; i++ ){
                array_int_message_get_value(&value, i, input_msg);
                yar_pack_push_long(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_int_string_3_handler", 1, &packager);
                if( response ){
                    struct string_msg_message* output_msg = string_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            uint32_t val_strlength = kv_data->val.via.str.size;
                            char* str = (char*)malloc(val_strlength + 1);
                            memset(str, 0, val_strlength + 1);
                            memcpy(str, kv_data->val.via.str.ptr, val_strlength);
                            string_msg_message_set_value(output_msg, str);
                            free(str);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_int_array_int_4") == 0 ){
            struct array_int_message* input_msg = (struct array_int_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            int64_t value;
            for( int i = 0; i < 5; i++ ){
                array_int_message_get_value(&value, i, input_msg);
                yar_pack_push_long(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_int_array_int_4_handler", 1, &packager);
                if( response ){
                    struct array_int_message* output_msg = array_int_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                int64_t value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                yar_unpack_data_value(array_value, &value);
                                array_int_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_int_array_float_5") == 0 ){
            struct array_int_message* input_msg = (struct array_int_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            int64_t value;
            for( int i = 0; i < 5; i++ ){
                array_int_message_get_value(&value, i, input_msg);
                yar_pack_push_long(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_int_array_float_5_handler", 1, &packager);
                if( response ){
                    struct array_float_message* output_msg = array_float_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_int_array_string_6") == 0 ){
            struct array_int_message* input_msg = (struct array_int_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            int64_t value;
            for( int i = 0; i < 5; i++ ){
                array_int_message_get_value(&value, i, input_msg);
                yar_pack_push_long(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_int_array_string_6_handler", 1, &packager);
                if( response ){
                    struct array_string_message* output_msg = array_string_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char* value = NULL;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                msgpack_object* obj = (msgpack_object*)array_value;
                                int length = obj->via.str.size;
                                value = (char*)malloc(length + 1);
                                memset(value, 0, length + 1);
                                memcpy(value, obj->via.str.ptr, length);
                                array_string_message_set_value(output_msg, value, index);
                                free(value);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_int_array_bool_7") == 0 ){
            struct array_int_message* input_msg = (struct array_int_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            int64_t value;
            for( int i = 0; i < 5; i++ ){
                array_int_message_get_value(&value, i, input_msg);
                yar_pack_push_long(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_int_array_bool_7_handler", 1, &packager);
                if( response ){
                    struct array_bool_message* output_msg = array_bool_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                struct msgpack_object* obj = (struct msgpack_object*)array_value;
                                value = obj->via.boolean;
                                array_bool_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_int_bool_8") == 0 ){
            struct array_int_message* input_msg = (struct array_int_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            int64_t value;
            for( int i = 0; i < 5; i++ ){
                array_int_message_get_value(&value, i, input_msg);
                yar_pack_push_long(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_int_bool_8_handler", 1, &packager);
                if( response ){
                    struct bool_msg_message* output_msg = bool_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            bool_msg_message_set_value(output_msg, kv_data->val.via.boolean);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_float_int_1") == 0 ){
            struct array_float_message* input_msg = (struct array_float_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            double value;
            for( int i = 0; i < 5; i++ ){
                array_float_message_get_value(&value, i, input_msg);
                yar_pack_push_double(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_float_int_1_handler", 1, &packager);
                if( response ){
                    struct int_msg_message* output_msg = int_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            int_msg_message_set_value(output_msg, kv_data->val.via.i64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_float_float_2") == 0 ){
            struct array_float_message* input_msg = (struct array_float_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            double value;
            for( int i = 0; i < 5; i++ ){
                array_float_message_get_value(&value, i, input_msg);
                yar_pack_push_double(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_float_float_2_handler", 1, &packager);
                if( response ){
                    struct float_msg_message* output_msg = float_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            float_msg_message_set_value(output_msg, kv_data->val.via.f64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_float_string_3") == 0 ){
            struct array_float_message* input_msg = (struct array_float_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            double value;
            for( int i = 0; i < 5; i++ ){
                array_float_message_get_value(&value, i, input_msg);
                yar_pack_push_double(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_float_string_3_handler", 1, &packager);
                if( response ){
                    struct string_msg_message* output_msg = string_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            uint32_t val_strlength = kv_data->val.via.str.size;
                            char* str = (char*)malloc(val_strlength + 1);
                            memset(str, 0, val_strlength + 1);
                            memcpy(str, kv_data->val.via.str.ptr, val_strlength);
                            string_msg_message_set_value(output_msg, str);
                            free(str);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_float_array_int_4") == 0 ){
            struct array_float_message* input_msg = (struct array_float_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            double value;
            for( int i = 0; i < 5; i++ ){
                array_float_message_get_value(&value, i, input_msg);
                yar_pack_push_double(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_float_array_int_4_handler", 1, &packager);
                if( response ){
                    struct array_int_message* output_msg = array_int_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                int64_t value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                yar_unpack_data_value(array_value, &value);
                                array_int_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_float_array_float_5") == 0 ){
            struct array_float_message* input_msg = (struct array_float_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            double value;
            for( int i = 0; i < 5; i++ ){
                array_float_message_get_value(&value, i, input_msg);
                yar_pack_push_double(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_float_array_float_5_handler", 1, &packager);
                if( response ){
                    struct array_float_message* output_msg = array_float_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_float_array_string_6") == 0 ){
            struct array_float_message* input_msg = (struct array_float_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            double value;
            for( int i = 0; i < 5; i++ ){
                array_float_message_get_value(&value, i, input_msg);
                yar_pack_push_double(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_float_array_string_6_handler", 1, &packager);
                if( response ){
                    struct array_string_message* output_msg = array_string_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char* value = NULL;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                msgpack_object* obj = (msgpack_object*)array_value;
                                int length = obj->via.str.size;
                                value = (char*)malloc(length + 1);
                                memset(value, 0, length + 1);
                                memcpy(value, obj->via.str.ptr, length);
                                array_string_message_set_value(output_msg, value, index);
                                free(value);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_float_array_bool_7") == 0 ){
            struct array_float_message* input_msg = (struct array_float_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            double value;
            for( int i = 0; i < 5; i++ ){
                array_float_message_get_value(&value, i, input_msg);
                yar_pack_push_double(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_float_array_bool_7_handler", 1, &packager);
                if( response ){
                    struct array_bool_message* output_msg = array_bool_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                struct msgpack_object* obj = (struct msgpack_object*)array_value;
                                value = obj->via.boolean;
                                array_bool_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_float_bool_8") == 0 ){
            struct array_float_message* input_msg = (struct array_float_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            double value;
            for( int i = 0; i < 5; i++ ){
                array_float_message_get_value(&value, i, input_msg);
                yar_pack_push_double(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_float_bool_8_handler", 1, &packager);
                if( response ){
                    struct bool_msg_message* output_msg = bool_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            bool_msg_message_set_value(output_msg, kv_data->val.via.boolean);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_string_int_1") == 0 ){
            struct array_string_message* input_msg = (struct array_string_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char* value;
            for( int i = 0; i < 5; i++ ){
                array_string_message_get_value(&value, i, input_msg);
                if( value == NULL ){
                    yar_pack_push_string(packager, "", 0);
                }
                else{
                    yar_pack_push_string(packager, value, strlen(value));
                }
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_string_int_1_handler", 1, &packager);
                if( response ){
                    struct int_msg_message* output_msg = int_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            int_msg_message_set_value(output_msg, kv_data->val.via.i64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_string_float_2") == 0 ){
            struct array_string_message* input_msg = (struct array_string_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char* value;
            for( int i = 0; i < 5; i++ ){
                array_string_message_get_value(&value, i, input_msg);
                if( value == NULL ){
                    yar_pack_push_string(packager, "", 0);
                }
                else{
                    yar_pack_push_string(packager, value, strlen(value));
                }
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_string_float_2_handler", 1, &packager);
                if( response ){
                    struct float_msg_message* output_msg = float_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            float_msg_message_set_value(output_msg, kv_data->val.via.f64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_string_string_3") == 0 ){
            struct array_string_message* input_msg = (struct array_string_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char* value;
            for( int i = 0; i < 5; i++ ){
                array_string_message_get_value(&value, i, input_msg);
                if( value == NULL ){
                    yar_pack_push_string(packager, "", 0);
                }
                else{
                    yar_pack_push_string(packager, value, strlen(value));
                }
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_string_string_3_handler", 1, &packager);
                if( response ){
                    struct string_msg_message* output_msg = string_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            uint32_t val_strlength = kv_data->val.via.str.size;
                            char* str = (char*)malloc(val_strlength + 1);
                            memset(str, 0, val_strlength + 1);
                            memcpy(str, kv_data->val.via.str.ptr, val_strlength);
                            string_msg_message_set_value(output_msg, str);
                            free(str);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_string_array_int_4") == 0 ){
            struct array_string_message* input_msg = (struct array_string_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char* value;
            for( int i = 0; i < 5; i++ ){
                array_string_message_get_value(&value, i, input_msg);
                if( value == NULL ){
                    yar_pack_push_string(packager, "", 0);
                }
                else{
                    yar_pack_push_string(packager, value, strlen(value));
                }
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_string_array_int_4_handler", 1, &packager);
                if( response ){
                    struct array_int_message* output_msg = array_int_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                int64_t value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                yar_unpack_data_value(array_value, &value);
                                array_int_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_string_array_float_5") == 0 ){
            struct array_string_message* input_msg = (struct array_string_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char* value;
            for( int i = 0; i < 5; i++ ){
                array_string_message_get_value(&value, i, input_msg);
                if( value == NULL ){
                    yar_pack_push_string(packager, "", 0);
                }
                else{
                    yar_pack_push_string(packager, value, strlen(value));
                }
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_string_array_float_5_handler", 1, &packager);
                if( response ){
                    struct array_float_message* output_msg = array_float_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_string_array_string_6") == 0 ){
            struct array_string_message* input_msg = (struct array_string_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char* value;
            for( int i = 0; i < 5; i++ ){
                array_string_message_get_value(&value, i, input_msg);
                if( value == NULL ){
                    yar_pack_push_string(packager, "", 0);
                }
                else{
                    yar_pack_push_string(packager, value, strlen(value));
                }
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_string_array_string_6_handler", 1, &packager);
                if( response ){
                    struct array_string_message* output_msg = array_string_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char* value = NULL;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                msgpack_object* obj = (msgpack_object*)array_value;
                                int length = obj->via.str.size;
                                value = (char*)malloc(length + 1);
                                memset(value, 0, length + 1);
                                memcpy(value, obj->via.str.ptr, length);
                                array_string_message_set_value(output_msg, value, index);
                                free(value);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_string_array_bool_7") == 0 ){
            struct array_string_message* input_msg = (struct array_string_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char* value;
            for( int i = 0; i < 5; i++ ){
                array_string_message_get_value(&value, i, input_msg);
                if( value == NULL ){
                    yar_pack_push_string(packager, "", 0);
                }
                else{
                    yar_pack_push_string(packager, value, strlen(value));
                }
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_string_array_bool_7_handler", 1, &packager);
                if( response ){
                    struct array_bool_message* output_msg = array_bool_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                struct msgpack_object* obj = (struct msgpack_object*)array_value;
                                value = obj->via.boolean;
                                array_bool_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_string_bool_8") == 0 ){
            struct array_string_message* input_msg = (struct array_string_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char* value;
            for( int i = 0; i < 5; i++ ){
                array_string_message_get_value(&value, i, input_msg);
                if( value == NULL ){
                    yar_pack_push_string(packager, "", 0);
                }
                else{
                    yar_pack_push_string(packager, value, strlen(value));
                }
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_string_bool_8_handler", 1, &packager);
                if( response ){
                    struct bool_msg_message* output_msg = bool_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            bool_msg_message_set_value(output_msg, kv_data->val.via.boolean);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_bool_int_1") == 0 ){
            struct array_bool_message* input_msg = (struct array_bool_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char value = 0;
            for( int i = 0; i < 5; i++ ){
                array_bool_message_get_value(&value, i, input_msg);
                yar_pack_push_bool(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_bool_int_1_handler", 1, &packager);
                if( response ){
                    struct int_msg_message* output_msg = int_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            int_msg_message_set_value(output_msg, kv_data->val.via.i64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_bool_float_2") == 0 ){
            struct array_bool_message* input_msg = (struct array_bool_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char value = 0;
            for( int i = 0; i < 5; i++ ){
                array_bool_message_get_value(&value, i, input_msg);
                yar_pack_push_bool(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_bool_float_2_handler", 1, &packager);
                if( response ){
                    struct float_msg_message* output_msg = float_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            float_msg_message_set_value(output_msg, kv_data->val.via.f64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_bool_string_3") == 0 ){
            struct array_bool_message* input_msg = (struct array_bool_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char value = 0;
            for( int i = 0; i < 5; i++ ){
                array_bool_message_get_value(&value, i, input_msg);
                yar_pack_push_bool(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_bool_string_3_handler", 1, &packager);
                if( response ){
                    struct string_msg_message* output_msg = string_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            uint32_t val_strlength = kv_data->val.via.str.size;
                            char* str = (char*)malloc(val_strlength + 1);
                            memset(str, 0, val_strlength + 1);
                            memcpy(str, kv_data->val.via.str.ptr, val_strlength);
                            string_msg_message_set_value(output_msg, str);
                            free(str);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_bool_array_int_4") == 0 ){
            struct array_bool_message* input_msg = (struct array_bool_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char value = 0;
            for( int i = 0; i < 5; i++ ){
                array_bool_message_get_value(&value, i, input_msg);
                yar_pack_push_bool(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_bool_array_int_4_handler", 1, &packager);
                if( response ){
                    struct array_int_message* output_msg = array_int_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                int64_t value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                yar_unpack_data_value(array_value, &value);
                                array_int_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_bool_array_float_5") == 0 ){
            struct array_bool_message* input_msg = (struct array_bool_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char value = 0;
            for( int i = 0; i < 5; i++ ){
                array_bool_message_get_value(&value, i, input_msg);
                yar_pack_push_bool(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_bool_array_float_5_handler", 1, &packager);
                if( response ){
                    struct array_float_message* output_msg = array_float_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_bool_array_string_6") == 0 ){
            struct array_bool_message* input_msg = (struct array_bool_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char value = 0;
            for( int i = 0; i < 5; i++ ){
                array_bool_message_get_value(&value, i, input_msg);
                yar_pack_push_bool(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_bool_array_string_6_handler", 1, &packager);
                if( response ){
                    struct array_string_message* output_msg = array_string_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char* value = NULL;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                msgpack_object* obj = (msgpack_object*)array_value;
                                int length = obj->via.str.size;
                                value = (char*)malloc(length + 1);
                                memset(value, 0, length + 1);
                                memcpy(value, obj->via.str.ptr, length);
                                array_string_message_set_value(output_msg, value, index);
                                free(value);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_bool_array_bool_7") == 0 ){
            struct array_bool_message* input_msg = (struct array_bool_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char value = 0;
            for( int i = 0; i < 5; i++ ){
                array_bool_message_get_value(&value, i, input_msg);
                yar_pack_push_bool(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_bool_array_bool_7_handler", 1, &packager);
                if( response ){
                    struct array_bool_message* output_msg = array_bool_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                struct msgpack_object* obj = (struct msgpack_object*)array_value;
                                value = obj->via.boolean;
                                array_bool_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_array_bool_bool_8") == 0 ){
            struct array_bool_message* input_msg = (struct array_bool_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            yar_pack_push_array(packager, 5);
            char value = 0;
            for( int i = 0; i < 5; i++ ){
                array_bool_message_get_value(&value, i, input_msg);
                yar_pack_push_bool(packager, value);
            }
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_array_bool_bool_8_handler", 1, &packager);
                if( response ){
                    struct bool_msg_message* output_msg = bool_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            bool_msg_message_set_value(output_msg, kv_data->val.via.boolean);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_bool_int_1") == 0 ){
            struct bool_msg_message* input_msg = (struct bool_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char value = 0;
            bool_msg_message_get_value(&value, input_msg);
            yar_pack_push_bool(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_bool_int_1_handler", 1, &packager);
                if( response ){
                    struct int_msg_message* output_msg = int_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            int_msg_message_set_value(output_msg, kv_data->val.via.i64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_bool_float_2") == 0 ){
            struct bool_msg_message* input_msg = (struct bool_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char value = 0;
            bool_msg_message_get_value(&value, input_msg);
            yar_pack_push_bool(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_bool_float_2_handler", 1, &packager);
                if( response ){
                    struct float_msg_message* output_msg = float_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            float_msg_message_set_value(output_msg, kv_data->val.via.f64);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_bool_string_3") == 0 ){
            struct bool_msg_message* input_msg = (struct bool_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char value = 0;
            bool_msg_message_get_value(&value, input_msg);
            yar_pack_push_bool(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_bool_string_3_handler", 1, &packager);
                if( response ){
                    struct string_msg_message* output_msg = string_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            uint32_t val_strlength = kv_data->val.via.str.size;
                            char* str = (char*)malloc(val_strlength + 1);
                            memset(str, 0, val_strlength + 1);
                            memcpy(str, kv_data->val.via.str.ptr, val_strlength);
                            string_msg_message_set_value(output_msg, str);
                            free(str);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_bool_array_int_4") == 0 ){
            struct bool_msg_message* input_msg = (struct bool_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char value = 0;
            bool_msg_message_get_value(&value, input_msg);
            yar_pack_push_bool(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_bool_array_int_4_handler", 1, &packager);
                if( response ){
                    struct array_int_message* output_msg = array_int_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                int64_t value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                yar_unpack_data_value(array_value, &value);
                                array_int_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_bool_array_float_5") == 0 ){
            struct bool_msg_message* input_msg = (struct bool_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char value = 0;
            bool_msg_message_get_value(&value, input_msg);
            yar_pack_push_bool(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_bool_array_float_5_handler", 1, &packager);
                if( response ){
                    struct array_float_message* output_msg = array_float_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_bool_array_string_6") == 0 ){
            struct bool_msg_message* input_msg = (struct bool_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char value = 0;
            bool_msg_message_get_value(&value, input_msg);
            yar_pack_push_bool(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_bool_array_string_6_handler", 1, &packager);
                if( response ){
                    struct array_string_message* output_msg = array_string_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char* value = NULL;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                msgpack_object* obj = (msgpack_object*)array_value;
                                int length = obj->via.str.size;
                                value = (char*)malloc(length + 1);
                                memset(value, 0, length + 1);
                                memcpy(value, obj->via.str.ptr, length);
                                array_string_message_set_value(output_msg, value, index);
                                free(value);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_bool_array_bool_7") == 0 ){
            struct bool_msg_message* input_msg = (struct bool_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char value = 0;
            bool_msg_message_get_value(&value, input_msg);
            yar_pack_push_bool(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_bool_array_bool_7_handler", 1, &packager);
                if( response ){
                    struct array_bool_message* output_msg = array_bool_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            const yar_data* value_data = yar_unpack_iterator_current(it_map);
                            yar_unpack_iterator* value_it_array = yar_unpack_iterator_init(value_data);
                            int index = 0;
                            do{
                                char value = 0;
                                const yar_data* array_value = yar_unpack_iterator_current(value_it_array);
                                struct msgpack_object* obj = (struct msgpack_object*)array_value;
                                value = obj->via.boolean;
                                array_bool_message_set_value(output_msg, value, index);
                                index++;
                            }while( yar_unpack_iterator_next(value_it_array) );
                            yar_unpack_iterator_free(value_it_array);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
        if( strcmp(func, "test_bool_bool_8") == 0 ){
            struct bool_msg_message* input_msg = (struct bool_msg_message*)input;
            packager = yar_pack_start_map(1);
            yar_pack_push_string(packager, "value", 5);
            char value = 0;
            bool_msg_message_get_value(&value, input_msg);
            yar_pack_push_bool(packager, value);
            client = yar_client_init(hostname);
            if( client ){
                int persistent = 1;
                yar_client_set_opt(client, YAR_PERSISTENT_LINK, &persistent);
                yar_response *response = client->call(client, "yar_Test_test_bool_bool_8_handler", 1, &packager);
                if( response ){
                    struct bool_msg_message* output_msg = bool_msg_message_create();
                    const yar_data* parameters = yar_response_get_response(response);
                    yar_unpack_iterator* it_map = yar_unpack_iterator_init(parameters);
                    do{
                        struct msgpack_object_kv* kv_data = (struct msgpack_object_kv*)yar_unpack_iterator_current(it_map);
                        uint32_t strlength = kv_data->key.via.str.size;
                        char* buffer = (char*)malloc(strlength + 1);
                        memset(buffer, 0, strlength + 1);
                        memcpy(buffer, kv_data->key.via.str.ptr, strlength);
                        yar_unpack_iterator_next(it_map);
                        if( strcmp(buffer, "value") == 0 ){
                            bool_msg_message_set_value(output_msg, kv_data->val.via.boolean);
                        }
                        free(buffer);
                    }while( yar_unpack_iterator_next(it_map) );
                    yar_unpack_iterator_free(it_map);
                    yar_response_free(response);
                    free(response);
                    yar_client_destroy(client);
                    yar_pack_free(packager);
                    packager = NULL;
                    return output_msg;
                }
            }
        }
    }
    return NULL;
}
