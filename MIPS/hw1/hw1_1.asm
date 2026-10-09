.data
    height: .word 0
    weight: .word 0
    bmi: .word 0
    underweight: .asciiz "underweight\n"
    overweight: .asciiz "overweight\n"
    newline: .asciiz "\n"

.text
main:
loop:
    li $v0, 5
    syscall
    la $t0, height
    sw $v0, 0($t0)

    li $t1, -1
    beq $v0, $t1, exit

    li $v0, 5
    syscall
    la $t1, weight
    sw $v0, 0($t1)

    lw $a0, height
    lw $a1, weight

    jal calculateBMI

    la $t0, bmi
    sw $v0, 0($t0)

    lw $a0, bmi

    jal printResult

    j loop

calculateBMI:
    mul $t0, $a0, $a0
    li $t1, 10000
    mul $t2, $a1, $t1
    div $v0, $t2, $t0
    jr $ra

printResult:
    li $t0, 17
    slt $t1, $a0, $t0
    beq $t1, $zero, elseif

    li $v0, 4
    la $a0, underweight
    syscall
    jr $ra

elseif:
    li $t0, 25
    slt $t1, $t0, $a0
    beq $t1, $zero, else

    li $v0, 4
    la $a0, overweight
    syscall
    jr $ra

else:
    li $v0, 1
    syscall
    
    li  $v0, 4
    la  $a0, newline
    syscall
    jr $ra

exit:
    li $v0, 10
    syscall