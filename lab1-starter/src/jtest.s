        # Basic branch test
	.text

main:
        addiu $v0, $zero, 0xa 
l_0:    
        addiu $5, $zero, 1 
        j l_1 
l_1:
        addiu $6, $zero, 1 
        j l_2
l_2:
        j l_3
l_3:
        addiu $8, $zero, 1 
        syscall

        