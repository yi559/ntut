.data
    x: .space 400
    n: .word 0

.text
main:
    la $s0, x                   # $s0 = &x
    li $t0, 1
    sw $t0, 0($s0)              # x[0] = 1

    li $s1, 1
    li $t1, 100
for:
    slt $t0, $s1, $t1
    beq $t0, $zero, exit
    sll $t0, $s1, 2
    add $t0, $s0, $t0
    sw $zero, 0($t0)            # x[i] = 0
    addi $s1, $s1, 1
    j for

exit:
    li $v0, 5
    syscall
    sw $v0, n

    move $a0, $v0
    la $a1, x
    jal fib

    lw $a0, n
    la $a1, x
    jal print

    li $v0, 10
    syscall

fib:
    addi $sp, $sp, -16
    sw $ra, 8($sp)
    sw $a0, 4($sp)
    sw $a1, 0($sp)

    li $t1, 2
    slt $t2, $a0, $t1
    beq $t2, $zero ,else

    li $t0, 1
    sll $t2, $a0, 2
    add $t2, $a1, $t2
    sw $t0, 0($t2)              # x[n] = 1
    move $v0, $t0               # return 1

    lw $a1, 0($sp)
    lw $a0, 4($sp)
    lw $ra, 8($sp)
    addi $sp, $sp, 16

    jr $ra
else:
    addi $a0, $a0, -1
    jal fib
    sw $v0, 12($sp)

    lw $a1, 0($sp)
    lw $a0, 4($sp)
    addi $a0, $a0, -2
    jal fib

    lw $t1, 12($sp)
    add $t0, $t1, $v0

    lw $a1, 0($sp)
    lw $a0, 4($sp)
    sll $t2, $a0, 2
    add $t2, $a1, $t2
    sw $t0, 0($t2)
    
    move $v0, $t0

    lw $ra, 8($sp)
    addi $sp, $sp, 16

    jr $ra

print:
    move $t0, $a0
    li $t1, 0
pfor:
    slt $t2, $t1, $t0
    beq $t2, $zero, pexit
    
    sll $t2, $t1, 2
    add $t2, $a1, $t2
    lw $a0, 0($t2)
    li $v0, 1
    syscall
    
    li $a0, 44
    li $v0, 11
    syscall

    addi $t1, $t1, 1
    j pfor

pexit:
    jr $ra