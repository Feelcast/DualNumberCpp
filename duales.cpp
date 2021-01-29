#include <iostream>
#include <cmath>
#include <vector>
using std::cout;
using std::string;
using std::to_string;
using std::endl;
//copiar y pegar en terminal:  g++ duales.cpp -o a && a.exe

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
      dual dr(log(d.a),d.b/d.a,-(d.b*d.b)/(d.a*d.a)+d.c/d.a);
      return dr;
    }
    else{
      dual dr(NAN,NAN,NAN);
      return dr;
    }
    }

    dual operator^(double d){
    dual dr(pow(a,d),d*pow(a,d-1)*b,(d)*(d-1)*pow(a,d-2)*b*b+d*pow(a,d-1)*c);
    return dr;
    }

   dual operator^(const dual &d){
    if(d.b == 0 && d.c == 0){
      double r =d.a;
      dual dr(pow(a,r),r*pow(a,r-1)*b,(r)*(r-1)*pow(a,r-2)*b*b+r*pow(a,r-1)*c);
      return dr;
    }
    else{
      if(a==0){
        dual dr(0,0,0);
      return dr;
      }
      else{
    dual buf(a,b,c);
    dual dr = intexp(intln(buf)*d);
    return dr;
      }
    }
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
    dual dr(NAN,NAN,NAN);
    return dr;
    }
}

dual tan(const dual &d){
    dual dr = sin(d)/cos(d);
    return dr;
}

int main(){

     dual A1 = dual(-1.1,1.0,0.0);
  dual B1 = dual(-1.1,0.0,0.0);
  dual A2 = dual(-1.0,0.0,0.0);
  dual B2 = dual(3.0,0.0,0.0);
  dual A3 = 1.0;
  dual B3 = 0.0;
  dual A4 = dual(0.0,1.0,2.0);
  dual B4 = dual(1.1,2.2,3.3);
  dual xd = dual(1.1,1.0,0.0);
  dual rd = 0.0;
  
  
  cout<< (A1^B1).ToString()<<endl; //deberia dar nans
  cout<< (A2^B2).ToString()<<endl; //deberia dar -1
  cout<< (A3).ToString()<<endl; //en mi opinion deberia dar 1, pero eso
  //depende de como se haya definido. Siempre ten en mente algo como la
  //extension de los reales a los complejos, el complejo 1 es 1 + 0i
  //solo se usa la parte h=1 cuando se desea derivar respecto a esa variable,
  //en general deberia ser arbitraria

  cout<< (B3).ToString()<<endl; // lo mismo que arriba
  cout<< (A4^B4).ToString()<<endl; //deberia dar 0+nanh+nank

  A4 = dual(0.0,0.0,0.0);
  B4 = dual(1.1,2.2,3.3);
  cout<< (A4^B4).ToString()<<endl; //deberia dar 0+0h+0k
  rd = sin(xd)^exp(cos(xd^2));

  cout<< (rd).ToString()<<endl; //debe dar 0.848793+0.901325h-3.186792k
    return 0;
}
