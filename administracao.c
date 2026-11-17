#include "header.h"

void administracao(void) {
    int opcao;

    do {
        system("clear"); //apenas no mac
        printf("\n=== PERFIL ADMINISTRACAO ===\n");
        printf("1 - Admitir Novo Utente\n");
        printf("2 - Listar Utentes Ativos\n");
        printf("3 - Listar Utentes com Alta\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                printf("A abrir admissao de utente...\n");
                break;
            case 2:
                printf("A listar utentes ativos...\n");
                break;
            case 3:
                printf("A listar utentes com alta...\n");
                break;
            case 0:
               //aqui vai apenas voltar ao menu principal, esse é o motivo pelo qual n existe printf
                break;
            default:        
                printf("Opção inválida. Tente novamente.\n");
        }
    } while(opcao != 0);
};