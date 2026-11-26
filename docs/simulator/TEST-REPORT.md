# LU-Alert Wio · Browser-Simulation RC8

26. November 2026. Wio Tracker L1 Pro, 128 × 64 Pixel, 1024-Byte-Framebuffer.

Die Browseransicht verwendet denselben C++-Simulator wie die native Mac-App.
JavaScript reicht Eingaben weiter und zeichnet den Framebuffer. Es gibt keine
Geräteverbindung, keinen echten Funkverkehr und keine JavaScript-Nachbildung
der Nachrichtenfilter, Laufschrift oder PIN-Prüfung.

## Empfangskanäle und Quick TX

Zehn Kanalmenüs: #public, #test, #lu-alert, #trafic, #luxembourg, #hammradio,
#bot, #emergency, #saarland und #trier. ENTER in der Inbox öffnet die echte
C++-Kanalauswahl. Die Browserauswahl „RX-Kanal“ bedient denselben Filter und
zeigt dessen Zustand. „Alle“ verwendet den vorhandenen RAM-Eingang.

`?demo=channels` liefert acht lokale Beispielnachrichten. Die Filter #bot und
#emergency bleiben darin ausdrücklich leer. Das Beispiel legt keine Kanäle
an und sendet keine Funkpakete.

PASS: 33 zusätzliche native/WASM-Framebuffer-Vergleiche, 28 Funktionsgruppen.
Geprüft wurden die zehn Kanäle, Alle/Einzelfilter, die physische
ENTER-Auswahl, unveränderte RAM-Nachrichten sowie gesperrte Filter- und
Demoaktionen. TX blieb null. Der bestehende Simulatorvergleich bestand mit
1730 Framebuffer-Vergleichen und 149 Funktionsgruppen.

## PIN und Laufschrift

PASS: 969 PIN-Pixelvergleiche in 55 Funktionsgruppen; zusätzlich 72
Laufschrift-Vergleiche in 60 Funktionsgruppen. Einrichtung, Wiederholung,
Ändern/Entfernen, Fehlerwartezeit, gesperrter Neustart, weiterlaufender RX,
blockierter TX und die Lesepausen/Bewegung/Endpause wurden geprüft.

Die Bridge gibt keine PIN-Ziffern oder gespeicherten Prüfdaten aus. RESET
behält die PIN der aktuellen Sitzung; Neuladen startet ohne voreingestellten
Code. Der WASM-Heap bleibt auf 16 MiB begrenzt.

## Grenzen

Die neue Wio-Version ist nicht am echten Gerät geprüft; nichts wurde geflasht.
Heltec bleibt eine separate Vorschau. Alle elf Dateien im veröffentlichten
Heltec-Simulator wurden unverändert erhalten.
