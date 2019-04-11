# Report 1

## 1-1

Source:

```
        .data
A:      .word 23
B:      .word 62
C:      .word 10
S:      .word 0

        .text
main:   lw      $8, A
        lw      $9, B
        add     $8, $8, $9
        lw      $9, C
        sub     $8, $8, $9
        ori     $8, 3
        sw      $8, S
```

`$8`にA、`$9`にBとCをロードし加算します。

Result: 75

## 1-2

Source:

```
        .data
N:      .word 10
A:      .word 5
        .word 3
        .word 12
        .word 7
        .word 23
        .word 1
        .word 23
        .word 43
        .word 54
        .word 31
S:      .word 0

        .text
main:
        lw      $8, N           # Counter
        la      $9, A           # Index
        move    $10, $0         # Sum
lp:     beq     $8, $0, lpend
        lw      $11, 0($9)
        add     $10, $10, $11
        addi    $8, $8, -1
        addi    $9, $9, 4
        j       lp
lpend:  sw      $10, S
```

`$8`は1ずつ減らし、0になったときにループを終了します。`$9`は4ずつ増やし、配列の要素の参照に利用します。`$10`にひとつずつ加算し、ループが終了した時点での`$10`を`S`に入れます。

Result: 202

## 1-3

Source:

```
        .data
N:      .word 10
A:      .word 5
        .word 3
        .word 12
        .word 7
        .word 23
        .word 1
        .word 23
        .word 43
        .word 54
        .word 31
B:      .space 40

        .text
main:   lw      $8, N           # Count
        la      $9, A           # Index for A
        la      $10, B          # Index for B
lp:     beq     $8, $0, exit
        lw      $11, 0($9)
        sw      $11, 0($10)
        addi    $8, $8, -1
        addi    $9, $9, 4
        addi    $10, $10, 4
        j       lp
exit:
```

`$8`は1ずつ減らし、0になった時点でループを終了します。`$9`と`$10`は4ずつ増やし、それぞれAとBの要素の参照に利用します。N回`B[$10] <- A[$9]`を実行することでコピーをします。

Result:

![](https://i.imgur.com/bV82niC.png)

## 1-4

Source:

擬似コード参照

```
        .data
N:      .word 10
A:      .word 5
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
main:   la      $8, A
        la      $9, A           # A
        # Calculate the address of the last element of A and set it as $8.
        lw      $10, N
lp1:    beq     $10, $0, lp2
        addi    $8, $8, 4
        addi    $10, $10, -1
        # Outer loop.
        j       lp1
lp2:    addi    $9, $9, 4
        beq     $9, $8, exit
        # Inner loop.
        move    $10, $8         # j
lp3:    beq     $10, $9, lp2
        addi    $10, $10, -4
        lw      $11, 0($10)     # A[j]
        lw      $12, -4($10)    # A[j-1]
        # If A[j] < A[j-1], swap them.
        slt     $13, $11, $12
        beq     $13, $0, lp3
        sw      $11, -4($10)
        sw      $12, 0($10)
        j       lp3
exit:
```

擬似コード:

```
  A := []int{5, 3, 12, 7, 23, 1, 23, 43, 54, 31}
  N := 10

  // At Here in the assembly, calcurate the address of the last element of A.

  i := 0
  for {
    i++

    if i == N {
      break
    }

    j := N
    for {
      if j == i {
        break
      }

      j--

      if A[j] < A[j-1] {
        A[j], A[j-1] = A[j-1], A[j]
      }
    }
  }
  print(A)
```

`$8` => `N-1`
`$9` => `i`
`$10` => `j`

です。アセンブリと擬似コードの違いとして、アセンブリでは初めにAの最後の要素のアドレスを計算し`$8`としています(`N*4($10)`のような指定ができないため)。

Result:

![](https://i.imgur.com/FbnB5LN.png)