WARNS     =	4

CPPFLAGS +=	-DDICT_VERSION=2.0.0
CPPFLAGS +=	-DDICT_CONFIG_PATH=$(SYSCONFDIR:U.)/
CPPFLAGS +=	-DDICT_PLUGIN_PATH=$(LIBEXECDIR:U.)/
CPPFLAGS +=	-DDICT_DICTIONARY_PATH=$(DATADIR:U.)/

#CPPFLAGS +=	-D_POSIX_C_SOURCE=200809L
#CPPFLAGS +=	-D_DEFAULT_SOURCE
#CPPFLAGS +=	-D_BSD_SOURCE
#CPPFLAGS +=	-D_NETBSD_SOURCE

AWK               ?=	awk
MKC_REQUIRE_PROGS +=	${AWK}
INTEXTS_REPLS     +=	AWK ${AWK:U${PROG.${AWK}}}

#CCSTD              =	c99
