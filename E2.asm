DATA SEGMENT
MARK DB ?
MSG0 DB 0DH,0AH,'INPUT 1 TO DISPLAY NAME,2 TO DISPLAY ID,3 TO DISPLAY CLASS','$'
MSG1 DB 0DH,0AH,'ZCJ','$'
MSG2 DB 0DH,0AH,'68','$'
MSG3 DB 0DH,0AH,'COMMUNICATION ENGINEERING CLASS 3','$'
ERROR DB 0DH,0AH,'ERROR',0DH,0AH,'$'
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE,DS:DATA,ES:DATA
START:  MOV AX,DATA
        MOV DS,AX
        MOV ES,AX
        
        ;将光标移到行首
        MOV AH,02H
        MOV DH,0
        MOV DL,0
        INT 10H
        
        JMP SHOW_MSG0

        ;无限循环等待按键输入
LOOP_START:
        
        MOV AH,01H
        INT 16H
        JZ LOOP_START
        
        ;READ ASCII
        MOV AH,00H
        INT 16H
        MOV BL,AL
        
        ;DISPLAY OR END
        CMP BL,'1'
        JE SHOW_MSG1
        CMP BL,'2'
        JE SHOW_MSG2
        CMP BL,'3'
        JE SHOW_MSG3
        CMP BL,20H
        JMP EXIT_PROGRAM
        
SHOW_MSG1:
        LEA DX,MSG1
        MOV AH,09H
        INT 21H
        JMP LOOP_START
        
SHOW_MSG2:
        LEA DX,MSG2
        MOV AH,09H
        INT 21H
        JMP LOOP_START
        
SHOW_MSG3:
        LEA DX,MSG3
        MOV AH,09H
        INT 21H
        JMP LOOP_START
        
SHOW_MSG0:
        LEA DX,MSG0
        MOV AH,09H
        INT 21H
        
EXIT_PROGRAM:
        MOV AH,4CH
        INT 21H
        
CODE ENDS
END START