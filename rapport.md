# Rapport algorithme minimax pour Gomoku



## Langage

On a décidé d'implémenter l'algorithme en **C++** car on a appris ce langage au premier semestre et aussi car c'est 400 fois plus rapide que Python.

[Source](https://stackoverflow.com/questions/801657/is-python-faster-and-lighter-than-c)

## Plateau

### Bitboard

L'utilisation d'un plateau de bit (0 ou 1) était peut-être intéressant pour l'implémentation de notre jeu, on a décidé d'essayer pour voir comment on allait s'en sortir avec cette façon de concevoir.

En ayant un plateau $(B_i)_{1 \le i \le 225}$ où $i$ est le bit à la $i$ème case. Chaque joueur aurait son propre bitboard $P_{1i}$ et $P_{2i}$. Ainsi l'opération "ou" des deux plateaux ($\ P_{1i}\  |\  P_{2i}\ $) ferait notre plateau final.



Résumé en code :

```cpp
//game.hpp
#include <bitset>
// 225 car notre plateau fait 15*15
bitset<225> board1; // board du premier joueu
bitset<225> board2; // board du second joueur

//board.hpp
bitset<225> board = board1 | board2;
```

Mais cela allait nous compliquer la tâche au fur et à mesure donc on a décidé de faire simple et d'utiliser une matrice (tableau de tableau)



### Matrice de caractère (char)

On est parti sur une matrice de caractère pour que ça soit plus simple à traiter car l'optimisation du plateau n'était pas important, on peut changer facilement notre plateau, il fallait se focaliser sur l'heuristique.

```cpp
// game.hpp
char **board;

// game.hpp
board = new char[15][15];
```

<img title="" src="https://www.techiedelight.com/wp-content/uploads/Dynamically-Allocate-Memory-for-2D-Array.png" alt="Dynamic memory allocation in C++ for 2D array" data-align="center">

### Tableau de caractère (version finale)

En ayant fait des recherches sur ce qu'il se faisait dans les compétitions de Gomoku, tout le monde utilisait juste un tableau. C'était logique car l'allocation de la mémoire pour une matrice est plus lourde que juste un simple pointeur de caractère.



La transition d'une matrice vers un tableau n'est pas un gros problème, du coup on a finalement un plateau de caractère pour le traitement des données.

```cpp
// board.hpp
char *board;

// board.hpp
board = new char[225];
```

<img src="file:///C:/Users/Tom/AppData/Roaming/marktext/images/2022-05-15-12-17-23-image.png" title="" alt="" data-align="center">



## Heuristique

### "Pattern" avec Regex

Lorsqu'on transforme la board en une suite de caractère on arrive à retrouver des motifs en particulier, c'est avec ces motifs qu'on peut évaluer un état du plateau.



**Remarque :**

- Motif en ligne : pour regarder les motifs en ligne, on regarde pour chaque ligne (ou tous les 15 caractères) on retrouve le motif (1 ou +).
- En colonne : chaque caractère du motif est espacé de 14 caractères quelconque
- Diagonale \\ : chaque caractère du motif est espacé de 15 caractères quelconque
- Diagonale / : chaque caractère du motif est espacé de 13 caractère quelconque



Exemple avec le motif `.OXO.`: 

```bash
   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 
0  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
1  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
2  -  -  -  -  -  -  -  -  -  -  -  -  -  -  O
3  -  -  -  -  -  -  -  -  O  -  -  -  -  -  X
4  -  -  -  -  -  -  -  -  X  -  -  -  -  -  O  
5  -  -  -  -  -  -  -  -  O  -  -  -  -  -  -
6  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  
7  -  -  -  -  -  -  -  -  O  -  -  -  -  -  -
8  -  -  -  -  -  -  -  -  X  -  -  -  -  -  -  
9  -  -  -  -  -  -  -  -  O  -  -  -  -  -  -
10 -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  
11 -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
12 -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  
13 -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
14 -  -  -  -  -  -  -  -  -  -  -  -  -  X  -

# getBoard(board);
# output :
--------------------------------------------O--------O-----X--------X-----O--------O-----------------------------O--------------X--------------O-------------------------------------------------------------------------------X-
 
# countMatch("-X-");
# output :
7
```

On retrouve le motif 7 fois :

<img src="file:///C:/Users/Tom/AppData/Roaming/marktext/images/2022-05-15-13-57-11-image.png" title="" alt="" data-align="center">

En **bleu** les motifs corrects, en **rouge** le faux positif.

Avec son regex associé (pour la colonne) on arrive facilement à retrouver ces motifs`(?=(-.{14}X.{14}-)+)`

**Contrainte :**

- Prendre en compte les faux motifs

**Solution :**

- Utiliser l'itérateur de `regex` sans s'arrêter à la première occurence.



Le problème en testant notre I.A., c'est qu'il prenait beaucoup trop de temps pour évaluer le plateau, on le comprend avec l'utilisation de regex, il fallait convertir et comprendre le regex passé et l'appliquer tout en extrayant la sous chaîne pendant l'itération.



### Adjacent

Une autre heuristique pour éviter de parcourir tout le plateau était de "voir" ce qu'il se passait dans les pions autours de celui qui venait d'être joué. On allait voir ce qu'il se passait tout autour à une distance de 1.



Exemple de plateau :

```
   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 
0  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
1  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
2  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
3  -  -  -  -  -  -  -  -  O  -  -  -  -  -  -
4  -  -  -  -  -  -  -  X  X  O  -  -  -  -  -  
5  -  -  -  -  -  -  O  O  O  X  -  -  -  -  -
6  -  -  -  -  -  -  -  X  O  -  -  -  -  -  -  
7  -  -  -  -  -  -  -  X  O  X  -  -  -  -  -
8  -  -  -  -  -  -  -  X  X  -  -  -  -  -  -  
9  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
10 -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  
11 -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
12 -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  
13 -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
14 -  -  -  -  -  -  -  -  -  -  -  -  -  -  -

```

 La fonction `adjacent(8,7)` va regarder autour d'elle et appliquer l'algorithme minimax de 1 profondeur pour retourner le coup à jouer.<img src="file:///C:/Users/Tom/AppData/Roaming/marktext/images/2022-05-15-14-04-10-image.png" title="" alt="" data-align="center">


