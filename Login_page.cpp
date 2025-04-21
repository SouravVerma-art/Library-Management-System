#include <iostream> 
#include <fstream>
using namespace std ; 

class temp {
    string userName,Email,Password;
    string searchName,searchaEmail,searchPassword;
    fstream file;
    public:
    void login();
    void signUp();
    void forgot();
}obj;

int main() {
    char choice;
    cout<<"\n1 - Login";
    cout<<"\n2 - Sign_Up";
    cout<<"\n3 - Forgot Password";
    cout<<"\n4 - Exit";
    cout<< "\nEnter Your Choice : " ;  
    cin>>choice;

    switch(choice){
        case '1':
         cin.ignore(); // Clears the Buffer
         obj.login();
         break;
        case '2':
         cin.ignore();
         obj.signUp();
         break;
        case '3':
         cin.ignore();
         obj.forgot();
         break;
        case '4':
         return 0 ;
         break;
        default :
             cout<<"Invalid Selection !" << '\n' ;
         break;
    }
}
void temp :: signUp(){
    cout<< "\nEnter User Name : " ;
    getline(cin, userName);
    cout<< "\nEnter Email : " ;
    getline(cin, Email);
    cout<< "\nEnter Password : " ;
    getline(cin, Password);

    file.open("LoginData.txt", ios :: out | ios :: app);
    file<<userName<<"*"<<Email<<"*"<<Password<<endl;
    file.close();
    cout<< "\nyour are signed up ... ";
}
void temp :: login(){
    cout<< "\n----------LOGN_IN----------";
    cout<< "\nEnter User Name : " ;
    getline(cin, searchName);

    cout<< "\nEnter Password : " ;
    getline(cin, searchPassword);

    file.open("LoginData.txt", ios :: in);
    getline(file, userName,'*');
    getline(file, Email,'*');
    getline(file, Password,'\n');

      while(!file.eof()){
        if( userName == searchName){
            if( Password == searchPassword){
            cout<<"\nLogin Successful....!";
            cout << "\nUser Name : "<<userName;
            cout<<"\nEmail : "<< Email ;
        }else {
        cout<<"Incorrect Password...!";
        }
      }
      getline(file, userName,'*');
      getline(file, Email,'*');
      getline(file, Password,'\n');
    }
    file.close();
}
void temp :: forgot(){
    cout<<"\nEnter Your User Name : ";
    getline(cin,searchName);
    cout<<"\nEnter Your Email Address : ";
    getline(cin, searchaEmail);

    file.open("LoginData.txt", ios :: in);
    getline(file, userName,'*');
    getline(file, Email,'*');
    getline(file, Password,'*');

    while(!file.eof()){
        if( userName == searchName && Email == searchaEmail ){
            cout<<"\n****Account Found****";
            cout<<"\nYour Password is : "<<Password ;
        }else {
        cout<<"****Not-Found****";
        }
        getline(file, userName,'*');
        getline(file, Email,'*');
        getline(file, Password,'*');
      }
    file.close();
}