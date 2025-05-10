# Gas AI

Gas AI è un progetto innovativo per il monitoraggio, l'analisi e l'ottimizzazione delle risorse di gas utilizzando l'intelligenza artificiale.

## Caratteristiche
- Monitoraggio in tempo reale dei consumi di gas.
- Analisi predittiva basata su algoritmi di machine learning.
- Ottimizzazione delle risorse per ridurre i costi e migliorare l'efficienza.
- Interfaccia grafica (GUI) moderna e intuitiva per una gestione semplificata.

## Requisiti
- **Hardware**:
  - Sensori di gas compatibili con Arduino o Raspberry Pi.
  - Scheda ESP32 con display economico giallo da 2,8 pollici ([ESP32-2432S028R](https://randomnerdtutorials.com/esp32-cheap-yellow-display-cyd-pinout-esp32-2432s028r/#available-pins)).
- **Software**: Librerie per AI e gestione sensori, come TensorFlow, [LVGL](https://lvgl.io/).

---

## Istruzioni per l'installazione
1. Clona questo repository:
   ```bash
   git clone https://github.com/fabiuz73/Gas-AI.git
   ```
   [Vai al repository Gas AI su GitHub](https://github.com/fabiuz73/Gas-AI)
2. Segui la documentazione per configurare il tuo ambiente.

---

## Obiettivo del Progetto

Gas AI mira a fornire un sistema completo che unisce **grafica interattiva** e **funzionalità avanzate**. L'obiettivo principale è implementare:
1. **Grafica**:
   - Creazione di interfacce utente intuitive e moderne utilizzando librerie grafiche come [LVGL](https://lvgl.io/).
   - Personalizzazione dei temi, pulsanti, icone e loghi.
   - Scarica le icone per il progetto da [Flaticon](https://www.flaticon.com/) o [Material Icons](https://fonts.google.com/icons).
   - Test delle icone in un file dedicato [`main_menu_with_icon.ino`](src/main_menu_with_icon.ino) come prossimo obiettivo.
2. **Funzionalità**:
   - Monitoraggio continuo dei dati provenienti dai sensori di gas.
   - Elaborazione e analisi dei dati per generare report e previsioni.
   - Sistema di notifiche per rilevare anomalie o cambiamenti nei consumi.

---

## Sketch Disponibili

1. **Sketch Funzionante**: Il codice principale è disponibile nel file [`main_menu_with_lvgl.ino`](src/main_menu_with_lvgl.ino).
   - Puoi trovarlo all'interno della directory `src` ed eseguirlo su una scheda ESP32.

2. **Sketch da Testare**: Un file specifico con il supporto alle icone è disponibile nel file [`main_menu_with_icon.ino`](src/main_menu_with_icon.ino).
   - Questo sketch è in fase di sviluppo e test, con l'aggiunta di nuove funzionalità grafiche.

---

## Risorse Utili
- [Creare un nuovo repository su GitHub](https://github.com/new)
- [LVGL - Grafica per Embedded](https://lvgl.io/)
- [Guida ufficiale: Clonare un repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository)
- [Flaticon - Icone gratuite](https://www.flaticon.com/)
- [Material Icons - Icone Google](https://fonts.google.com/icons)
- [ESP32-2432S028R - Documentazione e Pinout](https://randomnerdtutorials.com/esp32-cheap-yellow-display-cyd-pinout-esp32-2432s028r/#available-pins)

---

## Contributi
Siamo aperti a contributi! Sentiti libero di aprire una issue o una pull request per migliorare il progetto.

---

## Licenza
Questo progetto è rilasciato sotto la licenza [MIT](LICENSE).