#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <limits>
#include <string>
using namespace std;

inline void admin_menu(){
    cout << "---Admin Menu---" << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Edit Product" << endl;
    cout << "3. Remove Product" << endl;
    cout << "4. Search Product" << endl;
    cout << "5. Show Unavailable Products" << endl;
    cout << "6. Show Top 5 Products" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice:" << endl;
}
inline void client_menu(){
	cout << "---Customer Menu---" << endl;
    cout << "1. Search for a product" << endl;
    cout << "2. Add product to cart" << endl;
    cout << "3. Update product from cart" << endl;
    cout << "4. Remove product from cart" << endl;
    cout << "5. Complete order" << endl;
    cout << "6. View order history" << endl;
    cout << "7. View cart" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice:" << endl;
}

string file_path_prod,file_path_categ,file_path_user;

void printCategories() {//prints categories based on the file provided by the user and works flawlessly for the special categories file
	ifstream file2(file_path_categ.c_str());
	string line;
	int n = 1;
	while (getline(file2, line)) {
		string categ;

		for (int i = 0; i < line.length(); ++i) {

			if (line[i] == '(') {
	    		if (!categ.empty()) {
	
					cout << n << ". " << categ;
					cout << endl;
					n++;
				}
				break;
			} else {
				categ += line[i];
			}
		}
	}
	file2.close();
}

void printSubcategories(string categ){//prints the categories of the given category
	ifstream file2(file_path_categ.c_str());//we use c_str() because ifstream,fstream and ofstream require C-style string, not a std::string
	string word;
	int i = 0;
	while((getline(file2,word))&& (i == 0) ){
		if(word.find(categ) != string::npos){
			int j=categ.length() + 1;
			while(word[j] != ')'){
				if((word[j] != '(')&& (word[j] != '@')){
					cout << word[j];
				}
				j++;
			}
			i =1;
		}
	
	}	
	file2.close();
	cout<<endl;
}


class products {
	private:
		string title,description,Category,Subcategory,type; 
		float price_per;
		int amount;
		int sum;
	public:
		products() : title(""), description(""), Category(""), Subcategory(""), type(""), price_per(0.0f), amount(0), sum(0) {}
		void setTitle(string titl) { title = titl; }
		void setDescription(string descr) {description = descr; }
		void setType(string typ){ type = typ;}
		void setPrice_Per(float price){ price_per =price; }
		void setAmount(int amoun) {amount =amoun;}
		void setCategory(string categ){Category = categ; }
		void setSubcategory(string subcateg){Subcategory = subcateg; }
		void setSum(int su) { sum = su;}
	    int getSum(){return sum; }
	    string getSubcategory() { return Subcategory; }
	    string getTitle() {return title; }
	    string getDescription(){ return description; }
	    string getCategory() {return Category; }
	    string getType() { return type;}
	    int getAmount() { return amount;}
		string getPrice_Per() {
	        char buffer[50];
	        sprintf(buffer, "%.2f", price_per);
	        return string(buffer);
	    }
	    void print_p() {
	    	cout<<"Title: "<<getTitle()<<endl;
	        cout<< "Description: "<< getDescription() << endl;
	        cout << "Category: " <<getCategory() << endl;
	        cout<< "Subcategory: " <<getSubcategory() << endl;
	        cout<<"Price per unit: " <<getPrice_Per() <<endl;
	        cout << "Total "<<getType() <<"s available: " << getAmount()<<endl;
    	}    
};


class user{
	private:
		string username;
		string password;
		int isAdmin;
	public:
		user(){}
		~user(){}
		void setUsername(string usr);
		void setPass(string pass);
		void setIsadmin(int adm);
		void print();
		void addtocart();
		string getUsername(){return username;}
		string getPass(){return password;}
		int getIsadmin(){return isAdmin;}

};


class eshop{
	private:
		vector<products*> cart;
		vector<user*> users;
		vector<products*> prod;
	public:
		void productfile_vector();// Loads product data into a vector
		void userfile_vector();//Loads user data into a vector
		void addProduct_adm();//for admins
		void editProduct();//for admins
		void removeProduct();//for admins
		void search_product();//for admins
		void top5_products();//for admins
		void unavailable_p();//for admins
		string login_register();//for all users
		void vector_tousersfile();//Saves user data from the vector to a file
		void vector_toproductfile();//Saves product data from the vector to a file
		void search_product2();//for clients
		void Confirm_Order(string usrnm);//for clients
		void Add_Product_cl();//for clients
		void Remove_Product();//for clients
		void Order_History();//fot clients
		void Edit_Cart();//for clients
		void View_Cart();//for clients
		void View_History(string usrnm);//for clients
		int userfound(string found);
		~eshop();//destructor
};
void eshop::vector_tousersfile(){//KALO
	fstream file3(file_path_user.c_str(), ios::out | ios::trunc);
	for(int i=0; i<users.size(); i++){
		file3 << users[i]->getUsername() << ","<<users[i]->getPass() << "," << users[i]->getIsadmin()<<endl;
	}
	file3.close();
}

void eshop::vector_toproductfile(){//KALO
	fstream file2(file_path_prod.c_str(), ios:: out | ios:: trunc);
	for(int i =0; i <prod.size(); i++){
		file2 << prod[i]->getTitle() << " @ " << prod[i]->getDescription() << " @ " << prod[i]->getCategory() << " @ " << prod[i]->getSubcategory() << " @ " << prod[i]->getPrice_Per() << " @ " << prod[i]->getType() << " @ " << prod[i]->getAmount() << endl;
	}
	file2.close();
}

