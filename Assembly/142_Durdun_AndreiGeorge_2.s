.data
	m: .space 4
	n: .space 4
	p: .space 4
	lineIndex: .space 4
	colIndex: .space 4
	kindex: .space 4
	matrix: .zero 1600
	matrix2: .zero 1600
	k: .space 4
	x: .space 4
	y: .space 4
	nb: .space 4
	mb: .space 4
	
	fin: .asciz "in.txt"
	fout: .asciz "out.txt"
	r: .asciz "r"
	w: .asciz "w"
	pin: .space 4
	pout: .space 4
	
	formatScanf: .asciz "%d"
	formatPrintf: .asciz "%d "
	endl: .asciz "\n"
	

.text

.global main
main:
	
	push $r
	push $fin
	call fopen
	pop %ebx
	pop %ebx
	mov %eax, pin
	
	push $w
	push $fout
	call fopen
	pop %ebx
	pop %ebx
	mov %eax,pout 
	
	
	
	//////////
	push $m
	push $formatScanf
	push pin
	call fscanf
	add $12, %esp
	
	push $n
	push $formatScanf
	push pin
	call fscanf
	add $12, %esp
	
	push $p
	push $formatScanf
	push pin
	call fscanf
	add $12, %esp
	
	mov $matrix, %edi
	mov $0, %ecx
	
	movl m, %eax
	add $2, %eax
	mov %eax, mb
	
	movl n, %eax
	add $2, %eax
	mov %eax, nb
	
	for_p:
		cmp p, %ecx
		je continua_program_1
		
		
		push %ecx
		push $x
		push $formatScanf
		push pin
		call fscanf
		add $12, %esp
		pop %ecx
		
		push %ecx
		push $y
		push $formatScanf
		push pin
		call fscanf
		add $12, %esp
		pop %ecx 
		
		movl x, %eax
		inc %eax
		mull nb
		add y, %eax
		inc %eax
		movl $1, (%edi ,%eax, 4)
		
		inc %ecx
		jmp for_p
		
		continua_program_1:
	
	
		push $k
		push $formatScanf
		push pin
		call fscanf
		add $12, %esp
		
		mov $matrix2, %esi
		
		movl $0, kindex
		
		for_k:
		
			mov kindex, %ecx
			cmp k, %ecx
			je et_afis_matr
			
			movl $1, lineIndex
			for_m:
				mov lineIndex, %ecx
				mov mb, %edx
				dec %edx
				cmp %edx, %ecx
				je cop_a
				
				movl $1, colIndex
				for_n:
					mov colIndex, %ecx
					mov nb, %edx
					dec %edx
					cmp %edx, %ecx
					je cont_linie
					
					//instructiuni in for-ul lui j
					
					mov $0, %ebx
					
					a1:
					//a[i-1][j]:
					
					movl lineIndex, %eax
					dec %eax
					mull nb
					add colIndex, %eax
					addl (%edi, %eax, 4), %ebx
					
					a2:
					//a[i+1][j]:
					
					movl lineIndex, %eax
					inc %eax
					mull nb
					add colIndex, %eax
					addl (%edi, %eax, 4), %ebx
					
					a3:
					//a[i][j-1]:
					
					movl lineIndex, %eax
					mull nb
					add colIndex, %eax
					dec %eax
					addl (%edi, %eax, 4), %ebx
					
					a4:
					//a[i][j+1]
					
					movl lineIndex, %eax
					mull nb
					add colIndex, %eax
					inc %eax
					addl (%edi, %eax, 4), %ebx
					
					a5:
					//a[i-1][j-1]
					
					movl lineIndex, %eax
					dec %eax
					mull nb
					add colIndex, %eax
					dec %eax
					addl (%edi, %eax, 4), %ebx
					
					a6:
					//a[i-1][j+1]
					
					movl lineIndex, %eax
					dec %eax
					mull nb
					add colIndex, %eax
					inc %eax
					addl (%edi, %eax, 4), %ebx
					
					a7:
					//a[i+1][j-1]
					
					movl lineIndex, %eax
					inc %eax
					mull nb
					add colIndex, %eax
					dec %eax
					addl (%edi, %eax, 4), %ebx
					
					a8:
					//a[i+1][j+1]
					
					movl lineIndex, %eax
					inc %eax
					mull nb
					add colIndex, %eax
					inc %eax
					addl (%edi, %eax, 4), %ebx
					
					movl lineIndex, %eax
					mull nb
					add colIndex, %eax
					
					//conditiile
					cmp $2, %ebx
					je modif_2
					
					cmp $2, %ebx
					jl modif_1
					
					cmp $3, %ebx
					jg modif_1
					
					cmp $3, %ebx
					je modif_3
					
					modif_1:
						movl $0, (%esi, %eax, 4)
						jmp continua_program_2
						
					modif_2:
						mov (%edi, %eax, 4), %ebx
						mov %ebx, (%esi, %eax, 4)
						jmp continua_program_2
						
					modif_3:
						movl $1, (%esi, %eax, 4)
					
				continua_program_2:		
				    
				incl colIndex
				jmp for_n
					
					cont_linie:
						incl lineIndex
						jmp for_m
						
				cop_a:
			
					movl $1, lineIndex
					for_m1:
						mov lineIndex, %ecx
						mov mb, %edx
						dec %edx
						cmp %edx, %ecx
						je cont_for_k
					
						movl $0, colIndex
						for_n1:
							mov colIndex, %ecx
							mov nb, %edx
							dec %edx
							cmp %edx, %ecx
							je cont_linie1
							
							movl lineIndex, %eax
							mull nb
							add colIndex, %eax
							mov (%esi, %eax, 4), %ebx
							mov %ebx, (%edi, %eax, 4)
							
							incl colIndex
							jmp for_n1
						
							cont_linie1:
							
								incl lineIndex
								jmp for_m1
								
				cont_for_k:
			
					incl kindex
					jmp for_k
		
		et_afis_matr:
		movl $1, lineIndex
		
		for_lines:
			mov lineIndex, %ecx
			mov mb, %edx
			dec %edx
			cmp %edx, %ecx
			je et_exit
			
			movl $1, colIndex
			for_columns:
				mov colIndex, %ecx
				mov nb, %edx
				dec %edx
				cmp %edx, %ecx
				je cont_for_lines
				
				movl lineIndex, %eax
				mull nb
				add colIndex, %eax
				
				afis:
					lea matrix, %edi
					movl (%edi, %eax, 4), %ebx
					
					push %ebx
					push $formatPrintf
					push pout
					call fprintf
					add $12, %esp
					pop %ebx 
				
				incl colIndex
				jmp for_columns
				
			cont_for_lines:
				push $endl
				push pout
				call fprintf
				add $8, %esp
				incl lineIndex
				jmp for_lines
		
et_exit:
	
	push pout
	call fclose
	pop %ebx	
	
	push pin
	call fclose
	pop %ebx	
	
	movl $1, %eax
	movl $0, %ebx
	int $0x80
	
