#include <stdio.h>
#include <stdlib.h>

/*
//////////////////////////////////////TASKS///////////////////////////////////////////
1. menu precisa ser formatado;
2. descobrir como escrever em arquivo;
3. criar structs para empresa e pessoa;
4. criar structs para plantas energéticas;
5. trabalhar com a função main e prepará-la para receber demais funcionalidades;
6.
*/

typedef struct{
    //insert caracteristics of new type name.
} name;

int texttonum();
int verificadorcpf();
int verificadorcnpj();
float elevator(float, int);
int cpfchecker();
int menu();
int main(){
    int somefuck;
    printf("INICIALIZANDO...")
    while(somefuck < 8){
        somefuck = menu();
        switch(somefuck){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
        }
    }
    printf("OBRIGADO POR USAR NOSSO PROGRAMA.")
    return 0;
}
int menu(){
    int select;
    printf("1. ahahaha!\n");
    printf("2. ohohohoho!\n");
    printf("3. ihihihi\n");
    printf("4. megakek\n");
    printf("5. somestuff\n");
    printf("6. ohbrother\n");
    printf("7. nayfockenwayer\n");
    printf("8. nigerundaio!\n");
    printf("9. smokey!\n");
    printf("seleção: ");
    scanf("%d", &select);
    return select
}
int texttonum(char numonlytext[]){ /*NUMber ONLY TEXT -> Um texto composto somente por números!*/
    int trulen = sizeof(numonlytext)/sizeof(numonlytext[0]);
    int trunumber, buffer, failflag = 0, negflag = 0, i, negi;
    if(numonlytext[0] == '-'){
        negflag = 1;
    }
    if(negflag == 1){
        negi = trulen -1;
        for(i = 1; i <= trulen -1; i++){
            negi -= 1;
            buffer = (int)numonlytext[i] - (int)'0';
            if(buffer< 0 || buffer > 9){ //oh shit, we got a non-number!
                failflag = 1; // raise them failflaggers, boyos
            }
            else{
                trunumber += buffer * elevator(10, negi);
            }
        }
    }
    else{
        negi = trulen;
        for(i = 0; i <= trulen -1; i++){
            negi -= 1;
            buffer = (int)numonlytext[i] - (int)'0';
            if(buffer< 0 || buffer > 9){ //oh shit, we got a non-number!
                failflag = 1; // raise them failflaggers, boyos
            }
            else{
                trunumber += buffer * elevator(10, negi);
                }
        }
    }
    if(failflag == 1){ //if this shit failed, print failflag.
        printf("Failflag detected. There's something wrong."); //e nao retorna nada. Espero que isso não me dê nenhum erro...
    }
    else{
        if(negflag == 1){ //handles negativity
            return -trunumber;
        }
        else{
            return trunumber;
        }
    }
}
int cpfchecker(int cpf[]){//checa se o cpf atende à estrutura 9 digitos + 2 verificadores, 1 caracter por espaço
    int trulen = sizeof(cpf)/sizeof(cpf[0]), i, failflag;
    failflag = 0;
    for(i = 0; i <= trulen - 1; i++){
        if(cpf[i] > 9 || cpf[i] < 0){
            failflag = 1;
        }
    }
    return failflag;
}
int verificadorcnpj(int cnpj[]){ //Mesma coisa do verificador de cpf. É bom que o usuário nao coloque caracteres inválidos
                                 //Ou hei de comê-lo com garfo, faca e farinha.
}
int verificadorcpf(int cpf[]){ /* Imagina-se que aqui o cpf conterá todos os 9 digitos mais 2 verificadores, tot 11 num*/
    int trulen = (sizeof(cpf)/ sizeof(cpf[0])), i, j;
    int invertcpf[trulen -2], verifier[2] = {cpf[trulen - 2], cpf[trulen - 1]}, v1, v2;
    j = trulen;
    for(i = 0; i <= trulen - 1; i++){
        j -= 1;
        cpf[i] = invertcpf[j];
    }
    for(i = 0; i <= trulen - 1; i++){
        v1 += invertcpf[i] *(9 - (i%10));
        v2 += invertcpf[i] *(9 - ((i+1)%10));
    }
    v1 = (v1%11)%10;
    v2 += v1*9;
    v2 = (v2%11)%10;

    if(v1 == verifier[1] && v2 == verifier[2] && trulen == 11){
        return 1;
    }
    else
        return 0;
}

float elevator(float somenum, int somepot){ // retorna somenum^somepot. ex.: elevator(10, 2) retorna 100.
    float res; int i; //float para funcionar com somenum real.
    res = somenum;
    if(somepot == 0){
        res = 1;
    }
    else{
        for(i = 1; i < somepot; i++){
            res = res * somenum;
        }
    }
    return res;
}
