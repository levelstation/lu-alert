# Wio RC8 · Kanäle in Inbox und Live RX

**LU-Alert für MeshCore ist ein unabhängiges Community-Projekt für Luxemburg und die Region, keine offizielle LU-Alert-App.** MeshCore-Textnachrichten können verspätet eintreffen oder verloren gehen. Keine Gewähr für Zustellung, Vollständigkeit oder Aktualität; kein Ersatz für offizielle Warnungen oder Notfallkommunikation. [Offizielles Warnsystem LU-Alert](https://lu-alert.lu/de.html).

## Empfangskanal selbst auswählen

1. Im Wio-Hauptmenü **Messages** mit ENTER öffnen.
2. **Live RX / Inbox** wählen und mit ENTER öffnen. Die Ansicht startet mit **Alle Kanäle**.
3. In der Inbox öffnet ENTER die RX-Kanalauswahl.
4. Mit dem Joystick wählen, mit ENTER übernehmen. MENU kehrt ohne Änderung zur bisherigen Ansicht zurück.

Die RX-Auswahl enthält „Alle Kanäle“ sowie diese zehn Namen, in derselben Reihenfolge wie Quick TX:

| Reihenfolge | Kanal |
| --- | --- |
| 1 | #public |
| 2 | #test |
| 3 | #lu-alert |
| 4 | #trafic |
| 5 | #luxembourg |
| 6 | #hammradio |
| 7 | #bot |
| 8 | #emergency |
| 9 | #saarland |
| 10 | #trier |

Quick TX zeigt vier, vier und zwei Kanäle auf drei Seiten. Die RX-Auswahl hat mit „Alle Kanäle“ elf Einträge und ebenfalls drei Seiten.

## Was die Auswahl ändert

Die Auswahl filtert ausschließlich die lokale Anzeige. Der Empfang auf anderen korrekt eingerichteten Kanälen läuft weiter. Sie stimmt das Funkmodul nicht um, legt keine Funk- oder Kanalprofile an, übernimmt keine Schlüssel und sendet keine Nachricht. Alle Sendungen benötigen weiterhin die ausdrückliche Quick-TX-Bestätigung.

Die Inbox ist ein gemeinsamer RAM-Puffer mit höchstens **acht Nachrichten insgesamt**, nicht acht pro Kanal. Auch andere empfangene Kanäle können ältere Einträge verdrängen. Ein leerer Filter bedeutet deshalb nur „keine passende RAM-Nachricht“, nicht „kein Verkehr“. Es gibt hier kein dauerhaftes Nachrichtenarchiv.

Die Anzeige ist an die vorhandene Kanalzuordnung gebunden. Wird der gespeicherte Kanalname oder sein Schlüssel geändert oder ist die Zuordnung nicht mehr eindeutig, erscheint der gewählte Kanal als nicht verfügbar. Den gewünschten Kanal nach der Änderung erneut auswählen. Es werden keine anderen Schlüssel oder Kanäle stillschweigend eingesetzt.

## Nach dem Senden lesen

Nach der lokalen Annahme eines Quick-TX-Auftrags öffnet ENTER die RX-Ansicht desselben Kanals. **DEVICE ACCEPTED** bestätigt nur die lokale Annahme, keine Zustellung oder Bot-Antwort. Es gibt keine automatischen Wiederholungen.

`#emergency` ist ein Kanalname, keine Notruffunktion. Eine Überwachung oder Antwort durch Hilfsdienste wird nicht zugesagt.

## Bisherige Funktionen bleiben erhalten

Die optionale vierstellige PIN-Sperre und die Wio-Laufschrift bleiben erhalten. Gesperrte Tasten blockieren neue Quick-TX-Aufträge; Empfang und Hintergrundfunktionen laufen weiter. [PIN-Bedienung](SCREEN-PIN.md) · [Laufschrift](TEXT-SCROLL.md) · [Vorlagen](COMMANDS.md).

Diese Erweiterung betrifft **Wio RC8**. Die vorhandene Heltec-dev4-Vorschau behält ihre bisherigen acht Kanalmenüs. Die neue manuelle RX-Kanalauswahl ist keine Heltec-Freigabe. Es wurde kein Gerät geflasht.

[Wio mit Demodaten ausprobieren](https://lu-alert.nosrv.eu/simulator/?demo=channels) · [Wio-Downloads](https://lu-alert.nosrv.eu/downloads/?board=wio).
