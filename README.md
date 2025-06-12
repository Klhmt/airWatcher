# AirWatcher
# Auteurs : Binômes B3233 & B3225

Projet de Génie Logiciel - S2

## Installation
``` bash
git clone https://github.com/Klhmt/airWatcher.git
cd airWatcher
```

## Compilation
``` bash
make
```

## Lancement de l'application
```bash
./AirWatcher
```

## Exécuter les tests unitaires

Nous avons utilisé le framework de test Doctest (https://github.com/doctest/doctest?tab=readme-ov-file), dont le header est déjà inclus dans le code source du projet. Pour compiler l'exécutable de test :
```bash
make test
```

Pour lancer les tests :
```bash
./test
```

## Utiliser des données différentes

Pour utiliser vos propres données, il suffit de modifier le fichier "dataset/_fileGroupOrigine.csv", en mettant les chemins des fichiers contenant les :

- providers
- cleaners
- users
- sensors
- measurements

dans cet ordre, un par ligne.

## Manuel utilisateur

L'utilisateur est ensuite amené à choisir son type de profil ou bien quitter l'application
1. Agence Gouvernementale
2. Fournisseur
3. Particulier
4. Quitter l'application

Une fois le profil de l'utilisateur selectionnée, deux fonctionnalité principales sont proposées
1.  Déterminer la fiabilité d'un capteur
Vous devrez fournir les informations suivantes :
-> Numéro du capteur

2. Calculer la qualité de l'air
Vous devrez fournir les informations suivantes :
-> Latitude
-> Longitude
-> Rayon (doit-être strictement supérieur à 0)
-> Date de début (format : dd/mm/yyyy)
-> Heure de début (format : hh/mm)
-> Date de fin (format : dd/mm/yyyy)
-> Heure de fin (format : hh/mm)
La date de fin doit être postérieure à la date de début

Il peut également quitter l'application 
3. Quitter l'application



