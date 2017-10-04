<pre>
<b>a</b> is the starting address
<b>N</b> is the number of bits (32)
<b>M[i]</b> is the i'th mask
and <b>A[i]/M[i]</b>, i=1.. are the address/mask pairs
calculated from the start address and successive masks
ie 
A[1]	= a
A[i+1]	= A[i] + 2^(N-M[i])...
A[last]	= b 


<b>cidr_cover</b> (in a,b:Nat,  out M:list of Nat): 

	<b>{Pre: a &le; b }</b>
	m	&larr; N
	n	&larr; 0

	do a &ne; b+1 -->
	<b>{INV: a &le; b+1 }</b>
		if n &equals; m &rarr;
	<b>{ a & (2<sup>n</sup> - 1) = 0 }</b>
			do a & 2<sup>(n-1)</sup> - 1 = 0 -->
				n &larr; n - 1
				<b>{INV: a & 2<sup>n</sup> - 1 &equals; 0}</b>
			od
	<b>{~G: a & 2^(n-1) -1 &ne;0, INV: a & 2^n - 1 &equals; 0 }</b>

		[] n &ne; m &rarr;
			do a & 2^n - 1 &ne; 0 -->
				n &larr; n + 1
				<b>{INV: a & 2^(n-1) - 1 &ne; 0}</b>
			do
	<b>{~G: a & 2^n - 1 &equals; 0, INV: a & 2^(n-1) - 1 &ne; 0 }</b>
		fi

	<b>{   n &equals; m  &rArr; ~G: a & 2^(n-1) - 1 &ne;0, INV: a & 2^n - 1 = 0 </b>
	<b>or n&ne;m &rArr; ~G: a & 2^n - 1 &equals; 0, INV: a & 2^(n-1) - 1 &ne; 0 </b>
	<b>&rArr;   a & 2^n - 1 &equals; 0 and a & 2^(n-1) - 1 &ne;0 (n maximal) }</b>
		m	&larr; n
		do a + 2^(N-n) > b+1 &rarr;
			n	&larr; n + 1
			<b>{INV: a + 2<sup>N-(n-1)</sup> > b+1 }</b>
		od
	{~G: a + 2^(N-n)  <= b+1, INV: a + 2^N-(n-1) > b+1 (n maximal)}
		M &larr; M :: n		// Append n to list
		<b>{a + 2^(N-n) <= b+1}</b>
		a	&larr; a + 2^(N-n)
		<b>{ a <= b+1 }</b>
	od
	<b>{~G: a = b+1; INV: a <= b+1 }</b>
end
</pre>
