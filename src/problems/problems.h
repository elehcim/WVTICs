#ifndef WVTICS_PROBLEMS_H_H
#define WVTICS_PROBLEMS_H_H

void setup_Constant_Density();
float Constant_Density ( const int ipart );

void setup_TopHat_Density();
float TopHat_Density ( const int ipart );

void setup_Sawtooth_Density();
float Sawtooth_Density ( const int ipart );

void setup_SineWave_Density();
float SineWave_Density ( const int ipart );

void setup_Gradient_Density();
float Gradient_Density ( const int ipart );

void setup_Magneticum_Density();
float Magneticum_Density ( const int ipart );

void setup_Png_Density();
float Png_Density ( const int ipart );

void setup_Double_Shock ( const int subflag );
float Double_Shock_Density ( const int ipart );
float Double_Shock_U ( const int ipart );
void Double_Shock_Velocity ( const int ipart, float vel[3] );

void setup_Sod_Shock();
float Sod_Shock_Density ( const int ipart );
float Sod_Shock_U ( const int ipart );

void setup_Sedov_Blast();
float Sedov_Blast_Density ( const int ipart );
float Sedov_Blast_U ( const int ipart );
void Sedov_Blast_PostProcessing();

void setup_User_Density ( const int subflag );
float User_Density ( const int ipart );
float User_U ( const int ipart );
void User_Bfld ( const int ipart, float out[3] );
void User_PostProcessing();

#endif //WVTICS_PROBLEMS_H_H
