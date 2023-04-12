# Créer un executable à partir de fichiers sources
add_executable(VecteurTests  VecteurTest.cpp)
add_executable(TestLab  test_lab2.cpp)

# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.
target_link_libraries(VecteurTests Vecteur)

target_link_libraries(TestLab Vecteur)
target_link_libraries(TestLab Particle)
