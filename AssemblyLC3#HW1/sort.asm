; Do not add any comments beginning with @plugin

; Author: Wendi Tang
; GtId:903088141 

.orig x3000
			LD R0, ARRAY_SIZE		; R0 is array_size
			LEA R1, ARRAY			; R1 is array address
			
			ADD R2,R0,0			;R2(i) =n

			IFORLOOP ADD R2,R2,-1		;R2--
			BRz STOP			;If R2(i) is smaller than 1, stop the program
			ADD R3,R2,0			;R3(j)= R2
			JFORLOOP ADD R3,R3,-1		;R3--			
			BRn IFORLOOP			;If R3(j) is smaller than 0, go to next i loop

			ADD R4,R1,R2 			;R4=R1+R2,R2(i)
			ST R4,I				;I address
			ADD R5,R1,R3			;R5=R1+R3,R3(j)
			ST R5,J				;J address
			LDI R4,I			;R4=Array[i]
			LDI R5,J			;R5=Array[j]
			NOT R6,R5			;Flip all bits in R5
			ADD R6,R6,1			;R6=-R5
			ADD R6,R4,R6			;R6=R4-R5
			BRzp	JFORLOOP		;

			STI R5,I			;Array[j] = Array[i]
			STI R4,J			;Array[i] = Array[j]
			BR JFORLOOP			;

			STOP		HALT		; Stop program

			ARRAY_SIZE 	.fill 	7	

			ARRAY		.fill 	1	
					.fill 	0	
					.fill	4	
					.fill 	2	
					.fill	-1
					.fill	13
					.fill	19
			I		.fill 	0		
			J		.fill 	0
.end
