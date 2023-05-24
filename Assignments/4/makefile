CC		=  gcc
CFLAGS	= -wAll -pedantic 

% : %.o 
	$(CC) $(CFLAGS) $< -o $@

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@
