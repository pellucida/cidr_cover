/*
//	@(#) netaddr.c
//	@(License-CC0)
*/
# include	<ctype.h>
# include	<string.h>
# include	<stdio.h>
# include	<errno.h>
# include	<arpa/inet.h>
# include	"constant.h"
# include	"netaddr.h"

// _pton and _ntop versions that use host byte order. (IPV4 only) 
int     inet_ptoh (int family, const char* src, void* dst) {
        in_addr_t       addr    = 0;
        int     result  = -1;
        if (family != AF_INET) {
                errno   = EAFNOSUPPORT;
        }
        else    {
                result  = inet_pton (family, src, &addr);
                if (result == ADDR_OK) {
                        *((haddr_t*)(dst))      = ntohl(addr);
                }
        }
        return  result;
}
const char*  inet_htop (int family,const void *src,char *dst,socklen_t size) {
        const   char*   result  = 0;
        if (family != AF_INET) {
                errno   = EAFNOSUPPORT;
        }
        else    {       
                haddr_t addr    = *((haddr_t*)(src));
                in_addr_t       naddr   = htonl (addr);
                result  = inet_ntop (family, &naddr, dst, size);
        }
        return  result;
}
