.data
    A: .space 36
    #A[0][0]  A[0][1]  A[0][2]
    #A[1][0]  A[1][1]  A[1][2]
    #A[2][0]  A[2][1]  A[2][2]

    # 0(A)     4(A)     8(A)
    #12(A)    16(A)    20(A) 
    #24(A)    28(A)    32(A)
    transposeOFA1: .space 36
    transposeOFA2: .space 36

.text
main:
    la $s0, A                   # $s0 = *ptrA = &A[0][0]
    la $s1, transposeOFA2       # $s1 = *ptrTA2 = &transposeOfA2[0][0]

    la $a0, A
    jal inputMartrix            # inputMatrix(A);

    la $a1, transposeOFA1
    li $a2, 3
    jal transposeMatrixA1       # transposeMatrixA1(A, transposeOfA1, 3);

    la $a0, A
    move $a0, $s0
    move $a1, $s1
    li $a2, 3
    jal transposeMatrixA2       #transposeMatrixA2(ptrA, ptrTA2, 3);

    la $a0, transposeOFA1
    jal outputMatrix            #outputMatrix(transposeOfA1);

    la $a0, transposeOFA2
    jal outputMatrix            #outputMatrix(transposeOfA2);

    li $v0, 10
    syscall

#-------------------------------------------------------------------------
inputMartrix:
    li $t0, 0       # $t0 = i
    li $t1, 0       # $t1 = j
    li $t2, 3

inputifor:
    slt $t3, $t0, $t2
    beq $t3, $zero, inputiexit

inputjfor:
    slt $t3, $t1, $t2
    beq $t3, $zero, inputjexit

    sll $t3, $t0, 3         # $t3 = i * 8
    sll $t4, $t0, 2         # $t4 = i * 4
    add $t3, $t3, $t4       # $t3 = 8i + 4i = 12i

    sll $t4, $t1, 2         # $t4 = j * 4
    add $t3, $t3, $t4       # $t3 = 12i + 4j
    add $t3, $a0, $t3       # $t3 = A[i][j]

    li $v0, 5
    syscall
    sw $v0, 0($t3)          # scanf("%d", &A[i][j])

    addi $t1, $t1, 1
    j inputjfor

inputjexit:
    addi $t0, $t0, 1
    li $t1, 0
    j inputifor

inputiexit:
    jr $ra

#-------------------------------------------------------------------------
transposeMatrixA1:
    li $t0, 0       # $t0 = i
    li $t1, 0       # $t1 = j
    
transposeA1ifor:
    slt $t2, $t0, $a2
    beq $t2, $zero, transposeA1iexit

transposeA1jfor:
    slt $t2, $t1, $a2
    beq $t2, $zero, transposeA1jexit

    sll $t3, $t0, 3         # $t3 = i * 8
    sll $t4, $t0, 2         # $t4 = i * 4
    add $t3, $t3, $t4       # $t3 = 8i + 4i = 12i

    sll $t4, $t1, 2         # $t4 = j * 4
    add $t3, $t3, $t4       # $t3 = 12i + 4j
    add $t3, $a0, $t3       # $t3 = A[i][j]

    sll $t4, $t1, 3         # $t4 = j * 8
    sll $t5, $t1, 2         # $t5 = j * 4
    add $t4, $t4, $t5       # $t4 = 8j + 4j = 12j

    sll $t5, $t0, 2         # $t5 = i * 4
    add $t4, $t4, $t5       # $t4 = 12i + 4j
    add $t4, $a1, $t4       # $t4 = T[j][i]

    lw $t6, 0($t3)
    sw $t6, 0($t4)

    add $t1, $t1, 1
    j transposeA1jfor

transposeA1jexit:
    addi $t0, $t0, 1
    li $t1, 0
    j transposeA1ifor

transposeA1iexit:
    jr $ra

#-------------------------------------------------------------------------
transposeMatrixA2:      # $a0 = *B      # $a1 = *T      # $a2 = size
    li $t0, 1           # $t0 = i

    mul $t1, $a2, $a2
    sll $t1, $t1, 2
    add $t1, $t1, $a0

    addi $t4, $a2, -1   # $t4 = size-1
    mul $t4, $t4, $a2   # $t4 = size * (size - 1)
    addi $t4, $t4, -1   # $t4 = (size * (size - 1) - 1)
    sll $t4, $t4, 2

transposeA2for:
    slt $t2, $a0, $t1
    beq $t2, $zero, transposeA2exit
    
    lw $t2, 0($a0)
    sw $t2, 0($a1)      # *ptrT = *ptrB;

    slt $t2, $t0, $a2
    beq $t2, $zero, else

    sll $t3, $a2, 2
    add $a1, $a1, $t3   # ptrT += size;

    addi $t0, $t0, 1
    j next

else:     
    sub $a1, $a1, $t4   # ptrT -= (size * (size - 1) - 1);

    li $t0, 1

next:
    addi $a0, $a0, 4
    j transposeA2for

transposeA2exit:
    jr $ra

#-------------------------------------------------------------------------
outputMatrix:
    li $t0, 0       # $t0 = i
    li $t1, 0       # $t1 = j
    li $t2, 3
    
    addi $sp, $sp, -4
    sw $s0, 0($sp)

    move $s0, $a0

outputifor:
    slt $t3, $t0, $t2
    beq $t3, $zero, outputiexit

outputjfor:
    slt $t4, $t1, $t2
    beq $t4, $zero, outputjexit
    
    sll $t5, $t0, 3         # $t5 = i * 8
    sll $t6, $t0, 2         # $t6 = i * 4
    add $t5, $t5, $t6       # $t5 = 8i + 4i = 12i

    sll $t6, $t1, 2         # $t6 = j * 4
    add $t5, $t5, $t6       # $t5 = 12i + 4j
    add $t5, $s0, $t5       # $t5 = A[i][j]

    lw $a0, 0($t5)
    li $v0, 1
    syscall
    
    li $a0, 32
    li $v0, 11
    syscall
    
    addi $t1, $t1, 1
    j outputjfor
    
outputjexit:
    li $a0, 10
    li $v0, 11
    syscall

    addi $t0, $t0, 1
    li $t1, 0
    j outputifor

outputiexit:
    lw $s0, 0($sp)
    addi $sp, $sp, 4

    jr $ra