void eshop:: userfile_vector(){//users kalo
	ifstream file3(file_path_user.c_str());
	string line;
	while(getline(file3,line)){
		user*  newUser = new user;
		size_t pos1=0,pos2;
		pos2 = line.find(',',pos1);
		newUser ->setUsername(line.substr(pos1, pos2 - pos1));
		pos1 = pos2 +1;
		pos2 = line.find(',',pos1);
		newUser->setPass(line.substr(pos1,pos2 -pos1));
		pos1 = pos2 +1;
		newUser->setIsadmin(line[pos1] - '0');
		users.push_back(newUser);
	}
	file3.close();

}

void eshop::productfile_vector(){//kalo
	fstream file1(file_path_prod.c_str(),ios::in);
	string line;
	size_t first;
	size_t last;
	vector<string> words;
	while(getline(file1,line)){
		first = 0;
		products* newProd = new products;
		string word;
		while ((last = line.find('@', first)) != string::npos) { 
			word = line.substr(first, last - first);
			word.erase(0, word.find_first_not_of(" "));
			word.erase(word.find_last_not_of(" ") + 1);
			words.push_back(word);
			first = last + 1;
		}
		word =line.substr(first,line.length()-first);
		word.erase(0,word.find_first_not_of(" "));
		word.erase(word.find_last_not_of(" ") + 1);
		words.push_back(word);
		newProd->setTitle(words[0]);
		newProd->setDescription(words[1]);
		newProd->setCategory(words[2]);
		newProd->setSubcategory(words[3]);
		newProd->setPrice_Per(atof(words[4].c_str()));
		newProd->setType(words[5]);
		newProd->setAmount(atoi(words[6].c_str()));
		words.clear();
		prod.push_back(newProd);
		
	}
	file1.close();
}

void eshop::unavailable_p(){// Checks product quantities and prints titles of products with zero stock
	for(int i = 0; i< prod.size(); i++){
		if(prod[i]->getAmount() == 0){
			cout << " This product is temporarily unavailable: " << prod[i]->getTitle() <<", from the category: "<< prod[i]->getCategory() << " and the subcategory: " << prod[i]->getSubcategory() <<endl;
		}
	}	
}

void eshop::addProduct_adm(){ //products and categories kalo
	cout<< "Give product title:"<<endl;
	products* newProd = new products;
	float price;
	int amoun;
	string titl,descr,categ,subcateg,typ;
	getline(cin,titl);
	newProd->setTitle(titl);
	cout << "Give product description:"<<endl;
	getline(cin,descr);
	newProd->setDescription(descr);
	cout << "Give one of the following categories: "<<endl;
	printCategories();
	if(cin.peek() == '\n') {// Resolves input buffer issues caused by printCategories mixing with getline
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	}
	getline(cin,categ);
	newProd->setCategory(categ);
	cout << "Give one of the following subcategories: "<<endl;
	printSubcategories(categ);//It doesn't check if the subcategory belongs to the specific category, as this was clarified by the professor in response to a question.
	if(cin.peek() == '\n') {
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	}
	getline(cin,subcateg);
	newProd->setSubcategory(subcateg);
	cout << " Give product price: "<<endl;
	cin >> price;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	newProd->setPrice_Per(price);
	cout << "Give measurement type[Kg/Unit]:"<<endl;
	cin >> typ;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	newProd->setType(typ);
	cout << "Give amount of Unit:"<<endl;
	cin >> amoun;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	newProd->setAmount(amoun);
	prod.push_back(newProd);
	cout << "Product addedd successfully!" << endl;
}
	
void eshop::editProduct(){// edits the attributes of the product with the specified title 
	cout << "Enter the product's title you wish to edit: "<<endl;
	string titl;
	getline(cin,titl);
	int i,k = 0;
	for(i= 0; i < prod.size(); i++){
		if( prod[i] -> getTitle() == titl){//
			k = 1;
			break;//whether or not the title given is found. 
		}
	}
	if(k == 0){
		cout << "no product with the title " << titl << " was found"<<endl;
		return;
	}
	cout << "Enter number of field you want to edit: 1.Title 2.Description 3.Category and Subcategory 4.Price 5.Available " <<prod[i]->getType() << " 6.Nothing"<<endl;
	int selection;
	cin >> selection;
	string sub;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');	
	switch(selection){
		case 1://edits the attribute chosen by the admin.
			cout << "Enter new title:"<< endl;
			getline(cin,titl);
			prod[i] -> setTitle(titl);
			break;
		case 2:
			cout << "Enter new descrtiption:"<<endl;
			getline(cin,titl);
			prod[i]->setDescription(titl);
			break;
		case 3:
			cout << "Enter new category:"<<endl;
			getline(cin,titl);
			cout  <<"Enter new subcategory:"<< endl;
			getline(cin,sub);
			prod[i]->setCategory(titl);
			prod[i]->setSubcategory(sub);
			break;
		case 4:
			cout << "Enter new price"<<endl ;
			float pri;
			cin >> pri;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			prod[i]->setPrice_Per(pri);	
			break;	
		case 5:
			cout << "Enter new availability :"<< endl ;
			int quantity;
			cin >> quantity;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			prod[i]->setAmount(quantity);	
			break;		
		case 6:
			cout << "you chose nothing"<<endl;
			break;
		default:
			cout << "Error there isn't a " << selection << "choice" <<endl;
			break;
	}
	
	if((selection > 0) &&(selection < 6) ){
		cout << "Product updated!" << endl;
	}

}
void eshop::top5_products(){ //displays the top 5 products based on client selections.
	int n = prod.size();
	if(n>4){
		int top5[5],nums[n];
		string titls[5];
		for(int i = 0; i <n; i++){
			nums[i] = prod[i]->getSum();
		}
		for(int i =0; i < 5; i++){
			top5[i] = nums[i];
			titls[i]=prod[i]->getTitle();
		}
	    for (int i = 0; i < 5; i++) {
    		for (int j = i + 1; j < 5; j++) {
        		if (top5[i] < top5[j]) {
                int temp1 = top5[i];
                top5[i] = top5[j];
                top5[j] = temp1;
                string temp2 = titls[i];
                titls[i] = titls[j];
                titls[j] = temp2;
            	}
    		}
		}
		for (int i = 5; i < n; i++) {
		    if (nums[i] > top5[4]) {
		        top5[4] = nums[i];
		        titls[4] = titls[i];
		        for (int j = 3; j >= 0; j--) {
		            if (top5[j] < top5[j + 1]) {
		                int temp1 = top5[j];
		                top5[j] = top5[j + 1];
                    	top5[j + 1] = temp1;
                    	string temp2 = titls[j];
                    	titls[j] = titls[j+1];
                    	titls[j+1] = temp2;
                	}else{
                    	break;
                	}
            	}
        	}
    	}
    	cout <<"the top 5 products are: ";
		for (int i = 0; i < 5; i++) {
        	cout << " "<< i + 1 << "." << titls[i]; 
    	}
	}else{
		
	}

    cout << endl;
}

