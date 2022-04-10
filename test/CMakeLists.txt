project(Test)
cmake_minimum_required(VERSION 3.18)
set(YAR_PATH /home/ljr/local)

set(SERVER_SRC_LIST
	src/handler.c
	src/message.c
	src/yar_handler.c
	src/yar_server.c
)

set(CLIENT_SRC_LIST
	#src/client.c
	src/message.c
	src/yar_client.c
)

include_directories(
	./include
	${YAR_PATH}/include
	
)

link_directories(
	${YAR_PATH}/lib
)
	

#add_executable(client
#	${CLIENT_SRC_LIST}
#)

add_executable(server
	${SERVER_SRC_LIST}
)

#target_link_libraries(client
#	yar
#	msgpackc
#	event
#	pthread
#)

target_link_libraries(server
	yar
	msgpackc
	event
	pthread
)
