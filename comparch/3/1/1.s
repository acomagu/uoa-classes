	.data
A:	.word 0, 0, 0, 1
	.word 0, 2, 0, 0
	.word 0, 0, 3, 0
	.word 4, 0, 0, 0
B:	.word 0, 1, 2, 3
	.word 4, 5, 6, 7
	.word 8, 9, 10, 11
	.word 12, 13, 14, 15
C:	.space 64

	.text
mul:	or	$2, $0, $0	# ans
	ori	$8, $0, 1	# mask
	ori	$10, $0, 32	# i
mullp:	beq	$10, $0, mulext
	and	$9, $5, $8
	beq	$9, $0, mula
	addu	$2, $2, $4
mula:	addu	$8, $8, $8
	addu	$4, $4, $4
	add	$10, $10, -1
	j	mullp
mulext:	jr	$31		# ret

main:	la	$16, A		# i
	addi	$16, $16, 48	# 12( * 4)
lp1:	ori	$17, 12		# j = 3( * 4)
	la	$18, B		# jj
	addi	$18, $18, 48	# 12( * 4)
lp2:	add	$19, $15, $17	# tmp = i + j
	lw	$19, 0($19)	# aa = a[tmp]
	ori	$20, 12		# k = 3( * 4)
lp3:	addi	$21, $16, 128	# Calc the addr of c[0]
	add	$21, $21, $20	# tmp = i + k
	lw	$22, 0($21)	# tmp2 = c[tmp]
	add	$4, $18, $20	# tmp3 = jj + k
	lw	$4, 0($4)	# tmp3 = b[tmp3]
	move	$5, $19		# tmp4 = aa
	jal	mul		# tmp5 = tmp4 * tmp3
	add	$22, $22, $2	# tmp2 *= tmp5
	sw	$22, 0($21)	# c[tmp] = tmp2
	beq	$20, $0, lp3x	# if(k == 0) break
	addi	$20, $20, -4	# k--
	j	lp3		# continue
lp3x:	beq	$17, $0, lp2x	# if(j == 0) break
	addi	$17, $17, -4	# j--
	addi	$18, $18, -16	# j -= 4
	j	lp2		# continue
lp2x:	beq	$16, $0, exit	# if(i == 0) break
	addi	$16, $16, -16	# i -= 4
	j lp1
exit:
