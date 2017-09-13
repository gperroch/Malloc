-------------1-------------------
--------------2------------------
TINY : 0x10e08b040
BLOC: 0x10e08b040
	size_total	0
	next		0x10e08b080
	prev_area	0x10e08b000
	magic_number	810c
	free		0
	size_data	128
0x10e08b080 - 0x10e08b080 : 0 octets
BLOC: 0x10e08b080
	size_total	32
	next		0x10e08b0e0
	prev_area	0x10e08b000
	magic_number	810c
	free		0
	size_data	128
0x10e08b0c0 - 0x10e08b0e0 : 32 octets
BLOC: 0x10e08b0e0
	size_total	2
	next		0x10e08b122
	prev_area	0x10e08b000
	magic_number	810c
	free		0
	size_data	128
0x10e08b120 - 0x10e08b122 : 2 octets
BLOC: 0x10e08b122
	size_total	10240
	next		0x10e08d962
	prev_area	0x10e08b000
	magic_number	810c
	free		0
	size_data	20190
0x10e08b162 - 0x10e08d962 : 10240 octets
BLOC: 0x10e08d962							<=== PREMIER BLOC
	size_total	1
	next		0x10e08d9a3
	prev_area	0x10e08b000
	magic_number	810c
	free		0
	size_data	9886
0x10e08d9a2 - 0x10e08d9a3 : 1 octets
BLOC: 0x10e08d9a3
	size_total	1
	next		0x10e08d9e4
	prev_area	0x10e08b000
	magic_number	810c
	free		0
	size_data	128
0x10e08d9e3 - 0x10e08d9e4 : 1 octets
BLOC: 0x10e08d9e4
	size_total	1
	next		0x10e08da25
	prev_area	0x10e08b000
	magic_number	810c
	free		0
	size_data	128
0x10e08da24 - 0x10e08da25 : 1 octets

---------------3-----------------
BLOC: 0x10e08b122
	size_total	10240
	next		0x10e08d962
	prev_area	0x10e08b000
	magic_number	810c
	free		0
	size_data	20190
0x10e08b162 - 0x10e08d962 : 10240 octets
BLOC: 0x10e08d962	--------------------<=== PREMIER BLOC
	size_total	1
	next		0x10e08d9a3
	prev_area	0x10e08b000
	magic_number	810c
	free		1
	size_data	9886
BLOC: 0x10e08d9a3  ---------------------<= Ce bloc est reinitialise. Par quoi ?
	size_total	0
	next		0x0
	prev_area	0x10e08b000
	magic_number	810c
	free		1
	size_data	128
LARGE : 0x119c3e040
BLOC: 0x119c3e040
	size_total	2147483647
	next		0x0
	prev_area	0x119c3e000
	magic_number	810c
	free		0
	size_data	2147483647
0x119c3e080 - 0x199c3e07f : 2147483647 octets
