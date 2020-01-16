.macro movi reg, val
	lui \reg, %hi(\val)
	ori \reg, \reg, %lo(\val)
.endm

.macro STUB num
	.align 4
	.section .vector_new_\num,"ax",@progbits
	.global __vector_\num
	__vector_\num:
		movi $k0, _isr_primary_install
		lw $k0, \num * 4($k0)
		jr $k0
.endm

.align 4
.global __use_isr_install
__use_isr_install:
STUB 0

.text
.align 4
.global _isr_primary_install
_isr_primary_install:
.word _isr_trampoline

# Interrupts are handled here
.align 4
.set noreorder
.global _isr_trampoline
_isr_trampoline:

	.set noat

	addi $sp,$sp,-72
	sw $ra, 0($sp)
	sw  $1, 4($sp) # $at
	sw  $2, 8($sp) # $v0
	sw  $3,12($sp) # $v1
	sw  $4,16($sp) # $a0
	sw  $5,20($sp) # $a1
	sw  $6,24($sp) # $a2
	sw  $7,28($sp) # $a3
	sw  $8,32($sp) # $t0
	sw  $9,36($sp) # $t1
	sw $10,40($sp) # $t2
	sw $11,44($sp) # $t3
	sw $12,48($sp) # $t4
	sw $13,52($sp) # $t5
	sw $14,56($sp) # $t6
	sw $15,60($sp) # $t7
	sw $24,64($sp) # $t8 
	sw $25,68($sp) # $t9 

	jal user_isr
	nop

	lw $25,68($sp)
	lw $24,64($sp)
	lw $15,60($sp)
	lw $14,56($sp)
	lw $13,52($sp)
	lw $12,48($sp)
	lw $11,44($sp)
	lw $10,40($sp)
	lw  $9,36($sp)
	lw  $8,32($sp)
	lw  $7,28($sp)
	lw  $6,24($sp)
	lw  $5,20($sp)
	lw  $4,16($sp)
	lw  $3,12($sp)
	lw  $2, 8($sp)
	lw  $1, 4($sp)
	lw $ra, 0($sp)
	addi $sp,$sp,72

	.set at

	eret
	nop

# Exceptions are handled here (trap, syscall, etc)
.section .gen_handler,"ax",@progbits
.set noreorder
.ent _gen_exception
_gen_exception:
	mfc0 $k0, $14, 0
	addi $k0, $k0, 4
	mtc0 $k0, $14, 0
	eret
	nop

.end _gen_exception
