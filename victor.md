## Deuxieme heuristique

### Ideation

Nous avons constaté que notre première heuristique prenait trop de temps par rapport au 5s imposées par le sujet. Malgrè l'iterative deepening, chaque tours prenait plus d'une minute de calcule. Nous avons decidé de le modifer en s'inspirant d'heuristique trouvés sur internet:

- <http://premierlien.com>
- <http://deuxiemelien.com>
- <http://troisiemelien.com>

Nous nous sommes donc tournés vers une methode à la fois efficace en terme de temps mais surtout en terme de score.
<br></br>

### Representation Patterne

La methode choisi ne recherche pas des patternes sur seulement une dimension mais aussi sur deux. 

----

<div align="center">

***10 000 points*** 

</div>

----

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   | .   | .   |
| B   | .   | X   | X   | X   | X   | X   | .   |
| C   | .   | .   | .   | .   | .   | .   | .   |

***Représentation {1, 5,  0,  0}, {0, 0,  0,  0}***

----

<div align="center">

***700 points*** 

</div>

----

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   | .   | .   |
| B   | .   | X   | X   | X   | X   | .   | .   |
| C   | .   | .   | .   | .   | .   | .   | .   |

***Représentation {1, 4,  0,  0}, {0, 0,  0,  0}***

----

<div align="center">

***700 points*** 

</div>

----

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | .   | O   | .   | .   | .   | .   | .   |
| B   | O   | X   | X   | X   | X   | .   | .   |
| C   | .   | X   | .   | .   | .   | .   | .   |
| D   | .   | X   | .   | .   | .   | .   | .   |
| E   | .   | X   | .   | .   | .   | .   | .   |
| F   | .   | .   | .   | .   | .   | .   | .   |

***Représentation {2, 4,  1,  0}, {0, 0,  0,  0}***

----

<div align="center">

***700 points*** 

</div>

----

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | .   | ?   | .   | .   | .   | .   | .   |
| B   | ?   | X   | X   | .   | X   | X   | ?   |
| C   | .   | X   | .   | .   | .   | .   | .   |
| D   | .   | .   | .   | .   | .   | .   | .   |
| E   | .   | X   | .   | .   | .   | .   | .   |
| F   | .   | X   | .   | .   | .   | .   | .   |
| G   | .   | ?   | .   | .   | .   | .   | .   |

***Représentation   {2, 4, -1,  1}, {0, 0,  0,  0}***

----

<div align="center">

***700 points*** 

</div>

----

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | .   | ?   | .   | .   | .   | .   | .   |
| B   | O   | X   | X   | X   | X   | .   | .   |
| C   | .   | X   | .   | .   | .   | .   | .   |
| D   | .   | .   | .   | .   | .   | .   | .   |
| E   | .   | X   | .   | .   | .   | .   | .   |
| F   | .   | X   | .   | .   | .   | .   | .   |
| G   | .   | ?   | .   | .   | .   | .   | .   |

***Représentation   {1, 4,  1,  0}, {1, 4, -1,  1}***

----

<div align="center">

***500 points*** 

</div>

----

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   | .   | .   |
| B   | O   | X   | X   | X   | X   | .   | .   |
| C   | .   | X   | .   | .   | .   | .   | .   |
| D   | .   | X   | .   | .   | .   | .   | .   |
| E   | .   | .   | .   | .   | .   | .   | .   |

ou 

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   | .   | .   |
| B   | O   | X   | X   | X   | X   | .   | .   |
| C   | .   | .   | .   | .   | .   | .   | .   |
| D   | .   | X   | .   | .   | .   | .   | .   |
| E   | .   | X   | .   | .   | .   | .   | .   |
| F   | .   | .   | .   | .   | .   | .   | .   |

***Représentation  {1, 4,  1,  0}, {1, 3,  0, -1}***

----

<div align="center">

***500 points*** 

</div>

----

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   | .   | .   |
| B   | ?   | X   | X   | .   | X   | X   | ?   |
| C   | .   | X   | .   | .   | .   | .   | .   |
| D   | .   | X   | .   | .   | .   | .   | .   |
| E   | .   | .   | .   | .   | .   | .   | .   |

ou 

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   | .   | .   |
| B   | ?   | X   | X   | .   | X   | X   | ?   |
| C   | .   | .   | .   | .   | .   | .   | .   |
| D   | .   | X   | .   | .   | .   | .   | .   |
| E   | .   | X   | .   | .   | .   | .   | .   |
| F   | .   | .   | .   | .   | .   | .   | .   |

***Représentation {1, 4, -1,  1}, {1, 3,  0, -1}***

----

<div align="center">

***300 points*** 

</div>

----

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   | .   | .   |
| B   | .   | X   | X   | X   | .   | .   | .   |
| C   | .   | X   | .   | .   | .   | .   | .   |
| D   | .   | X   | .   | .   | .   | .   | .   |
| E   | .   | .   | .   | .   | .   | .   | .   |

ou 

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   | .   | .   |
| B   | .   | X   | X   | .   | X   | .   | .   |
| C   | .   | X   | .   | .   | .   | .   | .   |
| D   | .   | X   | .   | .   | .   | .   | .   |
| E   | .   | .   | .   | .   | .   | .   | .   |

***Représentation {2, 3,  0, -1}, {0, 0,  0,  0}***

----

<div align="center">

***50 points*** 

</div>

----

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   | .   | .   |
| B   | .   | X   | X   | .   | .   | .   | .   |
| C   | .   | X   | X   | .   | .   | .   | .   |
| D   | .   | .   | .   | .   | .   | .   | .   |
| E   | .   | .   | .   | .   | .   | .   | .   |

