	.global _print
	.align 2

; Write string to Stdout
;   X0 msg &str ; Message to print
;   X1 len uint ; Number of characters in msg
_print:
	mov X2, X1  ; Shift length into X2
	mov X1, X0  ; Shift string addr into X1
	mov X0, #1  ; Use stdout (1)

	mov X16, #4 ; System Call for Write
	svc 0       ; Signal system to run system call

	br lr       ; Branch-Return to linked register
