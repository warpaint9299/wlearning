include config.mk

TARGET = main.out
SRC = main.c
OBJ = ${SRC:.c=.o}

# SRC = myprintf.s util.s
# OBJ = ${SRC:.s=.o}

all: options ${TARGET} clean

options:
	@echo ${TARGET} build options:
	@echo "INCS      = ${INCS}"
	@echo "LDFLAGS   = ${LDFLAGS}"
	@echo "CFLAGS    = ${CFLAGS}"
	@echo "CC        = ${CC}"
	@echo "ASFLAGS   = ${ASFLAGS}"
	@echo "LINKFLAGS = ${LINKFLAGS}"
	@echo "SRC = ${SRC}"
	@echo "OBJ = ${OBJ}"
	
# Automatic Variables
# The value of ‘$^’ is a list of all the prerequisites of the rule
# The automatic variable ‘$<’ is just the first prerequisite

%.o: %.c
	${CC} -c ${CFLAGS} $<

${TARGET}: ${OBJ}
	cc -o $@ $< ${LDFLAGS}

# %.o: %.s
# as -o $@ $< ${ASFLAGS}

# ${TARGET}: ${OBJ}
# ld -o $@ $^ ${LINKFLAGS}

run:
	./${TARGET}

clean:
	rm -f ${OBJ}

.PHONY: all options ${TARGET} clean
