// ====================================================================
// JOGO DA MEMÓRIA - ARDUINO
// Sistema que gera sequências aleatórias de cores e testa a memória
// do usuário através de LEDs coloridos e comunicação serial
// ====================================================================

// Definições de pinos para componentes
#define buzzer 8              // Pino do buzzer para sons
#define potenciometro A2      // Pino analógico do potenciômetro (controla velocidade)

// Definições dos LEDs coloridos (cores do jogo)
#define led_verde 4           // LED verde - representa cor 'G'
#define led_vermelho 5        // LED vermelho - representa cor 'R'
#define led_amarelo 6         // LED amarelo - representa cor 'Y'
#define led_azul 7            // LED azul - representa cor 'B'

// Definições dos LEDs indicadores de velocidade
#define led_lento 12          // LED indicador de velocidade lenta
#define led_medio 11          // LED indicador de velocidade média
#define led_rapido 10         // LED indicador de velocidade rápida

// Constantes e variáveis globais do jogo
const int maxLength = 10;                    // Tamanho máximo da sequência
char coresPossiveis[4] = {'B', 'R', 'Y', 'G'}; // Array com as cores possíveis (Blue, Red, Yellow, Green)
char sequencia[maxLength + 1];               // Array para armazenar a sequência atual (+1 para terminador)
int comprimentoSequencia = 4;               // Tamanho atual da sequência (inicia com 4)
int contadorVitorias = 0;                   // Contador de vitórias consecutivas
int velocidadeAtual = 0;                    // Velocidade atual em millisegundos

// ====================================================================
// FUNÇÃO DE INICIALIZAÇÃO - EXECUTADA UMA VEZ AO LIGAR O ARDUINO
// ====================================================================
void setup() {
  // Configuração inicial do buzzer
  pinMode(buzzer, OUTPUT);     // Define buzzer como saída
  digitalWrite(buzzer, LOW);   // Garante que o buzzer está desligado
  noTone(buzzer);             // Para qualquer som que possa estar tocando
  delay(50);                  // Pequena pausa para estabilização
  
  // Configuração dos LEDs coloridos como saída
  pinMode(led_azul, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_verde, OUTPUT);
  
  // Configuração dos LEDs indicadores de velocidade como saída
  pinMode(led_lento, OUTPUT);
  pinMode(led_medio, OUTPUT);
  pinMode(led_rapido, OUTPUT);
  
  // Inicialização da comunicação serial
  Serial.begin(9600);
  Serial.println("SISTEMA INICIADO - JOGO DA MEMORIA");
  
  // Inicialização do gerador de números aleatórios
  randomSeed(analogRead(0));  // Usa ruído analógico para gerar semente aleatória
  
  // Sequência inicial do jogo
  lerVelocidadePotenciometro();  // Lê velocidade do potenciômetro
  atualizarLedsVelocidade();     // Atualiza LEDs indicadores de velocidade
  gerarSequenciaAleatoria();     // Gera primeira sequência
  mostrarSequenciaSerial();      // Mostra sequência no monitor serial
  mostrarSequenciaLed();         // Mostra sequência através dos LEDs
  
  Serial.println("\nEnvie sua Sequencia:");
}

