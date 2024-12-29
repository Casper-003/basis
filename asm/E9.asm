;**********************;
;*   数/模转换实验2   *;
;*   输出正弦波或锯齿波  *;
;**********************;
data segment
io0832a        equ 290h      
io8255CON      equ 28bh
io8255b        equ 289h

sin     db 80h,96h,0aeh,0c5h,0d8h,0e9h,0f5h,0fdh
    db 0ffh,0fdh,0f5h,0e9h,0d8h,0c5h,0aeh,96h
    db 80h,66h,4eh,38h,25h,15h,09h,04h
    db 00h,04h,09h,15h,25h,38h,4eh,66h           ;正弦波数据

sawtooth db 00h,10h,20h,30h,40h,50h,60h,70h,80h,90h,0a0h,0b0h,0c0h,0d0h,0e0h,0f0h
          db 0ffh,0f0h,0e0h,0d0h,0c0h,0b0h,0a0h,90h,80h,70h,60h,50h,40h,30h,20h,10h ;锯齿波数据
data ends

code segment
   assume cs:code,ds:data
start:  
    mov ax,data
    mov ds,ax
    
    ; 初始化8255
    mov dx,io8255CON
    mov al,82h               ; 设置8255：B口输入
    out dx,al

main_loop:
    ; 读取开关状态
    mov dx,io8255b           ; 从B口读取数据
    in al,dx
    and al,01h               ; 检查K0（最低位）
    cmp al,00h
    je output_sawtooth       ; 如果K0低电平，输出锯齿波
    jne output_sine          ; 如果K0高电平，输出正弦波

output_sine:
    mov si,offset sin        ; 设置正弦波数据的偏移地址为SI
    mov bh,32                ; 一组输出32个数据

sine_loop:
    mov al,[si]              ; 将数据输出到D/A转换器
    mov dx,io0832a
    out dx,al
    call delay               ; 延时
    inc si                   ; 取下一个数据
    dec bh
    jnz sine_loop            ; 若未取完32个数据则循环
    jmp main_loop            ; 返回主循环

output_sawtooth:
    mov si,offset sawtooth   ; 设置锯齿波数据的偏移地址为SI
    mov bh,32                ; 一组输出32个数据

sawtooth_loop:
    mov al,[si]              ; 将数据输出到D/A转换器
    mov dx,io0832a
    out dx,al
    call delay               ; 延时
    inc si                   ; 取下一个数据
    dec bh
    jnz sawtooth_loop        ; 若未取完32个数据则循环
    jmp main_loop            ; 返回主循环

delay proc
    mov cx,10h
outer_loop:
    mov di,0FFFFh
inner_loop:
    nop
    dec di
    jnz inner_loop
    loop outer_loop
    ret
delay endp

exit:
    mov ah,4ch               ; 退出
    int 21h
code ends
   end start
