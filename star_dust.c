#include <stdio.h>
#include <stdlib.h>

//functie pentru operatia "Modify" (modificare)
void modify(char **harta_byte, int *elemente_harta, int l, int dimensiune_bloc, int bloc){
        //declaram nr si byte* pt retinerea valorilor byte-ilor din diferitele tipuri de date
	//declaram nr_elem_vechi si *linie_realocata ca element ajutator pentru realocaea moemoriei 
 
	int byte1, byte2, byte, nr;
	int nr_elem_vechi;

	//in caz ca byte-tii ce trebuie modificati se afla in afara zonei de memorie, se realoca memoria pentru linia respectiva
	if(dimensiune_bloc * bloc > elemente_harta[l]){
		char *linie_realocata;
		linie_realocata = (char *)realloc(harta_byte[l], sizeof(int) * bloc);
		harta_byte[l] = linie_realocata;
		nr_elem_vechi = elemente_harta[l];
		//redefinim numarul de elemente de pe o linie dupa realocare
		elemente_harta[l] = bloc * sizeof(int);
		//byte-tii dintre numarul modificat si numerele existente deja in harta se zeroizeaza
		for(int i = nr_elem_vechi; i<elemente_harta[l]; i++){
			harta_byte[l][i] = (char) 0;
		}
	}	
		//se citeste numarul care va fi inlocuitor pentru anumiti byte-ti din memorie
		scanf("%x", &nr);

		//daca numarul e de tip short int, se va imparti in 2 byte-ti prin shiftare si se vor adauga/suprascrie in memorie 
		if(dimensiune_bloc == 2){
			byte1 = (nr << 24) >> 24;
			byte2 = (nr << 16) >> 24;
		
			harta_byte[l][dimensiune_bloc * bloc - dimensiune_bloc] = (byte1 & 0xFF);
	
			harta_byte[l][dimensiune_bloc * bloc - dimensiune_bloc + 1] = (byte2 & 0xFF);
			}

		//daca numarul e de tip int, se va imparti in 4 byte-ti prin shiftare si se vor adauga/suprascrie in memorie
		if(dimensiune_bloc == 4){
			for(int i =dimensiune_bloc - 1; i >= 0; i--){
				byte = (nr << (i*8)) >> 24;
				harta_byte[l][dimensiune_bloc * bloc - dimensiune_bloc + (3 - i)] = (byte & 0xFF);
			}
		}

		//daca numarul e de tip char, va ramane ca atare un singur byte si se va adauga/suprascrie in memorie
		if(dimensiune_bloc == 1){
			harta_byte[l][dimensiune_bloc * bloc - 1] = (nr & 0xFF);
		}
				


}

//functie pentru operatia "Swap" (interschimbare)
void swp(char **harta_byte, int l, int dimensiune_bloc, int bloc){
	//se declara un char auxiliar pentru operatia de interschimbare
	char aux;
	//daca tipul de date e short, se vor interschimba 2 byte-ti
	if(dimensiune_bloc == 2){
		aux = harta_byte[l][dimensiune_bloc * bloc];
	        harta_byte[l][dimensiune_bloc * bloc] =  harta_byte[l][dimensiune_bloc * bloc + 1];
		harta_byte[l][dimensiune_bloc * bloc + 1] = aux;	
	}
	//daca tipul de date e int, se vor interschimba 4 byte-ti, 2 cate 2
	if(dimensiune_bloc == 4){
		aux = harta_byte[l][dimensiune_bloc * bloc];
		harta_byte[l][dimensiune_bloc * bloc] = harta_byte[l][dimensiune_bloc * bloc + 3];
		harta_byte[l][dimensiune_bloc * bloc + 3] = aux;
		aux = harta_byte[l][dimensiune_bloc * bloc + 1];
		harta_byte[l][dimensiune_bloc * bloc + 1] = harta_byte[l][dimensiune_bloc * bloc + 2];
	        harta_byte[l][dimensiune_bloc * bloc + 2] = aux;
	}
}

