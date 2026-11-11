#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_UTENTES 25

// --- Estrutura de Dados ---
typedef struct {
    int id;
    char nome[100];
    int idade;
    int canal_proveniencia; // 1 a 4
    int hora_admissao;
    int minuto_admissao;
    
    // Estado: 0=Aguardar Triagem, 1=Em Triagem, 2=Aguardar Consulta, 3=Em Consulta, 4=Sala Emergencia, 5=Sala Observacao, 6=Alta
    int estado; 
    
    // Sinais Vitais
    float temperatura;
    int spo2;
    int fc; // Frequência Cardíaca
    
    // Prioridade (1=Vermelho, 2=Laranja, 3=Amarelo, 4=Verde, 0=Não atribuído)
    int cor_prioridade;
    
    int ativo; // 1 se o registo existe, 0 se livre
} Utente;

Utente utentes[MAX_UTENTES];
int total_utentes = 0;

// --- Funções Auxiliares ---
const char* get_nome_estado(int estado) {
    switch (estado) {
        case 0: return "Aguardar Triagem";
        case 1: return "Em Triagem";
        case 2: return "Aguardar Consulta";
        case 3: return "Em Consulta";
        case 4: return "Sala Emergência";
        case 5: return "Sala Observação";
        case 6: return "Alta";
        default: return "Desconhecido";
    }
}

const char* get_nome_cor(int cor) {
    switch (cor) {
        case 1: return "Vermelho";
        case 2: return "Laranja";
        case 3: return "Amarelo";
        case 4: return "Verde";
        default: return "Sem Triagem";
    }
}

int id_existe(int id) {
    for (int i = 0; i < total_utentes; i++) {
        if (utentes[i].ativo && utentes[i].id == id) {
            return 1;
        }
    }
    return 0;
}

// --- DEGRAU 1: Perfil 1 (Administração) ---
void admitir_utente() {
    if (total_utentes >= MAX_UTENTES) {
        printf("\n[ERRO] Limite maximo de 25 atendimentos por turno atingido!\n");
        return;
    }

    Utente u;
    printf("\n--- ADMISSAO DE UTENTE ---\n");
    
    do {
        printf("Numero de Processo (ID unico): ");
        scanf("%d", &u.id);
        if (id_existe(u.id)) {
            printf("[ERRO] ID ja existe! Tente outro.\n");
        }
    } while (id_existe(u.id));

    getchar(); // Limpar buffer
    printf("Nome completo: ");
    fgets(u.nome, sizeof(u.nome), stdin);
    u.nome[strcspn(u.nome, "\n")] = 0; // Remover a quebra de linha

    printf("Idade: ");
    scanf("%d", &u.idade);

    do {
        printf("Canal de Proveniencia (1 a 4): ");
        scanf("%d", &u.canal_proveniencia);
    } while (u.canal_proveniencia < 1 || u.canal_proveniencia > 4);

    printf("Hora de Admissao (0-23): ");
    scanf("%d", &u.hora_admissao);
    printf("Minuto de Admissao (0-59): ");
    scanf("%d", &u.minuto_admissao);

    u.estado = 0; // Aguardar Triagem
    u.cor_prioridade = 0;
    u.temperatura = 0.0;
    u.spo2 = 0;
    u.fc = 0;
    u.ativo = 1;

    utentes[total_utentes] = u;
    total_utentes++;

    printf("\n[SUCESSO] Utente admitido com sucesso e a aguardar triagem!\n");
}

