PROG =	dict
SRCS =	dict.c net.c clientscan.l clientparse.y
MAN  =	dict.1

INFILES =	dict.1

YHEADER =	1

DPSRCS =	clientparse.h clientparse.c
clientscan.o: clientparse.h

.PATH:${SRCDIR_dictd}

CPPFLAGS +=	-I${SRCDIR_dictdplugins_include:U.} -I${SRCDIR_libdictd} \
   -I${SRCDIR_dictd} -I${SRCDIR_libcommon} -I${.CURDIR}

CFLAGS.check +=	-Wno-error=cast-qual -Wno-error=unused-function \
   -Wno-error=format-truncation -Wno-error=unused-const-variable

MKC_REQUIRE_FUNCLIBS +=	lst_create:maa bind:socket inet_ntop:nsl

.include <mkc.mk>
