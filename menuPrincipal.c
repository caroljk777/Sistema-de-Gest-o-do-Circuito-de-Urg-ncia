#include <stdio.h>
#include "header.h"

int main(void){
    
    int opcao;

    do{
        printf("Menu Principal\n");
        printf("1 - Administração\n");
        printf("2 - Enfermagem\n");
        printf("3 - Médico\n");
        printf("4 - Gestão\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                printf("admin");
                break;
            case 2:
                printf("enfermagem");
                break;
            case 3:
                printf("medico");
                break;
            case 4:
                printf("gestao");
                break;
            case 5:
                printf("Final de turno, a sair..\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while(opcao != 5);


}