string eshop::login_register(){//return admin if the user is an admin ,return his name if the user is a client and returns error if the user did something wrong
	
	cout << "Do you want to login or register? (enter option): "<<endl;
	string opt;
	cin >> opt;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if(opt == "register"){
		cout << "Please enter your username:"<<endl;
		cin>>opt;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		for(int i = 0; i<users.size(); i++){
			if(opt == users[i]->getUsername()){
				cout << "name already exists please try again with a different name"<<endl;
				return "error";
			}
		}
		cout << "Please enter your password:"<<endl;
		string pass;
		cin >> pass;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Are you an admin user? (Y/N):"<<endl;
		char as;
		cin >>as;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while(as != 'n' && as != 'y' && as != 'Y' && as!= 'N'){
			cout << "you can only type y (for yes) and n (for no)" <<endl;
			cin >>as;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Thanks for signing up! Ysou are automatically logged-in as "<<opt <<endl;
		user* newUser = new user;
		newUser->setPass(pass);
		newUser->setUsername(opt);
		if(as == 'n' || as == 'N'){
			newUser->setIsadmin(0);
			string filepath = "files/order_history/" + opt + "_history.txt";
			fstream file(filepath.c_str(), ios::out);//creates the file of the client's order history
			file.close();
			users.push_back(newUser);
			return opt;
		}
		else{
			newUser->setIsadmin(1);
			users.push_back(newUser);
			return "admin";
		}

	}else if(opt == "login"){
		cout << "Please enter your username:" <<endl;
		cin >> opt;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		int k=0,j;
		for( j = 0; j <users.size(); j++){
			if(users[j]->getUsername() == opt){
				k = 1;
				break;
			}
		}//after user login, we immediately check whether the logged-in user is an admin or a client from the users vector
		if(k==0){
			cout << "Couldn't find the username: "<< opt << endl;
			return "error";
		}
		
		cout << "Please enter your password:"<<endl;
		string pass;
		cin >>pass;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if(pass != users[j]->getPass()){
			cout << "You gave incorrect password.Please try again."<< endl;
			return "error";
		}
		
		cout <<endl<< "Welcome " << opt << "!" <<endl<< endl; 
		if(users[j]->getIsadmin()==0){
			return users[j]->getUsername();
		}
		return "admin";
	}
	return "error";
}
void eshop::removeProduct(){//removes the product from the vector and deletes its memory, as it was created dynamically using new

	cout << "Enter product title you wish to remove:"<<endl;
	string titl;
	getline(cin,titl);
	int n = -1;	
	for (int i = 0; i < prod.size(); ++i) {
		if (prod[i]->getTitle() == titl) {
			n = i;
			break;
		}
	}//ends the function if the admin enters a title that doesn't match any of the current product titles.
	if(n == -1){
		cout << "Product not found" << endl;
	}else{
		delete prod[n];
		prod.erase(prod.begin() + n);
		cout << "Product removed" << endl;
	}
	
}
eshop::~eshop(){//destructor is must due to the use of the dynamic new in the vectors

	for(int i = 0; i < prod.size(); i++){
		delete prod[i];
	}
	prod.clear();
	for(int j = 0; j < users.size(); j++){
		delete users[j];
	}
	users.clear();
	cout << "Goodbye!"<<endl;
}

void eshop::search_product(){// last function that the admins can use 
	cout << " Product Search Options:"<<endl;
	cout << "1. Search for a specific product (by title)."<<endl;
	cout << "2. View the products of a specific category."<<endl;
	cout << "3. Show all the available products."<< endl;
	int n;//allows the admin to edit a product for each choice they make.
	cin >> n;//the edit functionality is the same as the one in the edit_product function.
	cin.ignore(numeric_limits<streamsize>::max(), '\n');//furthermore this function involves multiple user inputs, which may make it a bit complex due to the conditional statements, but it operates efficiently and as expected
	if(n == 1){
		cout << "Enter the title of the product you are looking for:" << endl;
		string titl;
		int k = 0;
		getline(cin,titl);
		int i;
		for(i = 0; i < prod.size(); i++){
			if(prod[i]->getTitle()== titl){
				k = 1;
				break;
			}
		}
		if(k == 1){
			prod[i]->print_p();
			cout << "do you want to edit this product? Enter [y/n]"<<endl;
			char yes_or_no;
			cin >> yes_or_no;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if(yes_or_no != 'Y' && yes_or_no != 'y'){
				return;
			}
			cout << "Enter number of field you want to edit: 1.Title 2.Description 3.Category and Subcategory 4.Price 5.Available " <<prod[i]->getType() << " 6.Nothing"<<endl;
			int selection;
			cin >> selection;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			string sub;
			string attr;
			switch(selection){
				case 1:
					cout << "Enter new title:"<< endl;
					getline(cin,attr);
					prod[i] -> setTitle(attr);
					break;
				case 2:
					cout << "Enter new descrtiption:"<<endl;
					getline(cin,attr);
					prod[i]->setDescription(attr);
					break;
				case 3:
					cout << "Enter new category:"<<endl;
					getline(cin,attr);
					cout  <<"Enter new subcategory:"<< endl;
					getline(cin,sub);
					prod[i]->setCategory(attr);
					prod[i]->setSubcategory(sub);
					break;
				case 4:
					cout << "Enter new price"<<endl ;
					float pri;
					cin >> pri;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					prod[i]->setPrice_Per(pri);		
					break;
				case 5:
					cout << "Enter new availability :"<< endl ;
					int quantity;
					cin >> quantity;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					prod[i]-> setAmount(quantity);	
					break;		
				case 6:
					cout << "you chose nothing"<<endl;
					break;
				default:
					cout << "Error there isn't a " << selection << "choice" <<endl;
					break;
			}
			
			if((selection > 0) &&(selection < 6) ){
				cout << "Product updated!" << endl;
			}			
		}else{
			cout << "couldn't find any product with the title: "<<titl << endl;
		}
	}else if(n == 2){
		cout << " Select a category from the list below :" << endl;
		printCategories();
		if (cin.peek() == '\n') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	}
		string categ;
		getline(cin,categ);
		cout <<"Would you like to select a subcategory? Enter[Y/N]:"<<endl;
		char an;
		cin>> an;
		if (cin.peek() == '\n') {
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	}
		if(an == 'y'|| an == 'Y'){
			printSubcategories(categ);
			string subcateg;
			cin >> subcateg;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			for(int j = 0; j <prod.size(); j++){
				if(prod[j]->getSubcategory() == subcateg){
					prod[j]->print_p();
				}
			}
			cout << "Do you want to edit a product from this subcategory? Enter[y/n]:"<<endl;
			char subcateg_y_or_n;
			cin >> subcateg_y_or_n;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if(subcateg_y_or_n == 'y' || subcateg_y_or_n == 'Y'){
				cout << "Enter the title of the product you want to edit:"<<endl;
				string titl2;
				getline(cin,titl2);
				int k5 = -1;
				for(int k4 = 0; k4 < prod.size(); k4++){
					if(prod[k4]->getSubcategory()==subcateg){
						k5 = 0;
					}
				}
				if(k5==-1){
					cout << "no product with this title in this subcategory"<<endl;
					return;
				}
				for(int k3 = 0; k3 <prod.size(); k3++){
					if(prod[k3]->getTitle()== titl2){
						cout << "Enter number of field you want to edit: 1.Title 2.Description 3.Category and Subcategory 4.Price 5.Available " <<prod[k3]->getType() << " 6.Nothing"<<endl;
						int selection;
						if(cin.peek() == '\n') {
					        cin.ignore(numeric_limits<streamsize>::max(), '\n');
					    }
						cin >> selection;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						string sub;
						string attr;
						switch(selection){
							case 1:
								cout << "Enter new title:"<< endl;
								getline(cin,attr);
								prod[k3] -> setTitle(attr);
								break;
							case 2:
								cout << "Enter new descrtiption:"<<endl;
								getline(cin,attr);
								prod[k3]->setDescription(attr);
								break;
							case 3:
								cout << "Enter new category:"<<endl;
								getline(cin,attr);
								cout  <<"Enter new subcategory:"<< endl;
								getline(cin,sub);
								prod[k3]->setCategory(attr);
								prod[k3]->setSubcategory(sub);
								break;
							case 4:
								cout << "Enter new price"<<endl ;
								float pri;
								cin >> pri;
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								prod[k3]->setPrice_Per(pri);		
								break;
							case 5:
								cout << "Enter new availability :"<< endl ;
								int quantity;
								cin >> quantity;
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								prod[k3]-> setAmount(quantity);	
								break;		
							case 6:
								cout << "you chose nothing"<<endl;
								break;
							default:
								cout << "Error there isn't a " << selection << "choice" <<endl;
								break;
						}
						
						if((selection > 0) &&(selection < 6) ){
							cout << "Product updated!" << endl;
						}
					}
				}
			}

		}else if(an == 'n'|| an== 'N'){
			for(int j = 0; j <prod.size(); j++){
				if(prod[j]->getCategory() == categ){
					prod[j]->print_p();
				}
			}
			cout << "Do you want to edit a product from this category? Enter[y/n]:"<<endl;
			char subcateg_y_or_n;
			cin >> subcateg_y_or_n;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if(subcateg_y_or_n == 'y' || subcateg_y_or_n == 'Y'){
				cout << "Enter the title of the product you want to edit:"<<endl;
				string titl2;
				getline(cin,titl2);
				int k5 = -1;
				for(int k4 = 0; k4 < prod.size(); k4++){
					if(prod[k4]->getCategory()==categ){
						k5 = 0;
					}
				}
				if(k5==-1){
					cout << "no product with this title in this category"<<endl;
					return;
				}
				for(int k3 = 0; k3 <prod.size(); k3++){
					if(prod[k3]->getTitle()== titl2){
						cout << "Enter number of field you want to edit: 1.Title 2.Description 3.Category and Subcategory 4.Price 5.Available " <<prod[k3]->getType() << " 6.Nothing"<<endl;
						int selection;
						if(cin.peek() == '\n') {
					        cin.ignore(numeric_limits<streamsize>::max(), '\n');
					    }
						cin >> selection;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						string sub;
						string attr;
						switch(selection){
							case 1:
								cout << "Enter new title:"<< endl;
								getline(cin,attr);
								prod[k3] -> setTitle(attr);
								break;
							case 2:
								cout << "Enter new descrtiption:"<<endl;
								getline(cin,attr);
								prod[k3]->setDescription(attr);
								break;
							case 3:
								cout << "Enter new category:"<<endl;
								getline(cin,attr);
								cout  <<"Enter new subcategory:"<< endl;
								getline(cin,sub);
								prod[k3]->setCategory(attr);
								prod[k3]->setSubcategory(sub);
								break;
							case 4:
								cout << "Enter new price"<<endl ;
								float pri;
								cin >> pri;
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								prod[k3]->setPrice_Per(pri);		
								break;
							case 5:
								cout << "Enter new availability :"<< endl ;
								int quantity;
								cin >> quantity;
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								prod[k3]-> setAmount(quantity);	
								break;		
							case 6:
								cout << "you chose nothing"<<endl;
								break;
							default:
								cout << "Error there isn't a " << selection << "choice" <<endl;
								break;
						}
						
						if((selection > 0) &&(selection < 6) ){
							cout << "Product updated!" << endl;
						}
					}
				}
			}
		}
	}else if(n == 3){
		cout << "Results: ";
		for(int i = 0; i<prod.size(); i++){
			cout << "\""<<prod[i]->getTitle() << "\"" << " ";
		}
		cout << endl << "Select a product title:" <<endl;
		string titl;
		int k = 0;
		getline(cin,titl);
		int i;
		for(i = 0; i < prod.size(); i++){
			if(prod[i]->getTitle()== titl){
				k = 1;
				break;
			}
		}
		if(k == 1){
			prod[i]->print_p();
			cout << "do you want to edit this product? Enter [y/n]"<<endl;
			char yes_or_no;
			cin >> yes_or_no;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if(yes_or_no != 'Y' && yes_or_no != 'y'){
				return;
			}
			cout << "Enter number of field you want to edit: 1.Title 2.Description 3.Category and Subcategory 4.Price 5.Available " <<prod[i]->getType() << " 6.Nothing"<<endl;
			int selection;
			cin >> selection;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			string attr;
			string sub;
			switch(selection){
				case 1:
					cout << "Enter new title:"<< endl;
					getline(cin,attr);
					prod[i] -> setTitle(attr);
					break;
				case 2:
					cout << "Enter new descrtiption:"<<endl;
					getline(cin,attr);
					prod[i]->setDescription(attr);
					break;
				case 3:
					cout << "Enter new category:"<<endl;
					getline(cin,attr);
					cout  <<"Enter new subcategory:"<< endl;
					getline(cin,sub);
					prod[i]->setCategory(attr);
					prod[i]->setSubcategory(sub);
					break;
				case 4:
					cout << "Enter new price"<<endl ;
					float pri;
					cin >> pri;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					prod[i]->setPrice_Per(pri);		
					break;
				case 5:
					cout << "Enter new availability :"<< endl ;
					int quantity;
					cin >> quantity;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					prod[i]-> setAmount(quantity);	
					break;		
				case 6:
					cout << "you chose nothing"<<endl;
					break;
				default:
					cout << "Error there isn't a " << selection << "choice" <<endl;
					break;
			}
			
			if((selection > 0) &&(selection < 6) ){
				cout << "Product updated!" << endl;
			}
		}else{
			cout << "couldn't find any product with the title: "<<titl << endl;
		}
	}else{
		cerr << "Error:please enter one of the given numbers" << endl;
	}
}	

