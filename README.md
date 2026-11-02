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

## Como funciona

1. O Arduino envia um pulso de 10 µs no pino TRIG.
2. O sensor emite uma onda ultrassônica e aguarda o eco.
3. O tempo de retorno é medido com `pulseIn()` no pino ECHO.
4. A distância é calculada pela fórmula:

   ```
   distância (cm) = tempo (µs) × 0,0343 / 2
   ```

5. São feitas 5 leituras seguidas e o programa calcula a média das válidas, o que deixa o valor mais estável.
6. Leituras fora do alcance do sensor (menos de 2 cm ou mais de 400 cm) são ignoradas.
7. O resultado, com uma casa decimal, é mostrado no LCD e enviado ao Monitor Serial a cada 300 ms.
8. Se nenhuma leitura válida for obtida, o display mostra **FORA DE FAIXA**.

## Como usar

1. Monte o circuito conforme as tabelas acima.
2. Instale o [Arduino IDE](https://www.arduino.cc/en/software).
3. Abra o arquivo `medidor_distancia/medidor_distancia.ino`.
4. Selecione a placa (**Arduino Uno**) e a porta correta.
5. Clique em **Upload**.
6. Aproxime objetos do sensor e veja a distância no display.
7. (Opcional) Abra o **Monitor Serial** em 9600 baud para acompanhar as leituras no computador.

A biblioteca `LiquidCrystal` já vem instalada com o Arduino IDE.
