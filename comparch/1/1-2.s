	.data
N:	.word 10
A:	.word 5
	.word 3
	.word 12
	.word 7
	.word 23
	.word 1
	.word 23
	.word 43
	.word 54
	.word 31
S:	.word 0

	.text
main:
	lw	$8, N		# Counter
	la	$9, A		# Index
	move	$10, $0		# Sum
lp:	beq	$8, $0, lpend
	lw	$11, 0($9)
	add	$10, $10, $11
	addi	$8, $8, -1
	addi	$9, $9, 4
	j	lp
lpend:	sw	$10, S
