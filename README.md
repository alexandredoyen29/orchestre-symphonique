# L’Orchestre symphonique par Alexandre et Floran

## Description

​	Ce logiciel client-serveur permet de simuler un orchestre symphonique. Ainsi, il est possible de placer plusieurs sources audios (des instruments) sur la scène. L’auditeur, qui se situe au centre de celle-ci, va pouvoir composer un morceau mélodieux et harmonique en fonction de ses besoins.

​	Ainsi, dans un contexte client-serveur, il va pouvoir déployer l’orchestre sur un système embarqué relié à un système hi-fi (dans le cadre de nos tests, un ordinateur équipé d’enceintes). Il va pouvoir utiliser les instruments situés sur la scène sur son ordinateur grâce au logiciel client. Pour ce faire, il pourra lancer et arrêter les instruments, mais aussi changer leur volume, leur position et leur direction, afin de devenir le nouveau Beethoven en herbe.

​	Tel un Beethoven, l’auditeur va pouvoir créer ses propres partitions afin de les faire jouer par l’orchestre de manière totalement automatisée, et ce, grâce à un langage intuitif centré utilisateur !

## Compilation

​	Le logiciel est fourni avec son Makefile associé, afin de faciliter le déploiement et la compilation sur le système hôte. Ainsi, plusieurs recettes sont disponibles, mais voici les principales :

```
– build-orchestre           -> Construit le logiciel serveur (Orchestre)
– build-instrument          -> Construit le logiciel client (Instrument)
– build-instrument-script   -> Construit le logiciel client fonctionnant grâce à un script créé par l’utilisateur (Instrument-Script)
– build-all                 -> Construit les trois logiciels
– clean                     -> Nettoie les dossiers de compilation
```

​	Sont fournis avec le logiciel des échantillons de sons WAV mono, afin de montrer le plein potentiel de celui-ci. Également, dans un souci de qualité, à chaque recette `build-{objet}`, il existe une recette `build-debug-{objet}`, qui permet d’inclure dans le logiciel compilé les symboles permettant le débogage via GDB (Gnu DeBugger).

## Exécution

### Orchestre

​	L’orchestre se lance grâce à la commande `./orchestre <Liste des instruments>`. Ainsi, on passe en paramètre la liste des fichiers audio correspondant aux différents instruments.

### Instrument

​	L’instrument se lance grâce à la commande `./instrument <Adresse de l’orchestre>`. En effet, dans un contexte client-serveur, il est primordial de spécifier l’adresse du serveur (ici l’orchestre) sur lequel se connecter. Une fois l’instrument lancé, il faut que l’utilisateur choisisse quel instrument il contrôle. Cette liste est générée dynamiquement suivant les instruments passés en paramètre de l’orchestre. Une fois l’instrument choisi, il peut le contrôler via un menu intuitif qui affiche clairement les différentes possibilités d’action possible sur ledit instrument.

### Instrument-Script

#### Utilisation du logiciel

​	L’instrument autonome se lance grâce à la commande `./instrument <Adresse de l’orchestre> <Partition>`. Ainsi, l’instrument va se connecter à l’orchestre, et dérouler la partition afin de restituer à l’auditeur le fruit de son travail acharné.

#### Langage de script pour les partitions

​	Le fichier `./doc/alphabet-script` décrit le langage de script permettant de générer des partitions.

​	Tout d’abord, la première ligne d’un script doit commencer par l’instruction `INSTRUMENT <N° de l’instrument>`, afin de sélectionner le numéro de l’instrument de l’orchestre à utiliser. Les instruments sont numérotés de 0 à (n - 1), où n correspond au nombre d’instruments. Ils sont numérotés en partant du premier argument du programme orchestre, et ainsi de suite (un appel à `./orchestre flute.wav guitare.wav` placera l’instrument `flute.wav` au numéro 0, et `guitare.wav` au numéro 1.).

​	Ensuite, les autres instructions sont décrites dans le fichier, dont voici une copie :
```
INSTRUMENT <Numéro de l’instrument> -> En en-tête, spécifie le numéro de l’instrument
LECTURE                             -> Lance la lecture de l’instrument
PAUSE                               -> Met en pause l’instrument
STOP                                -> Arrête l’instrument
VOLUME <v en %>                     -> Change le volume de l’instrument
POSITION <x> <y> <z>                -> Change la position de l’instrument
DIRECTION <x> <y> <z>               -> Change la direction de l’instrument
QUITTER                             -> Fait quitter l’instrument de l’orchestre
ATTENTE <n en seconde>              -> Met une attente entre deux actions
```

​	Par extension, il est possible de lancer plusieurs instruments en parallèle grâce à un script bash !
