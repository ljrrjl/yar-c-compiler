# Yar C Protoc


-----


A compiler to automatically generate server-side and client-side code for yar-c
(see also: [Yar-c](https://github.com/laruence/yar-c))
## Build dependencies
* flex
* bison
## Install
```
./build.sh [ install-path ]
```


-----


## Quick Start
To define a format for client-server interaction messages, we need an **xxx** file containing the definition of message and the definition of service, and then we compile this file with yar-c-protoc. Now we have the client-side and server-side code of yar-c. Then we complete the callback functions in **xxx_handler.c**. 
**Here is an example**:
The file name is: Hello
```
#The request message containing the user's name
message HelloRequest
{
    string name;
}

#The response message containing the msg
message HelloReply
{
    string msg;
}

#The Hello service definition.
service Hello
{
    rpc SayHello(HelloRequest) returns(HelloReply);
}
```
Then run
```
yar-c-protoc Hello
```
This will generate


| Hello_client.c/h | Hello_handler.c/h | Hello_message.c/h | Hello_server.c | Hello_handler.yar.c
| -------- | -------- | -------- | -------- | -------- |
| Encapsulates the client->call() interface, which is used to initiate requests from the client to the server.     | Requires the user to add callback functions     | Defines the data structure of the message     | Server side program entrance | Wrapped yar-c's rpc server-side callback function

**For server-side programming**
The user only needs to care about the xxx_handler.c file. 
as shown in the example above, the Hello_handler.c:
```
void Hello_SayHello_handler(struct HelloRequest_message* input, struct HelloReply_message* output)
{
        //Enter the code here...
}

```
Now you need to complete this callback function with the method defined in Hello_message.h.
We modify the callback function as follows:
```
void Hello_SayHello_handler(struct HelloRequest_message* input, struct HelloReply_message* output)
{
        //Enter the code here...
        char* name = NULL;
        HelloRequest_message_get_name(&name, input);
        printf("Hello %s.\n", name);
        HelloReply_message_set_msg(output, "Hello");
}
```
**For client-side programming**
The user calls **yar_protoc_call()** at the place where the rpc method needs to be called.
In client.c:
```
#include "Hello_client.h"
#include <stdio.h>

int main(int argc, char** argv)
{
        if(argc != 2)
                return 1;
        struct HelloRequest_message* request = HelloRequest_message_create();
        HelloRequest_message_set_name(request, "ljrrjl");
        //call rpc
        struct HelloReply_message* reply = (struct HelloReply_message*)yar_protoc_call(argv[1], "Hello", "SayHello", request);
        HelloRequest_message_free(request);
        if(reply)
        {
                char* msg = NULL;
                HelloReply_message_get_msg(&msg, reply);
                printf("%s\n", msg);
                HelloReply_message_free(reply);
        }
        return 0;
}
```
**Build**
```
gcc -g -o server Hello_handler.c Hello_handler.yar.c Hello_message.c Hello_server.c -lyar -levent -lmsgpackc -lpthread
```
```
gcc -g -o client client.c Hello_client.c Hello_message.c  -lyar -levent -lmsgpackc -lpthread
```
**RUN**
```
./server -S 127.0.0.1:3900 -X
```
```
./client 127.0.0.1:3900
```
## Tutorials
To be continued...
