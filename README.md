# Embarcatech-Final-Project
## Embarca-Tuner
#### Autor:
* Roberto Vítor Lima Gomes Rodrigues

### Afinador em RP2040
Como projeto final, optou-se pela implementação de um afinador utilizando o microfone, a conversão análogico-digital (ADC), e um processamento de sinais via Transformada Rápida de Fourier para trazer os sinais, agora digitais, novamente para o domínio real como frequências, comparando-as com as frequências das 12 notas da escala musical ocidental. As notas obtidas são representadas por meio de letras de A a G (notação americana) na Matrix de LEDs e também no display OLED (bem como a frequência obtida). Notas naturais são representadas como letras e os acidentes (notas sustenidas) são letras com um ponto na matriz de LEDs e letras seguidas de "#" no display.

#### Vídeo de funcionamento
* https://youtu.be/lGASCX_3wi4
    * Obs.: foram implementadas as seguintes características -> 
       * Conversor Analógico-Digital (ADC) para processar o sinal recebido pelo do microfone, 
       * Modulação de Largura de Pulso (PWM) para modular a intensidade dos LEDs RGB 
       * PIO para controlar a matriz de LEDs WS2812B
       * I2C para controlar a exibição no display OLED
       * UART para debugging através de prints.


#### Instruções de compilação
Certifique-se de que você tem o ambiente configurado conforme abaixo:
* Pico SDK instalado e configurado.
* VSCode com todas as extensões configuradas, CMake e Make instalados.
* Clone o repositório e abra a pasta do projeto, a extensão Pi Pico criará a pasta build
* Clique em Compile na barra inferior, do lado direito (ao lado esquerdo de RUN | PICO SDK)
* Verifique se gerou o arquivo .uf2
* Conecte a placa BitDogLab e ponha-a em modo BOOTSEL
* Arraste o arquivo até a placa, que o programa se iniciará

#### Manual do programa
Ao executar o programa, as seguintes características poderão ser verificadas:
* Ao emitir uma nota musical, o microfone a captará, e o firmware a processará mostrando-a na matriz de LEDs e também no display OLED, junto à frequência obtida.
* Ao tocar uma nota na frequência correta, o LED RGB verde será aceso, modulado com baixa intensidade.
* Ao tocar uma nota na frequência errada, o LED RGB vermelho será aceso, modulado com baixa intensidade.
* Ao não tocar nota nenhuma, o LED RGB ficará aceso com branco (verde, vermelho e azul ao mesmo tempo) com fraca intensidade, e o display OLED mostrará F (frequência) = 0 e N (nota) = n/a.
* Obs.: por conta da extensão de técnicas pedidas na atividade, o vídeo ficou um pouco mais extenso do que o normal.
