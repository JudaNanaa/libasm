; -----------------------------------------------------------------------------
; A 64-bit function that compare the two strings in parameter.  The function has signature:
;
;   int64_t ft_strcmp(int64_t dst, int64_t src)
;
; Note that the parameters have already been passed in rdi.  We
; just have to return the value in rax.
; -----------------------------------------------------------------------------

section .text
    global ft_strcmp

ft_strcmp:
	mov rcx, 0

.loop:
	mov al, [rdi + rcx]
	mov dl, [rsi + rcx]
	
	cmp al, 0
	je .end
	cmp dl, 0
	je .end
	
	cmp al, dl
	jne .end
	inc rcx
	jmp .loop

.end:
	mov rax, [rdi]
	sub rax, [rsi]
	cmp rax, 0
	jne .less 
	ret
	
.less:
	cmp rax, 0
	jg .greater
	mov rax, -1
	ret

.greater:
	mov rax, 1
	ret