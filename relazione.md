# Relazione Progetto C++ <br /> Aprile 2019

|             |                                   |       |
| :---------: | :-------------------------------: | :---: |
|    Nome     |           Adrian David            |       |
|   Cognome   |          Castro Tenemaya          |       |
|  Matricola  |              816015               |       |
|    Mail     | a.castrotenemaya@campus.unimib.it |       |
| Tempistiche |   Dal 29/03/2019 al 29/04/2019    |       |

## Introduzione

Ho scelto di rappresentare la matrice di adiacenza del grafo orientato nella seguente maniera: un puntatore di puntatori a numeri interi, dove il numero intero contenuto all'interno di ogni cella può essere solo `0` (quando non esiste un arco tra il nodo di partenza ed il nodo di arrivo) ed `1` (viceversa, l'arco esiste e parte dal nodo di partenza al nodo di arrivo).
Ho inoltre scelto di rappresentare gli identificativi dei nodi con un puntatore al tipo generico `T`.
I commenti sono deliberatamente scritti in inglese, poiché al termine della valutazione, il progetto verrà pubblicato sul [mio profilo su GitHub](https://github.com/IAL32/oriented-graph-unimib).

## Implementazione del grafo

Come da specifica e comunicazioni successive, non sono state utilizzate liste per rappresentare la matrice di adiacenza e la lista dei nodi.
È stato scelto di rappresentare la matrice di adiacenza con una matrice di dimensioni `n` x `n` scelta dall'utente, mentre la lista dei nodi è un vettore di tipo generico `T` di dimensioni `n`.

Per poter effettuare l'uguaglianza delle istanze dei nodi, è stato scelto di usare un funtore associato al tipo generico `E`, che verrà richiamato utilizzando l'operatore `()` con due parametri, cioè le due istanze da comparare. L'implementazione di questo funtore deve essere fatta dall'utente.

Dove possibile ed opportuno, è stata sfruttata la classe `const_iterator` per ciclare attraverso la lista dei nodi del grafo.

Internamente sono state utilizzate delle funzioni di supporto per poter meglio gestire le funzioni esposte in `public`.

È stato inoltre cercato di onorare il paradigma **DRY** (*Don't Repeat Yourself*), cercando quindi di minimizzare le ripetizioni, dove possibile.

### Eccezioni implementate

Sono state implementate le seguenti eccezioni:
- Eccezione quando si cerca di aggiungere un nodo già presente all'interno del grafo.
- Eccezione quando si cerca di accedere ad una posizione fuori dai margini di accesso della matrice di adiacenza o della lista dei nodi.
- Eccezione quando si cerca di assegnare un valore non valido (quindi diverso da `0` e `1`) ad una cella della matrice di adiacenza.
- Eccezione quando si cerca di accedere ad un nodo non presente all'interno del grafo.

### Metodi implementati

Sono stati implementati dei metodi di stampa che stampano la matrice di adiacenza a schermo, e la lista dei nodi (si presuppone che il tipo generico possa essere passato all'`operator<<` di `std::ostream`).

Come espresso da specifiche, sono stati implementati dei nodi di aggiunta e rimozione dei nodi.
L'aggiunta dei nodi è stata implementata seguendo una logica molto semplice: la matrice di adiacenza sarà di dimensioni `(n + 1)`x`(n + 1)`, così come la lista dei nodi sarà di dimensioni `(n + 1)`.
Il valore di default nella nuova matrice di adiacenza per il nuovo nodo sarà di 0 su tutti gli archi.

La rimozione dei nodi è stata invece gestita in maniera un po' più complessa: la nuova dimensione della matrice di adiacenza sarà di `(n - 1)`x`(n - 1)`, e quella della lista dei nodi di `(n - 1)`. La lista dei nodi viene quindi aggiornata rimuovendo solo il nodo di interesse dalla vecchia lista. La matrice di adiacenza risulta essere il **minore complementare** della matrice di partenza, rimuovendo la riga e colonna corrispondente alla posizione dell'elemento rimosso.

Sono state implementate funzioni di interrogazione dello stato del grafo, come per la verifica dell'esistenza di un nodo, l'esistenza di un arco tra due nodi ed il numero effettivo degli archi all'interno del grafo.

Per la funzione di esistenza di un nodo si va ad interrogare la lista dei nodi per verificare l'esistenza del nodo `label` all'interno del grafo.

Per la funziona di esistenza di un arco si va ad interrogare il grafo per ottenere il valore contenuto nella matrice di adiacenza nella posizione corrispondente ai due nodi. Se è `1` allora l'arco esiste, `0` l'arco non esiste. Se uno dei due nodi non esiste c'è un errore.

Sono state implementate funzioni di modifica del grafo, quindi è possibile "attivare" un arco impostando il valore corrispondente al nodo di partenza e di arrivo ad `1`, o "disattivarlo" ponendolo a `0`.

## Main

Il main è stato costruito in maniera tale da testare tutte le funzionalità presenti nella classe `graph`.

I test sono divisi in moduli, dove ogni modulo rappresenta l'utilizzo di una nuova istanza di `graph` sul quale effettuare i test.

Il primo modulo prevede la creazione delle tre istanze `graph` che mi servono, con i relativi template e funtori. `g` e `g2` utilizzano il tipo `char`, mentre `g3` utilizza la classe `voce`. Inoltre, vengono testate tutte le funzioni base, come l'interrogazione del grafo e la sua modifica sia mediante i tipi utilizzati per il template (quindi `char`), che mediante l'utilizzo degli indici della matrice e della lista dei nodi. Tra le funzioni base includiamo anche la stampa della matrice rappresentante il grafo.

Il secondo modulo verifica che la copia da `g` a `g2` avvenga correttamente, verificando sia gli archi che i nodi.

Il terzo modulo si concentra sul test delle eccezioni, che possono avvenire per vari motivi, come tentativo di accesso a nodi non esistenti o posizioni non esistenti, o aggiunta di un nodo duplicato, o rimozione di un nodo non presente all'interno del grafo.

Il quarto modulo verifica il corretto funzionamento della classe `const_iterator`.

Il quinto modulo prevede l'utilizzo del grafo con template `voce`, per dimostrare l'utilizzo del funtore e di una classe non primitiva.