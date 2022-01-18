# NAVAK - Lanterne sonore

## Installation
Je conseille d'utiliser Visual Studio Code avec PlatformIO pour l'intégration et le déploiement sur microcontrôleur. Cette dernière est disponible sous forme d'extension.

Une fenêtre s'affichera automatiquement lorsque vous ouvrirez ce dossier dans VS Code pour la première fois:
![PlatformIO](https://codex.netherwaves.com/media/uploads/Screenshot_24.png)
Vous n'avez qu'à cliquer sur "Install" pour démarrer le processus d'installation. Lorsque ce sera terminé, redémarrez VS Code.

### Remplacement de la librairie Teensy
À cause de certains problèmes de compatibilité avec une librairie tierce et parce que j'y ai moi-même rajouté quelques personnalisations, j'ai dû effectuer quelques modifications à même librairie de Teensy. Le code complet est disponible [ici](https://codex.netherwaves.com/media/files/framework-arduinoteensy.zip).

Après l'avoir extrait de l'archive, vous devez remplacer le dossier qui existe à l'adresse suivante: `~/.platformio/packages/framework-arduinoteensy` (c'est la même pour Windows et Unix).

`~` correspond au répertoire utilisateur (dans mon cas, c'est `/Users/netherwaves/`).

### Déploiement
Lorsque c'est fait, dans VS Code, ouvrez le dossier `Teensy` (SUPER IMPORTANT!). Vous devriez avoir la barre suivante dans le bas:
![Barre de tâches](https://codex.netherwaves.com/media/uploads/Screen-Shot-2022-01-18-at-3.02.33-PM.png)

Le crochet sert à **compiler** le code, et la flèche vers la droite sert à le **déployer** sur le Teensy (préalablement branché à l'ordinateur). Le déploiement compile automatiquement le code, mais la compilation ne déploie pas.

---

## Le code

Puisque ce projet est configuré avec PlatformIO, le code Arduino est organisé en classes C++ au lieu d'utiliser l'extension `.ino`. Le fichier correspondant au sketch principal est `main.cpp`.

Les modules d'action se divisent comme suit:
- `objects.h`: tous les objets requis pour la chaîne DSP du projet sont déclarés ici. Ça inclut les instruments .sf2 et certaines propriétés globales.
- `audio_manager.h`: fonctions relatives au moteur audio du Teensy (initialisation des librairies concernées et lecture de fichiers).
- `osc_manager.h`: gestion des messages OSC en provenance du module ESP32. C'est généralement dans la fonction `dispatcher` qu'on va vouloir déclarer de nouveaux événements; et l'adressage devra naturellement être reflété dans le code de l'ESP32.
- `lantern_events.h`: fonctions internes et événements globaux de la lanterne (surtout l'allumage et l'éteinte)
- `heartbeat_events.h`: fonctions internes et événements reliés au battement cardiaque
- `organique_events.h`: callbacks d'événements relatifs à la section Organique
- `silva_events.h`: callbacks d'événements relatifs à la section Silva
- `narr_events.h`: callbacks d'événements relatifs à la narration