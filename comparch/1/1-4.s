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

	.text
main:	la	$8, A		# A+N
	la	$9, A		# A
	# Calculate the address of the last element of A and set it as $8.
	lw	$10, N
lp1:	beq	$10, $0, lp2
	addi	$8, $8, 4
	addi	$10, $10, -1
	# Outer loop.
	j	lp1
lp2:	addi	$9, $9, 4
	beq	$9, $8, exit
	# Inner loop.
	move	$10, $8		# j
lp3:	beq	$10, $9, lp2
	addi	$10, $10, -4
	lw	$11, 0($10)	# A[j]
	lw	$12, -4($10)	# A[j-1]
	# If A[j] >= A[j-1], swap them.
	slt	$13, $11, $12
	beq	$13, $0, lp3
	sw	$11, -4($10)
	sw	$12, 0($10)
	j	lp3
exit:
