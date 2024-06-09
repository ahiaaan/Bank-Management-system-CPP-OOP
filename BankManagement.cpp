#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>

using namespace std;

#ifdef _WIN32
#define WINDOWS
#endif

void clearscreen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    std::system("clear");
#endif
}

class Account
{
private:
    string Name;
    long int Accountnum;
    double Balance;
    string Address;
    int byear;
    int bmonth;
    int bday;
    string username;
    string password;

public:

    Account() : Accountnum(0), Balance(0.0), byear(0), bmonth(0), bday(0) {}

    bool isactive = true;

    void setName(const string &name) { Name = name; }
    string getName() const { return Name; }

    void setbyear(int By) { byear = By; }
    int getbyear() const { return byear; }

    void setbmonth(int Bm) { bmonth = Bm; }
    int getbmonth() const { return bmonth; }

    void setbday(int Bd) { bday = Bd; }
    int getbday() const { return bday; }

    void setAccountnum(long int accountnum) { Accountnum = accountnum; }
    long int getAccountnum() const { return Accountnum; }

    void setBalance(double balance) { Balance = balance; }
    double getBalance() const { return Balance; }

    void setAddress(const string &address) { Address = address; }
    string getAddress() const { return Address; }

    void setUsername(const string &Username) { username = Username; }
    string getUsername() const { return username; }

    void setPassword(const string &Password) { password = Password; }
    string getPassword() const { return password; }



    //Function to Deposit money to the account

    void deposit(double ammount){
    
        if(ammount >= Balance){
            Balance += ammount;
            cout<<"Deposited the money , New Balance is  - "<<Balance<<std::endl;
        }
        else{
            std::cout<<"Please enter a positive number . "<<std::endl;
        }
    }


    //Funtion to withdraw money from the account .

    void withdraw(double ammount)
    {
        if(ammount > 0 && ammount <= Balance){
            Balance -= ammount;
            cout<<"Withdrawn money Successfully , New Balance is - " <<Balance<<std::endl;
        }
        else{
            cout<<"Insufficient funds . "<<std::endl;
        }
    }



    void showacc() const
    {
        std::cout << "Name: " << Name << "\n";
        std::cout << "Account Number: " << Accountnum << "\n";
        std::cout << "Address: " << Address << "\n";
        std::cout << "Balance: " << Balance << "\n";
        std::cout << "Birth Date: " << byear << "-" << bmonth << "-" << bday << "\n";
        cin.get();
    }

    

    
};

class Bank
{
protected:
    std::vector<Account> accounts;

public:

int countmistake;

Account* loggedinaccount = nullptr;



void aboutus(){
    std::cout<<"\n\n\tProject for the University"<<std::endl;
    std::cout<<"________________Author Name - Ahian Kabir Abid________________"<<std::endl;
    std::cout<<"____________University Name - Silesian University of Technology________________"<<std::endl;
    std::cout<<"____________________Contact - ahiankabir@icloud.com________________"<<std::endl;
    std::cin.get();
}


void useraccountshow(){
    for(Account &account :accounts){
        if(account.isactive){
            cout<<"Name - "<<account.getName()<<std::endl;
            cout<<"Address - "<<account.getAddress()<<std::endl;
            cout<<"Account number - "<<account.getAccountnum()<<std::endl;
            cout<<"Date of birth [DD-MM-YYYY] - "<<account.getbday()<<"-"<<account.getbmonth()<<"-"<<account.getbyear()<<std::endl;
            break;
        }
    }
    std::cerr<<"No account found"<<std::endl;
}



void deleteaccount(){
        long int accno;
        string delchoice;
        
        cout<<"Enter the account number of the user - ";
        cin>>  accno;
        for(Account &account :accounts){
            if(accno == account.getAccountnum()){
                account.showacc();
                std::cout<<"\nPLEASE ENTER Y TO DELETE THE ACCOUNT OR NO TO CANCEL - ";
                cin>>delchoice;
                if(delchoice == "y" || delchoice == "Y"){
                account.isactive = false;
                cout<<"Account deleted Successfully"<<std::endl;
                saveAccounts();
                return;
                }
                else if( delchoice == "N" or delchoice == "n"){
                    return;
             }
        }
    }
    std::cerr<<"No account found "<<std::endl;
}


/// Function to reactivate the account 

