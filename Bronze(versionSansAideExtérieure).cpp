#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
/***** Var global *****/

/**********************/
/*******fonction*******/
void addCP(int nextCheckpointX, int nextCheckpointY, vector<vector<int>>* vectorCP, vector<int>* actualCP,
           bool* listeFini,int* lapSize, int* lap);
void vitesseAI(int nextCheckpointAngle, int nextCheckpointDist, int* vitesse);
void mouvementAI(bool listeFini, int nextCheckpointX, int nextCheckpointY, int* dirX, int* dirY, 
                 int* distNextCheckX, int* distNextCheckY, int x, int y, vector<vector<int>>* vectorCP,
                 int lapSize, int* lap, int nextCheckpointDist);
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
    if( nextCheckpointDist < 2400 ) 
    {
        if( nextCheckpointAngle > 90 || nextCheckpointAngle < -90 )
        {
            *vitesse = 0;
        }else
        { 
            *vitesse *= ((90 - abs(nextCheckpointAngle)) / 90) ;
            //- abs(nextCheckpointAngle);
           // if( *vitesse < 30 ) *vitesse = 10;
        }      
    }
}

void mouvementAI(bool listeFini, int nextCheckpointX, int nextCheckpointY, int* dirX, int* dirY, 
                 int* distNextCheckX, int* distNextCheckY, int x, int y, vector<vector<int>>* vectorCP,
                 int lapSize, int* lap, int nextCheckpointDist)
{
    if(! listeFini )
    {
        *dirX = nextCheckpointX;
        *dirY = nextCheckpointY;

    }else if( nextCheckpointDist < 4000 )
    {
        *dirX = nextCheckpointX;
        *dirY = nextCheckpointY;
    }else
    {
      for(int i = 0; i<lapSize; i++)
        {
            if( nextCheckpointX == vectorCP->at(i).front() && nextCheckpointY == vectorCP->at(i).back() )
            {
                cerr << vectorCP->back().front() << endl;
                if(vectorCP->back().front() != nextCheckpointX && vectorCP->back().back() != nextCheckpointY)
                {
                    *distNextCheckX = vectorCP->at(i+1).front();
                    *distNextCheckY = vectorCP->at(i+1).back();
                }else
                {
                    *distNextCheckX = vectorCP->front().front();
                    *distNextCheckY = vectorCP->front().back();
                    *lap = 3;
                    i = lapSize;

                }
            }
        }
        if((nextCheckpointX - x ) > 0 && (nextCheckpointY - y ) > 0)
        {
            if(( nextCheckpointX - *distNextCheckX ) > 0 && ( nextCheckpointY - *distNextCheckY ) > 0)
            {
                *dirX = nextCheckpointX - 800;
                *dirY = nextCheckpointY - 800;
                cerr << "1.1" << endl;
            }else if(( nextCheckpointX - *distNextCheckX ) < 0 && ( nextCheckpointY - *distNextCheckY ) > 0)
            {
                *dirX = nextCheckpointX - 950;
                *dirY = nextCheckpointY - 450;
                cerr << "1.2" << endl;
            }else if(( nextCheckpointX - *distNextCheckX ) > 0 && ( nextCheckpointY - *distNextCheckY ) < 0)
            {
                *dirX = nextCheckpointX + 900;
                *dirY = nextCheckpointY - 450;
                cerr << "1.3" << endl;
            }else{
                *dirX = nextCheckpointX - 800;
                *dirY = nextCheckpointY - 800;
                cerr << "1.4" << endl;
            }  
        }else if((nextCheckpointX - x ) < 0 && (nextCheckpointY - y ) > 0)
        {
            if((nextCheckpointX - *distNextCheckX ) > 0 && (nextCheckpointY - *distNextCheckY ) > 0)
            {
                *dirX = nextCheckpointX + 900;
                *dirY = nextCheckpointY - 450;
                cerr << "2.1" << endl;
            }else if((nextCheckpointX - *distNextCheckX ) < 0 && (nextCheckpointY - *distNextCheckY ) > 0)
            {
                *dirX = nextCheckpointX + 800;
                *dirY = nextCheckpointY - 800;
                cerr << "2.2" << endl;
            }else if((nextCheckpointX - *distNextCheckX ) > 0 && (nextCheckpointY - *distNextCheckY ) < 0)
            {
                *dirX = nextCheckpointX + 800;
                *dirY = nextCheckpointY + 800;
                cerr << "2.3" << endl;
            }else{
                *dirX = nextCheckpointX - 900;
                *dirY = nextCheckpointY - 450;
                cerr << "2.4" << endl;
            }
        }else if((nextCheckpointX - x ) > 0 && (nextCheckpointY - y ) < 0)
        {
            if((nextCheckpointX - *distNextCheckX ) > 0 && (nextCheckpointY - *distNextCheckY ) > 0)
            {
                *dirX = nextCheckpointX + 450;
                *dirY = nextCheckpointY + 900;
                cerr << "3.1" << endl;
            }else if((nextCheckpointX - *distNextCheckX ) < 0 && (nextCheckpointY - *distNextCheckY ) > 0)
            {
                *dirX = nextCheckpointX - 800;
                *dirY = nextCheckpointY + 800;
                cerr << "3.2" << endl;
            }else if((nextCheckpointX - *distNextCheckX ) > 0 && (nextCheckpointY - *distNextCheckY ) < 0)
            {
                *dirX = nextCheckpointX - 800;
                *dirY = nextCheckpointY + 800;
                cerr << "3.3" << endl;
            }else{
                *dirX = nextCheckpointX - 900;
                *dirY = nextCheckpointY - 450;
                cerr << "3.4" << endl;
            }
        }else{
            if((nextCheckpointX - *distNextCheckX ) > 0 && (nextCheckpointY - *distNextCheckY ) > 0)
            {
                *dirX = nextCheckpointX + 800 ;
                *dirY = nextCheckpointY + 800;
                cerr << "4.1" << endl;
            }else if((nextCheckpointX - *distNextCheckX ) < 0 && (nextCheckpointY - *distNextCheckY ) > 0)
            {
                *dirX = nextCheckpointX - 450;
                *dirY = nextCheckpointY + 900;
                cerr << "4.2" << endl;
            }else if((nextCheckpointX - *distNextCheckX ) > 0 && (nextCheckpointY - *distNextCheckY ) < 0)
            {
                *dirX = nextCheckpointX + 450;
                *dirY = nextCheckpointY - 900;
                cerr << "4.3" << endl;
            }else{
                *dirX = nextCheckpointX + 800;
                *dirY = nextCheckpointY + 800;
                cerr << "4.4" << endl;
            }            
        }
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
    // game loop
    while (1) {
        
        
        
        int dirX, dirY, vitesse;
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
        mouvementAI(listeFini, nextCheckpointX, nextCheckpointY, &dirX, &dirY, &distNextCheckX, 
                   &distNextCheckY, x, y, vectorCP, lapSize, &lap , nextCheckpointDist);
        //dirX = nextCheckpointX;
        //dirY = nextCheckpointY;
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
        cerr << "lap : " << lap << " lapSize : " << lapSize << endl;
        cerr << "distNextCheckX : " << distNextCheckX << " distNextCheckY : " << distNextCheckY << endl;
    }

}