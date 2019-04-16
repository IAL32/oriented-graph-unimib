<style> table { width: 100% } </style>
# <center>Relazione Progetto C++ <br /> Aprile 2019 </center>

|||
|:--:|:--:|
| Nome |        Adrian David |
| Cognome |     Castro Tenemaya |
| Matricola |   816015 |
| Mail |        a.castrotenemaya@campus.unimib.it |
| Tempistiche | Dal 29/03/2019 al 29/04/2019 |

## Introduzione

Ho scelto di rappresentare la matrice di adiacenza del grafo orientato nella seguente maniera: un puntatore di puntatori a numeri interi, dove il numero intero centenuto all'interno di ogni cella può essere solo `0` (quando non esiste un arco tra il nodo di partenza ed il nodo di arrivo) ed `1` (viceversa, l'arco esiste e parte dal nodo di partenza al nodo di arrivo).
Ho inoltre scelto di rappresentare gli identificativi dei nodi con un puntatore al tipo generico `T`.

## Implementazione grafo

