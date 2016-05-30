# Tanks

Gra multiplayer dla dwóch osób. Zniszcz albo zostań zniszczony przez czołg przeciwnika.

### Wymagane biblioteki

Wszystkie wymagane biblioteki oraz pliki dll są folderze /Tanks/libs

[ENet](http://enet.bespin.org/index.html)

[SFML](http://www.sfml-dev.org)

[STP](https://github.com/edoren/STP)

### Jak uruchomić?

Klonujemy repozytorium a następnie tworzymy projekt z kodu w folderze src.
A biblioteki z folderu libs wypakowujemy z zip.

Następnie w properties projektu w zakładce C/C++ -> General -> Additional Include Directiories dodajemy ścieżki do folderów include bibliotek. Odpowiednio: libs\enet-1.3.13\include , libs\Parser STP\include oraz libs\SFML-2.3.2\include.

W zakładce Linker -> General -> Additional Library Directiories dodajemy ścieżki do folderów z bibliotekami.
Odpowiednio libs\enet-1.3.13, libs\Parser STP\lib oraz libs\SFML-2.3.2\lib.

W zakładce Linker -> Inpute -> Additional Dependencies dodajemy wpisy dla trybu Debug:
> sfml-audio-d.lib
sfml-graphics-d.lib
sfml-main-d.lib
sfml-network-d.lib
sfml-system-d.lib
sfml-window-d.lib
enet.lib
ws2_32.lib
winmm.lib
STP-d.lib



### Diagramy

Znajdują się w folderze /Tanks/diagrams

Są to:

1.Diagram klas

2.Diagram aktywności

3.Diagram scenariuszy przypadków użycia

## Autorzy

Marcin Migda

Dominik Nowak

Mateusz Skocz

Krzysztof Pęzioł
