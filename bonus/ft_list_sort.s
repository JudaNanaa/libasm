struc s_list 
	.data resq 1 ; 
	.next resq 1
endstruc

section .text
	global ft_list_sort

; void ft_list_sort(t_list **begin_list, int (*cmp)(void *, void *));

ft_list_sort:
	push rbp
	mov rbp, rsp
	push rbx
	push r12
	push r13

	cmp rdi, 0
	je .done

	cmp rsi, 0
	je .done
	
	mov rbx, [rdi] ; la liste

	mov r12, rsi ; le pointeur de fonction

.loop1:
	cmp rbx, 0x0
	je .done
	
	mov r13, [rbx + s_list.next] ; le suivant dans la liste
.loop2:
	cmp r13, 0x0
	je .increment_rbx

	mov rdi, [rbx + s_list.data]
	mov rsi, [r13 + s_list.data]
    call r12
	cmp eax, 0
	jng .increment_r13
	
	mov rax, [rbx + s_list.data]
	mov rcx, [r13 + s_list.data]
	mov [rbx + s_list.data], rcx
	mov [r13 + s_list.data], rax

.increment_r13:
	mov r13, [r13 + s_list.next]
	jmp .loop2

.increment_rbx:
	mov rbx, [rbx + s_list.next]
	jmp .loop1

.done:
	pop r13
	pop r12
	pop rbx
	mov rsp, rbp
	pop rbp
	ret