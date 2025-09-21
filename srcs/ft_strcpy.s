; -----------------------------------------------------------------------------
; A 64-bit function that copy the src string to the dst string and return dst.  The function has signature:
;
;   int64_t ft_strcpy(int64_t dst, int64_t src)
;
; Note that the parameters have already been passed in rdi.  We
; just have to return the value in rax.
; -----------------------------------------------------------------------------

section .text
    global ft_strcpy

ft_strcpy:
    mov rax, rdi        ; sauvegarder dest pour retour
	mov rcx, 0

.loop:
    mov dl, [rsi + rcx]       ; charger octet source
    mov [rdi + rcx], dl       ; écrire octet dans dest
    inc rcx
    cmp dl, 0         ; était-ce un 0 ?
    jne .loop

    ret
