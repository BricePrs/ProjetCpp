//
// Created by helen on 23/04/23.
//
/**
* This test answers the Lab 1 by correcting the provided code and running
 * both Euler explicit and implicit methods on a given EDO.
*/

/// Code élémentaire pour le calcul de la trace d'une matrice.
/// Printemps 2022
/// Objectif : manipuler les éléments de base du C++
///            utiliser des outils de profiling et de débogage
/// ref: l'exercice est inspiré très largement de ressources WWW

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <functional>
#include <random>

using namespace std;

double** initialization(int);
double* fill_vectors(double*, int);
void print_matrix(double** , int);
double trace (double** , int);

/*----------- PART 1 : Code Correction -------------------*/
/// Driver principal pour le calcul de la tace d'une matrice
void compute_trace()
{
    int i, n;
    double **matrix;
    double sum;

    cout << endl << "Enter the Dimension for a square matrix: " << flush;
    cin >> n;
    matrix = initialization(n);
    for(i = 0 ; i < n ; i++) {
        matrix[i] = fill_vectors(matrix[i], n);
    }
    sum = trace(matrix , n);
    print_matrix(matrix , n);
    cout << endl << "Sum of the diagonal elements are: " << sum << endl;
}

/// @brief Routine d'initialization qui permet d'allouer la mémoire pour une
///        matrice carrée de taille n et renvoie un pointer vers
///        la matrice allouée
/// @param[in] n est la taille souhaitée de la matrice
/// @return    Renvoie le pointeur vers la matrice allouée
double** initialization(int n)
{
    int i;
    double** matrix ;
    matrix = static_cast<double **>(calloc(n, sizeof(double **)));
    for(i=0 ; i< n ; ++i)
        matrix[i] = static_cast<double *>(calloc(n, sizeof(double *)));
    return (matrix);
}

/// @brief Intitialise un vecteur avec des valeurs aléatoires comprises
///        entre dans l'intervalle [-10;10]
/// @param[in] vec est le vecteur à initialiser
/// @param[in] n   est la taille du vecteur à initialiser
/// @return    Renvoie le vecteur initialisé.
double* fill_vectors(double* vec , int n)
{
    int i ;
    for(i = 0 ; i < n ; i++)
        vec[i] = rand() % 20 - 10 ;
    return vec;
}

/// @brief Affiche les éléments d'une matrice de taille n
/// @param[in] matrix est la matrice à afficher
/// @param[in] n est la taille de la matrice à afficher
void print_matrix(double** matrix , int n)
{
    int i,j;
    for (i= 0 ; i< n ; i++)
    {
        for(j = 0 ; j < n ; j++)
            cout << matrix[i][j] << ", ";
        cout << endl;
    }
}

/// @brief Calcule la trace d'une matrice
/// @param[in] matrix est la matrice dont on souhaite connaître la trace.
/// @param[in] n est la taille de la matrice.
double trace (double** matrix , int n)
{
    int i ;
    double sum = 0.0;
    for(i=0 ; i<n ; i++)
        sum+=matrix[i][i];
    return sum;
}

/*----------- PART 2 : EDO -------------------*/
double phi(double x, double u_x) {
    return 2.*x*u_x;
}

double phi2(double x, double u_x) {
    return 50.*(u_x*cos(x));
}


vector<double> euler_explicit(int iter_count, double initial_value, const function<double(double, double)>& phi) {
    vector<double> sol = vector<double>(iter_count);
    sol[0] = initial_value;
    double pas = 1./(iter_count-1);
    for (int i = 1; i < sol.size(); i++) {
        sol[i] = sol[i-1] + pas * phi(pas*(i-1), sol[i-1]);
    }
    return sol;
}

vector<double> euler_implicit(int iter_count, double initial_value, const function<double(double, double)>& phi) {
    vector<double> sol = vector<double>(iter_count);
    sol[0] = initial_value;
    double pas = 1./(iter_count-1);
    for (int i = 1; i < iter_count; i++) {
        sol[i] = sol[i-1] + pas * phi(pas*(i-1), sol[i-1]);
        sol[i] = sol[i-1] + pas * phi(pas*i, sol[i]);
    }
    return sol;
}

void run_euler_methods(int iter_count, double initial_value, const function<double(double, double)>& phi) {
    auto result = euler_explicit(iter_count, initial_value, phi);
    cout << "Euler explicite" << endl;
    for (auto val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    cout << "Euler implicite" << endl;
    result = euler_implicit(iter_count, initial_value, phi);
    for (auto val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {

    cout << "===Methodes d'Euler (explicite puis implicite) pour phi(x, u(x)) = 2xu(x) et u(0)=1 et N=50 itérations===\n";
    run_euler_methods(90, 1, &phi);

    cout << "\n\n===Methodes d'Euler (explicite puis implicite) pour phi(x, u(x)) = 2xu(x) et u(0)=1 et N=50 itérations===\n";
    run_euler_methods(500, 0, &phi2);
    return 0;
}