    void reactivateaccount(){
    long int accno;
    string accchoice;
        cout<<"Enter the account number - ";
        cin>>accno;

        for( Account &account :accounts){
            
                if(accno == account.getAccountnum()){
                account.showacc();
                std::cout<<"\nPLEASE ENTER Y TO ACTIVATE THE ACCOUNT OR NO TO CANCEL - ";
                cin>>accchoice;
                if(accchoice == "y" || accchoice == "Y"){
                account.isactive = true;
                cout<<"Account activated Successfully"<<std::endl;
                saveAccounts();
                return;
                }
                else if( accchoice == "N" or accchoice == "n"){
                return;
            }
        }
    }
    std::cerr<<"Account not found"<<std::endl;
}
    

    void saveAccounts()
    {
        std::ofstream write("accounts.txt", std::ios::trunc);

        if (!write)
        {
            std::cerr << "Failed to open the file." << std::endl;
            return;
        }
        for (const Account &account : accounts)
        {
            write << account.getUsername() << "\n";
            write << account.getPassword() << "\n";
            write << account.getName() << "\n";
            write << account.getAccountnum() << "\n";
            write << account.getAddress() << "\n";
            write << account.getBalance() << "\n";
            write << account.getbyear() << "\n";
            write << account.getbmonth() << "\n";
            write << account.getbday() << "\n";
            write << account.isactive<<"\n";
            write << "\n";
        }
        write.close();
    }

    void loadAccounts()
    {
        std::ifstream read("accounts.txt");
        if (!read)
        {
            std::cerr << "Failed to open the file." << std::endl;
            return;
        }
        while (true)
        {
            Account account;
            string name;
            long int accountnum;
            string address;
            double balance;
            int byear, bmonth, bday;
            string username, password;
            bool isactive;

            std::getline(read, username);
            if (username.empty())
            {
                break;
            }
            std::getline(read, password);
            std::getline(read, name);
            read >> accountnum;
            read.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(read, address);
            read >> balance;
            read.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            read >> byear >> bmonth >> bday;
            read.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            read>>isactive;
        

            account.setUsername(username);
            account.setPassword(password);
            account.setName(name);
            account.setAccountnum(accountnum);
            account.setAddress(address);
            account.setBalance(balance);
            account.setbyear(byear);
            account.setbmonth(bmonth);
            account.setbday(bday);
            account.isactive = isactive;

            accounts.push_back(account);
        }
        read.close();
    }

    void modifyacc()
    {
        long int accountnum;
        std::cout << "Enter the account number of the account you want to modify: ";
        std::cin >> accountnum;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        bool accountfound = false;

        for (Account &account : accounts)
        {
            if (accountnum == account.getAccountnum()&& account.isactive)
            {
                accountfound = true;
                int choice;
                std::cout << "What do you want to modify?\n1. Name\n2. Address\n";
                std::cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (choice == 1)
                {
                    string Fname, Lname;
                    std::cout << "Enter the new first name(s): ";
                    std::getline(std::cin, Fname);
                    for (char &c : Fname) c = std::toupper(c);

                    std::cout << "Enter the new last name: ";
                    std::getline(std::cin, Lname);
                    for (char &c : Lname) c = std::toupper(c);

                    string modname = Fname + " " + Lname;
                    account.setName(modname);
                    saveAccounts();
                    std::cout << "Account modified successfully.\n";
                }
                else if (choice == 2)
                {
                    string newAddress;
                    std::cout << "Enter the new address: ";
                    std::getline(std::cin, newAddress);
                    for (char &c : newAddress) c = std::toupper(c);

                    account.setAddress(newAddress);
                    saveAccounts();
                    std::cout << "Account modified successfully.\n";
                }
                else
                {
                    std::cout << "Invalid choice.\n";
                }
                break;
            }
        }

        if (!accountfound)
        {
            std::cerr << "Account not found" << std::endl;
        }
        cin.get();
    }

