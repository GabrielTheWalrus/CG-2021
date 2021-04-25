# Projeto 3 - Computação Gráfica - Campo de futebol

## Autor
Gabriel Bellomi Meale - 11091915

## Descrição
A aplicação consiste na tentativa de criar um campo de futebol. Porém, com a limitação de alguns modelos, algumas coisas foram improvisadas, como os gols. Todos os objetos da cena possuem textura e compartilham do mesmo shader. Além disso, usa a luz de forma similar ao projeto de trackball, onde utiliza-se a mesma movimentação para alterar a fonte de luz de posição.

Além disso, também é possivel andar pelo cenário, de forma parecida com a do projeto LookAt, porém, o movimento "pan" é feito com o mouse (o que é uma tentativa de replicar as movimentações de um jogo de FPS).

Houve também a tentativa de encaixar a cena dentro de um modelo do estadio de Wembley. Entretanto, o objetivo inicial era tentar manter as proporções o mais próximo possível do real. Dessa forma, a textura do estádio de wembley ficava extremamente esticada e extremamente difícil de encaixar com o objeto do campo de futebol.

Além disso, apesar de orientação do professor, não foi possível consertar o "bug" no mapeamento de textura do retângulo do campo de futebol. que acabou repetindo um pedaço que não deveria nas bordas.

O projeto está estrutura de uma forma mais "orientada a objetos", o que facilita a criação de objetos na cena, inclusive podendo receber como parâmetros variáveis que podem configurar sua posição e rotação na cena.

A camera "FPS" fica a uma altura de 1,8 no eixo y. Tentando simular uma pessoa de 180cm de altura, já que a proporção do campo de futebol é bem próxima de ser real (aproximadamente 100m x 70m).

## Movimentação

A movimentação de câmera é dada pelas teclas W, S (dolly), A, D (truck) e movimentação do mouse (pan) - semelhante a um FPS. Porém com alguns bugs, por exemplo de se basear de para onde o cursor vai (o qual quando chega ao fim da tela impede a movimentação pan).

A movimentação da bola de futebol que está ao centro do campo é dado pelas setas do teclado. Cima e baixo movimentam ao longo do eixo X. Esquerda e Direita ao longo do eixo Z.

## Código Fonte

O código fonte está dentro da pasta Examples, dentro do diretório ABC, como "Projeto 3".

## Link github pages

https://gabrielthewalrus.github.io/CAMPODEFUTEBOL/index.html

Obs.: esperar o FPS estabilizar para fazer movimentação do mouse (bug de câmera ficar girando até estabilizar FPS só acontece no build do WEBSM).

# Projeto 2 - Computação Gráfica - Balada com carro

## Autor
Gabriel Bellomi Meale - 11091915

## Descrição
A aplicação consiste em um modelo de carro obtido na internet renderizado em uma sala, onde as cores ficam piscando constantemente e aleatoriamente, dando efeito de luz de balada. 

## Movimentação

A movimentação é semelhante a do projeto look at (inclusive foi totalmente reaproveitada).

## Código Fonte

O código fonte está dentro da pasta Examples, dentro do diretório ABC, como "Projeto 2".

## Link github pages

https://gabrielthewalrus.github.io/BALADA/

Novamente, tive problemas na publicação no github pages, porém na pasta do public (do repositório original) está funcional o arquivo do carro na balada.

# Projeto 1 - Computação Gráfica - PONG

## Autor
Gabriel Bellomi Meale - 11091915

## Descrição
A aplicação consiste no clássico jogo PONG. Duas raquetes se movimentam pelo eixo Y (uma ao lado esquerdo da tela e outro do lado direito) rebatendo uma bola de uma lado para o outro. A primeira raquete que não conseguir bater leva um "GOL", somando um ponto para o adversário e, quando a somatória de um dos jogadores for de 5 gols, o jogo acaba e recomeça.

## Movimentação

Para movimentar a Raquete da esquerda, basta apertar a letra W e S para ir para cima e para baixo, respectivamente.
Para movimentar a Raquete da direita, basta apertar a tecla cima e baixo para ir para cima e para baixo, respectivamente.

## Código Fonte

O código fonte está dentro da pasta Examples, dentro do diretório ABC, como "Projeto 1".

## Link github pages

https://gabrielthewalrus.github.io/PONG/
