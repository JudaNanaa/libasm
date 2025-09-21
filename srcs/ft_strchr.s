
section .text
    global ft_strchr

; char *ft_strchr(const char *s, int c);

ft_strchr:
    push rbp
    mov rbp, rsp

.loop1:
    mov al, byte [rdi]     ; charger le caractère courant dans al
    cmp al, sil            ; comparer avec c (en 8 bits)
    je .found              ; si égal → trouvé
    test al, al            ; est-ce le '\0' ?
    je .not_found          ; fin de chaîne → pas trouvé
    inc rdi
    jmp .loop1

.found:
    mov rax, rdi           ; renvoyer le pointeur
    jmp .done

.not_found:
    mov rax, 0             ; renvoyer NULL
    jmp .done

.done:
	pop rbp
    ret
