
section .data
SPACES db 9,10,11,12,13,32


section .text
    global ft_atoi_base
    extern ft_strlen
    extern ft_strchr

; int ft_atoi_base(const char *str, const char *base)

check_duplicate:
	mov rcx, 0 ; index i
.loop1:
	cmp byte [rdi + rcx], 0x0 ; es ce que je suis arrive a la fin de la chaine a check
	je .no_duplicate ; si c'est bon pas de duplicate
	mov r8, rcx ; index j = i
	inc r8 ; j++
	mov dl, [rdi + rcx] ; 
.loop2:
	cmp byte [rdi + r8], 0x0
	je .increment
	cmp byte [rdi + r8], dl
	je .duplicate
	inc r8
	jmp .loop2
.increment:
	inc rcx
	jmp .loop1

.no_duplicate:
	mov rax, 1
	jmp .done
	
.duplicate:
	mov rax, 0
	jmp .done

.done:
	ret

index_in_base:
	push rbp
	mov rbp, rsp
	mov rax, 0

.loop:
	cmp byte [rdi + rax], sil
	je .done
	cmp byte [rdi + rax], 0
	je .not_found
	inc rax
	jmp .loop


.not_found:
	mov rax, -1
	jmp .done

.done:
	pop rbp
	ret

check_sign:
.loop:
	cmp byte [rdi], 0
	je .success
	cmp byte [rdi], '+'
	je .error
	cmp byte [rdi], '-'
	je .error
	inc rdi
	jmp .loop

.success:
	mov rax, 1
	jmp .done

.error: 
	mov rax, 0
	jmp .done

.done:
	ret

check_whitespace:
    push rbp
    mov rbp, rsp
	push r12
	
	mov r12, rdi
.loop:
	cmp byte [r12], 0
	je .success
	mov rsi, r12
	mov rdi, SPACES
	call ft_strchr
	cmp rax, 0x0
	jne .error
	inc r12
	jmp .loop

.success:
	mov rax, 1
	jmp .done

.error:
	mov rax, 0
	jmp .done

.done:
	pop r12
	pop rbp
	ret

ft_atoi_base:
    push rbp
    mov rbp, rsp
	push r12
	push r13
	push r14
	push r15

    ; === Vérif arguments ===
    cmp rdi, 0
    je .error
    cmp rsi, 0
    je .error

    ; rdi = str, rsi = base
    mov r12, rdi              ; sauver str
    mov r13, rsi              ; sauver base

    ; === check base valide ===
    mov rdi, rsi              ; arg pour ft_strlen(base)
    call ft_strlen
    cmp rax, 2                ; len(base) < 2 ?
    jl .error
    mov r14, rax              ; base_len

	mov rdi, r13
	call check_duplicate
	cmp rax, 0
	je .error
	
	mov rdi, r13
	call check_sign
	cmp rax, 0
	je .error

	mov rdi, r13
	call check_whitespace
	cmp rax, 0
	je .error

    ; === skip spaces ===
.skip_spaces:
    mov al, byte [r12]        ; *str
    cmp al, 0
    je .done                  ; fin de str
    cmp al, ' '					; sur un espace
    je .inc_str
    cmp al, 9
    jb .check_sign
    cmp al, 13
    jbe .inc_str
    jmp .check_sign

.inc_str:
    inc r12
    jmp .skip_spaces

    ; === gérer signes ===
.check_sign:
    mov r15, 1                ; sign = 1
.sign_loop:
    mov al, byte [r12]
    cmp al, '+'
    je .plus
    cmp al, '-'
    je .minus
    jmp .parse_digits

.plus:
    inc r12
    jmp .sign_loop

.minus:
    neg r15
    inc r12
    jmp .sign_loop

    ; === parsing des chiffres ===
.parse_digits:
    xor rbx, rbx              ; result = 0

.loop:
	cmp byte [r12], 0x0
	je .end_digits
    mov rdi, r13              ; base
    mov sil, byte [r12]       ; caractère courant dans sil
    call index_in_base        ; rax = index ou -1
    cmp rax, -1
    je .end_digits

    ; result = result * base_len + rax
    imul rbx, r14
    add rbx, rax

    inc r12
    jmp .loop

.end_digits:
    mov rax, rbx
    imul rax, r15             ; appliquer signe
    jmp .done

.error:
    xor rax, rax

.done:
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbp
    ret
