#define AVALIAR_TENSAO
#define USAR_PROXIMOS

#define MAIOR_PINO 14 // 14 Para Arduino Uno, 54 para Arduino Mega

int pinos, aux, valores[20];

#ifdef AVALIAR_TENSAO
    float tensao[20];

    #ifdef USAR_PROXIMOS
        int semelhantes[20];
    #endif
#endif



void setup()
{
    int x, aux;
    cont = 0;
    Serial.begin(9600);
    for(x = 1; x < MAIOR_PINO; x++)
        pinMode(x, INPUT);
    
    x = 0;
    Serial.println("Digite quantos pinos serão lidos:");
    pinos = (int) Serial.read();
    
    #ifdef AVALIAR_TENSAO
        while(cont < pinos){        
            Serial.println("Digite a tensão de referência:"); // Utilize . para casas decimais
            tensao[x] = (int) Serial.read();

            #ifdef USAR_PROXIMOS
                Serial.println("Por quantos próximos pinos usar esta tensão de referência:");
                aux = (int) Serial.read();
                cont = cont + aux;
                semelhantes[x] = aux;
            #endif
            x++;
        }
    #endif
}

void loop()
{
}