void eshop::View_History(string usrnm){// opens and displays the order history for the client who wishes to review their past orders
	string filepath = "files/order_history/"+usrnm+"_history.txt";
	ifstream file4(filepath.c_str());
	if (!file4.is_open()) {
    	cerr << "Error: Could not open the file." << endl;
    	return ;
	}
	string line;
	while(getline(file4,line)){
		cout << line <<endl;
	}
	file4.close();
}

void eshop::search_product2(){//the client's search function, which operates similarly to the admin's search, but allows the client to search by category and subcategory.Clients can add products to their cart, but cannot edit any product details
	cout << " Product Search Options:"<<endl;
	cout << "1. Search for a specific product (by title)."<<endl;
	cout << "2. View the products of a specific category."<<endl;
	cout << "3. Show all the available products."<< endl;
	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if(n == 1){
		cout << "Enter the title of the product you are looking for:" << endl;
		string titl;
		int k = 0;
		getline(cin,titl);
		int i;
		for(i = 0; i < prod.size(); i++){
			if(prod[i]->getTitle()== titl){
				k = 1;
				break;
			}
		}
		if(k == 1){
			prod[i]->print_p();
			cout << "Do you want to add this product to you cart? Enter y if you want to:" <<endl;
			char j;
			cin >> j;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if(j == 'y' || j == 'Y'){
				if(prod[i]->getAmount() == 0){
					cout<< "the product: " << prod[i]->getTitle() << " is currently unavailable"<<endl;
				}else{
					cout << "Enter quantity:"<< endl;
					int quantity;
					cin >> quantity;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					if(quantity > prod[i]->getAmount()){
						cout << "all the remaining product is added in your cart " <<prod[i]->getAmount() <<endl;
						quantity = prod[i]->getAmount();
					}
					products* newProd = new products;
					string titlenew= prod[i]->getTitle();
					float pricenew= atof(prod[i]->getPrice_Per().c_str());
					newProd->setTitle(titlenew);
					newProd->setPrice_Per(pricenew);
					newProd->setAmount(quantity);
					cart.push_back(newProd);
				}
			}
		}else{
			cout << "Product not found."<<endl;
		}
	}else if(n == 2){
		cout << " Select a category from the list below :" << endl;
		printCategories();
		 if (cin.peek() == '\n') {
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	}
		string categ;
		getline(cin,categ);
		cout <<"Would you like to select a subcategory? Enter[Y/N]:"<<endl;
		char an;
		cin >>an;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if(an == 'y'|| an == 'Y'){
			cout << "Select a subcategory from the list below:"<<endl;
			printSubcategories(categ);
			string subcateg;
			getline(cin,subcateg);
			for(int j = 0; j <prod.size(); j++){
				if(prod[j]->getSubcategory() == subcateg){
					prod[j]->getTitle();
				}
			}
			cout << "Do you want to search for a product from this subcategory?Enter[y/n]:"<<endl;
			char answ;
			cin >>answ;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if(answ == 'y' || answ == 'Y'){
				cout << "Enter the title of the product you are looking for"<<endl;
				string titl2;
				getline(cin,titl2);
				for(int k7 = 0; k7 <prod.size(); k7++){
					if(prod[k7]->getSubcategory()==subcateg){
						if(prod[k7]->getTitle()==titl2){
							prod[k7]->print_p();
							cout << "Do you want to add this product to you cart? Enter y if you want to:" <<endl;
							char j;
							cin >> j;
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							if(j == 'y' || j == 'Y'){
								if(prod[k7]->getAmount() == 0){
									cout<< "the product: " << prod[k7]->getTitle() << " is currently unavailable"<<endl;
								}else{
									cout << "Enter quantity:"<< endl;
									int quantity;
									cin >> quantity;
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
									if(quantity > prod[k7]->getAmount()){
										cout << "all the remaining product is added in your cart " <<prod[k7]->getAmount() <<endl;
										quantity = prod[k7]->getAmount();
									}
									products* newProd = new products;
									string titlenew= prod[k7]->getTitle();
									float pricenew= atof(prod[k7]->getPrice_Per().c_str());
									newProd->setTitle(titlenew);
									newProd->setPrice_Per(pricenew);
									newProd->setAmount(quantity);
									cart.push_back(newProd);
								}
							}
							
						}
					}
				}
			}

		}else if(an == 'n'|| an== 'N'){
			for(int j = 0; j <prod.size(); j++){
				if(prod[j]->getCategory() == categ){
					prod[j]->getTitle();
				}
			}
			cout << "Do you want to search for a product from this category?Enter[y/n]:"<<endl;
			char answ;
			cin >>answ;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if(answ == 'y' || answ == 'Y'){
				cout << "Enter the title of the product you are looking for"<<endl;
				string titl2;
				getline(cin,titl2);
				for(int k7 = 0; k7 <prod.size(); k7++){
					if(prod[k7]->getCategory()==categ){
						if(prod[k7]->getTitle()==titl2){
							prod[k7]->print_p();
							cout << "Do you want to add this product to you cart? Enter y if you want to:" <<endl;
							char j;
							cin >> j;
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							if(j == 'y' || j == 'Y'){
								if(prod[k7]->getAmount() == 0){
									cout<< "the product: " << prod[k7]->getTitle() << " is currently unavailable"<<endl;
								}else{
									cout << "Enter quantity:"<< endl;
									int quantity;
									cin >> quantity;
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
									if(quantity > prod[k7]->getAmount()){
										cout << "all the remaining product is added in your cart " <<prod[k7]->getAmount() <<endl;
										quantity = prod[k7]->getAmount();
									}
									products* newProd = new products;
									string titlenew= prod[k7]->getTitle();
									float pricenew= atof(prod[k7]->getPrice_Per().c_str());
									newProd->setTitle(titlenew);
									newProd->setPrice_Per(pricenew);
									newProd->setAmount(quantity);
									cart.push_back(newProd);
								}
							}
							
						}
					}
				}
			}
		}
	}else if(n == 3){
		cout << "Results: ";
		for(int i = 0; i<prod.size(); i++){
			cout << "\""<<prod[i]->getTitle() << "\"" << " ";
		}
		cout << endl << "Select a product title:" <<endl;
		string titl;
		int k = 0;
		getline(cin,titl);
		int i;
		for(i = 0; i < prod.size(); i++){
			if(prod[i]->getTitle()== titl){
				k = 1;
				break;
			}
		}
		if(k == 1){
			prod[i]->print_p();
			cout << "Do you want to add this product to you cart? Enter y if you want to:" <<endl;
			char j;
			cin >> j;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if(j == 'y' || j == 'Y'){
				if(prod[i]->getAmount() == 0){
					cout<< "the product: " << prod[i]->getTitle() << " is currently unavailable"<<endl;
				}else{
					cout << "Enter quantity:"<< endl;
					int quantity;
					cin >> quantity;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					if(quantity == prod[i]->getAmount()){
						cout << "all the remaining product is added in your cart " <<prod[i]->getAmount() <<endl;
						quantity = prod[i]->getAmount();
					}
					products* newProd = new products;
					string titlenew= prod[i]->getTitle();
					float pricenew= atof(prod[i]->getPrice_Per().c_str());
					newProd->setTitle(titlenew);
					newProd->setPrice_Per(pricenew);
					newProd->setAmount(quantity);
					cart.push_back(newProd);
				}
			}			
		}else{
			cout << "couldn't find any product with the title: "<<titl << endl;
		}
	}else{
		cerr << "Error:please enter one of the given numbers" << endl;
	}
}

