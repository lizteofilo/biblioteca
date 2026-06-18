#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/util.h"


int lerNumero()
{

    char entrada[50];
    int numero;


    while(1)
    {

        fgets(entrada,50,stdin);

        if(sscanf(entrada,"%d",&numero)==1)
        {
            return numero;
        }

        printf("Digite somente numeros: ");

    }

}

void lerTexto(char texto[], int tamanho)
{
    int valido;

    while(1)
    {
        valido = 1;

        fgets(texto, tamanho, stdin);

        // remove o \n do final
        texto[strcspn(texto, "\n")] = '\0';

        // verifica se ficou vazio
        if(strlen(texto) == 0)
        {
            valido = 0;
        }

        // verifica cada caractere
        for(int i = 0; texto[i] != '\0'; i++)
        {
            if(!isalpha(texto[i]) && texto[i] != ' ')
            {
                valido = 0;
                break;
            }
        }

        if(valido)
        {
            return;
        }

        printf("Digite apenas letras: ");
    }
}


 
void lerTitulo(char titulo[], int tamanho)
{


    while(1)
    {

        fgets(titulo,tamanho,stdin);

        if(strlen(titulo)>1)
        {

            titulo[strcspn(titulo,"\n")] = '\0';

            return;

        }


        printf("Campo obrigatorio: ");

    }


}



void pausar()
{

    printf("\nPressione ENTER para continuar...");
    getchar();

}