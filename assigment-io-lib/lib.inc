section .text

; Принимает код возрата и завершает текущий процесс
exit:
	mov rax, 60 ; syscall 'exit' number
	syscall
	ret

; Принимает указатель на нуль-терминированую строку, возращает её длинну
string_length:
	xor rax, rax

	.counter:
		cmp byte [rdi+rax], 0
		je .end
		inc rax
		jmp .counter

	.end:
		ret

; Принимает указатель на нуль-терминированую строку, выводит её в stdout
print_string:
	push rdi
	call string_length
   	mov rdx, rax
   	mov rax, 1
   	mov rsi, rdi
   	mov rdi, 1
   	syscall
   	pop rdi
   	ret

; Принимает код символа и выводит его в stdout
print_char:
	push rdi
    	mov rax, 1
    	mov rdi, 1
    	mov rsi, rsp
    	mov rdx, 1
    	syscall
	pop rdi
    	ret

; Переводит строку (выводит символ с кодом 0xA)
print_newline:
    	mov rdi, 0xA
    	call print_char
    	ret

; Выводит беззнаковое 8-байтовое число в десятичном формате 
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint:
	mov r11, 10
    	mov rax, rdi
	push 0
	jmp .separator
 
    	.separator:
       		xor rdx, rdx
       		div r11 
       		add rdx, 0x30
       		push rdx
       		cmp rax, 0
       		je .print
       		jmp .separator

    	.print:
       		pop rdi
		cmp rdi, 0
		je .end
		push rdi
       		call print_char
       		pop rdi
       		jmp .print

	.end:
		ret   

; Выводит знаковое 8-байтовое число в десятичном формате 
print_int:
    	.sign:
       		mov rax, rdi
       		sar rax, 63
       		and rax, 0x1
       		cmp rax, 0
       		je .print
                jnz .negative

   	.negative:
		push rdi
      		mov rdi, 0x2d
      		call print_char
      		pop rdi
      		neg rdi
      		jmp .print

    	.print:
      		call print_uint
      		ret

; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
 	xor rax, rax

	.compare_by_char:
		mov al, byte[rdi]
                cmp al, byte[rsi]
		jne .exception
		inc rdi
		inc rsi
		test al, al
		jnz .compare_by_char
		mov rax, 1
		ret

	.exception:
		mov rax, 0
		ret

; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
	push rsi
	push rdi
	push rdx
	push 0
	mov rax, 0
	mov rsi, rsp
	mov rdi, 0
	mov rdx, 1
	syscall
	pop rax
	pop rdx
	pop rdi
	pop rsi
    	ret 

; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор
read_word:
	.start_check:
		call read_char
		cmp rax, 0x20
		je .start_check
		cmp rax, 0x9
		je .start_check
		cmp rax, 0xA
		je .start_check
		xor rdx, rdx
		jmp .read

	.read:	
		cmp rdx, rsi
		je .exception
		cmp rax, 0x20
		je .add_null_term
		cmp rax, 0x9
		je .add_null_term
		cmp rax, 0xA
		je .add_null_term
		cmp rax, 0
		je .add_null_term
		mov byte[rdi+rdx], al
		inc rdx
		call read_char
		jmp .read

	.add_null_term:
		mov byte[rdi+rdx], 0
		mov rax, rdi
		ret
	
	.exception:
		xor rax, rax
		ret
 

; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
	push rbx
	xor rax, rax
	xor rdx, rdx
	xor rbx, rbx

	.get_number:
		mov bl, byte[rdi+rdx]
		cmp bl, 0x30
		jb .end
		cmp bl, 0x39
		ja .end
		imul rax, 10
		sub rbx, 0x30
		add rax, rbx
		inc rdx
		jmp .get_number

	.end:
		pop rbx
		ret


; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
parse_int:
	.sign:
		mov rax, rdi
		cmp byte[rax], 0x2D
		je .negative
		jmp .positive
		

	.negative:
		inc rdi
		call parse_uint
		neg rax
		inc rdx
		ret

	.positive:
		call parse_uint
		ret
		
; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
string_copy:
	push rdi
	call string_length
	pop rdi
	cmp rdx, rax
	jl .exception
	xor rax, rax
	jmp .copy

	.copy:
		xor r11, r11
		mov r11b, [rdi + rax]
		mov [rsi + rax], r11b
		cmp r11, 0
		je .end
		inc rax
		jnz .copy

	.exception:
		xor rax, rax
		ret

	.end:
		ret
