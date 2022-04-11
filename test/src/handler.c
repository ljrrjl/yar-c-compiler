#include "handler.h"
#include <math.h>
#include <stdio.h>
void Test_test_int_int_1_handler(struct int_msg_message* input, struct int_msg_message* output){
    //Enter the code here...
    int64_t value = 0;
    int_msg_message_get_value(&value, input);
    if(value == 1)
	    printf("[int_int] OK\n"); 
    else
	    printf("[int_int] ERROR\n");
    int_msg_message_set_value(output, value);
}
void Test_test_int_float_2_handler(struct int_msg_message* input, struct float_msg_message* output){
    //Enter the code here...
    int64_t value = 0;
    double out_double = 0;
    int_msg_message_get_value(&value, input);
    if(value == 2)
	    printf("[int_float] OK\n"); 
    else
	    printf("[int_float] ERROR\n");
    out_double = 2.0;
    float_msg_message_set_value(output, out_double);
}
void Test_test_int_string_3_handler(struct int_msg_message* input, struct string_msg_message* output){
    //Enter the code here...
    int64_t value = 0;
    char* out = "3";
    int_msg_message_get_value(&value, input);
    if(value == 3)
	    printf("[int_string] OK\n"); 
    else
	    printf("[int_string] ERROR\n");
    string_msg_message_set_value(output, out);
}
void Test_test_int_array_int_4_handler(struct int_msg_message* input, struct array_int_message* output){
    //Enter the code here...
    int64_t value = 0;
    int_msg_message_get_value(&value, input);
    if(value == 4)
	    printf("[int_array_int] OK\n"); 
    else
	    printf("[int_array_int] ERROR\n");
    for(int i = 0; i < 5; i++)
    {
	array_int_message_set_value(output, 4, i);
    }
}
void Test_test_int_array_float_5_handler(struct int_msg_message* input, struct array_float_message* output){
    //Enter the code here...
    int64_t value = 0;
    int_msg_message_get_value(&value, input);
    if(value == 5)
	    printf("[int_array_float] OK\n"); 
    else
	    printf("[int_array_float] ERROR\n");
    for(int i = 0; i < 5; i++)
    {
	array_float_message_set_value(output, 5.0, i);
    }
}
void Test_test_int_array_string_6_handler(struct int_msg_message* input, struct array_string_message* output){
    //Enter the code here...
    int64_t value = 0;
    int_msg_message_get_value(&value, input);
    if(value == 6)
	    printf("[int_array_string] OK\n"); 
    else
	    printf("[int_array_string] ERROR\n");
    for(int i = 0; i < 5; i++)
    {
	array_string_message_set_value(output, "6", i);
    }
}
void Test_test_int_array_bool_7_handler(struct int_msg_message* input, struct array_bool_message* output){
    //Enter the code here...
    int64_t value = 0;
    int_msg_message_get_value(&value, input);
    if(value == 7)
	    printf("[int_array_bool] OK\n"); 
    else
	    printf("[int_array_bool] ERROR\n");
    for(int i = 0; i < 5; i++)
    {
	array_bool_message_set_value(output, 1, i);
    }
}
void Test_test_int_bool_8_handler(struct int_msg_message* input, struct bool_msg_message* output){
    //Enter the code here...
    int64_t value = 0;
    int_msg_message_get_value(&value, input);
    if(value == 8)
	    printf("[int_bool] OK\n"); 
    else
	    printf("[int_bool] ERROR\n");
    bool_msg_message_set_value(output, 1);
}
void Test_test_float_int_1_handler(struct float_msg_message* input, struct int_msg_message* output){
    //Enter the code here...
    double value = 0; 
    float_msg_message_get_value(&value, input);
    if(fabs(value - 1) < 0.5)
	printf("[float_int] OK\n");
    else
	printf("[float_int] ERROR\n");
    int_msg_message_set_value(output, 1);
}
void Test_test_float_float_2_handler(struct float_msg_message* input, struct float_msg_message* output){
    //Enter the code here...
    double value = 0; 
    float_msg_message_get_value(&value, input);
    if(fabs(value - 2) < 0.5)
	printf("[float_float] OK\n");
    else
	printf("[float_float] ERROR\n");
    float_msg_message_set_value(output, 2);
}
void Test_test_float_string_3_handler(struct float_msg_message* input, struct string_msg_message* output){
    //Enter the code here...
    double value = 0; 
    float_msg_message_get_value(&value, input);
    if(fabs(value - 3) < 0.5)
	printf("[float_string] OK\n");
    else
	printf("[float_string] ERROR\n");
    string_msg_message_set_value(output, "3");
}
void Test_test_float_array_int_4_handler(struct float_msg_message* input, struct array_int_message* output){
    //Enter the code here...
    double value = 0; 
    float_msg_message_get_value(&value, input);
    if(fabs(value - 4) < 0.5)
	printf("[float_array_int] OK\n");
    else
	printf("[float_array_int] ERROR\n]");
    for(int i = 0; i < 5; i++)
    {
	array_int_message_set_value(output, 4, i);
    }
}
void Test_test_float_array_float_5_handler(struct float_msg_message* input, struct array_float_message* output){
    //Enter the code here...
    double value = 0; 
    float_msg_message_get_value(&value, input);
    if(fabs(value - 5) < 0.5)
	printf("[float_array_float] OK\n");
    else
	printf("[float_array_float] ERROR\n");
    for(int i = 0; i < 5; i++)
    {
	array_float_message_set_value(output, 5, i);
    }
}
void Test_test_float_array_string_6_handler(struct float_msg_message* input, struct array_string_message* output){
    //Enter the code here...
    double value = 0; 
    float_msg_message_get_value(&value, input);
    if(fabs(value - 6) < 0.5)
	printf("[float_array_string] OK\n");
    else
	printf("[float_array_string] ERROR\n");
    for(int i = 0; i < 5; i++)
    {
	array_string_message_set_value(output, "6", i);
    }
}
void Test_test_float_array_bool_7_handler(struct float_msg_message* input, struct array_bool_message* output){
    //Enter the code here...
    double value = 0; 
    float_msg_message_get_value(&value, input);
    if(fabs(value - 7) < 0.5)
	printf("[float_array_bool] OK\n");
    else
	printf("[float_array_bool] ERROR\n");
    for(int i = 0; i < 5; i++)
    {
	array_bool_message_set_value(output, 1, i);
    }
}
void Test_test_float_bool_8_handler(struct float_msg_message* input, struct bool_msg_message* output){
    //Enter the code here...
    double value = 0; 
    float_msg_message_get_value(&value, input);
    if(fabs(value - 8) < 0.5)
	printf("[float_bool] OK\n");
    else
	printf("[float_bool] ERROR\n");
    bool_msg_message_set_value(output, 1);
}
void Test_test_string_int_1_handler(struct string_msg_message* input, struct int_msg_message* output){
    //Enter the code here...

}
void Test_test_string_float_2_handler(struct string_msg_message* input, struct float_msg_message* output){
    //Enter the code here...

}
void Test_test_string_string_3_handler(struct string_msg_message* input, struct string_msg_message* output){
    //Enter the code here...

}
void Test_test_string_array_int_4_handler(struct string_msg_message* input, struct array_int_message* output){
    //Enter the code here...

}
void Test_test_string_array_float_5_handler(struct string_msg_message* input, struct array_float_message* output){
    //Enter the code here...

}
void Test_test_string_array_string_6_handler(struct string_msg_message* input, struct array_string_message* output){
    //Enter the code here...

}
void Test_test_string_array_bool_7_handler(struct string_msg_message* input, struct array_bool_message* output){
    //Enter the code here...

}
void Test_test_string_bool_8_handler(struct string_msg_message* input, struct bool_msg_message* output){
    //Enter the code here...

}
void Test_test_array_int_int_1_handler(struct array_int_message* input, struct int_msg_message* output){
    //Enter the code here...

}
void Test_test_array_int_float_2_handler(struct array_int_message* input, struct float_msg_message* output){
    //Enter the code here...

}
void Test_test_array_int_string_3_handler(struct array_int_message* input, struct string_msg_message* output){
    //Enter the code here...

}
void Test_test_array_int_array_int_4_handler(struct array_int_message* input, struct array_int_message* output){
    //Enter the code here...

}
void Test_test_array_int_array_float_5_handler(struct array_int_message* input, struct array_float_message* output){
    //Enter the code here...

}
void Test_test_array_int_array_string_6_handler(struct array_int_message* input, struct array_string_message* output){
    //Enter the code here...

}
void Test_test_array_int_array_bool_7_handler(struct array_int_message* input, struct array_bool_message* output){
    //Enter the code here...

}
void Test_test_array_int_bool_8_handler(struct array_int_message* input, struct bool_msg_message* output){
    //Enter the code here...

}
void Test_test_array_float_int_1_handler(struct array_float_message* input, struct int_msg_message* output){
    //Enter the code here...

}
void Test_test_array_float_float_2_handler(struct array_float_message* input, struct float_msg_message* output){
    //Enter the code here...

}
void Test_test_array_float_string_3_handler(struct array_float_message* input, struct string_msg_message* output){
    //Enter the code here...

}
void Test_test_array_float_array_int_4_handler(struct array_float_message* input, struct array_int_message* output){
    //Enter the code here...

}
void Test_test_array_float_array_float_5_handler(struct array_float_message* input, struct array_float_message* output){
    //Enter the code here...

}
void Test_test_array_float_array_string_6_handler(struct array_float_message* input, struct array_string_message* output){
    //Enter the code here...

}
void Test_test_array_float_array_bool_7_handler(struct array_float_message* input, struct array_bool_message* output){
    //Enter the code here...

}
void Test_test_array_float_bool_8_handler(struct array_float_message* input, struct bool_msg_message* output){
    //Enter the code here...

}
void Test_test_array_string_int_1_handler(struct array_string_message* input, struct int_msg_message* output){
    //Enter the code here...

}
void Test_test_array_string_float_2_handler(struct array_string_message* input, struct float_msg_message* output){
    //Enter the code here...

}
void Test_test_array_string_string_3_handler(struct array_string_message* input, struct string_msg_message* output){
    //Enter the code here...

}
void Test_test_array_string_array_int_4_handler(struct array_string_message* input, struct array_int_message* output){
    //Enter the code here...

}
void Test_test_array_string_array_float_5_handler(struct array_string_message* input, struct array_float_message* output){
    //Enter the code here...

}
void Test_test_array_string_array_string_6_handler(struct array_string_message* input, struct array_string_message* output){
    //Enter the code here...

}
void Test_test_array_string_array_bool_7_handler(struct array_string_message* input, struct array_bool_message* output){
    //Enter the code here...

}
void Test_test_array_string_bool_8_handler(struct array_string_message* input, struct bool_msg_message* output){
    //Enter the code here...

}
void Test_test_array_bool_int_1_handler(struct array_bool_message* input, struct int_msg_message* output){
    //Enter the code here...

}
void Test_test_array_bool_float_2_handler(struct array_bool_message* input, struct float_msg_message* output){
    //Enter the code here...

}
void Test_test_array_bool_string_3_handler(struct array_bool_message* input, struct string_msg_message* output){
    //Enter the code here...

}
void Test_test_array_bool_array_int_4_handler(struct array_bool_message* input, struct array_int_message* output){
    //Enter the code here...

}
void Test_test_array_bool_array_float_5_handler(struct array_bool_message* input, struct array_float_message* output){
    //Enter the code here...

}
void Test_test_array_bool_array_string_6_handler(struct array_bool_message* input, struct array_string_message* output){
    //Enter the code here...

}
void Test_test_array_bool_array_bool_7_handler(struct array_bool_message* input, struct array_bool_message* output){
    //Enter the code here...

}
void Test_test_array_bool_bool_8_handler(struct array_bool_message* input, struct bool_msg_message* output){
    //Enter the code here...

}
void Test_test_bool_int_1_handler(struct bool_msg_message* input, struct int_msg_message* output){
    //Enter the code here...

}
void Test_test_bool_float_2_handler(struct bool_msg_message* input, struct float_msg_message* output){
    //Enter the code here...

}
void Test_test_bool_string_3_handler(struct bool_msg_message* input, struct string_msg_message* output){
    //Enter the code here...

}
void Test_test_bool_array_int_4_handler(struct bool_msg_message* input, struct array_int_message* output){
    //Enter the code here...

}
void Test_test_bool_array_float_5_handler(struct bool_msg_message* input, struct array_float_message* output){
    //Enter the code here...

}
void Test_test_bool_array_string_6_handler(struct bool_msg_message* input, struct array_string_message* output){
    //Enter the code here...

}
void Test_test_bool_array_bool_7_handler(struct bool_msg_message* input, struct array_bool_message* output){
    //Enter the code here...

}
void Test_test_bool_bool_8_handler(struct bool_msg_message* input, struct bool_msg_message* output){
    //Enter the code here...

}
