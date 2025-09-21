; -----------------------------------------------------------------------------
; A 64-bit function that returns the len of the string.  The function has signature:
;
;   int32_t ft_strlen(int64_t x)
;
; Note that the parameters have already been passed in rdi.  We
; just have to return the value in rax.
; -----------------------------------------------------------------------------

section .text
    global ft_strlen

ft_strlen: 
    mov rax, 0 ; initialise la valeur de retour qui est aussi l'increment
.loop:
    cmp byte [rdi + rax], 0 ; regarde si debut de string + incr == \0
    je end
    inc rax ; incremente la len
    jmp .loop
end:
    ret