ASSUME CS:CODE, DS:DATA
DATA SEGMENT
  str DB 'heLlO worlD$'
  vowels DB 'aeiouAEIOU$'
  count DB ?
DATA ENDS
CODE SEGMENT
  START:
    MOV AX, DATA
    MOV DS, AX
    XOR AX, AX
    LEA SI, str
    XOR CL, CL

  S_COUNT:
    MOV AL, [SI]
    CMP AL, '$'
    JE CLEANUP 
    INC SI
    LEA DI, vowels
    JMP IS_VOWEL

  IS_VOWEL:
    MOV BL, [DI]
    CMP BL, '$'
    JE COUNT
    CMP AL, BL
    JE INC_COUNT
    INC DI
    JMP IS_VOWEL
  
  INC_COUNT:
    INC CL
    JMP S_COUNT

  CLEANUP:
    MOV count, CL
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START
