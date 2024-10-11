# Serveur HTTP 1.1 - Projet

## Description

Le but de ce projet est d'implémenter un serveur conforme à une version simplifiée du protocole **HTTP 1.1**, basée sur la spécification décrite dans le **RFC2616**. Mon serveur est capable de répondre aux requêtes HTTP et de servir différents types de fichiers, tout en supportant les méthodes HTTP principales.

## Fonctionnalités

Mon serveur implémente les fonctionnalités suivantes :

### 1. Parsing des Headers HTTP
- Mon serveur est capable de lire et d'analyser les headers des requêtes HTTP, pour extraire les informations nécessaires à la génération des réponses appropriées.

### 2. Méthodes HTTP supportées
- **GET** : Récupère et renvoie le contenu d'un fichier ou d'un dossier demandé par le client.
- **HEAD** : Renvoie uniquement les headers de la réponse, sans le corps.
- **POST** : Reçoit et traite les données envoyées par le client.
- **PUT** : Permet de créer ou mettre à jour une ressource sur le serveur.
- **DELETE** : Supprime une ressource sur le serveur.

### 3. Génération des réponses HTTP
- Mon serveur génère des réponses conformes au protocole HTTP 1.1 en fonction des méthodes reçues et de l'état des ressources demandées.
- Les codes de statut HTTP appropriés sont renvoyés en fonction des opérations (ex. : `200 OK`, `404 Not Found`, `500 Internal Server Error`).

### 4. Gestion des fichiers et dossiers
- Mon serveur peut servir des fichiers situés dans un **dossier racine spécifique**.
- Il est capable de lister le contenu d'un dossier lorsque celui-ci est demandé.
- Les fichiers sont servis avec le `Content-Type` approprié en fonction de leur type.

## Types de fichiers supportés

Mon serveur est capable de servir plusieurs types de fichiers, chacun avec le `Content-Type` correct :

- **Fichiers texte** (`text/plain`)
- **Fichiers HTML** (`text/html`)
- **Fichiers JSON** (`application/json`)
- **Images** (`image/jpeg`, `image/png`)

Tous les fichiers sont interprétés relativement à un **dossier racine** qui doit être spécifié lors de l'exécution du serveur.

## Structure du projet

Le projet contient les fichiers et dossiers suivants :

- **server.js** : Le fichier principal où est implémentée la logique du serveur HTTP.
- **/public** : Le dossier racine où sont stockés les fichiers et dossiers à servir.
- **/routes** : Dossier optionnel pour la gestion des différentes routes HTTP.
- **/logs** : Dossier pour stocker les journaux du serveur, si applicable.

## Installation et Exécution

### Prérequis
- **Node.js** doit être installé sur votre machine. Vous pouvez le télécharger sur [nodejs.org](https://nodejs.org).


RUN SERVER:
```
make
./webserver 127.0.0.1 8010
```


## LE CLIENT NE FONCTIONNE PLUS
RUN CLIENT:
./client <host> <port> <method> <url> <body?>
```
gcc client.c -o client && ./client 127.0.0.1 8010 GET index.html
gcc client.c -o client && ./client 127.0.0.1 8010 POST index.html '{"key": "value"}'
```

Les taches du programme a faire:
- [x] Creation du webserver, avec socket TCP (address and port)
- [x] Creation de websocket (pour les clients)
- [x] Boucler l'ecoute de client (utilisation de thread pour les taches voir aussi `select`)

Partie HTTP RFC2616:
- [x] Parsing du header 
- Mettre les requetes
  - [x] GET
  - [x] HEAD
  - [x] POST
  - [x] PUT
  - [x] DELETE
- La génération des réponses appropriées (A definir en details)

Servir des fichiers statiquement:
  - [x] Des fichiers texte
  - [x] Des fichiers HTML
  - [x] Des fichiers JSON
  - [x] Different types d'images, comme des JPEG ou PNG

Faire en meme temps :
- [x] Initialisation de Criterion
- [ ] Testes unitaires (pour chaque fonction)
- A la fin tester des sections plus grand (a definir)

Performance :
- [ ] La performance CPU
- [ ] La gestion de la mémoire (memory footprint, caches, etc...)
- [ ] La gestion des opérations I/O

Regle a pas oublier:
- Quand on ouvre / on ferme (malloc/free)
