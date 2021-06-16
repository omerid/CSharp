;Yarin Pinyan ,ID: 318330867
;
; 

;ebx - For 
;ecx - For 
;edx - For 
;esi - As 
;edi - As

include Irvine32.inc
include asm2_Q2_data.inc

.data
SubmmiterName BYTE "Yarin Pinyan ,ID: 318330867" , 10, 13, 0


.code
main PROC
MOV edx , OFFSET SubmmiterName
CALL WriteString
CALL CRLF


main ENDP
END main