# LU-Alert 0.2 RC3 · Testbericht

Stand: 2026-11-22. Eigenes Profil: #Public, #Test, #LU-Alert, #trafic, #luxembourg, #saarloorlux, #trier, #bot. Keine Schlüssel und keine Gerätekonfiguration enthalten.

| Prüfung | Ergebnis |
|---|---|
| Nativer Apple-Silicon-Build, macOS 14+, Ad-hoc-Signatur | PASS |
| Profilbezogene Pixel-/Screenshot-/Navigationsfälle | 171 PASS |
| AddressSanitizer / UndefinedBehaviorSanitizer | 171 PASS |
| Native Fenstergrößen, vollständiger Framebuffer, ENTER/RESET | 3 Layouts PASS |
| Exakte Profilnamen und alle Vorlagen | PASS |
| Kanalzuordnung über Laufzeitnamen, Mehrdeutigkeit, geänderter Name/Schlüssel | PASS |
| Tatsächlicher MeshCore-Adapter unter ASan/UBSan, Fake-Transport | PASS |
| Sperre, entprellte Drücke, Zeitgrenzen, Reset ohne Einstellungsverlust | PASS |
| 2× MENU: ein Sound-Toggle, keine Navigation/Sendung | PASS |
| 3× MENU: kein Sound-Toggle; Doppelklick während Sperre ignoriert | PASS |
| SOUND ON/OFF, Quittierungsfenster, gespeicherter Tonstatus/Reset | PASS |
| RX bei Sperre, keine unbeabsichtigten Quick-TX-Aufträge | PASS |
| RAM-Inbox, Scrollen, Text-/Framebuffergrenzen | PASS |
| Noise-Schätzung: gültig, unbekannt, außerhalb des Wertebereichs; kein TX | PASS |
| Firmware-Compile, ELF-Bereiche, DFU-Manifest/CRC/BIN und UF2-Payload | PASS |
| MeshCore-/Companion-/BLE-/SX1262-Quellcode-Regressionsprüfung | PASS |
| Bestehende 1153 lokale Release-Dateien | UNCHANGED |
| Bisherige Gerätebasis: Funk, BLE, Display, Bootloader | USER_CONFIRMED |
| Neue RC3-Funktionen auf echter Hardware | UNTESTED |
| Heltec 4V2 | PLANNED / UNTESTED; kein Build |

Acht Menüs werden auf zwei Seiten dargestellt und getestet. Das klassische Profil zeigt keine Pixelbegleiter, Datum oder Uhrzeit auf dem Home-Bildschirm. Es verwendet ein eigenes animiertes Logo, einen Titel und ein Pixel-Schloss. `meteo` ist durch Nutzerbeobachtung bestätigt; weitere Bot-Syntax und der produktive Parser sind nicht nachgewiesen. RAD, Warnungen und der allgemeine Bot-Eintrag bleiben gesperrt. Gruppen-Absender werden nicht aus Textpräfixen als authentifiziert ausgegeben.

Die Grundrausch-Anzeige liest ausschließlich den vorhandenen MeshCore-Cache. Sie misst nicht neu, triggert keine Kalibrierung und ändert keine Funkparameter. Die Schätzung aus 64 Empfangsproben ist nach unten auf -120 dBm begrenzt und muss nicht fortlaufend aktualisiert werden. Kein Spektrumanalysator und keine reine Labor-Rauschmessung. Vor gültigem Wert: not ready. Der Simulator kennzeichnet seine negativen dBm-Beispiele als Simulation.

Gemeinsame Dateien sind zwischen beiden Projekten bytegleich geprüft: QuickTx.h, FirmwareScreens.h, LockRenderer.h, KeyLock.h und FramebufferDisplay.h. Unterschiedlich sind das kleine Kanalprofil, Branding, App-Identität, Einstellungen und Buildziel. Menü- und Sendelogik wurden nicht unabhängig nachgebaut.

Die neuen Pixelreferenzen wurden für die bewussten Profil-/Noise-Änderungen erzeugt, visuell kontrolliert und danach normal sowie sanitisiert verglichen. Vorherige Referenzen wurden separat erhalten. Die Website verwendet aus denselben Framebuffern erzeugte Bilder; keine zweite Firmware-Menüimplementierung.

