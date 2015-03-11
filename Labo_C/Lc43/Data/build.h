#ifndef __BUILD_HEADER
	#define __BUILD_HEADER

	#define HARDCODE_DATA 1

	void __add_build(data_ouvrier_t *data, long numregistre, char nom[25], char prenom[30], char d_naiss_d, char d_naiss_m, short d_naiss_y, char rue[50], int codepostal, char ville[20], char specialite[20], char d_engag_d, char d_engag_m, short d_engag_y);
	void __build_hardcode_ouvrier(data_ouvrier_t *full);

	void Build_Ouvrier_FirstTime(char *filename, short hard);
	void Build_Chantier_FirstTime(char *filename);
#endif