ASSUME CS:CODE, DS:DATA
DATA SEGMENT
  str1 DB 'HELLO$'
  str2 DB 'HELO$'
  same DB 'Strings are equal$'
  notSame DB 'String are not equal$'
DATA ENDS
CODE SEGMENT
  START:
    MOV AX, DATA
    MOV DS, AX
    XOR AX, AX
    LEA SI, str1
    LEA DI, str2

  COMPARE:
    MOV AL, [SI]
    MOV BL, [DI]
    CMP AL, BL
    JNE NOT_SAME
    CMP AL, '$'
    JE SAME
    INC SI
    INC DI
    JMP COMPARE

  NOT_SAME:
    LEA DX, notSame
    JMP CLEANUP

  SAME:
    LEA DX, same
    JMP CLEANUP

  CLEANUP:
    MOV AH, 09H
    INT 21H
    MOV AH 4CH
    INT 21H
CODE ENDS
END START
