; Do not add any comments beginning with @plugin

; Author: Wendi Tang
; GtId:903088141 

.orig x3000
			LD R0, ARRAY_SIZE		; R0 is array_size					x3000
			LEA R1, ARRAY			; R1 is array address					x3001
			
			ADD R2,R0,0			;R2(i) =n						x3002

			IFORLOOP ADD R2,R2,-1		;R2--							x3003
			BRz STOP			;If R2(i) is smaller than 1, stop the program		x3004
			ADD R3,R2,0			;R3(j)= R2						x3005
			JFORLOOP ADD R3,R3,-1		;R3--							x3006
			BRn IFORLOOP			;If R3(j) is smaller than 0, go to next i loop		x3007

			ADD R4,R1,R2 			;R4=R1+R2,R2(i)						x3008
			ST R4,I				;Array[i] address					x3009
			ADD R5,R1,R3			;R5=R1+R3,R3(j)						x300A
			ST R5,J				;Array[j] address					x300B
			LDI R4,I			;R4=Array[i]						x300C
			LDI R5,J			;R5=Array[j]						x300D
			NOT R6,R4			;Flip all bits in R4					x300E
			ADD R6,R6,1			;R6=-R4							x300F
			ADD R6,R5,R6			;R6=R5-R4						x3010
			BRzp	JFORLOOP		;							x3011

			STI R5,I			;Array[j] = Array[i]					x3012
			STI R4,J			;Array[i] = Array[j]					x3013
			BR JFORLOOP			;							x3014

			STOP		HALT		; Stop program						x3015

			ARRAY_SIZE 	.fill 	7	

			ARRAY		.fill 	1	
					.fill 	300	
					.fill	4	
					.fill 	2	
					.fill	-1
					.fill	13
					.fill	19
			I		.fill 	0	;Array[i] address	
			J		.fill 	0	;Array[j] address
.end