ou 

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   | .   | .   |
| B   | .   | X   | X   | .   | .   | .   | .   |
| C   | .   | .   | X   | .   | .   | .   | .   |
| D   | .   | X   | .   | .   | .   | .   | .   |
| E   | .   | .   | .   | .   | .   | .   | .   |

***Représentation  {3, 2,  0, -1}, {0, 0,  0,  0}***

----

<div align="center">

***20 points*** 

</div>

----

| 1   | 2   | 3   | 4   | 5   | 6   | 7   |
| --- | --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   | .   |
| B   | .   | X   | X   | x   | .   | .   |
| C   | .   | .   | .   | .   | .   | .   |

ou 

| 1   | 2   | 3   | 4   | 5   | 6   | 7   |
| --- | --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   | .   |
| B   | .   | X   | X   | .   | X   | .   |
| C   | .   | .   | .   | .   | .   | .   |

***Représentation  {1, 3,  0, -1}, {0, 0,  0,  0}***

----

<div align="center">

***9 points*** 

</div>

----

| 1   | 2   | 3   | 4   | 5   | 6   |
| --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   |
| B   | .   | X   | X   | .   | .   |
| C   | .   | .   | .   | .   | .   |

ou 

| 1   | 2   | 3   | 4   | 5   | 6   |
| --- | --- | --- | --- | --- | --- |
| A   | .   | .   | .   | .   | .   |
| B   | .   | X   | .   | X   | .   |
| C   | .   | .   | .   | .   | .   |

***Représentation {1, 2,  0, -1}, {0, 0,  0,  0}***

----

La reprensation est sous la forme {1,2,3,4} avec pour signification:

1. Le nombre minimum d'occurence du patterne. Par exemple si i cette argument est egale à deux alors le patterne doit se retrouver:
   
   - dans la ligne et dans la diagonale
   - dans la ligne et dans la colonne
   - dans les deux diagonales
   - ...

2. Le nombre d'occurence de notre signe. La piece du joueur doit apparaitre x fois dans le compte.

3. Le nombre de blocage sur les extremitées. Si c'est egale à deux alors le joueur est bloqué des deux cotés soit par le joueur adverse soit par la board
   <i>(-1 signifit que l'algorithme ne prends pas en compte cette argument)</i>.

4. Le nombre de saut. Cela permet de savoir si le patterne tolere un espace dans l'algnement des pieces du joueur <i>(-1 signifit que l'algorithme ne prends pas en compte cette argument)</i>.
   <br></br>

### Recherche

Pour trouver les patternes, l'algorithme va parcourir toute la board de cette facon:

1. Instentier un tableau de taille 4, une pour chaque directions:
   
   - diagonale droite
   
   - diagonale gauche
   
   - ligne 
   
   - colonne
     
     Ce tableau contient la structure suivante: 
   
   - nombre d'occurences du signe
   
   - nombre de blocages
   
   - nombre de sauts
     <br></br>

2. On parcoure chaque points deux fois:
   
   - une fois en autorisant un espace dans la recherche
   
   - une fois sans autoriser d'espaces dans la recherche
     
     Pour chaque parcours l'algorithme regarde dans toutes les direction, dans les deux sens à partir du point. Cela rempli ainsi la partie du tableau dediée à la direction prise.
     <br></br>

### Comparaison

Pour la comparaison va comparer le tableau de la recherche aux tableau du patterne. En effet la representation des patternes est constitué avec deux tableau:

- {A,B,C,D}, {D,E,F,G}

Cela autorise un patternes a deux dimension, avec le premier stocké dans {A,B,C,D}
et le deuxieme dans {D,E,F,G}. Lorsque le patterne se repete identiquement D,E,F,G sont nuls et A=2. en effet A represente le nombre d'occurence minimum. 

Si le patterne est a seulement une dimension: D,E,F,G sont nuls et A=1. Cependant certains patternes doivent se repeter trois fois d'ou A=3.

### Exemple

Voici le board à evaluer

| 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| A   | X   | O   | .   | .   | .   | .   | .   |
| B   | O   | X   | X   | X   | X   | .   | .   |
| C   | .   | X   | 0   | O   | .   | .   | .   |
| D   | .   | .   | O   | 0   | .   | .   | .   |
| E   | .   | X   | 0   | O   | .   | .   | .   |
| F   | .   | X   | .   | .   | .   | .   | .   |
| G   | .   | .   | .   | .   | .   | .   | .   |

lorsque l'algorithme va arriver sur le point (B,3) il retournera le tableau suivant

<div align="center">[{4,1,0}, {4,1,1}, {1,0,0}, {2,2,0}]</div>

Car il y a repectivement:

- Dans la ligne: 4 pionts, 0 espaces et 1 blocage
- dans la colonne: 4 pionts, 1 espace et 1 blocage
- dans la diagonale droite: 1 piont, 0 espace et 0 blocage
- dans la diagonale gauche: 2 pionts, 0 espace et 2 blocages

Mainteneant essayons de comparer ce tableau avec ces patternes: 

***{1, 4, 1, 0}, {1, 4, -1, 1}***

On retouve 1 fois dans les 4 direction le premier patterne et 1 fois dans les 4 directions le deuxieme: le score augmente des points assignés

***{2, 4,  1,  0}, {0, 0,  0,  0}***

On retrouve 1 fois le premier patterne. Cependant on remarque que le nombre d'occurence minimum est de 2. Les points de sont pas assignés
