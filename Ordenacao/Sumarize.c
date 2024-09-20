/* 

Busca Sequencial
    roda um while até o maximo 
    ou enquanto v[i] for menor que o k
    quando parar verifica se i == max
    se for retorna -1, se não retorna i

Busca binária
    inicia start = 0 e end = max
    roda um while enquanto start < end
    middle = (start + end)/2
    se middle é igual a k sai
    se for maior start = middle + 1
    se for menor end = middle - 1
    se sair do while, retorna -1

Bubble sort
    vai comparando a posição com a próxima
    vai levando o maior para o final
    reduz o final e começa de novo

select sort
    vai procurando o menor numero
    quando acha coloca no começo
    aumenta o começo e faz de novo

insert sort 
    divide o vetor em 2, i e j
    i vai ser o normal
    j vai ser o ordenado
    i começa em 1
    j começa em 0
    vai pegando cada j e ordenando em i
    ordenando da direita pra esquerda
    comparando até achar algum menor que ele
    ai insere

Quick Sort 
    gera uma posição aleatório
    joga o numero para o fim
    armazena o numero em uma variavel k
    coloca uma posicao ip como inicio
    vai comparando todos com k
    se for menor troca com a posicao ip e ip++
    no fim troca ip com o final de novo
    depois chama 2 recursão
    uma para os que estão antes (fim = ip - 1)
    e outra para os que estão depois (inicio = ip + 1)

*/