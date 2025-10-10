ASSUME CS:CODE, DS:DATA
DATA SEGMENT
  str DB "hello world, this is some test string$"
  substr DB "is$"
  found DB "Substring found$"
  notFound DB "Substring not found$"
DATA ENDS
CODE SEGMENT
  START:
    MOV AX, DATA
    MOV DS, AX
    XOR AX, AX
    LEA BX, str

  FIND:
    MOV SI, BX
    LEA DI, substr

  CHECK:
    MOV DL, [DI]
    INC DI
    CMP DL, "$"
    JE STR_FOUND
    MOV AL, [SI]
    INC SI
    CMP AL, "$"
    JE STR_NOT_FOUND
    CMP AL, DL
    JE CHECK
    INC BX
    JMP FIND

  STR_NOT_FOUND:
    LEA DX, notFound
    JMP CLEANUP

  STR_FOUND:
    LEA DX, found
    JMP CLEANUP

  CLEANUP:
    MOV AH, 09H
    INT 21H
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START