// ====================================================================
// LOOP PRINCIPAL - EXECUTADO CONTINUAMENTE
// ====================================================================
void loop() {
  // Verifica se há dados disponíveis na comunicação serial
  if (Serial.available()) {
    // Lê a entrada do usuário até encontrar uma nova linha
    String entrada = Serial.readStringUntil('\n');
    entrada.trim();  // Remove espaços em branco do início e fim
    
    // Exibe a sequência recebida do usuário
    Serial.println();
    Serial.println("===============================");
    Serial.println("SEQUENCIA RECEBIDA DO USUARIO:");
    Serial.println(entrada);
    Serial.println("===============================");
    
    // Verifica se a sequência do usuário está correta
    if (verificarSequencia(entrada)) {
      // Sequência correta - incrementa contador e toca música de vitória
      contadorVitorias++;
      Serial.println("SEQUENCIA CORRETA! VITORIA!");
      Serial.print("VITORIAS:");
      Serial.println(contadorVitorias); 
      
      Serial.println("1");  // Código para indicar vitória
      tocarMusicaVitoria();
    } else {
      // Sequência incorreta - reseta contador e toca música de derrota
      Serial.println("SEQUENCIA ERRADA! DERROTA!");
      Serial.println("0");  // Código para indicar derrota
      
      Serial.print("Vitorias Consecutivas Finalizadas: ");
      Serial.println(contadorVitorias);
      contadorVitorias = 0;  // Reseta contador de vitórias
      tocarMusicaDerrota();
    }
    
    // Pausa antes de gerar nova sequência
    delay(1000);
    
    // Prepara próxima rodada
    lerVelocidadePotenciometro();  // Relê velocidade (pode ter mudado)
    atualizarLedsVelocidade();     // Atualiza indicadores de velocidade
    gerarSequenciaAleatoria();     // Gera nova sequência
    mostrarSequenciaSerial();      // Mostra nova sequência no serial
    mostrarSequenciaLed();         // Mostra nova sequência nos LEDs
    
    Serial.println("\nDigite sua Proxima Sequencia:");
  }
}

// ====================================================================
// FUNÇÃO PARA LER VELOCIDADE DO POTENCIÔMETRO
// ====================================================================
void lerVelocidadePotenciometro() {
  // Lê valor analógico do potenciômetro (0-1023)
  int valorPot = analogRead(potenciometro);
  
  // Mapeia o valor para velocidade em millisegundos (200-1000ms)
  // Valores menores = mais rápido, valores maiores = mais lento
  velocidadeAtual = map(valorPot, 0, 1023, 200, 1000);
  
  // Exibe informações de velocidade no monitor serial
  Serial.println();
  Serial.println(">>> CONFIGURACAO DE VELOCIDADE:");
  Serial.print("Valor do Potenciometro: ");
  Serial.print(valorPot);
  Serial.print("/1023 | Velocidade: ");
  Serial.print(velocidadeAtual);
  Serial.println("ms");
  
  // Determina e exibe categoria de velocidade
  if (velocidadeAtual <= 400) {
    Serial.println("Velocidade: RAPIDA");
  } else if (velocidadeAtual <= 700) {
    Serial.println("Velocidade: MEDIA");
  } else {
    Serial.println("Velocidade: LENTA");
  }
}

// ====================================================================
// FUNÇÃO PARA ATUALIZAR LEDs INDICADORES DE VELOCIDADE
// ====================================================================
void atualizarLedsVelocidade() {
  // Apaga todos os LEDs de velocidade primeiro
  digitalWrite(led_lento, LOW);
  digitalWrite(led_medio, LOW);
  digitalWrite(led_rapido, LOW);
  
  // Acende o LED correspondente à velocidade atual
  if (velocidadeAtual <= 400) {
    digitalWrite(led_rapido, HIGH);  // Velocidade rápida (≤400ms)
    Serial.println("LED RAPIDO: LIGADO");
  } else if (velocidadeAtual <= 700) {
    digitalWrite(led_medio, HIGH);   // Velocidade média (401-700ms)
    Serial.println("LED MEDIO: LIGADO");
  } else {
    digitalWrite(led_lento, HIGH);   // Velocidade lenta (>700ms)
    Serial.println("LED LENTO: LIGADO");
  }
}

// ====================================================================
// FUNÇÃO PARA GERAR SEQUÊNCIA ALEATÓRIA DE CORES
// ====================================================================
void gerarSequenciaAleatoria() {
  // Gera sequência aleatória baseada no comprimento atual
  for (int i = 0; i < comprimentoSequencia; i++) {
    // Seleciona aleatoriamente uma cor do array de cores possíveis
    sequencia[i] = coresPossiveis[random(0, 4)];
  }
  
  // Adiciona terminador de string
  sequencia[comprimentoSequencia] = '\0';
}

