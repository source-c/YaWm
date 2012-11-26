# yawm - Yet Another Window Manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = yawm.c
OBJ = ${SRC:.c=.o}

all: options yawm

options:
	@echo yawm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	@echo creating $@ from config.def.h
	@cp config.def.h $@

yawm: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f yawm ${OBJ} yawm-${VERSION}.tar.gz *~

clean-all: clean
	@rm -f config.h

dist: clean
	@echo creating dist tarball
	@mkdir -p yawm-${VERSION}
	@cp -R LICENSE Makefile README config.def.h config.mk \
		yawm.1 ${SRC} yawm-${VERSION}
	@tar -cf yawm-${VERSION}.tar yawm-${VERSION}
	@gzip yawm-${VERSION}.tar
	@rm -rf yawm-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f yawm ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/yawm
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < yawm.1 > ${DESTDIR}${MANPREFIX}/man1/yawm.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/yawm.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/yawm
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/yawm.1

.PHONY: all options clean dist install uninstall
