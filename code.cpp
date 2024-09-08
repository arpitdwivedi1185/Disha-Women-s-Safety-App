#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <iterator>
#include <queue>

using namespace std;


class Login_Details
{
    private:
    string ID;
    string Password;
    
    public:
    void setID(string id)
    {
        ID=id;
    }
    void setPassword(string pass)
    {
        Password = pass;
    }
    string getID()
    {
        return ID;
    }
    string getPassword()
    {
        return Password;
    }
};



class EmergencyContactList
{
    private:
    int nofcontacts;
    string *array;

    public:
    EmergencyContactList(){}
    EmergencyContactList(int num)
    {
        cout<<"It is mandatory to have "<<num<<" contacts in your Emergency contact list!\n";
        nofcontacts = num;
        array = new string[nofcontacts];
        string str;
        int i=0;
        while(i<nofcontacts)
        {
            cout<<"Enter contact number "<<i+1<<": ";
            cin>>str;
            if(str.length() == 10 && unique(str))
            {
                array[i] = str;
                i++;
            }
            else if(unique(str))
            {
                cout<<"Enter a valid number !"<<endl;
            }
            else
            {
                cout<<"Enter a non duplicate entry!\n";
            }
        }
    }

    int unique(string str)
    {
        int count=0;
        for(int i=0 ; i<nofcontacts ; i++)
        {
            if(str == array[i])
            {
                count++;
            }
        }
        if(!count)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    void printEmeregencyList()
    {
        cout<<"The Emergency Contact List is : \n";
        for(int i=0 ; i<nofcontacts ; i++)
        {
            cout<<array[i]<<endl;
        }
        cout<<endl;
    }
};


class User : public Login_Details
{
    int age;
    string name;
    string phone;
    string Address;
    EmergencyContactList Clist;

    public:
    User(){}
    User(int n) : Clist(n) {}
    User(string n,int a,string p,string add) : Clist(5)
    {
        name = n;
        age = a;
        phone = p;
        Address =add;
    }
    void setage(int a)
    {
        age = a;
    }
    int getage()
    {
        return age;
    }
    void setname(string n)
    {
        name = n;
    }
    string getname()
    {
        return name;
    }
    void setphone(string p)
    {
        phone = p;
    }
    string getphone()
    {
        return phone;
    }
    void setaddr(string add)
    {
        Address =add;
    }
    string getaddr()
    {
        return Address;
    }
    void operator ++ ()
    {
        cout<<"Enter name : \n";
        getline(cin>>ws,name);
        cout<<"Enter age : \n";
        cin>>age;
        cout<<"Enter personal contact number : \n";
        getline(cin>>ws,phone);
        cout<<"Enter address : \n";
        getline(cin>>ws,Address);
    }
};


class User_Management : public User
{
    private:
    string filename;


    public:

    User_Management(string filename)
    {
        this->filename = filename;
    }

