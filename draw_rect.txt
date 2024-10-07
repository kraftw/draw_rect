# draws a rectangle with the given dimensions
# as well as decorates it with the given border and filling

	# init values for rect
	.data
		height: 	.word 4
		width:		.word 4
		border:		.byte '@'
		fill:		.byte '*'
	
	.text
	.globl main
	
main:

	# load width and height into temps
	lw $t0, height		# load height into $t0
	lw $t1, width		# load width into $t1
	
	# subtract 1 from each dim
	addi $t0, $t0, -1			# subtract 1 from each
	addi $t1, $t1, -1			# (this is done for proper indexing)

	# load dim into saved regestries
	la $s0, border		# border -> $s0	(1st saved reg)
	la $s1, fill		# fill	 -> $s1	(2nd saved reg)
	
	
	jal draw_rect		# call the draw_rect function


	li $v0, 10			# exit the program
	syscall
	
	
draw_rect:

	# KEY:
	# $t0 = height-1,	$s0 = border
	# $t1 = width-1,	$s1 = fill
	# $t2 = y
	# $t3 = x
	
	li $t2, 0			# init row loop iterator, y = 0 (outer loop)
	

# -OUTER LOOP START-
row_loop_start:

	bgt $t2, $t0, row_loop_end			# if y > height-1, exit row loop
	
	li $t3, 0			# init column loop iterator, x = 0 (inner loop)

# -INNER LOOP START-
col_loop_start:

	bgt $t3, $t1, col_loop_end			# if x > width-1, exit column loop
	
	beq $t2, 0, top_bot_row				# if y = 0, branch to top_bot_row
	beq $t2, $t0, top_bot_row			# OR y = height-1, branch to top_bot_row
	
	beq $t3, 0, first_last_col			# else if x = 0, branch to first_last_col
	beq $t3, $t1, first_last_col		# OR x = width-1, branch to first_last_col
	
# -DRAWING BRANCHES-
	
#	NNNN
#	NYYN
#	NYYN
#	NNNN
	
fill_rect:

	li $v0, 11			# syscall code for print char
	lb $a0, 0($s1)		# load fill char into arg reg
	syscall
	
	addi $t3, $t3, 1	# x++
	j col_loop_start	# jump back to column loop start (inner loop)
	
	
#	YYYY
#	NNNN
#	NNNN
#	YYYY
	
top_bot_row:

	li $v0, 11			# syscall code for print char
	lb $a0, 0($s0)		# load border char into arg reg
	syscall

	addi $t3, $t3, 1	# x++
	j col_loop_start	# jump back to column loop start (inner loop)
	
	
#	YNNY
#	YNNY
#	YNNY
#	YNNY

first_last_col:

	li $v0, 11			# syscall code for print char
	lb $a0, 0($s0)		# load border char into arg reg
	syscall

	addi $t3, $t3, 1	# x++
	j col_loop_start	# jump back to column loop start (inner loop)



# -INNER LOOP END-
col_loop_end:

	li $v0, 11			# syscall code for print char
	li $a0, 10			# newline ACSII code
	syscall
	
	addi $t2, $t2, 1	# y++
	j row_loop_start	# jump back to row loop start (outer loop)
	

# -OUTER LOOP END-
row_loop_end:

	jr $ra				# return
