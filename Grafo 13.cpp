#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <locale.h>
#include <string.h>
using namespace std;

///// Función Gotoxy
void gotoxy(int x,int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y= y;
	SetConsoleCursorPosition(hcon,dwPos);
}

///// Función para maximizar pantalla
void AltEnter(){
	keybd_event(VK_LWIN,0x38,0,0);
	keybd_event(VK_UP,0x1c,0,0);
	keybd_event(VK_LWIN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_UP,0x38,KEYEVENTF_KEYUP,0);
	return;
}

void membrete(){
	cout<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl
			<<"::                                                                                                ::"<<endl
			<<":: Ing. de Sistemas                                                          INTEGRANTES:         ::"<<endl
			<<":: 5to semestre                               GRAFO 13            - Chirinos, Enmanuel 26.058.259 ::"<<endl
			<<":: Sección \"A\"                                                    - Petit, Anyelo      26.057.580 ::"<<endl
			<<"::                                                                - Vargas, Paola                 ::"<<endl
			<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl;
	int dia, mes, anno;
	string mess;
	time_t ahora;
  struct tm *fecha;

  time(&ahora); 
  fecha = localtime(&ahora); 
  
  dia=fecha->tm_mday;
  mes=fecha->tm_mon+1; 
  anno=fecha->tm_year+1900;
  if (mes==1) mess="Enero";if (mes==2) mess="Febrero";if (mes==3) mess="Marzo";
	if (mes==4) mess="Abril";if (mes==5) mess="Mayo";if (mes==6) mess="Junio";
	if (mes==7) mess="Julio";if (mes==8) mess="Agosto";if (mes==9) mess="Septiembre";
	if (mes==10) mess="Octubre";if (mes==11) mess="Noviembre";if (mes==12) mess="Diciembre";
  cout<<"                                   Punto Fijo, "<<dia<<" de "<<mess<<" del "<<anno<<"."<<endl<<endl;
}

// añadir vértice
int addnode(int &v){
	cout<<"\n *** SE HA AÑADIDO EL VÉRTICE ("<<++v<<") AL GRAFO. ***";
	getch();
	return v;
}

// grafo
void grafo(){
	int op, v=0, q=0, e[99][99], impares=0, val=0;
	
	do{
		system("cls");
		membrete();
		cout<<" 1. Añadir vértice."<<endl
				<<" 2. Añadir arista."<<endl
				<<" 3. Ver matriz adyacencia (no-binaria)"<<endl
				<<" 4. Verificar si existe un circuito o recorrido euleriano"<<endl<<endl
				<<" 0. Salir"<<endl<<endl
				<<" v="<<v<<" q="<<q<<endl<<endl // Cantidad de vértices (v) y aristas (q) en el grafo
				<<"    Opción: ";
		cin>>op;
		
		switch (op){
		  case 1: 
				cout<<"\n *** Se ha añadido el vértice "<<++v<<" al grafo. ***";
		 		getch();
				break;
	
			case 2: int i, j;
				if (v==0){
					 cout<<"\n ERROR: DEBE EXISTIR AL MENOS UN VÉRTICE PAR CREAR UNA ARISTA";
					 getch();
					 break;
				}
				else if (v==1){
					cout<<" ¿Desea crear un bucle en este único vértice? 1=Si 2=No: ";
					int opc;
					cin>>opc;
					if (opc==1){
						e[0][0]+=2;
						q++;
						// la arista e en la posicion i=1 y j=1 ahora es 1
					}
					break;
				}
				do{
					cout<<" Primer vértice que desee conectar: ";
					cin>>i;
					if (i>v) cout<<" ERROR: EL VÉRTICE NO SE ENCUENTRA EN EL GRAFO\a"<<endl;
				}while(i>v);
				do{
					cout<<" Segundo vértice que desee conectar: ";
					cin>>j;
					if (j>v) cout<<" ERROR: EL VÉRTICE NO SE ENCUENTRA EN EL GRAFO\a"<<endl;
				}while(j>v);
				if (i==j){
					cout<<" ¿Desea crear un bucle en este vértice? 1=Si 2=No: ";
					int opc;
					cin>>opc;
					if (opc==1){
						e[i-1][i-1]+=2;
						q++;
					}
					break;
				}
				// se le suma la arista al valor ixj y al jxi porque es no-dirigido
				// al ser un grafo no-dirigido la matriz adyacencia es simétrica
				e[i-1][j-1]+=1;
				e[j-1][i-1]+=1;
				q++;
				break;
        break;
			
			case 3: 
				// se muestra la fila de arriba E 1 2 3 ... N
				cout<<" E ";
				for(int i=0; i<v; i++){
					cout<<i+1<<" ";
				}
				cout<<endl;
				// se muestra cada fila con sus valores y su índice 1\n 2\n 3\n... N\n
				for(int j=0; j<v; j++){
				  cout<<" "<<j+1<<" ";
					for(int i=0; i<v; i++){
						cout<<e[i][j]<<" ";
					}
					cout<<endl;
				}
				getch();
				break;
			
			case 4: 
        impares=0;
				for(int j=0; j<v; j++){
					val=0;
					for(int i=0; i<v; i++){
						val+=e[i][j];
					}
					if (val%2!=0){
						impares++;
					}
					cout<<" val["<<j+1<<"]="<<val<<" impares="<<impares<<endl;
				}
				if (impares==0)
				  cout<<" Todos los vértices son de grado PAR, por ende existe un circuito.";
				else if (impares==2)
	 	 		  cout<<" Existen exactamente dos vértices de valencia impar, por ende existe un recorrido.";
				else {
	   		  if (impares==1) 
   		      cout<<" Sólo un vértice es de valencia impar. "<<endl;
					else if (impares>2) 
  		 		  cout<<" Existen más de dos vértices de grado impar."<<endl;
	   		  cout<<" ****** NO EXISTE NI UN CIRCUITO NI UN RECORRIDO EULERIANO.\a *****";
				}
				getch();
 				break;
				
			case 0: break;					
			
			default:
				cout<<" ERROR: INGRESE UNA OPCIÓN VÁLIDA\a";
				break;
		}
	}while(op!=0);
}

int main(){
	setlocale(LC_CTYPE, "Spanish");
	system("color 00");
	AltEnter();
	char despedida[] = " Hasta luego... ¡Vuelva pronto!";
	
	grafo();
	
	for(int i=0;despedida[i]!='\0';i++){
		cout<<despedida[i];
		Sleep(30); 
	}  

}
