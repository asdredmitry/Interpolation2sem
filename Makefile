NAME            = plot

CC              = gcc
LINK            = gcc

DEBUG           = 
OPTIMAZE_COMMON   = -O3 -ffast-math
OPTIMAZE_SPECIFIC =
OPTIMAZE        = $(OPTIMAZE_COMMON) $(OPTIMAZE_SPECIFIC)

WARNINGS        = 
INCLUDE_DIR     = -I. -I/usr/X11R6/include
CFLAGS          = -c $(DEBUG) $(OPTIMAZE) $(WARNINGS) $(INCLUDE_DIR)

LIB_DIR         = -L. -L/usr/X11R6/lib
LIB             = -lX11
LDFLAGS         = $(DEBUG)

OBJS            = plot_x11.o test.o metod_1_i.o metod_1_h.o metod_2_h.o metod_2_i.o 

all:    $(NAME)

$(NAME)         : $(OBJS)
	$(LINK) $(LDFLAGS) $(OBJS) $(LIB_DIR) $(LIB) -lm -o $(NAME)

clean:
	rm -f $(OBJS) $(NAME)

.c.o:
	$(CC) $(CFLAGS) $<

#-------------------------------------------------------------------------------

# ��������� � X11
plot_x11.o      : plot_x11.c plot_x11.h
# ����
test.o          : test.c plot_x11.h

metod_2_h.o : metod_2_h.c metod_2.h

metod_2_i.o : metod_2_i.c metod_2.h

metod_1_h.o : metod_1_h.c metod_1.h

metod_1_i.o : metod_1_i.c metod_1.h


#-------------------------------------------------------------------------------
