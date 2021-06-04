#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct sEntrada
{
    char nome[100], sexo[3], bairro[100], resultado[3], cpf[15];
    char valido[4];
    int idade, dia, mes, ano;

}Entrada;

void id(Entrada *d)
{
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    if ((d->mes) > (tm.tm_mon + 1))
    {
        d->idade = (tm.tm_year + 1900) - (d->ano) - 1;
    }
    else if ((d->mes) == (tm.tm_mon + 1))
    {

        if ((d->dia) > (tm.tm_mday))
        {
            d->idade = (tm.tm_year + 1900) - (d->ano) - 1;
        }
        else
        {
            d->idade = (tm.tm_year + 1900) - (d->ano);
        }
    }
    else
    {
        d->idade = (tm.tm_year + 1900) - (d->ano);
    }
}

int saudacao()
{
    int menu;

    system("cls||clear");

    printf("---------------------------------------------\n");
    printf("              #TESTE PARA COVID#             \n");
    printf("\nMENU DE OPCOES:\n");
    printf("1-Cadrastrar novos testes.\n");
    printf("2-Consultar teste\n");
    printf("3-Cancelar teste\n");
    printf("4-Salvar Informacoes em arquivo\n");
    printf("5-Visualizar informacoes de testes realizados\n");
    printf("6-Relatorio de testes realizados\n");
    printf("0-Sair\n");
    printf("---------------------------------------------\n");

    printf("Digite a opcao: ");
    scanf("%i", &menu);
    getchar();

    system("cls||clear");

    return menu;
}

void printar(Entrada d)
{
    printf("%s - %s - %s - %i anos\n", d.nome, d.sexo, d.cpf, d.idade);
    
    if(d.mes<10){
        printf("%i/0%i/%i\n", d.dia, d.mes, d.ano);
    }else{
        printf("%i/%i/%i\n", d.dia, d.mes, d.ano);
    }
    
    puts(d.bairro);
    printf("Resultado do teste: %s\n", d.resultado);
    printf("Valido: %s", d.valido);
}

int qtdinfectados(Entrada d[], int qtdcadastros){
    int infectados;
    int i;
    
    infectados = 0;

    for(i=0;i<qtdcadastros;i++){
        if(d[i].resultado[0] == 'P' || d[i].resultado[0] == 'p'){
            infectados = infectados + 1;
        }
    }

    return infectados;
}

int jovensinfectados(Entrada d[], int total){
    int i;
    int jovinfectados;

    jovinfectados = 0;

    for(i=0;i<total;i++){
        if(d[i].idade < 20 && (d[i].resultado[0] == 'P' || d[i].resultado[0] == 'p')){
            jovinfectados = jovinfectados + 1;
        }
    }

    return jovinfectados;
}

int idososinfectados(Entrada d[], int total){
    int i;
    int idosinfectados;

    idosinfectados = 0;

    for(i=0;i<total;i++){
        if(d[i].idade >= 60 && (d[i].resultado[0] == 'P' || d[i].resultado[0] == 'p')){
            idosinfectados = idosinfectados + 1;
        }
    }

    return idosinfectados;
}

float percent(int x, int total){
    float result;
    result = ((x*1.0)/total)*100;
    return result;
}

