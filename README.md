# ATIVIDADE 1 - Bubble Sort 

São feitos 10.000 testes de ordenção de uma lista randômica usando os dois algoritmos. O tempo de cada teste é registrado em um vetor (correspondente ao algoritmo), do qual obtemos a média e variância.

### Output:
```
Lista desorganizada: 
Payload: 84 87 78 16 94 36 87 93 50 22 

Bubble Sort (Padrão): 
Payload: 16 22 36 50 78 84 87 87 93 94 

Bubble Sort (Otimizado): 
Payload: 16 22 36 50 78 84 87 87 93 94 


Dados do algoritimo padrão: 
Média: 63.7308
Variância: 9.76033

Dados do algoritimo otimizado: 
Média: 63.9733
Variância: 11.3094
```

Percebemos que os dois algoritimos têm resultados similares. Isso acontece porque o algoritimo padrão tem um resultado melhor para as listas que estão muito desordenads, enquanto o segundo algotimo é mais rápido pra listas parcialmente ordenadas. Para ilustrar isso, basta imagina uma lista ordenada de forma decrescente, ambos teriam o máximo de iterações, mas o algoritimo otimizado iria fazer mais operações, pois sempre verifica se devem haver mais iterações.

# ATIVIDADE 2 - Selection Sort 

São feitos 10.000 testes de ordenção de uma lista randômica usando os dois algoritmos. O tempo de cada teste é registrado em um vetor (correspondente ao algoritmo), do qual obtemos a média e variância. Mesma metodologia da primeira atividade.

### Output:
```
Lista desorganizada: 
Payload: 84 87 78 16 94 

Selection Sort (Padrão): 
Payload: 16 78 84 87 94 

Selection Sort (Otimizado): 
Payload: 16 78 84 87 94 


Dados do algoritimo padrão: 
Média: 64.2353
Variância: 12.7807

Dados do algoritimo otimizado: 
Média: 37.8098
Variância: 2.57702
```

Nessa segunda atividade, vemos que o Selection Sort otimizado é de fato mais rápido que o algoritimo padrão. Olhando para a variância, vemos que o tempo do algotimo otimizado é distribuido concentrando valores próximos à média. Já com o algoritimo padrão é mais fácil de notar uma diferença expressiva de tempo comparando várias execuções.
