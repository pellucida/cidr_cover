
CFLAGS	+= -g
cidr_cover:	cidr_cover.o calc_cover.o addr_range.o netaddr.o calc_cover.o util.o

clean: 
	rm -f *.o a.out

distclean:	clean
	rm -f cidr_cover

addr_range.o: addr_range.c netaddr.h addr_range.h
addr_range.o: addr_range.h netaddr.h
calc_cover.o: calc_cover.c util.h netaddr.h addr_range.h calc_cover.h
calc_cover.o: calc_cover.h netaddr.h addr_range.h
cidr_cover.o: cidr_cover.c constant.h util.h netaddr.h addr_range.h calc_cover.h
constant.o: constant.h
netaddr.o: netaddr.c constant.h netaddr.h
netaddr.o: netaddr.h
util.o: util.c
util.o: util.h
