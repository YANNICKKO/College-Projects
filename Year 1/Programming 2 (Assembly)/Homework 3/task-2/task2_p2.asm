section .text
	global par

;; int par(int str_length, char* str)
;
; check for balanced brackets in an expression
par:
	push ebx
	push edx
	pop ecx
	xor ebx, ebx

loop1:
	;;vedem daca este open sau close
	cmp byte[eax + ecx - 1], '('
	jne close
	dec ebx
	jmp open
close:
	inc ebx
open:
;;daca este mai mica ca 0 inseamna ca avem o paranteza proasta
	cmp ebx, 0
	jl bad
	loop loop1
;;adunam sau scadem in functie de paranteza
;;daca este 0 este buna, daca nu e bad
	cmp ebx, 0
	jne bad
good:
	push 1
	pop eax
	jmp return
bad:
	push 0
	pop eax

return:
	pop ebx
	ret
