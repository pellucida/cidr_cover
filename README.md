## CIDR_COVER

### Synopis


<b>cidr_cover</b> [<b>-R</b> <i>start-end</i> [<b>-R</b> <i>start-end</i>]...] [<i>files</i>...]


Create minimal address/mask set to cover a given range of IPv4 addresses

### Example

>10.1.2.1-10.1.2.7 &rarr;
>	10.1.2.1/32 = 10.1.2.1
>	10.1.2.2/31 = 10.1.2.2-10.1.2.3
>	10.1.2.4/30 = 10.1.2.4-10.1.3.7


Cidr_cover inputs IPv4 address ranges from the command line
(-R start-end) and/or one per line from the input (by default stdin.)
For each such line it calculates the sequence of addresses and masks
and outputs each address and mask, one per line.


```
Address range format: start-address <hyphen> or <tab> end-address 
```

Note: these ranges  are inclusive.

```
$ ./cidr_cover -R 10.1.2.1-10.1.2.7
10.1.2.1/32
10.1.2.2/31
10.1.2.4/30
```

```
./cidr_cover <<_END_
1.0.1.0-1.0.1.255
_END_
1.0.1.0/24
```

```
./cidr_cover -R 10.1.1.0-10.1.3.255 /dev/stdin <<_END_
1.0.1.0-1.0.1.255
_END_
10.1.1.0/24
10.1.2.0/23
1.0.1.0/24
```


The range 0.0.0.1-255.255.255.254 generates 62 address/masks.


If the address ranges are being extracted from <a href="https://www.gnu.org/software/jwhois/">jwhois</a> listings
(can be two adjacent /20 that aren't /19) the ranges can be run
through this routine and then merged.
See <a href="https://github.com/pellucida/merge_nets">merge_nets</a> which include this routine. 
This works quite well where different ISPs in one locality have
obtained adjacent allocations and for your purpose the two ISPs
are equivalent.


### SEE ALSO
Iprange from http://www.cs.colostate.edu/~somlo/iprange.c and code forked
from it appear to merge subnets as well.  

### LICENSE
Creative Commons CC0
<a href="http://creativecommons.org/publicdomain/zero/1.0/legalcode">
http://creativecommons.org/publicdomain/zero/1.0/legalcode</a>


### AUTHOR
<a href="mailto:toves@sdf.lonestar.org">
James Sainsbury</a>

