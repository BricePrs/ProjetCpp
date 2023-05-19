# Créer un executable à partir de fichiers sources
add_executable(TestDataStructures test_data_structures.cpp)
add_executable(TestEulerEDO test_euler_edo.cpp)
add_executable(TestLennardJones test_lennard_jones.cpp)
add_executable(TestUnivers test_universe.cpp)
add_executable(TestSystemeSolaire test_solar_system.cpp)
add_executable(TestCollision test_collision.cpp)
add_executable(TwoAtomCollision two_atom_collision.cpp)
add_executable(TestReflexive reflexive_borders.cpp)
add_executable(TestCollision3D test_collision_3D.cpp)


# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.


# G TESTS ####
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})
include(GoogleTest)

# UNIT TESTS ####
add_executable(TestVectors  test_vector.cpp)
target_link_libraries(TestVectors -lgtest)
gtest_discover_tests(TestVectors)