void eshop::View_Cart(){//the client can view his current cart but if he has pressed "complete order" then the cart is empty
	float total_cost;
	cout << "---CART START---"  <<endl;
	int amoun;
	float pri;
	for(int i = 0; i < cart.size(); i++){
		pri = atof(cart[i]->getPrice_Per().c_str());
		amoun = cart[i]->getAmount();
		total_cost += pri * amoun;
		cout << amoun << " " << cart[i]->getTitle() <<endl;
	}
	cout << "---CART END---" <<endl;
	cout << "Total Cost: " << total_cost <<endl;
}

void eshop::Confirm_Order(string usrnm){//emptys the current cart and add it to the order history of it's client
	if(cart.empty()){
		cerr << " Your cart is empty.Cannot complete order with empty cart"<<endl;
		return ;
	}
	int count;//opens and reads the client's order history to determine how many orders have been completed,allowing us to update the cart with the correct information based on the order history
	string filepath = "files/order_history/"+usrnm+"_history.txt";
	ifstream file4(filepath.c_str());
	if (!file4.is_open()) {
    	cerr << "Error: Could not open the file." << endl;
    	return ;
	}
	file4.seekg(0, ios::beg);
	if(file4.peek() == fstream::traits_type::eof()){
		count = 1;
	}else{
		file4.seekg(0, ios::beg);
		string line2;
		while(getline(file4,line2)){
			if(line2.find("CART") != string::npos){
				string number = "";
				for(int k1 = 8; k1 < line2.size(); k1++){
					if(line2[k1] == ' '){
						break;
					}
					else{
						number += line2[k1] ;
					}
				}
				count = atoi(number.c_str());
			}
		}
	}
	file4.close();
	string filepath1 = "files/order_history/"+usrnm+"_history.txt";
	ofstream file5(filepath1.c_str(), ios::app);
	++count;//so it's not the same as the last cart
	file5 <<endl<< endl <<"---CART " << count <<" START---" <<endl;
	float summ = 0;
	for(int k = 0; k < cart.size(); k++){
		file5 << cart[k]->getAmount() << " " << cart[k]->getTitle() <<endl;
		int amountt = cart[k]->getAmount();
		float pricetag = std::stof(cart[k]->getPrice_Per());
		summ += amountt * pricetag ;
	}
	file5 << "---CART " << count << " END---"<<endl;
	file5 <<  "Total Cost: " << summ <<endl << endl;
	int quantity1,quantity2;
	for(int i= 0; i <cart.size(); i++){
		for(int j =0; j < prod.size(); j++){
			if(cart[i]->getTitle()==prod[j]->getTitle()){
				quantity1 = cart[i]->getAmount();
				quantity2 = prod[j]->getAmount();
				prod[j]->setAmount(quantity2 - quantity1);
			}
		}
		delete cart[i];
	}
	cart.clear();
	file5.close();
	cout << "Order Completed!" <<endl;
}

