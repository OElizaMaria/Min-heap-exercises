# Min-heap-exercises


    TASK 1

Am folosit un Min heap cu campurile data si nume pentru a citi
informatiile din fisiere. A urmat sortarea prin sort_for heap.
Face un fel de sortare bubble, mai intai dupa frecventa iar in
cazul in care frecventa e la fel o face dupa nume. Dupa acea se
face functia extrage_si_creeaza care ia datele in seturi de 2, face
nod nou pentru cele 2 si sorteaza din nou heap ul pentru a asigura
ca urmatorul nod facut este dupa alte date. In final se face 
initializare_binar care pune informatiile din heap in arbore 2
cate 2, verificand daca parintele este suma elementelor din heap si/sau
daca se gaseste numele. In final print_binary se face cu un fel de queue
care trece de la stanga la dreapta pe la toate.

    TASK 2

Decodificare se face prin functia cu acelasi nume astfel: daca e 0 se
verifica daca e frunza, in cazul in care este frunza se printeaza si se
trece la radacina. La fel si cu 1. Daca ajungem la caractreul newline, 
verificam sa nu vim la radacina, adica cazul in care pe linie e doar o
frunza codificata si daca nu e, printam ce avem in temporar. Printarea se
faace prin fprintf in argv[argc-1] deoarece acolo se afla fisierul de 
output.

    TASK 3  

Codificarea se face printr-o serie de str-uri si o functie verifica, 
basically daca in left de exemplu gasim cu strstr numele cautat mergem
in acea directie si printam 1. Functia este structurata ca un while infinit
care inceteaza atunci cand am ajuns la destinatie prin linia if (strcmp(s)==0)
in cazul acela se printeaza doar newline. Checkerul pica 3 teste deoarece 
exista nume de arbore care sa aiba nume similare cu cel cautat.

    TASK 4  

Cautarea parintilor se face din nou printr o serie de strstr uri, pasul initial
este la radacina, apelam functia verifica, care verifica pe rand ca toate numele
sa se afle in numele copiilor radacinii, fie stanga, fie dreapta. In cazul in care
le gaseste merge in firectia aceea si continua cu un for.
Valgrind or lack there of. Am incercat sa fac un free tree recursiv dar se pare ca
exista memorie alocata care nu o pot gasi asa ca imi asum soarta. A real valgrind
hater here

