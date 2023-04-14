# Créer un executable à partir de fichiers sources
add_executable(VectorTests  test_vector.cpp)
add_executable(TestLab2  test_lab2.cpp)
add_executable(TestLennardJones test_lennard_jones.cpp)
add_executable(TestUnivers test_universe.cpp)

# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.

