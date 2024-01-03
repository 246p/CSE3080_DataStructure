cc=gcc
cflags = -W -g
target = hw3
objects = hw3.o

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)

%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

.PHONY : clean
clean :
	rm $(target) $(objects)