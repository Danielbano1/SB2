#include <stdio.h>
#define TAMANHO_LONG sizeof(long int)  // tamanho necessario para armazenar um endereco literal

typedef int (*funcp)(int x);

// union para pegar os bytes do endereco real
typedef union enderecoDiretoUnion
{
    long int endereco;
    unsigned char c [TAMANHO_LONG];

} endDiretoUnion;

int add(int x)
{
    return x + 1;
}


int main()
{
    // vetor com codigo de maquina da funcao foo2 usando call direto
    unsigned char codigo[] = {
   		0x55,                           // push   %rbp
   		0x48, 0x89, 0xe5,               // mov    %rsp,%rbp
   		0x48, 0xb8,                     // movabs %rax, endereço (8 bytes a seguir)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // endereço (8 bytes)
        0xff, 0xd0,                     // call   *%rax
   		0xc9,                           // leaveq
   		0xc3                            // retq
	};

    endDiretoUnion u;

    // salva endereço real de add
    u.endereco = (long int)add;

    // colocando endereco real de add no codigo no formato little endian
    for (int i = 0; i < sizeof(long int); i++)
        codigo[6+i] = u.c[i];
    
    // f armazena o endereco da funcao
    funcp f = (funcp)codigo;

    // chamando a funcao com parametro 10
    int i = (*f)(10);

    printf("%d\n", i);

    return 0;
}
