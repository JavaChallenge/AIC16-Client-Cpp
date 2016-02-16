#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley) 01/20/90";
#endif
#define YYBYACC 1
#line 2 "grammar.y"
/*
 * Copyright (c) 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code distributions
 * retain the above copyright notice and this paragraph in its entirety, (2)
 * distributions including binary code include the above copyright notice and
 * this paragraph in its entirety in the documentation or other materials
 * provided with the distribution, and (3) all advertising materials mentioning
 * features or use of this software display the following acknowledgement:
 * ``This product includes software developed by the University of California,
 * Lawrence Berkeley Laboratory and its contributors.'' Neither the name of
 * the University nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior
 * written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#ifndef lint
static const char rcsid[] _U_ =
    "@(#) $Header: /tcpdump/master/libpcap/grammar.y,v 1.101 2007-11-18 02:03:52 guy Exp $ (LBL)";
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef WIN32
#include <pcap-stdinc.h>
#else /* WIN32 */
#include <sys/types.h>
#include <sys/socket.h>
#endif /* WIN32 */

#include <stdlib.h>

#ifndef WIN32
#if __STDC__
struct mbuf;
struct rtentry;
#endif

#include <netinet/in.h>
#include <arpa/inet.h>
#endif /* WIN32 */

#include <stdio.h>

#include "pcap-int.h"

#include "gencode.h"
#ifdef HAVE_NET_PFVAR_H
#include <net/if.h>
#include <net/pfvar.h>
#include <net/if_pflog.h>
#endif
#include "ieee80211.h"
#include <pcap/namedb.h>

#ifdef HAVE_OS_PROTO_H
#include "os-proto.h"
#endif

#define QSET(q, p, d, a) (q).proto = (p),\
			 (q).dir = (d),\
			 (q).addr = (a)

struct tok {
	int v;			/* value */
	const char *s;		/* string */
};

