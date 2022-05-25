all: exe lib		# просто обозначение конечной цели, без команды

exe: main.c			# убрали линковку с либой, линкуем с системной libdl
	gcc main.c -fPIC -ldl -o hello
    
lib: hello.h hello.c
	gcc -shared hello.c -fPIC -o libHello.so

clean: 				# '-': не учитывать результат операции как ошибку и т.п.
	-rm hello libHello.so 2>/dev/null 
