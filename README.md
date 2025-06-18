# Sistema de Medição de Diâmetro de Bobina

Este sistema foi desenvolvido para medir o diâmetro de uma bobina em tempo real durante o processo de enrolamento e desenrolamento, utilizando um encoder rotativo e um sensor magnético.

## Componentes Utilizados

1. **Arduino** (com suporte a interrupções)
2. **Encoder Rotativo**
   - 2500 PPR (Pulsos Por Revolução)
   - Conectado ao cilindro superior de 160mm de diâmetro
   - Pinos utilizados: 2 (Canal A) e 3 (Canal B)
3. **Sensor Magnético**
   - Tipo Hall com Pull-up
   - Detecta cada volta completa da bobina
   - Pino utilizado: 12

## Funcionamento do Sistema

### Medição do Comprimento do Fio

O sistema utiliza um cilindro superior de diâmetro conhecido (160mm) com um encoder acoplado. Para calcular o comprimento do fio que passa pelo cilindro:

1. **Cálculo da Circunferência do Cilindro**:
   ```
   CIRCUNF_CILINDRO = π × D_CILINDRO
   CIRCUNF_CILINDRO = π × 160 mm
   ```

2. **Cálculo do Número de Rotações**:
   ```
   rotacoesCilindro = contadorEncoder / PPR
   ```
   Onde PPR = 2500 (pulsos por revolução do encoder)

3. **Cálculo do Comprimento Total**:
   ```
   comprimentoFio = rotacoesCilindro × CIRCUNF_CILINDRO
   ```

### Cálculo do Diâmetro

O diâmetro da bobina é calculado usando a relação entre o comprimento total do fio e o número de voltas:

```
diametroBobina = (comprimentoFio / (voltas × π)) × FATOR_CORRECAO
```

Onde:
- `comprimentoFio` é o comprimento total do fio em milímetros
- `voltas` é o número de voltas contadas pelo sensor magnético
- `π` é a constante PI (3.14159...)
- `FATOR_CORRECAO` é 0.891 (calibrado para maior precisão)

## Detecção de Sentido

O sistema detecta automaticamente se a bobina está sendo enrolada ou desenrolada:

1. Compara o valor atual do encoder com o último valor registrado
2. Se o valor aumentou, está enrolando
3. Se o valor diminuiu, está desenrolando

## Características Especiais

1. **Precisão**:
   - Trabalha com valores inteiros para maior estabilidade
   - Fator de correção calibrado (0.891) para maior precisão
   - Evita valores negativos de diâmetro e voltas

2. **Monitoramento em Tempo Real**:
   - Exibe o sentido do movimento (Enrolando/Desenrolando)
   - Mostra o número de voltas atual
   - Apresenta o comprimento total do fio
   - Indica o diâmetro atual da bobina

3. **Robustez**:
   - Usa interrupções para não perder pulsos do encoder
   - Tratamento de debounce no sensor magnético
   - Proteção contra valores negativos

## Por que Usar Este Sistema?

1. **Precisão**: O uso do encoder de 2500 PPR oferece alta resolução na medição
2. **Tempo Real**: Medições instantâneas durante o processo
3. **Bidirecional**: Funciona tanto no enrolamento quanto no desenrolamento
4. **Não-Invasivo**: Não interfere no processo de bobinamento
5. **Baixo Custo**: Utiliza componentes comuns e acessíveis
6. **Manutenção Simples**: Poucos componentes móveis
7. **Adaptável**: Pode ser calibrado para diferentes diâmetros de cilindro

## Limitações e Considerações

1. O sistema assume que não há escorregamento entre o fio e o cilindro superior
2. A precisão depende da correta instalação do sensor magnético
3. O fator de correção pode precisar de ajustes para diferentes tipos de bobinas
4. É importante manter o encoder limpo e bem fixado para evitar erros de leitura 