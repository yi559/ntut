# while (save[i] == k) i++;
# 假設 $s3 = i, $s5 = k, $s6 = save 陣列基底位址
Loop:
    sll  $t1, $s3, 2       # $t1 = i * 4 (byte 偏移量)
    add  $t1, $t1, $s6     # $t1 = save + (i * 4) 位址
    lw   $t0, 0($t1)       # $t0 = save[i]
    
    bne  $t0, $s5, Exit    # 若 save[i] != k 則跳出迴圈
    addi $s3, $s3, 1       # i = i + 1
    j    Loop              # 跳回 Loop
Exit:

#-------------------------------------------------------------------------
#for (int i=0; i<10; i++) sum += i;
# 假設 $t0 = sum, $t1 = i, $t2 = 10
    li   $t0, 0            # sum = 0
    li   $t1, 0            # i = 0
    li   $t2, 10           # limit = 10

ForLoop:
    slt  $t3, $t1, $t2     # 若 i < 10 則 $t3 = 1，否則 0
    beq  $t3, $zero, EndFor # 若 $t3 == 0 (i >= 10) 則結束
    
    add  $t0, $t0, $t1     # sum += i
    addi $t1, $t1, 1       # i++
    j    ForLoop

EndFor:

#-------------------------------------------------------------------------
# int leaf_example(int g, int h, int i, int j) { return (g + h) - (i + j); }
# 引數由 $a0~$a3 傳入，結果存於 $v0
leaf_example:
    add  $t0, $a0, $a1     # $t0 = g + h
    add  $t1, $a2, $a3     # $t1 = i + j
    sub  $v0, $t0, $t1     # $v0 = (g + h) - (i + j)
    
    jr   $ra               # 返回呼叫者

#-------------------------------------------------------------------------
# int fact(int n) { if (n < 1) return 1; else return n * fact(n - 1); }
fact:
    # 1. 配置堆疊空間並儲存暫存器
    addi $sp, $sp, -8      # 騰出 8 Bytes 空間
    sw   $ra, 4($sp)       # 保存返回位址
    sw   $a0, 0($sp)       # 保存當前的 n ($a0)

    # 2. Base Case 檢查
    slti $t0, $a0, 1       # if n < 1 則 $t0 = 1
    beq  $t0, $zero, L1    # if n >= 1 轉至遞迴分支 L1

    # Base Case 回傳 1
    li   $v0, 1            # 回傳值 = 1
    addi $sp, $sp, 8       # 釋放堆疊
    jr   $ra               # 返回上一層

L1: # Recursive Case
    addi $a0, $a0, -1      # n = n - 1
    jal  fact              # 遞迴呼叫 fact(n - 1)

    # 3. 復原暫存器與釋放堆疊
    lw   $a0, 0($sp)       # 還原當前的 n
    lw   $ra, 4($sp)       # 還原當前的 $ra
    addi $sp, $sp, 8       # 釋放堆疊

    # 4. 運算與返回
    mul  $v0, $a0, $v0     # $v0 = n * fact(n - 1)
    jr   $ra               # 返回上一層

#-------------------------------------------------------------------------
# 假設函式需要保護 $ra, $s0, $s1, $s2 (共 4 個 Word = 16 Bytes)
process:
    # --------------------------------------------------
    # 1. 前言 (Prologue): 配置 16 Bytes 堆疊空間並存入暫存器
    # --------------------------------------------------
    addi $sp, $sp, -16     # $sp 指標下移 16 Bytes
    sw   $ra, 12($sp)      # 存入 $ra
    sw   $s2,  8($sp)      # 存入 $s2
    sw   $s1,  4($sp)      # 存入 $s1
    sw   $s0,  0($sp)      # 存入 $s0

    # --------------------------------------------------
    # 2. 函式主體
    # --------------------------------------------------
    addi $s0, $a0, 5       # $s0 = a + 5
    sll  $s1, $a1, 1       # $s1 = b * 2
    
    move $a0, $s0
    move $a1, $s1
    jal  helper            # 呼叫其他函式 (會覆寫 $ra)
    move $s2, $v0

    add  $v0, $s0, $s1
    add  $v0, $v0, $s2     # 計算最終傳回值

    # --------------------------------------------------
    # 3. 結尾 (Epilogue): 還原暫存器並釋放堆疊
    # --------------------------------------------------
    lw   $s0,  0($sp)      # 還原 $s0
    lw   $s1,  4($sp)      # 還原 $s1
    lw   $s2,  8($sp)      # 還原 $s2
    lw   $ra, 12($sp)      # 還原 $ra
    addi $sp, $sp, 16      # 推回 $sp 指標 (釋放 16 Bytes)

    jr   $ra               # 返回原呼叫處