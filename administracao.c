#include "header.h"

//Vetor que guarda até 25 utentes e o contador de quantos já lá estão
static Utente listaUtentes[25];
static int totalUtentes = 0;

void administracao(void) {
    int opcao;

    do {
        system("clear"); //apenas no mac- colocar cls dps no codeblocks
        printf("\n**********************************************\n");
        printf("\n**********************************************\n");
        printf("\n*********** PERFIL ADMINISTRACAO *************\n");
        printf("\n**********************************************\n");
        printf("\n**********************************************\n");
        printf("1 - Admitir Novo Utente\n");
        printf("2 - Listar Utentes Ativos\n");
        printf("3 - Listar Utentes com Alta\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                printf("A abrir admissao de utente...\n");
                if (totalUtentes < 25) {
                    int novoId;
                    printf("Digite o ID unico do utente (ex: Numero SNS):\n");
                    scanf("%d", &novoId);

                    //verificação se o ID já existe
                    int repetido = 0;
                    for(int i = 0; i < totalUtentes; i++) {
                        if(listaUtentes[i].id == novoId) {
                            repetido = 1;
                        }
                    }
                    if(repetido == 1) {
                        printf("\n[ERRO]: Ja existe um utente com este ID.\n");
                    } else {
                        listaUtentes[totalUtentes].id = novoId;

                        printf("Digite o Nome Completo:\n");
                        scanf(" %[^\n]", listaUtentes[totalUtentes].nome);     //o espaço antes do % descarta o \n que ficou no buffer

                        printf("Digite a Idade:\n");
                        scanf("%d", &listaUtentes[totalUtentes].idade);

                        printf("Canal de Proveniencia (1-4):\n");
                        scanf("%d", &listaUtentes[totalUtentes].canal); //especificar o canal - 1 - sns 2- ambulancia 3 - referencia 
                                                                        //de medico do centro de saude 4 - iniciativa propria (switch case)

                        printf("Hora de admissao (HH MM):\n"); //mudar isto HH MM
                        scanf("%d %d", &listaUtentes[totalUtentes].hora, &listaUtentes[totalUtentes].minuto);

                        strcpy(listaUtentes[totalUtentes].estado, "Aguarda Triagem");
                        totalUtentes++;
                        printf("\nUtente admitido com sucesso! Estado: Aguarda Triagem");
                    }
                } else {
                    printf("\nVai ser reencaminhado para o hospital.\n");
                }
                {
                int continuar;
                printf("\n Digite 0 para voltar ao menu:");
                scanf("%d",&continuar);  
                }             //Criei a variavel continuar, para conseguit continuar
                break;
            case 2:
                printf("A listar utentes ativos...\n");
                {
                    int contador = 0;
                    for (int i = 0; i < totalUtentes; i++) {
                        if (strcmp(listaUtentes[i].estado, "Alta Medica") != 0) {
                            printf("ID: %d | Nome: %s | Hora de Entrada: %02d:%02d\n", listaUtentes[i].id, listaUtentes[i].nome, listaUtentes[i].hora, listaUtentes[i].minuto);
                            contador++;
                        }
                    }
                    if (contador == 0) {
                        printf("Nenhum utente ativo de momento.\n");
                    }
                }
                {
                    int continuar;
                    printf("\nDigite 0 para voltar ao menu:");
                    scanf("%d", &continuar);
                }
                
                break;
            case 3:
                printf("A listar utentes com alta...\n");
                {
                    int contador = 0;
                    for(int i = 0; i < totalUtentes; i++) {
                        if(strcmp(listaUtentes[i].estado, "Alta Medica") == 0){
                            printf("ID: %d | Nome: %s | Hora de Entrada: %02d:%02d\n", listaUtentes[i].id, listaUtentes[i].nome, listaUtentes[i].hora, listaUtentes[i].minuto);
                            contador++;
                        }
                    }
                    if (contador == 0) {
                        printf("Nenhum utente com alta registado.\n");
                    }
                }
                {
                    int continuar;
                    printf("\nDigite 0 para voltar ao menu");
                    scanf("%d", &continuar);
                }
                break;
            case 0:
               //aqui vai apenas voltar ao menu principal, esse é o motivo pelo qual n existe printf
                break;
            default:        
                printf("Opção inválida. Tente novamente.\n");
        }
    } while(opcao != 0);
}