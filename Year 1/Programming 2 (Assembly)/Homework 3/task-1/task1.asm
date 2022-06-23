section .text
	global sort

section .data
	first: dd 0

; struct node {
;     	int val;
;    	struct node* next;
; };

;; struct node* sort(int n, struct node* node);
; 	The function will link the nodes in the array
;	in ascending order and will return the address
;	of the new found head of the list
; @params:
;	n -> the number of nodes in the array
;	node -> a pointer to the beginning in the array
; @returns:
;	the address of the head of the sorted list
sort:
	enter 0, 0
	push ebx

	mov ecx, [ebp + 8] 	;;//number
	mov edi, [ebp + 12]	;;//first

	mov edx, 1 ;;//cautam nr 1
first_num:
	mov eax, [edi]
	add edi, 8
	cmp edx, eax
	jne first_num

	;;cand il gasim in bagam pe first si bagam adresa pe stiva
	mov esi, edi
	sub esi, 8
	mov [first], esi
	push esi

	dec ecx

loop1:
	mov edi, [ebp + 12]
	inc edx

loop2:
	;;cautam prin tot vectorul
	mov eax, [edi]
	add edi, 8
	cmp edx, eax
	jne loop2

	;;cand il gasim il scoatem din stiva
	;;si ii dam push la final
	pop ebx
	mov esi, edi
	sub esi, 8
	mov [ebx + 4], esi
	push esi

	loop loop1

pop ebx
mov eax, [first]

	pop ebx
	leave
	ret
