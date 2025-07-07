# 🎮 Jogo da Memória - Arduino + App Inventor

[English Version Here](README_en.md)

## Anexos
### Tinkercad
- [Imagem da Montagem](https://ibb.co/LzRXN25Q)

### App Inventor
- [Código do MIT App Inventor](https://ibb.co/H1C3GtJ)
- [Imagem da Interface do Aplicativo](https://ibb.co/HDVVk1Bx)

## Descrição do Projeto

O **Jogo da Memória** é um projeto interativo que combina hardware (Arduino) e software (App Inventor) para criar uma experiência de jogo educativa e divertida. O sistema gera sequências aleatórias de cores através de LEDs e testa a capacidade de memorização do usuário, que deve reproduzir as sequências através de um aplicativo móvel.

## Funcionalidades Principais

### Hardware (Arduino)
- **Geração de Sequências**: Criação aleatória de sequências de cores.
- **Indicação Visual**: LEDs coloridos mostram a sequência a ser memorizada.
- **Controle de Velocidade**: Potenciômetro ajusta a velocidade de exibição.
- **Feedback Sonoro**: Buzzer reproduz sons de vitória e derrota.
- **Indicadores de Velocidade**: LEDs mostram a velocidade atual do jogo.

### Software (App Inventor)
- **Interface Intuitiva**: Botões coloridos para inserir a sequência.
- **Comunicação Bluetooth**: Conexão wireless com o Arduino.
- **Contador de Vitórias**: Acompanha o progresso do jogador.
- **Feedback Visual**: Indicação de acertos e erros.

## Componentes Utilizados

### Hardware
- **Arduino UNO** - Microcontrolador principal.
- **LEDs** (4 unidades):
  - LED Verde (Pino 4)
  - LED Vermelho (Pino 5)
  - LED Amarelo (Pino 6)
  - LED Azul (Pino 7)
- **LEDs Indicadores de Velocidade** (3 unidades):
  - LED Lento (Pino 12)
  - LED Médio (Pino 11)
  - LED Rápido (Pino 10)
- **Buzzer** (Pino 8) - Para feedback sonoro.
- **Potenciômetro** (Pino A2) - Controle de velocidade.
- **Protoboard** - Montagem dos componentes.
- **Resistores** - Limitação de corrente dos LEDs.
- **Jumpers** - Conexões entre componentes.

### Software
- **Arduino IDE** - Programação do microcontrolador.
- **MIT App Inventor** - Desenvolvimento do aplicativo móvel.
- **Bluetooth HC-05/HC-06** - Comunicação wireless (implícito no projeto).

## Diagrama de Conexões

### Pinagem do Arduino

| Componente | Pino | Descrição |
|------------|------|-----------|
| LED Verde | 4 | Representa a cor 'G' (Green) |
| LED Vermelho | 5 | Representa a cor 'R' (Red) |
| LED Amarelo | 6 | Representa a cor 'Y' (Yellow) |
| LED Azul | 7 | Representa a cor 'B' (Blue) |
| Buzzer | 8 | Feedback sonoro |
| LED Rápido | 10 | Indicador de velocidade rápida |
| LED Médio | 11 | Indicador de velocidade média |
| LED Lento | 12 | Indicador de velocidade lenta |
| Potenciômetro | A2 | Controle de velocidade |

### Esquema de Ligação
- Todos os LEDs conectados através de resistores de 220Ω.
- Potenciômetro conectado ao 5V, GND e pino analógico A2.
- Buzzer conectado diretamente ao pino 8 e GND.

## Código Arduino

### Principais Funções

#### `setup()`
- Inicializa os pinos como entrada ou saída.
- Configura comunicação serial.
- Inicializa gerador de números aleatórios.
- Executa primeira sequência do jogo.

#### `loop()`
- Monitora entrada serial do aplicativo.
- Processa sequência enviada pelo usuário.
- Verifica se a sequência está correta.
- Gera nova sequência para próxima rodada.

#### `lerVelocidadePotenciometro()`
- Lê valor analógico do potenciômetro (0-1023)
- Mapeia para velocidade em millisegundos (200-1000ms)
- Atualiza LEDs indicadores de velocidade.

#### `gerarSequenciaAleatoria()`
- Cria sequência aleatória de 4 cores
- Utiliza array `coresPossiveis['B', 'R', 'Y', 'G']`

#### `mostrarSequenciaLed()`
- Exibe sequência através dos LEDs coloridos.
- Duração baseada na velocidade do potenciômetro.

#### `verificarSequencia()`
- Compara sequência do usuário com sequência gerada.
- Retorna true/false para indicar acerto/erro.

### Controle de Velocidade

O potenciômetro controla a velocidade de exibição da sequência:
- **Rápida**: ≤ 400ms (LED Rápido aceso)
- **Média**: 401-700ms (LED Médio aceso)
- **Lenta**: > 700ms (LED Lento aceso)

### Feedback Sonoro

- **Vitória**: Melodia ascendente (Dó, Mi, Sol, Dó)
- **Derrota**: Melodia descendente (Sol, Ré, Dó, Sol)

## Interface do Aplicativo

### Elementos da Interface

1. **Título**: "Jogo da Memória"
2. **Contador de Vitórias**: Exibe vitórias consecutivas.
3. **Botões de Cores**:
   - Verde (G)
   - Vermelho (R)
   - Amarelo (Y)
   - Azul (B)
4. **Botão de Atualização**: Atualiza contador de vitórias.
5. **Área de Resultado**: Mostra resultado da última jogada.

### Lógica do Aplicativo

#### Inicialização
- Estabelece conexão Bluetooth com Arduino.
- Inicializa variáveis globais (resposta e vitórias).
- Configura interface inicial.

#### Interação do Usuário
- Cada botão de cor adiciona letra correspondente à resposta.
- Botão "reset" permite recomeçar a sequência.
- Envio automático da sequência quando completa.

#### Comunicação Bluetooth
- Recebe dados do Arduino via Bluetooth.
- Processa códigos de vitória (1) e derrota (0).
- Atualiza interface baseado no resultado.

## Jogatina

### Gameplay
1. **Observação**: Arduino mostra sequência de cores através dos LEDs.
2. **Memorização**: Memorize a ordem das cores exibidas.
3. **Reprodução**: Use o aplicativo para reproduzir a sequência.
4. **Feedback**: Sistema indica se acertou ou errou.
5. **Continuação**: Nova sequência é gerada automaticamente.

### Pontuação
- Cada sequência correta incrementa o contador de vitórias.
- Erro zera o contador de vitórias consecutivas.
- **Objetivo:** conseguir o maior número de vitórias consecutivas.

## Integrantes
- Maria Eduarda B.
- Gabriella A.
- Daniel R.
- Rafael T.
