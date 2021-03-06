#include "globals.h"

void Calculate_Bias()
// As suggested by Klaus Dolag.
{
  double epsilon = 0.01; // to avoid divergence.
  double bias = 0.0;
  double rho_mean = 0.0;
  int i;

  // loop to find rho_mean of particles.
  for ( i = 0; i < Param.Npart; i++)
  {
    rho_mean += SphP[i].Rho;
  }
  rho_mean /= Param.Npart;

  for ( i = 0; i < Param.Npart; i++)
  {
    bias +=  ( SphP[i].Rho - SphP[i].Rho_Model ) /
               ( SphP[i].Rho_Model - rho_mean +
                 ( SphP[i].Rho_Model - rho_mean) /
                 fabs( SphP[i].Rho_Model - rho_mean ) *
                rho_mean * epsilon);  // bias calculation (eq. )
  }

  bias /= Param.Npart;
  bias *= -1.0;   // reverse sign to be conform with formulation of bias subtraction.

  printf("\nDensity Bias: %g\n\n", bias);
}
