%include "../include/io.mac"

section .text
    global spiral
    extern printf

section .data
    linlow dd 0
    linhig dd 0
    collow dd 0
    colhig dd 0
    N_sq dd 0

; void spiral(int N, char *plain, int key[N][N], char *enc_string);
spiral:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]  ; N (size of key line)
    mov ebx, [ebp + 12] ; plain (address of first element in string)
    mov ecx, [ebp + 16] ; key (address of first element in matrix)
    mov edx, [ebp + 20] ; enc_string (address of first element in string)
    ;; DO NOT MODIFY
    ;; TODO: Implement spiral encryption
    ;; FREESTYLE STARTS HERE
    mov eax, [ebp + 8]
    mov [N_sq], eax
    dec eax
    mov [linhig], eax ;init cu n-1
    mov [colhig], eax ;init cu n-1
    mov eax, 0
    mov [linlow], eax ;init cu 0
    mov [collow], eax ;init cu 0
    mov eax, dword[N_sq]
    mov edx, dword[N_sq]
    mul eax
    mov [N_sq], eax ;calc n^2

    mov ebx, 0 ;incepem cu 0 (vom folosi ebx pe post de contor)
while:
;;============
    mov eax, dword[collow] ;mergem de la collow la colhig
line1:

    mov esi, [ebp + 12] ;plain
    mov cl, byte[esi + ebx]
    mov esi, [ebp + 16] ;key
    mov edi, [linlow] ;
    push eax ;il tin minte
    mov eax, dword[ebp + 8]
    mul edi ;inm i(linia) cu n si
    mov edi, eax
    pop eax 
    add eax, edi ;adunam cu j(eax)
    add cl, byte[esi + 4 * eax]
    sub eax, edi
    mov edi, [ebp + 20]
    mov [edi + ebx], cl ;il bagam

    inc ebx ;un ebx++ si cand ajungem la n^2 iese
    mov edi, dword[N_sq]
    cmp ebx, edi
    jge end

    inc eax ;un i++ si cand ajunge la colhig iese
    mov ecx, dword[colhig]
    cmp eax, ecx
    jle line1

mov edx, dword[linlow] ;reactualizam linia cu unu mai in dreapta
inc edx
mov [linlow], edx
;;============
    mov edx, dword[linlow]
col1:

    mov esi, [ebp + 12] ;plain
    mov cl, byte[esi + ebx]
    mov esi, [ebp + 16] ;key
    mov edi, dword[colhig]
    push eax ;le tinem minte ca nu mai am unde
    push edx ;il tin minte
    mov eax, dword[ebp + 8]
    mul edx ;inm i(colhig) cu n
    mov edx, eax
    add edx, edi ;adun j(edx)
    add cl, byte[esi + 4 * edx]
    sub edx, edi
    pop edx
    pop eax
    mov edi, [ebp + 20] ;il bag
    mov [edi + ebx], cl

    inc ebx ;inc
    mov edi, dword[N_sq]
    cmp ebx, edi
    jge end

    inc edx ;inc
    mov ecx, dword[linhig]
    cmp edx, ecx
    jle col1

mov eax, dword[colhig] ;react coloana
dec eax
mov [colhig], eax
;;============
    mov eax, dword[colhig]
line2:

    mov esi, [ebp + 12] ;plain
    mov cl, byte[esi + ebx]
    mov esi, [ebp + 16] ;key
    mov edi, dword[linhig]
    push eax
    mov eax, dword[ebp + 8]
    mul edi ;inm i(linhig) cu n
    mov edi, eax
    pop eax
    add eax, edi ;adunam cu j(eax)
    add cl, byte[esi + 4 * eax]
    sub eax, edi
    mov edi, [ebp + 20]
    mov [edi + ebx], cl

    inc ebx ;inc
    mov edi, [N_sq]
    cmp ebx, edi
    jge end

    dec eax ;inc
    mov ecx, dword[collow]
    cmp eax, ecx
    jge line2

mov edx, dword[linhig] ;react linia
dec edx
mov [linhig], edx
;;============
    mov edx, dword[linhig]
col2:

    mov esi, [ebp + 12] ;plain
    mov cl, byte[esi + ebx]
    mov esi, [ebp + 16] ;key
    mov edi, dword[collow]
    push eax ;le tinem minte ca nu mai am unde
    push edx
    mov eax, dword[ebp + 8]
    mul edx ;inm i(edx) cu n
    mov edx, eax
    add edx, edi ;adunam cu j(collow)
    add cl, byte[esi + 4 * edx]
    sub edx, edi
    pop edx
    pop eax
    mov edi, [ebp + 20]
    mov [edi + ebx], cl

    inc ebx ;inc
    mov edi, dword[N_sq]
    cmp ebx, edi
    jge end

    dec edx ;inc
    mov ecx, dword[linlow]
    cmp edx, ecx
    jge col2

mov eax, dword[collow] ;react coloana
inc eax
mov [collow], eax

jmp while

end:


    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY
