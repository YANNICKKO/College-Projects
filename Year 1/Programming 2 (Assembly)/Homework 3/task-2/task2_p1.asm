section .text
	global cmmmc

;; int cmmmc(int a, int b)
;
;; calculate least common multiple fow 2 numbers, a and b
cmmmc:
	push ebx

	push eax
	push edx

	push edx
	pop ebx
	
;;facem cmmdc prima data si apoi
;;punem formula cu a*b/cmmdc
loop:
;;facem modulo si vedem daca este 0
	xor edx, edx
	div ebx
	push ebx
	push edx
	pop ebx
	pop eax
	
	cmp ebx, 0
	jne loop

;;aici e a*b
	push eax
	pop ecx
	pop eax
	pop ebx

	mul ebx

	div ecx

	pop ebx
	ret
