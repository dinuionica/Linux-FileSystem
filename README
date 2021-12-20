325 CA - DINU ION-IRINEL
TEMA 1
------------------------
IOCLA - Sistemul lui Biju


Implementare:

Pentru rezolvarea temei am simulat o serie de operatii specifice
unei liste simple inlantuite pentru a implementat sistemul de fisiere
linux. De asemenea, pentru o modularizare buna a codului am impartit
functiile in mai multe fisiere header.


main-> In cadrul acestei functii am alocat memorie pentru
input, am creat root-ul si directorul curent si am apelat
functia de parsare pentru comenzi.


FUNCTIONS.C :

create_root-> In cadrul acestei functii am alocat memorie 
pentru structura, am alocat si creat numele si am redirectat
pointerii catre NULL.

check_exist_directory-> In aceasta functie am parcurs lista
de directoare si am verificat daca exista un director cu numele
dorit. In caz afirmativ am returnat true.

check_exist_file-> In mod similar am parcurs lista de fisiere
si am verificat daca exista deja un fisier cu acelasi nume.

check_exist-> In cadrul acestei functii am folosit functiile 
implementate mai sus pentru a verifica daca exista ori un director
ori un fisier cu numele dorit in directorul curent.

touch-> In cadrul acestei functii, am verificat daca exista deja 
un fisier cu acelasi nume. Daca nu, am alocat si am creat structura
unui fisier. Apoi am tratat cazul in care lista de fisierele este 
goala, iar daca nu am parcurs lista pana la final, si am adaugat
noul fisier pe ultima pozitie.

mkdir-> Am procedat similar functiei touch, doar ca rationamentul
a fost aplicat pe lista de directoare.

ls-> In cadrul acestei functii, am parcurs lista de subdirectoare
si am afisat fiecare director iar apoi am parcurs lista de 
fisiere si am afisat de asemenea fiecare fisier.

rm-> In cadrul acestei functii am verificat daca exista deja 
un fisier cu acelasi nume in directorul curent. Apoi am verificat
daca fisierul ce trebuie sters este head-ul listei, caz in care am  
sters fisierul si am actualizat head-ul.In caz contrat am parcurs
lista si am cautat elementul dorit.Daca l-am gasit am realizat
legatura dintre fisierul precedent si cel urmator, apoi am sters
fisierul curent, eliberand si memoria alocata.

__rmdir-> In cadrul acestei functii am parcurs fiecare subdirector
din directorul curent, si am apelat functia recursiva pentru 
fiecare dintre acestia pentru a sterge continutul, apoi am sters 
subdirectorul. In final am sters si fiecare fisier care se afla 
in directorul curent.

rmdir-> Pentru inceput am verificat daca exista un director cu numele
pe care dorim sa il stergem. Daca directorul este head-ul listei, 
am actualizat head-ul, am sters recursiv continutul si apoi am sters
si directorul. In caz contrar am parcurs lista de subdirectoare si am
cautat directorul cu numele dorit. Similar, am sters continutul si 
apoi directorul in sine.

cd-> In cadrul acestei functii am verificat daca argumentul transmis
ca parametru este "..", caz in care am schimbat directorul curent
cu parintele acestuia. Altfel, am parcurs lista de subdirectoare, am
gasit directorul cu numele dorit si am schimbat directorul curent
cu directorul gasit.

pwd-> Pentru realizarea acestei functii am folosit doua string-uri
in care am pastrat numele directorului. Plecand de la final, am
parcurs directoarele parinte, cat timp nu am ajuns la root. De fiecare
data, realocam memoria pentru stringuri, adaugam in auxiliar string-ul din path,
apoi adaugam numele directorului curent, si la final adaugam in path ceea
ce tocmai s-a adaugat in string-ul auxiliar. Cand am ajuns in directorul 
root, am realocat memoria, am adaugat si numele acestuia la path, si am 
eliberat memoria alocata pentru string-ul auxiliar folosit.

stop-> In cadrul acestei functii am parcurs toata lista de fisier,
si am sters fiecare fisier, apoi in mod similar am sters fiecare 
director. In final am sters si directorul root.

tree-> Am realizat o implementare recursiva a functiei. Am parcurs
lista de subdirectoare si pentru fiecare dintre acestia, am apelat 
functia in mod recursiv pe baza unui level, pentru a-i afisa continutul.
La final am afisat si fiecare fisier continut.

mv_file-> Pentru inceput, daca exista un singur fisier in directorul 
curent, i-am actualizat numele si am oprit functia. In mod similar 
functiilor de mai sus, am tratat cazul in care trebuie modificat
numele fisirului din head, am actualizat head-ul si am adaugat fisierul
la finalul liste. Daca nu, am parcurs lista de fisier, am actualizat
pozitia pe care se afla fisierul dorit, i-am schimbat numele si 
l-am adaugat la final.

mv_directory-> Am procedat in mod similar functiei de mv_file, doar ca
rationamentul a fost aplicat pentru directoare.

mv-> In cadrul acestei functii, am verificat daca exista fisierul/directorul
al carui nume dorim sa il modificam sau daca exista deja un director
cu noul nume dorit. Apoi in functie de existenta unui fisier sau director,
am apelat functii implementate: mv_file sau mv_directory.


COMMANDS.C :

split_commands-> In cadrul acestei am impartit string-ul command
transmis ca parametru pentru a obtine argumentele necesare 
functiilor touch, mkdir, mv etc. 

parsing_commands-> In cadrul acestei functii am citit inputul 
de la tastatura, am determinat comanda si argumentele necesare si
am apelat functiile corespunzatoare.

Pentru erorile legate de alocarea memoriei am folosit macro-ul
DIE preluat din headerul utils.h
