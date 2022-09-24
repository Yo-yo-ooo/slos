; naskfunc
; 用途:nasm写的函数，用来测试time.c
; 作者:Yo-yo-ooo
; Creat Time:2022-8-12
; Compiler: GCC && nasm
[BITS 32]						; 3制作32位模式用的机器语言
		GLOBAL  load_cr0, store_cr0, io_stihlt
		GLOBAL	io_in8,  io_in16,  io_in32
		GLOBAL	io_out8, io_out16, io_out32
		GLOBAL	io_load_eflags, io_store_eflags
		GLOBAL  Clear_Screen, write_mem8
[SECTION .text]

load_cr0:		; int load_cr0(void);
		MOV		EAX,CR0
		RET

store_cr0:		; void store_cr0(int cr0);
		MOV		EAX,[ESP+4]
		MOV		CR0,EAX
		RET
io_stihlt:	; void io_stihlt(void);
		STI
		HLT
		RET

io_in8:	; int io_in8(int port);
		MOV		EDX,[ESP+4]		; port
		MOV		EAX,0
		IN		AL,DX
		RET
io_in16:	; int io_in16(int port);
		MOV		EDX,[ESP+4]		; port
		MOV		EAX,0
		IN		AX,DX
		RET

io_in32:	; int io_in32(int port);
		MOV		EDX,[ESP+4]		; port
		IN		EAX,DX
		RET

io_out8:	; void io_out8(int port, int data);
		MOV		EDX,[ESP+4]		; port
		MOV		AL,[ESP+8]		; data
		OUT		DX,AL
		RET

io_out16:	; void io_out16(int port, int data);
		MOV		EDX,[ESP+4]		; port
		MOV		EAX,[ESP+8]		; data
		OUT		DX,AX
		RET

io_out32:	; void io_out32(int port, int data);
		MOV		EDX,[ESP+4]		; port
		MOV		EAX,[ESP+8]		; data
		OUT		DX,EAX
		RET

io_load_eflags:	; int io_load_eflags(void);
		PUSHFD		; PUSH EFLAGS 
		POP		EAX
		RET

io_store_eflags:	; void io_store_eflags(int eflags);
		MOV		EAX,[ESP+4]
		PUSH	EAX
		POPFD		; POP EFLAGS 
		RET

sleep:
	push	eax
	push	ebx
	mov	eax,0x06
	mov	edx,[esp+12]
	int	36h
	pop	ebx
	pop	eax
	ret

Clear_Screen:
	mov ax,cs
    mov ss,ax
    mov sp,0x7c00  ;set stack and sp

    mov ah,0x06
    mov al,0

    mov ch,0  ;(0,0)
    mov cl,0
    mov dh,24  ;(24,79)
    mov dl,79
    mov bh,0x07 ;黑底白字
    int 0x10
