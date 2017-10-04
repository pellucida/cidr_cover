# cidr_cover start end

Create minimal address/mask set to cover a range of IPv4 addresses

Example: 10.1.2.1 - 10.1.2.7
=>
	10.1.2.1/32 = 10.1.2.1
	10.1.2.2/31 = 10.1.2.2 - 10.1.2.3
	10.1.2.4/30 = 10.1.2.4 - 10.1.3.7
