DATA SEGMENT
DATA1  DB  34H,39H,32H,36H,39H,'$'      ;第一个数据（作为加数1）
DATA2  DB  31H,35H,30H,38H,33H          ;第二个数据（作为加数2）
MES1   DB  '+','$'
MES2   DB  '=','$'
DATA ENDS

STACK SEGMENT                       ;堆栈段
STA DB 20 DUP(?)
TOP EQU LENGTH STA
STACK ENDS

CODE SEGMENT
ASSUME CS:CODE,DS:DATA,SS:STACK,ES:DATA
START:  MOV     AX,DATA
        MOV     DS,AX
        MOV     ES,AX
        MOV     AX,STACK
        MOV     SS,AX
        MOV     AX,TOP
        MOV    SP,AX
        MOV    SI,OFFSET DATA1
        
        MOV    BX,05
        CALL    DISPL             ;显示加数1
        MOV    AH,09H
        LEA     DX,MES1
        INT     21H
        MOV    SI,OFFSET  DATA2
        
        MOV    BX,05               ;显示加数2
        CALL    DISPL
        MOV    AH,09H
        LEA     DX,MES2
        INT     21H
        MOV    SI,OFFSET DATA1
        MOV    DI,OFFSET  DATA2
        CALL    SUBA               ;加法运算
        MOV    SI,OFFSET  DATA1
        MOV    BX,06               ;显示结果
        CALL    DISPL
        MOV    DL,0DH
        MOV    AH,02H
        INT     21H
        MOV    DL,0AH
        MOV    AH,02H

        INT     21H
        MOV    AX,4C00H
        INT     21H
        
DISPL   PROC   NEAR                ;显示子功能
DSI:    MOV    AH,02
        MOV    DL,[SI+BX-1]         ;显示字符串中一字符
        INT     21H
        DEC     BX                  ;修改偏移量
        JNZ     DSI
        RET
DISPL   ENDP

SUBA    PROC    NEAR
        MOV     DX,SI
        MOV     BP,DI
        MOV     BX,05
        
SU1:    SUB      BYTE PTR[SI+BX-1],30H
        SUB      BYTE PTR[DI+BX-1],30H
        DEC     BX                           ;将ASCII 码表示的数字串  
        JNZ     SU1                          ;转化为十六进制的数字串
        MOV     SI,DX
        MOV     DI,BP
        MOV     CX,05                        ;包括进位,共5位
        CLC                                   ;清进单位
        
SU2:    MOV     AL,[SI]
        MOV     BL,[DI]
        ADC     AL,BL                        ;带进位相加
        AAA                                  ;非组合BCD码的减法调整
        MOV     [SI],AL                      ;结果送加数1区
        INC     SI
        INC     DI                           ;指向下一位
        LOOP    SU2                          ;循环
        MOV     SI,DX
        MOV     DI,BP
        MOV     BX,05
        
SU3:    ADD     BYTE PTR  [SI+BX-1],30H
        ADD     BYTE PTR  [DI+BX-1],30H
        DEC     BX                           ;十六进制的数字串转化ASCII码表示的数字串
        JNZ     SU3
        RET     
        
SUBA   ENDP
CODE   ENDS
END     START

