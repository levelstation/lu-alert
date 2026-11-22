# LU-Alert – übernommene Bot-Befehle

Quelle ist die vom Nutzer gelieferte Befehlsliste. Es wurden nur Syntax und Beschreibungen übernommen; die Fotos, persönlichen Daten und dortigen Kanalnummern werden nicht veröffentlicht. Die Vorlagen binden vorhandene Kanäle zur Laufzeit eindeutig über ihren Namen. Keine Schlüssel, Kontakte oder Gerätekonfiguration werden hinzugefügt.

Im lokalen Heltec-Profil sind 30 Vorlagen für `#LU-Alert` und 24 für `#trafic` enthalten. `#Public`, `#Test`, `#luxembourg`, `#saarloorlux`, `#trier` behalten ihre allgemeinen Vorlagen. `#bot` bleibt ohne erfundenen Befehl deaktiviert.

| Kanal | Kanonische Befehle im Menü |
| --- | --- |
| LU-Alert | `meteo`, `help`, `rad`, `pegel`, `pegel vianden`, `pegel <Ort>`, `pegel <Nummer>`, `pegel alle`, `pegel alle <Seite>`, `pegel mosel`, `hochwasser`, `erdbeben`, `erdbeben aktuell`, `erdbeben letzte` |
| LU-Alert und trafic | `trafic`, einzeln `trafic A1`, `trafic A3`, `trafic A4`, `trafic A6`, `trafic A7`, `trafic A13`, `unfall`, `panne`, `stau`, `baustelle`, `wartung`, `wartung aktuell`, `wartungsarbeiten`, `stoerung`, `hindernis` |
| trafic zusätzlich | `help`, `trafic <Seite>` sowie Seitenwahl für jede der sechs Autobahnvorlagen, etwa `trafic A4 2` |

Ort und Stationsnummer werden mit einem PRG-Zeicheneditor eingegeben (maximal 24 Zeichen); Seitennummern werden von 1 bis 999 gewählt. Der Ortseditor startet mit dem dokumentierten Beispiel `vianden`, das vor dem Versand bearbeitet werden kann. Leere Parameter sind nicht bestätigbar. `<Ort>`, `<Nummer>` und `<Seite>` werden niemals als Platzhalter gesendet. Nach der Eingabe folgt stets eine separate Vorschau und Sendebestätigung. Autobahnsyntax bleibt `trafic A13`, nicht `trafic A 13`.

Die Liste nennt außerdem Aliase: `hilfe`/`info` für `help`, `traffic` für `trafic`, `accident` für `unfall`, `stillstand` für `stau`, `störung` für `stoerung` sowie `technische störung` im trafic-Kanal. Für Strahlung verwendet die UI den ASCII-Befehl `rad`. Es gibt keine unnötigen doppelten Vorlagen für gleichartige Aliase.

Die Syntax stammt aus der Nutzerliste. Abgesehen von der bisherigen Nutzerbestätigung zu `meteo` wurden tatsächliche Bot-Antworten in diesem Auftrag nicht am Funk geprüft: **UNTESTED**. Das `?` im Menü beziehungsweise „Bot unbestaetigt“ kennzeichnet diesen Status, nicht eine erfundene Übertragungsbestätigung.

Der bisher veröffentlichte Wio-Stand wurde nicht ersetzt. Das erweiterte Katalogprofil ist über `MESHIS_HELTEC_PRG` beziehungsweise optional `LU_ALERT_BOT_CATALOG` selektierbar; das allein erstellt kein neues Wio-Release.
