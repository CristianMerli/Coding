#include <iostream>
using namespace std;


int main(){
  int a[3]={100,200,300};
  int b[3]={400,500,600};
  cout << endl;
  for (int i=0; i<sizeof(a)/4; ++i) cout << "Value a[" << i << "] = " << a[i] << endl;
  cout << endl;
  for (int i=0; i<sizeof(b)/4; ++i) cout << "Value b[" << i << "] = " << b[i] << endl;
  cout << endl;
  cout << "Address of a: " << (long)a << endl;
  cout << "Address of b: " << (long)b << endl;
  cout << endl;
  for (int i=0; i<7; ++i) cout << "Value a[" << i << "]: " << a[i] << endl;
}
