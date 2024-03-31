section .data 
    prompt db "Enter a three-digit number: ", 0 
    yes db "Yes, it is a palindrome.", 0 
    no db "No, it is not a palindrome.", 0 

section .bss 
    number resb 3 
    reversed resb 3 
 
section .text 
    global _start 
 
_start: 
    ; Выводим приглашение 
    mov rax, 0 
    mov rdi, 1 
    mov rsi, prompt 
    mov rdx, 26 
    syscall 
 
    ; Считываем введенное число 
    mov rax, 0 
    mov rdi, 0 
    mov rsi, number 
    mov rdx, 3 
    syscall 
 
    ; Переворачиваем число 
    mov rsi, number 
    mov rdi, reversed 
    call reverse 
 
    ; Сравниваем и выводим результат 
    mov rsi, number 
    mov rdi, reversed 
    call compare 
 
    ; Выход 
    mov rax, 60 
    xor rdi, rdi 
    syscall 
 
reverse: 
    mov rcx, 3 
    xor rdx, rdx 
 
reverse_loop: 
    mov al, [rsi+rdx] 
    mov [rdi+rcx-1], al 
    inc rdx 
    loop reverse_loop 
 
    ret 
 
compare: 
    mov rcx, 3 
    xor rdx, rdx 
    xor rbx, rbx 
 
compare_loop: 
    mov al, [rsi+rdx] 
    cmp al, [rdi+rdx] 
    jne not_equal 
    inc rdx 
    inc rbx 
    loop compare_loop 
 
    cmp rbx, 3 
    je equal 
 
not_equal: 
    mov rax, 1 
    mov rdi, 1 
    mov rsi, no 
    mov rdx, 27
    syscall 
    ret 
 
equal: 
    mov rax, 1 
    mov rdi, 1 
    mov rsi, yes 
    mov rdx, 24
    syscall 
    ret
