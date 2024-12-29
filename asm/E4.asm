data  segment
io8255a        equ 288h
io8255b        equ 289h
io8255k        equ 28bh
io8255c        equ 28ah
led      db   3fh,06h,5bh,4fh,66h,6dh,7dh,07h,7fh,6fh,77H,7CH,39H,5EH,79H,71H ;段码
buffer1  db   0,0         ;显示缓冲区，为需要显示的数（预留两个字节用于显示十六进制）
len equ $ - buffer1
bz      db   ?           ;位码
nums  db    ?             ;需要显示的数量
data ends

code  segment
    assume cs:code,ds:data

start:   
    mov ax,data
    mov ds,ax
    
    mov dx,io8255k            ;将8255设为A口输出，B口输入
    mov al,82h                ;设置A为输出，B为输入
    out dx,al
    mov al,00h
    mov dx,io8255a            ;清空段码
    out dx,al
    
    mov al,0ffh               ;熄灭所有数码管
    mov dx,io8255c
    out dx,al
    
bg: 
    ; 读取B口数据
    mov dx,io8255b            ;将B口的数据读取到al中
    in al, dx
    mov ah, al                ;将读取的B口数据保存到ah中
    
    ; 提取高四位并存入buffer1的第一个字节
    mov al, ah
    shr al, 4
    mov buffer1, al           ;保存高四位到buffer1
    
    ; 提取低四位并存入buffer1的第二个字节
    mov al, ah
    and al, 0fh
    mov buffer1+1, al         ;保存低四位到buffer1+1
    
    ; 设置显示缓冲区
    mov di, offset buffer1    ;设di为显示缓冲区
    
    mov al, len
    add di, len
    dec di                    ;使di指向最右边的数值                   
    mov nums, al              ;记录显示的字符数
    mov bz, 0feh              ;设置位码
    
    mov cx, word ptr nums     ;循环次数

displ:
    mov si, offset led
    xor bx, bx                ;bx清零
    mov bl, [di]              ;取想要显示的最右边的数值
    add si, bx  
    mov al, byte ptr [si]     ;取对应的段码
    
    mov dx, io8255a           ;从8255 PA的口输出
    out dx, al
    
    mov al, byte ptr bz       ;使相应的数码管亮
    mov dx, io8255c
    out dx, al
    
    push cx
    mov cx, 01h                
     
delay: 
    loop delay                ;延时
    pop cx  
    
    mov al, 0ffh
    out dx, al  
    
    dec di
    push bx
    mov bl, bz
    rol bl, 1
    mov bz, bl
    pop bx
    loop displ
    
    jmp bg

code ends
    end start
