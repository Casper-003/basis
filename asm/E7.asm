io8255a        equ 288h
io8255k        equ 28bh
io8255c        equ 28ah
data segment

led      db   3fh,06h,5bh,4fh,66h,6dh,7dh,07h,7fh,6fh,77h,7ch,39h,5eh,79h,71h 
buffer   db   0,0         
counter  db   00           
bz       dw   ?           
data ends

code segment
assume cs:code,ds:data
start:
        mov ax,cs
    mov ds,ax
    
    mov dx, offset int3 
    mov ax, 250bh
    int 21h

    in al, 21h
    and al, 0f7h            
    out 21h, al             
    
    mov ax,data
    mov ds,ax
    
    mov dx, io8255k          
    mov al, 82h
    out dx, al
    mov di,offset buffer      
   
    sti

loop1: 
    mov cx,030h             
    mov bl, byte ptr counter                          
    mov bh,bl
    and bl,0fh              
    mov byte ptr [di],bl  
    
    and bh,0f0h            
    shr bh,4                  
    push di                  
    inc di                  
    mov byte ptr [di],bh 
    pop di                    

loop2:  
    mov bh,02   
    
lll: 

    mov byte ptr bz,bh      
    push di
    dec di                         
    add di, bz              
    mov bl,[di]                  
    pop di
    mov bh,0            
    mov si,offset led        
    add si,bx           
    mov al,byte ptr [si]
    mov dx,io8255a               
    out dx,al
    mov al,byte ptr bz           
    mov dx,io8255c
    out dx,al
    push cx          
    mov cx,01h   

delay:    
    loop delay              
    pop cx                     
    mov al,0ffh               
    out dx,al                  
    mov bh,byte ptr bz         
    shr bh,1                   
    jnz lll
    loop loop2                 

    jmp loop1

int3:

    push ax
    push bx
    push cx
    push dx

    mov cl, byte ptr counter
    inc cl
    mov byte ptr counter, cl

    mov al, 20h
    mov dx, 0020h
    out dx, al              

    pop dx
    pop cx
    pop bx
    pop ax
    iret
  

code ends
end start
