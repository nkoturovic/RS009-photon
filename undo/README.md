## Undo - Šablonska klasa

- Cilj ove klase je da čuva istoriju akcija, i omogućava da instancu objekta koju obmotava vrati u bilo koje pređašnje stanje. 
- Ova klasa ima potpuno vlasništvo nad objektom koji čuva. 
- Izmena objekta se vrši metodom `action(Action = std::function<void(X& x))` koji prima instrukcije od korisnika kako da izmeni objekat.
- Na osnovu prosleđenih akcija Undo će kasnije znati kako da vrati objekat koji obmotava u pređašnje stanje.

```c++
auto xUndo = Undo<int>(3); // x = 3

/* uzimamo referencu na nas broj */
const int &xRef = xUndo.current();
cout << xRef << '\n';

/* Izmene broja vrsimo posredstvom akcija */
xUndo.action([](int &x) { x++; });
xUndo.action([](int &x) { x = 25; });
cout << xRef << '\n';

xUndo.undo(); // vracamo se korak unazad
cout << xRef << '\n';

xUndo.redo(); // idemo korak unapred
cout << xRef << '\n';

xUndo.undo(); // vracamo se korak unazad
cout << xRef << '\n';

xUndo.undo(); // vracamo se korak unazad
cout << xRef << '\n';
```
```
3
25
4
25
4
3
```
