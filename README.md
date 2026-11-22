# LU-Alert · MeshCore Luxembourg

**Version 0.2 · v0.2.0-lu-alert-rc3 · eigenständige öffentliche Ausgabe.** Klassische OLED-Menüs und animiertes LU-Alert-Logo, ohne Pixelbegleiter oder Board-Charakterauswahl. Eigene Mac-App und eigene DFU-Datei. Keine persönliche Tracker-Konfiguration enthalten.

| Kanalmenü | Vorlagen / Status |
|---|---|
| #Public | Hallo · Moin · Wie geht’s? · ACK 75 |
| #Test | Ping · Test · Hop |
| #LU-Alert | meteo: Nutzerbeobachtung bestätigt; hochwasser: unbestätigt; RAD/Warnungen ohne bekannte Syntax gesperrt |
| #trafic | traffic · info · A1 · A3 · A4 · A6 · A7 · A13: gewünschte Texte, Parser-Syntax unbestätigt |
| #luxembourg | Hallo · Moin · Wie geht’s? · ACK 75 |
| #saarloorlux | Hallo · Moin · Wie geht’s? · ACK 75 |
| #trier | Hallo · Moin · Wie geht’s? · ACK 75 |
| #bot | Menü vorhanden, bis zur bekannten Befehlssyntax gegen Versand gesperrt |

Die Schreibweise #saarloorlux entspricht dem Auftrag. Sie muss dem tatsächlich konfigurierten Kanalnamen entsprechen; keine stille Umleitung auf einen anderen Namen oder Index. Der produktive Bot-Parser liegt nicht vor. Es werden keine Kommandos erfunden und keine Serveränderungen vorgenommen. Acht Einträge werden auf zwei Seiten angezeigt. Die Tastensperre zeigt nur Titel und Pixel-Schloss.

