# Analizator składni

> ## JIMP zadanie z laboratorium nr 8

<br/>
<br/>

> ## Podział obowiązków

| Zadanie \ Osoba           | Kamil | Adrian | Poziom | Stopień Wykonania | Priorytet |
| ------------------------- | :---: | :----: | :----: | :---------------: | :-------: |
| Analizator leksykalny     |       |   x    | średni |      Gotowy       |     2     |
| Analizator składni        |   x   |        | trudny |      Gotowy       |     2     |
| Kontener danych           |       |   x    | trudny |      Gotowy       |     1     |
| Funkcja main              |   x   |        | średni |      Gotowy       |     3     |
| lista funkcji pomijalnych |       |   x    | łatwy  |      Gotowy       |     4     |
| Formatowanie wypisywannia |   x   |        | łatwy  |      Gotowy       |     4     |

<br/>

> ## Uruchomianie
>
> -   Programu\
>     W konsoli obsługującek Makefile oraz kompiler C wpisz
>
> ```bash
>    make init                  # Wymagane
>    make                       # Kompilacja
>    make [ test-all / test ]   # Jedna z
> ```
>
> `test-all` by wystestować odrazu wszystkie pliki w folderze testSourceFile \
> `test` by wybrać pliki poprzez wpisanie ich nazwy w konsoli
>
> W razie problemów z uruchomieniem komendy `test-all` | `test` należy użyć komedy `test-repair`
>
> Program posiada także komendy:
> `clean` - czyszczenie folderu /lib oraz /out z skomilowanych programów
> `init` - stworzenie niezbednych folderów do uruchomeina programu
