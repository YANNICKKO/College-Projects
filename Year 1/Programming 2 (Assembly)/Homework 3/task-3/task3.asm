global get_words
global compare_func
global sort

section .data
    delimiters db " ,.", 0xa, 0

section .text
    extern strtok
    extern strlen
    extern strcmp
    extern qsort

compare_func:
    enter 0, 0

;;dam call la strlen pentru primul si al doilea
    mov eax, dword[ebp + 8]
    mov eax, dword[eax]
    push eax
    call strlen
    add esp, 4
    mov ebx, eax

    mov eax, dword[ebp + 12]
    mov eax, dword[eax]
    push eax
    call strlen
    add esp, 4
;;daca sunt egale facem strcmp
    sub eax, ebx
    jnz return

    mov eax, dword[ebp + 8]
    mov eax, dword[eax]
    mov ebx, dword[ebp + 12]
    mov ebx, dword[ebx]
    push eax
    push ebx
    call strcmp

return:
    neg eax
    leave
    ret

;; sort(char **words, int number_of_words, int size)
;  functia va trebui sa apeleze qsort pentru soratrea cuvintelor 
;  dupa lungime si apoi lexicografix
sort:
    enter 0, 0

    mov eax, dword[ebp + 8]
    mov ebx, dword[ebp + 12]
    mov ecx, dword[ebp + 16]

;;qsort
    push compare_func
    push ecx
    push ebx
    push eax
    call qsort
    add esp, 16

    leave
    ret

;; get_words(char *s, char **words, int number_of_words)
;  separa stringul s in cuvinte si salveaza cuvintele in words
;  number_of_words reprezinta numarul de cuvinte
get_words:
    enter 0, 0
;;facem strtok pentru primul
    mov eax, [ebp + 8]
    push delimiters
    push eax
    call strtok
    add esp, 8
    mov ebx, [ebp + 12]
    mov [ebx], eax

    mov edx, 1
;;strtok pentru restul (cu NULL)
loop:
    push edx
    push delimiters
    push 0
    call strtok
    add esp, 8
    pop edx

    mov ebx, [ebp + 12]
    mov [ebx + 4 * edx], eax
    inc edx
    cmp edx, [ebp + 16]
;;daca am facut toate cuvintele iese
    jne loop

    leave
    ret
