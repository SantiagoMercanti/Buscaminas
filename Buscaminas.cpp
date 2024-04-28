#include <iostream>
#include <windows.h>
#include<stdlib.h>
#define CP 130
#include <ctime>
#include <iomanip>
using namespace std;

void gotoxy(int x,int y);
void Deck(char matrizUsuario[16][30],char matrizEscon[16][30],int fila, int columna, bool& jugando,bool& Salir, int& celdaspordescubrir); //TABLERO DE JUEGO
void pantallaMenu(); //PANTALLA MENU
void pantallaInicio(); //PANTALLA INICIO
bool descubrir(char matrizUsuario[16][30], char matrizEscon[16][30], int x, int y, int& celdaspordescubrir,int fila, int columna); //VER SI LA POSICION ENVIADA ES UNA MINA Y EN CASO CONTRARIO MOSTRAR EL NUMERO DE MINAS QUE TOCA
void jugar(char nivel); //FUNCION DEL JUEGO

int main(int argc, char *argv[]) {
	
	system("mode con: cols=130 lines=40");
	
	pantallaInicio();
	
	return 0;
}

void jugar(char nivel){
	
	int cantMinas,filas, columnas, celdaspordescubrir;
	bool jugando=true;
	char matrizEscon[16][30];
	char matrizUsuario[16][30]={{'?'}};
	srand(time(NULL));
	bool salir=true;
	bool ganar=true;
	
	switch(nivel){
	case '1': cantMinas=10; filas=8; columnas=8;break;
	case '2': cantMinas=40; filas=16; columnas=16;break;
	case '3': cantMinas=99; filas=16; columnas=30;break;
	}
	
	celdaspordescubrir=(filas*columnas)-cantMinas; //CADA VEZ QUE EL JUGADOR DESCUBRA UNA POSICION QUE NO SEA MINA, ESTE NUMERO SE REDUCE EN 1, HASTA LLEGAR A 0 QUE ES CUANDO GANA
	
	while(cantMinas>0){ //COLOCACION ALEATORIA DE MINAS EN LA MATRIZ ESCONDIDA
		int i=rand()% ((filas-1)-0)+1;
		int j=rand()% ((columnas-1)-0)+1;
		
		if(matrizEscon[i][j]!='M'){
			matrizEscon[i][j]='M';
			cantMinas--;
		}
	}
	
	for(int i=0;i<filas;i++){ //COLOCACION DE NUMEROS EN LAS POSICIONES QUE NO SON MINAS EN LA MATRIZ ESCONDIDA
		for(int j=0;j<columnas;j++){
			if(matrizEscon[i][j]!='M'){
				char cont='0';
				for(int k=i-1;k<i+2;k++){
					for(int n=j-1;n<j+2;n++){
						if(matrizEscon[k][n]=='M') cont++;
					}
				}
				matrizEscon[i][j]=cont;
			}
		}
	}
	
	for(int i=0;i<filas;i++){ //COLOCACION DE SIGNOS DE PREGUNTA EN LA MATRIZ QUE VE EL USUARIO
		for(int j=0;j<columnas;j++){
			matrizUsuario[i][j]='?';
		}
	}	
	
	clock_t t; //CONTADOR QUE ARRANCA CUANDO EL JUEGO INICIA
	t=clock();
	
	do{ //LA LLEVADA A CABO DEL JUEGO HASTA QUE GANE, PIERDA O QUIERA SALIR EL USUARIO, HACIENDO LLAMADO AL TABLERO QUE SE ACTUALIZA CADA JUGADA
		if(celdaspordescubrir==0) ganar=false;
		else {
			system("CLS");
			Deck(matrizUsuario,matrizEscon,filas,columnas,jugando,salir,celdaspordescubrir);
		}
	} while(jugando && salir && ganar);
	
	t=clock()-t;
	
	if(!ganar){ 
		system("CLS");
		cout<<endl;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
		cout<<"   ######      ###    ##    ##    ###     ######  ######## ######## ####"<<endl;
		cout<<"  ##    ##    ## ##   ###   ##   ## ##   ##    ##    ##    ##       ####"<<endl;
		cout<<"  ##         ##   ##  ####  ##  ##   ##  ##          ##    ##       ####"<<endl;
		cout<<"  ##   #### ##     ## ## ## ## ##     ##  ######     ##    ######    ##  "<<endl;
		cout<<"  ##    ##  ######### ##  #### #########       ##    ##    ##            "<<endl;
		cout<<"  ##    ##  ##     ## ##   ### ##     ## ##    ##    ##    ##        ##  "<<endl;
		cout<<"   ######   ##     ## ##    ## ##     ##  ######     ##    ########  ##  "<<endl<<endl;
		
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
		cout<<" Tu tiempo fue de: "<<int(t)/CLOCKS_PER_SEC<<" segundos."<<endl<<endl;
	}
	
	else if (!jugando){
		system("CLS");
		
		gotoxy(6, 5);cout<<"    _____                         ____                 "<<endl;
		gotoxy(6, 6);cout<<"   | _ __|                       | __ |                "<<endl;
		gotoxy(6, 7);cout<<"	| |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ "<<endl;
		gotoxy(6, 8);cout<<"	| | |_ || _` | '_ ` _ | | _ | | |  | | | | | _ | '__|"<<endl;
		gotoxy(6, 9);cout<<"	| |__| | (_| | | | | | |  __| | |__| || V |  __| |   "<<endl;
		gotoxy(6, 10);cout<<"	 |_____||__,_|_| |_| |_||___|  |____|  |_| |___|_|   "<<endl;
		
		gotoxy(5, 22);cout<<"Presione una tecla para ver el tablero con las minas."<<endl;
		
		system("PAUSE"); system("CLS");
		
		for(int i=0;i<columnas;i++) { // MUESTRA DEL TABLERO CON LAS MINAS
			if (i==0) cout<<"  | "<<i<<" |";
			else if(i<10) cout<<" "<<i<<setw(1)<<" |";
			else cout<<" "<<i<< setw(1)<<"|";
		}
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
		cout<<" X|"<<endl;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
		cout<<"---";
		for(int i=0;i<columnas;i++){
			cout<<"----";
		}
		cout<<endl;
		for (int i=0;i<filas;i++){
			int cont=0;
			for(int j=0;j<columnas;j++){
				
				if(j==0){
					if(i<10){
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
						cout<<" "<<i;
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
					}
					else {
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
						cout<<i;
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
					}
					cout<<"| ";
					if(matrizEscon[i][j]=='M'){
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
						cout<<matrizEscon[i][j];
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
					}
					else cout<<matrizEscon[i][j];
					cout<<" |";
				}
				else if(j<columnas){
					cout<<" ";
					if(matrizEscon[i][j]=='M'){
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
						cout<<matrizEscon[i][j];
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
					}
					else cout<<matrizEscon[i][j];
					cout<<" |";
				}
				else{
					cout<<" ";
					if(matrizEscon[i][j]=='M'){
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
						cout<<matrizEscon[i][j];
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
					}
				}
				cont++;
			}
			cout<<endl;
			cout<<"---";
			while(cont>0){
				cout << "----";
				cont--;
			}
			cout<<endl;
		}
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
		cout<<" Y|"<<endl;
	}
	
	system("PAUSE");
	
}

