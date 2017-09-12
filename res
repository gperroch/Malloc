	test_malloc 1.
	test_malloc 2.
	test_malloc 3.
	test_malloc 4.
	test_malloc 5.
test_malloc         : SUCCESS (0)
	test_malloc_free 1.
	test_malloc_free 2.
test_malloc_free    : SUCCESS (0)
	test_malloc_realloc 1.
	test_malloc_realloc 2.
	test_malloc_realloc 3.
test_malloc_realloc : SUCCESS (0)
	test_malloc_free_realloc 1.
error for object 0x103852962: pointer being realloc'd was not allocated.
test_malloc_free_realloc: SUCCESS (0)
	test_realloc 1.
	test_realloc 2.
	test_realloc 3.
test_realloc        : SUCCESS (0)
	test_realloc_free 1.
	test_realloc_free 2.
	test_realloc_free 3.
test_realloc_free   : SUCCESS (0)
LARGE : 0x103850038
0x103850070 - 0x103850070 : 0 octets
0x1038500a8 - 0x1038500c8 : 32 octets
0x103850100 - 0x103850102 : 2 octets
0x10385013a - 0x10385292a : 10224 octets
0x103852962 - 0x103852962 : 0 octets
0x10385299a - 0x1038529a4 : 10 octets
0x1038529dc - 0x1038529dc : 0 octets
0x103852a14 - 0x103852a15 : 1 octets
0x103852a4d - 0x103852a4d : 0 octets
LARGE : 0x103855038
0x103855070 - 0x103876051 : 135137 octets
