%include "../include/io.mac"

section .text
    global simple
    extern printf

simple:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     ecx, [ebp + 8]  ; len
    mov     esi, [ebp + 12] ; plain
    mov     edi, [ebp + 16] ; enc_string
    mov     edx, [ebp + 20] ; step

    ;; DO NOT MODIFY
   
    ;; Your code starts here

letter:
    mov al, byte[esi + ecx - 1]
    sub al, 'A' ;luam valoarea
    add al, dl ;aducam cifru
    mov bl, 26 ;in caz ca trece peste Z
    xor ah, ah
    div bl
    mov al, ah
    add al, 'A' ;adunam inapoi cu 'A'
    mov [edi + ecx - 1], al ;il bagam

    loop letter

    ;; Your code ends here
    
    ;; DO NOT MODIFY

    popa
    leave
    ret
    
    ;; DO NOT MODIFY
