#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLIENTS "clientes.txt"
#define USINAS "usinas.txt"
#define CNTRCTS "contratos.txt"

void cadastracliente();
void cadastrausina();
void cadastracontrato();
int texttonum();
int verificadorcpf();
int verificadorcnpj();
int verificadornome(char[]);
float elevator(float, int);
int cpfchecker();
int menu();
void gravapessoa(pessoa);
void gravausina(usina);
void gravacontrato(contrato);
void contratohunter(int[], int[]);
void manhunter(int[]);
void usinahunter(int[]);

typedef struct{
    int cnpj[14];
    char nome[20];
    int data[3];
    float potencia;
} usina;

typedef struct{
    int cpf[11];
    char nome[20];
} pessoa;

typedef struct{
    int pessoa[11];
    int usina[14];
    int data[3];
    float potencia;
} contrato;

int menu(){
    int select;
    printf("1. Cadastrar Usina\n");
    printf("2. Cadastrar Consumidor\n");
    printf("3. Cadastrar Contrato\n");
    printf("4. Consultar Usinas\n");
    printf("5. Consultar Consumidores\n");
    printf("6. Excluir Usina\n");
    printf("7. Excluir Consumidor\n");
    printf("8. Encerrar Programa\n");
    printf("seleção: ");
    scanf("%d", &select);
    return select;
}

