#pragma once
//#include<iostream>
#include"Scan_System.h"


class Meniu
{
private:
	void start_page()
	{
		int optiune = 0;

		std::cout << "    Aplicatie pentru detectarea documentelor plagiat!\n"
			"			Bine a-ti venit! \n Va rog sa introduceti datele necesare! 		"
			"	Meniu! \n"
			"=====================================================\n"
			"	1) Scanare completa (fara limita inferioara)\n"
			"	2) Scanare completa (cu limita inferioara)\n"
			"	--------------------------------------------\n"
			"	3) Exit"
			"=====================================================\n"
			"		Optiunea dumneavoastra este : \n    ";
		std::cin >> optiune;
		if (optiune == 1)
			C_scan_No_Limit();
		else if (optiune == 2)
			C_scan_Limit();
		else if (optiune == 3)
			exit;

	
	}

	void C_scan_No_Limit()
	{
		
		char fisier_copie[200], plagiat[200];//dupa fisierul plagiat a fost facut cel copiat.... se va verifica cel copiat
		system("cls");
		std::cout << " Trebuie sa introduceti cele doua fisiere:	\n"
			"Primul fisier este cel considerat copie ( introduceti adresa): ";
		std::cin >> fisier_copie;


		std::cout << "\n  Cel de-al doilea fisier este cel considerat plagiat ( introduceti adresa ) :   ";
		std::cin >> plagiat;

		//cele 2 fisiere trebuie trimise mai departe catre sistemul principal de scanare
	
	}


	void C_scan_Limit() // se va considera plagiat doar daca textug comun va fi asemanator  dupa un anumit procentaj
	{
		float limit = 0;
		char fisier_copie[200], plagiat[200];
		system("cls");
		std::cout << "Introduceti procentajul de asemanare dorit: ";
		std::cin >> limit;

		std::cout << " Trebuie sa introduceti cele doua fisiere:	\n"
			"Primul fisier este cel considerat copie ( introduceti adresa): ";
		std::cin >> fisier_copie;


		std::cout << "\n  Cel de-al doilea fisier este cel considerat plagiat ( introduceti adresa ) :   ";
		std::cin >> plagiat;

	// se va apela metoda din sisteul central de scanare.....
	};
public:


	void Menu_Method()
	{
		this->start_page();
	
	};

};