/******************************************************************************
                        ! ! !  Trabalho Final  ! ! !

  Ryan de Marque Sales;
  Mauro Diogo Fioravante Ferreira;
  Joâo Paulo Gonçalves Barros.
*******************************************************************************/


#include <string.h>
#include <stdio.h>

//Definicao das structs
struct Data
{
    int dia;
    int mes;
    int ano;
};

struct Cliente
{
    char nome_do_cliente[50];
    char telefone_do_cliente[15];
};

struct Animal
{
    struct Cliente cliente;
    char nome_do_animal[50];
    int especie;
    struct Data data_nascimento;
    char agressivo;
};

struct Servico
{
    int identificador;
    struct Data data_servico;
    struct Animal pet;
    int tipo_de_servico;
    char pago;

};

//Retorna se a data é valida ou não, 0 para caso for valida e 1 para caso não seja
int validarData(struct Data dataValidada){

    struct Data dAtual;

    printf("Informe a data de hoje (d/m/a): ");
    scanf(" %d/%d/%d",&dAtual.dia,&dAtual.mes,&dAtual.ano);

    //validar ano:
    if(dataValidada.ano <= dAtual.ano){
        //validar mês:
        if((dataValidada.ano == dAtual.ano && dataValidada.mes <= dAtual.mes) || (dataValidada.ano != dAtual.ano && dataValidada.mes <= 12)){
            //validar dia (mês comercial):
            if((dataValidada.mes == dAtual.mes && dataValidada.dia <= dAtual.dia) || (dataValidada.mes != dAtual.mes && dataValidada.dia <= 30)){   
                return 0;
            }
        }
    } 
    return 1;

}

//Retorna se o nome é valido ou não, 0 para caso for valido e 1 para caso não seja
int validarnome(char nome[50]){

    if(nome[0] == ' '){
        return 1;
    }

    else if(strlen(nome) < 4){
        return 1;
    }

    for (int i = 0; nome[i] != '\0'; i++)
    {
        if(nome[i] > 47 && nome[i] < 57){
            return 1;
        }
    }
    
    return 0;
}

//Retorna se o telefone é valido ou não, 0 para caso seja valido e 1 caso não seja
int validartelefone(char telefone[15]){
    if(telefone[0] != '0'){
        return 1;
    }
    else if(strlen(telefone) != 11 && strlen(telefone) != 12){
        return 1;
    }

    return 0;
}

//Cadastra o cliente retorna 0 caso seja um sucesso
int cadastrarclientes(struct Cliente *clientes,int cont){
    
    char nometemp[50],telefonetemp[15];



    while(1){
   
    printf("\e[1;1H\e[2J");    //comando para limpar o terminal

    printf("Por favor digite o nome do Cliente: ");
    scanf(" %[^\n]",nometemp);

    printf("\e[1;1H\e[2J");

    if(validarnome(nometemp) == 0){
        strcpy(clientes[cont].nome_do_cliente, nometemp);
        break;
    }

    else{
        printf("Nome invalido\n");
        getchar();
        getchar();
    }
    }

    while (1)
    {
            printf("\e[1;1H\e[2J");

            printf("Por Favor digite o telefone do Cliente: ");
            scanf(" %[^\n]",telefonetemp);

            printf("\e[1;1H\e[2J");

            if(validartelefone(telefonetemp) == 0){
                strcpy(clientes[cont].telefone_do_cliente,telefonetemp);
                break;    
            }
            else{
                printf("Telefone invalido\n");
                getchar();
                getchar();
            }
    }
    
    return 0;
}

//Cadastra o Pet e retorna 0 caso tenha tido sucesso
int cadstrarPet(struct Animal *animais, int cont){

    char nometemp[50],agressivotemp;
    struct Data temp;
    int tempesp;


    while(1){
   
    printf("\e[1;1H\e[2J");

    printf("Por favor digite o nome do Animal: ");
    scanf(" %[^\n]",nometemp);

    printf("\e[1;1H\e[2J");

    if(validarnome(nometemp) == 0){
        strcpy(animais[cont].nome_do_animal, nometemp);
        break;
    }

    else{
        printf("Nome invalido\n");
        getchar();
        getchar();
    }
    }


    while(1){
    printf("\e[1;1H\e[2J");

    printf("Por favor informe o codigo da especie\n1 - Cachorro\n2 - Gato\n3 - Passaro\n4 - Outros\n");
    scanf(" %d",&tempesp);

    printf("\e[1;1H\e[2J");
    
    if(tempesp >4 && tempesp < 1){
        
        printf("Entrada Invalida");
        getchar();
        getchar();
    }
    else{
        animais[cont].especie = tempesp;
        printf("\e[1;1H\e[2J");
        break;
    }
    }

    while(1){

    printf("\e[1;1H\e[2J");

    printf("Por favor digite se o animal é agressivo ou não (S/N): ");
    scanf(" %c",&agressivotemp);
    
    printf("\e[1;1H\e[2J");

    if (agressivotemp == 'S' || agressivotemp == 's' || agressivotemp == 'N' || agressivotemp == 'n')
    {
     animais[cont].agressivo = agressivotemp;
     break;
    }

    else{
        
        printf("Entrada Invalida\n");
        getchar();
        getchar();
        printf("\e[1;1H\e[2J");
    }
    

    }

    while(1){
    printf("Por favor digite a data de nascimento do animal no formato(Dia/Mes/Ano):\n");
    scanf( "%d/%d/%d",&temp.dia,&temp.mes,&temp.ano);

    if (validarData(temp) == 0){
        animais[cont].data_nascimento.dia = temp.dia;
        animais[cont].data_nascimento.mes = temp.mes;
        animais[cont].data_nascimento.ano = temp.ano;
        break;
    }
    else{

        printf("\e[1;1H\e[2J");
        printf("Data Invalida\n");
        getchar();
        getchar();
    }

    }

    //Reutiliza função anterior
    cadastrarclientes(&animais[cont].cliente,0);

    return 0;
}


