%include "../include/io.mac"

struc point
    .x: resw 1
    .y: resw 1
endstruc

section .text
    global road
    extern printf

road:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]      ; points
    mov ecx, [ebp + 12]     ; len
    mov ebx, [ebp + 16]     ; distances
    ;; DO NOT MODIFY
   
    ;; Your code starts here
    
    dec ecx ;mergem de la penultimul si luam 2 cate 2 puncte
while:
    mov bx, word[eax + ecx * 4 - 4]
    mov dx, word[eax + 2 + ecx * 4 - 4]
    mov si, word[eax + 4 + ecx * 4 - 4]
    mov di, word[eax + 6 + ecx * 4 - 4]

    xor eax,eax ;adun ca in cel precedent
    add ax, bx
    add ax, dx
    sub ax, si
    sub ax, di

    cmp ax, 0 ;in caz ca dist e neg
    jg write

    xor eax, eax 
    add ax, si
    add ax, di
    sub ax, bx
    sub ax, dx


write:
    mov ebx, [ebp + 16]
    mov [ebx + 4 * ecx - 4], eax
    mov eax, [ebp + 8]
    loop while


    ;; Your code ends here
    
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY