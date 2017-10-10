<pre>
<b>a</b> is the starting address
<b>N</b> is the number of bits (32)
<b>M<sub>i</sub></b> is the i'th mask
and <b>A<sub>i</sub>/M<sub>i</sub></b>, i=1.. are the address/mask pairs
calculated from the start address and successive masks
ie 
A<sub>1</sub>	= a
A<sub>i+1</sub>	= A<sub>i</sub> + 2<sup>(N-M<sub>i</sub>)</sup>...
A<sub>last</sub>	= b 


<b>cidr_cover</b> (in a,b:Nat,  out M:list of Nat): 

	<b>{Pre: a &le; b }</b>
	m	&larr; N
	n	&larr; 0

	do a &ne; b+1 &rarr;
	<b>{INV: a &le; b+1 }</b>
		if n &equals; m &rarr;
	<b>{ a & (2<sup>n</sup> - 1) &equals; 0 }</b>
			do a & 2<sup>(n-1)</sup> - 1 = 0 &rarr;
				n &larr; n - 1
				<b>{INV: (&forall; i&ge;n) a & 2<sup>n</sup> - 1 &equals; 0}</b>
			od
	<b>{~G: a & 2<sup>(n-1)</sup> -1 &ne;0, INV: a & 2<sup>n</sup> - 1 &equals; 0 }</b>

		[] n &ne; m &rarr;
			do a & 2<sup>n</sup> - 1 &ne; 0 &rarr;
				n &larr; n + 1
				<b>{INV: a & 2<sup>(n-1)</sup> - 1 &ne; 0}</b>
			do
	<b>{~G: a & 2<sup>n</sup> - 1 &equals; 0, INV: a & 2<sup>(n-1)</sup> - 1 &ne; 0 }</b>
		fi

	<b>{   n &equals; m  &rArr; ~G: a & 2<sup>(n-1)</sup> - 1 &ne;0, INV: a & 2<sup>n</sup> - 1 = 0 </b>
	<b>or n&ne;m &rArr; ~G: a & 2<sup>n</sup> - 1 &equals; 0, INV: a & 2<sup>(n-1)</sup> - 1 &ne; 0 </b>
	<b>&rArr;   a & 2<sup>n</sup> - 1 &equals; 0 and a & 2<sup>(n-1)</sup> - 1 &ne;0 (n maximal) }</b>
		m	&larr; n
		do a + 2<sup>(N-n)</sup> > b+1 &rarr;
			n	&larr; n + 1
			<b>{INV: a + 2<sup>N-(n-1)</sup> > b+1 }</b>
		od
	{~G: a + 2<sup>(N-n)</sup>  &le; b+1, INV: a + 2<sup>N-(n-1)</sup> b+1 (n maximal)}
		M &larr; M :: n		// Append n to list
		<b>{a + 2<sup>(N-n)</sup> &le; b+1}</b>
		a	&larr; a + 2<sup>(N-n)</sup>
		<b>{ a &le; b+1 }</b>
	od
	<b>{~G: a &equals; b+1; INV: a &le; b+1 }</b>
end
</pre>