void eshop::Remove_Product(){//removes product from the cart
	//and checks for incorrect inputs
	cout << "Which product do you want to remove from your cart? " <<endl;
	string titl;
	getline(cin,titl);
	int i,n=0;
	for( i = 0; i<cart.size(); i++){
		if(titl == cart[i]->getTitle()){
			n = 1;
			break;
		}
	}
	if(n==1){
		int i3 = -1;
		for (int i2 = 0; i2 != cart.size(); ++i2) {
			if (cart[i2]->getTitle() == titl) {
				i3 = i2;
				break;
			}
		}
		if(i3 != -1){
			delete cart[i3];
			cart.erase(cart.begin() + i3);
		}
	}
	else{
		cout << "there is no product in your cart with title:" << titl;
	}
}

void eshop::Edit_Cart(){//edits the client's cart, ensuring that the requested quantity does not exceed the available stock of the product
	cout << "Which product do you want to update?" <<endl;
	int n = 0,i;
	string product;
	getline(cin,product);
	for(i = 0; i <cart.size(); i++){
		if(product == cart[i]->getTitle()){
			n = 1;
			break;
		}
	}
	if(n == 1){	
		int j;
		for( j = 0; j< prod.size(); j++){
			if(product == prod[j]->getTitle()){
				break;
			}
		}
		if(prod[j]->getAmount()==0){
			cout << "Sorry there is no remaining of this product please try again later."<<endl;
		}
		else{
			cout << "Enter new quantity:" <<endl;
			int quantity; // float h int
			cin >> quantity;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if(quantity>cart[i]->getAmount()){
				if(prod[j]->getAmount()< quantity){	
					cout << "all of the remaining product is added in your cart " <<prod[j]->getAmount() <<endl;
					quantity = prod[j]->getAmount();
					cart[i]->setAmount(quantity);
				}
				else{
					cart[i]->setAmount(quantity);
				}
			}
			else{
				cart[i]->setAmount(quantity);
			}			
		}
	}
	else{
		cout << "There is no product with the title " << product << "in your cart" <<endl;
	}
}

