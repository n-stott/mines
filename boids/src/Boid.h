#ifndef BOIDS_H
#define BOIDS_H

#include <Eigen/Dense>
#include <cmath>


class Boid {
public:
  Eigen::Vector3f position;
  Eigen::Vector3f vitesse;
  float taille;
  int id;
  static const int nbreId = 2;

/*
  Eigen::Vector3f vCohesion(std::vector<Boid>& voisins){
    int n = voisins.size();
    Eigen::Vector3f v (0,0,0);
    for(int k=0; k<n;k++){
      v = v + 1.0/n*voisins[k].position;
    }
    v= v - position;
    return 0.2*v;
  }*/
  
  Eigen::Vector3f vSeparation(std::vector<Boid>& voisins){
    int n = voisins.size();
    Eigen::Vector3f v (0,0,0);
    Eigen::Vector3f ecart (0,0,0);
    for(int k=0; k<n;k++){
      ecart = position-voisins[k].position;
      if(sqrt(ecart.dot(ecart))<1){
         v = v + 2*ecart;
      }
    }
    return v;
  }
  /*
  Eigen::Vector3f vAlignement(std::vector<Boid>& voisins){
    int n = voisins.size();
    Eigen::Vector3f v (0,0,0);
    for(int k=0; k<n;k++){
      v = v + 1.0/n*voisins[k].vitesse;
    }
    v= v - vitesse;
    return 0.2*v;
  }*/
  
  Eigen::Vector3f vPredateur(std::vector<Boid>& voisins){
    Eigen::Vector3f v (0,0,0);
    Eigen::Vector3f ecart (0,0,0);
    int n = voisins.size();
    float d;
    float dmin=15;
    Eigen::Vector3f ecartmin (0,0,0);
    
    for(int k=0; k<n;k++){
      ecart = voisins[k].position-position;
      d = sqrt(ecart.dot(ecart));
      if(d>0){
          /*
          if((id - voisins[k].id)%nbreId == nbreId-1){
             v=v+5*ecart;
          }
          if((id - voisins[k].id)%nbreId == 1){
             v=v-5*ecart;
          }*/
          if(id== 1 && voisins[k].id==2 & d<dmin){
             ecartmin = ecart;  
             dmin=d;
          }
          if(id== 2 && voisins[k].id==1){
             ecartmin = ecart;  
             dmin=d;
          }
      }
    }
    if(id==1){
        return 2*ecartmin;
    }
    else{
        return -3*ecartmin;
    }
  }
  
  /*Eigen::Vector3f vMurs(){
    Eigen::Vector3f v (0,0,0);
    for(int k=0;k<3;k++){
        if(position[k]>6){
          v[k]=v[k]-5;
        }
        if(position[k]<-6){
          v[k]=v[k]+5;
        }
    }
    return v;
    
  }
  */
  /*
  Eigen::Vector3f vTarget(Eigen::Vector3f target){
    Eigen::Vector3f v (0,0,0);
    v = target-position;
    float d = sqrt(v.dot(v));
    if(d>0){
      return 0.1*v;
    }
    else{
      return 0*v;
    }  
    //std::cout<<v.transpose() << std::endl;
  }
  */
  
  void maj(float dt, std::vector<Boid>& voisins, Eigen::Vector3f target){
      //vitesse = vAlignement(voisins) + vSeparation(voisins)+ vCohesion(voisins)+vTarget(target);
      //vitesse = vitesse + dt*(vAlignement(voisins) + vSeparation(voisins)+ vCohesion(voisins)+vPredateur(voisins)+vMurs());
      vitesse = vitesse + dt*(vSeparation(voisins)+vPredateur(voisins));
      position = position + dt * vitesse;
      int lim=6;
      for(int k=0; k<3;k++){
 
          if(position[k]<-lim){
            position[k]=-lim;
            vitesse[k]=-vitesse[k];
          }
          if(position[k]>lim){
            position[k]=lim;
            vitesse[k]=-vitesse[k];
          }

          if(vitesse[k]>50){
            vitesse[k]=50;
          }
      }
  }
  
	// Constructor
	Boid();
	
	Boid(Eigen::Vector3f pos, Eigen::Vector3f vit, float t, int i){
	  position=pos;
	  vitesse=vit;
	  taille=t;
	  id = i;
	}
	
	// Destructor
	~Boid();
	void draw();
};


class Essaim{
  public:
  std::vector<Boid> listeBoids;
  int nombre=0;
  
  void draw(){
    for(int k=0; k<nombre;k++){
      listeBoids[k].draw();
    }
    glColor3d(1,1,1);
    glBegin(GL_LINE_LOOP);
	  glVertex3f(-7,-7,7);
	  glVertex3f(7,-7,7);
	  glVertex3f(-7,-7,-7);
	  glVertex3f(7,-7,-7);
	  glEnd();
	  
    glBegin(GL_LINE_LOOP);
	  glVertex3f(-7,7,7);
	  glVertex3f(7,7,7);
	  glVertex3f(-7,7,-7);
	  glVertex3f(7,7,-7);
	  glEnd();
	
    glBegin(GL_LINE_LOOP);
	  glVertex3f(7,7,7);
	  glVertex3f(7,7,-7);
	  glVertex3f(7,-7,7);
	  glVertex3f(7,-7,-7);
	  glEnd();
	  	
    glBegin(GL_LINE_LOOP);
	  glVertex3f(-7,7,7);
	  glVertex3f(-7,7,-7);
	  glVertex3f(-7,-7,7);
	  glVertex3f(-7,-7,-7);
	  glEnd();
  }
  
  void ajouter(Boid& b){
     listeBoids.push_back(b);
     nombre+=1;
  }
  
  void maj(float dt, Eigen::Vector3f target){
    for(int k=0; k<nombre;k++){
      listeBoids[k].maj(dt, listeBoids, target);
    }
  }
  
  Essaim(){nombre=0;}
};



#endif  // BOIDS_LIB_SAMPLE_CLASS_H_
