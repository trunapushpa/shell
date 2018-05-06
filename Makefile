CC=gcc
DEPS = headers.h
OBJ = print_prompt.o cd_cmd.o exec_cmds.o setup.o pinfo.o parse.o redirect.o overkill.o jobs.o ls.o kjob.o pwd.o echo.o fg.o main.c
EXEC = shell

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

shell: $(OBJ)
		gcc -o $@ $^ $(CFLAGS)
clean:
	rm -f *.o
	rm $(EXEC)