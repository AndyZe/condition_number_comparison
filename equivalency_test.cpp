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
  
  int size = 2;
  MatrixXd m(size,size);
  for (int row=0; row<size; ++row)
  	for (int col=0; col<size; ++col)
	{
		m(row,col) = distr(eng);
	}

  return m;
}

void calculate_condition_with_norms(MatrixXd &m)
{
  // K = ||m^-1||*||m||
  std::cout << "Result with norm method: " << m.inverse().norm() * m.norm() << std::endl;
}

void calculate_condition_with_singular_values(MatrixXd &m)
{
  // K = sigma_max(m) / sigma_min(m)
  // Declaring svd globally or locally here makes very little difference
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(m);
  std::cout << "Result with singular value method: " << svd.singularValues()(0) / svd.singularValues()(svd.singularValues().size() - 1) << std::endl;
}

int main()
{
  // Fill a random 6x6 matrix
  // Calculate condition number with the norm method
  // Then calculate it with the singular value method
  // Print both out so user can verify them

  MatrixXd m = generate_random_6x6();

  calculate_condition_with_norms(m);

  calculate_condition_with_singular_values(m);
}