struc s_list 
	.data resq 1 ; 
	.next resq 1
endstruc

section .text
	global ft_list_size

; int	ft_list_size(t_list *lst)

ft_list_size:
	push rbp
	mov rbp, rsp
	
	xor eax, eax
	
.loop:
	cmp rdi, 0x0
	je .done

	mov rdi, [rdi + s_list.next]
	inc eax
	jmp .loop

.done:
	mov rsp, rbp
	pop rbp
	ret