//functie pentru operatia "Delete" (stergere)
void del(char **harta_byte, int l, int dimensiune_bloc, int  bloc){
	//pentru operatia de stergere, se vor zeroiza toti byte-tii de pe o zona de memorie
	for(int i = 0; i< dimensiune_bloc; i++){
		harta_byte[l][dimensiune_bloc * bloc - dimensiune_bloc + i] = (char)0;
	}
}

//functie pentru rezolvarea taskului 1
void task1(int nr_linii, int *elemente_harta, char **harta_byte){
	//pentru taskul 1, declaram suma, numarul si media aritmetica a byte-tilor
	double suma_bytes = 0.0;
	int nr_bytes = 0;
	double m_a;
	//pentru fiecare element de pe prima si ultima linie sau de pe mariginile celorlalte linii, se vor contoriza suma si numarul acestora
	for(int i =0; i<nr_linii; i++){
		for(int j =0; j< *(elemente_harta +i); j ++){
			if(i == 0 || i == (nr_linii -1)){
				nr_bytes++;
				suma_bytes += harta_byte[i][j];
			}
			else if(*(elemente_harta + i) == 1){
				nr_bytes++;
				suma_bytes += harta_byte[i][j];
			}
			else if(j == 0 || j == (*(elemente_harta + i) - 1)){
				nr_bytes++;
				suma_bytes += harta_byte[i][j];
			}
		}
	}
		//se calculeaza media aritmetica de tip double si se afiseaza cu precizie de 8 zecimale
		m_a = (double)(suma_bytes/nr_bytes);
		printf("%0.8lf\n", m_a);
			
}

//functie pentru rezolvarea taskului 2
void task2(char **harta_byte, int *elemente_harta){
	//se declara si se citesc datele importante pt taskul 2: operatia(M, S, D), tipul de date(C, S, I), linia din matrice si blocul de date pe care se va lucra
	char op, tip_date;
	int l, dimensiune_bloc, bloc;
	scanf(" %c", &op);
	scanf(" %c", &tip_date);
	scanf("%d", &l);
	scanf("%d", &bloc);
		//daca tipul de date e char, dimensiunea acestuia e de 1 byte
		if(tip_date == 'C'){
			dimensiune_bloc = 1; 
		}
		//daca tipul de date e short, dimensiunea acestuia e de 2 bytes
		if(tip_date == 'S'){
			dimensiune_bloc = 2;	
		}	
		//daca tipul de date e int, dimensiunea acestuia e de 4 bytes
		if(tip_date == 'I'){
			dimensiune_bloc = 4;

		}	
		//daca operatia e 'M', se va apela functia modify
		if(op == 'M'){
			modify(harta_byte, elemente_harta, l, dimensiune_bloc, bloc);
		}
		//daca operatia e 'S', se va apela functia swp
		if(op == 'S'){
			swp(harta_byte, l, dimensiune_bloc, bloc);
		}
		//daca operatia e 'D', se va apela del
		if(op == 'D'){
			del(harta_byte, l, dimensiune_bloc, bloc);
		}

}	


