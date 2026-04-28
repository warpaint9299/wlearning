include config.mk

TARGET = hello-xlib.out
SRC = main.c
OBJ = ${SRC:.c=.o}

all: options ${TARGET} clean

options:
	@echo ${TARGET} build options:
	@echo "INCS    = ${INCS}"
	@echo "LDFLAGS = ${LDFLAGS}"
	@echo "CFLAGS  = ${CFLAGS}"
	@echo "CC      = ${CC}"

${TARGET}: ${OBJ}
	cc -o $@ ${OBJ} ${LDFLAGS}

run:
	./${TARGET}

clean:
	rm -f ${OBJ}

.PHONY: all options ${TARGET} clean
