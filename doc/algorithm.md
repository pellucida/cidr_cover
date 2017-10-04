
a is the starting address
N is the number of bits (32)
M[i] is the i'th mask
and A[i]/M[i], i=1.. are the address/mask pairs
calculated from the start address and successive masks
ie 
A[1]	= a
A[i+1]	= A[i] + 2^(N-M[i])...
A[last]	= b 

cidr_cover (a,b:Nat,  M:list of Nat): 

	{Pre: a <= b }
	m	= N
	n	= 0

	do a != b+1 -->
	{INV: a <= b+1 }
		if n=m -->
	{ a & (2^n - 1) = 0 }
			do a & 2^(n-1) - 1 = 0 -->
				n <- n - 1
				{INV: a & 2^n - 1 == 0}
			od
	{~G: a & 2^(n-1) -1 !=0, INV: a & 2^n - 1 == 0 }

		[] n != m -->
			do a & 2^n - 1 != 0 -->
				n <- n + 1
				{INV: a & 2^(n-1) - 1 != 0}
			do
	{~G: a & 2^n - 1 == 0, INV: a & 2^(n-1) - 1 != 0 }
		fi

	{   n=m  => ~G: a & 2^(n-1) - 1 !=0, INV: a & 2^n - 1 = 0 
	 or n!=m => ~G: a & 2^n - 1 == 0, INV: a & 2^(n-1) - 1 != 0
	 ==>   a & 2^n - 1 = 0 and a & 2^(n-1) - 1 !=0 (n maximal)
	}
		m	<- n
		do a + 2^(N-n) > b+1 -->
			n	<- n + 1
			{INV: a + 2^N-(n-1) > b+1}
		od
	{~G: a + 2^(N-n)  <= b+1, INV: a + 2^N-(n-1) > b+1 (n maximal)}
		M <- M :: n		// Append n to list
		{a + 2^(N-n) <= b+1}
		a	<- a + 2^(N-n)
		{ a <= b+1 }
	od
	{~G: a = b+1; INV: a <= b+1 }
end
