# 🎮 Memory Game - Arduino + App Inventor

## Attachments
### Tinkercad
- [Assembly Image](https://ibb.co/LzRXN25Q)

### App Inventor
- [MIT App Inventor Code](https://ibb.co/H1C3GtJ)
- [Application Interface Image](https://ibb.co/HDVVk1Bx)

## Project Description

The **Memory Game** is an interactive project that combines hardware (Arduino) and software (App Inventor) to create an educational and fun gaming experience. The system generates random color sequences through LEDs and tests the user's memorization ability, who must reproduce the sequences through a mobile application.

## Main Features

### Hardware (Arduino)
- **Sequence Generation**: Random creation of color sequences.
- **Visual Indication**: Colored LEDs show the sequence to be memorized.
- **Speed Control**: Potentiometer adjusts display speed.
- **Audio Feedback**: Buzzer plays victory and defeat sounds.
- **Speed Indicators**: LEDs show current game speed.

### Software (App Inventor)
- **Intuitive Interface**: Colored buttons to input the sequence.
- **Bluetooth Communication**: Wireless connection with Arduino.
- **Victory Counter**: Tracks player progress.
- **Visual Feedback**: Indication of correct and incorrect answers.

## Components Used

### Hardware
- **Arduino UNO** - Main microcontroller.
- **LEDs** (4 units):
  - Green LED (Pin 4)
  - Red LED (Pin 5)
  - Yellow LED (Pin 6)
  - Blue LED (Pin 7)
- **Speed Indicator LEDs** (3 units):
  - Slow LED (Pin 12)
  - Medium LED (Pin 11)
  - Fast LED (Pin 10)
- **Buzzer** (Pin 8) - For audio feedback.
- **Potentiometer** (Pin A2) - Speed control.
- **Breadboard** - Component assembly.
- **Resistors** - LED current limiting.
- **Jumpers** - Component connections.

### Software
- **Arduino IDE** - Microcontroller programming.
- **MIT App Inventor** - Mobile application development.
- **Bluetooth HC-05/HC-06** - Wireless communication (implicit in project).

## Connection Diagram

### Arduino Pinout

| Component | Pin | Description |
|-----------|-----|-------------|
| Green LED | 4 | Represents color 'G' (Green) |
| Red LED | 5 | Represents color 'R' (Red) |
| Yellow LED | 6 | Represents color 'Y' (Yellow) |
| Blue LED | 7 | Represents color 'B' (Blue) |
| Buzzer | 8 | Audio feedback |
| Fast LED | 10 | Fast speed indicator |
| Medium LED | 11 | Medium speed indicator |
| Slow LED | 12 | Slow speed indicator |
| Potentiometer | A2 | Speed control |

### Wiring Schematic
- All LEDs connected through 220Ω resistors.
- Potentiometer connected to 5V, GND and analog pin A2.
- Buzzer connected directly to pin 8 and GND.

## Arduino Code

### Main Functions

#### `setup()`
- Initializes pins as input or output.
- Configures serial communication.
- Initializes random number generator.
- Executes first game sequence.

#### `loop()`
- Monitors serial input from application.
- Processes sequence sent by user.
- Verifies if sequence is correct.
- Generates new sequence for next round.

#### `lerVelocidadePotenciometro()`
- Reads analog value from potentiometer (0-1023)
- Maps to speed in milliseconds (200-1000ms)
- Updates speed indicator LEDs.

#### `gerarSequenciaAleatoria()`
- Creates random sequence of 4 colors
- Uses array `coresPossiveis['B', 'R', 'Y', 'G']`

#### `mostrarSequenciaLed()`
- Displays sequence through colored LEDs.
- Duration based on potentiometer speed.

#### `verificarSequencia()`
- Compares user sequence with generated sequence.
- Returns true/false to indicate correct/incorrect.

### Speed Control

The potentiometer controls sequence display speed:
- **Fast**: ≤ 400ms (Fast LED on)
- **Medium**: 401-700ms (Medium LED on)
- **Slow**: > 700ms (Slow LED on)

### Audio Feedback

- **Victory**: Ascending melody (Dó, Mi, Sol, Dó)
- **Defeat**: Descending melody (Sol, Ré, Dó, Sol)

## Application Interface

### Interface Elements

1. **Title**: "Jogo da Memória"
2. **Victory Counter**: Displays consecutive victories.
3. **Color Buttons**:
   - Verde (G)
   - Vermelho (R)
   - Amarelo (Y)
   - Azul (B)
4. **Update Button**: Updates victory counter.
5. **Result Area**: Shows last game result.

### Application Logic

#### Initialization
- Establishes Bluetooth connection with Arduino.
- Initializes global variables (resposta and vitórias).
- Sets up initial interface.

#### User Interaction
- Each color button adds corresponding letter to resposta.
- "reset" button allows restarting the sequence.
- Automatic sequence sending when complete.

#### Bluetooth Communication
- Receives data from Arduino via Bluetooth.
- Processes victory (1) and defeat (0) codes.
- Updates interface based on result.

## Gameplay

### Game Flow
1. **Observation**: Arduino shows color sequence through LEDs.
2. **Memorization**: Memorize the order of colors displayed.
3. **Reproduction**: Use the app to reproduce the sequence.
4. **Feedback**: System indicates if you got it right or wrong.
5. **Continuation**: New sequence is generated automatically.

### Scoring
- Each correct sequence increments the victory counter.
- Error resets the consecutive victory counter.
- **Objective:** achieve the highest number of consecutive victories.

## Team Members
- Maria Eduarda B.
- Gabriella A.
- Daniel R.
- Rafael T.