Bootloader, Funk, BLE und Display wurden für die vorherige Firmware vom Nutzer bestätigt; deren genauer Build ist unbekannt. Die Agentenprüfungen sind reine Software-/Dateiprüfungen, kein Nachweis des neuen RC3 am Gerät. UF2-Family-ID ist keine Board-ID. Es wurden weder Ports noch ein gemounteter Tracker geöffnet. Kein Flash, Reset oder Factory Reset ausgeführt.

BUILD: PASS · SIMULATOR: PASS · IMAGE LAYOUT: PASS · NEW RC3 HARDWARE: UNTESTED · HARDWARE_FLASHED: NO.

GO für Simulator und öffentliches Quellcode-Alpha; keine Behauptung einer hardwarevalidierten RC3-Finalversion. Bedienung, Grenzen und Kanalnamen stehen in README.md. Heltec-Portierung steht in docs/ROADMAP.md.

## RC3-Doppelklick

1× MENU bleibt Zurück; 2× MENU schaltet Sound einmal; 3× MENU sperrt/entsperrt ohne Tonänderung. Für zwei Drücke wird nach dem inklusiven 1200-ms-Fenster ab dem ersten Druck auf den dritten gewartet. Keine zusätzlichen Wartepausen in der Hauptschleife. RX/GPS laufen weiter. Im gesperrten Zustand haben zwei Drücke keine Aktion. Auf dem Mac gilt dieselbe Logik für Escape und die sichtbare MENU-Taste. Der Tonstatus wird in der bestehenden separaten App-Preferences-Suite gespeichert und bei normalem Reset erhalten. Die bestehende Firmware-Methode toggleBuzzer speichert wie bisher den Tracker-Tonstatus.

Alle bisherigen 167 Pixelreferenzen blieben bytegleich; vier SOUND-ON/OFF-Popup-/Wiederherstellungsframes kamen hinzu. Neue RC3-Hardware und tatsächlicher Summer weiterhin UNTESTED; keine Geräteoperation durch den Agenten.

Am 22.11.2026 hat der Nutzer das Flashen und einwandfreie Funktionieren der zuletzt bereitgestellten LU-Alert-RC2-Version gemeldet. Die individuelle BIN-Prüfsumme wurde nicht unabhängig ausgelesen. Diese Nutzerbestätigung ist kein Test des neuen RC3-Doppelklick-Builds.

## Spätere Web-Ergänzung · 2026-11-22

Die nachstehenden Web-Dateien ergänzen die RC3-Ausgabe. DFU, BIN, UF2 und Mac-Download wurden dafür nicht verändert. Die obigen RC3-Prüfungen beschreiben weiterhin den RC3-Release; Meshis erhält unabhängig davon ein Board-Untermenü in RC4.

## Browser-Simulator

1272 native/WASM-Vergleiche aller Framebufferbytes und Zustände: PASS. Tatsächliche Browserbedienung und Layouts bei 1280/390 Pixeln: PASS. Siehe [Web-Testbericht](docs/simulator/TEST-REPORT.md). Keine Geräteverbindung.

## Heltec V4.3 – Vorschau

[Browser-Eingabetests](docs/simulator/heltec/UI-TEST-RESULT.json) · [Native/WASM-Vergleich](docs/simulator/heltec/TEST-RESULT.json) · [Mac-/Firmware-Testbericht](docs/HELTEC-TEST-REPORT.md). R2/R8-Compileziele, Hardware UNTESTED. Kein Gerät geflasht. Die bisherigen Wio-Referenzen und Downloaddateien wurden erneut unverändert geprüft.

## Gemeinsamer Funkmonitor für Wio und Heltec

[Neue Testergebnisse](docs/RADIO-LIVE-BUILD-MANIFEST.json) · [Protokoll-/Download-Regressionsprüfung](docs/RADIO-LIVE-REGRESSION.json) · [Bedienung](docs/RADIO-LIVE.md). Vollständige Namen, RSSI-Balken und direkte Browser-Einstiege; Wio- und Heltec-Builds PASS, neue Hardwaretests UNTESTED. Kein Gerät geflasht.

## Aktiver Zero-Hop-Scan

[Neuer Testbericht](docs/DISCOVERY-TEST-REPORT.json) · [Bedienung, Airtime und Grenzen](docs/DISCOVERY.md). Nativer MeshCore-Control-Discovery-Adapter; gemeinsame Wio-/Heltec-/WASM-Implementierung, keine echten Geräteports. Neue Hardwaretests UNTESTED.
