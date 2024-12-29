;**************************************
;*      A/D转换器数据在数码管上显示    *
;*      SW1--IN0  0809CS--298H       *
;**************************************
data segment
io8255a        equ 288h
io8255k        equ 28bh
io8255c        equ 28ah
io0809a        equ 298h

led      db   3fh,06h,5bh,4fh,66h,6dh,7dh,07h,7fh,6fh,77H,7CH,39H,5EH,79H,71H ;段码
bz       db   0feh                  ;位码初始化为右边第一位
data ends

code segment
    assume cs:code,ds:data

start:
    mov ax, data
    mov ds, ax
    
    ; 初始化8255
    mov dx, io8255k          ; 设置8255 A口为输出
    mov al, 80h
    out dx, al
    mov al, 00h
    mov dx, io8255a          ; 清空段码
    out dx, al
    mov al, 0ffh             ; 熄灭所有数码管
    mov dx, io8255c
    out dx, al

bg:
    mov dx, io0809a          ; 启动A/D转换器
    out dx, al
    
    ; 延时等待A/D转换完成
    mov cx, 008h
delay:
    loop delay
    
    ; 读取A/D转换后的值
    in al, dx
    mov bl, al               ; 保存原始数据到BL
 ; 显示低四位
    mov al, bl               ; 恢复原始数据
    and al, 0fh              ; 取低4位
    mov bz, 0feh             ; 设置位码为右边第二位
    call show_digit          ; 显示低4位到数码管
    mov al,bl
    ; 显示高四位
    mov cl, 4
    shr al, cl               ; 右移4位，保留高4位
    mov bz,0fdH
    call show_digit          ; 显示高4位到数码管
    
       
    jmp bg                   ; 循环

; 显示单个数字到数码管的子程序
show_digit proc near
    push bx
    mov si, offset led       ; 段码表起始地址
    xor bx, bx               ; 清零BX
    mov bl, al               ; 取当前数值
    add si, bx               ; 获取对应段码
    mov al, byte ptr [si]    ; AL中是段码
    
    mov dx, io8255a          ; 输出段码到8255 A口
    out dx, al
    
    mov al, bz               ; 设置位码到8255 C口
    mov dx, io8255c
    out dx, al
    
    ; 短暂延时以便显示稳定
    push cx
    mov cx, 01h
wait:
    loop wait
    pop cx
    
    ; 熄灭当前数码管
    mov al, 0ffh
    out dx, al
    pop bx
    ret
show_digit endp

code ends
end start
