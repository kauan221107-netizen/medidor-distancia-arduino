# Medidor de Distância com Arduino

Projeto que mede distâncias usando um sensor ultrassônico HC-SR04 e exibe o resultado em tempo real em um display LCD 16x2.

## Demonstração

<img src="medidor de distancia.jpeg">

## Componentes

- Arduino Uno
- Sensor ultrassônico HC-SR04
- Display LCD 16x2 (HD44780)
- Potenciômetro 10 kΩ (ajuste de contraste do LCD)
- Resistor de 220 Ω (backlight do LCD)
- Protoboard e jumpers

## Ligações

### Sensor HC-SR04

| HC-SR04 | Arduino |
|---------|---------|
| VCC     | 5V      |
| GND     | GND     |
| TRIG    | 9       |
| ECHO    | 10      |

### Display LCD 16x2

| LCD | Conexão |
|-----|---------|
| VSS | GND |
| VDD | 5V |
| V0  | Pino central do potenciômetro |
| RS  | 12 |
| RW  | GND |
| E   | 11 |
| D4  | 5 |
| D5  | 4 |
| D6  | 3 |
| D7  | 2 |
| A   | 5V (via resistor de 220 Ω) |
| K   | GND |
