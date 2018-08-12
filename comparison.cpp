#include <ctime>
#include <iostream>
#include <Eigen/Dense>
#include <random>

using Eigen::MatrixXd;

MatrixXd generate_random_6x6()
{
  // obtain a random number from hardware
  std::random_device rd;
  // seed the generator
  std::mt19937 eng(rd());
  // define the range
  std::uniform_real_distribution<> distr(-1000, 1000);
  
  MatrixXd m(6,6);
  for (int row=0; row<6; ++row)
  	for (int col=0; col<6; ++col)
	{
		m(row,col) = distr(eng);
	}

  return m;
}

void calculate_condition_with_norms(MatrixXd &m)
{
  // K = ||A^-1||*||A||
  (m.inverse()).norm() * m.norm();
}

void calculate_condition_with_singular_values(MatrixXd &m)
{
  // K = sigma_max(m) / sigma_min(m)
  // Declaring svd globally or locally here makes very little difference
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(m);
  svd.singularValues()(0) / svd.singularValues()(svd.singularValues().size() - 1);
}

void do_test_with_norms()
{
  std::clock_t start;
  start = std::clock();

  for (int i=0; i<100000; ++i)
  {
    MatrixXd m = generate_random_6x6();
    calculate_condition_with_norms(m);
  }

  double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  std::cout << "Duration for the norm method: " << duration << "s" << std::endl;
}

void do_test_with_singular_values()
{
  std::clock_t start;
  start = std::clock();

  for (int i=0; i<100000; ++i)
  {
    MatrixXd m = generate_random_6x6();
    calculate_condition_with_singular_values(m);
  }

  double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  std::cout << "Duration for the singular value method: " << duration << "s" << std::endl;
}

int main()
{
  // For the method based on norms:
	// Start a timer
	// Loop 200x:
	  // Generate a random 6x6 matrix
	  // Compute the condition number
	// Print out the time
  // Likewise for the method based on singular values

  do_test_with_norms();
  do_test_with_singular_values();
}