void listar_utentes_ativos() {
    printf("\n--- UTENTES ATIVOS (SEM ALTA) ---\n");
    int encontrou = 0;
    for (int i = 0; i < total_utentes; i++) {
        if (utentes[i].ativo && utentes[i].estado != 6) {
            printf("ID: %d | Nome: %s | Idade: %d | Estado: %s | Prioridade: %s\n",
                   utentes[i].id, utentes[i].nome, utentes[i].idade,
                   get_nome_estado(utentes[i].estado),
                   get_nome_cor(utentes[i].cor_prioridade));
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhum utente ativo no momento.\n");
}

void listar_utentes_alta() {
    printf("\n--- UTENTES COM ALTA ---\n");
    int encontrou = 0;
    for (int i = 0; i < total_utentes; i++) {
        if (utentes[i].ativo && utentes[i].estado == 6) {
            printf("ID: %d | Nome: %s | Prioridade Final: %s\n",
                   utentes[i].id, utentes[i].nome, get_nome_cor(utentes[i].cor_prioridade));
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhum utente com alta registada.\n");
}

// --- DEGRAU 2: Perfil 2 (Enfermagem e Triagem) ---
void realizar_triagem() {
    int idx_triagem = -1;
    
    // Procura o utente que deu entrada primeiro e está em "Aguardar Triagem" (estado 0)
    for (int i = 0; i < total_utentes; i++) {
        if (utentes[i].ativo && utentes[i].estado == 0) {
            idx_triagem = i;
            break; // O primeiro encontrado no vetor é o mais antigo na ordem de chegada
        }
    }

    if (idx_triagem == -1) {
        printf("\nNenhum utente a aguardar triagem.\n");
        return;
    }

    Utente *u = &utentes[idx_triagem];
    u->estado = 1; // Em Triagem

    printf("\n--- TRIAGEM DO UTENTE ---\n");
    printf("A triar Utente ID: %d - Nome: %s\n", u->id, u->nome);

    printf("Temperatura (Celsius): ");
    scanf("%f", &u->temperatura);
    printf("SpO2 (%%): ");
    scanf("%d", &u->spo2);
    printf("Frequencia Cardiaca (BPM): ");
    scanf("%d", &u->fc);

    // Algoritmo de Decisão de Triagem
    if (u->spo2 < 90 || u->temperatura >= 40.0 || u->fc > 140) {
        u->cor_prioridade = 1; // Vermelho
        u->estado = 4; // Encaminhado de imediato para a Sala de Emergência
        printf("\n[ALERTA CRITICO] Utente classificado como VERMELHO! Encaminhado para a Sala de Emergencia.\n");
    } else if (u->spo2 <= 94 || u->temperatura >= 39.0 || u->fc >= 120) {
        u->cor_prioridade = 2; // Laranja
        u->estado = 2; // Aguardar Consulta
        printf("\nUtente classificado como LARANJA. Encaminhado para a sala de espera da consulta.\n");
    } else if (u->temperatura >= 38.0 || u->fc >= 100) {
        u->cor_prioridade = 3; // Amarelo
        u->estado = 2; // Aguardar Consulta
        printf("\nUtente classificado como AMARELO. Encaminhado para a sala de espera da consulta.\n");
    } else {
        u->cor_prioridade = 4; // Verde
        u->estado = 2; // Aguardar Consulta
        printf("\nUtente classificado como VERDE. Encaminhado para a sala de espera da consulta.\n");
    }
}

// --- DEGRAU 3: Perfil 3 (Médico) ---
void chamar_medico() {
    int melhor_idx = -1;

    // Seleciona utente com estado 2 (Aguardar Consulta) com base na Hierarquia:
    // 1. Gravidade clínica (cor_prioridade: 1 é mais urgente que 4)
    // 2. Canal de proveniência (menor número assume preferência)
    // 3. Ordem de chegada (índice no vetor)
    for (int i = 0; i < total_utentes; i++) {
        if (utentes[i].ativo && utentes[i].estado == 2) {
            if (melhor_idx == -1) {
                melhor_idx = i;
            } else {
                Utente *atual = &utentes[i];
                Utente *melhor = &utentes[melhor_idx];

                if (atual->cor_prioridade < melhor->cor_prioridade) {
                    melhor_idx = i;
                } else if (atual->cor_prioridade == melhor->cor_prioridade) {
                    if (atual->canal_proveniencia < melhor->canal_proveniencia) {
                        melhor_idx = i;
                    }
                    // Em caso de empate na cor e canal, mantém o que chegou primeiro (menor índice)
                }
            }
        }
    }

    if (melhor_idx == -1) {
        printf("\nNenhum utente a aguardar consulta medica.\n");
        return;
    }

    Utente *u = &utentes[melhor_idx];
    u->estado = 3; // Em Consulta

    printf("\n--- CONSULTA MEDICA ---\n");
    printf("A chamar Utente ID: %d | Nome: %s | Prioridade: %s | Canal: %d\n", 
           u->id, u->nome, get_nome_cor(u->cor_prioridade), u->canal_proveniencia);

    int opcao_medica;
    printf("\nDecisao Medica:\n");
    printf("1. Dar Alta Clinica\n");
    printf("2. Transferir para Sala de Observacao (SO)\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao_medica);

    if (opcao_medica == 1) {
        u->estado = 6; // Alta
        printf("[SUCESSO] Alta clinica concedida ao utente %s.\n", u->nome);
    } else if (opcao_medica == 2) {
        u->estado = 5; // Sala de Observação
        printf("[SUCESSO] Utente %s transferido para a Sala de Observacao.\n", u->nome);
    } else {
        printf("[AVISO] Opcao invalida. O utente permanece em atendimento.\n");
    }
}

// --- DEGRAU 4: Perfil 4 (Gestão e Métricas) ---
void exibir_metricas() {
    if (total_utentes == 0) {
        printf("\nNenhum dado registado para apresentar metricas.\n");
        return;
    }

    int total_criticos = 0;
    int contagem_por_cor[5] = {0}; // 1:Vermelho, 2:Laranja, 3:Amarelo, 4:Verde

    for (int i = 0; i < total_utentes; i++) {
        if (utentes[i].ativo) {
            if (utentes[i].cor_prioridade >= 1 && utentes[i].cor_prioridade <= 4) {
                contagem_por_cor[utentes[i].cor_prioridade]++;
            }
            if (utentes[i].cor_prioridade == 1 || utentes[i].cor_prioridade == 2) {
                total_criticos++;
            }
        }
    }

    float pct_criticos = ((float)total_criticos / total_utentes) * 100.0;

    printf("\n--- ESTATISTICAS E METRICAS DO TURNO ---\n");
    printf("Total de atendimentos registados: %d / %d\n", total_utentes, MAX_UTENTES);
    printf("Percentagem de casos criticos (Vermelho + Laranja): %.2f%%\n", pct_criticos);
    printf("Distribuicao por Prioridade:\n");
    printf(" - Vermelho: %d\n", contagem_por_cor[1]);
    printf(" - Laranja:  %d\n", contagem_por_cor[2]);
    printf(" - Amarelo:  %d\n", contagem_por_cor[3]);
    printf(" - Verde:    %d\n", contagem_por_cor[4]);
}

// --- DEGRAU 1: Ciclo do-while e Switch-Case ---
int main() {
    int opcao;

    do {
        printf("\n=========================================\n");
        printf("    UEB-Sys - CIRCUITO DE URGENCIA      \n");
        printf("=========================================\n");
        printf("1. Admitir Novo Utente (Admin)\n");
        printf("2. Listar Utentes Ativos (Admin)\n");
        printf("3. Listar Utentes com Alta (Admin)\n");
        printf("4. Realizar Triagem (Enfermagem)\n");
        printf("5. Chamar Proximo Utente (Medico)\n");
        printf("6. Consultar Metricas do Turno (Gestao)\n");
        printf("0. Sair do Sistema\n");
        printf("-----------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                admitir_utente();
                break;
            case 2:
                listar_utentes_ativos();
                break;
            case 3:
                listar_utentes_alta();
                break;
            case 4:
                realizar_triagem();
                break;
            case 5:
                chamar_medico();
                break;
            case 6:
                exibir_metricas();
                break;
            case 0:
                printf("\nA encerrar o sistema UEB-Sys...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}