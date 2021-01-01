#include <iostream>
#include <cmath>
using namespace std;
//g++ duales.cpp -o a && a.exe

class dual{
    public: 
    double a;
    double b;
    double c;
    dual(double x, double y, double z){
        a=x;
        b=y;
        c=z;
    }
    dual operator+(const dual& d){
        dual dr(a+d.a,b+d.b,c+d.c);
        return dr;
    }
    dual operator-(const dual& d){
        dual dr(a-d.a,b-d.b,c+d.c);
        return dr;
    }
    dual operator*(const dual& d){
    dual dr(a*d.a,b*d.a+a*d.b,a*d.c+b*d.b+c*d.a);
    return dr;
    }
    dual operator/(const dual& d){
        dual dr(0,0,0);
        if(d.a!=0){
            dr.a =a/d.a;
            dr.b=(d.a*b-d.b*a)/(d.a*d.a);
            dr.c=(d.a*c-d.c*a)/(d.a*d.a*d.a*d.a);
        }
        return dr;
    }

    dual operator^(double i){
    dual dr(pow(a,i),i*pow(a,i-1)*b,i*(i-1)*pow(a,i-2)*c);
    return dr;
    }

    string ToString(){
           return to_string(a) + sgn(b) + to_string(b)+"h"+ sgn(c) + to_string(c)+"k";
    }
    string sgn(double x){
        if (x>=0){
            return "+";
        }
        else{
            return "";
        }
    }
    double* ToArray(){
        static double arr[3]={a,b,c};
        return arr;
    }
};

dual sin(const dual &d){
    dual dr(sin(d.a),d.b*cos(d.a),-d.c*sin(d.a));
    return dr;
}

int main(){

    dual d(4,1,0); 
    dual p(4,1,1);
    cout<< d.ToString()<<endl;
    cout<< p.ToString()<<endl;
    cout<< (p+d).ToString()<<endl;  
    cout<< (p*d).ToString()<<endl;
    cout<< (p^0.5).ToString()<<endl;
    cout<< (p*p).ToString()<<endl;
    cout<< (sin(sin(p))).ToString()<<endl;
    return 0;

}