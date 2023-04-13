# Créer un executable à partir de fichiers sources
add_executable(VectorTests  test_vector.cpp)
add_executable(TestLab  test_lab2.cpp)
add_executable(TestUnivers  TestUnivers.cpp)

# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.
target_link_libraries(VectorTests Vector)

target_link_libraries(TestLab Vector)
target_link_libraries(TestLab Particle)

target_link_libraries(TestUnivers Particle)
