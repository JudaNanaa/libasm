; -----------------------------------------------------------------------------
; A 64-bit function that copy the src string to the dst string and return dst.  The function has signature:
;
;   int64_t ft_strcpy(int64_t dst, int64_t src)
;
; Note that the parameters have already been passed in rdi.  We
; just have to return the value in rax.
; -----------------------------------------------------------------------------

section .text
	extern malloc
    global ft_strdup
	extern ft_strlen 
	extern ft_strcpy

ft_strdup:
	call ft_strlen
	push rdi
	inc rax
	mov rdi, rax
	call malloc  wrt ..plt
	cmp rax, 0x0
	je .done
	mov rdi, rax
	pop rsi
	call ft_strcpy

.done:
	ret
