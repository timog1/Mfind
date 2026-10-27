# mfind

Multithreaded `find`-Clone in C mit Filtern für Dateiname und Dateigröße.
Ein Uni-Projekt (FHWS), das ich hierher übernommen habe.

Die Filter werden nacheinander angewendet. Eine Datei erscheint nur in der Ausgabe,
wenn sie alle Filter besteht.

## Build

    make

Das erzeugt die ausführbare Datei `mfind`.

## Usage

    ./mfind <verzeichnis> <filter...>

## Filter

| Option | Beschreibung |
|--------|--------------|
| `-n`   | Namensfilter mit Wildcards (`*` = beliebig viele Zeichen, `?` = genau ein Zeichen) |
| `-s`   | Größenfilter mit `>`, `<` oder `=` und Einheit `B`, `K`, `M`, `G` |

Beispiele für Größen: `>3000B`, `<5M`, `=10K`

## Beispiele

    # Dateien über 3000 Bytes, die mit "S" beginnen
    ./mfind . -sn ">3000B" "S*"

    # Dateien über 10 KB, die mit "log" beginnen
    ./mfind ./logs -sn ">10K" "log*"

    # Dateien unter 1 MB
    ./mfind . -s "<1M"

    # Dateien, die mit "A" oder "B" beginnen
    ./mfind . -n "A*" -n "B*"

## Tests

    cd src/test
    bash fulltest.sh        # automatisierter Test mit Zeitmessung