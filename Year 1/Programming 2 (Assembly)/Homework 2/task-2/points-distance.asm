%include "../include/io.mac"

struc point
    .x: resw 1
    .y: resw 1
endstruc

section .text
    global points_distance
    extern printf

points_distance:
    ;; DO NOT MODIFY
    
    push ebp
    mov ebp, esp
    pusha

    mov ebx, [ebp + 8]      ; points
    mov eax, [ebp + 12]     ; distance
    ;; DO NOT MODIFY
   
    ;; Your code starts here

    mov cx, word[ebx]
    mov dx, word[ebx + 2]
    mov si, word[ebx + 4]
    mov di, word[ebx + 6]

    xor ebx, ebx
    add bx, cx
    add bx, dx
    sub bx, si
    sub bx, di ;adun toate punctele 

    cmp bx, 0 ;in caz ca distanta e negativa
    jg write

    xor ebx, ebx
    add bx, si
    add bx, di
    sub bx, cx
    sub bx, dx


write:
    mov eax, [ebp + 12]
    mov [eax], ebx
    mov ebx, [ebp + 8]
    ;; Your code ends here
    
    ;; DO NOT MODIFY
    popa
    leave
    ret

    ;; DO NOT MODIFY