void eshop::Add_Product_cl(){//adds a product to the client's cart and ensures again that the requested quantity does not exceed the available stock of the product
	cout << "Which product do you want to add? " << endl;
	string product;
	getline(cin,product);
	int n = 0,i;
	for(i = 0; i< prod.size(); i++){
		if(prod[i]->getTitle() == product){
			n = 1;
			break;
		}
	}
	if(n == 1){
		if(prod[i]->getAmount() == 0){
			cout<< "the product: " << prod[i]->getTitle() << " is currently unavailable"<<endl;
		}else{
			cout << "Enter quantity:"<< endl;
			int quantity;//den kserw an to quantity einai float h int
			cin >> quantity;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if(quantity > prod[i]->getAmount()){
				cout << "all the remaining product is added in your cart " <<prod[i]->getAmount() <<endl;
				quantity = prod[i]->getAmount();
			}
			products* newProd = new products;
			//newProd = prod[i];
			string titlenew= prod[i]->getTitle();
			float pricenew= atof(prod[i]->getPrice_Per().c_str());
			newProd->setTitle(titlenew);
			newProd->setPrice_Per(pricenew);
			newProd->setAmount(quantity);
			cart.push_back(newProd);
		}
	}else{
		cout << "there is no product with the name:"<<product;
	}

}
//the remaining functions assist with the implementation of the code
int eshop::userfound(string found){
	for(int i = 0; i< users.size(); i ++){
		if(users[i]->getUsername() == found){
			return 1;
		}
	}
	return 0;
}
void user::setUsername(string usr) {
    username = usr;
}

