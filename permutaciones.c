#include <stdio.h>
#include <stdlib.h>

/*Author: Sebastián Fuentes Arteaga 
  email:  sefuar210@hotmail.com*/

//cuenta cantidad de digitos del numero n
int cantDigitos(int n){
    int cDig = 0;
    while(n > 0){
        cDig = cDig +1;
        n = (int)n/10;
    }
    return cDig;
}
//muestra en pantalla el numero del arreglo A
void imprimir(int A[], int size){
    int i = 0;
    printf("\t>");
    for (int i = 0; i < size; ++i){
        printf("%d", A[i]);
    }
    printf("\n");
}

//Calcula las combinaciones posibles de un numero
int combPosibles(int digitos){
    if(digitos == 0)
        return 1;
    else
        return digitos * combPosibles(digitos -1);
}

void intercambiar (int *p1, int *p2){
    int aux;
    aux = *p1;
    *p1 = *p2;
    *p2 = aux;
}

//invierte el numero contenido en A[]
void invertir(int A[], int size){
    int i = 0;
    int j = size-1;

    while(j>=i){
        intercambiar(&A[i], &A[j]);
        i++;
        j--; 
    }
    imprimir(A, size);
}

void permutar (int A[], int size, int cp){//cp: combinaciones posibles
    int comb = 1;
    int i = 0;
    int j = 1;
    int c;

    printf("-----Permutaciones-----\n");

    while(comb <= cp/2){

        imprimir(A, size);
        
        int aux[size];
        for(c = 0; c < size; c++){
            aux[c] = A[c];
        }
        invertir(aux, size);
        intercambiar(&A[i], &A[j]);
        
        i++; j++;
        if(j%size == 0){
            j = 0;
        }
        else if(i%size == 0){
            i = 0;
        }
        comb++;
    }
}

void pasarAArreglo(int size, int num){
    int A[size];
    int i = size-1;
    int resto;
    for(i; i >= 0; i--){
        resto = num%10;
        num = num/10;
        A[i]=resto;
    }
    permutar(A, size, combPosibles(size));
}

void main(){

    int n, digitos, i = 0;
    printf("*0 para terminar la ejecución*\n");
    do{
        printf(">");
        scanf("%d",&n);
        pasarAArreglo(cantDigitos(n), n);
        i++;
    }while(n!=0);

}