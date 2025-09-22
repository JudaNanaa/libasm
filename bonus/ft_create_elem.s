
struc s_list 
	.data resq 1 ; 
	.next resq 1
endstruc

section .text
	global ft_create_elem
	extern malloc

; t_list *ft_create_elem(void *data);

ft_create_elem:
	push rbp
	mov rbp, rsp
	push rbx

	mov rbx, rdi

	mov edi, s_list_size
	call malloc wrt ..plt

	cmp rax, 0x0
	je .done

	mov [rax + s_list.data], rbx
	mov qword [rax + s_list.next], 0x0

.done:
	pop rbx
	pop rbp
	ret