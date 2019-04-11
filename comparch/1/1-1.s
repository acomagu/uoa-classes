	.data
A:	.word 23
B:	.word 62
C:	.word 10
S:	.word 0

	.text
main:	lw	$8, A
	lw	$9, B
	add	$8, $8, $9
	lw	$9, C
	sub	$8, $8, $9
	ori	$8, 3
	sw	$8, S
