# Exercice 1
1. Type abstrait au sens où est donnée une spécification mathématique, qui laisse libre l'implémentation.
2. Implémentation des structures de données.
3. Cohérence et contraintes déjà établies, plus haut niveau de conception, détachée de l'implémentation.

# Exercice 2
1. Voir "set.h".
2. Cela évite les copies de la structure à chaque fois que l'on appelle la fonction, alors qu'aucune modification n'est effectuée dessus.
3. Techniquement, on doit pouvoir exécuter set__is_empty(set__empty()), or set__empty() dans cette partie renvoie un "set" (pas d'allocation dynamique).

# Exercice 3
1. Passage par référence (adresse).
2. Savoir si l'opération d'ahout a été effectivement effectuée ou non.
3. int set__add(struct set * set, char c);

# Exercice 4
1. La variable ne sera plus référencée dès la fin de l'exécution de la fonction, et donc le pointeur est invalidé.
2. Pour que la structure ait une taille fixée.
3. 
-> struct set set__empty(); // Avantage : correspond à l'intuition : on crée un "set" à partir de rien.
-> struct * set set__empty(struct set * set); // Inconvénient : il faut instancier la structure avant d'appeler cette fonction pour s'en servir...

# Exercice 5
Voir "set.h.

# Exercice 6
Permet de travailler sur un structure "set" et la différencier d'un char.

# Exercice 8
bits[i] | 1 << 32-(c - 32*(c/32) - 1)

