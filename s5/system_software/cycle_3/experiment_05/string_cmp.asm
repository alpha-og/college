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
    JNE STR_NOT_SAME
    CMP AL, '$'
    JE STR_SAME
    INC SI
    INC DI
    JMP COMPARE

  STR_NOT_SAME:
    LEA DX, notSame
    JMP CLEANUP

  STR_SAME:
    LEA DX, same
    JMP CLEANUP

  CLEANUP:
    MOV AH, 09H
    INT 21H
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START
