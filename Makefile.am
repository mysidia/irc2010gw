# $Id: Makefile.am,v 1.1 2003/01/15 18:47:36 mysidia Exp $
#
#
DEFS = -D_IRCLIB_INTERNAL @DEFS@

bin_PROGRAMS = iirc_gw
iirc_gw_SOURCES = gw.c
iirc_gw_LDADD = -lirc -levent -ladns

#lib_LTLIBRARIES = libirc.la
#libirc_la_SOURCES = match.c mem.c sock.c server.c irc.c channel.c dns.c hash.c \
# proto.c
#include_HEADERS = irclib.h proto.h

DISTCLEANFILES = config.guess config.sub ltconfig ltmain.sh libtool