void pantallaMenu(){
	char nivel;
	bool chau=true;
	
	system("color 70");
	do{
		system("CLS");
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
		cout<<endl;for(int i=0;i<CP;i++) cout<<"-";cout<<endl;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
		gotoxy(3,3);cout<<"MENU PRINCIPAL";
		gotoxy(3,4);cout<<"°°°°°°°°°°°°°°"<<endl;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
		for(int i=0;i<CP;i++) cout<<"-";cout<<endl;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
		gotoxy(3,9);cout<<"Seleccione Nivel del Juego:";
		gotoxy(3,10);cout<<"===========================";
		gotoxy(3,13);cout<<"1 - Fácil: Tablero de 8x8 con 10 minas";
		gotoxy(3,15);cout<<"2 - Intermedio: Tablero de 16x16 con 40 minas";
		gotoxy(3,17);cout<<"3 - Difícil: Tablero de 16x30 con 99 minas";
		gotoxy(3,19);cout<<"S - Salir";
		gotoxy(3,23);cout<<"Nivel: ";cin>>nivel;
		if(nivel=='S'||nivel=='s'){
			char confirmar;
			do{
				system("CLS");
				cout<<endl<<"  ¿Seguro que desea salir de la aplicación?"<<endl<<endl<<"  Si -> Ingrese 'S'"<<endl<<"  No -> Ingrese 'N'"<<endl<<endl;
				cout<<"  ";cin>>confirmar;
			} while(confirmar!='s'&&confirmar!='S'&&confirmar!='N'&&confirmar!='n');
			if(confirmar=='s'||confirmar=='S')chau=false;
		}
		else if(nivel<'4'&&nivel>'0'){
			system("CLS");
			jugar(nivel);
		}
		else{
			gotoxy(3,23);cout<<"  Valor no válido. Vuelva a ingresar el nivel."<<endl;
			system("PAUSE");
		}
	} while((nivel>'3'&&nivel<='0')||chau);
	
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
	system("CLS");
	gotoxy(3,27);cout<<"¡Gracias por visitar!"<<endl; //CARTEL DE DESPEDIDA
}