int texttonum(char numonlytext[]){ /*NUMber ONLY TEXT -> Um texto composto somente por números!*/ //atoi(), kekeke.
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

int generalchecker(int cpf[]){//checa se o vetor possui somente um algoritmo unitario por espaço, o formato padrão cpf/cnpj.
    int trulen = sizeof(cpf)/sizeof(cpf[0]), i, failflag;
    failflag = 0;
    for(i = 0; i <= trulen - 1; i++){
        if(cpf[i] >= 10 || cpf[i] <= -1){
            failflag = 1;
        }
    }
    if(failflag == 1){
        return 0;
    }
    else{
        return 1;
    }
}

int verificadorcnpj(int cnpj[]){ //Mesma coisa do verificador de cpf. É bom que o usuário nao coloque caracteres inválidos
                                 //Ou hei de comê-lo com garfo, faca e farinha.
    int i, j, v[2];
    int invertcnpj[14]; //para o cnpj, o vetor tipo invert DEVE conter pelo menos o primeiro digito verificador
    j = 14;             // para fins de simplicidade, eu incluo logo os dois.
    for(i = 0; i <= 13; i++){//inverte cnpj para correto funcionamento do algoritmo
        j -= 1; // diminui j ANTES de realizar cálculo
        invertcnpj[i] = cnpj[j]; // 0 - 13; 1 - 12;...; 13 - 0
    }
    v[0] = v[1] = 0;
    int z = 2;
    for(i = 2; i <= 13; i++){//calcula primeiro digito. Loop começa após verificadores
        if(z == 10){ //garante loop {2, 3,...,9,2,3,...,9,...}.
            z = 2;
        }
        v[0] += invertcnpj[i]*z; //d12*2 + d11*3 + d10*4 +...+ d5*9 + d4*2 + ...
        z += 1;
    }

    v[0] = ((11 - ((v[0]%11)%10))%11);

    z = 2;
    for(i = 1; i <= 13; i++){//calcula segundo digito. Loop usa um dos verificadores.
        if(z == 10){
            z = 2;
        }
        v[1] += invertcnpj[i]*z;
        z += 1;
    }

    v[1] = ((11 - ((v[1]%11)%10))%11);
    printf("v0 = %d v1 = %d", v[0], v[1]);

    if(v[0] == invertcnpj[1] && v[1] == invertcnpj[0]){ //se o cálculo gerar digitos IGUAIS aos providos, então
        return 1; //é um cnpj válido. "Where 1 equals true, and truth is good!"
    }
    else{
        return 0; //senão, dê um código de erro.
    }
}

int verificadorcpf(int cpf[]){ /* Imagina-se que aqui o cpf conterá todos os 9 digitos mais 2 verificadores, tot 11 num*/
    int baselength = 11, i, v[2] = {0 , 0};
    for(i = 0; i <= 8; i++){
        v[0] += cpf[i]*(10 - i);
        v[1] += cpf[i]*(11 - i);
    }
    v[0] = ((11 - ((v[0]%11)%10))%11);
    v[1] = ((11 - ((v[1]%11)%10))%11);
    printf("v0 = %d, v1 = %d", v[0], v[1]);

    if(v[0] == cpf[9] && v[1] == cpf[10]){
        return 1;
    }
    else{
        return 0;
    }
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

int verificadornome(char nome[]){ //verifica se o nome tem pipe ("|"). Se tiver, eh um nome invalido.
    int trulen = sizeof(nome)/sizeof(nome[0]); //isso aqui serve para acomplar nomes de tamanhos variados
    int i, j; //os clássicos
    int failflag = 0;
    for(i=0; i<= trulen - 1; i++){
        if((int)nome[i] == 124){
            failflag = 1;
            printf("Bad char. Raised faiflag");

        }
    }
    if(failflag == 0){
        return 1;
    }
    else{
        return 0;
    }
}

void cadastrausina(){
    system("clear");
    usina itaipu;
    int i, isok;
    printf("Programa de cadastramento de usina iniciado!\n");
    printf("Insira nome da usina:\n");
    scanf("%s", itaipu.nome);
    printf("Insira cnpj da usina seguindo essa formatação: 1 2 3 4 5 6 7 8 9 1 2 3 4 5\n");
    for(i = 0; i <= 13; i++){
        scanf("%d", &itaipu.cnpj[i]);
    }
    printf("Insira data de inicio de funcionamento seguindo essa formatação: dd mm aaaa.\n");
    for(i = 0; i <= 2; i++){
        scanf("%d", &itaipu.data[i]);
    }
    printf("Insira capacidade de geração energetica em MW.");
    scanf("%f", &itaipu.potencia);
    //com dados coletados, vamos verificá-los :>
    printf("verificando formatacao do cnpj\n");
    isok = generalchecker(itaipu.cnpj);
    if(isok == 1){
        printf("verificando cnpj\n");
        isok = verificadorcnpj(itaipu.cnpj);
    }
    if(isok == 1){
        printf("verificando nome\n");
        isok = verificadornome(itaipu.nome);
    }
    //system("clear");
    //verificação feita
    if(isok == 1){ //se tudo está ok ("isok is True"):
        printf("Dados verificados com sucesso!\n\
        Cadastrando usina..\n");
        gravausina(itaipu);
    }
    else{ //senao:
        printf("Algo errado. Dados não cadastrados...\n Voltando ao menu. \n");
    }


}

void cadastracliente(){
    system("clear"); //limpa a tela :>
    printf("\n");
    int isok, i;

    //coleta de dados!
    printf("Programa de cadastramento de consumidor iniciado!\n");
    pessoa cliente;
    printf("Insira nome da pessoa. Favor n usar espacos.\n");
    //fgets(cliente.nome, 20, stdin);
    scanf("%s", cliente.nome);
    printf("Insira cpf da pessoa segundo essa formatação: 1 2 3 4 5 6 7 8 9 1 2\n");
    for(i = 0; i <= 10; i++){
        scanf("%d", &cliente.cpf[i]);
    }

    //com dados coletados, vamos verificá-los :>
    printf("verificando formatacao do cpf\n");
    isok = generalchecker(cliente.cpf);
    if(isok == 1){
        printf("verificando cpf\n");
        isok = verificadorcpf(cliente.cpf);
    }
    if(isok == 1){
        printf("verificando nome\n");
        isok = verificadornome(cliente.nome);
    }

    //system("clear");
    //verificação feita
    if(isok == 1){ //se tudo está ok ("isok is True"):
        printf("Dados verificados com sucesso!\n\
        Cadastrando cliente...\n");
        gravapessoa(cliente);
    }
    else{ //senao:
        printf("Algo errado. Dados não cadastrados...\n Voltando ao menu. \n");
    }
}

void cadastracontrato(){ //basicamente, ele so pode registrar contratos entre entes reconhecidos e registrados.
    system("clear");
    contrato control;
    printf("Registro de Contrato Iniciado!\n");
    //coleta de dados basica
    printf("Insira cpf do contratante seguindo a formatacao 1 2 3 4 5 6 7 8 9 1 2\n");
    for(int i = 0; i <= 10; i++){
        scanf("%d", &control.pessoa[i]);
    }
    printf("Insira cnpj do contratado seguindo a formatacao 1 2 3 4 5 6 7 8 9 1 2 3 4 5\n");
    for(int i = 0; i <= 13; i++){
        scanf("%d", &control.usina[i]);
    }
    printf("insira data de inicio do contrato seguindo a formatacao dd mm aaaa\n");
    for(int i = 0; i <= 2; i++){
        scanf("%d", &control.data[i]);
    }
    printf("insira a potencia contratada\n");
    scanf("%f", &control.potencia);

    //dados coletados, hora de avaliar os danados.
        //manhunter(control.pessoa);

}

void gravapessoa(pessoa consumidor){
    int i;
    FILE *clientes;
    clientes = fopen(CLIENTS, "a");
    for(i = 0; i <= 10; i++){
        fprintf(clientes, "%d", consumidor.cpf[i]);
    }
    fprintf(clientes, "|");
    fprintf(clientes, "%s", consumidor.nome);
    fprintf(clientes, "|\n");
    fclose(clientes);
}

void gravausina(usina trigarganta){
    int i;
    FILE *usinas;
    usinas = fopen(USINAS, "a");
    for(i = 0; i <= 10; i++){
        fprintf(usinas, "%d", trigarganta.cnpj[i]);
    }
    fprintf(usinas, "|%s|%d %d %d|%f|\n", trigarganta.nome, trigarganta.data[0], trigarganta.data[1], trigarganta.data[2],trigarganta.potencia);
    fclose(usinas);
}

void gravacontrato(contrato acordo){

}

void contratohunter(int cpf[], int cnpj[]){

}
void manhunter(int cpf[]){
    FILE *handler;
    handler = fopen(CLIENTS, "at");
    fclose(handler);
}
void usinahunter(int cnpj[]){

}