    bool check_user(string id,string pass)
    {
        ifstream file(this->filename,ios::binary);
        User user;
        while(file.read((char *)&user,sizeof(user)))
        {
            if(user.getID() == id && user.getPassword() == pass)
            {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    void signup(string id,string pass)
    {
        bool success = check_user(id,pass);
        if(!success)
        {
            ofstream file(this->filename, ios::out | ios::app | ios::binary);
            User user(5);
            //user.setvalues();
            ++user;
            user.setID(id);
            user.setPassword(pass);
            file.write((char *)&user,sizeof(user));
            file.close();
            cout<<"Successfully created account\n";
        }
        else
        {
            cout<<"User already exists\n";
        }
    }

    void login(string id,string pass)
    {
        bool success = check_user(id,pass);
        cout<< (success ? "Login Successful" : "Login Failed! Please try again!") << endl;
    }
};

class admin : public Login_Details
{
    public:
    admin(){}
    admin(int n)
    {
        string id,pass;
        cout<<"Enter admin ID : ";
        getline(cin>>ws,id);
        cout<<"Enter admin Password : ";
        getline(cin>>ws,pass);
        setID(id);
        setPassword(pass);
    }
};

class Admin_Management : public admin
{
    private:
    string filename;


    public:

    Admin_Management(string filename)
    {
        this->filename = filename;
    }

    bool check_admin(string id,string pass)
    {
        ifstream file(this->filename,ios::binary);
        admin user;
        while(file.read((char *)&user,sizeof(user)))
        {
            if(user.getID() == id && user.getPassword() == pass)
            {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    void signup(string id,string pass)
    {
        bool success = check_admin(id,pass);
        if(!success)
        {
            ofstream file(this->filename, ios::out | ios::app | ios::binary);
            admin user;
            user.setID(id);
            user.setPassword(pass);
            file.write((char *)&user,sizeof(user));
            file.close();
            cout<<"Successfully created account\n";
        }
        else
        {
            cout<<"User already exists\n";
        }
    }

    void login(string id,string pass)
    {
        bool success = check_admin(id,pass);
        cout<< (success ? "Login Successful" : "Login Failed! Please try again!") << endl;
    }
};


void menu()
{
    cout<<"\n-------------------------------------------------\n";
    cout<<"Enter options according to what would you like to do!!!\n";
    cout<<"1. Signup for a new account\n";
    cout<<"2. Login into an existing account\n";
    cout<<"3. Signup for a new admin account\n";
    cout<<"4. Login into an existing admin account\n";
    cout<<"5. For exit\n";
}

void menu2()
{
    cout<<"\n- - - - - - - - - - - - - - - - - - - - - - - -\n";
    cout<<"Enter options according to what would you like to do!!!\n";
    cout<<"1. For EMERGENCY!!!\n";
    cout<<"2. For getting details of nearest police station\n";
    cout<<"3. For getting the fastest path from source to destination\n";
    cout<<"4. For exit\n";
}


const int INF = 1e9 + 7;

class City_Map
{
    private:
    string *name;
	
	protected:
	int total_places, **APG;
    int **G;
    int total_police_stations;
	unordered_map<int, bool> check_police;
	
    public:
    City_Map(){}
    City_Map(int mn)
    {
        int n, m;
        cout << "Enter the value of n(number of Places) amd m(number of Police Stations): ";
        cin >> n >> m;
        vector<int> p_s(m);
		G = new int* [n + 1];
        APG = new int* [n + 1];
        for(int i = 1; i <= n; i++)
        {
        	G[i] = new int[n + 1];
        	APG[i] = new int[n + 1];
        	check_police[i] = false;
		}
        name = new string[n];
        cout<<"Enter the names of places : \n";
        for(int i=0 ; i < n ; i++)
        {
            cout<<"Name of place at index "<<i<<" is : ";
            getline(cin>>ws,name[i]);
        }
		cout << "Enter the police station Places: ";
		for(int i = 0; i < m; i++)
		{
			cin >> p_s[i];
		}
		total_places = n;
        total_police_stations = m;
		for(auto it: p_s)
		{
			check_police[it] = true;
		}
        cout<< "Enter the distance matrix : \n";
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
                if(i!=j)
                {
                    cout<<"The distance between "<<i<<" and "<<j<<" is : ";
				    cin >> G[i][j];
				    APG[i][j] = G[i][j];
                }
                
			}
		}
		All_Pair_Shortest(APG, total_places);
    }
    
    int Get_Distance(int i, int j)
    {
    	return G[i][j];
	}
	
	void All_Pair_Shortest(int **A, int total_places)
	{
		for(int k = 1; k <= total_places; k++)
		{
			for(int i = 1; i <= total_places; i++)
			{
				for(int j = 1; j <= total_places; j++)
				{
					if(A[i][k] + A[k][j] < A[i][j])
						A[i][j] = A[i][k] + A[k][j];
				}
			}
		}
	}

    string getname(int n)
    {
        return name[n];
    }
};

class Police_Map : public City_Map
{
	private:
	int **PG;
    int speed;
    string city;
	
	public:
    Police_Map(){}
	Police_Map(int n) : City_Map(5)
	{	
        cout<<"Enter City name of graph : ";
        string str;
        getline(cin>>ws,str);
        city = str;
        speed = 5;
		PG = new int* [total_places + 1];
		for(int i = 1; i <= total_places; i++)
		{
			PG[i] = new int[total_places + 1];
		}
		for(int i = 1; i <= total_places; i++)
		{
			if(check_police[i])
			{
				for(int j = 1; j <= total_places; j++)
				{
					PG[i][j] = APG[i][j];
				}
			}
			else
			{
				for(int j = 1; j <= total_places; j++)
				{
					PG[i][j] = INF;
				}
			}
		}
	}
	
	void call_nearest_police_station(int current)
	{
		int distance, nearest_police;
		distance = INF;
		for(int i = 1; i <= total_places; i++)
		{
			if(PG[i][current] < distance)
			{
				distance = PG[i][current];
				nearest_police = i;
			}
		}
        float time = float(distance) / float(speed);
        if(current == nearest_police)
        {
            cout<<"You are at the police station '"<< getname(nearest_police)<< "' itself and Help will arrive Immediately !!!\n";
        }
        else
        {
            cout << "\nNearest Police Station No. " << nearest_police <<" '"<<getname(nearest_police)<<"' has been informed.\n";
		    cout << "\nThey are at a distance of " << distance << " and will arrive in " << time << " minutes.\n"; 
        }
	}

    void nearest_police_station(int current)
	{
		int distance, nearest_police;
		distance = INF;
		for(int i = 1; i <= total_places; i++)
		{
			if(PG[i][current] < distance)
			{
				distance = PG[i][current];
				nearest_police = i;
			}
		}
        if(current == nearest_police)
        {
            cout<<"You are at the nearest police station '"<< getname(nearest_police)<< "' itself !!!\n";
        }
        else
        {
            cout << "\nNearest Police Station  is No. " << nearest_police <<" '"<<getname(nearest_police)<<"' at a distance of "<<distance<<" km\n"; 
        }
		
	}

    string getcity()
    {
        return city;
    }
    void setcity(string str)
    {
        city = str;
    }

   
    // Function to find the shortest path from source to destination and print the route
    void Shortest_Path(int source, int destination)
    {
        int n = total_places;
        vector<int> dist(n + 1, INF);
        vector<int> parent(n + 1, -1);
        vector<bool> visited(n + 1, false);

        dist[source] = 0;
        for (int i = 1; i <= n; i++)
        {
            int u = -1;
            for (int j = 1; j <= n; j++)
            {
                if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                {
                    u = j;
                }
            }

            visited[u] = true;

            for (int v = 1; v <= n; v++)
            {
                if (G[u][v] != 0 && !visited[v])
                {
                    int newDist = dist[u] + G[u][v];
                    if (newDist < dist[v])
                    {
                        dist[v] = newDist;
                        parent[v] = u;
                    }
                }
            }
        }

        // print shortest path
        if (dist[destination] == INF)
        {
            cout << "No path found\n";
        }
        else
        {
            vector<int> path;
            for (int v = destination; v != -1; v = parent[v])
            {
                path.push_back(v);
            }
            reverse(path.begin(), path.end());

            cout << "Shortest path from " << source << " to " << destination << ": ";
            for (int v : path)
            {
                cout << v << " ";
            }
            cout << "\n";
        }
    }
};



int main()
{
    User_Management users("Users.txt");
    Admin_Management admins("Admins.txt");
    
    cout<<"-------------------------------------------------\n";
    cout<<"Welcome to DISHA - The Women Safety App\n";
    int flag = 0;
    int flag2 = 0;
    int flag3 = 0;
    bool success;
    string name;
    Police_Map Police;
    while(!flag)
    {
        menu();
        int n;
        cout<<"Enter your choice : ";
        cin>>n;
        string id;
        string pass;
        switch(n)
        {
            case 1:
                cout<<"You have opted for signing up for a new account : \n";
                cout<<"Enter ID : ";
                cin>>id;
                cout<<"Enter password : ";
                cin>>pass;
                users.signup(id,pass);
                break;

            case 2:
                cout<<"You have opted for logging in into an old account : \n";
                cout<<"Enter ID : ";
                cin>>id;
                cout<<"Enter password : ";
                cin>>pass;
                users.login(id,pass);
                success = users.check_user(id,pass);
                if(!flag3)
                {
                    cout<<"Wait for the admin to enter the graph details!!!\n";
                    break;
                }
                flag2 = 0;
                while(!flag2 && success)
                {
                    menu2();
                    int n2;
                    cout<<"Enter your choice : ";
                    cin>>n2;
                    int source;
                    int destination;
                    switch(n2)
                    {
                        case 1:
                            cout<<"Enter index where you are at? ";
                            cin>>source;
                            Police.call_nearest_police_station(source);
                            break;
                        case 2:
                            cout<<"Enter index where you are at? ";
                            cin>>source;
                            Police.nearest_police_station(source);
                            break;
                        case 3:
                            cout<<"Enter index where you are at? ";
                            cin>>source;
                            cout<<"Enter the destination vertex : ";
                            cin>>destination;
                            Police.Shortest_Path(source,destination);
                            break;
                        case 4:
                            flag2 = 1;
                            break;
                        default:
                            cout<<"Kindly Enter a valid option!!!\n";
                            break;
                    }
                }
                break;

            case 3:
                cout<<"You have opted for signing up for a new admin account : \n";
                cout<<"Enter admin ID : ";
                cin>>id;
                cout<<"Enter admin password : ";
                cin>>pass;
                admins.signup(id,pass);
                break;

            case 4:
                cout<<"You have opted for logging in into an old admin account : \n";
                cout<<"Enter admin ID : ";
                cin>>id;
                cout<<"Enter admin password : ";
                cin>>pass;
                admins.login(id,pass);
                success = admins.check_admin(id,pass);
                if(success)
                {
                    Police_Map Police1(5);
                    Police = Police1;
                }
                flag3 = 1;
                break;


            case 5:
                flag = 1;
                break;

            default:
                cout<<"Kindly Enter a valid option!!!\n";
                break;
        }
    }
    return 0;
}


