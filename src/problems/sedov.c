#include "../globals.h"
#include <gsl/gsl_sort.h>

void setup_Sedov_Blast()
{
    Problem.Boxsize[0] = 3;
    Problem.Boxsize[1] = 3;
    Problem.Boxsize[2] = 3;

    sprintf ( Problem.Name, "IC_SedovBlast" );

    const double rho = 1.24E7;

    Problem.Rho_Max = rho;

    Density_Func_Ptr = &Sedov_Blast_Density;
    U_Func_Ptr = &Sedov_Blast_U;
    PostProcessing_Func_Ptr = &Sedov_Blast_PostProcessing;
}

float Sedov_Blast_Density ( const int ipart )
{
    return 1.24E7;
}

// This function counts to the the wanted particle number
// initializing the explosion and saves maximum of the
// distance within this subset of particles

float Sedov_Blast_abs ( const int ipart )
{

    int NNpart = 32;
    int i;

    // double const Estimated_Radius = pow((3 * Problem.Boxsize[0] * NNpart / 2 / pi / Param.Npart), 1./3.);
    double abs_of_zero[ipart];
    double sort_abs_of_zero[ipart];

    for ( i = 0; i < Param.Npart; i++ ) {

        abs_of_zero[i] = sqrt ( ( P[i].Pos[0] - 0.5 * Problem.Boxsize[0] ) * ( P[i].Pos[0] - 0.5 * Problem.Boxsize[0] ) + ( P[i].Pos[1] * 0.5 * Problem.Boxsize[1] ) * ( P[i].Pos[1] - 0.5 * Problem.Boxsize[0] )
                                + ( P[i].Pos[2] - 0.5 * Problem.Boxsize[2] ) * ( P[i].Pos[2] - 0.5 * Problem.Boxsize[2] ) );
    }

    sort_abs_of_zero = gsl_sort_vector ( abs_of_zero );

    return sort_abs_of_zero[NNpart];

}

float Sedov_Blast_U ( const int ipart )
{

    const double x = P[ipart].Pos[0] - Problem.Boxsize[0] * 0.5;
    const double y = P[ipart].Pos[1] - Problem.Boxsize[1] * 0.5;
    const double z = P[ipart].Pos[2] - Problem.Boxsize[2] * 0.5;
    double Radius = sqrt ( x * x + y * y + z * z );
    // int NNpart = 32;
    const double  Supernova_Energy = 0.00502765; // This is the value of one supernova energy per unit mass in Gadget units 1e51 erg
    // const double hsml = SphP[i].Hsml;

    if ( Radius <= Sedov_Blast_abs ( ipart ) ) {

        return Supernova_Energy;

    } else {
        return 0.0;
    }
}

/*void Sedov_Blast_PostProcessing ()
{
    const double u_sn = 4.18971E5;
    int sn_count = pow ( Param.Npart / 3200., 3.0 );
    sn_count = min ( sn_count, 1 );
    //! @todo assign u_sn to sn_count innermost particles
}*/
