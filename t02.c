#include <stdio.h>

typedef int (*funcp)(int x);

// union para pegar os bytes do offset
typedef union OffsetUnion
{
    int offset;
    unsigned char c [sizeof(int)];
} offsetUnion;

int add(int x)
{
    return x + 1;
}

int main()
{
    // vetor com codigo de maquina da funcao foo2
    unsigned char codigo[] = {0x55, 0x48, 0x89, 0xe5, 0xe8, 0x00, 0x00, 0x00, 0x00, 0xc9, 0xc3};

    offsetUnion u;

    // endereço de add
    unsigned char *ptr_add = (unsigned char *)&add;
    printf("%p\n", ptr_add);
    // endereco de proxima instrucao
    unsigned char *ptr_prox = &(codigo[9]);
    printf("%p\n", ptr_prox);

    // calculo de offset = add - proxima instrucao
    u.offset = (int)(ptr_add - ptr_prox);

    // colocando o offset em little endian no codigo
    for (int i = 0; i < sizeof(int); i++)
        codigo[5+i] = u.c[i];

    for (int i = 0; i < sizeof(codigo); i++)
        printf("%0x\n", codigo[i]);
    

    // f armazena o endereco da funcao
    funcp f = (funcp)codigo;

    // chamando a funcao com parametro 10
    int i = (*f)(10);

    printf("%d\n", i);

    return 0;
}
