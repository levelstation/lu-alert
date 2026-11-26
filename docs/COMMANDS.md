# LU-Alert für MeshCore · Kanäle und Bedienung

**Unabhängiges Community-Projekt für MeshCore in Luxemburg und der Region, keine offizielle LU-Alert-App.** Das [offizielle Warn- und Informationssystem LU-Alert](https://lu-alert.lu/de.html) wird von den öffentlichen Behörden betrieben. MeshCore-Textnachrichten können verspätet eintreffen oder verloren gehen. Keine Gewähr für Zustellung, Vollständigkeit oder Aktualität; kein Ersatz für offizielle Warnungen oder Notfallkommunikation.

## Wio RC8: zehn Kanalmenüs

Die manuelle Auswahl in Inbox und Live RX sowie Quick TX verwenden dieselben zehn Kanalnamen, in dieser Reihenfolge. In der Inbox kann außerdem kanalübergreifend gelesen werden. Quick TX zeigt die zehn Kanäle auf drei Seiten: vier, vier und zwei. Die RX-Auswahl enthält zusätzlich „Alle Kanäle“ und damit elf Einträge.

| Wio-Kanalmenü | Quick-TX-Vorlagen |
| --- | --- |
| #public | Hallo · Moin · Wie geht’s? · ACK 75 |
| #test | Ping · Test · Hop |
| #lu-alert | meteo · hochwasser; RAD und Warnungen ohne hinterlegten Text gesperrt |
| #trafic | traffic · info · A1 · A3 · A4 · A6 · A7 · A13 |
| #luxembourg | Hallo · Moin · Wie geht’s? · ACK 75 |
| #hammradio | Hallo · Moin · Wie geht’s? · ACK 75 |
| #bot | Platzhalter ohne Sendetext; Versand gesperrt |
| #emergency | Hallo · Moin · Wie geht’s? · ACK 75 |
| #saarland | Hallo · Moin · Wie geht’s? · ACK 75 |
| #trier | Hallo · Moin · Wie geht’s? · ACK 75 |

Das sind Menüvorlagen für die vorhandene Tracker-Konfiguration, keine mitgelieferten Kanäle oder Schlüssel. Fehlt ein passender Kanal oder ist seine Zuordnung mehrdeutig, wird der Versand blockiert. Es werden keine Kanalprofile angelegt oder ersetzt.

`#emergency` ist ein Kanalname. Er stellt keine Notruffunktion her und garantiert keine Überwachung oder Antwort durch Hilfsdienste.

## Inbox und Live RX

[Ausführliche RX-Kanalbedienung](CHANNELS.md).

Im Hauptmenü „Messages“ mit ENTER öffnen und „Live RX / Inbox“ wählen. Die Ansicht startet mit „Alle Kanäle“. Dort öffnet ENTER die RX-Kanalauswahl: mit dem Joystick wählen, mit ENTER übernehmen oder mit MENU abbrechen. „Alle Kanäle“ zeigt die lokal gespeicherten Nachrichten kanalübergreifend. Die Kanalwahl ändert nur die Ansicht; Empfang auf anderen korrekt eingerichteten Kanälen läuft weiter. Sie stimmt das Funkmodul nicht um.

Nach einer lokal angenommenen Quick-TX-Nachricht öffnet ENTER die RX-Ansicht desselben Kanals. Eine leere Ansicht bedeutet, dass im lokalen Nachrichtenpuffer keine passende Nachricht liegt. Sie beweist weder, dass der Kanal still ist, noch dass eine Anfrage angekommen ist. Der Puffer enthält höchstens acht Nachrichten und ist kein dauerhaftes Archiv.

## Quick TX

Kanal wählen → Vorlage wählen → exakten Text prüfen → mit ENTER senden. Die Texte der Botvorlagen sind gewöhnliche MeshCore-Nachrichten. Eine Antwort oder eine bestimmte Funktion des erreichbaren Bots wird nicht zugesichert. Ein fehlender Befehlstext bleibt gesperrt.

„DEVICE ACCEPTED“ bestätigt nur die lokale Annahme, keine Zustellung und keine Bot-Antwort. Es gibt keine automatischen Wiederholungen. Die Tastensperre blockiert neue Sendungen; Empfang und Hintergrundfunktionen bleiben aktiv.

## Lesen und Sperren

Überlange Wio-Texte laufen nach kurzer Lesepause nach links. Kurze Texte bleiben stehen. Auf/Ab bewegt die Nachrichtenansicht, Links/Rechts blättert durch die verfügbaren lokalen Nachrichten. Ein anderer Eintrag beginnt wieder am Textanfang.

Zweimal MENU innerhalb von 1,2 Sekunden schaltet Sound an oder aus. Dreimal MENU sperrt oder entsperrt. Eine optionale vierstellige PIN wird unter „Bildschirmsperre“ erstellt, geändert oder entfernt. [PIN-Bedienung](SCREEN-PIN.md).

## Heltec bleibt eine eigene Vorschau

Die vorhandene Heltec-dev4-Vorschau mit PRG-Bedienung und PIN bleibt unverändert. Sie verwendet weiterhin die bisherigen acht Kanalmenüs: #Public, #Test, #LU-Alert, #trafic, #luxembourg, #saarloorlux, #trier und #bot. Die neue Zehnerliste und manuelle RX-Kanalauswahl dieser Wio-Ausgabe werden nicht als Heltec-Funktion zugesagt. [Heltec-Bedienung](HELTEC-V4.3.md).

## Ausprobieren

[Wio-Kanalauswahl im Browser](https://lu-alert.nosrv.eu/simulator/?demo=channels) · [Wio-Downloads](https://lu-alert.nosrv.eu/downloads/?board=wio) · [Heltec-Vorschau](https://lu-alert.nosrv.eu/simulator/heltec/?demo=pin).

Alle Browserereignisse sind lokale Demodaten, keine Funk-, GPS- oder BLE-Verbindung. Wio RC8 und Heltec dev4 sind Vorschauen; die aktuellen Änderungen wurden nicht auf ein Gerät geflasht.
