%define   com
%ifdef    com
orgaddr   equ   100h
%else
orgaddr   equ   7c00h
%endif

[SECTION .text]
[BITS 16]
global winit

welcome db 'Welcome Jiang OS!','$'

winit:

mov ax, cs
add ax, orgaddr/10h
mov ds, ax
mov es, ax

mov si, welcome   ;开机默认文本模式
call   printstr
call   newline

call   windows    ;切换到图形模式

mov ah,4ch
int 21h
jmp $


printstr:                  ;显示指定的字符串, 以'$'为结束标记
      mov al,[si]
      cmp al,'$'
      je disover
      mov ah,0eh
      int 10h
      inc si
      jmp printstr
disover:
      ret

newline:                     ;显示回车换行
      mov ah,0eh
      mov al,0dh
      int 10h
      mov al,0ah
      int 10h
      ret


windows:
    call setmode
    call alllines    ;画背景蓝色
    call win1
    call win2
    call win3
    call win4
    ret


setmode:
    mov  bx,0x4105    ;设置图形模式：1024×768 256色
    mov  ax,0x4f02
    int 10h
    ret


oneline:                 ;该程序是在第dx行画水平线
        ;mov cx,0        ;x坐标
        ;mov dx,0        ;y坐标
        mov al,0001b     ;颜色
        mov ah,0ch       ;写入点像
goon:   inc cx
        cmp cx,1023
        int 10h
        jne goon
        ret

alllines: mov dx,0      ;该程序画满整屏水平线
 goon2:   mov cx,0
          call  oneline
          inc dx
          cmp dx,767
          jne goon2
          ret

 win1:    mov dx,200      ;画矩形
  linew1:  mov cx,300
  goonw1: mov al,0100b     ;颜色
        mov ah,0ch       ;写入点像
        inc cx
        cmp cx,500
        int 10h
        jne goonw1
        inc dx
        cmp dx,400
        jne linew1
        ret


 win2:    mov dx,200      ;画矩形
  linew2:  mov cx,520
  goonw2: mov al,0010b     ;颜色
        mov ah,0ch       ;写入点像
        inc cx
        cmp cx,720
        int 10h
        jne goonw2
        inc dx
        cmp dx,400
        jne linew2
        ret


 win3:    mov dx,420      ;画矩形
  linew3:  mov cx,300
  goonw3: mov al,0110b     ;颜色
        mov ah,0ch       ;写入点像
        inc cx
        cmp cx,500
        int 10h
        jne goonw3
        inc dx
        cmp dx,620
        jne linew3
        ret


 win4:    mov dx,420      ;画矩形
  linew4:  mov cx,520
  goonw4: mov al,0111b     ;颜色
        mov ah,0ch       ;写入点像
        inc cx
        cmp cx,720
        int 10h
        jne goonw4
        inc dx
        cmp dx,620
        jne linew4
        ret