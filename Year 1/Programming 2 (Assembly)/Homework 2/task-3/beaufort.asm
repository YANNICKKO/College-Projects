%include "../include/io.mac"

section .text
    global beaufort
    extern printf

; void beaufort(int len_plain, char *plain, int len_key, char *key, char tabula_recta[26][26], char *enc) ;
beaufort:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]  ; len_plain
    mov ebx, [ebp + 12] ; plain (address of first element in string)
    mov ecx, [ebp + 16] ; len_key
    mov edx, [ebp + 20] ; key (address of first element in matrix)
    mov edi, [ebp + 24] ; tabula_recta
    mov esi, [ebp + 28] ; enc
    ;; DO NOT MODIFY
    ;; TODO: Implement spiral encryption
    ;; FREESTYLE STARTS HERE
    mov ecx, eax
while:
    mov edi, [ebp + 12] ;plain
    mov esi, [ebp + 20] ;key
    xor eax, eax
    xor ebx, ebx

    mov al, byte[edi + ecx - 1] ;luam el cu el
    sub al, 'A' ;ii punem valoarea in al si bl
    mov bl, al

    mov edi, ecx ;in edi si eax este nr la care suntem din vector
    mov eax, ecx
    dec eax ;suntem cu unu mai jos de fapt
    xor edx, edx
    mov ecx, [ebp + 16] ;len key
    div ecx ;imp n la len_key (restul este in edx)
    xor eax, eax
    mov al, bl ;ii punem inapoi valoare lui al
    mov bl, byte[esi + edx] ;valoarea cheii necesare
    sub bl, 'A'
    mov ecx, edi ;ne trebuie ecx asa ca il luam din edi la care era salvat

    sub bl, al ;scadem din plain cheia
    jge poz
    add bl, 26 ;daca e neg ii mai punem inca 26
poz:
    add bl, 'A'

    mov esi, [ebp + 28]
    mov [esi + ecx - 1], bl ;il bagam
    loop while

    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY
