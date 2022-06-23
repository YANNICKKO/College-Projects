%include "../include/io.mac"

section .text
    global is_square
    extern printf

is_square:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov ebx, [ebp + 8]      ; dist
    mov eax, [ebp + 12]     ; nr
    mov ecx, [ebp + 16]     ; sq
    ;; DO NOT MODIFY
   
    ;; Your code starts here
    mov ebx, [ebp + 8]  
    mov edi, dword[ebp + 12]
while1:
    mov ebx, [ebp + 8]  
    mov ecx, dword[ebx + 4 * edi - 4]
    mov ebx, 0
while2:
    mov eax, ebx ;mergem prin toate valorile pana la n si le inmultim
    mul ebx      ;si apoi le comparam cu n
    cmp eax, ecx ;daca gasim un pp bagam 1
    jz is_sq

    inc ebx
    cmp ebx, ecx
    jle while2
not_sq:
    mov ecx, [ebp + 16] ;in caz ca nu gasim bagam 0
    mov esi, 0
    mov [ecx  + 4 * edi - 4], esi 
    jmp end
is_sq:
    mov ecx, [ebp + 16] 
    mov esi, 1
    mov [ecx + 4 * edi - 4], esi
end:
    dec edi
    jnz while1
    ;; Your code ends here
    
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY