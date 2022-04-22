# NAVAK - Lanterne sonore

## Installation
Je conseille d'utiliser Visual Studio Code avec PlatformIO pour l'intégration et le déploiement sur microcontrôleur. Cette dernière est disponible sous forme d'extension.

Une fenêtre s'affichera automatiquement lorsque vous ouvrirez ce dossier dans VS Code pour la première fois:

![PlatformIO](https://codex.netherwaves.com/media/uploads/Screenshot_24.png)

Vous n'avez qu'à cliquer sur "Install" pour démarrer le processus d'installation. Lorsque ce sera terminé, redémarrez VS Code.

### Remplacement de la librairie Teensy
À cause de certains problèmes de compatibilité avec une librairie tierce et parce que j'y ai moi-même rajouté quelques personnalisations, j'ai dû effectuer quelques modifications à même librairie de Teensy. Le code complet est disponible [**ici**](https://codex.netherwaves.com/media/files/framework-arduinoteensy.zip).

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
- `objects.h`: tous les objets requis pour la chaîne DSP du projet sont déclarés ici (voir plus loin pour plus d'infos). Ça inclut les instruments .sf2 et certaines propriétés globales.
- `audio_manager.h`: fonctions relatives au moteur audio du Teensy (initialisation des librairies concernées et lecture de fichiers).
- `osc_manager.h`: gestion des messages OSC en provenance du module ESP32. C'est généralement dans la fonction `dispatcher` qu'on va vouloir déclarer de nouveaux événements; et l'adressage devra naturellement être reflété dans le code de l'ESP32.
- `lantern_events.h`: fonctions internes et événements globaux de la lanterne (surtout l'allumage et l'éteinte)
- `heartbeat_events.h`: fonctions internes et événements reliés au battement cardiaque
- `organique_events.h`: callbacks d'événements relatifs à la section Organique
- `silva_events.h`: callbacks d'événements relatifs à la section Silva
- `narr_events.h`: callbacks d'événements relatifs à la narration

---

## La chaîne DSP

Teensy offre une librairie sonore en DSP ("digital signal processing") permettant de créer des réseaux de signaux sonores complexes, de façon similaire à Max/MSP mais en moins complexe. La personne qui développe l'environnement Teensy offre [**cet outil de design**](https://www.pjrc.com/teensy/gui) afin de faciliter l'interprétation vers du code. Le site sert aussi de référence pour toutes les fonctions que chaque objet peut accomplir.

Afin d'importer le code qui existe déjà au sein de ce projet, copiez tout ce qui se trouve entre les deux commentaires débutant par `GUItool` dans `objects.h` et collez-le dans la boîte texte qui apparaît lorsque vous cliquez sur le bouton "Import". 

Similairement, pour exporter les modifications que vous avez faites dans l'outil GUI, cliquez sur le bouton "Export" et **NE COPIEZ QUE CE QUI SE TROUVE ENTRE LES DEUX COMMENTAIRES DÉBUTANT PAR `GUItool`!!!** C'est très important, puisque le projet utilise une version différente de la librairie `Wire` qui ne doit PAS être surchargée; et, en plus, les importations de librairies se font ailleurs, donc vous ne voudriez pas avoir des doublons!

---

## Gestion des fichiers audio

La librairie Teensy permet la lecture et le traitement en temps réel de fichiers audio à partir d'une carte microSD. La plupart des déclenchements reposent sur ce procédé, et chaque lanterne se doit donc d'être munie d'une carte préalablement remplie avec tous les fichiers audio nécessaires au bon fonctionnement des interactions programmées. À noter que **le programme du Teensy ne fonctionnera jamais si aucune carte n'est insérée!**

### Récupérer les fichiers audio
[25 janvier 2022] La totalité des fichiers audio se trouve [**ici**](https://codex.netherwaves.com/media/files/teensy_sd_04.22.22.zip).

### Nomenclature
La nomenclature repose sur un un système d'assignation d'identifiant afin de jouer certains clips en fonction de la lanterne spécifique qui est appelée. En date de janvier 2022, trois lanternes avec trois identifiants spécifiques étaient programmées, et les identifiants à quatre caractères étaient enregistrés manuellement dans une grille de données statique, assignant chacun d'eux à un index. Ce processus est utilisé à deux endroits:

- dans `lantern_events.h` > `idChart`, L.14: id de lanterne --> index (lecture dynamique de triggers: ex. `ignites/ignite_1`);
- dans `heartbeat_events.h` > `heartToneChart`, L.12: id de lanterne --> accord musical à 4 voix (voir `updateHeartbeat` plus bas).

### Standards de conversion

Les fichiers audio doivent **impérativement** être:
- des fichiers **.raw**;
- à une résolution de **16 bits**;
- et une fréquence d'échantillonnage de **44.1kHz**.

Audacity reste le logiciel le plus accessible afin de faire la conversion vers du RAW. Audition ne le fait malheureusement pas...

