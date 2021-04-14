#include <iostream>
#include <cmath>
#include <vector>
#include <bits/stdc++.h> 
using std::cout;
using std::string;
using std::to_string;
using std::endl;
using std::vector;
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
        b=0;
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
  public:
  vector<dual> v;
  duvec(vector<dual> t){
      v=t;
  }
  duvec(dual t[], int size){
      for(int i=0;i<size;i++){
          v.push_back(t[i]);
      }
  }
  duvec(std::initializer_list<dual> t){
      v = vector<dual>(t);
  }
  duvec operator+(const duvec &d){
        int s;
        if (d.v.size()<=v.size()){
          s = d.v.size();  
        }
        else{
            s = v.size();
        }
        
        vector<dual> buf;
        for(int i =0;i<s;i++){
            buf.push_back(v[i]+d.v[i]);
        }
        return duvec(buf);
    }

    duvec operator-(const duvec &d){
        int s;
        if (d.v.size()<=v.size()){
          s = d.v.size();  
        }
        else{
            s = v.size();
        }
        
        vector<dual> buf;
        for(int i =0;i<s;i++){
            buf.push_back(v[i]-d.v[i]);
        }
        return duvec(buf);
    }
    void  operator=(std::initializer_list<dual> t){
        v = vector<dual>(t);
    }
    void  operator=(std::initializer_list<double> t){
         vector<double> dbuf = vector<double>(t);
         for (double d: dbuf){
             v.push_back(dual(d));
         }
    }
    string ToString(){
           string s = "[";
           for(int i =0;i<v.size();i++ ){               
            if(i==v.size()-1){
            s+= v[i].ToString()+"]"; 
            }  
            else{
            s+= v[i].ToString()+","; 
            }    
        }
        return s;
    }
    string RealPart(){
           string s = "{";
           for(int i =0;i<v.size();i++ ){               
            if(i==v.size()-1){
            s+= to_string(v[i].a) + "}"; 
            }  
            else{
            s+= to_string(v[i].a) + ","; 
            }    
        }
        return s;
    }
    dual operator[](const unsigned int i){
        if (i< v.size()){
            return v[i];
        }
        else{
            return dual(0);
        }
    }
    void add (dual d){
        v.push_back(d);
    }

};


class dumat{
public:
int n,m;
vector<dual> mat;

template <size_t rows, size_t cols>
dumat(dual (&array)[rows][cols])
{
    n = rows;
    m = cols;
for (int i = 0; i < rows; ++i)
    {     
        for (int j = 0; j < cols; ++j){
            mat.push_back(array[j][i]);
        }
    }
}

template <size_t rows, size_t cols>
dumat(double (&array)[rows][cols],char part)
{
    n = rows;
    m = cols;
for (int i = 0; i < rows; ++i)
    {       
        for (int j = 0; j < cols; ++j){
            switch (part){
                case 'r':
                mat.push_back(dual(array[j][i],0,0));
                break;
                
                case 'h':
                mat.push_back(dual(0,array[j][i],0));
                break;

                case 'k':
                mat.push_back(dual(0,0,array[j][i]));
                break;
            }         
        }
    }
}

dual element(int i,int j){
    if(j*n+i < n*m){
        return mat[j*n+i];
    }
    else{
        return dual(0);
    }
}

string Show(){
    for (int i =0;i<n;i++){
        for (int j =0;j<m;j++){
        cout<<mat[j*n+i].ToString() + ' ';
        } 
        cout<<endl;
    }          
}

string ShowReal(){
    for (int i =0;i<n;i++){
        for (int j =0;j<m;j++){
        cout<<to_string(mat[j*n+i].a) + ' ';
        } 
        cout<<endl;
    }          
}



};


duvec uh(unsigned int id){
        vector<dual> buf;
        for(int i =0;i<id;i++){
            if(i<id-1){
                buf.push_back(dual(0));
            }
            else{
                buf.push_back(dual(0,1,0));
            }         
        }
    return duvec(buf);
}

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

duvec gradient(std::function<dual(duvec)> function, duvec in){
    duvec  g = duvec({});
    for (dual d : in.v){
        if(d.b || d.c !=0){
        d.b = 0;
        d.c = 0;
        }
    }
    for (int i =1;i<=in.v.size();i++){
        dual buf = function(in+uh(i)).b;
        g.add(buf);
    }
    return g;
}

dual sphere(duvec dv){
dual x = dv[0];
dual y = dv[1];
dual z = dv[2];

return (x^2) + (y^2)+(z^2);
}

int main(){

  dual A1 = dual(-1.1,1.0,0.0);
  dual B1 = dual(-1.1,0.0,0.0);
  dual A2 = dual(-1.0,0.0,0.0);
  dual B2 = dual(3.0,0.0,0.0);
  dual A3 = 2.0;
  dual B3 = 0.0;
  dual A4 = dual(0.0,1.0,2.0);
  dual B4 = dual(1.1,2.2,3.3);
  dual xd = dual(1.1,1.0,0.0);
  dual rd = 0.0;

  double exmat[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
  dumat t = dumat(exmat,'r');

  duvec v1 = {2,2,2}; 

  duvec g = gradient(sphere, v1);
  
  cout<< (A1^B1).ToString()<<endl; //deberia dar nans
  cout<< (A2^B2).ToString()<<endl; //deberia dar -1
  cout<< (A3^2).ToString()<<endl; //en mi opinion deberia dar 1, pero eso
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
  cout<< g.RealPart() <<endl;
    cout<< endl;
   t.ShowReal();
   cout<< endl;
   cout<<t.element(0,1).ToString();
    return 0;
}
