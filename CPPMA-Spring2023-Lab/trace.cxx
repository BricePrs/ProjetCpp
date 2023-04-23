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

vector<double> euler_explicite(int iter_count, double initial_value, const function<double(double, double)>& phi);
vector<double> euler_implicite(int iter_count, double initial_value, const function<double(double, double)>& phi);


double phi(double x, double ux) {
    return 2.*x*ux;
}

double phi2(double x, double ux) {
    return 50.*(ux*cos(x));
}

/// Driver principal pour le calcul de la tace d'une matrice 
int main()
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

  cout << "Methode d'Euler" << endl << "Entrez le nombre d\'iterations a effectuer :";
  int iter_count = 0;
  cin >> iter_count;
  cout << endl << "Entrez la valeur initiale :";
  double init_val;
  cin >> init_val;
  auto result = euler_explicite(iter_count, init_val, &phi2);
  cout << "Euler explicite" << endl;
  for (auto val : result) {
      std::cout << val << " ";
  }
  std::cout << std::endl;

  cout << "Euler implicite" << endl;
  result = euler_implicite(iter_count, init_val, &phi2);
  for (auto val : result) {
      std::cout << val << " ";
  }
  std::cout << std::endl;

  return 0;
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

vector<double> euler_explicite(int iter_count, double initial_value, const function<double(double, double)>& phi) {
    vector<double> sol = vector<double>(iter_count);
    sol[0] = initial_value;
    double pas = 1./(iter_count-1);
    for (int i = 1; i < sol.size(); i++) {
        sol[i] = sol[i-1] + pas * phi(pas*(i-1), sol[i-1]);
    }
    return sol;
}

vector<double> euler_implicite(int iter_count, double initial_value, const function<double(double, double)>& phi) {
    vector<double> sol = vector<double>(iter_count);
    sol[0] = initial_value;
    double pas = 1./(iter_count-1);
    for (int i = 1; i < sol.size(); i++) {
        sol[i] = sol[i-1] + pas * phi(pas*(i-1), sol[i-1]);
        sol[i] = sol[i-1] + pas * phi(pas*i, sol[i]);
    }
    return sol;
}

