Incepem cu o functie de read care incepe cu citirea nr. de pagini.
Apoi initializeaza matricea de adiacenta si matricea cu nr de
legaturi totale de pe fiecare pagina.
Printr-un loop obtinem si toate legaturile si le adaugam, iar
pe diagonala principala punem 0.
Calculam matricea cu diagonala L si citim si val1 si val2.

In functia main de PageRank initializam si output-ul cu un strcat.
Apelam fiecare functie si o printam.

Functia Iterative citste elementele si apoi foloseste formulele
algoritmului, adica calcularea M-ului si iteram pana cand
eroarea noastra este mai mica decat epsilon.

Functia Algebraic face acelasi lucru, dar M este calculat diferit,
nu mai folosim functia de inversa, ci o calculam noi mai simplu.
Apoi folosim algoritmul pentru a calcula si R, nu prin iteratii.
Calculam inversa cu ajutorul functiei PR_Inv care desparte
matricea in Q si R, pentru a calcula mai usor inversa (inversa
lui Q este Q'). Am folosit si functiile Gram_Schmidt si SST care
sunt cele din laborator.

Pentru Apartenenta nu facem altceva decat sa sortam cu functia
sort rezultatul R2 de la functia Algebraic si sa calculam
valoarea functiei cu ajutorul valorilor 1 si 2. Intre ele
avem ax + b, in rest 0 sau 1.