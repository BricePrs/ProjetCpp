# Créer une bibliothèque à partir d'un ensemble de fichiers de définitions (.cxx) sans main.
# Ces fichiers ne contiennent pas de fonction main
# Remplacer ... par les fichiers nécessaires
add_library(Particle STATIC Particle.cpp Univers.cpp)
target_link_libraries(Particle)