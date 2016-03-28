#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*Author: Sebastián Fuentes Arteaga 
  email:  sefuar210@hotmail.com*/

#define MAX_NUMEROS 100
#define TRUE 1
#define FALSE 0

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
void imprimir(int *A, int size){
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
//función que intercambia los valores a partir de sus punteros
void intercambiar (int *p1, int *p2){
    int aux;
    aux = *p1;
    *p1 = *p2;
    *p2 = aux;
}
//función que retorna la potencia de la base elevada al exponente ex 
int elevar(int base, int ex){
    int e = 0;
    int b = 1;
    while(e < ex){
        b = b * base;
        e++;
    }
    return b;
}
//A partir del arreglo A, se calcula el numero contenido completo a partir de los digitos en cada celda
int pasarANumero(int A[], int size){
    int suma = 0;
    int i;
    int ex = size-1;

    for (i = 0; i < size; ++i){
        suma = suma + A[i]*elevar(10, i);
        ex--;
    }
    return suma;
}
//funcion que retorna 1 si n es primo, y 0 si no lo es
int esPrimo(int n){
    int divisores = 0;
    int i = 1;

    for(i; i <= n; i++){
        if(n%i == 0){
            divisores++;
        }
    }
    if(divisores == 2)
        return TRUE;
    else
        return FALSE;
}

//invierte el numero contenido en A[] y revisa que sea primo.
int invertir(int A[], int size){
    int i = 0;
    int j = size-1;

    while(j>=i){
        intercambiar(&A[i], &A[j]);
        i++;
        j--; 
    }
    if(esPrimo(pasarANumero(A, size))){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int permutar (int A[], int size, int cp){//cp: combinaciones posibles
    int comb = 1;
    int i = 0;
    int j = 1;
    int c;

    while(comb <= cp/2){

        int aux[size];
        for(c = 0; c < size; c++){
            aux[c] = A[c];
        }
        invertir(aux, size);
        if(esPrimo(pasarANumero(A, size)) == FALSE || invertir(aux, size) == FALSE){
            return FALSE;//si una combinación no es prima, ya no busca mas combinaciones
        }
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
    return TRUE;//si todas las combinaciones son numeros primos retorna verdadero/1
}
//función que ingresa a un arreglo un numero, digito por digito, a partir de la última casilla
int pasarAArreglo(int size, int num){
    int A[size];
    int i = size-1;
    int resto;
    for(i; i >= 0; i--){
        resto = num%10;//se calcula el resto, y se ingresa desde la ultima casilla hasta la primera. Asi queda ordenado
        num = num/10;
        A[i]=resto;
    }
    return permutar(A, size, combPosibles(size));
}
//se descartan todos los numeros con digitos pares, ya que nunca será primo
int noTienePares(int n, int size){
    int resto;
    while(n > 0){
        resto = n%10;
        if(resto%2 == 0){
            return FALSE;
        }
        n = (int)n/10;
    }
    return TRUE;
}
//función que busca el primo anagramatico a partir del limite inferior, hasta la maxima potencia de 10 elevada a la cantidad de digitos de limInf
int buscarAnagramatico(int limInf){
    int cont = limInf;
    int limSup = elevar(10,cantDigitos(cont));
    while(cont < limSup){
        if(noTienePares(cont,cantDigitos(cont))){
            if(pasarAArreglo(cantDigitos(cont), cont) == TRUE)
                return cont;
        }
        cont++;
    }
    return FALSE;
}

void main(){

    int n, digitos, i = 0;
    int numeros[MAX_NUMEROS];
    int tam_arreglo;
    //se ingresan numeros y se van guardando en un arreglo, este proceso acaba cuando se ingresa un 0
    do{
        printf(">");
        scanf("%d",&n);
        numeros[i] = n;
        i++;
    }while(n!=0);

    tam_arreglo = i -1;//se revisan los numeros ingresados por pantalla, hasta llegar al 0.
    for (i = 0; i < tam_arreglo; i++){
        int primoAnagramatico = buscarAnagramatico(numeros[i]);
        printf("PRIMO ANAGRAMATICO: %d\n", primoAnagramatico);
    }
}