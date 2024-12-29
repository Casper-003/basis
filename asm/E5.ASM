CONTROL EQU 283H
COUNT0  EQU 280H
COUNT1  EQU 281H                  
COUNT2  EQU 282H
B8255   EQU 289H
C8255   EQU 28aH
K8255   EQU 28bH
CODE   SEGMENT
ASSUME CS:CODE
START:
       MOV   AL, 36H; 00110110B  ; 计数器0,16位,方式3,二进制
       MOV   DX, CONTROL
       OUT   DX, AL
       MOV   AX, 1000
       MOV   DX, COUNT0
       OUT   DX, AL              ; 计数器低字节
       MOV   AL, AH
       OUT   DX, AL              ; 计数器高字节
       MOV   AL, 76H; 01110110B  ; 计数器1,16位,方式3,二进制
       MOV   DX, CONTROL
       OUT   DX, AL
       MOV   AX, 2000
       MOV   DX, COUNT1
       OUT   DX, AL              ; 计数器低字节
       MOV   AL, AH
       OUT   DX, AL              ; 计数器高字节
       MOV   DX, K8255
       MOV   AL, 82H
       OUT   DX, AL
       mov bl,01H
L1:    
       mov dx,B8255             ;从b口输入一数据
        in al,dx
        and al,01h
        cmp al,00h
        je L1
        
you:
      mov al,bl
      mov dx,C8255                
      out dx,al
wait1s:
      mov dx,B8255             ;从b口输入一数据
        in al,dx
        and al,01h
        cmp al,01h
        je wait1s
       MOV   AL, 00000000B
       MOV   DX, C8255
       OUT   DX, AL
      rol bl,1h
      jmp L1

EXIT:  MOV   AX,4C00H
       INT   21H
CODE   ENDS
       END START
