;***********************************;
;*   8255方式0的C口输入,A口输出      *;
;*8255CS--288H  PC2--PK2  PA2--PL1 *;
;***********************************;
io8255con        equ 28bh
io8255b        equ 289h
io8255c        equ 28ah
code   segment
      assume cs:code
start:  
       mov dx,io8255con           ;设8255为C口输入,B口输出
       mov al,82h
       out dx,al                
       mov dx,io8255c
       out dx,al
       mov bl,80h
inout:  
        mov dx,io8255b             ;从b口输入一数据
        in al,dx
        and al,01h
        cmp al,00h
        je lft
        jne rt
rt:  
      mov al,bl
      mov dx,io8255c                ;从c口输出刚刚在b口输入的数据
      out dx,al
      call dly
      rol bl,1h    
      jmp inout

lft:
      mov al,bl
      mov dx,io8255c                ;从c口输出刚刚在b口输入的数据
      out dx,al
      call dly
      ror bl,1h
      jmp inout
dly   proc
      mov cx,10h                    ;延时

abi:mov di,0ffffh
     nop
     
again:dec di
     jnz again
     loop abi
     ret
     
dly endp      
      mov ah,4ch
      int 21h
code   ends
     end start