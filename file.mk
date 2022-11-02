makebuildserver:
	
	gcc server.c -o server 

runserver:

	./server               

makebuildclient:
    
	gcc client.c -o client 

runclient:
	
	./client 127.0.0.1 5001 