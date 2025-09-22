
struc s_list 
	.data resq 1 ; 
	.next resq 1
endstruc

section .text
	global ft_list_push_front
	extern ft_create_elem

; void ft_list_push_front(t_list **begin_list, void *data);

ft_list_push_front:
	push rbp
	mov rbp, rsp
	push rbx
	push r12

	cmp rdi, 0x0
	je	.done

	mov rbx, [rdi]

	mov r12, rdi

	mov rdi, rsi

	call ft_create_elem
	cmp rax, 0
	je .done

	mov rdi, r12

	mov [rax + s_list.next], rbx
	mov [rdi], rax

.done:
	pop r12
	pop rbx
	pop rbp
	ret