	.text
	.globl	test_and_set

/**
 * test_and_set: assume it's called with test_and_set(&lock);
 * @param lock pointer to a mutex_t variable
 *
 * TODO - add a comment each line describing its action
 */
test_and_set:
	cli
	pushl	%ebx		# preserve contents of the %ebx register, which is about to be modified
	movl	8(%esp), %ebx	# place value at %ebx register into second byte of stack pointer
	movl	$1, %eax	# move contents of %eax register to temporary register $1
	xchg	%eax, (%ebx)	# Swap contents of %eax and %ebx registers (set part
	popl	%ebx		# pop off stack and place in %ebx register		of test and set)
	sti
	ret			# returns if lock was locked or not before test after renabling interrupts
