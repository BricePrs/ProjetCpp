# Dépot du projet de C++ de Brice PERES et Hélène HASSAN - RENDU FINAL
---
(Rapport de projet dans le dossier doc/)

# Simulateur de particules en C++


## Utilisation du simulateur

### Choix des contraintes du système

La structure publique **SimulationConstraints** permet de définir un environnement physique (de dimension *n* = 1, 2 ou 3) dans laquelle le système définit pourra évoluer. L'univers de particules est consistué de cellules (en dimension *n* également donc) auxquelles on peut attribuer une taille à l'initialisation.
*Exemple d'utilisation :*

```cpp
# Création d'un cube de 400 unités de côté dans lequel l'univers de particules évoluera
# Les cellules qui composent l'univers sont des cubes de côté 2.5
SimulationConstraints constraintes = SimulationConstraints(Vector<3>(-200.), Vector<3>(200.));
Universe<3> monUnivers(contraintes, 2.5);
```


### Choix des paramètres physiques du système

La structure publique **SimulationSettings** permet de définir plusieurs paramètres selon l'effet voulu lors de la simulation. La définition de la structure est présente dans la documentation du projet.
*Exemple d'utilisation : *

```cpp
# Création d'une simulation prenant en compte les forces d'intéraction de Lennard-Joes avec les parametres eps = 5. et sigma = 1., avec un pas de simulation de 0.00005 secondes et un temps total de simulation de 19.5 secondes. La simulation est sauvegardée toutes les 2000 itérations.
    
    PhysicsConstants constants = {
            .eps =  5.,
            .sigma =  1.
    };

    auto settings = SimulationSettings {
        .lennard_jones_interaction = true,
        .physics_time_step = .00005,
        .physics_time_total = .5,
        .iter_count_until_save = 2000,
        .boundary_behaviour = Absorption,
        .constants = constants
    };

# Simulation
univers.simulate(settings);
```

### Initialisation des particules

Il est possible d'initialiser les particules du système de deux manières qui requièrent toutes les deux la vitesse, masse, et catégorie (Neutron, Proton, Electron) pour chacune d'entre elles.

La position de chaque particule peut être donnée explicitement à l'initialisation, dans ce cas-là il faudra appeler la méthode  ***add*** de la classe **Universe** qui permettra d'ajouter une seule particule à l'univers. 

Il est également possible de générer un univers de particules de même nature (même masse, vitesse, catégorie) régulièrement espacées les unes des autres dans un espace de dimension *n* = 1, 2 ou 3 on peut avec la méthode ***add_packed_particles*** de la classe **Universe** qui renvoie le nombre de particules utilisé pour remplir l'espace en fin de fonction. La description de ces deux méthodes de la classe est présente dans la documentation.

À l'inverse, il est également possible de générer un univers de particules dans un espace de dimension n (cube en dimension 3, carré en dimension 2 et ligne en dimension 1) avec des paramètres aléatoires pour chacun d'entre elles.
Pour cela, il faudra utiliser la méthode **_random_fill_**.

Lorsque l'Univers est réglé en dimension 2, il est possible de remplir ce dernier à l'aide de la méthode **_fill_disk_** qui va remplir un disque (2D).

La description des méthodes précédentes est disponible dans la documentation.

*Exemple d'utilisation :*

```cpp

// Contraintes de simulation  
SimulationConstraints constraints = SimulationConstraints(Vector<2>(-50.), Vector<2>(50.));  
Universe<2> univers(constraints, 100);

---
  
// Création d'un univers avec 4 particules dont la position est au préalable définie 
univers.add(Vector<2>(0., 0.), Vector<2>(0., 0.), 1., Category::NEUTRON);  
univers.add(Vector<2>(0., 1.), Vector<2>(-1., 0.), 3.0e-6, Category::NEUTRON);  
univers.add(Vector<2>(0., 5.36), Vector<2>(-0.425, 0.), 9.55e-4, Category::NEUTRON);  
univers.add(Vector<2>(34.75, 0.), Vector<2>(0., 0.0296), 1.0e-14, Category::NEUTRON);

---
// Création d'un univers composé d'un rectangle et d'un cube contenant des particules régulièrements espacées de la quantité "spacing". 
double spacing = pow(2., 1./6.)*.1;
int a = univers.add_packed_particles(Vector<3>(-20., 20., -20.)*spacing+Vector<3>(0., 5., 0.), Vector<3>(20., 60., 20.)*spacing+Vector<3>(0., 5., 0.), Vector<3>(0., -10., 0.), 1., NEUTRON, Vector<3>(4, 4, 4));  
int b = univers.add_packed_particles(Vector<3>(-80., -20., -80.)*spacing, Vector<3>(80., 20., 80.)*spacing, Vector<3>(0.), 1., NEUTRON, Vector<3>(16, 4, 16));

---
// Création d'un univers composé d'un carré contenant 'k' particules initialisée aléatoirement (position, vitesse, masse et catégorie)
univers.random_fill(k);

---
// Création d'un univers composé d'un disque contenant 'k' particules régulièrement espacées dans un cercle de centre (1.0, 0.0, 1.0) avec une masse de 1.0, une vitesse de Vector<3>(0., -10., 0.) et de type NEUTRON
double spacing = pow(2., 1./6.)*.1;
univers.fill_disk(Vector<3>(1.0, 0.0, 1.0), spacing, Vector<3>(0., -10., 0.), 1., NEUTRON, k)

```