int main()
{
    int nt, i, num, menu, total;
    int qtd_infectados, qtd_nao_infectados, jov_infectados, adult_infectados, idos_infectados;
    char name[100], val[4], s[4];
    Entrada d[100];

    total=0;
    nt = -1;

    do
    {
        system("cls||clear");
        menu=saudacao();
        system("cls||clear");

        switch (menu)
        {

            case 1:

                printf("Qual a quantidade de novos testes que deseja cadrastrar: ");
                scanf("%i", &nt); //quantidade de testes
                getchar();


                if (nt > 0)
                {
                    for (i = total; i < (nt + total); i++)
                    {
                        strcpy(d[i].valido, "SIM");

                        system("cls||clear");

                        printf("Teste(%i)\n", i+1);
                        printf("Nome Completo: ");
                        gets(d[i].nome);
                        printf("CPF: ");
                        gets(d[i].cpf);
                        printf("Sexo [F/M]:");
                        gets(d[i].sexo);
                        strupr(d[i].sexo);
                        printf("Data de Nascismento:\nDia:");
                        scanf("%i", &(d[i].dia));
                        getchar();
                        printf("Mes: ");
                        scanf("%s", s);
                        getchar();

                        d[i].mes=atoi(s);

                        printf("Ano: ");
                        scanf("%i", &(d[i].ano));
                        getchar();
                        printf("Bairro: ");
                        gets(d[i].bairro);
                        printf("Resultado do teste [P/N]:");
                        gets(d[i].resultado);
                        strupr(d[i].resultado);
                        id(&d[i]);
                    }
                        total+=nt;
                }
                else
                {
                    puts("Eh necessario realizar pelo menos 1 cadastro!");
                }
            break;

            case 2:
                if (nt != -1)
                {
                    printf("Digite um nome: ");
                    gets(name);

                    for (i = 0; i < nt; i++)
                    {
                        if (strcmp(name, d[i].nome) == 0)
                        {
                            break;
                        }
                    }

                    if (strcmp(name, d[i].nome) == 0)
                    {
                        printar(d[i]);

                        printf("\nAperte |ENTER| para voltar ao menu principal");
                    }
                    else
                    {
                        printf("Nome nao encontrado.\n");
                    }
                }
                else
                {
                    printf("Nenhum valor cadrastado\n");
                }

                getchar(); //esperar digitar enter
            break;

            case 3:
                if (nt != -1)
                {
                    puts("Digite o numero do teste que deseja cancelar: ");
                    scanf("%d", &num);

                    getchar();

                    num--;

                    printar(d[num]);

                    printf("\n------------------------------------------------\n");
                    puts("Deseja realmente cancelar esse teste? [SIM/NAO]");
                    gets(val);
                    
                    strupr(val);
                    
                    if(strcmp(val, "SIM") == 0)
                    {
                        strcpy(d[num].valido, "NAO");
                        printf("\n\n\tEsse teste foi cancelado com sucesso!\n");
                        printf("\t-----------------------------------------\n");
                        printar(d[num]);
                        printf("\nAperte |ENTER| para voltar ao menu principal");
                    }
                    else
                    {
                        puts("O teste NAO foi cancelado!");
                    }
                }
                else
                {
                    printf("Nenhum valor cadrastado\n");
                }

                getchar();

            break;

            case 4:
                for(i=0; i<nt; i++){
                    printar(d[i]);
                    getchar();
                }

            case 5:
                printf("---------------------------------------------\n");
                printf("Visualizando informacoes de %i testes cadastrados\n", total);
                printf("---------------------------------------------\n");
            
                for(i=0;i<total;i++){
                    printf("---------------------------------------------\n");
                    printf("Teste %i\n", i);
                    printf("---------------------------------------------\n");
                    printf("Nome: %s\n", d[i].nome);
                    printf("CPF: %s\n", d[i].cpf);
                    printf("Data de Nascimento: %i\n", d[i].dia);
                    printf("Idade: %i\n", d[i].idade);
                    printf("Sexo: %s\n", d[i].sexo);
                    printf("Bairro: %s\n", d[i].bairro);
                    printf("COVID-19: %s\n", d[i].resultado);
                    printf("Valido: %s\n", d[i].valido);
                    printf("---------------------------------------------\n");

                }

                getchar();

            break;
            
            case 6:
                
                qtd_infectados = qtdinfectados(d, total);

                qtd_nao_infectados = total - qtd_infectados;

                jov_infectados = jovensinfectados(d, total);
                idos_infectados = idososinfectados(d, total);

                adult_infectados = qtd_infectados - (jov_infectados + idos_infectados);



                printf("---------------------------------------------\n");
                printf("\tRELATORIO COVID-19\n");
                printf("---------------------------------------------\n");
                printf("Total de pessoas cadastradas: %i\n", total);
                printf("Pessoas nao infectadas: %i (%.2f%%)\n", qtd_nao_infectados, percent(qtd_nao_infectados, total));
                printf("Pessoas Infectadas: %i (%.2f%%)\n", qtd_infectados, percent(qtd_infectados, total));
                printf("\tJovens Infectados: %i (%.2f%% dos infectados)\n", jov_infectados, percent(jov_infectados, qtd_infectados));
                printf("\tAdultos Infectados: %i (%.2f%% dos infectados)\n", adult_infectados, percent(adult_infectados, qtd_infectados));
                printf("\tIdosos Infectados: %i (%.2f%% dos infectados)\n", idos_infectados, percent(idos_infectados, qtd_infectados));


                getchar();

            break;
        }

            

            
    }while (menu != 0);

    return 0;
}
