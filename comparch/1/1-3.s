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
B:	.space 40

	.text
main:	lw	$8, N		# Count
	la	$9, A		# Index for A
	la	$10, B		# Index for B
lp:	beq	$8, $0, exit
	lw	$11, 0($9)
	sw	$11, 0($10)
	addi	$8, $8, -1
	addi	$9, $9, 4
	addi	$10, $10, 4
	j	lp
exit:
