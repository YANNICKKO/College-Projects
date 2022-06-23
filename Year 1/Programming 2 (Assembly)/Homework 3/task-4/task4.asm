section .text
	global cpu_manufact_id
	global features
	global l2_cache_info

;; void cpu_manufact_id(char *id_string);
;
;  reads the manufacturer id string from cpuid and stores it in id_string

;;La fiecare dintre ele bag in eax ce imi trebuie si dupa caut
;;in functie de ce cere. Am dat shiftari am si cautat pe net
;;cu ce trebuie sa dau end in fucntie de fiecare chestie

cpu_manufact_id:
	enter 	0, 0
	push ebx

	mov eax, 0
	cpuid
	mov eax, [ebp + 8]
	mov	[eax], ebx
	mov	[eax + 4], edx
	mov	[eax + 8], ecx
	
	pop ebx
	leave
	ret

;; void features(int *apic, int *rdrand, int *mpx, int *svm)
;
;  checks whether apic, rdrand and mpx / svm are supported by the CPU
;  MPX should be checked only for Intel CPUs; otherwise, the mpx variable
;  should have the value -1
;  SVM should be checked only for AMD CPUs; otherwise, the svm variable
;  should have the value -1
features:
	enter 	0, 0
	push ebx
;;apic
	mov eax, 1
	cpuid
	mov eax, [ebp + 8]
	shl edx, 27
	shr edx, 31
	cmp edx, 0
	je zero1
	mov edx, 1
zero1:
	mov	[eax], edx
;;rdrand
	mov eax, [ebp + 12]
	shl ecx, 5
	shr ecx, 31
	cmp ecx, 0
	je zero2
	mov ecx, 1
zero2:
	mov	[eax], ecx
;;mpx
	mov eax, 0
	cpuid
	cmp edx, 0x49656e69
	jne not_amd
	mov eax, 7
	cpuid
	mov eax, [ebp + 16]
	shl ebx, 21
	shr ebx, 31
	cmp ebx, 0
	je zero3
	mov ebx, 1
zero3:
	mov	[eax], ebx

not_amd:
	mov eax, [ebp + 16]
	mov ebx, -1
	mov [eax], ebx
;;svm
	mov eax, 0
	cpuid
	cmp edx, 0x49656e69
	je not_intel
	mov eax, 0x80000001
	cpuid
	mov eax, [ebp + 20]
	shr ecx, 2
	cmp ecx, 0
	je zero4
	mov ecx, 1
zero4:
	mov	[eax], ecx
	jmp end


not_intel:
	mov eax, [ebp + 20]
	mov ebx, -1
	mov dword[eax], ebx

end:
	pop ebx
	leave
	ret

;; void l2_cache_info(int *line_size, int *cache_size)
;
;  reads from cpuid the cache line size, and total cache size for the current
;  cpu, and stores them in the corresponding parameters
l2_cache_info:
	enter 	0, 0
	push ebx
	mov eax, 0x80000006
	cpuid
	mov eax, [ebp + 8]
	shl ecx, 24
	shr ecx, 24
	mov [eax], ecx

	pop ebx
	leave
	ret
