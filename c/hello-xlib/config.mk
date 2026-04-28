VERSION = 0.0.1

COMMONINC = /usr/include

X11INC = /usr/include/X11
X11LIB = /usr/lib

INCS = -I${COMMONINC} -I${COMMONINC}/X11
LIBS = -L${X11LIB} -lX11 -lm -lxcb-util -lxcb

CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L -DVERSION=\"${VERSION}\"
CFLAGS = -g -std=gnu11 -pedantic -Wall -Wextra -Os ${INCS} ${CPPFLAGS}
LDFLAGS = ${LIBS}

CC = cc
