# RS-IMG - Biblioteka za rad za slikama

## O Biblioteci

Biblioteka je napisana kao integralni deo projekta `Photon`:

<https://github.com/MATF-RS20/RS009-photon>

## Zavisnosti

- Linux operativni sistem
- Potrebno je na sistemu imati instaliranu `OpenCV 4.1.2` biblioteku.

## Buildovanje

Da buildujete biblioteku i dobijete je zapakovanu u `rsimage.tar.gz` kucajte: 

```
make
```

Biće generisani i test programi iz `demo` direktorijuma.

## Koriscenje biblioteke

- Extract-ujte fajl `rsimage.tar.gz` u folder projekta.
- Dobicete direktorijum sa header fajlovima i sa bibliotekom koja se staticki linkuje.
- Dobijenu biblioteku `librsimg.a` prilikom kompilacije navedite u listu zavisnosti (kao sto navodite .o fajlove).
- Potrebno je pri kompilaciji vaseg projekta izvrsiti dinamicko linkovanje sa `opencv` bibliotekom.
- Pogledajte demo primere u folderu `demo`.

## Primer (korisnikovog) Makefile-a

```
OPENCV_CFLAGS := $(shell pkg-config opencv --cflags)
OPENCV_LIBS := $(shell pkg-config opencv --libs)

CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic $(OPENCV_CFLAGS)
LDLIBS = $(OPENCV_LIBS)

main.out: main.o librsimg.a
	clang++ -o $@ $(CXXFLAGS) $(LDLIBS) $^ librsimg.a

main.o: main.cpp
	clang++ -c -o $@ $(CXXFLAGS) $<
	
.PHONY:
	clean

clean:
	rm -rf *.out *.o
```

## Primer koriscenja biblioteke

```c++
#include <iostream>
#include "rsimg/image.hpp"
#include "rsimg/transform.hpp"
#include "rsimg/display.hpp"
#include "rsimg/exception.hpp"

int main()
{
    try 
    {
        rs::Image img1("lena.png"); // may throw

        /* Kompozicija u redosledu primene (f | g)(x) = g(f(x)) */
        img1 <<= rs::Rotate(rs::Rotate::Direction::LEFT) 
               | rs::Rotate(rs::Rotate::Direction::RIGHT)
               | rs::Contrast(50)
               | rs::BlackNWhite();
        
        /* Klasicna kompozicija (f * g)(x) = f(g(x)) */
        img1 <<= rs::Rotate(rs::Rotate::Direction::LEFT) 
        rs::Image img2 = img1 << rs::Rotate(rs::Rotate::Direction::LEFT) 
                               * rs::Flip(rs::Flip::Axis::Y)
                               * rs::BlackNWhite();

        rs::stdisp.show(img2);
        rs::Display::waitKey();

        img2.write("output.png");

    } catch (const rs::Exception &e) 
    {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
```
