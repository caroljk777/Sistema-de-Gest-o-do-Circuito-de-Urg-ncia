#include "header.h"

void menuPrincipal(void) {
    int opcao;

    do {
        system("clear"); // para limpar o ecra (só funciona no meu mac, tens de alterar) 
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Administração\n");
        printf("2 - Enfermagem\n");
        printf("3 - Médico\n");
        printf("4 - Gestão\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                administracao(); // Entra no ficheiro administracao.c
                break;
            case 2:
                enfermagem();
                break;
            case 3:
                medico();
                break;
            case 4:
                gestao();
                break;
            case 5:
                printf("Final de turno, a sair..\n");
                break;
            default:        
                printf("Opção inválida. Tente novamente.\n");
        }
    } while(opcao != 5);
}