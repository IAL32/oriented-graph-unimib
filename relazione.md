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
I commenti sono deliberatamente scritti in inglese, poiché al termine della valutazione, il progetto verrà pubblicato sul [mio profilo su GitHub](https://github.com/IAL32/oriented-graph-unimib).

## Implementazione grafo

Come da specifica e comunicazioni successive, non sono state utilizzate liste per rappresentare la matrice di adiacenza e la lista dei nodi.
È stato scelto di rappresentare la matrice di adiacenza con una matrice di dimensioni `n`x`n` scelta dall'utente, mentre la lista dei nodi è un vettore di tipo generico `T` di dimensioni `n`.

Per poter effettuare l'uguaglianza delle istanze dei nodi, è stato scelto di usare un funtore associato al tipo generico `E`, che verrà richiamato utilizzando l'operatore `()` con due parametri, cioè le due istanze da comparare. L'implementazione di questo funtore deve essere fatta dall'utente.

### Eccezioni implementate

Sono state implementate le seguenti eccezioni:
- `DuplicateException` <br /> Lanciata quando si cerca di aggiungere un nodo già presente all'interno del grafo.
- `IndexOutOfBoundsException` <br /> Lanciata quando si cerca di accedere ad una posizione fuori dai margini di accesso della matrice di adiacenza o della lista dei nodi.
- `NodeValueNotValidException` <br /> Lanciata quando si cerca di assegnare un valore non valido (quindi diverso da `0` e `1`) ad una cella della matrice di adiacenza.
- `NodeNotFoundException` <br /> Lanciata quando si cerca di accedere ad un nodo non presente all'interno del grafo.

### Metodi implementati

Sono stati implementati dei metodi di stampa, `void graph::print()` e `void graph::print_labels()`, che stampano rispettivamente la matrice di adiacenza a schermo, e la lista dei nodi (si presuppone che il tipo generico possa essere passato all'`operator<<` di `std::ostream`).

Come espresso da specifiche, sono stati implementati dei nodi di aggiunta e rimozione dei nodi, rispettivamente `void graph::add_node(T label)` e `void graph::remove_node(T label)`.
L'aggiunta dei nodi è stata implementata seguendo una logica molto semplice: la matrice di adiacenza sarà di dimensioni `(n + 1)`x`(n + 1)`, così come la lista dei nodi sarà di dimensioni `(n + 1)`.
Il valore di default nella nuova matrice di adiacenza per il nuovo nodo sarà di 0 su tutti gli archi.

Un esempio:

Matrice di partenza
|||||
|:--:|:--:|:--:|:--:|
|/| a | b | c |
|a| 1 | 1 | 1 |
|b| 1 | 1 | 1 |
|c| 1 | 1 | 1 |
Lista dei nodi `T = char`:
||||
|:--:|:--:|:--:|
|a|b|c|

Si cerca di aggiungere un nodo `d`, la matrice risultante sarà:

||||||
|:--:|:--:|:--:|:--:|:--:|
|/| a | b | c | d |
|a| 1 | 1 | 1 | 0 |
|b| 1 | 1 | 1 | 0 |
|c| 1 | 1 | 1 | 0 |
|d| 0 | 0 | 0 | 0 |

Lista dei nodi `T = char`:
|||||
|:--:|:--:|:--:|:--:|
|a|b|c|d|

La rimozione dei nodi è stata invece gestita in maniera un po' più complessa: la nuova dimensione della matrice di adiacenza sarà di `(n - 1)`x`(n - 1)`, e quella della lista dei nodi di `(n - 1)`. La lista dei nodi viene quindi aggiornata rimuovendo solo il nodo di interesse dalla vecchia lista. La matrice di adiacenza risulta essere il **minore complementare** della matrice di partenza, rimuovendo la riga e colonna corrispondente alla posizione dell'elemento rimosso.