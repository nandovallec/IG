#include "revolutionobject.h"
#define PI 3.14159265f

_revolutionObject::_revolutionObject()
{

}


_vertex3f _revolutionObject::getPointsBetw(_vertex3f x, _vertex3f y, float t){
    float new_x = (1-t)*x.x + t* y.x;
    float new_y = (1-t)*x.y + t* y.y;
    float new_z = (1-t)*x.z + t* y.z;

    return _vertex3f(new_x, new_y, new_z);
}


void _revolutionObject::revolucionar(vector<_vertex3f> &Vertices, int revoluciones){
    vector<_vertex3f> cop = Vertices;
    Vertices.clear();
    //Vertices.resize((Vertices.size()-2)*(revoluciones));
    //cerr << "nuevo"<<Vertices.size()<<endl;

    float prog = 0;

    //cop[1].show_values();
    //cerr<<"first "<<"    "<< float(cop[1].x)*cos((45)*PI / 180)<<endl;
    //cop[0].show_values();

    Vertices.reserve((cop.size()-2)*revoluciones +2);
    Vertices.push_back(cop[0]);
    for(int i = 1; i < cop.size()-1; i++){
        prog = (float)360/revoluciones;
        float Size = sqrt(cop[i].x * cop[i].x+cop[i].z+cop[i].z);
        //cerr<<"metoooooo ";cop[i].show_values();cerr<<endl;
        for(int j = 0; j < revoluciones; j++){
            //cerr<<"aa"<<cop[i].x<<"     "<<float(cop[i].x)*cos((360-prog)*PI / 180)<<endl;

            Vertices.push_back(_vertex3f(Size*cos((prog)*PI / (float)180),cop[i].y,Size*sin((prog)*PI / (float)180)));
            //Vertices[i*revoluciones+j].show_values();
            //cerr<<i*revoluciones+j<<endl;
            prog += (float)(360)/(float)revoluciones;
        }
    }
    Vertices.push_back(cop[cop.size()-1]);
    //cerr<<"maamamamam"<<endl<<endl<<endl;
    //cerr<<Vertices.size()<<endl;
    //Vertices[Vertices.size()-1] = cop[cop.size()-1];

}



void _revolutionObject::connect(vector<_vertex3f> &Vertices, vector<_vertex3ui> & Triangles,int revoluciones){
    //cerr<<"aaaaaaaaaaaa"<<endl;
    //int index = 0;
    int count = 0;
    int act_lay = 1;
    //Triangles.resize(layers*2*revoluciones);
    //cerr<<"prop"<<layers*2*revoluciones<<endl;
    //cerr<<"mis rev   "<<revoluciones<<endl;

    for(int i = 0; i < revoluciones-1; i++)
        Triangles.push_back(_vertex3ui(i+1, 0, i+2));
    Triangles.push_back(_vertex3ui(revoluciones,0 ,1 ));

    for(int i = 1; i < Vertices.size()-(revoluciones)-1; i++){
        if(count == revoluciones){
            count = 0;
            act_lay++;
            //cerr<<"meem"<<Vertices.size()<<endl;
        }
        count++;
        //cerr<<revoluciones<<"dddd"<<act_lay<<endl;
        int r = rightVert(i, act_lay, revoluciones), d = downVert(i, revoluciones), dr = downRight(i, act_lay, revoluciones);
        //cerr << "connect "<< i <<"  "<< r<<"  "<<d<<endl;
        //cerr<< "Conecting:    "; Vertices[i].show_values();cerr<<"      ";Vertices[r].show_values();cerr<<"      ";Vertices[d].show_values();cerr<<"      "<<endl;
        //cerr<<"Conecto : "<<i<<"   "<<r<<"    "<<dr<<"                         y"<<i<<"     "<<d<<"      "<<dr<<endl;
        Triangles.push_back(_vertex3ui(i,r,dr));
        Triangles.push_back(_vertex3ui(d,i, dr));
        //index = index+2;

    }
    int last = Vertices.size()-1;
    Triangles.push_back(_vertex3ui(last,last-1, last-revoluciones));
    for(int i = 0; i < revoluciones-1; i++)
        Triangles.push_back(_vertex3ui(last-i-1, last, last-i-2 ));
}

