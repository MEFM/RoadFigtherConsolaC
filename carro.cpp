#include <windows.h>  
  #include <iostream>  
  #include <thread>  
  
using namespace std;  
    
    //Funcion que me permite mover posicion en la pantalla
  void gotoXY(int x, int y)  
  {  
   COORD coord;  
   coord.X = x;  
   coord.Y = y;  
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);  
  }  
    
  int matrix[8][16]; //defines our game screen  
  
  void Dibujar_Puntos(int x,int y){
  	
  	if(y<16 && x<8){
  		matrix[x][y]=1;
	  }
  } 
  
  void Limpiar_Tablero(){
  	for(int i=0;i<8;i++){
  		for(int j=0;j<16;j++){
  			matrix[i][j]=0;
		  }
	  }
  }
  
  
  class Carro{
  	public:
  		int posx;
  		int posy;

	Carro(){
		posx=1;
		posy=13;
	}  		
	
	void Dibujar_carro(){
		Dibujar_Puntos(posx,posy);
		Dibujar_Puntos(posx+1,posy);
		Dibujar_Puntos(posx+2,posy);
		Dibujar_Puntos(posx+1,posy+1);
		Dibujar_Puntos(posx,posy+2);
		Dibujar_Puntos(posx+1,posy+2);
		Dibujar_Puntos(posx+2,posy+2);
		
	}
	
	void Mover_Izquierda(){
		posx=1;
	}
	void mover_Derecha(){
		posx=4;
	}
  
  };
  
  class Enemigo{
  	public:
  		int posx;
  		int posy;
  	Enemigo(){
  		posx=5;
  		posy=-3;
	  }
	  
	  void aparecer(){
	  	if(posy==16){  
			int randomNo=rand()%2;  
    		if(randomNo==0){  
     			posx=2;  
    		}  
    		else {  
     		 posx=5;  
   			}  
  		 posy=-3;  
    	} 
	  }
	  
	  void draw(){  
	    Dibujar_Puntos(posx,posy);  
    	Dibujar_Puntos(posx-1,posy+1);  
    	Dibujar_Puntos(posx+1,posy+1);  
    	Dibujar_Puntos(posx,posy+1);  
    	Dibujar_Puntos(posx,posy+2);  
    	Dibujar_Puntos(posx-1,posy+3);  
    	Dibujar_Puntos(posx+1,posy+3);  
    	Dibujar_Puntos(posx,posy+3); 
  		}
		  	  
  		void move(){  
    		posy++;  
  		} 
  
};	

  	void myListener(Carro *c){  
    	while(1){  
        	if (GetAsyncKeyState(VK_LEFT) & (0x8000 != 0)){  
            	c->Mover_Izquierda();  
          	}  
        	else if (GetAsyncKeyState(VK_RIGHT) & (0x8000 != 0)){  
            	c->mover_Derecha();  
         	}	  
  		}  
	 }  
  
  /*
  if(chocar == true)
	{
	perder
}
  */
  int chocar(){
  	cout<<"Que triste hermano";
  	return 0;
  }
  void Iniciar(){
  	Carro micarro=Carro();
  	Enemigo ene=Enemigo();
  	
  	thread myHilo(myListener,&micarro);
  	
  	bool correr=true;
	bool terminar = true;
  	
  	while(correr){
  		Limpiar_Tablero();
  		ene.aparecer();
  		ene.draw();
  		ene.move();
  		micarro.Dibujar_carro();
	  
       for(int j=0;j<16;j++){  
        	for(int i=0;i<8;i++){  
          	   if(i==0 | i==7){
          	   		gotoXY(i,j);
          	   		//cout<<"0"; 
				 }
               else if(matrix[i][j]==1){  
             		 gotoXY(i,j);  
             		 std::cout<<"0";  
             		 cout << "                 Enemigo" <<ene.posx << " " << ene.posy<<"		Carro"<<micarro.posx<<" "<<micarro.posy;
             			if(((ene.posx == 5 && micarro.posx == 4)&&(ene.posy == 14 && micarro.posy == 13))){
             			Limpiar_Tablero();
						 	cout<<"Me chocaron";
							correr = false;
						 	
						 }else if(((ene.posx == 2 && micarro.posx == 1)&&(ene.posy == 14 && micarro.posy == 13))){
						 	cout<<"Ya termino esto";
						 	correr = false;
						
						 }
             		
           	   }  
                else {  
                 gotoXY(i,j);  
                  cout<<" ";  
            	}  
            }  
       }  
    
      Sleep(50);  
   } 
  
  	myHilo.detach();
  }
  
  int main(){
  	Iniciar();
  	
  	cout<<"Se termino esta mierda"<<endl;
  	return 0;
  }
  

    
  

