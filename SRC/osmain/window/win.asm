;ratsos
[bits 16]

    org     0x7c00 			;指明程序的偏移的基地址
    
    jmp     Entry			;跳转到程序入口
    db 		0x90
    db      "RATSBOOT"              

;----------------------------
;程序入口
Entry:

Clear_Screen: 				;清除屏幕	    
    mov ah,0x06				
    mov bh,0x07					
    mov al,0
    mov cx,0   
    mov dx,0xffff  
    mov bh,0x17				;属性为蓝底白字
    int 0x10
    
Clear_Cursor: 				; 光标位置初始化
    mov ah,0x02				
    mov bh,0
    mov dx,0
    int 0x10

Fin:
	hlt
    jmp Fin				;进入死循环，不再往下执行。

Fill_Sector:
	resb    510-($-$$)       	;处理当前行$至结束(1FE)的填充
	db      0x55, 0xaa
