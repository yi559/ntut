.data
    array: .space 24

.text
main:
    li $t0, 0                   #i
    li $t1, 6
    la $s0, array               #array[]
for:
    slt $t2, $t0, $t1
    beq $t2, $zero, exit
    
    li $v0, 5                   #scanf("%d", &array[i]);
    syscall

    sll $t2, $t0, 2
    add $t2, $s0, $t2
    sw $v0, 0($t2)

    addi $t0, $t0, 1            #i++
    j for

exit:
    la $a0, array
    li $a1, 6
    jal selectionSort

    li $t0, 0           #i
    li $t1, 6

sfor:
    slt $t2, $t0, $t1
    beq $t2, $zero, sexit

    sll $t2, $t0, 2
    add $t2, $s0, $t2
    lw $a0, 0($t2)      #array[i]
    li $v0, 1
    syscall

    li $a0, 10
    li $v0, 11
    syscall
    
    addi $t0, $t0, 1
    j sfor

sexit:
    li $v0, 10
    syscall

selectionSort:
    addi $sp, $sp, -4
    sw $s0, 0($sp)

    li $t0, 0           #i
ifor:
    add $t2, $a1, -1    #n-1
    slt $t2, $t0, $t2
    beq $t2, $zero, iexit
    move $s0, $t0       #min_idx = i

    addi $t1, $t0, 1    #j = i+1
jfor:
    slt $t3, $t1, $a1
    beq $t3, $zero, jexit

    sll $t3, $t1, 2
    add $t3, $a0, $t3
    lw $t3, 0($t3)      #array[j]

    sll $t4, $s0, 2
    add $t4, $a0, $t4
    lw $t4, 0($t4)      #array[min_idx]

    slt $t5, $t3, $t4
    beq $t5, $zero, skip
    move $s0, $t1

skip:
    addi $t1, $t1, 1
    j jfor

jexit:
    sll $t6, $t0, 2
    add $t6, $a0, $t6
    lw  $t4, 0($t6)    #array[i]

    sll $t7, $s0, 2
    add $t7, $a0, $t7
    lw  $t5, 0($t7)    #array[min_idx]

    sw  $t5, 0($t6)
    sw  $t4, 0($t7)

    addi $t0, $t0, 1
    j ifor

iexit:
    lw $s0, 0($sp)
    addi $sp, $sp, 4

    jr $ra