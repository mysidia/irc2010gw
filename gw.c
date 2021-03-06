/*
 *  Sample/Test Server
 *  Copyright C 2001 Mysidia (mysidia at qmud dot org)  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include "config.h"
#include <irclib/irclib.h>
#include "../irclib/dns.h"
#include <assert.h>
ID("$Id: gw.c,v 1.1 2003/01/15 18:55:01 mysidia Exp $");

IRC(Socket) *testCli;

int Test(IrcSocket *cl)
{
	IrcListener *q;
	IrcSocket *p;
	static time_t lasttime = 0;

	q = cl->port;

	for(p = q->links.lh_first; p; p = p->socket_list.le_next) {
		if ((CTime - lasttime) > 3)
			IrcSend(p, "Hi!\r\n");
	}

	lasttime = time(NULL);
}

int funFin ( IRC(dns_query)*q, char *r, void *d )
{
	if (d)
		printf("DNS: %s -> %s\n", q->ip, r);
	else
		printf("DNS: %s -> ???\n", q->ip);
///
}

int IRCUnknown(IRC(Socket)*q, IRC(Message)*t);

int IRCblah(IRC(Socket)*q, IRC(Message)*t) {
	IrcSend(q, "BLAH!\r\n");
	return 0;
}


IRC(MsgTab) endUserTable[] = {
	{"OK",	IRCblah},
	{NULL,	IRCUnknown}
};

int listenHandler( IRC(Socket) * sock, char* buf )
{
//	if (errcode)
//		printf("Connection %d\n", errcode);
//	else
		printf("Connection with %X established\n", sock->addr.s_addr);

	sock->parser = endUserTable;
}

int main()
{
	IRC(Socket) *p;
	IRC(Listener) *q;
	struct in_addr addr;

	LibIrcInit();
	p = IRC(socket_make)();

	if (p == NULL)
		abort();

	addr.s_addr = INADDR_ANY;

	if (IRC(socket_bind)(p, 9000, addr) < 0)
		abort();
	if ((q = IRC(MakeListener)(p)) == NULL)
		abort();
	IrcSetSockHandler(p, listenHandler);

	printf("Listening on %d\n", 9000);

	IRC(ListenerAddEvents)(q);



//	q->sock->periodic = Test; /* periodically Test(...) */

	addr.s_addr = inet_addr("127.0.0.1");

//	query_dns(0, "rs.internic.net", funFin, NULL); /* test DNS */

	IRC(SystemLoop)();

//	sleep (6000);
}

//
