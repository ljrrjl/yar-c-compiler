#include "handler.h"
#include <getopt.h>

yar_server_handler handlers[] = {
	{"yar_Test_test_int_int_1_handler", sizeof("yar_Test_test_int_int_1_handler") - 1, yar_Test_test_int_int_1_handler},
	{"yar_Test_test_int_float_2_handler", sizeof("yar_Test_test_int_float_2_handler") - 1, yar_Test_test_int_float_2_handler},
	{"yar_Test_test_int_string_3_handler", sizeof("yar_Test_test_int_string_3_handler") - 1, yar_Test_test_int_string_3_handler},
	{"yar_Test_test_int_array_int_4_handler", sizeof("yar_Test_test_int_array_int_4_handler") - 1, yar_Test_test_int_array_int_4_handler},
	{"yar_Test_test_int_array_float_5_handler", sizeof("yar_Test_test_int_array_float_5_handler") - 1, yar_Test_test_int_array_float_5_handler},
	{"yar_Test_test_int_array_string_6_handler", sizeof("yar_Test_test_int_array_string_6_handler") - 1, yar_Test_test_int_array_string_6_handler},
	{"yar_Test_test_int_array_bool_7_handler", sizeof("yar_Test_test_int_array_bool_7_handler") - 1, yar_Test_test_int_array_bool_7_handler},
	{"yar_Test_test_int_bool_8_handler", sizeof("yar_Test_test_int_bool_8_handler") - 1, yar_Test_test_int_bool_8_handler},
	{"yar_Test_test_float_int_1_handler", sizeof("yar_Test_test_float_int_1_handler") - 1, yar_Test_test_float_int_1_handler},
	{"yar_Test_test_float_float_2_handler", sizeof("yar_Test_test_float_float_2_handler") - 1, yar_Test_test_float_float_2_handler},
	{"yar_Test_test_float_string_3_handler", sizeof("yar_Test_test_float_string_3_handler") - 1, yar_Test_test_float_string_3_handler},
	{"yar_Test_test_float_array_int_4_handler", sizeof("yar_Test_test_float_array_int_4_handler") - 1, yar_Test_test_float_array_int_4_handler},
	{"yar_Test_test_float_array_float_5_handler", sizeof("yar_Test_test_float_array_float_5_handler") - 1, yar_Test_test_float_array_float_5_handler},
	{"yar_Test_test_float_array_string_6_handler", sizeof("yar_Test_test_float_array_string_6_handler") - 1, yar_Test_test_float_array_string_6_handler},
	{"yar_Test_test_float_array_bool_7_handler", sizeof("yar_Test_test_float_array_bool_7_handler") - 1, yar_Test_test_float_array_bool_7_handler},
	{"yar_Test_test_float_bool_8_handler", sizeof("yar_Test_test_float_bool_8_handler") - 1, yar_Test_test_float_bool_8_handler},
	{"yar_Test_test_string_int_1_handler", sizeof("yar_Test_test_string_int_1_handler") - 1, yar_Test_test_string_int_1_handler},
	{"yar_Test_test_string_float_2_handler", sizeof("yar_Test_test_string_float_2_handler") - 1, yar_Test_test_string_float_2_handler},
	{"yar_Test_test_string_string_3_handler", sizeof("yar_Test_test_string_string_3_handler") - 1, yar_Test_test_string_string_3_handler},
	{"yar_Test_test_string_array_int_4_handler", sizeof("yar_Test_test_string_array_int_4_handler") - 1, yar_Test_test_string_array_int_4_handler},
	{"yar_Test_test_string_array_float_5_handler", sizeof("yar_Test_test_string_array_float_5_handler") - 1, yar_Test_test_string_array_float_5_handler},
	{"yar_Test_test_string_array_string_6_handler", sizeof("yar_Test_test_string_array_string_6_handler") - 1, yar_Test_test_string_array_string_6_handler},
	{"yar_Test_test_string_array_bool_7_handler", sizeof("yar_Test_test_string_array_bool_7_handler") - 1, yar_Test_test_string_array_bool_7_handler},
	{"yar_Test_test_string_bool_8_handler", sizeof("yar_Test_test_string_bool_8_handler") - 1, yar_Test_test_string_bool_8_handler},
	{"yar_Test_test_array_int_int_1_handler", sizeof("yar_Test_test_array_int_int_1_handler") - 1, yar_Test_test_array_int_int_1_handler},
	{"yar_Test_test_array_int_float_2_handler", sizeof("yar_Test_test_array_int_float_2_handler") - 1, yar_Test_test_array_int_float_2_handler},
	{"yar_Test_test_array_int_string_3_handler", sizeof("yar_Test_test_array_int_string_3_handler") - 1, yar_Test_test_array_int_string_3_handler},
	{"yar_Test_test_array_int_array_int_4_handler", sizeof("yar_Test_test_array_int_array_int_4_handler") - 1, yar_Test_test_array_int_array_int_4_handler},
	{"yar_Test_test_array_int_array_float_5_handler", sizeof("yar_Test_test_array_int_array_float_5_handler") - 1, yar_Test_test_array_int_array_float_5_handler},
	{"yar_Test_test_array_int_array_string_6_handler", sizeof("yar_Test_test_array_int_array_string_6_handler") - 1, yar_Test_test_array_int_array_string_6_handler},
	{"yar_Test_test_array_int_array_bool_7_handler", sizeof("yar_Test_test_array_int_array_bool_7_handler") - 1, yar_Test_test_array_int_array_bool_7_handler},
	{"yar_Test_test_array_int_bool_8_handler", sizeof("yar_Test_test_array_int_bool_8_handler") - 1, yar_Test_test_array_int_bool_8_handler},
	{"yar_Test_test_array_float_int_1_handler", sizeof("yar_Test_test_array_float_int_1_handler") - 1, yar_Test_test_array_float_int_1_handler},
	{"yar_Test_test_array_float_float_2_handler", sizeof("yar_Test_test_array_float_float_2_handler") - 1, yar_Test_test_array_float_float_2_handler},
	{"yar_Test_test_array_float_string_3_handler", sizeof("yar_Test_test_array_float_string_3_handler") - 1, yar_Test_test_array_float_string_3_handler},
	{"yar_Test_test_array_float_array_int_4_handler", sizeof("yar_Test_test_array_float_array_int_4_handler") - 1, yar_Test_test_array_float_array_int_4_handler},
	{"yar_Test_test_array_float_array_float_5_handler", sizeof("yar_Test_test_array_float_array_float_5_handler") - 1, yar_Test_test_array_float_array_float_5_handler},
	{"yar_Test_test_array_float_array_string_6_handler", sizeof("yar_Test_test_array_float_array_string_6_handler") - 1, yar_Test_test_array_float_array_string_6_handler},
	{"yar_Test_test_array_float_array_bool_7_handler", sizeof("yar_Test_test_array_float_array_bool_7_handler") - 1, yar_Test_test_array_float_array_bool_7_handler},
	{"yar_Test_test_array_float_bool_8_handler", sizeof("yar_Test_test_array_float_bool_8_handler") - 1, yar_Test_test_array_float_bool_8_handler},
	{"yar_Test_test_array_string_int_1_handler", sizeof("yar_Test_test_array_string_int_1_handler") - 1, yar_Test_test_array_string_int_1_handler},
	{"yar_Test_test_array_string_float_2_handler", sizeof("yar_Test_test_array_string_float_2_handler") - 1, yar_Test_test_array_string_float_2_handler},
	{"yar_Test_test_array_string_string_3_handler", sizeof("yar_Test_test_array_string_string_3_handler") - 1, yar_Test_test_array_string_string_3_handler},
	{"yar_Test_test_array_string_array_int_4_handler", sizeof("yar_Test_test_array_string_array_int_4_handler") - 1, yar_Test_test_array_string_array_int_4_handler},
	{"yar_Test_test_array_string_array_float_5_handler", sizeof("yar_Test_test_array_string_array_float_5_handler") - 1, yar_Test_test_array_string_array_float_5_handler},
	{"yar_Test_test_array_string_array_string_6_handler", sizeof("yar_Test_test_array_string_array_string_6_handler") - 1, yar_Test_test_array_string_array_string_6_handler},
	{"yar_Test_test_array_string_array_bool_7_handler", sizeof("yar_Test_test_array_string_array_bool_7_handler") - 1, yar_Test_test_array_string_array_bool_7_handler},
	{"yar_Test_test_array_string_bool_8_handler", sizeof("yar_Test_test_array_string_bool_8_handler") - 1, yar_Test_test_array_string_bool_8_handler},
	{"yar_Test_test_array_bool_int_1_handler", sizeof("yar_Test_test_array_bool_int_1_handler") - 1, yar_Test_test_array_bool_int_1_handler},
	{"yar_Test_test_array_bool_float_2_handler", sizeof("yar_Test_test_array_bool_float_2_handler") - 1, yar_Test_test_array_bool_float_2_handler},
	{"yar_Test_test_array_bool_string_3_handler", sizeof("yar_Test_test_array_bool_string_3_handler") - 1, yar_Test_test_array_bool_string_3_handler},
	{"yar_Test_test_array_bool_array_int_4_handler", sizeof("yar_Test_test_array_bool_array_int_4_handler") - 1, yar_Test_test_array_bool_array_int_4_handler},
	{"yar_Test_test_array_bool_array_float_5_handler", sizeof("yar_Test_test_array_bool_array_float_5_handler") - 1, yar_Test_test_array_bool_array_float_5_handler},
	{"yar_Test_test_array_bool_array_string_6_handler", sizeof("yar_Test_test_array_bool_array_string_6_handler") - 1, yar_Test_test_array_bool_array_string_6_handler},
	{"yar_Test_test_array_bool_array_bool_7_handler", sizeof("yar_Test_test_array_bool_array_bool_7_handler") - 1, yar_Test_test_array_bool_array_bool_7_handler},
	{"yar_Test_test_array_bool_bool_8_handler", sizeof("yar_Test_test_array_bool_bool_8_handler") - 1, yar_Test_test_array_bool_bool_8_handler},
	{"yar_Test_test_bool_int_1_handler", sizeof("yar_Test_test_bool_int_1_handler") - 1, yar_Test_test_bool_int_1_handler},
	{"yar_Test_test_bool_float_2_handler", sizeof("yar_Test_test_bool_float_2_handler") - 1, yar_Test_test_bool_float_2_handler},
	{"yar_Test_test_bool_string_3_handler", sizeof("yar_Test_test_bool_string_3_handler") - 1, yar_Test_test_bool_string_3_handler},
	{"yar_Test_test_bool_array_int_4_handler", sizeof("yar_Test_test_bool_array_int_4_handler") - 1, yar_Test_test_bool_array_int_4_handler},
	{"yar_Test_test_bool_array_float_5_handler", sizeof("yar_Test_test_bool_array_float_5_handler") - 1, yar_Test_test_bool_array_float_5_handler},
	{"yar_Test_test_bool_array_string_6_handler", sizeof("yar_Test_test_bool_array_string_6_handler") - 1, yar_Test_test_bool_array_string_6_handler},
	{"yar_Test_test_bool_array_bool_7_handler", sizeof("yar_Test_test_bool_array_bool_7_handler") - 1, yar_Test_test_bool_array_bool_7_handler},
	{"yar_Test_test_bool_bool_8_handler", sizeof("yar_Test_test_bool_bool_8_handler") - 1, yar_Test_test_bool_bool_8_handler},
	{NULL, 0, NULL}
};
int main(int argc, char** argv){
    int opt, max_childs = 5;
    char *hostname = NULL, *yar_pid=NULL, *log_file = NULL;
    char *user = NULL, *group = NULL;
    int standalone = 0;
    while( (opt = getopt(argc, argv, "hS:n:K:p:Xl:u:g:")) != -1 ){
        switch( opt ){
            case 'n':
                max_childs = atoi(optarg);
            break;
            case 'S':
                hostname = optarg;
            break;
            case 'p':
                yar_pid = optarg;
            break;
            case 'X':
                standalone = 1;
            break;
            case 'g':
                group = optarg;
            break;
            default:
                yar_server_print_usage(argv[0]);
                return 0;
            break;
        }
    }
    if( !hostname ){
        yar_server_print_usage(argv[0]);
        return 0;
    }
    if( yar_server_init(hostname) ){
        yar_server_set_opt(YAR_STAND_ALONE, &standalone);
        yar_server_set_opt(YAR_MAX_CHILDREN, &max_childs);
        yar_server_set_opt(YAR_PID_FILE, yar_pid);
        yar_server_set_opt(YAR_LOG_FILE, log_file);
        yar_server_set_opt(YAR_CUSTOM_DATA, (void *)1);
        yar_server_set_opt(YAR_CHILD_USER, user);
        yar_server_set_opt(YAR_CHILD_GROUP, group);
        yar_server_register_handler(handlers);
        yar_server_run();
    }
    return 0;
}
