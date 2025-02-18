# Projet 10 (Groupe 2) - Analyseur de Fichier Texte

## Description

Il s’agit de développer un programme qui nous permet d’analyser un texte communiquant divers statistiques. 

## Fonctionnalités

- **Statistiques(nb de mots, de caractères, de lignes, de paragraphe)** : Lire un fichier texte et compter le nombres de lignes, de mots et de caractères.
- **Frequence des mots dans un dictionnaire** : Créer un dictionnaire de mot et en calculer la fréquence. 
- **Affichage des mots les plus fréquents** : Affiche les mots les plus fréquents dans le fichier.
- **Sauvegarde des résultats dans un fichier txt** : Sauvegarde les résultats dans un fichier txt.


## Fonctionnalités bonus 

- **Support Multilingue** : Prend en charge des textes en Français, Anglais, Russe et Espagnol, avec un menu interactif pour sélectionner la langue.
- **Concaténation de deux fichiers texte** : Détecte et affiche les mots palindromes.

## Fonctions utilisées

- **outcome_stat** : Pour afficher le nombre de caractère, de mots et de ligne.
- **analyser_frequence_txt** : Un fonction qui nous permet de calculer et d'afficher la frequence de chaque et le mettre dans une structure,
d'afficher les mots les plus fréquents à travers un calcul de moyenne et de rechercher la fréquence d'un mot spécifique.
- **sauvegarder_statistiques** : Une fonction qui sauvegarde les resultats de outcome et de la frequence des mots dans un fichier nommé 'Sauvegarder_fichier' situé dans le même repertoire que notre projet


## Remarque

-Notre programme traite seulement les fichiers textes et non les fichiers binaires


## Outils et Utilisation

Téléchargez le projet en **.zip** situé dans le repertoire main(default) et extraire les fichiers.
Ouvrez l'outil Vscode ou l'IDE de votre choix puis compiler l'executable du projet. 

### Compilation

Pour compiler le projet, vous pouvez utiliser le compilateur 'gcc' , sur Windows ou un compilateur 'C' de votre choix:

```bash
gcc -o Analyzer_text Analyzer_text.c
```
Et ajoutez cette ligne de commande pour pouvoir mettre le terminal en encodage UTF-8 (évite les bugs):
```bash
chcp 65001
```

**Cela génère l'exécutable Analyzer_text.exe.**

Executez le avec : 

```bash
./Analyzer_text.exe (sur powershell)
```
```bash
Analyzer_text.exe (sur le cdm)
```
Un menu interactif s'affichera pour vous guider à travers les étapes :
Choisissez une langue parmi les 4 disponibles :

- Français
- Anglais
- Russe
- Espagnol

Entrez le nom du fichier à analyser : **Un chemin absolue ou le fichier étant dans le meme repertoire** Des fichiers dans chaque langues sont fournis.


## Dépendances

- **GCC** :  Le projet utilise le compilateur GCC (GNU Compiler Collection).
- **MinGW** : Utilisé pour la compilation sous Windows.

