;******************************************************;
;*            8253方式0计数器实验                     *;
;* 8253CS--280H  CLK0--PULSE1+  GATE0--+5V    *;
;8255Bpb0--PULSE1+
;******************************************************;
io8253_cnt0        equ 280h
io8253_cnt1        equ 281h
io8253_ctrl        equ 283h
io8255a              equ 288h
io8255con          equ 28bh    ;8255控制口
io8255b          equ 289h
io8255c        equ 28ah
data  segment
led      db   3fh,06h,5bh,4fh,66h,6dh,7dh,07h,7fh,6fh ;段码
buffer1  db   0,0         ;存放要显示的十位和个位
bz       dw   ?           ;位码
data ends

code  segment
    assume cs:code,ds:data
start:    mov ax,data
     mov ds,ax
     mov al,15h       ;设置8253计数器0为工作方式2,BCD计数
     mov dx,io8253_ctrl
     out dx,al
     mov dx,io8253_cnt0      ;送计数初值为99H
     mov al,99h
     out dx,al
     ;8255初始化
     mov dx,io8255con          
     mov al,82h     ;A口输出，C口输出，B口输入
     out dx,al
     
     mov di,offset buffer1      ;设di为显示缓冲区
     
loop1: 
   mov cx,030h  
    mov al,05h
    mov dx,io8253_ctrl
    out dx,al 
    mov dx,io8253_cnt0  
    in al,dx
    mov ah,00h
    mov bx,99h
    sub bx,ax
    aas 
    mov bh,bl
    and bl,0fh    ;取出低四位
    mov byte ptr [di],bl
    
    and bh,0f0h
    shr bh,1
    shr bh,1
    shr bh,1
    shr bh,1
    push di
    inc di
    mov byte ptr [di],bh
    pop di

loop2:  
    mov bh,02   ;要显示两位数
lll: 
    mov byte ptr bz,bh      ;将bx的高8位bh赋值给bz的低字节处
    push di
    dec di
    add di, bz
    mov bl,[di]                  ;bl为要显示的数
    pop di
    mov bh,0
    mov si,offset led            ;置led数码表偏移地址为SI
    add si,bx                    ;求出对应的led数码
    mov al,byte ptr [si]
    mov dx,io8255a               ;自8255A的口输出
    out dx,al
    mov al,byte ptr bz           ;使相应的数码管亮
    mov dx,io8255c
    out dx,al
    push cx
        mov cx,01h                 
delay:    loop delay                 ;延时
    pop cx   
    mov al,0ffh                    ;清空数码管显示
    out dx,al                         ;pc1和pc0为高电平
    mov bh,byte ptr bz         ;开始显示十位数了
    shr bh,1                  ;bh02h循环右移1位变成01h最后变成00h
    jnz lll
    loop loop2                  ;循环延时

    jmp loop1



    mov ah,4ch       ;退出
         int 21h
code ends
end start
