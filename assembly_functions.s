
                AREA    |.text|, CODE, READONLY
					
read_sp			proc
				export read_sp	[WEAK]
					
				push {lr}
				mov r0, sp
	
				pop {pc}
				endp
					
					
				end