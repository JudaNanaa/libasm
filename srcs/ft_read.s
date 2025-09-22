; -----------------------------------------------------------------------------
; A 64-bit function that copy the src string to the dst string and return dst.  The function has signature:
;
;   int64_t ft_strcpy(int64_t dst, int64_t src)
;
; Note that the parameters have already been passed in rdi.  We
; just have to return the value in rax.
; -----------------------------------------------------------------------------

section .text
    global ft_read
    extern __errno_location

ft_read:
	push rbp
	mov rbp, rsp

	mov rax, 0
	syscall

    cmp rax, 0
    jge .done           ; si rax >= 0 => pas d'erreur, return

    ; en cas d'erreur
    mov rcx, rax        ; sauvegarder rax (valeur négative)
    neg rcx             ; rcx = code d'erreur positif
    mov edi, ecx        ; mettre l’erreur dans edi (arg pour plus tard)

    call __errno_location wrt ..plt
    mov [rax], edi      ; *errno = code erreur (32 bits)

    mov rax, -1         ; valeur de retour standard en cas d’erreur
.done:
	mov rsp, rbp
	pop rbp
    ret
