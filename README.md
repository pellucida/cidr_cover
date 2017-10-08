# cidr_cover start end

<p>
Create minimal address/mask set to cover a given range of IPv4 addresses
</p>
<p>Example</p>
<pre>
10.1.2.1 - 10.1.2.7 &rarr;
	10.1.2.1/32 = 10.1.2.1
	10.1.2.2/31 = 10.1.2.2 - 10.1.2.3
	10.1.2.4/30 = 10.1.2.4 - 10.1.3.7
</pre>
<p>
The executable is a thin wrapper around the routine that
calculates the sequence off addresses and masks.
Getting the code right can be a bit tricky especially
for the edge cases.
</p>
<pre>
$ ./cidr_cover 10.1.2.1 10.1.2.7
10.1.2.1/32
10.1.2.2/31
10.1.2.4/30
</pre>
<p>
The range 0.0.0.1 to 255.255.255.254 generates 62 address/masks.
</p>
<p>
If the address ranges are being extracted from jwhois listings
can be two adjacent /20 that aren't /19) the ranges can be run
through this routine then merged with
<a href="https://github.com/pellucida/subnet_merge">subnet_merge</a>.
This works quite well where different ISPs in one locality have
obtained adjacent allocations and for your purpose the two ISPs
are equivalent.
</p>

### LICENSE
Creative Commons CC0
<a href="http://creativecommons.org/publicdomain/zero/1.0/legalcode">
http://creativecommons.org/publicdomain/zero/1.0/legalcode</a>


### AUTHOR
<a href="mailto:toves@sdf.lonestar.org">
James Sainsbury</a>

