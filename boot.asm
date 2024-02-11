org 0x7c00
bits 16

start:
	call cls
	mov bx, display
	

print:
	mov al, [bx]
	cmp al, 0
	je halt
	call print_char
	inc bx
	jmp print

print_char:
	mov ah, 0x0e
	int 0x10
	ret

halt:
	ret

cls:
	mov ah, 0x07
	mov al, 0x00
	mov bh, 0x42 ; Color: 0x{background}{Foreground}
	mov cx, 0x00
	mov dx, 0x184f
	int 0x10
	ret
	
display db "Your system has officially been fucked.", 13, 10, "Goodbye.", 0 ; Text to display
;times 510 - ($ - $$) db 0 ; Fill up the rest
;dw  0xaa55 ; Make it bootable