# Radar & Decision system


### Radar 
---
Déplacer la détection dans un composant  à  part :
    
* Mettre dans un tick component la détéction qui aura un fréquence plus basse
* Donner le tableau d'acteur à décision component via le radar


### Decision Component 

---

Remplacer totalement le tick :

* Lors de l'appel du radar activer une fonction qui : 
  * Fais une comparaison avec le précedent tableau envoyé avec la clé de la map 
  * Si un acteur n'est plus dedans il est retirer 
  * Si un acteur était déjà à l'intérieur augmenté l'entier dans la valeur de la map
  * Si l'entier est à un certain niveau confirmé comme target et passé l'information au missile Launcher

<br>
<br>
<br>

---
<br>
<br>
<br>


# Missile Launcher Et Missile 

Déplacer le fi