void fill(char **harta_byte, int *elemente_harta, int nr_linii, int x, int y,int *suma){
	printf("a intrat in functie\n");
	
	if(x < 0 || y <0 || x == nr_linii || y == elemente_harta[x]) return;
	printf("fill pe pozitia %d, %d\n", x, y);
	*suma+=1;
	printf("suma actuala este acum: %d\n", *suma);
	harta_byte[x][y] = '1';
	printf("harta are in punctul asta valoare %d", harta_byte[x][y]);
	if((x-1>0) && (y >0) && (y != elemente_harta[x]) && ((x-1) != nr_linii) && (harta_byte[x-1][y] == 0)){ fill(harta_byte, elemente_harta, nr_linii, x-1, y, suma);}
        if((x>0) && ((y-1) >0) && ((y-1) != elemente_harta[x]) && (x!= nr_linii) && (harta_byte[x][y-1] == 0)){ fill(harta_byte, elemente_harta, nr_linii, x, y-1, suma);}
	if(((x+1) > 0) && (y>0) && (y != elemente_harta[x]) && ((x+1)!=nr_linii) && (harta_byte[x+1][y] == 0)){ fill(harta_byte, elemente_harta, nr_linii, x+1, y, suma);}
	if((x > 0) && ((y+1)> 0) && ((y+1) != elemente_harta[x]) && (x!=nr_linii) && (harta_byte[x][y+1] == 0)){ fill(harta_byte, elemente_harta, nr_linii, x, y+1, suma);}	

}

void num_gauri_negre(char **harta_byte, int *elemente_harta, int nr_linii){
	int suma_maxima =0, coordonate_x =0, coordonate_y =0;
	int suma;
	suma = 0;
	for(int i =0; i<nr_linii; i++){
		for(int j =0; j<elemente_harta[i]; j++){
			if(harta_byte[i][j] == '0'){
				printf("a gasit un 0 pe pozitia %d, %d\n", i, j);
				fill(harta_byte, elemente_harta, nr_linii, i, j, &suma);					
				if(suma > suma_maxima){
					printf("suma maxima: %d, suma actuala: %d\n", suma_maxima, suma);
					coordonate_x = i;
					coordonate_y = j;
				        suma_maxima = suma;
					printf("%d\n", suma_maxima);
				}	  
			}
		}
		suma =0;
	}	
	printf("%d %d ",coordonate_x, coordonate_y); 
	printf("%d", suma_maxima);

}


int main(){
	//se declara harta tip matrice si nr elementelor de pe fiecare linie intr-un vector
	int nr_linii, *elemente_harta, nr_operatii;
	char **harta_byte;
	
	//se citeste numarul d elinii, apoi se aloca memorie pentru matrice si vector
	scanf("%d", &nr_linii);
	elemente_harta = (int *) malloc(nr_linii * sizeof(int));
	harta_byte = (char **) malloc(nr_linii * sizeof(char*)); 

	//se citeste matricea
	for(int i =0; i<nr_linii; i++){
		scanf("%d", (elemente_harta+i));
		*(elemente_harta +i) *= 4; 
		*(harta_byte+i) = (char *) malloc(*(elemente_harta+i) * sizeof(char));
		for(int j=0; j<*(elemente_harta+i); j+=4){
			scanf("%x", (unsigned int *) (*(harta_byte+i)+j));
		}
	}
/*	for(int i =0; i<nr_linii; i++){
		for(int j =0; j<(*(elemente_harta+i)); j++){
			printf("%02x ", *(*(harta_byte+i)+j) & 0xFF);
		}
	}*/
		//se rezolva taskul 1
		printf("task 1\n");
		task1(nr_linii, elemente_harta, harta_byte);
		//se citeste numarul de operatii pentru taskul 2 si apoi se rezolva taskul 2
	
		scanf("%d", &nr_operatii);
		for(int i =0; i< nr_operatii; i++){
			task2(harta_byte, elemente_harta);
		}

		printf("task 2\n");

		//se afiseaza matricea dupa modificari	
		for(int i =0; i<nr_linii; i++){
			for(int j =0; j<(*(elemente_harta+i)); j += 4){
				for(int t = 3; t>=0; t--){
					printf("%02X", *(*(harta_byte+i)+(j+t)) & 0xFF);
				}
				printf(" ");
			}
			printf("\n");
		}

		//se elibereaza memoria
		printf("task 3\n");
		num_gauri_negre(harta_byte, elemente_harta, nr_linii);
		for(int i =0; i<nr_linii; i++){
			free(harta_byte[i]);
		}
		free(harta_byte);
		free(elemente_harta);

		
	

		
	return 0;
}
