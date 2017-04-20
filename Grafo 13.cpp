#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
using namespace std;

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
			<<"::                                                                - Vargas, Paola      27.723.540 ::"<<endl
			<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl<<endl;
}

// añadir vértice
int addnode(int &v){
	cout<<"\n *** SE HA AÑADIDO EL VÉRTICE ("<<++v<<") AL GRAFO. ***";
	getch();
	return v;
}

// grafo
void grafo13(){
	int op, v=0, q=0, e[99][99], impares=0, val[99], vi[99], vf[99], aislados=0, repite=0, cont=0, repitemas=0;
  set<int> k;
	vector<int> inc;
	
	do{
	  int aux2=0;
    int av[v];// DECLARACION DE ARREGLO DE VÉRTICES
		int visited[q], aux; // Aux es el current node mientras se recorre el vértice
		set<int> vr; // vértices recorridos
    bool allvisited=false;
		system("cls");
		membrete();
		cout<<" 1. Añadir vértice."<<endl
				<<" 2. Añadir arista."<<endl
				<<" 3. Ver matriz adyacencia (de valencias)."<<endl
				<<" 4. Ver lista de aristas."<<endl
				<<" 5. Verificar si existe un circuito o recorrido euleriano."<<endl
        <<" 6. Eliminar grafo."<<endl<<endl
				<<" 0. Salir."<<endl<<endl
				<<" Vértices= "<<v<<" Aristas= "<<q<<": "; // Cantidad de vértices (v) y aristas (q) en el grafo
				for(int i=0;i<q;i++){
				  cout<<"("<<vi[i]<<","<<vf[i]<<") ";
        }
    cout<<endl<<endl 
				<<"    Opción: ";
		cin>>op;
		cout<<endl;
		
		switch (op){
		  case 1: 
				addnode(v);
				break;
	
			case 2: int v1, v2;
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
						e[0][0]+=2; // el vértice 1 pasaría a tener valencia 2 por el lazo
						vi[0]=1; // el vértice inicial de la arista es 1
						vf[0]=1; // el vértice final de la arista también es 1
						q++; // se le suma 1 a la cantidad total de aristas
						// la arista e en la posicion i=1 y j=1 ahora es 2
					}
					break;
				}
				do{
					cout<<" Primer vértice que desee conectar: ";
					cin>>v1;
					vi[q]=v1;
					if (v1>v) cout<<" ERROR: EL VÉRTICE NO SE ENCUENTRA EN EL GRAFO\a"<<endl;
				}while(v1>v);
				do{
					cout<<" Segundo vértice que desee conectar: ";
					cin>>v2;
					vf[q]=v2;
					if (v2>v) cout<<" ERROR: EL VÉRTICE NO SE ENCUENTRA EN EL GRAFO\a"<<endl;
				}while(v2>v);
				if (v1==v2){
					cout<<" ¿Desea crear un bucle en este vértice? 1=Si 2=No: ";
					int opc;
					cin>>opc;
					if (opc==1){
						e[v1-1][v1-1]+=2; // se crea un lazo en el índice que indicó el usuario -1
						vi[q]=v1; // se agrega i como vértice inicial en la posición q
						vf[q]=v1; // se agrega j como vértice final en la posición q
						q++;
					}
					break;
				}
				e[v1-1][v2-1]+=1; // se le suma la arista al valor ixj y al jxi porque es no-dirigido
				e[v2-1][v1-1]+=1; // al ser un grafo no-dirigido la matriz adyacencia es simétrica
				vi[q]=v1; // se agrega i como vértice inicial en la posición q
				vf[q]=v2; // se agrega j como vértice final en la posición q
				q++;
				
				k.insert(vi[0]);
				k.insert(vf[0]);
				if (k.count(v1)>0) k.insert(v2);
				if (k.count(v2)>0) k.insert(v1);
        break;
			
			case 3: 
				// se muestra la fila de arriba E 1 2 3 ... N
				if (v==0){
				  cout<<" ERROR: *** MATRIZ VACÍA *** NO EXISTEN VÉRTICES EN EL GRAFO.";
				  getch();
				  break;
        }
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
			  if (q==0){
			    cout<<" ERROR: *** LISTA VACÍA *** NO EXISTEN ARISTAS EN EL GRAFO";
			    getch();
			    break;
        }
        cout<<"\n LISTA DE ARISTAS:"<<endl;
			  for(int i=0; i<q; i++){
			    cout<<" "<<i+1<<": ("<<vi[i]<<","<<vf[i]<<")"<<endl;
        }
        getch();
			  break;
			
			case 5: 
        
				// Inicialización del arreglo de visitado
				for(int i=0; i<q; ++i){
				  visited[i]=false;
        }
        
        for(int i=0;i<q;++i){//LLENADO DEL ARRAY DE VÉRTICES  
        	av[i]=i+1;
				}
				
        if(v==0){
          cout<<"\n ERROR: NO EXISTEN VÉRTICES EN EL GRAFO. INGRESE VÉRTICES ANTES DE VERIFICAR."<<endl;
          getch();
          break;
        }
        else if(q==0){
          cout<<"\n No existen aristas en el grafo, por lo tanto es no-conexo con "<<v<<" componentes."<<endl;
  	   		cout<<"\n ****** NO EXISTE NI UN CIRCUITO NI UN RECORRIDO EULERIANO.\a *****";
  	   		getch();
  	   		break;
        }
        if (k.size()!=v){
          cout<<"\n Existe más de un componente en el grafo, por lo tanto es no-conexo."<<endl;
          cout<<"\n ****** NO EXISTE NI UN CIRCUITO NI UN RECORRIDO EULERIANO.\a *****";
          getch();
          break;
        } 
        impares=0;
        aislados=0;
        for(int i=0;i<v;++i) val[i]=0; // Se inicializan todas las valencias en 0
        
				for(int j=0;j<v;++j){
					for(int i=0;i<v;++i){
						val[j]+=e[i][j];
					}
					if (val[j]==0){
					  aislados++;
          }
					if (val[j]%2!=0){
						impares++;
					}
					//cout<<" val("<<j+1<<")="<<val[j]<<" impares="<<impares<<" aislados="<<aislados<<endl;
				}
				if (aislados>0){
				  cout<<"\n Existen "<<aislados<<" vértices aislados en el grafo, por lo tanto es no-conexo."<<endl;
				  cout<<"\n ****** NO EXISTE NI UN CIRCUITO NI UN RECORRIDO EULERIANO.\a *****";
        }
				else if ((impares==0&&aislados==0)||(impares==2&&aislados==0)){ // Si cumple con circuito o recorrido
				  if (impares==0&&aislados==0){ // Circuito
  				  cout<<"\n Todos los vértices son de grado PAR. \n\n ***** EXISTE UN CIRCUITO EULERIANO. *****"<<endl
  				      <<"\n El circuito euleriano podría ser: "<<endl<<endl;
  				  aux=av[0];
          }
          else if (impares==2&&aislados==0){ // Recorrido
            cout<<"\n Existen exactamente dos vértices de valencia IMPAR."<<endl
                <<"\n ***** EXISTE UN RECORRIDO EULERIANO *****"<<endl
                <<"\n El recorrido euleriano podría ser: "<<endl<<endl;
              // Se asigna un vértice de grado impar como auxiliar
  				  for(int j=0;j<v;++j){
  				    if(val[j]==1){ // Si encuentra un vértice de grado 1, se le asigna a aux
  				      aux = av[j]; // Auxiliar será el que recorra el grafo por vértice
  				      goto val1;
              }
              else if(val[j]%2!=0) aux=av[j];
            }
          }
          val1:
          vr.insert(aux);
          cout<<" "<<aux; // Se muestra el primer vértice del recorrido
				      
          //Circuito y recorrido
          while(allvisited==false){
            aux2=0;
            repite=0;
            cont=0;
            repitemas=0;
            //for(int i=0;i<inc.size();i++) inc[i]=0;
					  for(int i=0;i<q;i++){
    					if(aux==vi[i]&&visited[i]==false){ // si aux es el vértice inicial de una arista no visitada
    					  inc.push_back(vf[i]);
              }
    					else if(aux==vf[i]&&visited[i]==false){ // si aux es el vértice final de una arista no visitada
    					  inc.push_back(vi[i]);
              }
    				}
    				for(int i=0;i<inc.size();i++){
    				  for(int j=0;j<inc.size();j++){
    				    if(inc[i]==inc[j]) repite++;
              }
              if (repite>repitemas){
                repitemas=repite;
                aux2=inc[i];
              } 
            }
					  for(int l=0;l<q;l++){ // verifica si alguna de las aristas es un lazo de aux
					    if((aux==vi[l]&&aux==vf[l])&&visited[l]==false){ // si aux posee un lazo no visitado
					      cout<<" - "<<aux;
                val[aux-1]-=2; // se le restan 2 valencias del lazo
					      visited[l]=true;
              }
            }
					  for(int j=0;j<=q;j++){
              if((aux==vi[j]&&aux2==vf[j])&&(val[aux-1]==1&&visited[j]==false)){ // si aux es igual al vértice inicial de una arista no visitada
                val[aux-1]--; // su valencia queda en cero
                aux=aux2;
                val[aux-1]--;
                vr.insert(aux);
                cout<<" - "<<aux;
                visited[j]=true;
              }
              else if((aux==vi[j]&&aux2==vf[j])&&(val[aux-1]>1&&val[aux2-1]>1)&&(visited[j]==false&&vr.count(aux2)==0)){// si los vértices de la arista tienen valencia > 
                val[aux-1]--; // se le resta una valencia al vértice
                aux=aux2;
                cout<<" - "<<aux;
                val[aux-1]--;
                visited[j]=true;
              }
              
              else if((aux==vf[j]&&aux2==vi[j])&&(val[aux-1]==1&&visited[j]==false)){ // si aux es igual al vértice inicial de una arista no visitada
                val[aux-1]--; // su valencia queda en cero
                aux=aux2;
                val[aux-1]--;
                vr.insert(aux);
                cout<<" - "<<aux;
                visited[j]=true;
              }
              else if((aux==vf[j]&&aux2==vi[j])&&(val[aux-1]>1&&val[aux2-1]>1)&&(visited[j]==false&&vr.count(vi[j])==0)){
                val[aux-1]--; // se le resta una valencia al vértice
                aux=aux2;
                cout<<" - "<<aux;
                val[aux-1]--;
                visited[j]=true;
              }
            }
            int suma=0, grad=0;
            for(int i=0;i<q;++i) suma+=visited[i];
            for(int j=0;j<v;++j) grad+=val[j];
            if(suma==q&&grad==0) allvisited=true;
            //cout<<" suma="<<suma<<" grad="<<grad;
          }
          getch();
        }
				else {
	   		  if (impares==1) 
   		      cout<<"\n Sólo un vértice es de valencia impar. "<<endl;
					else if (impares>2) 
  		 		  cout<<"\n Existen más de dos vértices de grado impar."<<endl;
				  cout<<"\n ****** NO EXISTE NI UN CIRCUITO NI UN RECORRIDO EULERIANO.\a *****";
				}
				getch();
 				break;
 			
 			case 6: v=0, q=0; break;
				
			case 0: break;					
			
			default:
				cout<<" ERROR: INGRESE UNA OPCIÓN VÁLIDA\a";
				getch();
				break;
		}
	}while(op!=0);
}

int main(){
	setlocale(LC_CTYPE, "Spanish");
	system("color 00");
	AltEnter();
	char despedida[] = " Hasta luego... ¡Vuelva pronto!";
	
	grafo13();
	
	for(int i=0;despedida[i]!='\0';i++){
		cout<<despedida[i];
		Sleep(30); 
	}  
}
