.data
	m: .space 4
	n: .space 4
	p: .space 4
	lineIndex: .space 4
	colIndex: .space 4
	matrix: .zero 1600
	matrix2: .zero 1600
	v: .space 1600
	v1: .space 1600
	vindex: .space 4
	lungv: .space 4
	lungkey: .space 4
	k: .space 4
	x: .space 4
	y: .space 4
	nb: .space 4
	mb: .space 4
	cript: .space 4
	cuv: .space 30
	lungCuv: .space 4
	kindex: .space 4
	numar: .space 4
	i: .space 4
	j: .space 4
	put2: .space 4
	stop: .space 4
	numere: .space 200 
	nindex: .long 0
	c: .space 11
	prefix: .asciz "x"
	a: .long 16
	b: .long 1
	formatScanf: .asciz "%d"
	formatPrintf: .asciz "%c"
	formatPrintf1: .asciz "%02X"
	formatPrintf2: .asciz "%d"
	formatPrintf3: .asciz "%s\n"
	formatScanf1: .asciz "%s"
	formatScanf2: .asciz "%c"
	formatScanf3: .asciz "%x"
	endl: .asciz "\n"
	
	

.text

.global main
main:
	
	push $m
	push $formatScanf
	call scanf
	add $8, %esp
	
	push $n
	push $formatScanf
	call scanf
	add $8, %esp
	
	push $p
	push $formatScanf
	call scanf
	add $8, %esp
	
	mov $matrix, %edi
	mov $matrix2, %esi
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
		call scanf
		add $8, %esp
		pop %ecx
		
		push %ecx
		push $y
		push $formatScanf
		call scanf
		add $8, %esp
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
	call scanf
	add $8, %esp
	
	mov $matrix2, %esi
		
		movl $0, kindex
		
		for_k:
		
			mov kindex, %ecx
			cmp k, %ecx
			je continua_program_3
			
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
		
	continua_program_3:
	//////////////
	
	
	push $cript
	push $formatScanf
	call scanf
	add $8, %esp
	
	//COPIERE_IN_VECTOR
	
	movl $0, vindex
	movl $0, lineIndex
	for_lines:
		mov lineIndex, %ecx
		cmp mb, %ecx
		je continua_program_4
		
		movl $0, colIndex
		for_columns:
			mov colIndex, %ecx
			cmp nb, %ecx
			je cont_for_lines
			
			movl lineIndex, %eax
			mull nb
			addl colIndex, %eax
			
			mov $matrix, %esi
			mov $v, %edi
			movl (%esi, %eax, 4), %ebx
			movl %ebx, (%edi, %eax, 4)
			movl vindex, %eax
			movl (%edi, %eax, 4), %ebx
		
		    
		incl colIndex
		incl vindex
		jmp for_columns
		
	cont_for_lines:
		incl lineIndex
		jmp for_lines
		
	continua_program_4:
	//LUNGIMEA CUVANTULUI
	
	
	push $cuv
	push $formatScanf1
	call scanf
	pop %ebx
	pop %ebx	
	
	lea cuv, %edi
	movl $0, lungCuv
	for_cuv:
		mov lungCuv, %ecx
		cmp $30, %ecx
		je cont
		
		movb (%edi, %ecx, 1), %al	
		
		cmp $0, %eax
		je cont
		
	incl lungCuv
	jmp for_cuv
		
		
	cont:
		
		/////test
		movl cript, %ecx
		cmp $1, %ecx
		je modifica
		jmp nimic
		modifica:
			movl $2, %ebx
			movl lungCuv, %eax
			subl $2, %eax
			div %ebx
			movl %eax, lungCuv
			
			
		nimic:
		
		
		
		movl mb, %eax
		mull nb
		movl %eax, lungv
		
		//lungkey
		movl $8, %ebx
		movl lungCuv, %eax
		mul %ebx
		movl %eax, lungkey
		
		//FORMARE CHEIE
		movl $0, i
		movl $0, j
		for_key:
			movl i, %ecx
			cmp lungkey, %ecx
			je cont2
			
			lea v, %edi
			lea v1, %esi
			
			movl j, %eax
			divl lungv
			cmp $0, %edx
			je reset_j
			jmp creste_j
			
			reset_j:
				movl $0, j
			creste_j:
				movl j, %eax
				
				movl (%edi, %eax, 4), %ebx
				movl %ebx, (%esi, %ecx, 4)
				//test
				push %ebx
			push $formatPrintf2
			//call printf
			pop %edx
			pop %edx
				
				incl j
		
		incl i
		jmp for_key
			
		
		cont2:
		
		
		//FORMARE NUMERE
		
		//FORMARE NUMERE
		movl $7, vindex
		movl $0, stop
		for_parcurgere_8x8:
			
			mov vindex, %ecx
			cmp lungkey ,%ecx
			jg cont3
			
			movl vindex, %eax
			
			movl $0, numar
			
			lea v1, %edi
			movl numar, %ebx
			addl (%edi, %eax, 4), %ebx
			movl %ebx, numar
			
			
			dec %eax
			movl %eax, i
			movl $2, put2
			
			for_formare:
				movl i, %ecx
				cmp stop ,%ecx
				jl afis_nr
				
				
				
				
				mov (%edi, %ecx, 4), %eax
				mull put2
				addl numar, %eax
				movl %eax, numar
				
				
				
				movl $2, %edx
				movl put2, %eax
				mull %edx
				movl %eax, put2
						
			decl i
			jmp for_formare
			
			afis_nr:
				
				
				//pun numarul in vector
				lea numere, %esi
				movl nindex, %eax
				movl numar, %ebx
				movl %ebx, (%esi, %eax, 4)
				
				
				incl nindex
				
				mov vindex, %ebx
				addl $8, %ebx
				movl %ebx, vindex
				
				
				mov stop, %ebx
				addl $8, %ebx
				movl %ebx, stop
				
				
				jmp for_parcurgere_8x8
				
					
		cont3:
			
			
		
	
	//CRIPTARE / DECRIPTARE
		
	cmpl $0, cript
	je cripteaza
	jmp decripteaza
	
	cripteaza:
		
		//citire cuv
		push $cuv
		push $formatScanf1
		call scanf
		pop %ebx
		pop %ebx
		
		push $0
		push $formatPrintf2
		call printf
		pop %edx
		pop %edx
		
		push prefix
		push $formatPrintf
		call printf
		pop %edx
		pop %edx
		
		movl $0, vindex
		for_cript:
			movl vindex, %ecx
			cmp lungCuv, %ecx
			je afisare_cr
			
			lea cuv, %edi
			lea numere, %esi
			
			mov $0, %eax
			movb (%edi, %ecx, 1), %al
			movl (%esi, %ecx, 4), %ebx
			
			
			//////////////////////
			xor %ebx, %eax
			/////////////////////
			
			
			push %eax
			push $formatPrintf1
			call printf
			pop %edx
			pop %edx
			
		incl vindex
		jmp for_cript
		
		afisare_cr:
			push endl
			push $formatPrintf
			call printf
			pop %edx
			pop %edx
		
		jmp et_exit
	
	
	decripteaza:
	
		
	
		movl $0, i
		movl $2, vindex
	for_pla:
		movl vindex, %ecx
		cmp $22, %ecx
		je cont4
		
		lea cuv, %edi
		movb (%edi, %ecx, 1), %al
		
		
		cmp $0, %eax
		je cont4
		
		cmp $57, %eax
		jle scade_48
		
		cmp $65, %eax
		jge scade_55
		
		scade_48:
			sub $48, %eax
			jmp trans_b
			
		scade_55:
			sub $55, %eax
		
		trans_b:
		
		mov %eax, %ebx
		
		inc %ecx
		movb (%edi, %ecx, 1), %al
		dec %ecx
		
		cmp $0, %eax
		je cont4
		
		cmp $57, %eax
		jle scade_48b
		
		cmp $65, %eax
		jge scade_55b
		
		scade_48b:
			sub $48, %eax
			jmp formare
			
		scade_55b:
			sub $55, %eax
			
				
		
		formare:
		
		mull b
		push %eax
		mov %ebx, %eax
		mull a
		mov %eax, %ebx
		pop %eax
		add %ebx, %eax
		
		
		movl i, %ecx
		lea v, %esi
		movl %eax, (%esi, %ecx, 4)
		
	incl i	
	addl $2, vindex
	jmp for_pla

		
	cont4:
	movl i, %eax
	movl %eax, lungCuv	
	movl $0, vindex
	
	for_decr:
		movl vindex, %ecx
		cmp lungCuv, %ecx
		je afisare_decr
		
		lea v, %edi
		lea numere, %esi
		
		mov (%edi, %ecx, 4), %eax
		movl (%esi, %ecx, 4), %ebx
		
		
		//////////////////////
		xor %ebx, %eax
		/////////////////////
		push %eax
		push $formatPrintf
		call printf
		pop %edx
		pop %edx
			
	incl vindex
	jmp for_decr	
	
	afisare_decr:
		push endl
		push $formatPrintf
		call printf
		pop %edx
		pop %edx
	
	et_exit:
		
		pushl $0
		call fflush
		addl $4, %esp
	
		movl $1, %eax
		movl $0, %ebx
		int $0x80
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
