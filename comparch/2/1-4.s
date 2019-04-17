	.text
main:	ori	$4, $0, 23
	ori	$5, $0, 4
	or	$2, $0, $0	# ans
	ori	$8, $0, 1	# mask
	ori	$10, $0, 32	# i
loop:	beq	$10, $0, exit
	and	$9, $5, $8
	beq	$9, $0, a
	addu	$2, $2, $4
a:	addu	$8, $8, $8
	addu	$4, $4, $4
	add	$10, $10, -1
	j	loop
exit:
