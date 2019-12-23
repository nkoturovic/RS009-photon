## Undo - Šablonska klasa

- Cilj ove klase je da čuva istoriju akcija, i omogućava da instancu objekta koju obmotava vrati u bilo koje pređašnje stanje. 
- Ova klasa ima potpuno vlasništvo nad objektom koji čuva. 
- Izmena objekta se vrši metodom `action(Action = std::function<void(X& x))` koji prima instrukcije od korisnika kako da izmeni objekat.
- Na osnovu prosleđenih akcija Undo će kasnije znati kako da vrati objekat koji obmotava u pređašnje stanje.

```c++
auto intUndo = Undo<int>(3); // x = 3

/* uzimamo referencu na nas broj */
const int &ref = intUndo.current();
cout << ref << '\n';

/* Izmene broja vrsimo posredstvom akcija */
intUndo.action([](int &x) { x++; });
intUndo.action([](int &x) { x = 25; });
cout << ref << '\n';

intUndo.undo(); // vracamo se korak unazad
cout << ref << '\n';

intUndo.redo(); // idemo korak unapred
cout << ref << '\n';

intUndo.undo(); // vracamo se korak unazad
cout << ref << '\n';

intUndo.undo(); // vracamo se korak unazad
cout << ref << '\n';
```
```
3
25
4
25
4
3
```
