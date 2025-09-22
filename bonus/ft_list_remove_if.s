struc s_list 
	.data resq 1 ; 
	.next resq 1
endstruc

section .text
	global ft_list_remove_if
	extern free

; void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(void *, void *), void (*free_fct)(void *));

ft_list_remove_if:
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	push r13
	push r14
	push r15

	cmp rdi, 0 ; check 1st arg
	je .done

	cmp rdx, 0 ; check 3rd arg
	je .done

	cmp rcx, 0  ; check 4th arg
	je .done 

	mov rbx, [rdi] ; rbx contient la tete de list
	mov r12, rsi ; r12 contient le data_ref
	mov r13, rdx ; r13 contient le pointeur de fonction cmp
	mov r14, rcx ; r14 contient le pointeur de fonction free
	mov r15, 0 ; r15 contient le pointeur du prev de rbx
.loop:
	cmp rbx, 0
	je .done
	
	push rdi
	mov rdi, [rbx + s_list.data]
	mov rsi, r12
	call r13
	pop rdi
	cmp eax, 0
	je .remove
	jmp .increment 

.remove:
	push rdi

	mov rdi, [rbx + s_list.data]
	call r14
	pop rdi
	
	cmp r15, 0
	jne .free
	mov rax, [rbx + s_list.next]
	mov [rdi], rax
	push rdi
	mov rdi, rbx
	mov rbx, [rbx + s_list.next]
	call free wrt ..plt
	pop rdi
	jmp .loop

.free:
	mov rax, [rbx + s_list.next]
	mov [r15 + s_list.next], rax
	push rdi
	mov rdi, rbx
	mov rbx, [rbx + s_list.next]
	call free wrt ..plt
	pop rdi
	jmp .loop


.increment:
	mov r15, rbx
	mov rbx, [rbx + s_list.next]
	jmp .loop

.done:
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	mov rsp, rbp
	pop rbp
	ret