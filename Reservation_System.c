#include <stdio.h>
#include <stdbool.h>

#define NUM_MESAS 4
#define MAX_SIZE 10
#define numMaxHoras 10

int fim = 0;
int inicio = 0;
int fila[MAX_SIZE];

typedef struct {
    int ocupacao;
    int hora_inicio;
} Mesa;

void qstore(int quant) {
    if (fim == MAX_SIZE) {
        printf("Fila cheia.\n");
        return;
    }
    fila[fim] = quant;
    fim++;
}

int qretrieve() {
    if (inicio == fim) {
        return 1;
    }
    inicio++;
    
    return fila[inicio - 1];
}

void printMesas(Mesa mesas[], int hora, int fila[]) {
    int i = inicio;
    printf("----------\nFila:");
    while (i < fim) {
        printf("%d-", fila[i]);
        i++;
    }
    printf("\nHora Atual: %d\n----------\n\n", hora);
    i = 0;
    while (i < 4) {
        printf("Mesa %d: %d\n", i + 1, mesas[i].ocupacao);
        i++;
    }
}

void updateHorasMesas(Mesa mesas[], int hora) {
    int i = 0;
    while (i < 4) {
        if (mesas[i].ocupacao != 0 && (hora >= mesas[i].hora_inicio + 2)) {
            mesas[i].hora_inicio = -1;
            mesas[i].ocupacao = 0;
        }
        i++;
    }
}

void Mesas(Mesa mesas[], int *hora_atual, int pessoas, int hora_chegada) {
    bool mesa_atribuida = false;
    int i = 0;

    if (hora_chegada < *hora_atual) {
        printf("Que horas chegaram?\n");
        scanf("%d", &hora_chegada);
        Mesas(mesas, hora_atual, pessoas, hora_chegada);
        return;
    }

    *hora_atual = hora_chegada;
    updateHorasMesas(mesas, *hora_atual);

    
    while (inicio < fim) {
        int grupo = fila[inicio];
        mesa_atribuida = false;
        for (i = 0; i < 4 && !mesa_atribuida; i++) {
            if (mesas[i].ocupacao == 0) {
                mesas[i].ocupacao = grupo;
                mesas[i].hora_inicio = *hora_atual;
                mesa_atribuida = true;
                inicio++;
            }
        }

        if (!mesa_atribuida) {
            break;
        }
    }

    mesa_atribuida = false;
    i = 0;

    while (i < 4 && !mesa_atribuida) {
        if (mesas[i].ocupacao == 0) {
            mesas[i].ocupacao = pessoas;
            mesas[i].hora_inicio = *hora_atual;
            mesa_atribuida = true;
        }
        i++;
    }

    if (!mesa_atribuida) {
        qstore(pessoas);
    }
}
void mesasFila(Mesa mesas[], int *hora_atual) {
    while (inicio < fim) {
        int grupo = fila[inicio];
        bool mesa_atribuida = false;
        for (int i = 0; i < 4 && !mesa_atribuida; i++) {
            if (mesas[i].ocupacao == 0) {
                mesas[i].ocupacao = grupo;
                mesas[i].hora_inicio = *hora_atual;
                mesa_atribuida = true;
                inicio++;
            }
        }
        if (!mesa_atribuida) {
            break;
        }
    }
}

int main() {
    Mesa mesas[4] = {0};
    int hora = 14;
    int pessoas, hora_chegada;  
    while (hora < 23) {
        printMesas(mesas, hora, fila);    
        printf("\nQuantas pessoas chegaram?\n");
        scanf("%d", &pessoas);
        if (pessoas == 0) {
            printf("Que horas chegaram?\n");
            scanf("%d", &hora_chegada);
            Mesas(mesas, &hora, 0, hora_chegada);
            continue;
        }
        printf("Que horas chegaram?\n");
        scanf("%d", &hora_chegada);
        Mesas(mesas, &hora, pessoas, hora_chegada);
        mesasFila(mesas, &hora);
    }
    return 0;
}