// ====================================================================
// FUNÇÃO PARA MOSTRAR SEQUÊNCIA NO MONITOR SERIAL
// ====================================================================
void mostrarSequenciaSerial() {
  Serial.println();
  Serial.println(">>> NOVA SEQUENCIA GERADA:");
  Serial.println(sequencia);  // Exibe a sequência gerada
}

// ====================================================================
// FUNÇÃO PARA MOSTRAR SEQUÊNCIA ATRAVÉS DOS LEDs
// ====================================================================
void mostrarSequenciaLed() {
  // Percorre cada cor da sequência
  for (int i = 0; i < comprimentoSequencia; i++) {
    // Acende LED correspondente à cor por tempo determinado pela velocidade
    acenderLedPorChar(sequencia[i], velocidadeAtual);
    delay(200);  // Pausa entre cada LED da sequência
  }
}

// ====================================================================
// FUNÇÃO PARA ACENDER LED ESPECÍFICO BASEADO NO CARACTERE
// ====================================================================
void acenderLedPorChar(char c, int duracao) {
  int ledPin = -1;  // Variável para armazenar o pino do LED
  
  // Determina qual LED acender baseado no caractere
  switch (c) {
    case 'B': ledPin = led_azul; break;     // 'B' = Blue (Azul)
    case 'R': ledPin = led_vermelho; break; // 'R' = Red (Vermelho)
    case 'Y': ledPin = led_amarelo; break;  // 'Y' = Yellow (Amarelo)
    case 'G': ledPin = led_verde; break;    // 'G' = Green (Verde)
  }
  
  // Se foi encontrado um LED válido, acende por determinado tempo
  if (ledPin != -1) {
    digitalWrite(ledPin, HIGH);  // Liga o LED
    delay(duracao);             // Mantém ligado pelo tempo especificado
    digitalWrite(ledPin, LOW);   // Desliga o LED
  }
}

// ====================================================================
// FUNÇÃO PARA VERIFICAR SE A SEQUÊNCIA DO USUÁRIO ESTÁ CORRETA
// ====================================================================
bool verificarSequencia(String resposta) {
  // Verifica se o comprimento da resposta está correto
  if (resposta.length() != comprimentoSequencia) return false;
  
  // Compara cada caractere da resposta com a sequência gerada
  for (int i = 0; i < comprimentoSequencia; i++) {
    // Converte para maiúscula e compara
    if (toupper(resposta.charAt(i)) != sequencia[i]) {
      return false;  // Retorna falso se encontrar diferença
    }
  }
  
  return true;  // Retorna verdadeiro se toda a sequência estiver correta
}

// ====================================================================
// FUNÇÃO PARA TOCAR MÚSICA DE VITÓRIA
// ====================================================================
void tocarMusicaVitoria() {
  // Definição da melodia de vitória (frequências em Hz)
  int melodia[] = { 523, 659, 784, 1047 };  // Dó, Mi, Sol, Dó (oitava acima)
  int durNotas[] = { 150, 150, 300, 600 };  // Durações das notas em ms
  
  // Toca cada nota da melodia
  for (int i = 0; i < 4; i++) {
    tone(buzzer, melodia[i], durNotas[i]);  // Toca a nota
    delay(durNotas[i] * 1.3);              // Pausa entre notas (30% maior que a duração)
  }
}

// ====================================================================
// FUNÇÃO PARA TOCAR MÚSICA DE DERROTA
// ====================================================================
void tocarMusicaDerrota() {
  // Definição da melodia de derrota (frequências descendentes em Hz)
  int melodia[] = { 196, 147, 131, 98 };    // Sol, Ré, Dó, Sol (oitava abaixo)
  int durNotas[] = { 400, 400, 400, 800 };  // Durações das notas em ms
  
  // Toca cada nota da melodia
  for (int i = 0; i < 4; i++) {
    tone(buzzer, melodia[i], durNotas[i]);  // Toca a nota
    delay(durNotas[i] * 1.3);              // Pausa entre notas (30% maior que a duração)
  }
}