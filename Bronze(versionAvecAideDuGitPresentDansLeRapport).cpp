#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;
/***** Var global *****/

/**********************/
/*******fonction*******/
void addCP(int nextCheckpointX, int nextCheckpointY, vector<vector<int>>* vectorCP, vector<int>* actualCP,
           bool* listeFini,int* lapSize, int* lap);
void vitesseAI(int nextCheckpointAngle, int nextCheckpointDist, int* vitesse);

/**********************/

void addCP(int nextCheckpointX, int nextCheckpointY, vector<vector<int>>* vectorCP, vector<int>* actualCP, 
           bool* listeFini,int* lapSize, int* lap)
{
    if(vectorCP->empty())
    {
        vectorCP->push_back(*actualCP); 
    }else 
    {
        if (nextCheckpointX != (vectorCP->back().front()) && nextCheckpointY != (vectorCP->back().back())) 
        {
            
            for (auto cp = vectorCP->begin(); cp != vectorCP->end(); ++cp)
            {
               if ( (*(cp->begin())  == nextCheckpointX) &&  (*(--cp->end()) == nextCheckpointY ))
               {
                   *listeFini = true;
                   *lapSize = vectorCP->size();
                   *lap = 2;
            }   }
            if (! *listeFini)
            {
                vectorCP->push_back(*actualCP);
            }
        }
    }
}

void vitesseAI(int nextCheckpointAngle, int nextCheckpointDist, int* vitesse)
{
    if( nextCheckpointAngle >= 1 || nextCheckpointAngle <= -1)
    {
        if( nextCheckpointAngle >= 90 || nextCheckpointAngle <= -90 )
        {
            *vitesse = 0;
        }else if( nextCheckpointDist < 2400 ) 
        {
            *vitesse *= ((90 - abs(nextCheckpointAngle)) / (float)90);
        }      
    }else
    {
        if( nextCheckpointDist < 2400 ) *vitesse *= nextCheckpointDist / 2400;      
    }
}

int main()
{
    bool boost = true;
    vector<vector<int>>* vectorCP = new vector<vector<int>>();
    vector<int>* actualCP = new vector<int>(2);
    bool listeFini = false;
    int lap = 1;
    int lapSize;
    float pi = 3.14159265;
    // game loop
    while (1) {
        
        
        
        int dirX, dirY, vitesse, dirXdesi, dirYdesi;
        int distNextCheckX, distNextCheckY;
        
        int x;
        int y;
        int nextCheckpointX; // x position of the next check point
        int nextCheckpointY; // y position of the next check point
        int nextCheckpointDist; // distance to the next checkpoint
        int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint
        cin >> x >> y >> nextCheckpointX >> nextCheckpointY >> nextCheckpointDist >> nextCheckpointAngle; cin.ignore();
        
        int opponentX;
        int opponentY;
        cin >> opponentX >> opponentY; cin.ignore();

       // actualCP = new vector<int>();      
        actualCP->at(0) = nextCheckpointX;
        actualCP->at(1) = nextCheckpointY;
        if(!listeFini)
        {
        addCP(nextCheckpointX, nextCheckpointY, vectorCP, actualCP, &listeFini, &lapSize, &lap); 
        }
        
        vitesse = 100;
       
        
        if( nextCheckpointAngle <= -1 || nextCheckpointAngle >= 1)
        {
            
            vector<float>* dirDesi = new vector<float>(2);
            vector<float>* dir = new vector<float>(2);
            
            dirDesi->at(0) = (nextCheckpointX - x);
            dirDesi->at(1) = (nextCheckpointY - y);
            float sqrtVal = dirDesi->at(0)*dirDesi->at(0) + dirDesi->at(1) * dirDesi->at(1);
            dirDesi->at(0) = dirDesi->at(0) * (1 / std::sqrt(sqrtVal));
            dirDesi->at(1) = dirDesi->at(1) * (1 / std::sqrt(sqrtVal));
            
            dir->at(0) = ((dirDesi->at(0) * cos(-nextCheckpointAngle * pi / 180) ) - (dirDesi->at(1) * sin(-nextCheckpointAngle * pi / 180) ));    
            dir->at(1) = ((dirDesi->at(1) * cos(-nextCheckpointAngle * pi / 180) ) - (dirDesi->at(0) * sin(-nextCheckpointAngle * pi / 180) ));    
            sqrtVal = dir->at(0)*dir->at(0) + dir->at(1) * dir->at(1);
            dir->at(0) = dir->at(0) / std::sqrt(sqrtVal);
            dir->at(1) = dir->at(1) / std::sqrt(sqrtVal);
            
            dirDesi->at(0) = (dirDesi->at(0) - dir->at(0));
            dirDesi->at(1) = (dirDesi->at(1) - dir->at(1));
            sqrtVal = dirDesi->at(0)*dirDesi->at(0) + dirDesi->at(1) * dirDesi->at(1);
            dirDesi->at(0) = (dirDesi->at(0) * (1 / std::sqrt(sqrtVal)))*100;
            dirDesi->at(1) = (dirDesi->at(1) * (1 / std::sqrt(sqrtVal)))*100;
                        
            dirX = nextCheckpointX + dirDesi->at(0);
            dirY = nextCheckpointY + dirDesi->at(1);
            
        }else
        {
         dirX = nextCheckpointX;
         dirY = nextCheckpointY;
        }
        a
        vitesseAI(nextCheckpointAngle, nextCheckpointDist, &vitesse);
       
       
        cout << dirX << " " << dirY << " ";
        if( boost && lap >= 2 && nextCheckpointDist > 5000 && nextCheckpointAngle < 1 && nextCheckpointAngle > -1 )
        {
            cout << "BOOST" << endl;
            boost = false;
        }
        else
        {
            cout << vitesse << endl;
        } 

            int i = 0;
            for (auto checkpoint = vectorCP->begin(); checkpoint != vectorCP->end(); ++checkpoint)
            {
                cerr << "DEBUG: ARRAY[" << i << "], X=" << *(checkpoint->begin()) << ", Y=" << *(--checkpoint->end()) << endl;
                i++;
            }
        cerr << "vitesse : " << vitesse << endl;
        cerr << "dirX : " << dirX << " dirY : " << dirY << endl;
        cerr << "nextCheckpointDist : " << nextCheckpointDist << endl;
        cerr << "boost : " << boost << endl;
        cerr << "lap : " << lap << " lapSize : " << nextCheckpointAngle << endl;
        cerr << "distNextCheckX : " << distNextCheckX << " distNextCheckY : " << distNextCheckY << endl;
    }

}