void user::setPass(string pass) {
    password = pass;
}

void user::setIsadmin(int admi){
    isAdmin = admi;
}

void user::print(){
    cout << username << " " << password << " " << isAdmin << endl;
}



int main(int argc, char* argv[]){
	if (argc != 4) {
		cerr << "Error: Wrong number of arguments provided " << endl;
		return 1;
    }
	cout << "Welcome to the e-shop!!!"<<endl;
	file_path_categ = argv[1];
	file_path_prod = argv[2];
	file_path_user = argv[3];
    eshop eshop1;//we use these files in many functions so we open and we close them and we use ifstream , ofstream or fstream for whatever reason we need them in each function
    eshop1.userfile_vector();
    eshop1.productfile_vector();
	string ad_or_cl = eshop1.login_register();
    
    while(ad_or_cl == "error"){//do it till login_register doesn't return error .If it does then the user just entered something wrong
    	


	ad_or_cl = eshop1.login_register();//If the user logged in then it will return "admin" if he's an admin or his username if he is a client
	}
	int menu_opt;
	if(ad_or_cl != "admin"){
		//client
		if(eshop1.userfound(ad_or_cl) == 0){
			cout << " mpulhs "<<endl;//Just to make sure that ad_or_cl is the client's username
			return 1;
		}
		int ending = -1;
		client_menu();
		cin >> menu_opt;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');//we use this because when we mix getline(cin,...) and cin the input buffer can leave a newline charachter in the buffer.
		while(menu_opt != 8){
			switch(menu_opt){
				case 1://these are the different actions available to the cliennt
					eshop1.search_product2();
					cout <<endl;
					break;
				case 2:
					eshop1.Add_Product_cl();
					cout <<endl;
					break;
				case 3:
					eshop1.Edit_Cart();
					cout <<endl;
					break;
				case 4:
					eshop1.Remove_Product();
					cout <<endl;
					break;
				case 5:
					eshop1.Confirm_Order(ad_or_cl);
					cout <<endl;
					break;
				case 6:
					eshop1.View_History(ad_or_cl);
					cout <<endl;
					break;
				case 7:
					eshop1.View_Cart();
					cout <<endl;
					break;
				case 8:
					ending == 0;
					cout <<endl;
					break;
				default:
					break;
				
			}
			if(ending== 0){
				break;
			}
			client_menu();
			cin >> menu_opt;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}else{
		//admin
		int ending = -1;
		admin_menu();
		cin >> menu_opt;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while(menu_opt != 7){//these are the different actions available to the admin 
			switch(menu_opt){
				case 1:
					eshop1.addProduct_adm();
					cout <<endl;
					break;
				case 2:
					eshop1.editProduct();
					cout <<endl;
					break;
				case 3:
					eshop1.removeProduct();
					cout <<endl;
					break;
				case 4:
					eshop1.search_product();
					cout <<endl;
					break;
				case 5:
					eshop1.unavailable_p();
					cout <<endl;
					break;
				case 6:
					eshop1.top5_products();
					cout <<endl;
					break;
				case 7:
					ending = 0;
				default:
					cout << "Enter only 1 to 7"<<endl<<endl;
					break;
			}
			
			if(ending == 0){
				break;
			}
			admin_menu();
			cin >> menu_opt;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
			
	}
    eshop1.vector_toproductfile();
    eshop1.vector_tousersfile();
    
	return 0;
    

}


