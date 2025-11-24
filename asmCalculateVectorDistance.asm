section .text
bits 64
default rel
global asmCalculateVectorDistance

asmCalculateVectorDistance:
    mov r10, rcx               ; n (size)
    mov r11, rdx               ; x_1
    mov r12, r8                ; x_2
    mov r13, r9                ; y_1
    mov r14, [rsp + 40]        ; y_2
    mov r15, [rsp + 48]        ; z (result)
    xor rbx, rbx               ; for indexing

loop_start:
    ; loading values into registers
    movsd xmm3, [r11+rbx]  
    movsd xmm4, [r12+rbx]  
    movsd xmm5, [r13+rbx]  
    movsd xmm6, [r14+rbx]  

    ; calculating euclidean distance
    subsd xmm4, xmm3  
    mulsd xmm4, xmm4    
    subsd xmm6, xmm5    
    mulsd xmm6, xmm6    
    addsd xmm4, xmm6    
    sqrtsd xmm4, xmm4   
    
    ; storing result in z
    movsd [r15+rbx], xmm4 

    ; loop dec + indexing
    add rbx, 8
    dec r10
    jnz loop_start      
    ret