void pantallaInicio(){
	char i;
	system("color 70");
	do{
		system("CLS");
		
		cout<<endl<<endl<<endl;
		//cartel de BUSCAMINAS
		for(int i=0;i<CP;i++) cout<<"-";cout<<endl; 
		for(int i=0;i<CP;i++) cout<<"-";cout<<endl;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
		cout<<endl<<"                 @@@@@@   @@@  @@@   @@@@@@    ,@@@@@      @@     @@@     ,@@  @@@  @@    @@     @@@      @@@@@. "<<endl<<"                 @@* /@@. @@@  @@@  @@@  @@@  @@@. @@@    #@@@    @@@@    @@@  @@@  @@@   @@     @@@    ,@@%  @@@"<<endl<<"                 @@*  @@. @@@  @@@  @@@       @@@         @@@@#   @@@@@  @@@@  @@@  @@@@  @@    @@@@@   .@@(     "<<endl<<"                 @@@@@.   @@@  @@@   @@@@@&   @@@        @@@ @@   @@@@@@@@ @@  @@@  @@/@@ @@    @@ @@*    @@@@@  "<<endl<<"                 @@*  @@@ @@@  @@@       @@@  @@@        @@  @@@  @@@ @@@@ @@  @@@  @@* @@@@   @@@ %@@        @@@"<<endl<<"                 @@*  @@@ @@@  @@@  @@@  @@@  @@@  @@@  @@@@@@@@  @@@  @@  @@  @@@  @@*  @@@  &@@@@@@@@ (@@   @@@"<<endl<<"                 @@@@@@@   @@@@@@,   @@@@@@.   @@@@@@, /@@    @@@ @@@      @@  @@@  @@*  .@@  @@@   %@@  @@@@@@@ "<<endl<<endl; 
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
		for(int i=0;i<CP;i++) cout<<"-";cout<<endl;
		for(int i=0;i<CP;i++) cout<<"-";cout<<endl;
		//NOMBRES
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
		gotoxy(32,23);cout<<"  Santiago Mercanti - santi.mercanti15@gmail.com - Comision B"<<endl;
		gotoxy(32,24);cout<<"     Benjamin Pozzi -    benshapozzi@gmail.com   - Comision B"<<endl;
		gotoxy(32,25);cout<<"Lucas José Pairetti -     ljpairetti@gmail.com    - Comision B"<<endl;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
		gotoxy(50,33);cout<<"VERSION 1.0.0 - 2020"<<endl;
		gotoxy(4,36);cout<<"Presione 'i' mas ENTER para comenzar... ";
		
		cin>>i;
		if(i=='i'||i=='I'){
			pantallaMenu();
		}
		
	}while(i!='i'&&i!='I');
}
	
	
	void Deck(char matrizUsuario[16][30],char matrizEscon[16][30],int fila, int columna, bool& jugando, bool& Salir, int& celdaspordescubrir){
		
		int x, y; char a;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
		for(int i=0;i<columna;i++) {
			if (i==0) cout<<"  | "<<i<<" |";
			else if(i<10) cout<<" "<<i<<setw(1)<<" |";
			else cout<<" "<<i<< setw(1)<<"|";
		}
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
		cout<<" X|"<<endl;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
		cout<<"---";
		for(int i=0;i<columna;i++){
			cout<<"----";
		}
		cout<<endl;
		for (int i=0;i<fila;i++){
			int cont=0;
			for(int j=0;j<columna;j++){
				
				if(j==0){
					if(i<10){
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
						cout<<" "<<i;
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
					}
					else {
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
						cout<<i;
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
					}
					cout<<"| ";
					 if(matrizUsuario[i][j]!='?'){
						if(matrizUsuario[i][j]=='X'){
							SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
							cout<<matrizUsuario[i][j];
							SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
						}
						else {
							SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
							cout<<matrizUsuario[i][j];
					        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
						    }
					 }
					 else cout<<matrizUsuario[i][j];
					 cout<<" |";
				}
				else if(j<columna){
					cout<<" ";
					if(matrizUsuario[i][j]!='?'){
						if(matrizUsuario[i][j]=='X'){
							SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
							cout<<matrizUsuario[i][j];
							SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
						}
						else {SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
						cout<<matrizUsuario[i][j];
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
						}
					}
					else cout<<matrizUsuario[i][j];
					cout<<" |";
				}
				else{
					cout<<" ";
					if(matrizUsuario[i][j]!='?'){
						if(matrizUsuario[i][j]=='X'){
							SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
							cout<<matrizUsuario[i][j];
							SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
						}
						else {SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
						cout<<matrizUsuario[i][j];
						SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
						}
					}
				}
				cont++;
			}
			cout<<endl;
			cout<<"---";
			while(cont>0){
				cout << "----";
				cont--;
			}
			cout<<endl;
		}
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
		cout<<" Y|"<<endl;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
		gotoxy(67, 35); cout<<"Acciones admitidas:";
		gotoxy(68, 36); cout<<"M : marcar/desmarcar";
		gotoxy(68, 37); cout<<"D : descubir posición";
		gotoxy(68, 38); cout<<"S : salir";
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
		gotoxy(2, 36); cout<<"Ingrese accion: ";cin>>a;
		
		if(a=='S'||a=='s'){
			char confirmar;
			do{
				system("CLS");
				cout<<endl<<"  ¿Seguro que quiere volver al menú?"<<endl<<endl<<"  Si -> Ingrese 'S' "<<endl<<"  No -> Ingrese 'N'"<<endl<<endl;
				cout<<"  ";cin>>confirmar;
			} while(confirmar!='s'&&confirmar!='S'&&confirmar!='N'&&confirmar!='n');
			
			if(confirmar=='s'||confirmar=='S')Salir= false;
		}
		
		else if(a=='D' || a=='M'||a=='m'||a=='d'){
		gotoxy(2, 37); cout<<"Ingrese valor en X: ";cin>>x;
		gotoxy(2, 38); cout<<"Ingrese valor en Y: ";cin>>y;
		
		    if(x>columna-1 || y>fila-1 ||x<0 ||y<0) {
			    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+4);
			    cout<<"  El valor ingresado no pertenece al tablero"<<endl;
			    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
			    system("PAUSE");
		    }
		    else{ /*if(x<columna || y<fila ||x>0 ||y>0)*/
		        if(a=='M'||a=='m'){
			        if(matrizUsuario[y][x]=='?'){
			        	matrizUsuario[y][x]='X';
			        }
			        else if(matrizUsuario[y][x]=='X'){
				        matrizUsuario[y][x]='?';
			        }
			        else {
				        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
				        cout<<"  Ese casilla ya ha sido descubierta."<<endl;;
				        system("PAUSE");
				        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
			        }
		        }
		        else if(a=='D'||a=='d'){
			        if(matrizUsuario[y][x]=='?'){
				        jugando=descubrir(matrizUsuario,matrizEscon,y,x, celdaspordescubrir, fila, columna);
				        
			        }
			        else if(matrizUsuario[y][x]=='X'){
				        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
				        cout<<"  Ese casilla está marcada."<<endl;
				        system("PAUSE");
				        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
			        }
			        else{
				        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
				        cout<<"  Ese casilla ya ha sido descubierta."<<endl;
				        system("PAUSE");
				        SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
			        }
		        }
		    }
		}
		else /*if(a!='S'&&a!='s')*/ {
			SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+0);
			cout<<"  Accion erronea. Presione enter para indicar un nuevo valor."<<endl;
			SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7*16+1);
			system("PAUSE");
		}
	}	
	
		bool descubrir(char matrizUsuario[16][30], char matrizEscon[16][30], int y, int x, int& celdaspordescubrir, int fila, int columna){
			bool retorno=true;
			if(matrizEscon[y][x]=='M')retorno=false;
			else if(matrizEscon[y][x]=='0'){ //DESAFÍO
				for(int k=y-1;k<y+2;k++){
					if(k>=0&&k<fila){
						for(int n=x-1;n<x+2;n++){
							if(n>=0&&n<columna){
								if(matrizUsuario[k][n]=='?'){
									matrizUsuario[k][n]=matrizEscon[k][n];
									celdaspordescubrir--;
									if(matrizEscon[k][n]=='0'&&!(k==y&&n==x)){
										descubrir(matrizUsuario,matrizEscon, k, n, celdaspordescubrir, fila, columna);
									}
								}
								
								
							}
							
							
						}
					}
					
				}
				
			}
			else {
				matrizUsuario[y][x]=matrizEscon[y][x];
				celdaspordescubrir--;
			}
			return retorno;
		}
		
	void gotoxy(int x,int y){  
		HANDLE hcon;  
		hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
		COORD dwPos;  
		dwPos.X = x;  
		dwPos.Y= y;  
		SetConsoleCursorPosition(hcon,dwPos);  
	}