    void admindeposit()
    {
        bool accountFound = false;
        long int accountnum;
        std::cout << "Enter account number: ";
        std::cin >> accountnum;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (Account &account : accounts)
        {
            if (accountnum == account.getAccountnum() && account.isactive)
            {
                accountFound = true;
                cout<<"Enter the ammount - "<<endl;
                double depammount;
                cin>>depammount;
                account.deposit(depammount);
                saveAccounts();                
                break;
            }
            else{
                std::cout<<"The account is deactivated or ";
                break;
            }
        }
        if (!accountFound)
        {
            std::cerr << "Account not found" << std::endl;
        }
        cin.get();
    }
    


    /// @brief  admin withdraw money option 


    void adminwithdraw(){
    
        long int accountnum;
        std::cout << "Enter account number: ";
        std::cin >> accountnum;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        bool accountfound = false;
        for(Account &account : accounts){
            if(accountnum == account.getAccountnum()){
                accountfound =true;
                double withdrawammount;
                cout<<"Enter the ammount - ";
                cin>>withdrawammount;
                account.withdraw(withdrawammount);
                saveAccounts();
                break;                
            }
        }
        if(!accountfound){
            cout<<"No account found"<<std::endl;
        }
        cin.get();
    }

    void useracc()
    {
        long int accountnum;
        std::cout << "Enter your account number: ";
        std::cin >> accountnum;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (Account &account : accounts)
        {
            if (accountnum == account.getAccountnum())
            {
                account.showacc();
                return;
            }
        }
        std::cerr << "Account not found.\n";
    }

    void adminlogin()
    {
        string adminusername, adminpassword;

        std::cout << "Username: ";
        std::cin >> adminusername;
        std::cout << "Password: ";
        std::cin >> adminpassword;

        const string correct_adminusername = "a";
        const string correct_adminpassword = "a";

        if (adminusername == correct_adminusername && adminpassword == correct_adminpassword)
        {
            int choice;
            do
            {
                std::cout << "1. Modify account\n";
                std::cout << "2. Deposit money\n";
                std::cout << "3. Withdraw money\n";
                std::cout << "4. Show account\n";
                std::cout <<"5. Delete an account\n";
                std::cout <<"6. Activate an account\n";
                std::cout <<"7. Go back\n";
                std::cin >> choice;
                clearscreen();

                switch (choice)
                {
                case 1:
                    modifyacc();
                    break;
                case 2:
                    admindeposit();
                    break;
                case 3:
                    adminwithdraw();
                    break;
                case 4:
                    useracc();
                    break;
                case 5:
                    deleteaccount();
                    break;
                case 6:
                    reactivateaccount();
                    break;
                case 7:
                    return;

                default:
                    std::cout << "Invalid choice, please select between 1-5\n";
                }
            } while (choice != 7);
        }
        else
        {
            std::cout << "Invalid admin credentials.\n";
        }
    }


    /// @brief login function for the user 

    void login(){

        string uname,pa;

        std::cout<<"Enter username - ";
        cin>>uname;

        cout<<"Enter password - ";
        cin>>pa;

        for(Account &account :accounts){
            if(uname == account.getUsername() && pa == account.getPassword()){
                loggedinaccount = &account;
                cout<<"Login Successfull " <<account.getName() <<'\n';
                return;

            }
        }
        cout<<"No account found"<<std::endl;
    }



