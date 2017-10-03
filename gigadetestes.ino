/*
 * gigadetestes.ino
 * 
 * Programa em Arduino para realização de testes de sinais elétricos em placas de circuito impresso.
 *
 * Criado em 2 Outubro de 2017
 * Por Otacilio Neto (github: @OtacilioN | Email: contato@otaciliomaia.com)
 * Publicado na Licensa MIT
 */


// Passar os defines para comentário para as funções que não serão utilizadas
#define AVALIAR_TENSAO  // Se a giga de testes deve além de informar, avaliar as tensões lidas
#define USAR_PROXIMOS   // Se os pinos semelhantes estiverem em sequência na placa, por exemplo pinos de 0 até 3v3 da porta A0 até A2, pinos de 0 até 10v da porta A3 até A4 e pino de alimentação na porta A5 
#define CHECKAR_ALIMENTACAO // Se houverem pinos de alimentação cuja tensão não deve variar
#define NOMEAR_PLACAS
// Fim dos defines de funções

// Modificar de acordo com a sua placa
#define MAIOR_DIGITAL 0 // 13 Para Arduino Uno, 53 para Arduino Mega (Analise digital ainda não implementada)
#define MAIOR_ANALOGICA 5  // 5 para Arduino Uno, 15 para Arduino Mega
#define TOTAL_PINOS (MAIOR_ANALOGICA + MAIOR_DIGITAL) 
#define QUANTIDADE_PLACAS 80 // 80 para 80 placas de testes
#define FAIXA_TOLERANCIA 0.1 // 0.1 indica 10% de tolerancia

// Inicio do código, não é necessário parametrizar mais nada pelo código a partir daqui

unsigned int x, y;
unsigned char aux, pinos;
unsigned char cont = 0;
float tensao_medida[TOTAL_PINOS][3];

#ifdef AVALIAR_TENSAO
    float tensao_referencia[TOTAL_PINOS];

    #ifdef USAR_PROXIMOS
        unsigned char proximos = 0;
    #endif
#endif

#ifdef CHECKAR_ALIMENTACAO
    unsigned char qntd_alimentacao;

    #ifdef USAR_PROXIMOS
        unsigned char pino_alimentacao;
    #else
        unsigned char pinos_alimentacao[TOTAL_PINOS];
    #endif
#endif 

#ifdef NOMEAR_PLACAS
    unsigned int nomes[QUANTIDADE_PLACAS];
#endif

void parametrizar();
void testar();

void setup()
{
    Serial.begin(9600);

    for(x = 0; x <= MAIOR_DIGITAL; x++)
        pinMode(x, INPUT);
    
    parametrizar();
    x = 0;
    while(x < QUANTIDADE_PLACAS){
        testar();   
    }   
    
}

void loop()
{
}

// Parametrização da GIGA
void parametrizar(){

    x = 0;
    Serial.print("Digite quantos pinos analogicos serão lidos: ");
    pinos = Serial.read();
    
    // Aquisição das tensões de referência
    #ifdef AVALIAR_TENSAO
        while(cont < pinos){        
            Serial.print("Digite a tensão de referência: "); // Utilize . para casas decimais
            tensao_referencia[x] = (int) Serial.read();

            #ifdef USAR_PROXIMOS
                Serial.print("Por quantos próximos pinos usar esta tensão de referência: ");
                aux = (int) Serial.read();
                cont = cont + aux;
                y = 0;
                while(y < aux){
                    x++;
                    tensao_referencia[x] = tensao_referencia[x-1];
                    y++;
                }
                
            #else
                cont++;
            #endif
            x++;
        }
    #endif

    // Aquisição dos pinos de alimentação
    #ifdef CHECKAR_ALIMENTACAO
        Serial.print("Digite quantos pinos de alimentação serão lidos: ");
        qntd_alimentacao = Serial.read();

        #ifdef USAR_PROXIMOS
            Serial.print("Digite o primeiro pino para alimentação (exemplo, para A0 digite 0): ");
            pino_alimentacao = Serial.read();
        #else
            x = 0;
            while(x < qntd_alimentacao){
                Serial.print("Digite o numero do ");
                Serial.print(x+1);
                Serial.print("° pino de alimentacao (exemplo, para A0 digite 0): ");
                pinos_alimentacao[x] = Serial.read();
                x++;
            }            
        #endif
    #endif 
}

void testar(){
    y = aux = 0;

    #ifdef NOMEAR_PLACAS
        Serial.print("Digite o código numérico da placa: ");
        nomes[x] = Serial.read();      
    #endif
    Serial.print("Aterre todos os pinos de sinais, e deixe a placa alimentada, então envie algum caractere na serial: ");
    Serial.read();

    while(y < pinos){
        tensao_medida[y][0] = map(analogRead(A0+y), 0, 1023, 0, tensao_referencia[y]);
        Serial.print("Foi medido na porta A"); Serial.print(y);  Serial.print(" uma tensao de: "); Serial.print(tensao_medida[y][0]); Serial.println(" volts");
        y++;
    }
    #ifdef USAR_PROXIMOS
        y = 0;
        while(y < pino_alimentacao)
        {
            Serial.print("passe o pino A"); Serial.print(y); Serial.print("para a tensão máxima, aterre os demais, então envie algum caractere na serial:");
            Serial.read();
            tensao_medida[y][1] = map(analogRead(A0+y), 0, 1023, 0, tensao_referencia[y]);
            y++;
        }
        while(y < pinos){
            tensao_medida[y][1] = map(analogRead(A0+y), 0, 1023, 0, tensao_referencia[y]);
            y++;
        }

        y = 0;
        Serial.print("Passe todos os pinos para a tensão máxima, e deixe a placa alimentada, então envie algum caractere na serial: ");
        Serial.read();

        while(y < pinos){
            tensao_medida[y][2] = map(analogRead(A0+y), 0, 1023, 0, tensao_referencia[y]);
            y++;
        }


    #else // implementar depois
    #endif
        
}