//Busca clientes com o nome desejado e caso encontre buscará animais que possuem o cliente como dono
int buscarcliente(struct Cliente *cliente,int cont,char nome[50],struct Animal *animais, int contanimais){
    printf("\e[1;1H\e[2J");

    for (int i = 0; i < cont; i++){

        if(strcmp(cliente[i].nome_do_cliente,nome) == 0){
            printf("\nNome do Cliente: %s\nTelefone do Cliente: %s\n\n",cliente[i].nome_do_cliente,cliente[i].telefone_do_cliente);

            for (int j = 0; j < contanimais; j++)
            {
                if (strcmp(animais[j].cliente.nome_do_cliente,cliente[i].nome_do_cliente) == 0){
                    printf("Nome do Animal: %s\nEspecie do animal: %d\nData de Nascimento: %d/%d/%d\nAgressivo: %c\n\n",animais[j].nome_do_animal,animais[j].especie,animais[j].data_nascimento.dia,animais[j].data_nascimento.mes,animais[j].data_nascimento.ano,animais[j].agressivo);
                }
                
            }
            
        }

    
}
    getchar();
    getchar();
}

//ordena o array de animais por meio de um algoritimo de quicksort
void ordenarAnimais(struct Animal *animais, int cont) {
    struct Animal temp;
    for (int i = 0; i < cont - 1; i++) {
        for (int j = i + 1; j < cont; j++) {
            if (strcmp(animais[i].nome_do_animal, animais[j].nome_do_animal) > 0) {
                temp = animais[i];
                animais[i] = animais[j];
                animais[j] = temp;
            }
        }
    }
}

//imprime os animais após ordena-los
int listarpets(struct Animal *animais, int cont) {
    ordenarAnimais(animais, cont);
    printf("\e[1;1H\e[2J\n");
    for (int i = 0; i < cont; i++) {
        printf("Nome do Animal: %s\n", animais[i].nome_do_animal);
        printf("Especie do animal: %d\n", animais[i].especie);
        printf("Data de Nascimento: %d/%d/%d\n", animais[i].data_nascimento.dia, animais[i].data_nascimento.mes, animais[i].data_nascimento.ano);
        printf("Agressivo: %c\n", animais[i].agressivo);
        printf("\n");
    }
    getchar();
    getchar();
    return 0;
}

//Percorre todo o array de animais e imprime as informacoes daqueles que possuem o nome correspondente com o parametro em formato de tabela
int buscarPet(struct Animal *animais, int cont,char nome[50]){
    printf("\e[1;1H\e[2J");

    for (int i = 0; i < cont; i++){

        if(strcmp(animais[i].nome_do_animal,nome) == 0){
            printf("\nNome do Animal: %s | Especie do animal: %d | Data de Nascimento: %d/%d/%d | Agressivo: %c | Nome do Cliente: %s | Telefone do Cliente: %s |\n", animais[i].nome_do_animal, animais[i].especie,animais[i].data_nascimento.dia, animais[i].data_nascimento.mes, animais[i].data_nascimento.ano,animais[i].agressivo,animais[i].cliente.nome_do_cliente,animais[i].cliente.telefone_do_cliente);   
        }
}
    getchar();
    getchar();
}

//Percorre o Array e ultiliza um contador para adquirir a quantidade de animais agressivos retornando assuim a quantidade
int retornarPetsAgressivos(struct Animal *animais,int cont){
    int qnt = 0;
    printf("\e[1;1H\e[2J");
    for (int i = 0; i < cont; i++)
    {
        if(animais[i].agressivo == 's' || animais[i].agressivo == 'S'){
            qnt++;
        }
    }
    
    return qnt;
}


int main(){

    printf("\e[1;1H\e[2J");
    struct Cliente clientes[100];
    struct Animal animais[100];
    
    char nome[50];
    int op = -1,numAnimais=0,numClientes=0;

    while(op != 0){
    
    printf("\e[1;1H\e[2J");
    printf("\nMenu de Gerenciamento do Pet shop\n\n");
    printf("1- Cadastrar Cliente\n");
    printf("2- Cadastrar Pet\n");
    printf("3- Buscar Clientes\n");
    printf("4- Buscar Pet\n");
    printf("5- Listar Pets\n");
    printf("6- Mostrar quantidade de animais Agressivos\n");
    printf("Opcao: ");
    scanf(" %d",&op);

    switch (op)
    {
    case 1:
        cadastrarclientes(clientes,numClientes);
        numClientes++;
        break;
    
    case 2:
        cadstrarPet(animais,numAnimais);
        numAnimais++;
        break;

    case 3:

        printf("\e[1;1H\e[2J");
        printf("Por favor Digite o Nome do Cliente: ");
        scanf(" %[^\n]",nome);

        buscarcliente(clientes,numClientes,nome,animais,numAnimais);
        break;

    case 4:
        printf("\e[1;1H\e[2J");
        printf("Por favor Digite o Nome do Pet: ");
        scanf(" %[^\n]",nome);

        buscarPet(animais,numAnimais,nome);
        break;

    case 5:

        listarpets(animais,numAnimais);

        break;

    case 6:
        printf("\nExistem %d animais agressivos cadastrados.\n",retornarPetsAgressivos(animais,numAnimais));
        getchar();
        getchar();


    break;

    default:
        break;
    }
    }
}