; DO NOT ADD ANY LINES THAT BEGIN WITH @plugin OR YOU RISK GETTING A ZERO FOR THIS PART.

; Author: Wendi Tang
; GtId:903088141 

.orig x3000
		LD R0, U				; U x3000
		LD R1, V				; V x3001
		LD R2,QUOTIENT				;Load R4 from QUOTIENT x3002

		;if(b == 0)
		ADD R1,R1,0				;Change cc x3003
		BRz IVDEN				;If R1 is 0 x3004, set QUOTIENT to -1

		;while( a >= b)
		WHILELOOP ADD R3,R1,0			;Copy R1 to R3 x3005
		NOT R3,R3				;Flip all bits in R3 x3006
		ADD R3,R3,1				;Make a 2's complement x3007
		ADD R4,R0,R3				;ADD R0 and R3 x3008
		BRzp SUBSTRACT				;If R0 is still greater than R1, do substraction x3009
		
		ST R0,REMAINDER				;Set REMAINDER to R0 x300A			
					
		STOP HALT				; Stop program x300B

		;a -= b
		SUBSTRACT ADD R0,R4,0			;Load R0 from R4 which contains the result from R0 - R1 x300C
		;quotient++
		ADD R2,R2,1				;Increment R2 x300D
		ST R2,QUOTIENT				;Set QUTIENT to R2 x300E
		BR WHILELOOP				;BR to while check unconditionally x300F
		
		;{quotient = -1}
		IVDEN AND R2,R2,0			;Set R2 to 0 x3010
		ADD R2,R2,-1				;Set R2 to -1 x3011
		ST R2,QUOTIENT				;Set QUTIENT to R2 x3012
		BR STOP					;BR to STOP to stop the program x3013

		; Change U and V to suit your needs
		U .fill 300				; Initialize U x3014
		V .fill 0				; Initialize V x3015
		QUOTIENT .blkw 1			; Store your quotient here x3016
		REMAINDER .blkw 1			; Store your remainder here x3017
.end