    void loginpage(){
        
        login();
        for(Account &account : accounts){
            if(account.isactive && loggedinaccount){
                

                int choice;

            do{
                std::cout<<"1 . Modify Account"<<std::endl;
                std::cout<<"2 . Deposit Money"<<std::endl;
                std::cout<<"3 . Withdraw Money"<<std::endl;
                std::cout<<"4 . Showc Account"<<std::endl;
                std::cout<<"5 . Log out"<<std::endl;

                std::cin>>choice;

                switch (choice)
                {
                case 1:
                    cout<<"You have to contact the administrator to modify your account."<<std::endl;
                    break;

                case 2:
                    userdepositmoney();
                    break;

                case 3:
                    userwithdrawmoney();
                    break;

                case 4:
                    useraccountshow();
                    break;   
                case 5:
                    return;

                default:
                    std::cout<<"Select a valid option between 1 to 4"<<std::endl;
                    break;
                }


            }while(choice != 5);
        }
            }
        }


/// @brief interface after running the program 

    void mainpage()
    {
        int choice;
        do
        {
            std::cout << "Please select an option:\n";
            std::cout << "1. Create new account\n";            
            std::cout << "2. Login\n";
            std::cout << "3. Admin login\n";
            std::cout << "4. About Us\n";
            std::cout << "5. Close\n";
            
            std::cin >> choice;
            clearscreen();

            switch (choice)
            {
            case 1:
                createacc();
                break;
            
            case 2:
                loginpage();
                break;
            case 3:
                adminlogin();
                break;

            case 4:
                aboutus();
                break;
            
            case 5:
                clearscreen();
                break;

            default:
                std::cout << "Invalid choice, please select between 1-4\n";
            }
        } while (choice != 5);
    }


    /// @brief User deposit function

    void userdepositmoney(){

        long int accountnum;
        double depositamm;
        
        if(loggedinaccount){
            cout<<"Enter the ammount - ";
            cin>>depositamm;

            loggedinaccount->deposit(depositamm);
            saveAccounts();
        }
    }


    /// @brief user withdraaw function

    void userwithdrawmoney(){

        if(!loggedinaccount){
            std::cout<<" No account found "<<std::endl;
        }
         
        double withdrawamm;

        cout<<"Enter the ammont - "<<std::endl;
        cin>>  withdrawamm;
        loggedinaccount-> withdraw(withdrawamm);
    }


    /// @brief create account funciton for users

    void createacc() 
    {
        Account newaccount;
        string Fname, Lname, newAddress;
        int biyear, bimonth, biday;
        string username, password;

        std::cout << "Enter your username: ";
        std::cin.ignore();
        std::getline(cin, username);

        std::cout << "Enter your password: ";
        
        std::getline(cin, password);

        std::cout << "Enter your first name(s): ";
        std::getline(std::cin, Fname);
        for (char &c : Fname)
            c = std::toupper(c);

        std::cout << "Enter your last name: ";
        std::getline(std::cin, Lname);
        for (char &c : Lname)
            c = std::toupper(c);

        std::cout << "Enter your address: ";
        std::getline(std::cin, newAddress);
        for (char &c : newAddress)
            c = std::toupper(c);

        std::cout << "Enter your birth year: ";
        std::cin >> biyear;

        std::cout << "Enter your birth month and day: ";
        std::cin >> bimonth >> biday;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        string createname = Fname + " " + Lname;

        newaccount.setUsername(username);
        newaccount.setPassword(password);
        newaccount.setName(createname);
        newaccount.setAddress(newAddress);
        newaccount.setAccountnum(accounts.size() + 1);
        newaccount.setBalance(0);
        newaccount.setbyear(biyear);
        newaccount.setbmonth(bimonth);
        newaccount.setbday(biday);

        accounts.push_back(newaccount);
        saveAccounts();

        std::cout << "Account created successfully.\n";
        newaccount.showacc();
    }




};


int main()
{
    Bank bank;
    bank.loadAccounts();
    bank.mainpage();
    bank.saveAccounts();
    return 0;
}