int _revolutionObject::rightVert(int i, int layer, int rev){
    if (i+1 > (layer)*rev)
        return i+1-rev;
    return i+1;
}


int _revolutionObject::downVert(int i, int rev){
    return i+rev;
}

int _revolutionObject::downRight(int i, int layer, int rev){
    return rightVert(i+rev, layer+1, rev);
}

void _revolutionObject::revolucionarX(vector<_vertex3f> &Vertices, int revoluciones){
    vector<_vertex3f> cop = Vertices;
    Vertices.clear();
    //Vertices.resize((Vertices.size()-2)*(revoluciones));
    //cerr << "nuevo"<<Vertices.size()<<endl;

    float prog = 0;

    //cop[1].show_values();
    //cerr<<"first "<<"    "<< float(cop[1].x)*cos((45)*PI / 180)<<endl;
    //cop[0].show_values();

    Vertices.reserve((cop.size()-2)*revoluciones +2);
    Vertices.push_back(cop[0]);
    for(int i = 1; i < cop.size()-1; i++){
        float step = (float)360/revoluciones;
        prog = (float)360/revoluciones;
        float Size = sqrt(cop[i].y * cop[i].y+cop[i].z+cop[i].z);
        //cerr<<"metoooooo ";cop[i].show_values();cerr<<endl;
        for(int j = 0; j < revoluciones; j++){
            //cerr<<"aa"<<cop[i].x<<"     "<<float(cop[i].x)*cos((360-prog)*PI / 180)<<endl;

            // If we change sin and cos the triangles will be inside out
            Vertices.push_back(_vertex3f(cop[i].x, Size*sin((prog)*PI / (float)180),Size*cos((prog)*PI / (float)180)));
            //Vertices[i*revoluciones+j].show_values();
            //cerr<<i*revoluciones+j<<endl;
            prog = step * (j+2);
        }
    }
    Vertices.push_back(cop[cop.size()-1]);
    //cerr<<"maamamamam"<<endl<<endl<<endl;
    //cerr<<Vertices.size()<<endl;
    //Vertices[Vertices.size()-1] = cop[cop.size()-1];

}

void _revolutionObject::revolucionarZ(vector<_vertex3f> &Vertices, int revoluciones){
    vector<_vertex3f> cop = Vertices;
    Vertices.clear();
    //Vertices.resize((Vertices.size()-2)*(revoluciones));
    //cerr << "nuevo"<<Vertices.size()<<endl;

    float prog = 0;

    //cop[1].show_values();
    //cerr<<"first "<<"    "<< float(cop[1].x)*cos((45)*PI / 180)<<endl;
    //cop[0].show_values();

    Vertices.reserve((cop.size()-2)*revoluciones +2);
    Vertices.push_back(cop[0]);
    for(int i = 1; i < cop.size()-1; i++){
        float step = (float)360/revoluciones;
        prog = (float)360/revoluciones;
        float Size = sqrt(cop[i].x * cop[i].x+cop[i].y+cop[i].y);
        //cerr<<"metoooooo ";cop[i].show_values();cerr<<endl;
        for(int j = 0; j < revoluciones; j++){
            //cerr<<"aa"<<cop[i].x<<"     "<<float(cop[i].x)*cos((360-prog)*PI / 180)<<endl;

            // If we change sin and cos the triangles will be inside out
            Vertices.push_back(_vertex3f(Size*sin((prog)*PI / (float)180),Size*cos((prog)*PI / (float)180), cop[i].z));
            //Vertices[i*revoluciones+j].show_values();
            //cerr<<i*revoluciones+j<<endl;
            prog = step * (j+2);
        }
    }
    Vertices.push_back(cop[cop.size()-1]);
    //cerr<<"maamamamam"<<endl<<endl<<endl;
    //cerr<<Vertices.size()<<endl;
    //Vertices[Vertices.size()-1] = cop[cop.size()-1];

}
