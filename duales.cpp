#include <iostream>
#include <cmath>
using std::cout;
using std::string;
using std::to_string;
using std::endl;
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

    dual(double x){
        a=x;
        b=1;
        c=0;
    }

    dual operator+(const dual& d){
        dual dr(a+d.a,b+d.b,c+d.c);
        return dr;
    }
    dual operator+(double d){
        dual dr(a+d,b,c);
        return dr;
    }
    dual operator-(const dual& d){
        dual dr(a-d.a,b-d.b,c+d.c);
        return dr;
    }
    dual operator-(double d){
        dual dr(a-d,b,c);
        return dr;
    }
    dual operator*(double d){
    dual dr(d*a,d*b,d*c);
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

    dual operator/(double d){
        dual dr(0,0,0);
        if(d!=0){
            dr.a =a/d;
            dr.b=b/d;
            dr.c=c/d;
        }
        return dr;
    }
    void operator=(const dual &d){
        a=d.a;
        b=d.b;
        c=d.c;
    }
    void operator=(double d){
        a=d;
        b=1;
        c=0;
    }

    bool operator==(const dual &d){
        return (a==d.a & b==d.b & c==d.c);
    }
    bool operator!=(const dual &d){
        return !(a==d.a & b==d.b & c==d.c);
    }

    dual intexp(const dual &d){
    dual dr(exp(d.a),d.b*exp(d.a),exp(d.a)*d.b*d.b+exp(d.a)*d.c);
    return dr;
    }

    dual intln(const dual &d){
    if(d.a>0){
    dual dr(log(d.a),d.b/d.a,-d.b*d.b/(d.a*d.a)+d.c/d.a);
    return dr;
    }
    else{
    dual dr(0,0,0);
    return dr;
    }
    }

    dual operator^(double d){
    dual dr(pow(a,d),d*pow(a,d-1)*b,(d)*(d-1)*pow(a,d-2)*b*b+d*pow(a,d-1)*c);
    return dr;
    }

    dual operator^(const dual &d){
    dual buf(a,b,c);
    dual dr = intexp(intln(buf)*d);
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

class duvec{
    public:
    dual *v;
    int s;
    duvec(dual vi[],int size){
        s = size;
        for(int i =0 ;i<size;i++){
            v[i]=vi[i];
        }
    }

    duvec operator+(const duvec &r){
        if(s==r.s){
            dual *b;
            for(int i =0 ;i<s;i++){
            b[i]= v[i] + r.v[i];
            }
            return duvec(b,s);
        }
        else{
            return duvec(0,1);
        }
    }

    duvec ih(){
        dual b[3] = {dual(0,1,0),dual(0),dual(0)};
        return duvec(b,3);
    }

    duvec jh(){
        dual b[3] = {dual(0),dual(0,1,0),dual(0)};
        return duvec(b,3);
    }

    duvec kh(){
        dual b[3] = {dual(0),dual(0),dual(0,1,0)};
        return duvec(b,3);
    }

    void rep(){
        string b ="[";
        for(int i =0 ;i<s;i++){
            if(i<s-1){
            b+=v[i].ToString()+",";
            }
            else{
              b+=v[i].ToString()+"]";  
            }
    }
    }
};

dual operator+(double d, const dual &r){
        dual dr(r.a+d,r.b,r.c);
        return dr;
}
dual operator-(double d, const dual &r){
        dual dr(d-r.a,-r.b,-r.c);
        return dr;
}

dual operator-(const dual &r){
        dual dr(-r.a,-r.b,-r.c);
        return dr;
}


dual sin(const dual &d){
    dual dr(sin(d.a),d.b*cos(d.a),-sin(d.a)*d.b*d.b+cos(d.a)*d.c);
    return dr;
}

dual cos(const dual &d){
    dual dr(cos(d.a),-d.b*sin(d.a),-cos(d.a)*d.b*d.b-sin(d.a)*d.c);
    return dr;
}

dual exp(const dual &d){
    dual dr(exp(d.a),d.b*exp(d.a),exp(d.a)*d.b*d.b+exp(d.a)*d.c);
    return dr;
}

dual ln(const dual &d){
    if(d.a>0){
    dual dr(log(d.a),d.b/d.a,-d.b*d.b/(d.a*d.a)+d.c/d.a);
    return dr;
    }
    else{
    dual dr(0,0,0);
    return dr;
    }
}

dual tan(const dual &d){
    dual dr = sin(d)/cos(d);
    return dr;
}

int main(){

    dual d = 0.2;
    dual p = 4;
    dual q = -1;
    dual v1[3] = {p,d,q};
    dual v2[3] = {q,d,p};
    duvec av(v1,3);
    duvec bv(v2,3);
    cout<< d.ToString()<<endl;
    cout<< p.ToString()<<endl;
    cout<< (1-d).ToString()<<endl;  
    cout<< (-d).ToString()<<endl; 
    cout<< (p^0.5).ToString()<<endl;
    cout<< (sin(sin(p))).ToString()<<endl;
    cout<< (p^2).ToString()<<endl;
    cout<< (exp(exp(d))).ToString()<<endl;
    cout<< (p^cos(p)).ToString()<<endl;
    cout<< (0-d).ToString()<<endl;
    cout<< (q^3).ToString()<<endl;
    return 0;
}
