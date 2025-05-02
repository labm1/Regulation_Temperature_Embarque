# Projet de régulation de température embarqué

Projet créé dans le cadre du cours INF1633 Programmation de systèmes embarqués en C/C++ à l'Université du Québec en Outaouais (UQO) durant la session d'automne 2024.

Le but de ce projet est de créer un système embarqué qui active un ventilateur et des DELs selon la température. Un écran LCD doit également afficher la température ambiante. L’état de la DEL verte dépend de si le ventilateur est activé ou non, l’état de la DEL bleue dépend de l’état du système (normal ou actif), et l’état de la DEL rouge dépend si la température est sous le seuil supérieur ou non. Voici les spécifications du projet:

1.  Lorsque la température ne dépasse pas le seuil supérieur, la DEL de la carte est allumée en bleu.
2.	La température actuelle doit être affichée sur l’écran LCD
3.	Si la température dépasse le seuil supérieur, la DEL rouge s’allume. La DEL bleue est éteinte.
4.	Si la température dépasse le seuil supérieur, le ventilateur et la DEL verte s’activent. 
5.	Si la température tombe sous le seuil supérieur la DEL rouge s’éteint.
6.	Après que la température ai baissée sous le seuil inférieur, les DEL et le ventilateur sont désactivés, et la DEL bleue est allumée.
7.  L’écran LCD doit être mis à jour toutes les secondes.
8.  Lorsque la température a dépassé le seuil supérieur, le système est en état actif. Si la température est sous le seuil inférieur et est en état actif, il passe à l’état normal.    

La carte utilisée est FRDM-KL28Z avec le logiciel MCUXpresso.

## Matériel
- **Carte FRDM-KL28Z**  
  Microcontrôleur pour contrôler les composantes et exécuter notre programme pour le projet.
- **3 DELs : rouge, bleue, verte**  
  Pour montrer l’état du système. On a décidé de ne pas prendre la DEL intégrée à la carte pour pouvoir distinguer chaque couleur lorsqu’il y a plusieurs DELs d’activées.
- **Breadboard**  
  Pour connecter facilement les composantes entre elles.
- **Fils**  
  Pour connecter les composantes aux ports de la carte.
- **Résistances : 3x 220 Ohms, 1x 270 Ohms**  
  Pour ne pas avoir du courant qui passe directement à travers les DELs sans résistance, ce qui pourrait abimer la carte, et pour le circuit du ventilateur.
- **Diode 1N4001**  
  Pour le circuit du ventilateur.
- **Transistor PN2222**  
  Pour le circuit du ventilateur.
- **Écran LCD 94V-0 avec adapteur I2C**  
  Pour afficher la température. L’adapteur I2C a été ajouté pour réduire le nombre de ports utilisé sur la carte de 7 à 4.
- **Moteur DC 5V**  
  Pour le ventilateur à activer.
- **Capteur de température BMP280**  
  Pour mesurer la température.
- **Source externe de courant 5V**  
  Pour alimenter le moteur. Selon le moteur utilisé la carte FRDM-KL28Z peut avoir des problèmes pour l'alimenter, c'est donc mieux d'utiliser une source externe.

## Diagramme bloc
![image](https://github.com/user-attachments/assets/f23a5d55-63b2-4134-a762-6d0f8a8e9bdf)

## Montage
![image](https://github.com/user-attachments/assets/1f3984aa-ea4c-4377-a7a5-8366e38b9612)

## Diagramme d'états
![image](https://github.com/user-attachments/assets/df89f701-6158-4d9f-a6f3-04e2d43304de)

## Organigramme
![image](https://github.com/user-attachments/assets/e363cf7e-e081-453b-8908-a1dd508baca6)
