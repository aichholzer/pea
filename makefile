

MYSQL_INC=/usr/local/include/mysql
MYSQL_LIB=/usr/local/lib/mysql

RM=rm
CC=gcc -c -D_DEBUG=1 -I$(MYSQL_INC) $<
LD=gcc -L$(MYSQL_LIB)
LEX=flex -8 
BISON=bison -d -t $<

CORE_OBJECTS=pea_main.o pea_array.o pea_atom.o pea_class.o pea_exec.o pea_function.o\
	pea_hash.o pea_lex.o pea_map.o pea_mem.o pea_object.o pea_parse.o\
	pea_segment.o pea_stack.o pea_string.o pea_type.o pea_variable.o\
	pea_util.o pea_stream.o

RTL_OBJECT=pea_rtl_lang.o pea_rtl_io.o pea_rtl_db.o pea_rtl_cgi.o pea_rtl_socket.o

pea:	$(CORE_OBJECTS)	$(RTL_OBJECT)
	$(LD) -o pea $(CORE_OBJECTS) $(RTL_OBJECT) -lmysqlclient -lz

clean:	
	$(RM) pea $(CORE_OBJECTS) $(RTL_OBJECT) pea_parse.c pea_lex.c pea_parse.h
	
pea_main.o:	pea_main.c
	$(CC)

pea_array.o:	pea_array.c
	$(CC)

pea_atom.o:	pea_atom.c
	$(CC)

pea_class.o:	pea_class.c
	$(CC)

pea_exec.o:	pea_exec.c
	$(CC)

pea_function.o:	pea_function.c
	$(CC)

pea_hash.o:	pea_hash.c
	$(CC)

pea_lex.c:	pea_lex.l
	$(LEX) -opea_lex.c pea_lex.l

pea_lex.o:	pea_lex.c pea_parse.h
	$(CC)

pea_map.o:	pea_map.c
	$(CC)

pea_mem.o:	pea_mem.c
	$(CC)

pea_parse.c pea_parse.h:	pea_parse.y
	$(BISON) -opea_parse.c

pea_parse.o:	pea_parse.c
	$(CC)

pea_object.o:	pea_object.c
	$(CC)

pea_segment.o:	pea_segment.c
	$(CC)

pea_stack.o:	pea_stack.c
	$(CC)

pea_string.o:	pea_string.c
	$(CC)

pea_type.o:	pea_type.c
	$(CC)

pea_variable.o:	pea_variable.c
	$(CC)

pea_rtl_lang.o:	pea_rtl_lang.c
	$(CC)

pea_rtl_io.o:	pea_rtl_io.c
	$(CC)

pea_rtl_db.o:	pea_rtl_db.c
	$(CC)

pea_rtl_cgi.o:	pea_rtl_cgi.c
	$(CC)

pea_rtl_socket.o:	pea_rtl_socket.c
	$(CC)

pea_util.o:		pea_util.c
	$(CC)

pea_stream.o:	pea_stream.c
	$(CC)