[Website](https://lu-alert.nosrv.eu) · [GitHub](https://github.com/levelstation/lu-alert) · [Testbericht](TEST-REPORT.md) · [Heltec-Roadmap](docs/ROADMAP.md)

## Technik und Grenzen

Ziel ist der ursprüngliche Seeed Studio Wio Tracker L1 Pro OLED: 128 × 64 Pixel, ein Bit und ein gemeinsamer 1024-Byte-Framebuffer. Firmware und Mac-App verwenden dieselben Menü-, Quick-TX-, RX-, Sperr- und Displayklassen. Die App ersetzt Hardware durch ausdrücklich simulierte lokale Adapter. Bestehende MeshCore-/BLE-/Funkprotokolle bleiben erhalten.

Die Menünamen sind keine gespeicherten Kanalprofile. Ein Eintrag wird zur Laufzeit anhand des eindeutigen vorhandenen Namens gesucht und vor dem Senden einschließlich Schlüssel erneut geprüft. Die Anwendung erstellt, ändert und löscht keine Kanäle oder Schlüssel. Fehlt der passende Name, erscheint CHANNEL NOT CONFIGURED. Bereits bestehender Empfang und Companion-Funktionen bleiben erhalten.

Quick TX: Kanal → Vorlage → exakter Text → Enter. DEVICE ACCEPTED bedeutet lokale Annahme, kein Empfangs-ACK. Keine automatischen Wiederholungen. Die letzten acht RX-Texte bleiben in begrenztem RAM, Auf/Ab scrollt, Links/Rechts blättert. Gruppen-Absender werden nicht allein anhand eines Namenspräfixes als verifizierter Bot ausgegeben.

Drei entprellte MENU-Drücke innerhalb von 1200 ms sperren oder entsperren. Einzeldrücke werden bis zum Ende des Zeitfensters zurückgehalten. Zwei MENU-Drücke innerhalb von 1200 ms schalten Sound genau einmal an oder aus, ohne Menüaktion. Der Doppelklick wartet das vollständige Dreifachklick-Fenster ab; ein dritter Druck sperrt/entsperrt ohne Tonänderung. SOUND ON/OFF bestätigt den Zustand. Während der Sperre wird auch der Sound-Doppelklick ignoriert. Während der Sperre sind Navigation und neue Quick-TX-Aufträge blockiert; RX, GPS und Hintergrundfunktionen laufen weiter. Normaler Reset erhält Einstellungen und die bisherigen Dateischlüssel.

Radio und Live Radio / GPS zeigen `Noise est: … dBm`. Das ist der bereits vom MeshCore-Treiber geschätzte Grundrauschpegel, keine neue Messung durch das Menü. Die Anzeige liest nur `getNoiseFloor()`; sie startet weder Scan noch Kalibrierung und ändert keine Funkparameter. Vor einer gültigen Schätzung erscheint `not ready`. Der vorhandene Treiber mittelt 64 ruhige Empfangsproben und begrenzt die Schätzung nach unten auf -120 dBm. Der Wert kann nach einer Kalibrierung unverändert bleiben und ist kein laufender Spektrumanalysator. RSSI/SNR des letzten Pakets sind davon getrennte Werte.

GPS-Kurs ist ein Bewegungskurs aus frischen gültigen RMC-Daten, kein Magnetkompass. Ohne Fix, im Stillstand und nach acht Sekunden werden keine aktuellen Richtungen vorgetäuscht. UTC und Anzeigezeit bleiben getrennt; Europe/Luxembourg ist Standard.

Die bisherige Gerätebasis einschließlich Funk, BLE, Display und Bootloader wurde vom Nutzer bestätigt. Der genaue alte Build wurde nicht angegeben. Neue RC3-Dateien sind auf echter Hardware UNTESTED. Es wurde kein Gerät geflasht, gelöscht, zurückgesetzt oder umkonfiguriert. Die neue App verhindert automatische Dateisystemformatierung bei einem Mountfehler.

## Build und Start

Apple Silicon, macOS 14+, Apple Command Line Tools. Keine zusätzliche GUI-Bibliothek nötig; bestehende AppKit-App und vendorte Grafikquellen.

```sh
sh simulator/build.sh
./meshis-simulator
./meshis-simulator --self-test build/screenshots
SIM_SANITIZE=1 sh simulator/build.sh
./build/meshis-simulator-asan --self-test build/asan
```

Pfeile = Joystick, Enter = Joystick-Druck, Escape = MENU. 2× Escape/MENU in 1,2 s schaltet Sound an/aus; 3× sperrt/entsperrt. Der Doppelklick wird nach Ablauf des 1200-ms-Fensters ausgeführt. Cmd+R setzt nur die Simulation zurück. Der Simulator öffnet keine Geräteschnittstelle.

Firmware: Python-Umgebung mit PlatformIO 6.1.19 und pyelftools, dann `sh tools/build_firmware.sh`. Das Skript kompiliert ausschließlich und validiert BIN, UF2, echte Anwendungs-DFU, CRC und Speicherbereiche. Kein Upload-Schritt. Grundlage: MeshCore-Commit 75b04ef06def54b348400cb1b138afb6749ffd4f, S140 7.3.0 / FWID 0x0123. Abhängigkeiten mit Versionsbereichen und Compiler-Zeitstempel verhindern eine allgemeine Zusage bitidentischer Neubauten.

UF2-Family-ID 0xADA52840 ist keine Board-ID. Die individuelle INFO_UF2-Board-ID und installierte SoftDevice-Version wurden nicht ausgelesen. E-Ink und Pro 1W sind nicht unterstützt. Der individuelle OLED-Controller ist nicht anhand einer Panelkennzeichnung nachgewiesen.

[Offizielle Hardwaredokumentation](https://wiki.seeedstudio.com/wio_tracker_l1_node/) · MeshCore MIT, siehe LICENSE und vendor/meshcore/LICENSE · Adafruit GFX BSD, siehe simulator/vendor/adafruit-gfx/license.txt. Unabhängiges Community-Projekt.

## Websimulation

[Im Browser ausprobieren](https://lu-alert.nosrv.eu/simulator/). Die Browser-Version kompiliert denselben C++-Simulator nach WebAssembly: FirmwareScreens, QuickTx, KeyLock, MenuActions, LockRenderer und FramebufferDisplay. JavaScript skaliert ausschließlich den 1024-Byte-Framebuffer und reicht Eingaben weiter. Keine zweite Implementierung der Firmwaremenüs oder Animationen.

Pfeile/Enter/Escape sowie die sichtbaren Joystick-, ENTER-, MENU- und RESET-Tasten bedienen die Simulation. 2× MENU schaltet den simulierten Summerstatus; 3× sperrt/entsperrt. Kein Audio im Browser. Die Ereignisse sind lokale Testdaten, ohne echte Funk-, BLE-, GPS- oder Geräteschnittstelle. RESET erhält die Einstellungen dieser Sitzung; Neuladen startet eine neue Sitzung. Pause friert auch die Simulationszeit und Gestenerkennung ein.

Mit einem aktivierten offiziellen Emscripten-SDK **7.0.1**, Python 3 und Node.js:

```sh
sh tools/build_web_simulator.sh
sh tools/test_web_simulator.sh
python3 -m http.server 4176 --directory docs
```

Dann `http://localhost:4176/simulator/` öffnen. Für die native Vergleichsreferenz ist ein C++17-Compiler erforderlich. SDK-Installation: im offiziellen emsdk-Checkout `./emsdk install 7.0.1`, `./emsdk activate 7.0.1 --embedded`, dann `source ./emsdk_env.sh`. Kein SDK und keine Zugangsdaten sind im Projekt enthalten. Die Ausgabe ist statisch hostbar. Build- und Quellprüfsummen stehen in `docs/simulator/BUILD-MANIFEST.json`.

1272 native/WASM-Pixelvergleiche bestanden; Details in [Web-Testbericht](docs/simulator/TEST-REPORT.md). Der WebAssembly-Heap ist auf 16 MiB begrenzt; der OLED-Framebuffer bleibt 1024 Byte. Dies ist keine Emulation des nRF52840, Funkchips oder Bootloaders.