static const struct tok ieee80211_types[] = {
	{ IEEE80211_FC0_TYPE_DATA, "data" },
	{ IEEE80211_FC0_TYPE_MGT, "mgt" },
	{ IEEE80211_FC0_TYPE_MGT, "management" },
	{ IEEE80211_FC0_TYPE_CTL, "ctl" },
	{ IEEE80211_FC0_TYPE_CTL, "control" },
	{ 0, NULL }
};
static const struct tok ieee80211_mgt_subtypes[] = {
	{ IEEE80211_FC0_SUBTYPE_ASSOC_REQ, "assocreq" },
	{ IEEE80211_FC0_SUBTYPE_ASSOC_REQ, "assoc-req" },
	{ IEEE80211_FC0_SUBTYPE_ASSOC_RESP, "assocresp" },
	{ IEEE80211_FC0_SUBTYPE_ASSOC_RESP, "assoc-resp" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_REQ, "reassocreq" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_REQ, "reassoc-req" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_RESP, "reassocresp" },
	{ IEEE80211_FC0_SUBTYPE_REASSOC_RESP, "reassoc-resp" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_REQ, "probereq" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_REQ, "probe-req" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_RESP, "proberesp" },
	{ IEEE80211_FC0_SUBTYPE_PROBE_RESP, "probe-resp" },
	{ IEEE80211_FC0_SUBTYPE_BEACON, "beacon" },
	{ IEEE80211_FC0_SUBTYPE_ATIM, "atim" },
	{ IEEE80211_FC0_SUBTYPE_DISASSOC, "disassoc" },
	{ IEEE80211_FC0_SUBTYPE_DISASSOC, "disassociation" },
	{ IEEE80211_FC0_SUBTYPE_AUTH, "auth" },
	{ IEEE80211_FC0_SUBTYPE_AUTH, "authentication" },
	{ IEEE80211_FC0_SUBTYPE_DEAUTH, "deauth" },
	{ IEEE80211_FC0_SUBTYPE_DEAUTH, "deauthentication" },
	{ 0, NULL }
};
static const struct tok ieee80211_ctl_subtypes[] = {
	{ IEEE80211_FC0_SUBTYPE_PS_POLL, "ps-poll" },
	{ IEEE80211_FC0_SUBTYPE_RTS, "rts" },
	{ IEEE80211_FC0_SUBTYPE_CTS, "cts" },
	{ IEEE80211_FC0_SUBTYPE_ACK, "ack" },
	{ IEEE80211_FC0_SUBTYPE_CF_END, "cf-end" },
	{ IEEE80211_FC0_SUBTYPE_CF_END_ACK, "cf-end-ack" },
	{ 0, NULL }
};
static const struct tok ieee80211_data_subtypes[] = {
	{ IEEE80211_FC0_SUBTYPE_DATA, "data" },
	{ IEEE80211_FC0_SUBTYPE_CF_ACK, "data-cf-ack" },
	{ IEEE80211_FC0_SUBTYPE_CF_POLL, "data-cf-poll" },
	{ IEEE80211_FC0_SUBTYPE_CF_ACPL, "data-cf-ack-poll" },
	{ IEEE80211_FC0_SUBTYPE_NODATA, "null" },
	{ IEEE80211_FC0_SUBTYPE_NODATA_CF_ACK, "cf-ack" },
	{ IEEE80211_FC0_SUBTYPE_NODATA_CF_POLL, "cf-poll"  },
	{ IEEE80211_FC0_SUBTYPE_NODATA_CF_ACPL, "cf-ack-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_DATA, "qos-data" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_CF_ACK, "qos-data-cf-ack" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_CF_POLL, "qos-data-cf-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_CF_ACPL, "qos-data-cf-ack-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_NODATA, "qos" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_NODATA_CF_POLL, "qos-cf-poll" },
	{ IEEE80211_FC0_SUBTYPE_QOS|IEEE80211_FC0_SUBTYPE_NODATA_CF_ACPL, "qos-cf-ack-poll" },
	{ 0, NULL }
};
struct type2tok {
	int type;
	const struct tok *tok;
};
static const struct type2tok ieee80211_type_subtypes[] = {
	{ IEEE80211_FC0_TYPE_MGT, ieee80211_mgt_subtypes },
	{ IEEE80211_FC0_TYPE_CTL, ieee80211_ctl_subtypes },
	{ IEEE80211_FC0_TYPE_DATA, ieee80211_data_subtypes },
	{ 0, NULL }
};

static int
str2tok(const char *str, const struct tok *toks)
{
	int i;

	for (i = 0; toks[i].s != NULL; i++) {
		if (pcap_strcasecmp(toks[i].s, str) == 0)
			return (toks[i].v);
	}
	return (-1);
}

int n_errors = 0;

static struct qual qerr = { Q_UNDEF, Q_UNDEF, Q_UNDEF, Q_UNDEF };

static void
yyerror(const char *msg)
{
	++n_errors;
	bpf_error("%s", msg);
	/* NOTREACHED */
}

#ifdef NEED_YYPARSE_WRAPPER
int yyparse(void);

int
pcap_parse()
{
	return (yyparse());
}
#endif

#ifdef HAVE_NET_PFVAR_H
static int
pfreason_to_num(const char *reason)
{
	const char *reasons[] = PFRES_NAMES;
	int i;

	for (i = 0; reasons[i]; i++) {
		if (pcap_strcasecmp(reason, reasons[i]) == 0)
			return (i);
	}
	bpf_error("unknown PF reason");
	/*NOTREACHED*/
}

static int
pfaction_to_num(const char *action)
{
	if (pcap_strcasecmp(action, "pass") == 0 ||
	    pcap_strcasecmp(action, "accept") == 0)
		return (PF_PASS);
	else if (pcap_strcasecmp(action, "drop") == 0 ||
		pcap_strcasecmp(action, "block") == 0)
		return (PF_DROP);
#if HAVE_PF_NAT_THROUGH_PF_NORDR
	else if (pcap_strcasecmp(action, "rdr") == 0)
		return (PF_RDR);
	else if (pcap_strcasecmp(action, "nat") == 0)
		return (PF_NAT);
	else if (pcap_strcasecmp(action, "binat") == 0)
		return (PF_BINAT);
	else if (pcap_strcasecmp(action, "nordr") == 0)
		return (PF_NORDR);
#endif
	else {
		bpf_error("unknown PF action");
		/*NOTREACHED*/
	}
}
#else /* !HAVE_NET_PFVAR_H */
static int
pfreason_to_num(const char *reason)
{
	bpf_error("libpcap was compiled on a machine without pf support");
	/*NOTREACHED*/

	/* this is to make the VC compiler happy */
	return -1;
}

static int
pfaction_to_num(const char *action)
{
	bpf_error("libpcap was compiled on a machine without pf support");
	/*NOTREACHED*/

	/* this is to make the VC compiler happy */
	return -1;
}
#endif /* HAVE_NET_PFVAR_H */
#line 242 "grammar.y"
typedef union {
	int i;
	bpf_u_int32 h;
	u_char *e;
	char *s;
	struct stmt *stmt;
	struct arth *a;
	struct {
		struct qual q;
		int atmfieldtype;
		int mtp3fieldtype;
		struct block *b;
	} blk;
	struct block *rblk;
} YYSTYPE;
#line 261 "y.tab.c"
#define DST 257
#define SRC 258
#define HOST 259
#define GATEWAY 260
#define NET 261
#define NETMASK 262
#define PORT 263
#define PORTRANGE 264
#define LESS 265
#define GREATER 266
#define PROTO 267
#define PROTOCHAIN 268
#define CBYTE 269
#define ARP 270
#define RARP 271
#define IP 272
#define SCTP 273
#define TCP 274
#define UDP 275
#define ICMP 276
#define IGMP 277
#define IGRP 278
#define PIM 279
#define VRRP 280
#define CARP 281
#define ATALK 282
#define AARP 283
#define DECNET 284
#define LAT 285
#define SCA 286
#define MOPRC 287
#define MOPDL 288
#define TK_BROADCAST 289
#define TK_MULTICAST 290
#define NUM 291
#define INBOUND 292
#define OUTBOUND 293
#define PF_IFNAME 294
#define PF_RSET 295
#define PF_RNR 296
#define PF_SRNR 297
#define PF_REASON 298
#define PF_ACTION 299
#define TYPE 300
#define SUBTYPE 301
#define DIR 302
#define ADDR1 303
#define ADDR2 304
#define ADDR3 305
#define ADDR4 306
#define RA 307
#define TA 308
#define LINK 309
#define GEQ 310
#define LEQ 311
#define NEQ 312
#define ID 313
#define EID 314
#define HID 315
#define HID6 316
#define AID 317
#define LSH 318
#define RSH 319
#define LEN 320
#define IPV6 321
#define ICMPV6 322
#define AH 323
#define ESP 324
#define VLAN 325
#define MPLS 326
#define PPPOED 327
#define PPPOES 328
#define ISO 329
#define ESIS 330
#define CLNP 331
#define ISIS 332
#define L1 333
#define L2 334
#define IIH 335
#define LSP 336
#define SNP 337
#define CSNP 338
#define PSNP 339
#define STP 340
#define IPX 341
#define NETBEUI 342
#define LANE 343
#define LLC 344
#define METAC 345
#define BCC 346
#define SC 347
#define ILMIC 348
#define OAMF4EC 349
#define OAMF4SC 350
#define OAM 351
#define OAMF4 352
#define CONNECTMSG 353
#define METACONNECT 354
#define VPI 355
#define VCI 356
#define RADIO 357
#define FISU 358
#define LSSU 359
#define MSU 360
#define HFISU 361
#define HLSSU 362
#define HMSU 363
#define SIO 364
#define OPC 365
#define DPC 366
#define SLS 367
#define HSIO 368
#define HOPC 369
#define HDPC 370
#define HSLS 371
#define OR 372
#define AND 373
#define UMINUS 374
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,   24,    1,    1,    1,    1,    1,   20,   21,
    2,    2,    2,    3,    3,    3,    3,    3,    3,    3,
    3,    3,   23,   22,    4,    4,    4,    7,    7,    5,
    5,    8,    8,    8,    8,    8,    8,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    9,    9,
   10,   10,   10,   10,   10,   10,   10,   10,   10,   10,
   10,   10,   11,   11,   11,   11,   12,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   25,   25,   25,   25,
   25,   25,   25,   25,   25,   25,   25,   25,   25,   25,
   25,   25,   26,   26,   26,   26,   26,   26,   27,   27,
   27,   27,   41,   41,   42,   42,   43,   44,   44,   40,
   40,   39,   18,   18,   18,   19,   19,   19,   13,   13,
   14,   14,   14,   14,   14,   14,   14,   14,   14,   14,
   14,   14,   14,   15,   15,   15,   15,   15,   17,   17,
   28,   28,   28,   28,   28,   28,   28,   28,   29,   29,
   29,   29,   30,   30,   32,   32,   32,   32,   31,   33,
   33,   34,   34,   34,   34,   34,   34,   35,   35,   35,
   35,   35,   35,   35,   35,   37,   37,   37,   37,   36,
   38,   38,
};
short yylen[] = {                                         2,
    2,    1,    0,    1,    3,    3,    3,    3,    1,    1,
    1,    1,    3,    1,    3,    3,    1,    3,    1,    1,
    1,    2,    1,    1,    1,    3,    3,    1,    1,    1,
    2,    3,    2,    2,    2,    2,    2,    2,    3,    1,
    3,    3,    1,    1,    1,    2,    1,    2,    1,    0,
    1,    1,    3,    3,    3,    3,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    2,    2,    2,    2,
    4,    1,    1,    2,    1,    2,    1,    1,    2,    1,
    1,    2,    2,    2,    2,    2,    2,    2,    4,    2,
    2,    2,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    4,    6,    3,    3,    3,    3,    3,    3,    3,    3,
    2,    3,    1,    1,    1,    1,    1,    1,    1,    3,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    2,    2,    3,    1,    1,
    3,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    2,    2,    3,    1,
    1,    3,
};
short yydefred[] = {                                      3,
    0,    0,    0,    0,    0,   70,   71,   69,   72,   73,
   74,   75,   76,   77,   78,   79,   80,   81,   82,   83,
   84,   85,   87,   86,  169,  112,  113,    0,    0,    0,
    0,    0,    0,   68,  163,   88,   89,   90,   91,    0,
    0,  118,    0,   92,   93,  102,   94,   95,   96,   97,
   98,   99,  101,  100,  103,  104,  105,  171,  172,  173,
  174,  177,  178,  175,  176,  179,  180,  181,  182,  183,
  184,  106,  192,  193,  194,  195,  196,  197,  198,  199,
  200,  201,  202,  203,  204,  205,   23,    0,   24,    0,
    4,   30,    0,    0,    0,  150,    0,  149,    0,    0,
   43,  121,   44,   45,    0,   47,    0,  109,  110,    0,
  123,  124,  125,  126,  140,  141,  127,  142,  128,  114,
    0,  116,  119,  161,    0,    0,   10,    9,    0,    0,
   14,   20,    0,    0,   21,   38,   11,   12,    0,    0,
    0,    0,   63,   67,   64,   65,   66,   35,   36,  107,
  108,    0,    0,    0,   57,   58,   59,   60,   61,   62,
    0,   34,   37,  122,  144,  146,  148,    0,    0,    0,
    0,    0,    0,    0,    0,  143,  145,  147,    0,    0,
    0,    0,    0,    0,   31,  189,    0,    0,    0,  185,
   46,  210,    0,    0,    0,  206,   48,  165,  164,  167,
  168,  166,    0,    0,    0,    6,    5,    0,    0,    0,
    8,    7,    0,    0,    0,   25,    0,    0,    0,   22,
    0,    0,    0,    0,  133,  134,    0,  137,  131,  138,
  139,  132,   32,    0,    0,    0,    0,    0,    0,  155,
  156,    0,    0,    0,   39,  162,  170,  186,  187,  190,
    0,  207,  208,  211,    0,  111,    0,   16,   15,   18,
   13,    0,    0,   54,   56,   53,   55,    0,  151,    0,
  188,    0,  209,    0,   26,   27,  135,  136,  129,    0,
  191,  212,  152,
};
short yydgoto[] = {                                       1,
  182,  220,  137,  217,   91,   92,  218,   93,   94,  161,
  162,  163,   95,   96,  203,  125,   98,  179,  180,  129,
  130,  126,  140,    2,  101,  102,  164,  103,  104,  105,
  190,  191,  251,  106,  107,  196,  197,  255,  119,  117,
  227,  279,  229,  232,
};
short yysindex[] = {                                      0,
    0,  296, -274, -271, -251,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -256, -243, -209,
 -186, -266, -206,    0,    0,    0,    0,    0,    0,  -40,
  -40,    0,  -40,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  398,    0, -365,
    0,    0,  -28,  686,  655,    0,   29,    0,  296,  296,
    0,    0,    0,    0,  708,    0,  772,    0,    0,   87,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -40,    0,    0,    0,   29,  398,    0,    0,  183,  183,
    0,    0,  -38,   70,    0,    0,    0,    0,  -28,  -28,
 -349, -229,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -264, -178, -258,    0,    0,    0,    0,    0,    0,
  -96,    0,    0,    0,    0,    0,    0,  398,  398,  398,
  398,  398,  398,  398,  398,    0,    0,    0,  398,  398,
  398,  -39,  104,  115,    0,    0, -131, -112, -100,    0,
    0,    0,  -98,  -94,  -93,    0,    0,    0,    0,    0,
    0,    0,  -92,  115,  170,    0,    0,    0,  183,  183,
    0,    0, -115,  -90,  -88,    0,  163, -365,  115,    0,
  -53,  -52,  -50,  -36,    0,    0,  -83,    0,    0,    0,
    0,    0,    0,  133,  133,   -8,   50,  111,  111,    0,
    0,  170,  170,  768,    0,    0,    0,    0,    0,    0,
  -37,    0,    0,    0,  -35,    0,  115,    0,    0,    0,
    0,  -28,  -28,    0,    0,    0,    0, -181,    0,  -72,
    0, -100,    0,  -93,    0,    0,    0,    0,    0,  127,
    0,    0,    0,
};
short yyrindex[] = {                                      0,
    0,  486,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   11,
   19,    0,   21,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  222,
    0,    0,    0,    0,    0,    0,    1,    0,  831,  831,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  831,  831,
    0,    0,   26,   31,    0,    0,    0,    0,    0,    0,
  -18,  450,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  523,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  735,  760,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    3,  831,  831,
    0,    0,    0,    0,    0,    0, -203,    0, -191,    0,
    0,    0,    0,    0,    0,    0,   36,    0,    0,    0,
    0,    0,    0,   28,   53,   68,   78,   13,   38,    0,
    0,   43,   61,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  112,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,
};
short yygindex[] = {                                      0,
  223,   -6, -129,    0,    4,    0,    0,    0,    0,    0,
   65,    0,   15,  -67,    0,  110,  787,  -91,   59,    9,
 -133,  802,  149,    0,    0,    0,    0,    0,    0,    0,
 -171,    0,    0,    0,    0, -166,    0,    0,    0,    0,
    0,    0,    0,    0,
};
#define YYTABLESIZE 1139
short yytable[] = {                                      89,
   40,  245,   12,  271,   87,  273,  127,  128,  214,  216,
  115,   89,  153,  187,   52,  193,  108,  250,  117,  109,
  120,   52,  221,  222,  115,   17,  225,  159,  254,  171,
   19,  183,  230,  174,  172,  130,  173,  154,  175,  110,
  149,   40,   41,   12,  149,  149,  116,  149,  226,  149,
  153,  115,  160,  153,  231,  153,  111,  153,  183,  117,
   42,  120,  149,  149,  149,  159,   17,  158,  159,  112,
  153,   19,  153,  153,  153,  154,  130,  157,  154,  216,
  154,  113,  154,   41,  263,  159,  136,  159,  159,  159,
  160,  174,  172,  160,  173,  154,  175,  154,  154,  154,
  281,   42,  124,  185,  114,  153,  118,  282,  158,  277,
  160,   97,  160,  160,  160,  157,  215,  272,  157,  181,
  159,  274,  206,  211,  199,  158,  149,  158,  158,  158,
  154,  278,  207,  212,  228,  157,  153,  157,  157,  157,
  205,  183,  223,  224,  246,  160,  202,  201,  200,  149,
  100,  159,  174,  149,  149,  247,  149,  175,  149,  248,
  158,  154,  143,  188,  145,  194,  146,  147,   29,   29,
  157,  149,  149,  149,  174,  172,  160,  173,  249,  175,
   28,   28,  234,  235,  236,  237,  238,  239,  240,  241,
  186,  158,  252,  242,  243,  244,  253,  192,  256,  258,
  259,  157,  260,  261,  264,  265,  266,  171,   97,   97,
  198,  174,  172,  185,  173,   87,  175,  268,  280,  283,
  267,    1,   89,  213,   90,  233,  262,   88,    0,    0,
    0,    0,    0,    0,    0,  149,    0,    0,   97,   97,
   52,    0,   52,    0,   52,   52,    0,  100,  100,    0,
   25,    0,    0,    0,    0,  275,  276,   49,   49,   49,
   49,   49,   25,   49,   49,    0,    0,   49,   49,    0,
    0,    0,   52,    0,    0,    0,    0,  210,  210,    0,
    0,    0,    0,    0,  131,  132,  133,  134,  135,   49,
   49,    0,    0,  170,   52,   52,   52,   52,   52,    0,
   49,   49,   49,   49,   49,   49,   49,   49,   49,  168,
  169,    0,  149,  149,  149,    0,    0,    0,   97,   97,
  149,  149,  153,  153,  153,    0,    0,    0,   87,    0,
  153,  153,  127,  128,  127,   89,  127,  159,  159,  159,
   88,    0,    0,    0,    0,  159,  159,  154,  154,  154,
    0,    0,    0,    0,    0,  154,  154,  210,  210,    0,
    0,    0,  160,  160,  160,    0,    0,  168,  169,    0,
  160,  160,   40,   40,   12,   12,    0,  158,  158,  158,
    0,    0,  115,  115,  153,  153,    0,  157,  157,  157,
  117,  117,  120,  120,    0,    0,    0,   17,   17,  159,
  159,    0,   19,   19,    0,    0,    0,  130,  130,  154,
  154,    0,    0,    0,   41,   41,    0,    0,    0,    0,
    0,  149,  149,  149,  160,  160,    0,    0,    0,  149,
  149,    0,   42,   42,    0,    0,    0,   89,    0,  158,
  158,    0,   88,    0,    0,    0,    0,    3,    4,  157,
  157,    5,    6,    7,    8,    9,   10,   11,   12,   13,
   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
   24,    0,    0,   25,   26,   27,   28,   29,   30,   31,
   32,   33,   51,   28,   28,    2,    0,  168,  169,   51,
    0,   34,    0,    0,    0,  131,  132,  133,  134,  135,
    0,    0,   35,   36,   37,   38,   39,   40,   41,   42,
   43,   44,   45,   46,   47,   48,   49,   50,   51,   52,
   53,   54,   55,   56,   57,   58,   59,   60,   61,   62,
   63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
   73,   74,   75,   76,   77,   78,   79,   80,   81,   82,
   83,   84,   85,   86,    0,   33,    0,    0,    0,    0,
    3,    4,   33,    0,    5,    6,    7,    8,    9,   10,
   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
   21,   22,   23,   24,    0,    0,   25,   26,   27,   28,
   29,   30,   31,   32,   33,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   34,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   35,   36,   37,   38,   39,
   40,   41,   42,   43,   44,   45,   46,   47,   48,   49,
   50,   51,   52,   53,   54,   55,   56,   57,   58,   59,
   60,   61,   62,   63,   64,   65,   66,   67,   68,   69,
   70,   71,   72,   73,   74,   75,   76,   77,   78,   79,
   80,   81,   82,   83,   84,   85,   86,    6,    7,    8,
    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   23,   24,    0,    0,   25,    0,
    0,    0,  171,    0,    0,    0,  174,  172,    0,  173,
    0,  175,    0,    0,    0,    0,   34,    0,   51,    0,
   51,    0,   51,   51,  178,  177,  176,   35,   36,   37,
   38,   39,    0,    0,    0,    0,   44,   45,   46,   47,
   48,   49,   50,   51,   52,   53,   54,   55,   56,   57,
   51,    0,   50,   50,   50,   50,   50,   89,   50,   50,
    0,    0,   50,   50,   72,    0,    0,    0,    0,    0,
    0,    0,   51,   51,   51,   51,   51,  178,  177,  176,
    0,    0,  150,    0,   50,   50,  150,  150,  170,  150,
    0,  150,    0,    0,    0,   50,   50,   50,   50,   50,
   50,   50,   50,   50,  150,  150,  150,  149,    0,    0,
    0,  149,  149,   99,  149,  171,  149,    0,    0,  174,
  172,   89,  173,   33,  175,    0,    0,    0,    0,  149,
  149,  149,    0,    0,    0,  270,  120,  122,    0,  123,
    0,  178,  177,  176,    0,   33,   33,   33,   33,   33,
    0,  121,  121,    0,  121,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  150,    0,
  269,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  138,
    0,    0,    0,  149,    0,  184,    0,    0,    0,    0,
    0,  170,    0,    0,  139,    0,    0,    0,    0,    0,
   99,   99,    0,    0,    0,    0,  189,  204,  195,    0,
    0,    0,  184,    0,    0,  208,  208,    0,    0,    0,
    0,    0,  121,    0,    0,  219,  138,    0,    0,    0,
  209,  209,    0,    0,    0,    0,    0,    0,    0,    0,
  121,  139,  141,  142,  143,  144,  145,    0,  146,  147,
    0,    0,  148,  149,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  165,  166,  167,    0,    0,    0,
    0,    0,  168,  169,  150,  151,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  152,  153,  154,  155,  156,
  157,  158,  159,  160,    0,  257,  208,    0,  186,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   99,  209,    0,    0,    0,    0,    0,  165,  166,  167,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  150,  150,  150,    0,  138,  138,
    0,    0,  150,  150,    0,    0,    0,    0,    0,    0,
    0,    0,  192,  139,  139,    0,    0,    0,    0,  149,
  149,  149,    0,    0,    0,    0,    0,  149,  149,    0,
    0,  165,  166,  167,    0,  168,  169,   50,   50,   50,
   50,   50,    0,   50,   50,    0,    0,   50,   50,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   50,
   50,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   50,   50,   50,   50,   50,   50,   50,   50,   50,
};
short yycheck[] = {                                      40,
    0,   41,    0,   41,   33,   41,  372,  373,   47,  139,
    0,   40,    0,  105,   33,  107,  291,  189,    0,  291,
    0,   40,  372,  373,  291,    0,  291,    0,  195,   38,
    0,   99,  291,   42,   43,    0,   45,    0,   47,  291,
   38,   41,    0,   41,   42,   43,  313,   45,  313,   47,
   38,   41,    0,   41,  313,   43,  313,   45,  126,   41,
    0,   41,   60,   61,   62,   38,   41,    0,   41,  313,
   58,   41,   60,   61,   62,   38,   41,    0,   41,  209,
   43,  291,   45,   41,  218,   58,   93,   60,   61,   62,
   38,   42,   43,   41,   45,   58,   47,   60,   61,   62,
  272,   41,   88,  100,  291,   93,  313,  274,   41,  291,
   58,    2,   60,   61,   62,   38,   47,  251,   41,   91,
   93,  255,  129,  130,   38,   58,  124,   60,   61,   62,
   93,  313,  129,  130,  313,   58,  124,   60,   61,   62,
  126,  209,  372,  373,   41,   93,   60,   61,   62,   38,
    2,  124,   42,   42,   43,   41,   45,   47,   47,  291,
   93,  124,  259,  105,  261,  107,  263,  264,  372,  373,
   93,   60,   61,   62,   42,   43,  124,   45,  291,   47,
  372,  373,  168,  169,  170,  171,  172,  173,  174,  175,
  291,  124,  291,  179,  180,  181,  291,  291,  291,  315,
  291,  124,  291,   41,  258,  258,  257,   38,   99,  100,
  124,   42,   43,  210,   45,   33,   47,  301,  291,   93,
  257,    0,   40,  262,    2,  161,  218,   45,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  124,   -1,   -1,  129,  130,
  259,   -1,  261,   -1,  263,  264,   -1,   99,  100,   -1,
  291,   -1,   -1,   -1,   -1,  262,  263,  257,  258,  259,
  260,  261,  291,  263,  264,   -1,   -1,  267,  268,   -1,
   -1,   -1,  291,   -1,   -1,   -1,   -1,  129,  130,   -1,
   -1,   -1,   -1,   -1,  313,  314,  315,  316,  317,  289,
  290,   -1,   -1,  124,  313,  314,  315,  316,  317,   -1,
  300,  301,  302,  303,  304,  305,  306,  307,  308,  318,
  319,   -1,  310,  311,  312,   -1,   -1,   -1,  209,  210,
  318,  319,  310,  311,  312,   -1,   -1,   -1,   33,   -1,
  318,  319,  372,  373,  372,   40,  372,  310,  311,  312,
   45,   -1,   -1,   -1,   -1,  318,  319,  310,  311,  312,
   -1,   -1,   -1,   -1,   -1,  318,  319,  209,  210,   -1,
   -1,   -1,  310,  311,  312,   -1,   -1,  318,  319,   -1,
  318,  319,  372,  373,  372,  373,   -1,  310,  311,  312,
   -1,   -1,  372,  373,  372,  373,   -1,  310,  311,  312,
  372,  373,  372,  373,   -1,   -1,   -1,  372,  373,  372,
  373,   -1,  372,  373,   -1,   -1,   -1,  372,  373,  372,
  373,   -1,   -1,   -1,  372,  373,   -1,   -1,   -1,   -1,
   -1,  310,  311,  312,  372,  373,   -1,   -1,   -1,  318,
  319,   -1,  372,  373,   -1,   -1,   -1,   40,   -1,  372,
  373,   -1,   45,   -1,   -1,   -1,   -1,  265,  266,  372,
  373,  269,  270,  271,  272,  273,  274,  275,  276,  277,
  278,  279,  280,  281,  282,  283,  284,  285,  286,  287,
  288,   -1,   -1,  291,  292,  293,  294,  295,  296,  297,
  298,  299,   33,  372,  373,    0,   -1,  318,  319,   40,
   -1,  309,   -1,   -1,   -1,  313,  314,  315,  316,  317,
   -1,   -1,  320,  321,  322,  323,  324,  325,  326,  327,
  328,  329,  330,  331,  332,  333,  334,  335,  336,  337,
  338,  339,  340,  341,  342,  343,  344,  345,  346,  347,
  348,  349,  350,  351,  352,  353,  354,  355,  356,  357,
  358,  359,  360,  361,  362,  363,  364,  365,  366,  367,
  368,  369,  370,  371,   -1,   33,   -1,   -1,   -1,   -1,
  265,  266,   40,   -1,  269,  270,  271,  272,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
  285,  286,  287,  288,   -1,   -1,  291,  292,  293,  294,
  295,  296,  297,  298,  299,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  309,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  320,  321,  322,  323,  324,
  325,  326,  327,  328,  329,  330,  331,  332,  333,  334,
  335,  336,  337,  338,  339,  340,  341,  342,  343,  344,
  345,  346,  347,  348,  349,  350,  351,  352,  353,  354,
  355,  356,  357,  358,  359,  360,  361,  362,  363,  364,
  365,  366,  367,  368,  369,  370,  371,  270,  271,  272,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
  283,  284,  285,  286,  287,  288,   -1,   -1,  291,   -1,
   -1,   -1,   38,   -1,   -1,   -1,   42,   43,   -1,   45,
   -1,   47,   -1,   -1,   -1,   -1,  309,   -1,  259,   -1,
  261,   -1,  263,  264,   60,   61,   62,  320,  321,  322,
  323,  324,   -1,   -1,   -1,   -1,  329,  330,  331,  332,
  333,  334,  335,  336,  337,  338,  339,  340,  341,  342,
  291,   -1,  257,  258,  259,  260,  261,   40,  263,  264,
   -1,   -1,  267,  268,  357,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  313,  314,  315,  316,  317,   60,   61,   62,
   -1,   -1,   38,   -1,  289,  290,   42,   43,  124,   45,
   -1,   47,   -1,   -1,   -1,  300,  301,  302,  303,  304,
  305,  306,  307,  308,   60,   61,   62,   38,   -1,   -1,
   -1,   42,   43,    2,   45,   38,   47,   -1,   -1,   42,
   43,   40,   45,  291,   47,   -1,   -1,   -1,   -1,   60,
   61,   62,   -1,   -1,   -1,   58,   40,   41,   -1,   43,
   -1,   60,   61,   62,   -1,  313,  314,  315,  316,  317,
   -1,   40,   41,   -1,   43,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  124,   -1,
   93,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   93,
   -1,   -1,   -1,  124,   -1,   99,   -1,   -1,   -1,   -1,
   -1,  124,   -1,   -1,   93,   -1,   -1,   -1,   -1,   -1,
   99,  100,   -1,   -1,   -1,   -1,  105,  121,  107,   -1,
   -1,   -1,  126,   -1,   -1,  129,  130,   -1,   -1,   -1,
   -1,   -1,  121,   -1,   -1,  139,  140,   -1,   -1,   -1,
  129,  130,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  139,  140,  257,  258,  259,  260,  261,   -1,  263,  264,
   -1,   -1,  267,  268,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  310,  311,  312,   -1,   -1,   -1,
   -1,   -1,  318,  319,  289,  290,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  300,  301,  302,  303,  304,
  305,  306,  307,  308,   -1,  209,  210,   -1,  291,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  209,  210,   -1,   -1,   -1,   -1,   -1,  310,  311,  312,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  310,  311,  312,   -1,  262,  263,
   -1,   -1,  318,  319,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  291,  262,  263,   -1,   -1,   -1,   -1,  310,
  311,  312,   -1,   -1,   -1,   -1,   -1,  318,  319,   -1,
   -1,  310,  311,  312,   -1,  318,  319,  257,  258,  259,
  260,  261,   -1,  263,  264,   -1,   -1,  267,  268,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  289,
  290,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  300,  301,  302,  303,  304,  305,  306,  307,  308,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 374
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,0,"'&'",0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,
0,"':'",0,"'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'|'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"DST","SRC","HOST","GATEWAY","NET","NETMASK",
"PORT","PORTRANGE","LESS","GREATER","PROTO","PROTOCHAIN","CBYTE","ARP","RARP",
"IP","SCTP","TCP","UDP","ICMP","IGMP","IGRP","PIM","VRRP","CARP","ATALK","AARP",
"DECNET","LAT","SCA","MOPRC","MOPDL","TK_BROADCAST","TK_MULTICAST","NUM",
"INBOUND","OUTBOUND","PF_IFNAME","PF_RSET","PF_RNR","PF_SRNR","PF_REASON",
"PF_ACTION","TYPE","SUBTYPE","DIR","ADDR1","ADDR2","ADDR3","ADDR4","RA","TA",
"LINK","GEQ","LEQ","NEQ","ID","EID","HID","HID6","AID","LSH","RSH","LEN","IPV6",
"ICMPV6","AH","ESP","VLAN","MPLS","PPPOED","PPPOES","ISO","ESIS","CLNP","ISIS",
"L1","L2","IIH","LSP","SNP","CSNP","PSNP","STP","IPX","NETBEUI","LANE","LLC",
"METAC","BCC","SC","ILMIC","OAMF4EC","OAMF4SC","OAM","OAMF4","CONNECTMSG",
"METACONNECT","VPI","VCI","RADIO","FISU","LSSU","MSU","HFISU","HLSSU","HMSU",
"SIO","OPC","DPC","SLS","HSIO","HOPC","HDPC","HSLS","OR","AND","UMINUS",
};
char *yyrule[] = {
"$accept : prog",
"prog : null expr",
"prog : null",
"null :",
"expr : term",
"expr : expr and term",
"expr : expr and id",
"expr : expr or term",
"expr : expr or id",
"and : AND",
"or : OR",
"id : nid",
"id : pnum",
"id : paren pid ')'",
"nid : ID",
"nid : HID '/' NUM",
"nid : HID NETMASK HID",
"nid : HID",
"nid : HID6 '/' NUM",
"nid : HID6",
"nid : EID",
"nid : AID",
"nid : not id",
"not : '!'",
"paren : '('",
"pid : nid",
"pid : qid and id",
"pid : qid or id",
"qid : pnum",
"qid : pid",
"term : rterm",
"term : not term",
"head : pqual dqual aqual",
"head : pqual dqual",
"head : pqual aqual",
"head : pqual PROTO",
"head : pqual PROTOCHAIN",
"head : pqual ndaqual",
"rterm : head id",
"rterm : paren expr ')'",
"rterm : pname",
"rterm : arth relop arth",
"rterm : arth irelop arth",
"rterm : other",
"rterm : atmtype",
"rterm : atmmultitype",
"rterm : atmfield atmvalue",
"rterm : mtp2type",
"rterm : mtp3field mtp3value",
"pqual : pname",
"pqual :",
"dqual : SRC",
"dqual : DST",
"dqual : SRC OR DST",
"dqual : DST OR SRC",
"dqual : SRC AND DST",
"dqual : DST AND SRC",
"dqual : ADDR1",
"dqual : ADDR2",
"dqual : ADDR3",
"dqual : ADDR4",
"dqual : RA",
"dqual : TA",
"aqual : HOST",
"aqual : NET",
"aqual : PORT",
"aqual : PORTRANGE",
"ndaqual : GATEWAY",
"pname : LINK",
"pname : IP",
"pname : ARP",
"pname : RARP",
"pname : SCTP",
"pname : TCP",
"pname : UDP",
"pname : ICMP",
"pname : IGMP",
"pname : IGRP",
"pname : PIM",
"pname : VRRP",
"pname : CARP",
"pname : ATALK",
"pname : AARP",
"pname : DECNET",
"pname : LAT",
"pname : SCA",
"pname : MOPDL",
"pname : MOPRC",
"pname : IPV6",
"pname : ICMPV6",
"pname : AH",
"pname : ESP",
"pname : ISO",
"pname : ESIS",
"pname : ISIS",
"pname : L1",
"pname : L2",
"pname : IIH",
"pname : LSP",
"pname : SNP",
"pname : PSNP",
"pname : CSNP",
"pname : CLNP",
"pname : STP",
"pname : IPX",
"pname : NETBEUI",
"pname : RADIO",
"other : pqual TK_BROADCAST",
"other : pqual TK_MULTICAST",
"other : LESS NUM",
"other : GREATER NUM",
"other : CBYTE NUM byteop NUM",
"other : INBOUND",
"other : OUTBOUND",
"other : VLAN pnum",
"other : VLAN",
"other : MPLS pnum",
"other : MPLS",
"other : PPPOED",
"other : PPPOES pnum",
"other : PPPOES",
"other : pfvar",
"other : pqual p80211",
"pfvar : PF_IFNAME ID",
"pfvar : PF_RSET ID",
"pfvar : PF_RNR NUM",
"pfvar : PF_SRNR NUM",
"pfvar : PF_REASON reason",
"pfvar : PF_ACTION action",
"p80211 : TYPE type SUBTYPE subtype",
"p80211 : TYPE type",
"p80211 : SUBTYPE type_subtype",
"p80211 : DIR dir",
"type : NUM",
"type : ID",
"subtype : NUM",
"subtype : ID",
"type_subtype : ID",
"dir : NUM",
"dir : ID",
"reason : NUM",
"reason : ID",
"action : ID",
"relop : '>'",
"relop : GEQ",
"relop : '='",
"irelop : LEQ",
"irelop : '<'",
"irelop : NEQ",
"arth : pnum",
"arth : narth",
"narth : pname '[' arth ']'",
"narth : pname '[' arth ':' NUM ']'",
"narth : arth '+' arth",
"narth : arth '-' arth",
"narth : arth '*' arth",
"narth : arth '/' arth",
"narth : arth '&' arth",
"narth : arth '|' arth",
"narth : arth LSH arth",
"narth : arth RSH arth",
"narth : '-' arth",
"narth : paren narth ')'",
"narth : LEN",
"byteop : '&'",
"byteop : '|'",
"byteop : '<'",
"byteop : '>'",
"byteop : '='",
"pnum : NUM",
"pnum : paren pnum ')'",
"atmtype : LANE",
"atmtype : LLC",
"atmtype : METAC",
"atmtype : BCC",
"atmtype : OAMF4EC",
"atmtype : OAMF4SC",
"atmtype : SC",
"atmtype : ILMIC",
"atmmultitype : OAM",
"atmmultitype : OAMF4",
"atmmultitype : CONNECTMSG",
"atmmultitype : METACONNECT",
"atmfield : VPI",
"atmfield : VCI",
"atmvalue : atmfieldvalue",
"atmvalue : relop NUM",
"atmvalue : irelop NUM",
"atmvalue : paren atmlistvalue ')'",
"atmfieldvalue : NUM",
"atmlistvalue : atmfieldvalue",
"atmlistvalue : atmlistvalue or atmfieldvalue",
"mtp2type : FISU",
"mtp2type : LSSU",
"mtp2type : MSU",
"mtp2type : HFISU",
"mtp2type : HLSSU",
"mtp2type : HMSU",
"mtp3field : SIO",
"mtp3field : OPC",
"mtp3field : DPC",
"mtp3field : SLS",
"mtp3field : HSIO",
"mtp3field : HOPC",
"mtp3field : HDPC",
"mtp3field : HSLS",
"mtp3value : mtp3fieldvalue",
"mtp3value : relop NUM",
"mtp3value : irelop NUM",
"mtp3value : paren mtp3listvalue ')'",
"mtp3fieldvalue : NUM",
"mtp3listvalue : mtp3fieldvalue",
"mtp3listvalue : mtp3listvalue or mtp3fieldvalue",
};
#endif
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#ifdef YYSTACKSIZE
#ifndef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#endif
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#define YYABORT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("yydebug: state %d, reading %d (%s)\n", yystate,
                    yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("yydebug: state %d, shifting to state %d (%s)\n",
                    yystate, yytable[yyn],yyrule[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("yydebug: state %d, error recovery shifting\
 to state %d\n", *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("yydebug: error recovery discarding state %d\n",
                            *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("yydebug: state %d, error recovery discards token %d (%s)\n",
                    yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("yydebug: state %d, reducing by rule %d (%s)\n",
                yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 317 "grammar.y"
{
	finish_parse(yyvsp[0].blk.b);
}
break;
case 3:
#line 322 "grammar.y"
{ yyval.blk.q = qerr; }
break;
case 5:
#line 325 "grammar.y"
{ gen_and(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
break;
case 6:
#line 326 "grammar.y"
{ gen_and(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
break;
case 7:
#line 327 "grammar.y"
{ gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
break;
case 8:
#line 328 "grammar.y"
{ gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
break;
case 9:
#line 330 "grammar.y"
{ yyval.blk = yyvsp[-1].blk; }
break;
case 10:
#line 332 "grammar.y"
{ yyval.blk = yyvsp[-1].blk; }
break;
case 12:
#line 335 "grammar.y"
{ yyval.blk.b = gen_ncode(NULL, (bpf_u_int32)yyvsp[0].i,
						   yyval.blk.q = yyvsp[-1].blk.q); }
break;
case 13:
#line 337 "grammar.y"
{ yyval.blk = yyvsp[-1].blk; }
break;
case 14:
#line 339 "grammar.y"
{ yyval.blk.b = gen_scode(yyvsp[0].s, yyval.blk.q = yyvsp[-1].blk.q); }
break;
case 15:
#line 340 "grammar.y"
{ yyval.blk.b = gen_mcode(yyvsp[-2].s, NULL, yyvsp[0].i,
				    yyval.blk.q = yyvsp[-3].blk.q); }
break;
case 16:
#line 342 "grammar.y"
{ yyval.blk.b = gen_mcode(yyvsp[-2].s, yyvsp[0].s, 0,
				    yyval.blk.q = yyvsp[-3].blk.q); }
break;
case 17:
#line 344 "grammar.y"
{
				  /* Decide how to parse HID based on proto */
				  yyval.blk.q = yyvsp[-1].blk.q;
				  if (yyval.blk.q.addr == Q_PORT)
				  	bpf_error("'port' modifier applied to ip host");
				  else if (yyval.blk.q.addr == Q_PORTRANGE)
				  	bpf_error("'portrange' modifier applied to ip host");
				  else if (yyval.blk.q.addr == Q_PROTO)
				  	bpf_error("'proto' modifier applied to ip host");
				  else if (yyval.blk.q.addr == Q_PROTOCHAIN)
				  	bpf_error("'protochain' modifier applied to ip host");
				  yyval.blk.b = gen_ncode(yyvsp[0].s, 0, yyval.blk.q);
				}
break;
case 18:
#line 357 "grammar.y"
{
#ifdef INET6
				  yyval.blk.b = gen_mcode6(yyvsp[-2].s, NULL, yyvsp[0].i,
				    yyval.blk.q = yyvsp[-3].blk.q);
#else
				  bpf_error("'ip6addr/prefixlen' not supported "
					"in this configuration");
#endif /*INET6*/
				}
break;
case 19:
#line 366 "grammar.y"
{
#ifdef INET6
				  yyval.blk.b = gen_mcode6(yyvsp[0].s, 0, 128,
				    yyval.blk.q = yyvsp[-1].blk.q);
#else
				  bpf_error("'ip6addr' not supported "
					"in this configuration");
#endif /*INET6*/
				}
break;
case 20:
#line 375 "grammar.y"
{ 
				  yyval.blk.b = gen_ecode(yyvsp[0].e, yyval.blk.q = yyvsp[-1].blk.q);
				  /*
				   * $1 was allocated by "pcap_ether_aton()",
				   * so we must free it now that we're done
				   * with it.
				   */
				  free(yyvsp[0].e);
				}
break;
case 21:
#line 384 "grammar.y"
{
				  yyval.blk.b = gen_acode(yyvsp[0].e, yyval.blk.q = yyvsp[-1].blk.q);
				  /*
				   * $1 was allocated by "pcap_ether_aton()",
				   * so we must free it now that we're done
				   * with it.
				   */
				  free(yyvsp[0].e);
				}
break;
case 22:
#line 393 "grammar.y"
{ gen_not(yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
break;
case 23:
#line 395 "grammar.y"
{ yyval.blk = yyvsp[-1].blk; }
break;
case 24:
#line 397 "grammar.y"
{ yyval.blk = yyvsp[-1].blk; }
break;
case 26:
#line 400 "grammar.y"
{ gen_and(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
break;
case 27:
#line 401 "grammar.y"
{ gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
break;
case 28:
#line 403 "grammar.y"
{ yyval.blk.b = gen_ncode(NULL, (bpf_u_int32)yyvsp[0].i,
						   yyval.blk.q = yyvsp[-1].blk.q); }
break;
case 31:
#line 408 "grammar.y"
{ gen_not(yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
break;
case 32:
#line 410 "grammar.y"
{ QSET(yyval.blk.q, yyvsp[-2].i, yyvsp[-1].i, yyvsp[0].i); }
break;
case 33:
#line 411 "grammar.y"
{ QSET(yyval.blk.q, yyvsp[-1].i, yyvsp[0].i, Q_DEFAULT); }
break;
case 34:
#line 412 "grammar.y"
{ QSET(yyval.blk.q, yyvsp[-1].i, Q_DEFAULT, yyvsp[0].i); }
break;
case 35:
#line 413 "grammar.y"
{ QSET(yyval.blk.q, yyvsp[-1].i, Q_DEFAULT, Q_PROTO); }
break;
case 36:
#line 414 "grammar.y"
{ QSET(yyval.blk.q, yyvsp[-1].i, Q_DEFAULT, Q_PROTOCHAIN); }
break;
case 37:
#line 415 "grammar.y"
{ QSET(yyval.blk.q, yyvsp[-1].i, Q_DEFAULT, yyvsp[0].i); }
break;
case 38:
#line 417 "grammar.y"
{ yyval.blk = yyvsp[0].blk; }
break;
case 39:
#line 418 "grammar.y"
{ yyval.blk.b = yyvsp[-1].blk.b; yyval.blk.q = yyvsp[-2].blk.q; }
break;
case 40:
#line 419 "grammar.y"
{ yyval.blk.b = gen_proto_abbrev(yyvsp[0].i); yyval.blk.q = qerr; }
break;
case 41:
#line 420 "grammar.y"
{ yyval.blk.b = gen_relation(yyvsp[-1].i, yyvsp[-2].a, yyvsp[0].a, 0);
				  yyval.blk.q = qerr; }
break;
case 42:
#line 422 "grammar.y"
{ yyval.blk.b = gen_relation(yyvsp[-1].i, yyvsp[-2].a, yyvsp[0].a, 1);
				  yyval.blk.q = qerr; }
break;
case 43:
#line 424 "grammar.y"
{ yyval.blk.b = yyvsp[0].rblk; yyval.blk.q = qerr; }
break;
case 44:
#line 425 "grammar.y"
{ yyval.blk.b = gen_atmtype_abbrev(yyvsp[0].i); yyval.blk.q = qerr; }
break;
case 45:
#line 426 "grammar.y"
{ yyval.blk.b = gen_atmmulti_abbrev(yyvsp[0].i); yyval.blk.q = qerr; }
break;
case 46:
#line 427 "grammar.y"
{ yyval.blk.b = yyvsp[0].blk.b; yyval.blk.q = qerr; }
break;
case 47:
#line 428 "grammar.y"
{ yyval.blk.b = gen_mtp2type_abbrev(yyvsp[0].i); yyval.blk.q = qerr; }
break;
case 48:
#line 429 "grammar.y"
{ yyval.blk.b = yyvsp[0].blk.b; yyval.blk.q = qerr; }
break;
case 50:
#line 433 "grammar.y"
{ yyval.i = Q_DEFAULT; }
break;
case 51:
#line 436 "grammar.y"
{ yyval.i = Q_SRC; }
break;
case 52:
#line 437 "grammar.y"
{ yyval.i = Q_DST; }
break;
case 53:
#line 438 "grammar.y"
{ yyval.i = Q_OR; }
break;
case 54:
#line 439 "grammar.y"
{ yyval.i = Q_OR; }
break;
case 55:
#line 440 "grammar.y"
{ yyval.i = Q_AND; }
break;
case 56:
#line 441 "grammar.y"
{ yyval.i = Q_AND; }
break;
case 57:
#line 442 "grammar.y"
{ yyval.i = Q_ADDR1; }
break;
case 58:
#line 443 "grammar.y"
{ yyval.i = Q_ADDR2; }
break;
case 59:
#line 444 "grammar.y"
{ yyval.i = Q_ADDR3; }
break;
case 60:
#line 445 "grammar.y"
{ yyval.i = Q_ADDR4; }
break;
case 61:
#line 446 "grammar.y"
{ yyval.i = Q_RA; }
break;
case 62:
#line 447 "grammar.y"
{ yyval.i = Q_TA; }
break;
case 63:
#line 450 "grammar.y"
{ yyval.i = Q_HOST; }
break;
case 64:
#line 451 "grammar.y"
{ yyval.i = Q_NET; }
break;
case 65:
#line 452 "grammar.y"
{ yyval.i = Q_PORT; }
break;
case 66:
#line 453 "grammar.y"
{ yyval.i = Q_PORTRANGE; }
break;
case 67:
#line 456 "grammar.y"
{ yyval.i = Q_GATEWAY; }
break;
case 68:
#line 458 "grammar.y"
{ yyval.i = Q_LINK; }
break;
case 69:
#line 459 "grammar.y"
{ yyval.i = Q_IP; }
break;
case 70:
#line 460 "grammar.y"
{ yyval.i = Q_ARP; }
break;
case 71:
#line 461 "grammar.y"
{ yyval.i = Q_RARP; }
break;
case 72:
#line 462 "grammar.y"
{ yyval.i = Q_SCTP; }
break;
case 73:
#line 463 "grammar.y"
{ yyval.i = Q_TCP; }
break;
case 74:
#line 464 "grammar.y"
{ yyval.i = Q_UDP; }
break;
case 75:
#line 465 "grammar.y"
{ yyval.i = Q_ICMP; }
break;
case 76:
#line 466 "grammar.y"
{ yyval.i = Q_IGMP; }
break;
case 77:
#line 467 "grammar.y"
{ yyval.i = Q_IGRP; }
break;
case 78:
#line 468 "grammar.y"
{ yyval.i = Q_PIM; }
break;
case 79:
#line 469 "grammar.y"
{ yyval.i = Q_VRRP; }
break;
case 80:
#line 470 "grammar.y"
{ yyval.i = Q_CARP; }
break;
case 81:
#line 471 "grammar.y"
{ yyval.i = Q_ATALK; }
break;
case 82:
#line 472 "grammar.y"
{ yyval.i = Q_AARP; }
break;
case 83:
#line 473 "grammar.y"
{ yyval.i = Q_DECNET; }
break;
case 84:
#line 474 "grammar.y"
{ yyval.i = Q_LAT; }
break;
case 85:
#line 475 "grammar.y"
{ yyval.i = Q_SCA; }
break;
case 86:
#line 476 "grammar.y"
{ yyval.i = Q_MOPDL; }
break;
case 87:
#line 477 "grammar.y"
{ yyval.i = Q_MOPRC; }
break;
case 88:
#line 478 "grammar.y"
{ yyval.i = Q_IPV6; }
break;
case 89:
#line 479 "grammar.y"
{ yyval.i = Q_ICMPV6; }
break;
case 90:
#line 480 "grammar.y"
{ yyval.i = Q_AH; }
break;
case 91:
#line 481 "grammar.y"
{ yyval.i = Q_ESP; }
break;
case 92:
#line 482 "grammar.y"
{ yyval.i = Q_ISO; }
break;
case 93:
#line 483 "grammar.y"
{ yyval.i = Q_ESIS; }
break;
case 94:
#line 484 "grammar.y"
{ yyval.i = Q_ISIS; }
break;
case 95:
#line 485 "grammar.y"
{ yyval.i = Q_ISIS_L1; }
break;
case 96:
#line 486 "grammar.y"
{ yyval.i = Q_ISIS_L2; }
break;
case 97:
#line 487 "grammar.y"
{ yyval.i = Q_ISIS_IIH; }
break;
case 98:
#line 488 "grammar.y"
{ yyval.i = Q_ISIS_LSP; }
break;
case 99:
#line 489 "grammar.y"
{ yyval.i = Q_ISIS_SNP; }
break;
case 100:
#line 490 "grammar.y"
{ yyval.i = Q_ISIS_PSNP; }
break;
case 101:
#line 491 "grammar.y"
{ yyval.i = Q_ISIS_CSNP; }
break;
case 102:
#line 492 "grammar.y"
{ yyval.i = Q_CLNP; }
break;
case 103:
#line 493 "grammar.y"
{ yyval.i = Q_STP; }
break;
case 104:
#line 494 "grammar.y"
{ yyval.i = Q_IPX; }
break;
case 105:
#line 495 "grammar.y"
{ yyval.i = Q_NETBEUI; }
break;
case 106:
#line 496 "grammar.y"
{ yyval.i = Q_RADIO; }
break;
case 107:
#line 498 "grammar.y"
{ yyval.rblk = gen_broadcast(yyvsp[-1].i); }
break;
case 108:
#line 499 "grammar.y"
{ yyval.rblk = gen_multicast(yyvsp[-1].i); }
break;
case 109:
#line 500 "grammar.y"
{ yyval.rblk = gen_less(yyvsp[0].i); }
break;
case 110:
#line 501 "grammar.y"
{ yyval.rblk = gen_greater(yyvsp[0].i); }
break;
case 111:
#line 502 "grammar.y"
{ yyval.rblk = gen_byteop(yyvsp[-1].i, yyvsp[-2].i, yyvsp[0].i); }
break;
case 112:
#line 503 "grammar.y"
{ yyval.rblk = gen_inbound(0); }
break;
case 113:
#line 504 "grammar.y"
{ yyval.rblk = gen_inbound(1); }
break;
case 114:
#line 505 "grammar.y"
{ yyval.rblk = gen_vlan(yyvsp[0].i); }
break;
case 115:
#line 506 "grammar.y"
{ yyval.rblk = gen_vlan(-1); }
break;
case 116:
#line 507 "grammar.y"
{ yyval.rblk = gen_mpls(yyvsp[0].i); }
break;
case 117:
#line 508 "grammar.y"
{ yyval.rblk = gen_mpls(-1); }
break;
case 118:
#line 509 "grammar.y"
{ yyval.rblk = gen_pppoed(); }
break;
case 119:
#line 510 "grammar.y"
{ yyval.rblk = gen_pppoes(yyvsp[0].i); }
break;
case 120:
#line 511 "grammar.y"
{ yyval.rblk = gen_pppoes(-1); }
break;
case 121:
#line 512 "grammar.y"
{ yyval.rblk = yyvsp[0].rblk; }
break;
case 122:
#line 513 "grammar.y"
{ yyval.rblk = yyvsp[0].rblk; }
break;
case 123:
#line 516 "grammar.y"
{ yyval.rblk = gen_pf_ifname(yyvsp[0].s); }
break;
case 124:
#line 517 "grammar.y"
{ yyval.rblk = gen_pf_ruleset(yyvsp[0].s); }
break;
case 125:
#line 518 "grammar.y"
{ yyval.rblk = gen_pf_rnr(yyvsp[0].i); }
break;
case 126:
#line 519 "grammar.y"
{ yyval.rblk = gen_pf_srnr(yyvsp[0].i); }
break;
case 127:
#line 520 "grammar.y"
{ yyval.rblk = gen_pf_reason(yyvsp[0].i); }
break;
case 128:
#line 521 "grammar.y"
{ yyval.rblk = gen_pf_action(yyvsp[0].i); }
break;
case 129:
#line 525 "grammar.y"
{ yyval.rblk = gen_p80211_type(yyvsp[-2].i | yyvsp[0].i,
					IEEE80211_FC0_TYPE_MASK |
					IEEE80211_FC0_SUBTYPE_MASK);
				}
break;
case 130:
#line 529 "grammar.y"
{ yyval.rblk = gen_p80211_type(yyvsp[0].i,
					IEEE80211_FC0_TYPE_MASK);
				}
break;
case 131:
#line 532 "grammar.y"
{ yyval.rblk = gen_p80211_type(yyvsp[0].i,
					IEEE80211_FC0_TYPE_MASK |
					IEEE80211_FC0_SUBTYPE_MASK);
				}
break;
case 132:
#line 536 "grammar.y"
{ yyval.rblk = gen_p80211_fcdir(yyvsp[0].i); }
break;
case 134:
#line 540 "grammar.y"
{ yyval.i = str2tok(yyvsp[0].s, ieee80211_types);
				  if (yyval.i == -1)
				  	bpf_error("unknown 802.11 type name");
				}
break;
case 136:
#line 547 "grammar.y"
{ const struct tok *types = NULL;
				  int i;
				  for (i = 0;; i++) {
				  	if (ieee80211_type_subtypes[i].tok == NULL) {
				  		/* Ran out of types */
						bpf_error("unknown 802.11 type");
						break;
					}
					if (yyvsp[-2].i == ieee80211_type_subtypes[i].type) {
						types = ieee80211_type_subtypes[i].tok;
						break;
					}
				  }

				  yyval.i = str2tok(yyvsp[0].s, types);
				  if (yyval.i == -1)
					bpf_error("unknown 802.11 subtype name");
				}
break;
case 137:
#line 567 "grammar.y"
{ int i;
				  for (i = 0;; i++) {
				  	if (ieee80211_type_subtypes[i].tok == NULL) {
				  		/* Ran out of types */
						bpf_error("unknown 802.11 type name");
						break;
					}
					yyval.i = str2tok(yyvsp[0].s, ieee80211_type_subtypes[i].tok);
					if (yyval.i != -1) {
						yyval.i |= ieee80211_type_subtypes[i].type;
						break;
					}
				  }
				}
break;
case 139:
#line 584 "grammar.y"
{ if (pcap_strcasecmp(yyvsp[0].s, "nods") == 0)
					yyval.i = IEEE80211_FC1_DIR_NODS;
				  else if (pcap_strcasecmp(yyvsp[0].s, "tods") == 0)
					yyval.i = IEEE80211_FC1_DIR_TODS;
				  else if (pcap_strcasecmp(yyvsp[0].s, "fromds") == 0)
					yyval.i = IEEE80211_FC1_DIR_FROMDS;
				  else if (pcap_strcasecmp(yyvsp[0].s, "dstods") == 0)
					yyval.i = IEEE80211_FC1_DIR_DSTODS;
				  else
					bpf_error("unknown 802.11 direction");
				}
break;
case 140:
#line 597 "grammar.y"
{ yyval.i = yyvsp[0].i; }
break;
case 141:
#line 598 "grammar.y"
{ yyval.i = pfreason_to_num(yyvsp[0].s); }
break;
case 142:
#line 601 "grammar.y"
{ yyval.i = pfaction_to_num(yyvsp[0].s); }
break;
case 143:
#line 604 "grammar.y"
{ yyval.i = BPF_JGT; }
break;
case 144:
#line 605 "grammar.y"
{ yyval.i = BPF_JGE; }
break;
case 145:
#line 606 "grammar.y"
{ yyval.i = BPF_JEQ; }
break;
case 146:
#line 608 "grammar.y"
{ yyval.i = BPF_JGT; }
break;
case 147:
#line 609 "grammar.y"
{ yyval.i = BPF_JGE; }
break;
case 148:
#line 610 "grammar.y"
{ yyval.i = BPF_JEQ; }
break;
case 149:
#line 612 "grammar.y"
{ yyval.a = gen_loadi(yyvsp[0].i); }
break;
case 151:
#line 615 "grammar.y"
{ yyval.a = gen_load(yyvsp[-3].i, yyvsp[-1].a, 1); }
break;
case 152:
#line 616 "grammar.y"
{ yyval.a = gen_load(yyvsp[-5].i, yyvsp[-3].a, yyvsp[-1].i); }
break;
case 153:
#line 617 "grammar.y"
{ yyval.a = gen_arth(BPF_ADD, yyvsp[-2].a, yyvsp[0].a); }
break;
case 154:
#line 618 "grammar.y"
{ yyval.a = gen_arth(BPF_SUB, yyvsp[-2].a, yyvsp[0].a); }
break;
case 155:
#line 619 "grammar.y"
{ yyval.a = gen_arth(BPF_MUL, yyvsp[-2].a, yyvsp[0].a); }
break;
case 156:
#line 620 "grammar.y"
{ yyval.a = gen_arth(BPF_DIV, yyvsp[-2].a, yyvsp[0].a); }
break;
case 157:
#line 621 "grammar.y"
{ yyval.a = gen_arth(BPF_AND, yyvsp[-2].a, yyvsp[0].a); }
break;
case 158:
#line 622 "grammar.y"
{ yyval.a = gen_arth(BPF_OR, yyvsp[-2].a, yyvsp[0].a); }
break;
case 159:
#line 623 "grammar.y"
{ yyval.a = gen_arth(BPF_LSH, yyvsp[-2].a, yyvsp[0].a); }
break;
case 160:
#line 624 "grammar.y"
{ yyval.a = gen_arth(BPF_RSH, yyvsp[-2].a, yyvsp[0].a); }
break;
case 161:
#line 625 "grammar.y"
{ yyval.a = gen_neg(yyvsp[0].a); }
break;
case 162:
#line 626 "grammar.y"
{ yyval.a = yyvsp[-1].a; }
break;
case 163:
#line 627 "grammar.y"
{ yyval.a = gen_loadlen(); }
break;
case 164:
#line 629 "grammar.y"
{ yyval.i = '&'; }
break;
case 165:
#line 630 "grammar.y"
{ yyval.i = '|'; }
break;
case 166:
#line 631 "grammar.y"
{ yyval.i = '<'; }
break;
case 167:
#line 632 "grammar.y"
{ yyval.i = '>'; }
break;
case 168:
#line 633 "grammar.y"
{ yyval.i = '='; }
break;
case 170:
#line 636 "grammar.y"
{ yyval.i = yyvsp[-1].i; }
break;
case 171:
#line 638 "grammar.y"
{ yyval.i = A_LANE; }
break;
case 172:
#line 639 "grammar.y"
{ yyval.i = A_LLC; }
break;
case 173:
#line 640 "grammar.y"
{ yyval.i = A_METAC;	}
break;
case 174:
#line 641 "grammar.y"
{ yyval.i = A_BCC; }
break;
case 175:
#line 642 "grammar.y"
{ yyval.i = A_OAMF4EC; }
break;
case 176:
#line 643 "grammar.y"
{ yyval.i = A_OAMF4SC; }
break;
case 177:
#line 644 "grammar.y"
{ yyval.i = A_SC; }
break;
case 178:
#line 645 "grammar.y"
{ yyval.i = A_ILMIC; }
break;
case 179:
#line 647 "grammar.y"
{ yyval.i = A_OAM; }
break;
case 180:
#line 648 "grammar.y"
{ yyval.i = A_OAMF4; }
break;
case 181:
#line 649 "grammar.y"
{ yyval.i = A_CONNECTMSG; }
break;
case 182:
#line 650 "grammar.y"
{ yyval.i = A_METACONNECT; }
break;
case 183:
#line 653 "grammar.y"
{ yyval.blk.atmfieldtype = A_VPI; }
break;
case 184:
#line 654 "grammar.y"
{ yyval.blk.atmfieldtype = A_VCI; }
break;
case 186:
#line 657 "grammar.y"
{ yyval.blk.b = gen_atmfield_code(yyvsp[-2].blk.atmfieldtype, (bpf_int32)yyvsp[0].i, (bpf_u_int32)yyvsp[-1].i, 0); }
break;
case 187:
#line 658 "grammar.y"
{ yyval.blk.b = gen_atmfield_code(yyvsp[-2].blk.atmfieldtype, (bpf_int32)yyvsp[0].i, (bpf_u_int32)yyvsp[-1].i, 1); }
break;
case 188:
#line 659 "grammar.y"
{ yyval.blk.b = yyvsp[-1].blk.b; yyval.blk.q = qerr; }
break;
case 189:
#line 661 "grammar.y"
{
	yyval.blk.atmfieldtype = yyvsp[-1].blk.atmfieldtype;
	if (yyval.blk.atmfieldtype == A_VPI ||
	    yyval.blk.atmfieldtype == A_VCI)
		yyval.blk.b = gen_atmfield_code(yyval.blk.atmfieldtype, (bpf_int32) yyvsp[0].i, BPF_JEQ, 0);
	}
break;
case 191:
#line 669 "grammar.y"
{ gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
break;
case 192:
#line 672 "grammar.y"
{ yyval.i = M_FISU; }
break;
case 193:
#line 673 "grammar.y"
{ yyval.i = M_LSSU; }
break;
case 194:
#line 674 "grammar.y"
{ yyval.i = M_MSU; }
break;
case 195:
#line 675 "grammar.y"
{ yyval.i = MH_FISU; }
break;
case 196:
#line 676 "grammar.y"
{ yyval.i = MH_LSSU; }
break;
case 197:
#line 677 "grammar.y"
{ yyval.i = MH_MSU; }
break;
case 198:
#line 680 "grammar.y"
{ yyval.blk.mtp3fieldtype = M_SIO; }
break;
case 199:
#line 681 "grammar.y"
{ yyval.blk.mtp3fieldtype = M_OPC; }
break;
case 200:
#line 682 "grammar.y"
{ yyval.blk.mtp3fieldtype = M_DPC; }
break;
case 201:
#line 683 "grammar.y"
{ yyval.blk.mtp3fieldtype = M_SLS; }
break;
case 202:
#line 684 "grammar.y"
{ yyval.blk.mtp3fieldtype = MH_SIO; }
break;
case 203:
#line 685 "grammar.y"
{ yyval.blk.mtp3fieldtype = MH_OPC; }
break;
case 204:
#line 686 "grammar.y"
{ yyval.blk.mtp3fieldtype = MH_DPC; }
break;
case 205:
#line 687 "grammar.y"
{ yyval.blk.mtp3fieldtype = MH_SLS; }
break;
case 207:
#line 690 "grammar.y"
{ yyval.blk.b = gen_mtp3field_code(yyvsp[-2].blk.mtp3fieldtype, (u_int)yyvsp[0].i, (u_int)yyvsp[-1].i, 0); }
break;
case 208:
#line 691 "grammar.y"
{ yyval.blk.b = gen_mtp3field_code(yyvsp[-2].blk.mtp3fieldtype, (u_int)yyvsp[0].i, (u_int)yyvsp[-1].i, 1); }
break;
case 209:
#line 692 "grammar.y"
{ yyval.blk.b = yyvsp[-1].blk.b; yyval.blk.q = qerr; }
break;
case 210:
#line 694 "grammar.y"
{
	yyval.blk.mtp3fieldtype = yyvsp[-1].blk.mtp3fieldtype;
	if (yyval.blk.mtp3fieldtype == M_SIO ||
	    yyval.blk.mtp3fieldtype == M_OPC ||
	    yyval.blk.mtp3fieldtype == M_DPC ||
	    yyval.blk.mtp3fieldtype == M_SLS ||
	    yyval.blk.mtp3fieldtype == MH_SIO ||
	    yyval.blk.mtp3fieldtype == MH_OPC ||
	    yyval.blk.mtp3fieldtype == MH_DPC ||
	    yyval.blk.mtp3fieldtype == MH_SLS)
		yyval.blk.b = gen_mtp3field_code(yyval.blk.mtp3fieldtype, (u_int) yyvsp[0].i, BPF_JEQ, 0);
	}
break;
case 212:
#line 708 "grammar.y"
{ gen_or(yyvsp[-2].blk.b, yyvsp[0].blk.b); yyval.blk = yyvsp[0].blk; }
break;
#line 2079 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("yydebug: after reduction, shifting from state 0 to\
 state %d\n", YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("yydebug: state %d, reading %d (%s)\n",
                        YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("yydebug: after reduction, shifting from state %d \
to state %d\n", *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
